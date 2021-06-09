/*!
 * \file 3dface.c
 *
 * \author Copyright (C) 2010, 2012, 2013, 2014, 2015, 2016, 2017, 2018,
 * 2019, 2020, 2021 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF 3D face entity (\c 3DFACE).
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
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
 * For more details see http://www.autodesk.com.
 * <hr>
 */


#include "3dface.h"


/*!
 * \brief Allocate memory for a DXF \c 3DFACE entity.
 *
 * Fill the memory contents with zeros.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_new.png
 *
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
Dxf3dface *
dxf_3dface_new ()
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        Dxf3dface *face = NULL;
        size_t size;

        size = sizeof (Dxf3dface);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((face = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                face = NULL;
        }
        else
        {
                memset (face, 0, size);
        }
#ifdef DEBUG
        DXF_DEBUG_END
#endif
        return (face);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c 3DFACE
 * entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_init.png
 *
 * \return \c NULL when an error occurred, a pointer to the initialized
 * memory when successful.
 */
Dxf3dface *
dxf_3dface_init
(
        Dxf3dface *face
                /*!< a pointer to a DXF \c 3DFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                face = dxf_3dface_new ();
        }
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        /* Assign initial values to members. */
        face->id_code = 0;
        face->linetype = strdup (DXF_DEFAULT_LINETYPE);
        face->layer = strdup (DXF_DEFAULT_LAYER);
        face->elevation = 0.0;
        face->thickness = 0.0;
        face->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        face->visibility = DXF_DEFAULT_VISIBILITY;
        face->color = DXF_COLOR_BYLAYER;
        face->paperspace = DXF_MODELSPACE;
        face->graphics_data_size = 0;
        face->shadow_mode = 0;
        face->dictionary_owner_soft = strdup ("");
        face->object_owner_soft = strdup ("");
        face->material = strdup ("");
        face->dictionary_owner_hard = strdup ("");
        face->lineweight = 0;
        face->plot_style_name = strdup ("");
        face->color_value = 0;
        face->color_name = strdup ("");
        face->transparency = 0;
        face->flag = 0;
        /* Initialize new structs for the following members later,
         * when they are required and when we have content. */
        face->binary_graphics_data = NULL;
        face->p0 = NULL;
        face->p1 = NULL;
        face->p2 = NULL;
        face->p3 = NULL;
        face->next = NULL;
#ifdef DEBUG
        DXF_DEBUG_END
#endif
        return (face);
}


/*!
 * \brief Read data from a DXF file into a DXF \c 3DFACE entity.
 *
 * The last line read from file contained the string "3DFACE". \n
 * Now follows some data for the \c 3DFACE, to be terminated with a "  0"
 * string announcing the following entity, or the end of the \c ENTITY
 * section marker \c ENDSEC. \n
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_read.png
 *
 * \return a pointer to a DXF \c 3DFACE entity, or \c NULL when an error
 * occurred.
 */
