/*!
 * \file leader.c
 *
 * \author Copyright (C) 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF leader entity (\c LEADER).
 *
 * \version The \c LEADER entity was introduced in DXF R13.
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


#include "leader.h"


/*!
 * \brief Allocate memory for a DXF \c LEADER.
 *
 * Fill the memory contents with zeros.
 *
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfLeader *
dxf_leader_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfLeader *leader = NULL;
        size_t size;

        size = sizeof (DxfLeader);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((leader = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfArc struct.\n")),
                  __FUNCTION__);
                leader = NULL;
        }
        else
        {
                memset (leader, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (leader);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c LEADER
 * entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfLeader *
dxf_leader_init
(
        DxfLeader *leader
                /*!< pointer to a DXF \c LEADER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        /* Do some basic checks. */
        if (leader == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                leader = dxf_leader_new ();
        }
        if (leader == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfLeader struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        leader->id_code = 0;
        leader->linetype = strdup (DXF_DEFAULT_LINETYPE);
        leader->layer = strdup (DXF_DEFAULT_LAYER);
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                leader->x0[i] = 0.0;
                leader->y0[i] = 0.0;
                leader->z0[i] = 0.0;
        }
        leader->x_extr = 0.0;
        leader->y_extr = 0.0;
        leader->z_extr = 0.0;
        leader->elevation = 0.0;
        leader->thickness = 0.0;
        leader->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        leader->visibility = DXF_DEFAULT_VISIBILITY;
        leader->color = DXF_COLOR_BYLAYER;
        leader->paperspace = DXF_MODELSPACE;
        leader->dictionary_owner_soft = strdup ("");
        leader->dictionary_owner_hard = strdup ("");
        leader->dimension_style_name = strdup ("");
        leader->text_annotation_height = 0.0;
        leader->text_annotation_width = 0.0;
        leader->arrow_head_flag = 0;
        leader->path_type = 0;
        leader->creation_flag = 0;
        leader->hookline_direction_flag = 0;
        leader->hookline_flag = 0;
        leader->number_vertices = 0;
        leader->leader_color = 0;
        leader->x1 = 0.0;
        leader->y1 = 0.0;
        leader->z1 = 0.0;
        leader->x2 = 0.0;
        leader->y2 = 0.0;
        leader->z2 = 0.0;
        leader->x3 = 0.0;
        leader->y3 = 0.0;
        leader->z3 = 0.0;
        leader->annotation_reference_hard = strdup ("");
        leader->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (leader);
}


