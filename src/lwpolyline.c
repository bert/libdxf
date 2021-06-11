/*!
 * \file lwpolyline.c
 *
 * \author Copyright (C) 2008, 2010, 2012, 2014, 2015, 2017, 2018, 2019,
 * 2020 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \author Copyright (C) 2010 by Luis Matos <gass@otiliamatos.ath.cx>.
 *
 * \brief Functions for a DXF light weight polyline entity (\c LWPOLYLINE).
 *
 * \warning This entity requires AutoCAD version R14 or higher.
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


#include "lwpolyline.h"


/*!
 * \brief Allocate memory for a DXF \c LWPOLYLINE entity.
 *
 * Fill the memory contents with zeros.
 * 
 * \return a pointer to the DXF \c LWPOLYLINE entity.
 */
DxfLWPolyline *
dxf_lwpolyline_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfLWPolyline *lwpolyline = NULL;
        size_t size;

        size = sizeof (DxfLWPolyline);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((lwpolyline = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfLWPolyline struct.\n")),
                  __FUNCTION__);
                lwpolyline = NULL;
        }
        else
        {
                memset (lwpolyline, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lwpolyline);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF
 * \c LWPOLYLINE entity.
 *
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfLWPolyline *
dxf_lwpolyline_init
(
        DxfLWPolyline *lwpolyline
                /*!< a pointer to the DXF \c LWPOLYLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lwpolyline == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                lwpolyline = dxf_lwpolyline_new ();
        }
        if (lwpolyline == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory for a DxfLWPolyline struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        /* Assign initial values to members. */
        lwpolyline->id_code = 0;
        lwpolyline->linetype = strdup (DXF_DEFAULT_LINETYPE);
        lwpolyline->layer = strdup (DXF_DEFAULT_LAYER);
        lwpolyline->elevation = 0.0;
        lwpolyline->thickness = 0.0;
        lwpolyline->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        lwpolyline->visibility = DXF_DEFAULT_VISIBILITY;
        lwpolyline->constant_width = 0.0;
        lwpolyline->color = DXF_COLOR_BYLAYER;
        lwpolyline->paperspace = DXF_MODELSPACE;
        lwpolyline->graphics_data_size = 0;
        lwpolyline->shadow_mode = 0;
        lwpolyline->dictionary_owner_soft = strdup ("");
        lwpolyline->object_owner_soft = strdup ("");
        lwpolyline->material = strdup ("");
        lwpolyline->dictionary_owner_hard = strdup ("");
        lwpolyline->lineweight = 0;
        lwpolyline->plot_style_name = strdup ("");
        lwpolyline->color_value = 0;
        lwpolyline->color_name = strdup ("");
        lwpolyline->transparency = 0;
        lwpolyline->constant_width = 0.0;
        lwpolyline->flag = 0;
        lwpolyline->number_vertices = 0;
        lwpolyline->extr_x0 = 0.0;
        lwpolyline->extr_y0 = 0.0;
        lwpolyline->extr_z0 = 0.0;
        /* Initialize new structs for the following members later,
         * when they are required and when we have content. */
        lwpolyline->binary_graphics_data = NULL;
        lwpolyline->vertices = NULL;
        lwpolyline->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lwpolyline);
}


/*!
 * \brief Read data from a DXF file into an \c LWPOLYLINE entity.
 *
 * The last line read from file contained the string "LWPOLYLINE". \n
 * Now follows some data for the \c LWPOLYLINE, to be terminated with a
 * "  0" string announcing the following entity, or the end of the
 * \c ENTITY section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c lwpolyline. \n
 *
 * \return a pointer to \c lwpolyline.
 */