Dxf3dface *
dxf_3dface_read
(
        DxfFile *fp,
                /*!< a DXF \c FILE pointer to an input file (or device). */
        Dxf3dface *face
                /*!< a pointer to a DXF \c 3DFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *temp_string = NULL;
        DxfBinaryData *iter310 = NULL;
        int iter330;

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
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                face = dxf_3dface_init (face);
        }
        if (face->binary_graphics_data == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfBinaryData struct.\n")));
                face->binary_graphics_data = dxf_binary_data_init (face->binary_graphics_data);
                if (face->binary_graphics_data == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        if (face->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                face->p0 = dxf_point_init (face->p0);
                if (face->p0 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        if (face->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                face->p1 = dxf_point_init (face->p1);
                if (face->p1 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        if (face->p2 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                face->p2 = dxf_point_init (face->p2);
                if (face->p2 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        if (face->p3 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                face->p3 = dxf_point_init (face->p3);
                if (face->p3 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        iter310 = (DxfBinaryData *) face->binary_graphics_data;
        iter330 = 0;
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
                        fscanf (fp->fp, "%x\n", (uint *) &face->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, face->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, face->layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the first point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &face->p0->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the first point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &face->p0->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of first the point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &face->p0->z0);
                }
                else if (strcmp (temp_string, "11") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the second point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &face->p1->x0);
                }
                else if (strcmp (temp_string, "21") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the second point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &face->p1->y0);
                }
                else if (strcmp (temp_string, "31") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the second point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &face->p1->z0);
                }
                else if (strcmp (temp_string, "12") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the third point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &face->p2->x0);
                }
                else if (strcmp (temp_string, "22") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the third point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &face->p2->y0);
                }
                else if (strcmp (temp_string, "32") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the third point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &face->p2->z0);
                }
                else if (strcmp (temp_string, "13") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the fourth point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &face->p3->x0);
                }
                else if (strcmp (temp_string, "23") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the fourth point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &face->p3->y0);
                }
                else if (strcmp (temp_string, "33") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the fourth point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &face->p3->z0);
                }
                else if ((strcmp (temp_string, "38") == 0))
                {
                        /* Now follows a string containing the
                         * elevation. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &face->elevation);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &face->thickness);
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing the linetype
                         * scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &face->linetype_scale);
                }
                else if (strcmp (temp_string, "60") == 0)
                {
                        /* Now follows a string containing the
                         * visibility value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &face->visibility);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &face->color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &face->paperspace);
                }
                else if (strcmp (temp_string, "70") == 0)
                {
                        /* Now follows a string containing the
                         * value of edge visibility flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &face->flag);
                }
                else if (strcmp (temp_string, "92") == 0)
                {
                        /* Now follows a string containing the
                         * graphics data size value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%" PRIi32 "\n", &face->graphics_data_size);
                }
                else if (strcmp (temp_string, "100") == 0)
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if ((strcmp (temp_string, "AcDbEntity") != 0)
                        && (strcmp (temp_string, "AcDbFace") != 0))
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () found a bad subclass marker in: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                        }
                }
                else if (strcmp (temp_string, "160") == 0)
                {
                        /* Now follows a string containing the
                         * graphics data size value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%" PRIi32 "\n", &face->graphics_data_size);
                }
                else if (strcmp (temp_string, "284") == 0)
                {
                        /* Now follows a string containing the shadow
                         * mode value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &face->shadow_mode);
                }
                else if (strcmp (temp_string, "310") == 0)
                {
                        /* Now follows a string containing binary
                         * graphics data. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, iter310->data_line);
                        dxf_binary_data_init ((DxfBinaryData *) iter310->next);
                        iter310 = (DxfBinaryData *) iter310->next;
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        if (iter330 == 0)
                        {
                                /* Now follows a string containing a soft-pointer
                                 * ID/handle to owner dictionary. */
                                (fp->line_number)++;
                                fscanf (fp->fp, DXF_MAX_STRING_FORMAT, face->dictionary_owner_soft);
                        }
                        if (iter330 == 1)
                        {
                                /* Now follows a string containing a soft-pointer
                                 * ID/handle to owner object. */
                                (fp->line_number)++;
                                fscanf (fp->fp, DXF_MAX_STRING_FORMAT, face->object_owner_soft);
                        }
                        iter330++;
                }
                else if (strcmp (temp_string, "347") == 0)
                {
                        /* Now follows a string containing a
                         * hard-pointer ID/handle to material object. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, face->material);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, face->dictionary_owner_hard);
                }
                else if (strcmp (temp_string, "370") == 0)
                {
                        /* Now follows a string containing the lineweight
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &face->lineweight);
                }
                else if (strcmp (temp_string, "390") == 0)
                {
                        /* Now follows a string containing a plot style
                         * name value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, face->plot_style_name);
                }
                else if (strcmp (temp_string, "420") == 0)
                {
                        /* Now follows a string containing a color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%" PRIi32 "\n", &face->color_value);
                }
                else if (strcmp (temp_string, "430") == 0)
                {
                        /* Now follows a string containing a color
                         * name value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", face->color_name);
                }
                else if (strcmp (temp_string, "440") == 0)
                {
                        /* Now follows a string containing a transparency
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%" PRIi32 "\n", &face->transparency);
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
        /* Handle omitted members and/or illegal values. */
        if (strcmp (face->linetype, "") == 0)
        {
                face->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (face->layer, "") == 0)
        {
                face->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Clean up. */
        free (temp_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face);
}


/*!
 * \brief Write DXF output to a file for a DXF \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_write.png
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_3dface_write
(
        DxfFile *fp,
                /*!< a DXF \c FILE pointer to an output file (or device). */
        Dxf3dface *face
                /*!< a pointer to a DXF \c 3DFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("3DFACE");

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
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if ((strcmp (face->layer, "") == 0) || (face->layer == NULL))
        {
                fprintf (stderr,
                  (_("Warning in %s () invalid layer string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, face->id_code);
                fprintf (stderr,
                  (_("\t%s entity is relocated to layer 0")),
                  dxf_entity_name);
                face->layer = strdup (DXF_DEFAULT_LAYER);
        }
        if (face->linetype == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () invalid linetype string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, face->id_code);
                fprintf (stderr,
                  (_("\t%s linetype is set to %s\n")),
                  dxf_entity_name, DXF_DEFAULT_LINETYPE);
                face->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (face->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", face->id_code);
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
        if ((strcmp (face->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", face->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (face->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", face->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (face->object_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_2000))
        {
                fprintf (fp->fp, "330\n%s\n", face->object_owner_soft);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
        }
        if (face->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%hd\n", (int16_t) DXF_PAPERSPACE);
        }
        fprintf (fp->fp, "  8\n%s\n", face->layer);
        if (strcmp (face->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", face->linetype);
        }
        if ((fp->acad_version_number >= AutoCAD_2008)
          && (strcmp (face->material, "") != 0))
        {
                fprintf (fp->fp, "347\n%s\n", face->material);
        }
        if (face->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%hd\n", face->color);
        }
        if (fp->acad_version_number >= AutoCAD_2002)
        {
                fprintf (fp->fp, "370\n%d\n", face->lineweight);
        }
        if ((fp->acad_version_number <= AutoCAD_11)
          && DXF_FLATLAND
          && (face->elevation != 0.0))
        {
                fprintf (fp->fp, " 38\n%f\n", face->elevation);
        }
        if ((fp->acad_version_number <= AutoCAD_13)
          && (face->thickness != 0.0))
        {
                fprintf (fp->fp, " 39\n%f\n", face->thickness);
        }
        if (face->linetype_scale != 1.0)
        {
                fprintf (fp->fp, " 48\n%f\n", face->linetype_scale);
        }
        if (face->visibility != 0)
        {
                fprintf (fp->fp, " 60\n%d\n", face->visibility);
        }
        if ((fp->acad_version_number >= AutoCAD_2000)
          && (face->binary_graphics_data != NULL))
        {
#ifdef BUILD_64
                fprintf (fp->fp, "160\n%" PRIi32 "\n", face->graphics_data_size);
#else
                fprintf (fp->fp, " 92\n%" PRIi32 "\n", face->graphics_data_size);
#endif
                if (face->binary_graphics_data)
                {
                        DxfBinaryData *iter;
                        iter = (DxfBinaryData *) face->binary_graphics_data;
                        while (iter != NULL)
                        {
                                fprintf (fp->fp, "310\n%s\n", iter->data_line);
                                iter = (DxfBinaryData *) iter->next;
                        }
                }
        }
        if (fp->acad_version_number >= AutoCAD_2004)
        {
                fprintf (fp->fp, "420\n%" PRIi32 "\n", face->color_value);
                fprintf (fp->fp, "430\n%s\n", face->color_name);
                fprintf (fp->fp, "440\n%" PRIi32 "\n", face->transparency);
        }
        if (fp->acad_version_number >= AutoCAD_2009)
        {
                fprintf (fp->fp, "390\n%s\n", face->plot_style_name);
                fprintf (fp->fp, "284\n%d\n", face->shadow_mode);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbFace\n");
        }
        if (face->p0 != NULL)
        {
                fprintf (fp->fp, " 10\n%f\n", face->p0->x0);
                fprintf (fp->fp, " 20\n%f\n", face->p0->y0);
                fprintf (fp->fp, " 30\n%f\n", face->p0->z0);
        }
        if (face->p1 != NULL)
        {
                fprintf (fp->fp, " 11\n%f\n", face->p1->x0);
                fprintf (fp->fp, " 21\n%f\n", face->p1->y0);
                fprintf (fp->fp, " 31\n%f\n", face->p1->z0);
        }
        if (face->p2 != NULL)
        {
                fprintf (fp->fp, " 12\n%f\n", face->p2->x0);
                fprintf (fp->fp, " 22\n%f\n", face->p2->y0);
                fprintf (fp->fp, " 32\n%f\n", face->p2->z0);
        }
        if (face->p3)
        {
                fprintf (fp->fp, " 13\n%f\n", face->p3->x0);
                fprintf (fp->fp, " 23\n%f\n", face->p3->y0);
                fprintf (fp->fp, " 33\n%f\n", face->p3->z0);
        }
        fprintf (fp->fp, " 70\n%hd\n", face->flag);
        /* Clean up. */
        free (dxf_entity_name);
#ifdef DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c 3DFACE and all it's
 * data fields.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_free.png
 *
 * \return \c NULL when successful, or pointer to \c face when an error
 * occurred.
 */
Dxf3dface *
dxf_3dface_free
(
        Dxf3dface *face
                /*!< a pointer to the memory occupied by the DXF
                 * \c 3DFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (face->next != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to next was not NULL.\n")),
                __FUNCTION__);
              return (face);
        }
        free (face->linetype);
        free (face->layer);
        dxf_binary_data_free_list (face->binary_graphics_data);
        free (face->dictionary_owner_soft);
        free (face->object_owner_soft);
        free (face->material);
        free (face->dictionary_owner_hard);
        free (face->plot_style_name);
        free (face->color_name);
        dxf_point_free_list (face->p0);
        dxf_point_free_list (face->p1);
        dxf_point_free_list (face->p2);
        dxf_point_free_list (face->p3);
        free (face);
        face = NULL;
#ifdef DEBUG
        DXF_DEBUG_END
#endif
        return (face);
}


/*!
 * \brief Free the allocated memory for a single linked list of
 * DXF \c 3DFACE entities and all their data fields.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_free_list.png
 */
void
dxf_3dface_free_list
(
        Dxf3dface *faces
                /*!< a pointer to the single linked list of DXF
                 * \c 3DFACE entities. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (faces == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (faces != NULL)
        {
                Dxf3dface *iter = (Dxf3dface *) faces->next;
                dxf_3dface_free (faces);
                faces = (Dxf3dface *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the \c id_code from a DXF \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_get_id_code.png
 *
 * \return \c id_code.
 */
int
dxf_3dface_get_id_code
(
        Dxf3dface *face
                /*!< a pointer to a DXF \c 3DFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (face->id_code < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face->id_code);
}


/*!
 * \brief Set the \c id_code for a DXF \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_set_id_code.png
 *
 * \return a pointer to \c face when sucessful, \c NULL when an error
 * occurred.
 */
Dxf3dface *
dxf_3dface_set_id_code
(
        Dxf3dface *face,
                /*!< a pointer to a DXF \c 3DFACE entity. */
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
        if (face == NULL)
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
        face->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face);
}


/*!
 * \brief Get the linetype from a DXF \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_get_linetype.png
 *
 * \return a pointer to \c linetype when sucessful, \c NULL when an
 * error occurred.
 */
char *
dxf_3dface_get_linetype
(
        Dxf3dface *face
                /*!< a pointer to a DXF \c 3DFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (face->linetype ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (face->linetype));
}


/*!
 * \brief Set the \c linetype for a DXF \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_set_linetype.png
 *
 * \return a pointer to \c face when sucessful, \c NULL when an error
 * occurred.
 *
 * \warning The passed \c linetype variable is not freed by this
 * function.
 */
Dxf3dface *
dxf_3dface_set_linetype
(
        Dxf3dface *face,
                /*!< a pointer to a DXF \c 3DFACE entity. */
        char *linetype
                /*!< a string containing the \c linetype for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
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
        face->linetype = strdup (linetype);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face);
}


/*!
 * \brief Get the \c layer from a DXF \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_get_layer.png
 *
 * \return a pointer to \c layer when sucessful, \c NULL when an error
 * occurred.
 */
char *
dxf_3dface_get_layer
(
        Dxf3dface *face
                /*!< a pointer to a DXF \c 3DFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (face->layer ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (face->layer));
}


/*!
 * \brief Set the \c layer for a DXF \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_set_layer.png
 *
 * \return a pointer to \c face when sucessful, \c NULL when an error
 * occurred.
 *
 * \warning The passed \c layer variable is not freed by this function.
 */
Dxf3dface *
dxf_3dface_set_layer
(
        Dxf3dface *face,
                /*!< a pointer to a DXF \c 3DFACE entity. */
        char *layer
                /*!< a string containing the \c layer for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
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
        face->layer = strdup (layer);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face);
}


/*!
 * \brief Get the \c elevation a this DXF \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_get_elevation.png
 *
 * \return \c elevation.
 */
double
dxf_3dface_get_elevation
(
        Dxf3dface *face
                /*!< a pointer to a DXF \c 3DFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face->elevation);
}


/*!
 * \brief Set the \c elevation for a DXF \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_set_elevation.png
 *
 * \return a pointer to \c face when sucessful, \c NULL when an error
 * occurred.
 */
Dxf3dface *
dxf_3dface_set_elevation
(
        Dxf3dface *face,
                /*!< a pointer to a DXF \c 3DFACE entity. */
        double elevation
                /*!< the \c elevation to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        face->elevation = elevation;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face);
}


/*!
 * \brief Get the \c thickness from a DXF \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_get_thickness.png
 *
 * \return \c thickness.
 */
double
dxf_3dface_get_thickness
(
        Dxf3dface *face
                /*!< a pointer to a DXF \c 3DFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (face->thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face->thickness);
}


/*!
 * \brief Set the \c thickness for a DXF \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_set_thickness.png
 *
 * \return a pointer to \c face when sucessful, \c NULL when an error
 * occurred.
 */
Dxf3dface *
dxf_3dface_set_thickness
(
        Dxf3dface *face,
                /*!< a pointer to a DXF \c 3DFACE entity. */
        double thickness
                /*!< the \c thickness to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        face->thickness = thickness;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face);
}


/*!
 * \brief Get the \c linetype_scale from a DXF \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_get_linetype_scale.png
 *
 * \return \c linetype_scale.
 */
double
dxf_3dface_get_linetype_scale
(
        Dxf3dface *face
                /*!< a pointer to a DXF \c 3DFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (face->linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face->linetype_scale);
}


/*!
 * \brief Set the \c linetype_scale for a DXF \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_set_linetype_scale.png
 *
 * \return a pointer to \c face when sucessful, \c NULL when an error
 * occurred.
 */
Dxf3dface *
dxf_3dface_set_linetype_scale
(
        Dxf3dface *face,
                /*!< a pointer to a DXF \c 3DFACE entity. */
        double linetype_scale
                /*!< the \c linetype_scale to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        face->linetype_scale = linetype_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face);
}


/*!
 * \brief Get the \c visibility from a DXF \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_get_visibility.png
 *
 * \return \c visibility.
 */
int16_t
dxf_3dface_get_visibility
(
        Dxf3dface *face
                /*!< a pointer to a DXF \c 3DFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (face->visibility < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (face->visibility > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face->visibility);
}


/*!
 * \brief Set the \c visibility for a DXF \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_set_visibility.png
 *
 * \return a pointer to \c face when sucessful, \c NULL when an error
 * occurred.
 */
Dxf3dface *
dxf_3dface_set_visibility
(
        Dxf3dface *face,
                /*!< a pointer to a DXF \c 3DFACE entity. */
        int16_t visibility
                /*!< the visibility to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (visibility < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (visibility > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        face->visibility = visibility;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face);
}


/*!
 * \brief Get the \c color from a DXF \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_get_color.png
 *
 * \return \c color.
 */
int16_t
dxf_3dface_get_color
(
        Dxf3dface *face
                /*!< a pointer to a DXF \c 3DFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (face->color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face->color);
}


/*!
 * \brief Set the \c color for a DXF \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_set_color.png
 *
 * \return a pointer to \c face when sucessful, \c NULL when an error
 * occurred.
 */
Dxf3dface *
dxf_3dface_set_color
(
        Dxf3dface *face,
                /*!< a pointer to a DXF \c 3DFACE entity. */
        int16_t color
                /*!< the \c color to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
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
        face->color = color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face);
}


/*!
 * \brief Get the \c paperspace flag value from a DXF \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_get_paperspace.png
 *
 * \return \c paperspace flag value.
 */
int16_t
dxf_3dface_get_paperspace
(
        Dxf3dface *face
                /*!< a pointer to a DXF \c 3DFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (face->paperspace < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (face->paperspace > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face->paperspace);
}


/*!
 * \brief Set the \c paperspace flag for a DXF \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_set_paperspace.png
 *
 * \return a pointer to \c face when sucessful, \c NULL when an error
 * occurred.
 */
Dxf3dface *
dxf_3dface_set_paperspace
(
        Dxf3dface *face,
                /*!< a pointer to a DXF \c 3DFACE entity. */
        int16_t paperspace
                /*!< the \c paperspace flag value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (paperspace < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (paperspace > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        face->paperspace = paperspace;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face);
}


/*!
 * \brief Get the \c graphics_data_size value from a DXF \c 3DFACE
 * entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_get_graphics_data_size.png
 *
 * \return \c graphics_data_size value when successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
int32_t
dxf_3dface_get_graphics_data_size
(
        Dxf3dface *face
                /*!< a pointer to a DXF \c 3DFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (face->graphics_data_size < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (face->graphics_data_size == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face->graphics_data_size);
}


/*!
 * \brief Set the \c graphics_data_size value for a DXF \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_set_graphics_data_size.png
 *
 * \return a pointer to \c face when successful, or \c NULL when an
 * error occurred.
 */
Dxf3dface *
dxf_3dface_set_graphics_data_size
(
        Dxf3dface *face,
                /*!< a pointer to a DXF \c 3DFACE entity. */
        int32_t graphics_data_size
                /*!< the \c graphics_data_size value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
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
        face->graphics_data_size = graphics_data_size;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face);
}


/*!
 * \brief Get the \c shadow_mode from a DXF \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_get_shadow_mode.png
 *
 * \return \c shadow_mode when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_3dface_get_shadow_mode
(
        Dxf3dface *face
                /*!< a pointer to a DXF \c 3DFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (face->shadow_mode < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (face->shadow_mode > 3)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face->shadow_mode);
}


/*!
 * \brief Set the \c shadow_mode for a DXF \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_set_shadow_mode.png
 *
 * \return a pointer to \c face when successful, or \c NULL when an
 * error occurred.
 */
Dxf3dface *
dxf_3dface_set_shadow_mode
(
        Dxf3dface *face,
                /*!< a pointer to a DXF \c 3DFACE entity. */
        int16_t shadow_mode
                /*!< the shadow mode to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (shadow_mode < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (shadow_mode > 3)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        face->shadow_mode = shadow_mode;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face);
}


/*!
 * \brief Get the pointer to the \c binary_graphics_data from a DXF
 * \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_get_binary_graphics_data.png
 *
 * \return pointer to the \c binary_graphics_data.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfBinaryData *
dxf_3dface_get_binary_graphics_data
(
        Dxf3dface *face
                /*!< a pointer to a DXF \c 3DFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (face->binary_graphics_data ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfBinaryData *) face->binary_graphics_data);
}


/*!
 * \brief Set the pointer to the \c binary_graphics_data for a DXF
 * \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_set_binary_graphics_data.png
 */
Dxf3dface *
dxf_3dface_set_binary_graphics_data
(
        Dxf3dface *face,
                /*!< a pointer to a DXF \c 3DFACE entity. */
        DxfBinaryData *data
                /*!< a string containing the pointer to the
                 * \c binary_graphics_data for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
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
        face->binary_graphics_data = (DxfBinaryData *) data;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face);
}


/*!
 * \brief Get the soft pointer to the \c dictionary_owner_soft from a
 * DXF \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_get_dictionary_owner_soft.png
 *
 * \return a pointer to the \c dictionary_owner_soft.
 *
 * \warning No checks are performed on the returned pointer.
 */
char *
dxf_3dface_get_dictionary_owner_soft
(
        Dxf3dface *face
                /*!< a pointer to a DXF \c 3DFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (face->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (face->dictionary_owner_soft));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_soft for a DXF
 * \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_set_dictionary_owner_soft.png
 */
Dxf3dface *
dxf_3dface_set_dictionary_owner_soft
(
        Dxf3dface *face,
                /*!< a pointer to a DXF \c 3DFACE entity. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the
                 * \c dictionary_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
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
        face->dictionary_owner_soft = strdup (dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face);
}


/*!
 * \brief Get the soft pointer to the object owner from a DXF 
 * \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_get_object_owner_soft.png
 *
 * \return soft pointer to the object owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_3dface_get_object_owner_soft
(
        Dxf3dface *face
                /*!< a pointer to a DXF \c 3DFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (face->object_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (face->object_owner_soft));
}


/*!
 * \brief Set the pointer to the \c object_owner_soft for a DXF
 * \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_set_object_owner_soft.png
 */
Dxf3dface *
dxf_3dface_set_object_owner_soft
(
        Dxf3dface *face,
                /*!< a pointer to a DXF \c 3DFACE entity. */
        char *object_owner_soft
                /*!< a string containing the pointer to the
                 * \c object_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (object_owner_soft == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        face->object_owner_soft = strdup (object_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face);
}


/*!
 * \brief Get the pointer to the \c material from a DXF \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_get_material.png
 *
 * \return a pointer to \c material when successful, or \c NULL when an
 * error occurred.
 *
 * \warning No checks are performed on the returned pointer.
 */
char *
dxf_3dface_get_material
(
        Dxf3dface *face
                /*!< a pointer to a DXF \c 3DFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (face->material ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (face->material));
}


/*!
 * \brief Set the pointer to the \c material for a DXF \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_set_material.png
 *
 * \return a pointer to \c face when successful, or \c NULL when an
 * error occurred.
 */
Dxf3dface *
dxf_3dface_set_material
(
        Dxf3dface *face,
                /*!< a pointer to a DXF \c 3DFACE entity. */
        char *material
                /*!< a string containing the pointer to the \c
                 * material for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
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
        face->material = strdup (material);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_hard from a DXF 
 * \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_get_dictionary_owner_hard.png
 *
 * \return a pointer to the \c dictionary_owner_hard.
 *
 * \warning No checks are performed on the returned pointer.
 */
char *
dxf_3dface_get_dictionary_owner_hard
(
        Dxf3dface *face
                /*!< a pointer to a DXF \c 3DFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (face->dictionary_owner_hard ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (face->dictionary_owner_hard));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_hard for a DXF
 * \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_set_dictionary_owner_hard.png
 *
 * \return a pointer to \c face when sucessful, \c NULL when an error
 * occurred.
 */
Dxf3dface *
dxf_3dface_set_dictionary_owner_hard
(
        Dxf3dface *face,
                /*!< a pointer to a DXF \c 3DFACE entity. */
        char *dictionary_owner_hard
                /*!< a string containing the pointer to the \c
                 * dictionary_owner_hard for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
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
        face->dictionary_owner_hard = strdup (dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face);
}


/*!
 * \brief Get the \c lineweight from a DXF \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_get_lineweight.png
 *
 * \return \c lineweight when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_3dface_get_lineweight
(
        Dxf3dface *face
                /*!< a pointer to a DXF \c 3DFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face->lineweight);
}


/*!
 * \brief Set the \c lineweight for a DXF \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_set_lineweight.png
 *
 * \return a pointer to \c face when successful, or \c NULL when an
 * error occurred.
 */
Dxf3dface *
dxf_3dface_set_lineweight
(
        Dxf3dface *face,
                /*!< a pointer to a DXF \c 3DFACE entity. */
        int16_t lineweight
                /*!< the \c lineweight to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        face->lineweight = lineweight;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face);
}


/*!
 * \brief Get the \c plot_style_name from a DXF \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_get_plot_style_name.png
 *
 * \return a pointer to \c plot_style_name when sucessful, or \c NULL
 * when an error occurred.
 */
char *
dxf_3dface_get_plot_style_name
(
        Dxf3dface *face
                /*!< a pointer to a DXF \c 3DFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (face->plot_style_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (face->plot_style_name));
}


/*!
 * \brief Set the \c plot_style_name for a DXF \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_set_plot_style_name.png
 *
 * \return a pointer to \c face when successful, or \c NULL when an
 * error occurred.
 */
Dxf3dface *
dxf_3dface_set_plot_style_name
(
        Dxf3dface *face,
                /*!< a pointer to a DXF \c 3DFACE entity. */
        char *plot_style_name
                /*!< a string containing the \c plot_style_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
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
        face->plot_style_name = strdup (plot_style_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face);
}


/*!
 * \brief Get the \c color_value from a DXF \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_get_color_value.png
 *
 * \return \c color_value when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int32_t
dxf_3dface_get_color_value
(
        Dxf3dface *face
                /*!< a pointer to a DXF \c 3DFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face->color_value);
}


/*!
 * \brief Set the \c color_value for a DXF \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_set_color_value.png
 *
 * \return a pointer to \c face when successful, or \c NULL when an
 * error occurred.
 */
Dxf3dface *
dxf_3dface_set_color_value
(
        Dxf3dface *face,
                /*!< a pointer to a DXF \c 3DFACE entity. */
        int32_t color_value
                /*!< the \c color_value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        face->color_value = color_value;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face);
}


/*!
 * \brief Get the \c color_name from a DXF \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_get_color_name.png
 *
 * \return \c color_name when sucessful, or \c NULL when an error
 * occurred.
 */
char *
dxf_3dface_get_color_name
(
        Dxf3dface *face
                /*!< a pointer to a DXF \c 3DFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (face->color_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (face->color_name));
}


/*!
 * \brief Set the \c color_name for a DXF \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_set_color_name.png
 *
 * \return a pointer to \c face when successful, or \c NULL when an
 * error occurred.
 */
Dxf3dface *
dxf_3dface_set_color_name
(
        Dxf3dface *face,
                /*!< a pointer to a DXF \c 3DFACE entity. */
        char *color_name
                /*!< a string containing the \c color_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
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
        face->color_name = strdup (color_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face);
}


/*!
 * \brief Get the \c transparency from a DXF \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_get_transparency.png
 *
 * \return \c transparency when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int32_t
dxf_3dface_get_transparency
(
        Dxf3dface *face
                /*!< a pointer to a DXF \c 3DFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face->transparency);
}


/*!
 * \brief Set the \c transparency for a DXF \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_set_transparency.png
 *
 * \return a pointer to \c face when successful, or \c NULL when an
 * error occurred.
 */
Dxf3dface *
dxf_3dface_set_transparency
(
        Dxf3dface *face,
                /*!< a pointer to a DXF \c 3DFACE entity. */
        int32_t transparency
                /*!< the \c transparency to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        face->transparency = transparency;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face);
}


/*!
 * \brief Get the base point of a DXF \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_get_p0.png
 *
 * \return the base point \c p0.
 */
DxfPoint *
dxf_3dface_get_p0
(
        Dxf3dface *face
                /*!< a pointer to a DXF \c 3DFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (face->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face->p0);
}


/*!
 * \brief Set the base point \c p0 of a DXF \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_set_p0.png
 *
 * \return a pointer to \c face when successful, or \c NULL when an
 * error occurred.
 */
Dxf3dface *
dxf_3dface_set_p0
(
        Dxf3dface *face,
                /*!< a pointer to a DXF \c 3DFACE entity. */
        DxfPoint *point
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        face->p0 = (DxfPoint *) point;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face);
}


/*!
 * \brief Get the X-value of the base point \c x0 of a DXF \c 3DFACE
 * entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_get_x0.png
 *
 * \return the X-value of the base point \c x0.
 */
double
dxf_3dface_get_x0
(
        Dxf3dface *face
                /*!< a pointer to a DXF \c 3DFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (face->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face->p0->x0);
}


/*!
 * \brief Set the X-value of the base point \c x0 of a DXF \c 3DFACE
 * entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_set_x0.png
 *
 * \return a pointer to \c face when successful, or \c NULL when an
 * error occurred.
 */
Dxf3dface *
dxf_3dface_set_x0
(
        Dxf3dface *face,
                /*!< a pointer to a DXF \c 3DFACE entity. */
        double x0
                /*!< the X-value of the base point \c x0 of a DXF
                 * \c 3DFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (face->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                face->p0 = dxf_point_init (face->p0);
                if (face->p0 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        face->p0->x0 = x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face);
}


/*!
 * \brief Get the Y-value of the base point \c y0 of a DXF \c 3DFACE
 * entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_get_y0.png
 *
 * \return the Y-value of the base point \c y0.
 */
double
dxf_3dface_get_y0
(
        Dxf3dface *face
                /*!< a pointer to a DXF \c 3DFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (face->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face->p0->y0);
}


/*!
 * \brief Set the Y-value of the base point \c y0 of a DXF \c 3DFACE
 * entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_set_y0.png
 *
 * \return a pointer to \c face when successful, or \c NULL when an
 * error occurred.
 */
Dxf3dface *
dxf_3dface_set_y0
(
        Dxf3dface *face,
                /*!< a pointer to a DXF \c 3DFACE entity. */
        double y0
                /*!< the Y-value of the base point \c y0 of a DXF
                 * \c 3DFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (face->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                face->p0 = dxf_point_init (face->p0);
                if (face->p0 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        face->p0->y0 = y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face);
}


/*!
 * \brief Get the Z-value of the base point \c z0 of a DXF \c 3DFACE
 * entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_get_z0.png
 *
 * \return the Z-value of the base point \c z0.
 */
double
dxf_3dface_get_z0
(
        Dxf3dface *face
                /*!< a pointer to a DXF \c 3DFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (face->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face->p0->z0);
}


/*!
 * \brief Set the Z-value of the base point \c z0 of a DXF \c 3DFACE
 * entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_set_z0.png
 *
 * \return a pointer to \c face when successful, or \c NULL when an
 * error occurred.
 */
Dxf3dface *
dxf_3dface_set_z0
(
        Dxf3dface *face,
                /*!< a pointer to a DXF \c 3DFACE entity. */
        double z0
                /*!< the Z-value of the base point \c z0 of a DXF
                 * \c 3DFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (face->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                face->p0 = dxf_point_init (face->p0);
                if (face->p0 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        face->p0->z0 = z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face);
}


/*!
 * \brief Get the first alignment point \c p1 of a DXF \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_get_p1.png
 *
 * \return the first alignment point \c p1.
 */
DxfPoint *
dxf_3dface_get_p1
(
        Dxf3dface *face
                /*!< a pointer to a DXF \c 3DFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (face->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face->p1);
}


/*!
 * \brief Set the first alignment point \c p1 of a DXF \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_set_p1.png
 *
 * \return a pointer to \c face when successful, or \c NULL when an
 * error occurred.
 */
Dxf3dface *
dxf_3dface_set_p1
(
        Dxf3dface *face,
                /*!< a pointer to a DXF \c 3DFACE entity. */
        DxfPoint *point
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        face->p1 = (DxfPoint *) point;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face);
}


/*!
 * \brief Get the X-value of the first alignment point \c x1 of a DXF
 * \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_get_x1.png
 *
 * \return the X-value of the first alignment point \c x1.
 */
double
dxf_3dface_get_x1
(
        Dxf3dface *face
                /*!< a pointer to a DXF \c 3DFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (face->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face->p1->x0);
}


/*!
 * \brief Set the X-value of the first alignment point \c x1 of a DXF
 * \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_set_x1.png
 *
 * \return a pointer to \c face when successful, or \c NULL when an
 * error occurred.
 */
Dxf3dface *
dxf_3dface_set_x1
(
        Dxf3dface *face,
                /*!< a pointer to a DXF \c 3DFACE entity. */
        double x1
                /*!< the X-value of the first alignment point \c x1 of a
                 * DXF \c 3DFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (face->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                face->p1 = dxf_point_init (face->p1);
                if (face->p1 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        face->p1->x0 = x1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face);
}


/*!
 * \brief Get the Y-value of the first alignment point \c y1 of a DXF
 * \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_get_y1.png
 *
 * \return the Y-value of the first alignment point \c y1.
 */
double
dxf_3dface_get_y1
(
        Dxf3dface *face
                /*!< a pointer to a DXF \c 3DFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (face->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face->p1->y0);
}


/*!
 * \brief Set the Y-value of the first alignment point \c y1 of a DXF
 * \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_set_y1.png
 *
 * \return a pointer to \c face when successful, or \c NULL when an
 * error occurred.
 */
Dxf3dface *
dxf_3dface_set_y1
(
        Dxf3dface *face,
                /*!< a pointer to a DXF \c 3DFACE entity. */
        double y1
                /*!< the Y-value of the first alignment point \c y1 of a
                 * DXF \c 3DFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (face->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                face->p1 = dxf_point_init (face->p1);
                if (face->p1 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        face->p1->y0 = y1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face);
}


/*!
 * \brief Get the Z-value of the first alignment point \c z1 of a DXF
 * \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_get_z1.png
 *
 * \return the Z-value of the first alignment point \c z1.
 */
double
dxf_3dface_get_z1
(
        Dxf3dface *face
                /*!< a pointer to a DXF \c 3DFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (face->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face->p1->z0);
}


/*!
 * \brief Set the Z-value of the first alignment point \c z1 of a DXF
 * \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_set_z1.png
 *
 * \return a pointer to \c face when successful, or \c NULL when an
 * error occurred.
 */
Dxf3dface *
dxf_3dface_set_z1
(
        Dxf3dface *face,
                /*!< a pointer to a DXF \c 3DFACE entity. */
        double z1
                /*!< the Z-value of the first alignment point \c z1 of a
                 * DXF \c 3DFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (face->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                face->p1 = dxf_point_init (face->p1);
                if (face->p1 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        face->p1->z0 = z1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face);
}


/*!
 * \brief Get the second alignment point \c p2 of a DXF \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_get_p2.png
 *
 * \return the second alignment point \c p2.
 */
DxfPoint *
dxf_3dface_get_p2
(
        Dxf3dface *face
                /*!< a pointer to a DXF \c 3DFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (face->p2 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face->p2);
}


/*!
 * \brief Set the second alignment point \c p2 of a DXF \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_set_p2.png
 *
 * \return a pointer to \c face when successful, or \c NULL when an
 * error occurred.
 */
Dxf3dface *
dxf_3dface_set_p2
(
        Dxf3dface *face,
                /*!< a pointer to a DXF \c 3DFACE entity. */
        DxfPoint *point
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        face->p2 = (DxfPoint *) point;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face);
}


/*!
 * \brief Get the X-value of the second alignment point \c x2 of a DXF
 * \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_get_x2.png
 *
 * \return the X-value of the second alignment point \c x2.
 */
double
dxf_3dface_get_x2
(
        Dxf3dface *face
                /*!< a pointer to a DXF \c 3DFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (face->p2 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face->p2->x0);
}


/*!
 * \brief Set the X-value of the second alignment point \c x2 of a DXF
 * \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_set_x2.png
 *
 * \return a pointer to \c face when successful, or \c NULL when an
 * error occurred.
 */
Dxf3dface *
dxf_3dface_set_x2
(
        Dxf3dface *face,
                /*!< a pointer to a DXF \c 3DFACE entity. */
        double x2
                /*!< the X-value of the second alignment point \c x2 of
                 * a DXF \c 3DFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (face->p2 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                face->p2 = dxf_point_init (face->p2);
                if (face->p2 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        face->p2->x0 = x2;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face);
}


/*!
 * \brief Get the Y-value of the second alignment point \c y2 of a DXF
 * \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_get_y2.png
 *
 * \return the Y-value of the second alignment point \c y2.
 */
double
dxf_3dface_get_y2
(
        Dxf3dface *face
                /*!< a pointer to a DXF \c 3DFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (face->p2 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face->p2->y0);
}


/*!
 * \brief Set the Y-value of the second alignment point \c y2 of a DXF
 * \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_set_y2.png
 *
 * \return a pointer to \c face when successful, or \c NULL when an
 * error occurred.
 */
Dxf3dface *
dxf_3dface_set_y2
(
        Dxf3dface *face,
                /*!< a pointer to a DXF \c 3DFACE entity. */
        double y2
                /*!< the Y-value of the second alignment point \c y2 of
                 * a DXF \c 3DFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (face->p2 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                face->p2 = dxf_point_init (face->p2);
                if (face->p2 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        face->p2->y0 = y2;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face);
}


/*!
 * \brief Get the Z-value of the second alignment point \c z2 of a DXF
 * \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_get_z2.png
 *
 * \return the Z-value of the second alignment point \c z2.
 */
double
dxf_3dface_get_z2
(
        Dxf3dface *face
                /*!< a pointer to a DXF \c 3DFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (face->p2 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face->p2->z0);
}


/*!
 * \brief Set the Z-value of the second alignment point \c z2 of a DXF
 * \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_set_z2.png
 *
 * \return a pointer to \c face when successful, or \c NULL when an
 * error occurred.
 */
Dxf3dface *
dxf_3dface_set_z2
(
        Dxf3dface *face,
                /*!< a pointer to a DXF \c 3DFACE entity. */
        double z2
                /*!< the Z-value of the second alignment point \c z2 of
                 * a DXF \c 3DFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (face->p2 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                face->p2 = dxf_point_init (face->p2);
                if (face->p2 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        face->p2->z0 = z2;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face);
}


/*!
 * \brief Get the third alignment point \c p3 of a DXF \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_get_p3.png
 *
 * \return the third alignment point \c p3.
 */
DxfPoint *
dxf_3dface_get_p3
(
        Dxf3dface *face
                /*!< a pointer to a DXF \c 3DFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (face->p3 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face->p3);
}


/*!
 * \brief Set the third alignment point \c p3 of a DXF \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_set_p3.png
 *
 * \return a pointer to \c face when successful, or \c NULL when an
 * error occurred.
 */
Dxf3dface *
dxf_3dface_set_p3
(
        Dxf3dface *face,
                /*!< a pointer to a DXF \c 3DFACE entity. */
        DxfPoint *point
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        face->p3 = (DxfPoint *) point;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face);
}


/*!
 * \brief Get the X-value of the third alignment point \c x3 of a DXF
 * \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_get_x3.png
 *
 * \return the X-value of the third alignment point \c x3.
 */
double
dxf_3dface_get_x3
(
        Dxf3dface *face
                /*!< a pointer to a DXF \c 3DFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (face->p3 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face->p3->x0);
}


/*!
 * \brief Set the X-value of the third alignment point \c x3 of a DXF
 * \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_set_x3.png
 *
 * \return a pointer to \c face when successful, or \c NULL when an
 * error occurred.
 */
Dxf3dface *
dxf_3dface_set_x3
(
        Dxf3dface *face,
                /*!< a pointer to a DXF \c 3DFACE entity. */
        double x3
                /*!< the X-value of the third alignment point \c x3 of a
                 * DXF \c 3DFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (face->p3 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                face->p3 = dxf_point_init (face->p3);
                if (face->p3 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        face->p3->x0 = x3;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face);
}


/*!
 * \brief Get the Y-value of the third alignment point \c y3 of a DXF
 * \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_get_y3.png
 *
 * \return the Y-value of the third alignment point \c y3.
 */
double
dxf_3dface_get_y3
(
        Dxf3dface *face
                /*!< a pointer to a DXF \c 3DFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (face->p3 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face->p3->y0);
}


/*!
 * \brief Set the Y-value of the third alignment point \c y3 of a DXF
 * \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_set_y3.png
 *
 * \return a pointer to \c face when successful, or \c NULL when an
 * error occurred.
 */
Dxf3dface *
dxf_3dface_set_y3
(
        Dxf3dface *face,
                /*!< a pointer to a DXF \c 3DFACE entity. */
        double y3
                /*!< the Y-value of the third alignment point \c y3 of a
                 * DXF \c 3DFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (face->p3 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                face->p3 = dxf_point_init (face->p3);
                if (face->p3 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        face->p3->y0 = y3;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face);
}


/*!
 * \brief Get the Z-value of the third alignment point \c z3 of a DXF
 * \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_get_z3.png
 *
 * \return the Z-value of the third alignment point \c z3.
 */
double
dxf_3dface_get_z3
(
        Dxf3dface *face
                /*!< a pointer to a DXF \c 3DFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (face->p3 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face->p3->z0);
}


/*!
 * \brief Set the Z-value of the third alignment point \c z3 of a DXF
 * \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_set_z3.png
 *
 * \return a pointer to \c face when successful, or \c NULL when an
 * error occurred.
 */
Dxf3dface *
dxf_3dface_set_z3
(
        Dxf3dface *face,
                /*!< a pointer to a DXF \c 3DFACE entity. */
        double z3
                /*!< the Z-value of the third alignment point \c z3 of a
                 * DXF \c 3DFACE entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (face->p3 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                face->p3 = dxf_point_init (face->p3);
                if (face->p3 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        face->p3->z0 = z3;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face);
}


/*!
 * \brief Get the \c flag value from a DXF \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_get_flag.png
 *
 * \return \c flag value.
 */
int16_t
dxf_3dface_get_flag
(
        Dxf3dface *face
                /*!< a pointer to a DXF \c 3DFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (face->flag < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (face->flag > 15)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face->flag);
}


/*!
 * \brief Set the flag value for a DXF \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_set_flag.png
 *
 * \return a pointer to \c face when successful, or \c NULL when an
 * error occurred.
 */
Dxf3dface *
dxf_3dface_set_flag
(
        Dxf3dface *face,
                /*!< a pointer to a DXF \c 3DFACE entity. */
        int16_t flag
                /*!< \c flag value for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
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
        face->flag = flag;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face);
}


/*!
 * \brief Test if the first edge of a DXF \c 3DFACE is invisible.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_is_first_edge_invisible.png
 *
 * \return \c TRUE when the edge is invisible, or \c FALSE when the edge
 * is visible.
 */
int
dxf_3dface_is_first_edge_invisible
(
        Dxf3dface *face
                /*!< a pointer to a DXF \c 3DFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (DXF_CHECK_BIT (face->flag, 0));
}


/*!
 * \brief Test if the second edge of a DXF \c 3DFACE is invisible.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_is_second_edge_invisible.png
 *
 * \return \c TRUE when the edge is invisible, or \c FALSE when the edge
 * is visible.
 */
int
dxf_3dface_is_second_edge_invisible
(
        Dxf3dface *face
                /*!< a pointer to a DXF \c 3DFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (DXF_CHECK_BIT (face->flag, 1));
}


/*!
 * \brief Test if the third edge of a DXF \c 3DFACE is invisible.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_is_third_edge_invisible.png
 *
 * \return \c TRUE when the edge is invisible, or \c FALSE when the edge
 * is visible.
 */
int
dxf_3dface_is_third_edge_invisible
(
        Dxf3dface *face
                /*!< a pointer to a DXF \c 3DFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (DXF_CHECK_BIT (face->flag, 2));
}


/*!
 * \brief Test if the fourth edge of a DXF \c 3DFACE is invisible.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_is_fourth_edge_invisible.png
 *
 * \return \c TRUE when the edge is invisible, or \c FALSE when the edge
 * is visible.
 */
int
dxf_3dface_is_fourth_edge_invisible
(
        Dxf3dface *face
                /*!< a pointer to a DXF \c 3DFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (DXF_CHECK_BIT (face->flag, 3));
}


/*!
 * \brief Create a DXF \c 3DFACE by means of at least three valid DXF
 * \c POINT entities.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_create_from_points.png
 *
 * \return a pointer to \c face when successful, or \c NULL when an
 * error occurred.
 */
Dxf3dface *
dxf_3dface_create_from_points
(
        DxfPoint *p0,
                /*!< a pointer to a DXF \c POINT entity. */
        DxfPoint *p1,
                /*!< a pointer to a DXF \c POINT entity. */
        DxfPoint *p2,
                /*!< a pointer to a DXF \c POINT entity. */
        DxfPoint *p3,
                /*!< a pointer to a DXF \c POINT entity. */
        int id_code,
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file. */
        int inheritance
                /*!< Inherit layer, linetype, color and other relevant
                 * properties from either:
                 * <ol>
                 * <li value = "0"> Default (as initialised).</li>
                 * <li value = "1"> Point \c p0.</li>
                 * <li value = "2"> Point \c p1.</li>
                 * <li value = "3"> Point \c p2.</li>
                 * <li value = "4"> Point \c p3.</li>
                 * </ol>
                 */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        Dxf3dface *face = NULL;

        /* Do some basic checks. */
        if (((p0 != NULL) && (p1 != NULL) && (p2 != NULL))
          || ((p0 != NULL) && (p1 != NULL) && (p3 != NULL))
          || ((p1 != NULL) && (p2 != NULL) && (p3 != NULL)))
        {
                /* Do nothing, we only need three valid points to form a
                 * 3dface (test of all three valid permutations). */
        }
        else
        {
                fprintf (stderr,
                  (_("Error in %s () to many NULL pointers were passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (id_code < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if ((inheritance < 0) || (inheritance > 4))
        {
                fprintf (stderr,
                  (_("Warning in %s () an illegal inherit value was passed.\n")),
                  __FUNCTION__);
        }
        face = dxf_3dface_init (face);
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (p0 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        else
        {
                face->p0 = (DxfPoint *) p0;
        }
        if (p1 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        else
        {
                face->p1 = (DxfPoint *) p1;
        }
        if (p2 != NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        else
        {
                face->p2 = (DxfPoint *) p2;
        }
        if (p3 != NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        else
        {
                face->p3 = (DxfPoint *) p3;
        }
        switch (inheritance)
        {
                case 0:
                        /* Do nothing. */
                        break;
                case 1:
                        if (p0 == NULL)
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () a NULL pointer was passed.\n")),
                                  __FUNCTION__);
                                break;
                        }
                        if (p0->linetype == NULL)
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () a NULL pointer was found.\n")),
                                  __FUNCTION__);
                        }
                        else
                        {
                                face->linetype = strdup (p0->linetype);
                        }
                        if (p0->layer == NULL)
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () a NULL pointer was found.\n")),
                                  __FUNCTION__);
                        }
                        else
                        {
                                face->layer = strdup (p0->layer);
                        }
                        face->elevation = p0->elevation;
                        face->thickness = p0->thickness;
                        face->linetype_scale = p0->linetype_scale;
                        face->visibility = p0->visibility;
                        face->color = p0->color;
                        face->paperspace = p0->paperspace;
                        /*! \todo Add graphics_data_size. */
                        face->shadow_mode = p0->shadow_mode;
                        /*! \todo Add binary_graphics_data. */
                        if (p0->dictionary_owner_soft == NULL)
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () a NULL pointer was found.\n")),
                                  __FUNCTION__);
                        }
                        else
                        {
                                face->dictionary_owner_soft = strdup (p0->dictionary_owner_soft);
                        }
                        if (p0->object_owner_soft == NULL)
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () a NULL pointer was found.\n")),
                                  __FUNCTION__);
                        }
                        else
                        {
                                face->object_owner_soft = strdup (p0->object_owner_soft);
                        }
                        if (p0->material == NULL)
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () a NULL pointer was found.\n")),
                                  __FUNCTION__);
                        }
                        else
                        {
                                face->material = strdup (p0->material);
                        }
                        if (p0->dictionary_owner_hard == NULL)
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () a NULL pointer was found.\n")),
                                  __FUNCTION__);
                        }
                        else
                        {
                                face->dictionary_owner_hard = strdup (p0->dictionary_owner_hard);
                        }
                        face->lineweight = p0->lineweight;
                        if (p0->plot_style_name == NULL)
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () a NULL pointer was found.\n")),
                                  __FUNCTION__);
                        }
                        else
                        {
                                face->plot_style_name = strdup (p0->plot_style_name);
                        }
                        face->color_value = p0->color_value;
                        if (p0->color_name == NULL)
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () a NULL pointer was found.\n")),
                                  __FUNCTION__);
                        }
                        else
                        {
                                face->color_name = strdup (p0->color_name);
                        }
                        face->transparency = p0->transparency;
                        break;
                case 2:
                        if (p1 == NULL)
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () a NULL pointer was passed.\n")),
                                  __FUNCTION__);
                                break;
                        }
                        if (p1->linetype == NULL)
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () a NULL pointer was found.\n")),
                                  __FUNCTION__);
                        }
                        else
                        {
                                face->linetype = strdup (p1->linetype);
                        }
                        if (p1->layer == NULL)
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () a NULL pointer was found.\n")),
                                  __FUNCTION__);
                        }
                        else
                        {
                                face->layer = strdup (p1->layer);
                        }
                        face->elevation = p1->elevation;
                        face->thickness = p1->thickness;
                        face->linetype_scale = p1->linetype_scale;
                        face->visibility = p1->visibility;
                        face->color = p1->color;
                        face->paperspace = p1->paperspace;
                        /*! \todo Add graphics_data_size. */
                        face->shadow_mode = p1->shadow_mode;
                        /*! \todo Add binary_graphics_data. */
                        if (p1->dictionary_owner_soft == NULL)
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () a NULL pointer was found.\n")),
                                  __FUNCTION__);
                        }
                        else
                        {
                                face->dictionary_owner_soft = strdup (p1->dictionary_owner_soft);
                        }
                        if (p1->object_owner_soft == NULL)
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () a NULL pointer was found.\n")),
                                  __FUNCTION__);
                        }
                        else
                        {
                                face->object_owner_soft = strdup (p1->object_owner_soft);
                        }
                        if (p1->material == NULL)
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () a NULL pointer was found.\n")),
                                  __FUNCTION__);
                        }
                        else
                        {
                                face->material = strdup (p1->material);
                        }
                        if (p1->dictionary_owner_hard == NULL)
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () a NULL pointer was found.\n")),
                                  __FUNCTION__);
                        }
                        else
                        {
                                face->dictionary_owner_hard = strdup (p1->dictionary_owner_hard);
                        }
                        face->lineweight = p1->lineweight;
                        if (p1->plot_style_name == NULL)
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () a NULL pointer was found.\n")),
                                  __FUNCTION__);
                        }
                        else
                        {
                                face->plot_style_name = strdup (p1->plot_style_name);
                        }
                        face->color_value = p1->color_value;
                        if (p1->color_name == NULL)
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () a NULL pointer was found.\n")),
                                  __FUNCTION__);
                        }
                        else
                        {
                                face->color_name = strdup (p1->color_name);
                        }
                        face->transparency = p1->transparency;
                        break;
                case 3:
                        if (p2 == NULL)
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () a NULL pointer was passed.\n")),
                                  __FUNCTION__);
                                break;
                        }
                        if (p2->linetype == NULL)
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () a NULL pointer was found.\n")),
                                  __FUNCTION__);
                        }
                        else
                        {
                                face->linetype = strdup (p2->linetype);
                        }
                        if (p2->layer == NULL)
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () a NULL pointer was found.\n")),
                                  __FUNCTION__);
                        }
                        else
                        {
                                face->layer = strdup (p2->layer);
                        }
                        face->elevation = p2->elevation;
                        face->thickness = p2->thickness;
                        face->linetype_scale = p2->linetype_scale;
                        face->visibility = p2->visibility;
                        face->color = p2->color;
                        face->paperspace = p2->paperspace;
                        /*! \todo Add graphics_data_size. */
                        face->shadow_mode = p2->shadow_mode;
                        /*! \todo Add binary_graphics_data. */
                        if (p2->dictionary_owner_soft == NULL)
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () a NULL pointer was found.\n")),
                                  __FUNCTION__);
                        }
                        else
                        {
                                face->dictionary_owner_soft = strdup (p2->dictionary_owner_soft);
                        }
                        if (p2->object_owner_soft == NULL)
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () a NULL pointer was found.\n")),
                                  __FUNCTION__);
                        }
                        else
                        {
                                face->object_owner_soft = strdup (p2->object_owner_soft);
                        }
                        if (p2->material == NULL)
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () a NULL pointer was found.\n")),
                                  __FUNCTION__);
                        }
                        else
                        {
                                face->material = strdup (p2->material);
                        }
                        if (p2->dictionary_owner_hard == NULL)
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () a NULL pointer was found.\n")),
                                  __FUNCTION__);
                        }
                        else
                        {
                                face->dictionary_owner_hard = strdup (p2->dictionary_owner_hard);
                        }
                        face->lineweight = p2->lineweight;
                        if (p2->plot_style_name == NULL)
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () a NULL pointer was found.\n")),
                                  __FUNCTION__);
                        }
                        else
                        {
                                face->plot_style_name = strdup (p2->plot_style_name);
                        }
                        face->color_value = p2->color_value;
                        if (p2->color_name == NULL)
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () a NULL pointer was found.\n")),
                                  __FUNCTION__);
                        }
                        else
                        {
                                face->color_name = strdup (p2->color_name);
                        }
                        face->transparency = p2->transparency;
                        break;
                case 4:
                        if (p3 == NULL)
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () a NULL pointer was passed.\n")),
                                  __FUNCTION__);
                                break;
                        }
                        if (p3->linetype == NULL)
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () a NULL pointer was found.\n")),
                                  __FUNCTION__);
                        }
                        else
                        {
                                face->linetype = strdup (p3->linetype);
                        }
                        if (p3->layer == NULL)
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () a NULL pointer was found.\n")),
                                  __FUNCTION__);
                        }
                        else
                        {
                                face->layer = strdup (p3->layer);
                        }
                        face->elevation = p3->elevation;
                        face->thickness = p3->thickness;
                        face->linetype_scale = p3->linetype_scale;
                        face->visibility = p3->visibility;
                        face->color = p3->color;
                        face->paperspace = p3->paperspace;
                        /*! \todo Add graphics_data_size. */
                        face->shadow_mode = p3->shadow_mode;
                        /*! \todo Add binary_graphics_data. */
                        if (p3->dictionary_owner_soft == NULL)
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () a NULL pointer was found.\n")),
                                  __FUNCTION__);
                        }
                        else
                        {
                                face->dictionary_owner_soft = strdup (p3->dictionary_owner_soft);
                        }
                        if (p3->object_owner_soft == NULL)
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () a NULL pointer was found.\n")),
                                  __FUNCTION__);
                        }
                        else
                        {
                                face->object_owner_soft = strdup (p3->object_owner_soft);
                        }
                        if (p3->material == NULL)
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () a NULL pointer was found.\n")),
                                  __FUNCTION__);
                        }
                        else
                        {
                                face->material = strdup (p3->material);
                        }
                        if (p3->dictionary_owner_hard == NULL)
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () a NULL pointer was found.\n")),
                                  __FUNCTION__);
                        }
                        else
                        {
                                face->dictionary_owner_hard = strdup (p3->dictionary_owner_hard);
                        }
                        face->lineweight = p3->lineweight;
                        if (p3->plot_style_name == NULL)
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () a NULL pointer was found.\n")),
                                  __FUNCTION__);
                        }
                        else
                        {
                                face->plot_style_name = strdup (p3->plot_style_name);
                        }
                        face->color_value = p3->color_value;
                        if (p3->color_name == NULL)
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () a NULL pointer was found.\n")),
                                  __FUNCTION__);
                        }
                        else
                        {
                                face->color_name = strdup (p3->color_name);
                        }
                        face->transparency = p3->transparency;
                        break;
                default:
                        fprintf (stderr,
                          (_("Warning in %s (): unknown inheritance option passed.\n")),
                          __FUNCTION__);
                        fprintf (stderr,
                          (_("\tResolving to default.\n")));
                        break;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face);
}


/*!
 * \brief Get the pointer to the next \c 3DFACE entity from a DXF 
 * \c 3DFACE entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_get_next.png
 *
 * \return pointer to the next \c 3DFACE entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
Dxf3dface *
dxf_3dface_get_next
(
        Dxf3dface *face
                /*!< a pointer to a DXF \c 3DFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (face->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((Dxf3dface *) face->next);
}


/*!
 * \brief Set the pointer to the next \c 3DFACE for a DXF \c 3DFACE
 * entity.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_set_next.png
 *
 * \return a pointer to \c face when successful, or \c NULL when an
 * error occurred.
 */
Dxf3dface *
dxf_3dface_set_next
(
        Dxf3dface *face,
                /*!< a pointer to a DXF \c 3DFACE entity. */
        Dxf3dface *next
                /*!< a pointer to the next \c 3DFACE for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
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
        face->next = (struct Dxf3dface *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face);
}


/*!
 * \brief Get the pointer to the last \c 3DFACE entity from a linked
 * list of DXF \c 3DFACE entities.
 *
 * <b>Flow diagram:</b>
 * \image html drakon/dxf_3dface_get_last.png
 *
 * \return pointer to the last \c 3DFACE entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
Dxf3dface *
dxf_3dface_get_last
(
        Dxf3dface *face
                /*!< a pointer to a DXF \c 3DFACE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (face == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (face->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((Dxf3dface *) face);
        }
        Dxf3dface *iter = (Dxf3dface *) face->next;
        while (iter->next != NULL)
        {
                iter = (Dxf3dface *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((Dxf3dface *) iter);
}


/* EOF */