/*!
 * \brief Read data from a DXF file into a DXF \c LEADER entity.
 *
 * The last line read from file contained the string "LEADER". \n
 * Now follows some data for the \c LEADER, to be terminated with a "  0"
 * string announcing the following entity, or the end of the \c ENTITY
 * section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c leader. \n
 *
 * \return \c a pointer to \c leader.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfLeader *
dxf_leader_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfLeader *leader
                /*!< Pointer to a DXF \c LEADER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *temp_string = NULL;
        int i;

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
        if (fp->acad_version_number < AutoCAD_13)
        {
                fprintf (stderr,
                  (_("Warning in %s () illegal DXF version for this entity.\n")),
                  __FUNCTION__);
        }
        if (leader == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                leader = dxf_leader_new ();
                leader = dxf_leader_init (leader);
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
                        /* Clean up. */
                        free (temp_string);
                        fclose (fp->fp);
                        return (NULL);
                }
                else if (strcmp (temp_string, "  3") == 0)
                {
                        /* Now follows a string containing additional
                         * proprietary data. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", leader->dimension_style_name);
                }
                if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", &leader->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", leader->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", leader->layer);
                }
                else if ((strcmp (temp_string, "10") == 0)
                  || (strcmp (temp_string, "20") == 0)
                  || (strcmp (temp_string, "30") == 0))
                {
                        if (strcmp (temp_string, "10") == 0)
                        {
                                /* Now follows a string containing the X-value
                                 * of the Vertex coordinates (one entry for each
                                 * vertex). */
                                (fp->line_number)++;
                                fscanf (fp->fp, "%lf\n", &leader->x0[i]);
                        }
                        else if (strcmp (temp_string, "20") == 0)
                        {
                                /* Now follows a string containing the Y-value
                                 * of the Vertex coordinates (one entry for each
                                 * vertex). */
                                (fp->line_number)++;
                                fscanf (fp->fp, "%lf\n", &leader->y0[i]);
                        }
                        else if (strcmp (temp_string, "30") == 0)
                        {
                                /* Now follows a string containing the Z-value
                                 * of the Vertex coordinates (one entry for each
                                 * vertex). */
                                (fp->line_number)++;
                                fscanf (fp->fp, "%lf\n", &leader->z0[i]);
                                i++;
                        }
                }
                else if ((fp->acad_version_number <= AutoCAD_11)
                  && DXF_FLATLAND
                  && (strcmp (temp_string, "38") == 0))
                {
                        /* Now follows a string containing the
                         * elevation. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &leader->elevation);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &leader->thickness);
                }
                else if (strcmp (temp_string, "40") == 0)
                {
                        /* Now follows a string containing the text
                         * annotation height. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &leader->text_annotation_height);
                }
                else if (strcmp (temp_string, "41") == 0)
                {
                        /* Now follows a string containing the text
                         * annotation width. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &leader->text_annotation_width);
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing the linetype
                         * scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &leader->linetype_scale);
                }
                else if (strcmp (temp_string, "60") == 0)
                {
                        /* Now follows a string containing the
                         * visibility value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &leader->visibility);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &leader->color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &leader->paperspace);
                }
                else if (strcmp (temp_string, "71") == 0)
                {
                        /* Now follows a string containing the arrow
                         * head flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &leader->arrow_head_flag);
                }
                else if (strcmp (temp_string, "72") == 0)
                {
                        /* Now follows a string containing the path type. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &leader->path_type);
                }
                else if (strcmp (temp_string, "73") == 0)
                {
                        /* Now follows a string containing the creation
                         * flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &leader->creation_flag);
                }
                else if (strcmp (temp_string, "74") == 0)
                {
                        /* Now follows a string containing the hookline
                         * direction flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &leader->hookline_direction_flag);
                }
                else if (strcmp (temp_string, "75") == 0)
                {
                        /* Now follows a string containing the hookline
                         * flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &leader->hookline_flag);
                }
                else if (strcmp (temp_string, "76") == 0)
                {
                        /* Now follows a string containing the number of
                         * vertices. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &leader->number_vertices);
                }
                else if (strcmp (temp_string, "77") == 0)
                {
                        /* Now follows a string containing the leader
                         * color. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &leader->leader_color);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
                        if (strcmp (temp_string, "AcDbLeader") != 0)
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () found a bad subclass marker in: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                        }
                }
                else if (strcmp (temp_string, "210") == 0)
                {
                        /* Now follows a string containing the
                         * X-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &leader->x_extr);
                }
                else if (strcmp (temp_string, "220") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &leader->y_extr);
                }
                else if (strcmp (temp_string, "230") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &leader->z_extr);
                }
                else if (strcmp (temp_string, "211") == 0)
                {
                        /* Now follows a string containing the
                         * X-value of the "Horizontal" direction for
                         * leader. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &leader->x1);
                }
                else if (strcmp (temp_string, "221") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the "Horizontal" direction for
                         * leader. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &leader->y1);
                }
                else if (strcmp (temp_string, "231") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the "Horizontal" direction for
                         * leader. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &leader->z1);
                }
                else if (strcmp (temp_string, "212") == 0)
                {
                        /* Now follows a string containing the
                         * X-value of the Block reference insertion
                         * point offset from last leader vertex. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &leader->x2);
                }
                else if (strcmp (temp_string, "222") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the Block reference insertion
                         * point offset from last leader vertex. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &leader->y2);
                }
                else if (strcmp (temp_string, "232") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the Block reference insertion
                         * point offset from last leader vertex. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &leader->z2);
                }
                else if (strcmp (temp_string, "213") == 0)
                {
                        /* Now follows a string containing the
                         * X-value of the Annotation placement point
                         * offset from last leader vertex. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &leader->x3);
                }
                else if (strcmp (temp_string, "223") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the Annotation placement point
                         * offset from last leader vertex. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &leader->y3);
                }
                else if (strcmp (temp_string, "233") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the Annotation placement point
                         * offset from last leader vertex. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &leader->z3);
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing Soft-pointer
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", leader->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "340") == 0)
                {
                        /* Now follows a string containing Hard
                         * reference to associated annotation (mtext,
                         * tolerance, or insert entity). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", leader->annotation_reference_hard);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", leader->dictionary_owner_hard);
                }
                else if (strcmp (temp_string, "999") == 0)
                {
                        /* Now follows a string containing a comment. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
                        fprintf (stdout, (_("DXF comment: %s\n")), temp_string);
                }
                else
                {
                        fprintf (stderr,
                          (_("Warning in %s () unknown string tag found while reading from: %s in line: %d.\n")),
                          __FUNCTION__, fp->filename, fp->line_number);
                }
        }
        /* Handle omitted members and/or illegal values. */
        if (strcmp (leader->linetype, "") == 0)
        {
                leader->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (leader->layer, "") == 0)
        {
                leader->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Clean up. */
        free (temp_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (leader);
}


/*!
 * \brief Free the allocated memory for a DXF \c LEADER and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
int
dxf_leader_free
(
        DxfLeader *leader
                /*!< Pointer to the memory occupied by the DXF
                 * \c LEADER entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (leader->next != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to next DxfLeader was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (leader->linetype);
        free (leader->layer);
        free (leader->dictionary_owner_soft);
        free (leader->dictionary_owner_hard);
        free (leader->dimension_style_name);
        free (leader->annotation_reference_hard);
        free (leader);
        leader = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
