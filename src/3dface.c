/*!
 * \file 3dface.c
 *
 * \author Copyright (C) 2010 ... 2013 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF 3D face entity (\c 3DFACE).
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


#include "3dface.h"


/*!
 * \brief Allocate memory for a DXF \c 3DFACE.
 *
 * Fill the memory contents with zeros.
 */
Dxf3dface *
dxf_3dface_new ()
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_3dface_new () function.\n",
                __FILE__, __LINE__);
#endif
        Dxf3dface *dxf_3dface = NULL;
        size_t size;

        size = sizeof (Dxf3dface);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_3dface = malloc (size)) == NULL)
        {
                fprintf (stderr, "ERROR in dxf_3dface_new () could not allocate memory for a Dxf3dface struct.\n");
                dxf_3dface = NULL;
        }
        else
        {
                memset (dxf_3dface, 0, size);
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_3dface_new () function.\n",
                __FILE__, __LINE__);
#endif
        return (dxf_3dface);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c 3DFACE
 * entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
Dxf3dface *
dxf_3dface_init
(
        Dxf3dface *dxf_3dface
                /*!< DXF 3dface entity. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_3dface_init () function.\n",
                __FILE__, __LINE__);
#endif
        dxf_3dface = dxf_3dface_new ();
        if (dxf_3dface == NULL)
        {
              fprintf (stderr, "ERROR in dxf_3dface_init () could not allocate memory for a Dxf3dface struct.\n");
              return (NULL);
        }
        dxf_3dface->id_code = 0;
        dxf_3dface->linetype = strdup (DXF_DEFAULT_LINETYPE);
        dxf_3dface->layer = strdup (DXF_DEFAULT_LAYER);
        dxf_3dface->x0 = 0.0;
        dxf_3dface->y0 = 0.0;
        dxf_3dface->z0 = 0.0;
        dxf_3dface->x1 = 0.0;
        dxf_3dface->y1 = 0.0;
        dxf_3dface->z1 = 0.0;
        dxf_3dface->x2 = 0.0;
        dxf_3dface->y2 = 0.0;
        dxf_3dface->z2 = 0.0;
        dxf_3dface->x3 = 0.0;
        dxf_3dface->y3 = 0.0;
        dxf_3dface->z3 = 0.0;
        dxf_3dface->thickness = 0.0;
        dxf_3dface->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        dxf_3dface->visibility = DXF_DEFAULT_VISIBILITY;
        dxf_3dface->color = DXF_COLOR_BYLAYER;
        dxf_3dface->paperspace = DXF_MODELSPACE;
        dxf_3dface->flag = 0;
        dxf_3dface->next = NULL;
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_3dface_init () function.\n",
                __FILE__, __LINE__);
#endif
        return (dxf_3dface);
}


/*!
 * \brief Read data from a DXF file into a DXF \c 3DFACE entity.
 *
 * The last line read from file contained the string "3DFACE". \n
 * Now follows some data for the \c 3DFACE, to be terminated with a "  0"
 * string announcing the following entity, or the end of the \c ENTITY
 * section marker \c ENDSEC. \n
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred while reading from the input file.
 */
int
dxf_3dface_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        Dxf3dface *dxf_3dface
                /*!< DXF 3dface entity. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_3dface_read () function.\n",
                __FILE__, __LINE__);
#endif
        char *temp_string = NULL;

        if (!dxf_3dface)
        {
                dxf_3dface = dxf_3dface_new ();
        }
        (fp->line_number)++;
        fscanf (fp->fp, "%[^\n]", temp_string);
        while (strcmp (temp_string, "0") != 0)
        {
                if (ferror (fp->fp))
                {
                        fprintf (stderr, "Error in dxf_3dface_read () while reading from: %s in line: %d.\n",
                                fp->filename, fp->line_number);
                        fclose (fp->fp);
                        return (0);
                }
                if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", &dxf_3dface->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_3dface->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_3dface->layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the first point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_3dface->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the first point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_3dface->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of first the point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_3dface->z0);
                }
                else if (strcmp (temp_string, "11") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the second point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_3dface->x1);
                }
                else if (strcmp (temp_string, "21") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the second point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_3dface->y1);
                }
                else if (strcmp (temp_string, "31") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the second point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_3dface->z1);
                }
                else if (strcmp (temp_string, "12") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the third point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_3dface->x2);
                }
                else if (strcmp (temp_string, "22") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the third point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_3dface->y2);
                }
                else if (strcmp (temp_string, "32") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the third point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_3dface->z2);
                }
                else if (strcmp (temp_string, "13") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the fourth point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_3dface->x3);
                }
                else if (strcmp (temp_string, "23") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the fourth point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_3dface->y3);
                }
                else if (strcmp (temp_string, "33") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the fourth point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_3dface->z3);
                }
                else if ((fp->acad_version_number <= AutoCAD_11)
                        && (strcmp (temp_string, "38") == 0)
                        && (dxf_3dface->z0 = 0.0))
                {
                        /*!
                         * \todo Elevation is a pre AutoCAD R11 variable
                         * so additional testing for the version should
                         * probably be added. */
                        /* Now follows a string containing the
                         * elevation. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_3dface->z0);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_3dface->thickness);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_3dface->color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_3dface->paperspace);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
                        if ((strcmp (temp_string, "AcDbEntity") != 0)
                        && (strcmp (temp_string, "AcDbFace") != 0))
                        {
                                fprintf (stderr, "Error in dxf_3dface_read () found a bad subclass marker in: %s in line: %d.\n",
                                        fp->filename, fp->line_number);
                        }
                }
                else if (strcmp (temp_string, "70") == 0)
                {
                        /* Now follows a string containing the
                         * value of edge visibility flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_3dface->flag);
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
                        fprintf (stderr, "Warning in dxf_3dface_read () unknown string tag found while reading from: %s in line: %d.\n",
                                fp->filename, fp->line_number);
                }
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_3dface_read () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write DXF output to a file for a DXF \c 3DFACE entity.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_3dface_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        Dxf3dface *dxf_3dface
                /*!< DXF 3D face entity. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_3dface_write () function.\n",
                __FILE__, __LINE__);
#endif
        char *dxf_entity_name = strdup ("3DFACE");

        /* Do some basic checks. */
        if (dxf_3dface == NULL)
        {
                return (EXIT_FAILURE);
                fprintf (stderr, "Error in dxf_3dface_write () a NULL pointer was passed.\n");
        }
        if (strcmp (dxf_3dface->layer, "") == 0)
        {
                fprintf (stderr, "Warning in dxf_3dface_write () empty layer string for the %s entity with id-code: %x\n",
                        dxf_entity_name, dxf_3dface->id_code);
                fprintf (stderr, "    %s entity is relocated to layer 0",
                        dxf_entity_name);
                dxf_3dface->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
        }
        if (dxf_3dface->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", dxf_3dface->id_code);
        }
        if (dxf_3dface->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
        fprintf (fp->fp, "  8\n%s\n", dxf_3dface->layer);
        if (strcmp (dxf_3dface->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", dxf_3dface->linetype);
        }
        if (dxf_3dface->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", dxf_3dface->color);
        }
        if (dxf_3dface->thickness != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", dxf_3dface->thickness);
        }
        if (dxf_3dface->linetype_scale != 1.0)
        {
                fprintf (fp->fp, " 48\n%f\n", dxf_3dface->linetype_scale);
        }
        if (dxf_3dface->visibility != 0)
        {
                fprintf (fp->fp, " 60\n%d\n", dxf_3dface->visibility);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbFace\n");
        }
        fprintf (fp->fp, " 10\n%f\n", dxf_3dface->x0);
        fprintf (fp->fp, " 20\n%f\n", dxf_3dface->y0);
        fprintf (fp->fp, " 30\n%f\n", dxf_3dface->z0);
        fprintf (fp->fp, " 11\n%f\n", dxf_3dface->x1);
        fprintf (fp->fp, " 21\n%f\n", dxf_3dface->y1);
        fprintf (fp->fp, " 31\n%f\n", dxf_3dface->z1);
        fprintf (fp->fp, " 12\n%f\n", dxf_3dface->x2);
        fprintf (fp->fp, " 22\n%f\n", dxf_3dface->y2);
        fprintf (fp->fp, " 32\n%f\n", dxf_3dface->z2);
        fprintf (fp->fp, " 13\n%f\n", dxf_3dface->x3);
        fprintf (fp->fp, " 23\n%f\n", dxf_3dface->y3);
        fprintf (fp->fp, " 33\n%f\n", dxf_3dface->z3);
        fprintf (fp->fp, " 70\n%d\n", dxf_3dface->flag);
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_3dface_write () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c 3DFACE and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_3dface_free
(
        Dxf3dface *dxf_3dface
                /*!< Pointer to the memory occupied by the DXF \c 3DFACE
                 * entity. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_3dface_free () function.\n",
                __FILE__, __LINE__);
#endif
        if (dxf_3dface->next != NULL)
        {
              fprintf (stderr, "ERROR in dxf_3dface_free () pointer to next Dxf3dface was not NULL.\n");
              return (EXIT_FAILURE);
        }
        free (dxf_3dface->linetype);
        free (dxf_3dface->layer);
        free (dxf_3dface);
        dxf_3dface = NULL;
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_3dface_free () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
