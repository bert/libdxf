/*!
 * \file vertex.c
 *
 * \author Copyright (C) 2008 ... 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF vertex entity (\c VERTEX).
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


#include "vertex.h"


/*!
 * \brief Allocate memory for a \c DxfVertex.
 *
 * Fill the memory contents with zeros.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfVertex *
dxf_vertex_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfVertex *dxf_vertex = NULL;
        size_t size;

        size = sizeof (DxfVertex);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_vertex = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfVertex struct.\n")),
                  __FUNCTION__);
                dxf_vertex = NULL;
        }
        else
        {
                memset (dxf_vertex, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_vertex);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c VERTEX entity.
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
DxfVertex *
dxf_vertex_init
(
        DxfVertex *dxf_vertex
                /*!< DXF vertex entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dxf_vertex == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                dxf_vertex = dxf_vertex_new ();
        }
        if (dxf_vertex == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory for a DxfVertex struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        dxf_vertex->id_code = 0;
        dxf_vertex->linetype = strdup (DXF_DEFAULT_LINETYPE);
        dxf_vertex->layer = strdup (DXF_DEFAULT_LAYER);
        dxf_vertex->x0 = 0.0;
        dxf_vertex->y0 = 0.0;
        dxf_vertex->z0 = 0.0;
        dxf_vertex->elevation = 0.0;
        dxf_vertex->thickness = 0.0;
        dxf_vertex->start_width = 0.0;
        dxf_vertex->end_width = 0.0;
        dxf_vertex->bulge = 0.0;
        dxf_vertex->curve_fit_tangent_direction = 0.0;
        dxf_vertex->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        dxf_vertex->visibility = DXF_DEFAULT_VISIBILITY;
        dxf_vertex->color = DXF_COLOR_BYLAYER;
        dxf_vertex->paperspace = DXF_MODELSPACE;
        dxf_vertex->flag = 0;
        dxf_vertex->dictionary_owner_soft = strdup ("");
        dxf_vertex->dictionary_owner_hard = strdup ("");
        dxf_vertex->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_vertex);
}


/*!
 * \brief Read data from a DXF file into an \c VERTEX entity.
 *
 * The last line read from file contained the string "VERTEX". \n
 * Now follows some data for the \c VERTEX, to be terminated with a "  0"
 * string announcing the following entity, or the end of the \c ENTITY
 * section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c dxf_vertex. \n
 *
 * \return a pointer to \c dxf_vertex.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfVertex *
dxf_vertex_read
(
        DxfFile *fp,
                /*!< filepointer to the input file (or device). */
        DxfVertex *dxf_vertex
                /*!< DXF vertex entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *temp_string = NULL;

        /* Do some basic checks. */
        if (dxf_vertex == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                dxf_vertex = dxf_vertex_new ();
                dxf_vertex = dxf_vertex_init (dxf_vertex);
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
                        fscanf (fp->fp, "%x\n", &dxf_vertex->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_vertex->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_vertex->layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_vertex->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_vertex->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_vertex->z0);
                }
                else if ((fp->acad_version_number <= AutoCAD_11)
                        && (strcmp (temp_string, "38") == 0)
                        && (dxf_vertex->elevation != 0.0))
                {
                        /* Now follows a string containing the
                         * elevation. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_vertex->elevation);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_vertex->thickness);
                }
                else if (strcmp (temp_string, "40") == 0)
                {
                        /* Now follows a string containing the
                         * start width. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_vertex->start_width);
                }
                else if (strcmp (temp_string, "41") == 0)
                {
                        /* Now follows a string containing the
                         * end width. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_vertex->end_width);
                }
                else if (strcmp (temp_string, "42") == 0)
                {
                        /* Now follows a string containing the
                         * bulge. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_vertex->bulge);
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing the linetype
                         * scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_vertex->linetype_scale);
                }
                else if (strcmp (temp_string, "50") == 0)
                {
                        /* Now follows a string containing the
                         * curve fitting tangent. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_vertex->curve_fit_tangent_direction);
                }
                else if (strcmp (temp_string, "60") == 0)
                {
                        /* Now follows a string containing the
                         * visibility value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &dxf_vertex->visibility);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_vertex->color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_vertex->paperspace);
                }
                else if (strcmp (temp_string, "70") == 0)
                {
                        /* Now follows a string containing the flag
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_vertex->flag);
                }
                else if (strcmp (temp_string, "71") == 0)
                {
                        /* Now follows a string containing the Polyface
                         * mesh vertex index value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_vertex->polyface_mesh_vertex_index_1);
                }
                else if (strcmp (temp_string, "72") == 0)
                {
                        /* Now follows a string containing the Polyface
                         * mesh vertex index value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_vertex->polyface_mesh_vertex_index_2);
                }
                else if (strcmp (temp_string, "73") == 0)
                {
                        /* Now follows a string containing the Polyface
                         * mesh vertex index value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_vertex->polyface_mesh_vertex_index_3);
                }
                else if (strcmp (temp_string, "74") == 0)
                {
                        /* Now follows a string containing the Polyface
                         * mesh vertex index value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_vertex->polyface_mesh_vertex_index_4);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
                        if ((strcmp (temp_string, "AcDbEntity") != 0)
                        && (strcmp (temp_string, "AcDbVertex") != 0)
                        && (strcmp (temp_string, "AcDb2dVertex") != 0)
                        && (strcmp (temp_string, "AcDb3dPolylineVertex") != 0))
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () found a bad subclass marker in: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                        }
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing Soft-pointer
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_vertex->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_vertex->dictionary_owner_hard);
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
        if (strcmp (dxf_vertex->linetype, "") == 0)
        {
                dxf_vertex->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (dxf_vertex->layer, "") == 0)
        {
                dxf_vertex->layer = strdup (DXF_DEFAULT_LAYER);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_vertex);
}


/*!
 * \brief Write DXF output to fp for a vertex entity.
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
dxf_vertex_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfVertex *dxf_vertex
                /*!< DXF vertex entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("VERTEX");

        /* Do some basic checks. */
        if (dxf_vertex == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (strcmp (dxf_vertex->linetype, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty linetype string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, dxf_vertex->id_code);
                fprintf (stderr,
                  (_("    %s entity is reset to default linetype")),
                  dxf_entity_name);
                dxf_vertex->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (dxf_vertex->layer, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, dxf_vertex->id_code);
                fprintf (stderr,
                  (_("    %s entity is relocated to layer 0")),
                  dxf_entity_name);
                dxf_vertex->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (dxf_vertex->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", dxf_vertex->id_code);
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
        if ((strcmp (dxf_vertex->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", dxf_vertex->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (dxf_vertex->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", dxf_vertex->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
        }
        if (dxf_vertex->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
        fprintf (fp->fp, "  8\n%s\n", dxf_vertex->layer);
        if (strcmp (dxf_vertex->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", dxf_vertex->linetype);
        }
        if ((fp->acad_version_number <= AutoCAD_11)
          && DXF_FLATLAND
          && (dxf_vertex->elevation != 0.0))
        {
                fprintf (fp->fp, " 38\n%f\n", dxf_vertex->elevation);
        }
        if (dxf_vertex->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", dxf_vertex->color);
        }
        if (dxf_vertex->linetype_scale != 1.0)
        {
                fprintf (fp->fp, " 48\n%f\n", dxf_vertex->linetype_scale);
        }
        if (dxf_vertex->visibility != 0)
        {
                fprintf (fp->fp, " 60\n%d\n", dxf_vertex->visibility);
        }
        /*! \todo Put \c thickness in the correct order. */ 
        if (dxf_vertex->thickness != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", dxf_vertex->thickness);
        }
        fprintf (fp->fp, "100\nAcDbVertex\n");
        /*! \todo We use a \c 3dPolylineVertex for now,
         * it could have been a \c 2dVertex as well, in that case use:\n
        fprintf (fp->fp, "100\nAcDb2dVertex\n");
         */
        fprintf (fp->fp, "100\nAcDb3dPolylineVertex\n");
        fprintf (fp->fp, " 10\n%f\n", dxf_vertex->x0);
        fprintf (fp->fp, " 20\n%f\n", dxf_vertex->y0);
        fprintf (fp->fp, " 30\n%f\n", dxf_vertex->z0);
        if (dxf_vertex->start_width != 0.0)
        {
                fprintf (fp->fp, " 40\n%f\n", dxf_vertex->start_width);
        }
        if (dxf_vertex->end_width != 0.0)
        {
                fprintf (fp->fp, " 41\n%f\n", dxf_vertex->end_width);
        }
        if (dxf_vertex->bulge != 0.0)
        {
                fprintf (fp->fp, " 42\n%f\n", dxf_vertex->bulge);
        }
        fprintf (fp->fp, " 70\n%d\n", dxf_vertex->flag);
        if (dxf_vertex->curve_fit_tangent_direction != 0.0)
        {
                fprintf (fp->fp, " 50\n%f\n", dxf_vertex->curve_fit_tangent_direction);
        }
        if (dxf_vertex->polyface_mesh_vertex_index_1 != 0)
        {
                fprintf (fp->fp, " 71\n%d\n", dxf_vertex->polyface_mesh_vertex_index_1);
        }
        if (dxf_vertex->polyface_mesh_vertex_index_2 != 0)
        {
                fprintf (fp->fp, " 72\n%d\n", dxf_vertex->polyface_mesh_vertex_index_2);
        }
        if (dxf_vertex->polyface_mesh_vertex_index_3 != 0)
        {
                fprintf (fp->fp, " 73\n%d\n", dxf_vertex->polyface_mesh_vertex_index_3);
        }
        if (dxf_vertex->polyface_mesh_vertex_index_4 != 0)
        {
                fprintf (fp->fp, " 74\n%d\n", dxf_vertex->polyface_mesh_vertex_index_4);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a \c VERTEX entity and all it's
 * data fields.\n
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
dxf_vertex_free
(
        DxfVertex *dxf_vertex
                /*!< DXF vertex entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (dxf_vertex->next != NULL)
        {
                fprintf (stderr,
                  (_("ERROR in %s () pointer to next DxfVertex was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (dxf_vertex->linetype);
        free (dxf_vertex->layer);
        free (dxf_vertex->dictionary_owner_soft);
        free (dxf_vertex->dictionary_owner_hard);
        free (dxf_vertex);
        dxf_vertex = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