DxfLWPolyline *
dxf_lwpolyline_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfLWPolyline *lwpolyline
                /*!< a pointer to the DXF \c LWPOLYLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *temp_string = NULL;
        DxfVertex *iter = NULL;

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
        if (lwpolyline == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                lwpolyline = dxf_lwpolyline_init (lwpolyline);
        }
        if (lwpolyline->binary_graphics_data == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfBinaryData struct.\n")));
                lwpolyline->binary_graphics_data = dxf_binary_data_init (lwpolyline->binary_graphics_data);
                if (lwpolyline->binary_graphics_data == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        if (lwpolyline->vertices == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfVertex struct.\n")));
                lwpolyline->vertices = (struct DxfVertex *) dxf_vertex_init ((DxfVertex *) lwpolyline->vertices);
                if (lwpolyline->vertices == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        iter = (DxfVertex *) lwpolyline->vertices;
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
                        fscanf (fp->fp, "%x\n", (uint *) &lwpolyline->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, lwpolyline->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, lwpolyline->layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                        * X-coordinate of a vertex. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &iter->p0->x0);
                        /*! \todo Create a pointer to the next DxfVertex if and when required. */
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                        * Y-coordinate of a vertex. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &iter->p0->y0);
                        /*! \todo Create a pointer to the next DxfVertex if and when required. */
                }
                else if ((fp->acad_version_number <= AutoCAD_11)
                        && (strcmp (temp_string, "38") == 0)
                        && (lwpolyline->elevation != 0.0))
                {
                        /* Now follows a string containing the
                         * elevation. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &lwpolyline->elevation);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &lwpolyline->thickness);
                }
                else if (strcmp (temp_string, "40") == 0)
                {
                        /* Now follows a string containing the
                         * start width of the vertex. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &iter->start_width);
                }
                else if (strcmp (temp_string, "41") == 0)
                {
                        /* Now follows a string containing the
                         * start width of the vertex. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &iter->end_width);
                }
                else if (strcmp (temp_string, "42") == 0)
                {
                        /* Now follows a string containing the bulge of
                         * the vertex. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &iter->bulge);
                        /* The last member of the vertex is read.\n */
                        /*! \todo The pointer administration needs to be checked for functionality. */
                         /* Increment iter to next DxfVertex. */
                        iter->next = (struct DxfVertex *) dxf_vertex_new ();
                        iter = (DxfVertex *) iter->next;
                }
                else if (strcmp (temp_string, "43") == 0)
                {
                        /* Now follows a string containing the
                         * constant width. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &lwpolyline->constant_width);
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing the linetype
                         * scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &lwpolyline->linetype_scale);
                }
                else if (strcmp (temp_string, "60") == 0)
                {
                        /* Now follows a string containing the
                         * visibility value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &lwpolyline->visibility);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &lwpolyline->color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &lwpolyline->paperspace);
                }
                else if (strcmp (temp_string, "70") == 0)
                {
                        /* Now follows a string containing the
                         * flag value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &lwpolyline->flag);
                }
                else if (strcmp (temp_string, "90") == 0)
                {
                        /* Now follows a string containing the number
                         * of following vertices. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &lwpolyline->number_vertices);
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
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                }
                else if (strcmp (temp_string, "210") == 0)
                {
                        /* Now follows a string containing the
                         * X-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &lwpolyline->extr_x0);
                }
                else if (strcmp (temp_string, "220") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &lwpolyline->extr_y0);
                }
                else if (strcmp (temp_string, "230") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &lwpolyline->extr_z0);
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing Soft-pointer
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, lwpolyline->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, lwpolyline->dictionary_owner_hard);
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
        /*! \todo Free memory to the last (unused) vertex in the linked list. */

        /* Set the pointer to the last (unused) vertex in the linked list to NULL. */
        iter->next = NULL;
        /* Handle omitted members and/or illegal values. */
        if (strcmp (lwpolyline->linetype, "") == 0)
        {
                lwpolyline->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (lwpolyline->layer, "") == 0)
        {
                lwpolyline->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Clean up. */
        free (temp_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lwpolyline);
}


/*!
 * \brief Write DXF output to fp for a light weight polyline entity.
 *
 * \warning This entity requires AutoCAD version R14 or higher.
 * When the \c follow_strict_version_rules flag is set to \c TRUE in the
 * \c DxfFile struct, this entity will be skipped from file.
 * When the \c follow_strict_version_rules flag is set to \c FALSE in the
 * \c DxfFile struct, libdxf will write this entity to file and report
 * with a warning message to \c stderr.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_lwpolyline_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfLWPolyline *lwpolyline
                /*!< a pointer to the DXF \c LWPOLYLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("LWPOLYLINE");
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
        if (lwpolyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (lwpolyline->vertices == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if ((fp->acad_version_number < AutoCAD_14)
          && (fp->follow_strict_version_rules))
        {
                fprintf (stderr,
                  (_("Error in %s () illegal DXF version for this %s entity with id-code: %x.\n")),
                  __FUNCTION__, dxf_entity_name, lwpolyline->id_code);
                return (EXIT_FAILURE);
        }
        else
        {
                fprintf (stderr,
                  (_("Warning in %s () illegal DXF version for this %s entity with id-code: %x.\n")),
                  __FUNCTION__, dxf_entity_name, lwpolyline->id_code);
        }
        if (strcmp (lwpolyline->linetype, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty linetype string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, lwpolyline->id_code);
                fprintf (stderr,
                  (_("\t%s entity is reset to default linetype")),
                  dxf_entity_name);
                lwpolyline->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (lwpolyline->layer, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, lwpolyline->id_code);
                fprintf (stderr,
                  (_("\t%s entity is relocated to layer 0\n")),
                  dxf_entity_name);
                lwpolyline->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (lwpolyline->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", lwpolyline->id_code);
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
        if ((strcmp (lwpolyline->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", lwpolyline->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (lwpolyline->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", lwpolyline->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
        }
        if (lwpolyline->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%d\n", (int16_t) DXF_PAPERSPACE);
        }
        fprintf (fp->fp, "  8\n%s\n", lwpolyline->layer);
        if (strcmp (lwpolyline->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", lwpolyline->linetype);
        }
        if (lwpolyline->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", lwpolyline->color);
        }
        if (lwpolyline->linetype_scale != 1.0)
        {
                fprintf (fp->fp, " 48\n%f\n", lwpolyline->linetype_scale);
        }
        if (lwpolyline->visibility != 0)
        {
                fprintf (fp->fp, " 60\n%d\n", lwpolyline->visibility);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbPolyline\n");
        }
        fprintf (fp->fp, " 90\n%d\n", lwpolyline->number_vertices);
        fprintf (fp->fp, " 70\n%d\n", lwpolyline->flag);
        fprintf (fp->fp, " 43\n%f\n", lwpolyline->constant_width);
        if (lwpolyline->elevation != 0.0)
        {
                fprintf (fp->fp, " 38\n%f\n", lwpolyline->elevation);
        }
        if (lwpolyline->thickness != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", lwpolyline->thickness);
        }
        /* Start of writing (multiple) vertices. */
        iter = (DxfVertex *) lwpolyline->vertices;
        while (iter != NULL)
        {
                if (iter->p0 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () a NULL pointer was found.\n")),
                          __FUNCTION__);
                        return (EXIT_FAILURE);
                }
                fprintf (fp->fp, " 10\n%f\n", iter->p0->x0);
                fprintf (fp->fp, " 20\n%f\n", iter->p0->y0);
                if ((iter->start_width != lwpolyline->constant_width)
                  || (iter->end_width != lwpolyline->constant_width))
                {
                        fprintf (fp->fp, " 40\n%f\n", iter->start_width);
                        fprintf (fp->fp, " 41\n%f\n", iter->end_width);
                }
                fprintf (fp->fp, " 42\n%f\n", iter->bulge);
                iter = (DxfVertex *) iter->next;
        }
        /* End of writing (multiple) vertices. */
        if (fp->acad_version_number >= AutoCAD_12)
        {
                fprintf (fp->fp, "210\n%f\n", lwpolyline->extr_x0);
                fprintf (fp->fp, "220\n%f\n", lwpolyline->extr_y0);
                fprintf (fp->fp, "230\n%f\n", lwpolyline->extr_z0);
        }
        /* Clean up. */
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c LWPOLYLINE and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_lwpolyline_free
(
        DxfLWPolyline *lwpolyline
                /*!< a pointer to the DXF \c LWPOLYLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lwpolyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (lwpolyline->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (lwpolyline->linetype);
        free (lwpolyline->layer);
        free (lwpolyline);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c LWPOLYLINE entities and all their data fields.
 */
void
dxf_lwpolyline_free_list
(
        DxfLWPolyline *lwpolylines
                /*!< a pointer to the single linked list of DXF
                 * \c LWPOLYLINE entities. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (lwpolylines == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (lwpolylines != NULL)
        {
                DxfLWPolyline *iter = (DxfLWPolyline *) lwpolylines->next;
                dxf_lwpolyline_free (lwpolylines);
                lwpolylines = (DxfLWPolyline *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the ID code from a DXF \c LWPOLYLINE entity.
 *
 * \return ID code.
 */
int
dxf_lwpolyline_get_id_code
(
        DxfLWPolyline *lwpolyline
                /*!< a pointer to a DXF \c LWPOLYLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lwpolyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (lwpolyline->id_code < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lwpolyline->id_code);
}


/*!
 * \brief Set the ID code for a DXF \c LWPOLYLINE entity.
 */
DxfLWPolyline *
dxf_lwpolyline_set_id_code
(
        DxfLWPolyline *lwpolyline,
                /*!< a pointer to a DXF \c LWPOLYLINE entity. */
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
        if (lwpolyline == NULL)
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
        lwpolyline->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lwpolyline);
}


/*!
 * \brief Get the linetype from a DXF \c LWPOLYLINE entity.
 *
 * \return linetype when sucessful, \c NULL when an error occurred.
 */
char *
dxf_lwpolyline_get_linetype
(
        DxfLWPolyline *lwpolyline
                /*!< a pointer to a DXF \c LWPOLYLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lwpolyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (lwpolyline->linetype ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (lwpolyline->linetype));
}


/*!
 * \brief Set the linetype for a DXF \c LWPOLYLINE entity.
 */
DxfLWPolyline *
dxf_lwpolyline_set_linetype
(
        DxfLWPolyline *lwpolyline,
                /*!< a pointer to a DXF \c LWPOLYLINE entity. */
        char *linetype
                /*!< a string containing the linetype for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lwpolyline == NULL)
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
        lwpolyline->linetype = strdup (linetype);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lwpolyline);
}


/*!
 * \brief Get the layer from a DXF \c LWPOLYLINE entity.
 *
 * \return layer when sucessful, \c NULL when an error occurred.
 */
char *
dxf_lwpolyline_get_layer
(
        DxfLWPolyline *lwpolyline
                /*!< a pointer to a DXF \c LWPOLYLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lwpolyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (lwpolyline->layer ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (lwpolyline->layer));
}


/*!
 * \brief Set the layer for a DXF \c LWPOLYLINE entity.
 */
DxfLWPolyline *
dxf_lwpolyline_set_layer
(
        DxfLWPolyline *lwpolyline,
                /*!< a pointer to a DXF \c LWPOLYLINE entity. */
        char *layer
                /*!< a string containing the layer for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lwpolyline == NULL)
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
        lwpolyline->layer = strdup (layer);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lwpolyline);
}


/*!
 * \brief Get the elevation from a DXF \c LWPOLYLINE entity.
 *
 * \return \c elevation.
 */
double
dxf_lwpolyline_get_elevation
(
        DxfLWPolyline *lwpolyline
                /*!< a pointer to a DXF \c LWPOLYLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lwpolyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lwpolyline->elevation);
}


/*!
 * \brief Set the elevation for a DXF \c LWPOLYLINE entity.
 */
DxfLWPolyline *
dxf_lwpolyline_set_elevation
(
        DxfLWPolyline *lwpolyline,
                /*!< a pointer to a DXF \c LWPOLYLINE entity. */
        double elevation
                /*!< the elevation to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lwpolyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        lwpolyline->elevation = elevation;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lwpolyline);
}


/*!
 * \brief Get the thickness from a DXF \c LWPOLYLINE entity.
 *
 * \return \c thickness.
 */
double
dxf_lwpolyline_get_thickness
(
        DxfLWPolyline *lwpolyline
                /*!< a pointer to a DXF \c LWPOLYLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lwpolyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (lwpolyline->thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lwpolyline->thickness);
}


/*!
 * \brief Set the thickness for a DXF \c LWPOLYLINE entity.
 */
DxfLWPolyline *
dxf_lwpolyline_set_thickness
(
        DxfLWPolyline *lwpolyline,
                /*!< a pointer to a DXF \c LWPOLYLINE entity. */
        double thickness
                /*!< the thickness to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lwpolyline == NULL)
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
        lwpolyline->thickness = thickness;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lwpolyline);
}


/*!
 * \brief Get the linetype scale from a DXF \c LWPOLYLINE entity.
 *
 * \return \c linetype scale.
 */
double
dxf_lwpolyline_get_linetype_scale
(
        DxfLWPolyline *lwpolyline
                /*!< a pointer to a DXF \c LWPOLYLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lwpolyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (lwpolyline->linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lwpolyline->linetype_scale);
}


/*!
 * \brief Set the linetype scale for a DXF \c LWPOLYLINE entity.
 */
DxfLWPolyline *
dxf_lwpolyline_set_linetype_scale
(
        DxfLWPolyline *lwpolyline,
                /*!< a pointer to a DXF \c LWPOLYLINE entity. */
        double linetype_scale
                /*!< the linetype scale to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lwpolyline == NULL)
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
        lwpolyline->linetype_scale = linetype_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lwpolyline);
}


/*!
 * \brief Get the visibility from a DXF \c LWPOLYLINE entity.
 *
 * \return \c visibility.
 */
int16_t
dxf_lwpolyline_get_visibility
(
        DxfLWPolyline *lwpolyline
                /*!< a pointer to a DXF \c LWPOLYLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lwpolyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (lwpolyline->visibility < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (lwpolyline->visibility > 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lwpolyline->visibility);
}


/*!
 * \brief Set the visibility for a DXF \c LWPOLYLINE entity.
 */
DxfLWPolyline *
dxf_lwpolyline_set_visibility
(
        DxfLWPolyline *lwpolyline,
                /*!< a pointer to a DXF \c LWPOLYLINE entity. */
        int16_t visibility
                /*!< the visibility to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lwpolyline == NULL)
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
        lwpolyline->visibility = visibility;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lwpolyline);
}


/*!
 * \brief Get the color from a DXF \c LWPOLYLINE entity.
 *
 * \return \c color.
 */
int
dxf_lwpolyline_get_color
(
        DxfLWPolyline *lwpolyline
                /*!< a pointer to a DXF \c LWPOLYLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lwpolyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (lwpolyline->color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lwpolyline->color);
}


/*!
 * \brief Set the color for a DXF \c LWPOLYLINE entity.
 */
DxfLWPolyline *
dxf_lwpolyline_set_color
(
        DxfLWPolyline *lwpolyline,
                /*!< a pointer to a DXF \c LWPOLYLINE entity. */
        int color
                /*!< the color to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lwpolyline == NULL)
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
        lwpolyline->color = color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lwpolyline);
}


/*!
 * \brief Get the paperspace flag value from a DXF \c LWPOLYLINE entity.
 *
 * \return paperspace flag value.
 */
int
dxf_lwpolyline_get_paperspace
(
        DxfLWPolyline *lwpolyline
                /*!< a pointer to a DXF \c LWPOLYLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lwpolyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (lwpolyline->paperspace < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (lwpolyline->paperspace > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lwpolyline->paperspace);
}


/*!
 * \brief Set the paperspace flag for a DXF \c LWPOLYLINE entity.
 */
DxfLWPolyline *
dxf_lwpolyline_set_paperspace
(
        DxfLWPolyline *lwpolyline,
                /*!< a pointer to a DXF \c LWPOLYLINE entity. */
        int paperspace
                /*!< the paperspace flag value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lwpolyline == NULL)
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
        lwpolyline->paperspace = paperspace;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lwpolyline);
}


/*!
 * \brief Get the \c graphics_data_size value from a DXF \c LWPOLYLINE
 * entity.
 *
 * \return \c graphics_data_size value when successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
int32_t
dxf_lwpolyline_get_graphics_data_size
(
        DxfLWPolyline *lwpolyline
                /*!< a pointer to a DXF \c LWPOLYLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lwpolyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (lwpolyline->graphics_data_size < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (lwpolyline->graphics_data_size == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lwpolyline->graphics_data_size);
}


/*!
 * \brief Set the \c graphics_data_size value for a DXF \c LWPOLYLINE
 * entity.
 *
 * \return a pointer to \c lwpolyline when successful, or \c NULL when
 * an error occurred.
 */
DxfLWPolyline *
dxf_lwpolyline_set_graphics_data_size
(
        DxfLWPolyline *lwpolyline,
                /*!< a pointer to a DXF \c LWPOLYLINE entity. */
        int32_t graphics_data_size
                /*!< the \c graphics_data_size value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lwpolyline == NULL)
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
        lwpolyline->graphics_data_size = graphics_data_size;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lwpolyline);
}


/*!
 * \brief Get the \c shadow_mode from a DXF \c LWPOLYLINE entity.
 *
 * \return \c shadow_mode when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_lwpolyline_get_shadow_mode
(
        DxfLWPolyline *lwpolyline
                /*!< a pointer to a DXF \c LWPOLYLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lwpolyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (lwpolyline->shadow_mode < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (lwpolyline->shadow_mode > 3)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lwpolyline->shadow_mode);
}


/*!
 * \brief Set the \c shadow_mode for a DXF \c LWPOLYLINE entity.
 *
 * \return a pointer to \c lwpolyline when successful, or \c NULL when an
 * error occurred.
 */
DxfLWPolyline *
dxf_lwpolyline_set_shadow_mode
(
        DxfLWPolyline *lwpolyline,
                /*!< a pointer to a DXF \c LWPOLYLINE entity. */
        int16_t shadow_mode
                /*!< the shadow mode to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lwpolyline == NULL)
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
        lwpolyline->shadow_mode = shadow_mode;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lwpolyline);
}


/*!
 * \brief Get the pointer to the \c binary_graphics_data from a DXF
 * \c LWPOLYLINE entity.
 *
 * \return pointer to the \c binary_graphics_data.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfBinaryData *
dxf_lwpolyline_get_binary_graphics_data
(
        DxfLWPolyline *lwpolyline
                /*!< a pointer to a DXF \c LWPOLYLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lwpolyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (lwpolyline->binary_graphics_data ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfBinaryData *) lwpolyline->binary_graphics_data);
}


/*!
 * \brief Set the pointer to the \c binary_graphics_data for a DXF
 * \c LWPOLYLINE entity.
 */
DxfLWPolyline *
dxf_lwpolyline_set_binary_graphics_data
(
        DxfLWPolyline *lwpolyline,
                /*!< a pointer to a DXF \c LWPOLYLINE entity. */
        DxfBinaryData *data
                /*!< a string containing the pointer to the
                 * \c binary_graphics_data for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lwpolyline == NULL)
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
        lwpolyline->binary_graphics_data = (DxfBinaryData *) data;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lwpolyline);
}


/*!
 * \brief Get the soft pointer to the dictionary owner from a DXF 
 * \c LWPOLYLINE entity.
 *
 * \return soft pointer to the dictionary owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_lwpolyline_get_dictionary_owner_soft
(
        DxfLWPolyline *lwpolyline
                /*!< a pointer to a DXF \c LWPOLYLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lwpolyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (lwpolyline->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (lwpolyline->dictionary_owner_soft));
}


/*!
 * \brief Set the pointer to the dictionary_owner_soft for a DXF
 * \c LWPOLYLINE entity.
 */
DxfLWPolyline *
dxf_lwpolyline_set_dictionary_owner_soft
(
        DxfLWPolyline *lwpolyline,
                /*!< a pointer to a DXF \c LWPOLYLINE entity. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the
                 * dictionary_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lwpolyline == NULL)
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
        lwpolyline->dictionary_owner_soft = strdup (dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lwpolyline);
}


/*!
 * \brief Get the pointer to the \c material from a DXF \c LWPOLYLINE entity.
 *
 * \return a pointer to \c material when successful, or \c NULL when an
 * error occurred.
 *
 * \warning No checks are performed on the returned pointer.
 */
char *
dxf_lwpolyline_get_material
(
        DxfLWPolyline *lwpolyline
                /*!< a pointer to a DXF \c LWPOLYLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lwpolyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (lwpolyline->material ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (lwpolyline->material));
}


/*!
 * \brief Set the pointer to the \c material for a DXF \c LWPOLYLINE
 * entity.
 *
 * \return a pointer to \c lwpolyline when successful, or \c NULL when
 * an error occurred.
 */
DxfLWPolyline *
dxf_lwpolyline_set_material
(
        DxfLWPolyline *lwpolyline,
                /*!< a pointer to a DXF \c LWPOLYLINE entity. */
        char *material
                /*!< a string containing the pointer to the \c
                 * material for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lwpolyline == NULL)
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
        lwpolyline->material = strdup (material);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lwpolyline);
}


/*!
 * \brief Get the hard pointer to the dictionary owner from a DXF 
 * \c LWPOLYLINE entity.
 *
 * \return hard pointer to the dictionary owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_lwpolyline_get_dictionary_owner_hard
(
        DxfLWPolyline *lwpolyline
                /*!< a pointer to a DXF \c LWPOLYLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lwpolyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (lwpolyline->dictionary_owner_hard ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (lwpolyline->dictionary_owner_hard));
}


/*!
 * \brief Set the pointer to the dictionary_owner_hard for a DXF
 * \c LWPOLYLINE entity.
 */
DxfLWPolyline *
dxf_lwpolyline_set_dictionary_owner_hard
(
        DxfLWPolyline *lwpolyline,
                /*!< a pointer to a DXF \c LWPOLYLINE entity. */
        char *dictionary_owner_hard
                /*!< a string containing the pointer to the
                 * dictionary_owner_hard for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lwpolyline == NULL)
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
        lwpolyline->dictionary_owner_hard = strdup (dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lwpolyline);
}


/*!
 * \brief Get the \c lineweight from a DXF \c LWPOLYLINE entity.
 *
 * \return \c lineweight when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_lwpolyline_get_lineweight
(
        DxfLWPolyline *lwpolyline
                /*!< a pointer to a DXF \c LWPOLYLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lwpolyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lwpolyline->lineweight);
}


/*!
 * \brief Set the \c lineweight for a DXF \c LWPOLYLINE entity.
 *
 * \return a pointer to \c lwpolyline when successful, or \c NULL when
 * an error occurred.
 */
DxfLWPolyline *
dxf_lwpolyline_set_lineweight
(
        DxfLWPolyline *lwpolyline,
                /*!< a pointer to a DXF \c LWPOLYLINE entity. */
        int16_t lineweight
                /*!< the \c lineweight to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lwpolyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        lwpolyline->lineweight = lineweight;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lwpolyline);
}


/*!
 * \brief Get the \c plot_style_name from a DXF \c LWPOLYLINE entity.
 *
 * \return a pointer to \c plot_style_name when sucessful, or \c NULL
 * when an error occurred.
 */
char *
dxf_lwpolyline_get_plot_style_name
(
        DxfLWPolyline *lwpolyline
                /*!< a pointer to a DXF \c LWPOLYLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lwpolyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (lwpolyline->plot_style_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (lwpolyline->plot_style_name));
}


/*!
 * \brief Set the \c plot_style_name for a DXF \c LWPOLYLINE entity.
 *
 * \return a pointer to \c lwpolyline when successful, or \c NULL when
 * an error occurred.
 */
DxfLWPolyline *
dxf_lwpolyline_set_plot_style_name
(
        DxfLWPolyline *lwpolyline,
                /*!< a pointer to a DXF \c LWPOLYLINE entity. */
        char *plot_style_name
                /*!< a string containing the \c plot_style_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lwpolyline == NULL)
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
        lwpolyline->plot_style_name = strdup (plot_style_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lwpolyline);
}


/*!
 * \brief Get the \c color_value from a DXF \c LWPOLYLINE entity.
 *
 * \return \c color_value when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int32_t
dxf_lwpolyline_get_color_value
(
        DxfLWPolyline *lwpolyline
                /*!< a pointer to a DXF \c LWPOLYLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lwpolyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lwpolyline->color_value);
}


/*!
 * \brief Set the \c color_value for a DXF \c LWPOLYLINE entity.
 *
 * \return a pointer to \c lwpolyline when successful, or \c NULL when an
 * error occurred.
 */
DxfLWPolyline *
dxf_lwpolyline_set_color_value
(
        DxfLWPolyline *lwpolyline,
                /*!< a pointer to a DXF \c LWPOLYLINE entity. */
        int32_t color_value
                /*!< the \c color_value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lwpolyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        lwpolyline->color_value = color_value;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lwpolyline);
}


/*!
 * \brief Get the \c color_name from a DXF \c LWPOLYLINE entity.
 *
 * \return \c color_name when sucessful, or \c NULL when an error
 * occurred.
 */
char *
dxf_lwpolyline_get_color_name
(
        DxfLWPolyline *lwpolyline
                /*!< a pointer to a DXF \c LWPOLYLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lwpolyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (lwpolyline->color_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (lwpolyline->color_name));
}


/*!
 * \brief Set the \c color_name for a DXF \c LWPOLYLINE entity.
 *
 * \return a pointer to \c lwpolyline when successful, or \c NULL when an
 * error occurred.
 */
DxfLWPolyline *
dxf_lwpolyline_set_color_name
(
        DxfLWPolyline *lwpolyline,
                /*!< a pointer to a DXF \c LWPOLYLINE entity. */
        char *color_name
                /*!< a string containing the \c color_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lwpolyline == NULL)
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
        lwpolyline->color_name = strdup (color_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lwpolyline);
}


/*!
 * \brief Get the \c transparency from a DXF \c LWPOLYLINE entity.
 *
 * \return \c transparency when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int32_t
dxf_lwpolyline_get_transparency
(
        DxfLWPolyline *lwpolyline
                /*!< a pointer to a DXF \c LWPOLYLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lwpolyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lwpolyline->transparency);
}


/*!
 * \brief Set the \c transparency for a DXF \c LWPOLYLINE entity.
 *
 * \return a pointer to \c lwpolyline when successful, or \c NULL when an
 * error occurred.
 */
DxfLWPolyline *
dxf_lwpolyline_set_transparency
(
        DxfLWPolyline *lwpolyline,
                /*!< a pointer to a DXF \c LWPOLYLINE entity. */
        int32_t transparency
                /*!< the \c transparency to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lwpolyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        lwpolyline->transparency = transparency;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lwpolyline);
}


/*!
 * \brief Get the \c constant_width of a DXF \c LWPOLYLINE entity.
 *
 * \return the \c constant_width.
 */
double
dxf_lwpolyline_get_constant_width
(
        DxfLWPolyline *lwpolyline
                /*!< a pointer to a DXF \c LWPOLYLINE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (lwpolyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (lwpolyline->constant_width < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lwpolyline->constant_width);
}


/*!
 * \brief Set the Z-value of the center point \c z0 of a DXF
 * \c LWPOLYLINE entity.
 *
 * \return a pointer to \c lwpolyline when successful, or \c NULL when
 * an error occurred.
 */
DxfLWPolyline *
dxf_lwpolyline_set_constant_width
(
        DxfLWPolyline *lwpolyline,
                /*!< a pointer to a DXF \c LWPOLYLINE entity. */
        double constant_width
                /*!< the \c constant_width of a DXF \c LWPOLYLINE
                 * entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lwpolyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (lwpolyline->constant_width < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        lwpolyline->constant_width = constant_width;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lwpolyline);
}


/*!
 * \brief Get the \c flag from a DXF \c LWPOLYLINE entity.
 *
 * \return \c flag.
 */
int
dxf_lwpolyline_get_flag
(
        DxfLWPolyline *lwpolyline
                /*!< a pointer to a DXF \c LWPOLYLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lwpolyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (lwpolyline->flag < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lwpolyline->flag);
}


/*!
 * \brief Set the \c flag value for a DXF \c LWPOLYLINE entity.
 */
DxfLWPolyline *
dxf_lwpolyline_set_flag
(
        DxfLWPolyline *lwpolyline,
                /*!< a pointer to a DXF \c LWPOLYLINE entity. */
        int flag
                /*!< \c flag value for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lwpolyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (flag < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        lwpolyline->flag = flag;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lwpolyline);
}


/*!
 * \brief Get the \c number_vertices from a DXF \c LWPOLYLINE entity.
 *
 * \return \c number_vertices.
 */
int
dxf_lwpolyline_get_number_vertices
(
        DxfLWPolyline *lwpolyline
                /*!< a pointer to a DXF \c LWPOLYLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lwpolyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (lwpolyline->number_vertices < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lwpolyline->number_vertices);
}


/*!
 * \brief Set the \c number_vertices value for a DXF \c LWPOLYLINE
 * entity.
 */
DxfLWPolyline *
dxf_lwpolyline_set_number_vertices
(
        DxfLWPolyline *lwpolyline,
                /*!< a pointer to a DXF \c LWPOLYLINE entity. */
        int number_vertices
                /*!< \c number_vertices value for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lwpolyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (number_vertices < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        lwpolyline->number_vertices = number_vertices;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lwpolyline);
}


/*!
 * \brief Get the X-value of the extrusion vector \c extr_x0 of a DXF
 * \c LWPOLYLINE entity.
 *
 * \return the X-value of the extrusion vector \c extr_x0.
 */
double
dxf_lwpolyline_get_extr_x0
(
        DxfLWPolyline *lwpolyline
                /*!< a pointer to a DXF \c LWPOLYLINE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (lwpolyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lwpolyline->extr_x0);
}


/*!
 * \brief Set the X-value of the extrusion vector \c extr_x0 of a DXF
 * \c LWPOLYLINE entity.
 *
 * \return a pointer to \c lwpolyline when successful, or \c NULL when
 * an error occurred.
 */
DxfLWPolyline *
dxf_lwpolyline_set_extr_x0
(
        DxfLWPolyline *lwpolyline,
                /*!< a pointer to a DXF \c LWPOLYLINE entity. */
        double extr_x0
                /*!< the X-value of the extrusion vector \c extr_x0 of a
                 * DXF \c LWPOLYLINE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lwpolyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        lwpolyline->extr_x0 = extr_x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lwpolyline);
}


/*!
 * \brief Get the Y-value of the extrusion vector \c extr_y0 of a DXF
 * \c LWPOLYLINE entity.
 *
 * \return the Y-value of the extrusion vector \c extr_y0.
 */
double
dxf_lwpolyline_get_extr_y0
(
        DxfLWPolyline *lwpolyline
                /*!< a pointer to a DXF \c LWPOLYLINE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (lwpolyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lwpolyline->extr_y0);
}


/*!
 * \brief Set the Y-value of the extrusion vector \c extr_y0 of a DXF
 * \c LWPOLYLINE entity.
 *
 * \return a pointer to \c lwpolyline when successful, or \c NULL when an
 * error occurred.
 */
DxfLWPolyline *
dxf_lwpolyline_set_extr_y0
(
        DxfLWPolyline *lwpolyline,
                /*!< a pointer to a DXF \c LWPOLYLINE entity. */
        double extr_y0
                /*!< the Y-value of the extrusion vector \c extr_y0 of a
                 * DXF \c LWPOLYLINE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lwpolyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        lwpolyline->extr_y0 = extr_y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lwpolyline);
}


/*!
 * \brief Get the Z-value of the extrusion vector \c extr_z0 of a DXF
 * \c LWPOLYLINE entity.
 *
 * \return the Z-value of the extrusion vector \c extr_z0.
 */
double
dxf_lwpolyline_get_extr_z0
(
        DxfLWPolyline *lwpolyline
                /*!< a pointer to a DXF \c LWPOLYLINE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (lwpolyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lwpolyline->extr_z0);
}


/*!
 * \brief Set the Z-value of the extrusion vector \c extr_z0 of a DXF
 * \c LWPOLYLINE entity.
 *
 * \return a pointer to \c lwpolyline when successful, or \c NULL when
 * an error occurred.
 */
DxfLWPolyline *
dxf_lwpolyline_set_extr_z0
(
        DxfLWPolyline *lwpolyline,
                /*!< a pointer to a DXF \c LWPOLYLINE entity. */
        double extr_z0
                /*!< the Z-value of the extrusion vector \c extr_z0 of a
                 * DXF \c LWPOLYLINE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lwpolyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        lwpolyline->extr_z0 = extr_z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lwpolyline);
}


/*!
 * \brief Get the pointer to the first vertex of a linked list of
 * \c vertices from a DXF \c LWPOLYLINE entity.
 *
 * \return pointer to the first vertex of a linked list of \c vertices.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfVertex *
dxf_lwpolyline_get_vertices
(
        DxfLWPolyline *lwpolyline
                /*!< a pointer to a DXF \c LWPOLYLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lwpolyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (lwpolyline->vertices == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the vertices member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfVertex *) lwpolyline->vertices);
}


/*!
 * \brief Set the pointer to the first vertex of a linked list of
 * \c vertices for a DXF \c LWPOLYLINE entity.
 */
DxfLWPolyline *
dxf_lwpolyline_set_vertices
(
        DxfLWPolyline *lwpolyline,
                /*!< a pointer to a DXF \c LWPOLYLINE entity. */
        DxfVertex *vertices
                /*!< a pointer to the first vertex of a linked list of
                 * \c vertices. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lwpolyline == NULL)
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
        lwpolyline->vertices = (struct DxfVertex *) vertices;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lwpolyline);
}


/*!
 * \brief Get the pointer to the next \c LWPOLYLINE entity from a DXF 
 * \c LWPOLYLINE entity.
 *
 * \return pointer to the next \c LWPOLYLINE entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfLWPolyline *
dxf_lwpolyline_get_next
(
        DxfLWPolyline *lwpolyline
                /*!< a pointer to a DXF \c LWPOLYLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lwpolyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (lwpolyline->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the next member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfLWPolyline *) lwpolyline->next);
}


/*!
 * \brief Set the pointer to the next \c LWPOLYLINE for a DXF
 * \c LWPOLYLINE entity.
 */
DxfLWPolyline *
dxf_lwpolyline_set_next
(
        DxfLWPolyline *lwpolyline,
                /*!< a pointer to a DXF \c LWPOLYLINE entity. */
        DxfLWPolyline *next
                /*!< a pointer to the next \c LWPOLYLINE for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lwpolyline == NULL)
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
        lwpolyline->next = (struct DxfLWPolyline *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (lwpolyline);
}


/*!
 * \brief Get the pointer to the last \c LWPOLYLINE entity from a linked
 * list of DXF \c LWPOLYLINE entities.
 *
 * \return pointer to the last \c LWPOLYLINE entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfLWPolyline *
dxf_lwpolyline_get_last
(
        DxfLWPolyline *lwpolyline
                /*!< a pointer to a DXF \c LWPOLYLINE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (lwpolyline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (lwpolyline->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfLWPolyline *) lwpolyline);
        }
        DxfLWPolyline *iter = (DxfLWPolyline *) lwpolyline->next;
        while (iter->next != NULL)
        {
                iter = (DxfLWPolyline *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfLWPolyline *) iter);
}


/* EOF */
