/*!
 * \file image.c
 *
 * \author Copyright (C) 2013 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF image entity (\c IMAGE).
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


#include "image.h"


/*!
 * \brief Allocate memory for a DXF \c IMAGE.
 *
 * Fill the memory contents with zeros.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfImage *
dxf_image_new ()
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_image_new () function.\n",
                __FILE__, __LINE__);
#endif
        DxfImage *dxf_image = NULL;
        size_t size;

        size = sizeof (DxfImage);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_image = malloc (size)) == NULL)
        {
                fprintf (stderr, "ERROR in dxf_image_new () could not allocate memory for a DxfImage struct.\n");
                dxf_image = NULL;
        }
        else
        {
                memset (dxf_image, 0, size);
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_image_new () function.\n",
                __FILE__, __LINE__);
#endif
        return (dxf_image);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c IMAGE
 * entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfImage *
dxf_image_init
(
        DxfImage *dxf_image
                /*!< DXF image entity. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_image_init () function.\n",
                __FILE__, __LINE__);
#endif
        int i;

        dxf_image = dxf_image_new ();
        if (dxf_image == NULL)
        {
              fprintf (stderr, "ERROR in dxf_image_init () could not allocate memory for a DxfImage struct.\n");
              return (NULL);
        }
        dxf_image->id_code = 0;
        dxf_image->linetype = strdup (DXF_DEFAULT_LINETYPE);
        dxf_image->layer = strdup (DXF_DEFAULT_LAYER);
        dxf_image->thickness = 0.0;
        dxf_image->color = DXF_COLOR_BYLAYER;
        dxf_image->paperspace = DXF_MODELSPACE;
        dxf_image->x0 = 0.0;
        dxf_image->y0 = 0.0;
        dxf_image->z0 = 0.0;
        dxf_image->x1 = 0.0;
        dxf_image->y1 = 0.0;
        dxf_image->z1 = 0.0;
        dxf_image->x2 = 0.0;
        dxf_image->y2 = 0.0;
        dxf_image->z2 = 0.0;
        dxf_image->x3 = 0.0;
        dxf_image->y3 = 0.0;
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                dxf_image->x4[i] = 0.0;
                dxf_image->y4[i] = 0.0;
        }
        dxf_image->image_display_properties = 0;
        dxf_image->clipping_boundary_type = 0;
        dxf_image->class_version = 0;
        dxf_image->number_of_clip_boundary_vertices = 0;
        dxf_image->clipping_state = 0;
        dxf_image->brightness = 50;
        dxf_image->contrast = 50;
        dxf_image->fade = 50;
        dxf_image->imagedef_object = strdup ("");
        dxf_image->imagedef_reactor_object = strdup ("");
        dxf_image->next = NULL;
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_image_init () function.\n",
                __FILE__, __LINE__);
#endif
        return (dxf_image);
}


/*!
 * \brief Read data from a DXF file into a DXF \c IMAGE entity.
 *
 * The last line read from file contained the string "IMAGE". \n
 * Now follows some data for the \c IMAGE, to be terminated with a "  0"
 * string announcing the following entity, or the end of the \c ENTITY
 * section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c dxf_image. \n
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_image_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfImage *dxf_image
                /*!< DXF \c IMAGE entity. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_image_read () function.\n",
                __FILE__, __LINE__);
#endif
        char *temp_string = NULL;
        int i;
        int j;

        if (!dxf_image)
        {
                dxf_image = dxf_image_new ();
        }
        i = 0;
        j = 0;
        (fp->line_number)++;
        fscanf (fp->fp, "%[^\n]", temp_string);
        while (strcmp (temp_string, "0") != 0)
        {
                if (ferror (fp->fp))
                {
                        fprintf (stderr, "Error in dxf_arc_read () while reading from: %s in line: %d.\n",
                                fp->filename, fp->line_number);
                        fclose (fp->fp);
                        return (EXIT_FAILURE);
                }
                if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", &dxf_image->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_image->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_image->layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-value of the insertion point coordinate. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_image->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the insertion point coordinate. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_image->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the insertion point coordinate. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_image->z1);
                }
                else if (strcmp (temp_string, "11") == 0)
                {
                        /* Now follows a string containing the
                         * X-value of the U-vector of a single pixel. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_image->x1);
                }
                else if (strcmp (temp_string, "21") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the U-vector of a single pixel. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_image->y1);
                }
                else if (strcmp (temp_string, "31") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the U-vector of a single pixel. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_image->z1);
                }
                else if (strcmp (temp_string, "12") == 0)
                {
                        /* Now follows a string containing the
                         * X-value of the V-vector of a single pixel. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_image->x2);
                }
                else if (strcmp (temp_string, "22") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the V-vector of a single pixel. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_image->y2);
                }
                else if (strcmp (temp_string, "32") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the V-vector of a single pixel. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_image->z2);
                }
                else if (strcmp (temp_string, "13") == 0)
                {
                        /* Now follows a string containing the
                         * U-value of image size in pixels. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_image->x3);
                }
                else if (strcmp (temp_string, "23") == 0)
                {
                        /* Now follows a string containing the
                         * V-value of image size in pixels. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_image->y3);
                }
                else if (strcmp (temp_string, "14") == 0)
                {
                        /* Now follows a string containing the
                         * X-value of a clip boundary vertex. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_image->x4[i]);
                        i++;
                }
                else if (strcmp (temp_string, "24") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of a clip boundary vertex. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_image->y4[j]);
                        j++;
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_image->thickness);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_image->color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_image->paperspace);
                }
                else if (strcmp (temp_string, "70") == 0)
                {
                        /* Now follows a string containing the
                         * image display properties. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_image->image_display_properties);
                }
                else if (strcmp (temp_string, "71") == 0)
                {
                        /* Now follows a string containing the
                         * clipping boundary type. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_image->clipping_boundary_type);
                }
                else if (strcmp (temp_string, "90") == 0)
                {
                        /* Now follows a string containing the class
                         * version. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%ld\n", &dxf_image->class_version);
                }
                else if (strcmp (temp_string, "91") == 0)
                {
                        /* Now follows a string containing the number of
                         * clip boundary vertices. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%ld\n", &dxf_image->number_of_clip_boundary_vertices);
                }
                else if (strcmp (temp_string, "280") == 0)
                {
                        /* Now follows a string containing the clipping
                         * state. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_image->clipping_state);
                }
                else if (strcmp (temp_string, "281") == 0)
                {
                        /* Now follows a string containing the
                         * brightness value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_image->brightness);
                }
                else if (strcmp (temp_string, "282") == 0)
                {
                        /* Now follows a string containing the contrast
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_image->contrast);
                }
                else if (strcmp (temp_string, "283") == 0)
                {
                        /* Now follows a string containing the fade
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_image->fade);
                }
                else if (strcmp (temp_string, "340") == 0)
                {
                        /* Now follows a string containing a hard
                         * reference to imagedef object. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_image->imagedef_object);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing a hard
                         * reference to imagedef_reactor object. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_image->imagedef_reactor_object);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
                        if ((strcmp (temp_string, "AcDbEntity") != 0)
                        && ((strcmp (temp_string, "AcDbRasterImage") != 0)))
                        {
                                fprintf (stderr, "Error in dxf_image_read () found a bad subclass marker in: %s in line: %d.\n",
                                        fp->filename, fp->line_number);
                        }
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
                        fprintf (stderr, "Warning: in dxf_image_read () unknown string tag found while reading from: %s in line: %d.\n",
                                fp->filename, fp->line_number);
                }
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_image_read () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write DXF output for a DXF \c IMAGE entity.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_image_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfImage *dxf_image
                /*!< DXF \c IMAGE entity. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_image_write () function.\n",
                __FILE__, __LINE__);
#endif
        char *dxf_entity_name = strdup ("IMAGE");
        int i;

        if (dxf_image == NULL)
        {
                fprintf (stderr, "Error in dxf_image_write () a NULL pointer was passed.\n");
                return (EXIT_FAILURE);
        }
        if (strcmp (dxf_image->layer, "") == 0)
        {
                fprintf (stderr, "Warning in dxf_image_write () empty layer string for the %s entity with id-code: %x.\n",
                        dxf_entity_name, dxf_image->id_code);
                fprintf (stderr, "\t%s entity is relocated to default layer.\n",
                        dxf_entity_name);
                dxf_image->layer = DXF_DEFAULT_LAYER;
        }
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
                fprintf (fp->fp, "100\nAcDbRasterImage\n");
        }
        if (dxf_image->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", dxf_image->id_code);
        }
        if (strcmp (dxf_image->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", dxf_image->linetype);
        }
        fprintf (fp->fp, "  8\n%s\n", dxf_image->layer);
        fprintf (fp->fp, " 10\n%f\n", dxf_image->x0);
        fprintf (fp->fp, " 20\n%f\n", dxf_image->y0);
        fprintf (fp->fp, " 30\n%f\n", dxf_image->z0);
        fprintf (fp->fp, " 11\n%f\n", dxf_image->x1);
        fprintf (fp->fp, " 21\n%f\n", dxf_image->y1);
        fprintf (fp->fp, " 31\n%f\n", dxf_image->z1);
        fprintf (fp->fp, " 12\n%f\n", dxf_image->x2);
        fprintf (fp->fp, " 22\n%f\n", dxf_image->y2);
        fprintf (fp->fp, " 32\n%f\n", dxf_image->z2);
        fprintf (fp->fp, " 13\n%f\n", dxf_image->x3);
        fprintf (fp->fp, " 23\n%f\n", dxf_image->y3);
        for (i = 0; i < dxf_image->number_of_clip_boundary_vertices; i++)
        {
                fprintf (fp->fp, " 14\n%f\n", dxf_image->x4[i]);
                fprintf (fp->fp, " 24\n%f\n", dxf_image->y4[i]);
        }
        if (dxf_image->thickness != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", dxf_image->thickness);
        }
        if (dxf_image->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", dxf_image->color);
        }
        if (dxf_image->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
        fprintf (fp->fp, " 70\n%d\n", dxf_image->image_display_properties);
        fprintf (fp->fp, " 71\n%d\n", dxf_image->clipping_boundary_type);
        fprintf (fp->fp, " 90\n%ld\n", dxf_image->class_version);
        fprintf (fp->fp, " 91\n%ld\n", dxf_image->number_of_clip_boundary_vertices);
        fprintf (fp->fp, "280\n%d\n", dxf_image->clipping_state);
        fprintf (fp->fp, "281\n%d\n", dxf_image->brightness);
        fprintf (fp->fp, "282\n%d\n", dxf_image->contrast);
        fprintf (fp->fp, "283\n%d\n", dxf_image->fade);
        fprintf (fp->fp, "340\n%s\n", dxf_image->imagedef_object);
        fprintf (fp->fp, "360\n%s\n", dxf_image->imagedef_reactor_object);
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_image_write () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c IMAGE and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_image_free
(
        DxfImage *dxf_image
                /*!< Pointer to the memory occupied by the DXF \c IMAGE
                 * entity. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_image_free () function.\n",
                __FILE__, __LINE__);
#endif
        if (dxf_image->next != NULL)
        {
              fprintf (stderr, "ERROR in dxf_image_free () pointer to next DxfImage was not NULL.\n");
              return (EXIT_FAILURE);
        }
        free (dxf_image->linetype);
        free (dxf_image->layer);
        free (dxf_image->imagedef_object);
        free (dxf_image->imagedef_reactor_object);
        free (dxf_image);
        dxf_image = NULL;
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_image_free () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/* EOF*/
