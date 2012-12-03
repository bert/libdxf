/*!
 * \file 3dface.c
 *
 * \author Copyright (C) 2010 ... 2012 by Bert Timmerman <bert.timmerman@xs4all.nl>.
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
        dxf_3dface->color = DXF_COLOR_BYLAYER;
        dxf_3dface->paperspace = DXF_MODELSPACE;
        dxf_3dface->flag = 0;
        dxf_3dface->acad_version_number = 0;
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
        char *filename,
                /*!< filename of input file (or device). */
        FILE *fp,
                /*!< filepointer to the input file (or device). */
        int *line_number,
                /*!< current line number in the input file (or device). */
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
        (*line_number)++;
        fscanf (fp, "%[^\n]", temp_string);
        while (strcmp (temp_string, "0") != 0)
        {
                if (ferror (fp))
                {
                        fprintf (stderr, "Error in dxf_3dface_read () while reading from: %s in line: %d.\n",
                                filename, *line_number);
                        fclose (fp);
                        return (0);
                }
                if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (*line_number)++;
                        fscanf (fp, "%x\n", &dxf_3dface->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (*line_number)++;
                        fscanf (fp, "%s\n", dxf_3dface->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (*line_number)++;
                        fscanf (fp, "%s\n", dxf_3dface->layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the first point. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_3dface->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the first point. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_3dface->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of first the point. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_3dface->z0);
                }
                else if (strcmp (temp_string, "11") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the second point. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_3dface->x1);
                }
                else if (strcmp (temp_string, "21") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the second point. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_3dface->y1);
                }
                else if (strcmp (temp_string, "31") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the second point. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_3dface->z1);
                }
                else if (strcmp (temp_string, "12") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the third point. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_3dface->x2);
                }
                else if (strcmp (temp_string, "22") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the third point. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_3dface->y2);
                }
                else if (strcmp (temp_string, "32") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the third point. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_3dface->z2);
                }
                else if (strcmp (temp_string, "13") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the point. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_3dface->x3);
                }
                else if (strcmp (temp_string, "23") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the fourth point. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_3dface->y3);
                }
                else if (strcmp (temp_string, "33") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the fourth point. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_3dface->z3);
                }
                else if ((dxf_3dface->acad_version_number <= AutoCAD_11)
                        && (strcmp (temp_string, "38") == 0)
                        && (dxf_3dface->z0 = 0.0))
                {
                        /*!
                         * \todo Elevation is a pre AutoCAD R11 variable
                         * so additional testing for the version should
                         * probably be added. */
                        /* Now follows a string containing the
                         * elevation. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_3dface->z0);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (*line_number)++;
                        fscanf (fp, "%lf\n", &dxf_3dface->thickness);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (*line_number)++;
                        fscanf (fp, "%d\n", &dxf_3dface->color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (*line_number)++;
                        fscanf (fp, "%d\n", &dxf_3dface->paperspace);
                }
                else if ((dxf_3dface->acad_version_number >= AutoCAD_12)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /*!
                         * \todo Subclass markers are post AutoCAD R12
                         * variable so additional testing for the
                         * version should probably be added here. */
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (*line_number)++;
                        fscanf (fp, "%s\n", temp_string);
                        if ((strcmp (temp_string, "AcDbEntity") != 0)
                        && ((strcmp (temp_string, "AcDbFace") != 0)))
                        {
                                fprintf (stderr, "Error in dxf_3dface_read () found a bad subclass marker in: %s in line: %d.\n",
                                        filename, *line_number);
                        }
                }
                else if (strcmp (temp_string, "70") == 0)
                {
                        /* Now follows a string containing the
                         * value of edge visibility flag. */
                        (*line_number)++;
                        fscanf (fp, "%d\n", &dxf_3dface->flag);
                }
                else if (strcmp (temp_string, "999") == 0)
                {
                        /* Now follows a string containing a comment. */
                        (*line_number)++;
                        fscanf (fp, "%s\n", temp_string);
                        fprintf (stdout, "DXF comment: %s\n", temp_string);
                }
                else
                {
                        fprintf (stderr, "Warning in dxf_3dface_read () unknown string tag found while reading from: %s in line: %d.\n",
                                filename, *line_number);
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
 * occurred while reading from the input file.
 */
int
dxf_3dface_write_lowlevel
(
        FILE *fp,
                /*!< file pointer to output file (or device). */
        int id_code,
                /*!< group code = 5. */
        char *linetype,
                /*!< group code = 6\n
                 * optional, defaults to \c BYLAYER. */
        char *layer,
                /*!< group code = 8. */
        double x0,
                /*!< group code = 10\n
                 * base point X-value, bottom left. */
        double y0,
                /*!< group code = 20\n
                 * base point Y-value, bottom left. */
        double z0,
                /*!< group code = 30\n
                 * base point Z-value, bottom left. */
        double x1,
                /*!< group code = 11\n
                 * alignment point X-vaule, bottom right. */
        double y1,
                /*!< group code = 21\n
                 * alignment point Y-vaule, bottom right. */
        double z1,
                /*!< group code = 31\n
                 * alignment point Z-vaule, bottom right. */
        double x2,
                /*!< group code = 12\n
                 * alignment point X-value, top left. */
        double y2,
                /*!< group code = 22\n
                 * alignment point Y-value, top left. */
        double z2,
                /*!< group code = 32\n
                 * alignment point Z-value, top left. */
        double x3,
                /*!< group code = 13\n
                 * alignment point X-value, top right. */
        double y3,
                /*!< group code = 23\n
                 * alignment point Y-value, top right. */
        double z3,
                /*!< group code = 33\n
                 * alignment point Z-value, top right. */
        double thickness,
                /*!< group code = 39\n
                 * optional, defaults to 0.0. */
        int color,
                /*!< group code = 62\n
                 * optional, defaults to \c BYLAYER */
        int paperspace,
                /*!< group code = 67\n
                 * optional, defaults to 0 (modelspace). */
        int flag
                /*!< group code = 70\n
                 * optional, defaults to 0\n
                 * bit coded:\n
                 * 1 = First edge is invisible\n
                 * 2 = Second edge is invisible\n
                 * 4 = Third edge is invisible\n
                 * 8 = Fourth edge is invisible\n */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_3dface_write_lowlevel () function.\n",
                __FILE__, __LINE__);
#endif
        char *dxf_entity_name = strdup ("3DFACE");

        if (strcmp (layer, "") == 0)
        {
                fprintf (stderr, "Warning in dxf_3dface_write_lowlevel () empty layer string for the %s entity with id-code: %x\n",
                        dxf_entity_name, id_code);
                fprintf (stderr, "    %s entity is relocated to layer 0",
                        dxf_entity_name);
                layer = strdup (DXF_DEFAULT_LAYER);
        }
        fprintf (fp, "  0\n%s\n", dxf_entity_name);
        if (id_code != -1)
        {
                fprintf (fp, "  5\n%x\n", id_code);
        }
        if (strcmp (linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp, "  6\n%s\n", linetype);
        }
        fprintf (fp, "  8\n%s\n", layer);
        fprintf (fp, " 10\n%f\n", x0);
        fprintf (fp, " 20\n%f\n", y0);
        fprintf (fp, " 30\n%f\n", z0);
        fprintf (fp, " 11\n%f\n", x1);
        fprintf (fp, " 21\n%f\n", y1);
        fprintf (fp, " 31\n%f\n", z1);
        fprintf (fp, " 12\n%f\n", x2);
        fprintf (fp, " 22\n%f\n", y2);
        fprintf (fp, " 32\n%f\n", z2);
        fprintf (fp, " 13\n%f\n", x3);
        fprintf (fp, " 23\n%f\n", y3);
        fprintf (fp, " 33\n%f\n", z3);
        if (thickness != 0.0)
        {
                fprintf (fp, " 39\n%f\n", thickness);
        }
        if (color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp, " 62\n%d\n", color);
        }
        if (paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
        fprintf (fp, " 70\n%d\n", flag);
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_3dface_write_lowlevel () function.\n",
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
        FILE *fp,
                /*!< file pointer to output file (or device). */
        Dxf3dface *dxf_3dface
                /*!< DXF 3D face entity. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_3dface_write () function.\n",
                __FILE__, __LINE__);
#endif
        char *dxf_entity_name = strdup ("3DFACE");

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
        fprintf (fp, "  0\n%s\n", dxf_entity_name);
        if (dxf_3dface->id_code != -1)
        {
                fprintf (fp, "  5\n%x\n", dxf_3dface->id_code);
        }
        if (strcmp (dxf_3dface->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp, "  6\n%s\n", dxf_3dface->linetype);
        }
        fprintf (fp, "  8\n%s\n", dxf_3dface->layer);
        fprintf (fp, " 10\n%f\n", dxf_3dface->x0);
        fprintf (fp, " 20\n%f\n", dxf_3dface->y0);
        fprintf (fp, " 30\n%f\n", dxf_3dface->z0);
        fprintf (fp, " 11\n%f\n", dxf_3dface->x1);
        fprintf (fp, " 21\n%f\n", dxf_3dface->y1);
        fprintf (fp, " 31\n%f\n", dxf_3dface->z1);
        fprintf (fp, " 12\n%f\n", dxf_3dface->x2);
        fprintf (fp, " 22\n%f\n", dxf_3dface->y2);
        fprintf (fp, " 32\n%f\n", dxf_3dface->z2);
        fprintf (fp, " 13\n%f\n", dxf_3dface->x3);
        fprintf (fp, " 23\n%f\n", dxf_3dface->y3);
        fprintf (fp, " 33\n%f\n", dxf_3dface->z3);
        if (dxf_3dface->thickness != 0.0)
        {
                fprintf (fp, " 39\n%f\n", dxf_3dface->thickness);
        }
        if (dxf_3dface->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp, " 62\n%d\n", dxf_3dface->color);
        }
        if (dxf_3dface->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
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
