/*!
 * \file 3dface.c
 *
 * \author Copyright (C) 2010 ... 2016 by Bert Timmerman <bert.timmerman@xs4all.nl>.
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
                  (_("Error in %s () could not allocate memory for a Dxf3dface struct.\n")),
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
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
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
                  (_("Error in %s () could not allocate memory for a Dxf3dface struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        face->id_code = 0;
        face->linetype = strdup (DXF_DEFAULT_LINETYPE);
        face->layer = strdup (DXF_DEFAULT_LAYER);
        face->p0 = dxf_point_init (face->p0);
        face->p1 = dxf_point_init (face->p1);
        face->p2 = dxf_point_init (face->p2);
        face->p3 = dxf_point_init (face->p3);
        face->elevation = 0.0;
        face->thickness = 0.0;
        face->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        face->visibility = DXF_DEFAULT_VISIBILITY;
        face->color = DXF_COLOR_BYLAYER;
        face->paperspace = DXF_MODELSPACE;
        face->flag = 0;
        face->dictionary_owner_soft = strdup ("");
        face->dictionary_owner_hard = strdup ("");
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
 * \return a pointer to a DXF \c 3DFACE entity.
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
                face = dxf_3dface_new ();
                face = dxf_3dface_init (face);
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
                        fscanf (fp->fp, "%x\n", &face->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", face->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", face->layer);
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
                else if ((fp->acad_version_number <= AutoCAD_11)
                  && DXF_FLATLAND
                  && (strcmp (temp_string, "38") == 0)
                  && (face->elevation != 0.0))
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
                        fscanf (fp->fp, "%d\n", &face->color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &face->paperspace);
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
                                fprintf (stderr,
                                  (_("Warning in %s () found a bad subclass marker in: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                        }
                }
                else if (strcmp (temp_string, "70") == 0)
                {
                        /* Now follows a string containing the
                         * value of edge visibility flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &face->flag);
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing Soft-pointer
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", face->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", face->dictionary_owner_hard);
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
        if (strcmp (face->linetype, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty linetype string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, face->id_code);
                fprintf (stderr,
                  (_("\t%s entity is reset to default linetype")),
                  dxf_entity_name);
                face->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (face->layer, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, face->id_code);
                fprintf (stderr,
                  (_("\t%s entity is relocated to layer 0")),
                  dxf_entity_name);
                face->layer = strdup (DXF_DEFAULT_LAYER);
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
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
        }
        if (face->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
        fprintf (fp->fp, "  8\n%s\n", face->layer);
        if (strcmp (face->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", face->linetype);
        }
        if (face->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", face->color);
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
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbFace\n");
        }
        fprintf (fp->fp, " 10\n%f\n", face->p0->x0);
        fprintf (fp->fp, " 20\n%f\n", face->p0->y0);
        fprintf (fp->fp, " 30\n%f\n", face->p0->z0);
        fprintf (fp->fp, " 11\n%f\n", face->p1->x0);
        fprintf (fp->fp, " 21\n%f\n", face->p1->y0);
        fprintf (fp->fp, " 31\n%f\n", face->p1->z0);
        fprintf (fp->fp, " 12\n%f\n", face->p2->x0);
        fprintf (fp->fp, " 22\n%f\n", face->p2->y0);
        fprintf (fp->fp, " 32\n%f\n", face->p2->z0);
        fprintf (fp->fp, " 13\n%f\n", face->p3->x0);
        fprintf (fp->fp, " 23\n%f\n", face->p3->y0);
        fprintf (fp->fp, " 33\n%f\n", face->p3->z0);
        fprintf (fp->fp, " 70\n%d\n", face->flag);
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
        if (face->next != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to next Dxf3dface was not NULL.\n")),
                __FUNCTION__);
              return (face);
        }
        free (face->linetype);
        free (face->layer);
        free (face->dictionary_owner_soft);
        free (face->dictionary_owner_hard);
        dxf_point_free (face->p0);
        dxf_point_free (face->p1);
        free (face);
        face = NULL;
#ifdef DEBUG
        DXF_DEBUG_END
#endif
        return (face);
}


/*!
 * \brief Free the allocated memory for a chain of DXF \c 3DFACE
 * entities and all their data fields.
 */
void
dxf_3dface_free_chain
(
        Dxf3dface *faces
                /*!< a pointer to the chain of DXF \c 3DFACE entities. */
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
                struct Dxf3dface *iter = faces->next;
                dxf_3dface_free (faces);
                faces = (Dxf3dface *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the ID code from a DXF \c 3DFACE entity.
 *
 * \return ID code.
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
                  (_("Error in %s () a negative value was found in the id-code member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face->id_code);
}


/*!
 * \brief Set the ID code for a DXF \c 3DFACE entity.
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
                  (_("Error in %s () a negative id-code value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
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
 * \return linetype when sucessful, \c NULL when an error occurred.
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
                  (_("Error in %s () a NULL pointer was found in the linetype member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (face->linetype));
}


/*!
 * \brief Set the linetype for a DXF \c 3DFACE entity.
 */
Dxf3dface *
dxf_3dface_set_linetype
(
        Dxf3dface *face,
                /*!< a pointer to a DXF \c 3DFACE entity. */
        char *linetype
                /*!< a string containing the linetype for the entity. */
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
 * \brief Get the layer from a DXF \c 3DFACE entity.
 *
 * \return layer when sucessful, \c NULL when an error occurred.
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
                  (_("Error in %s () a NULL pointer was found in the layer member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (face->layer));
}


/*!
 * \brief Set the layer for a DXF \c 3DFACE entity.
 */
Dxf3dface *
dxf_3dface_set_layer
(
        Dxf3dface *face,
                /*!< a pointer to a DXF \c 3DFACE entity. */
        char *layer
                /*!< a string containing the layer for the entity. */
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
 * \brief Get the elevation a this DXF \c 3DFACE entity.
 *
 * \return elevation.
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
 * \brief Set the elevation for a DXF \c 3DFACE entity.
 */
Dxf3dface *
dxf_3dface_set_elevation
(
        Dxf3dface *face,
                /*!< a pointer to a DXF \c 3DFACE entity. */
        double elevation
                /*!< the elevation to be set for the entity. */
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
 * \brief Get the thickness from a DXF \c 3DFACE entity.
 *
 * \return thickness.
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
                  (_("Error in %s () a negative value was found in the thickness member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face->thickness);
}


/*!
 * \brief Set the thickness for a DXF \c 3DFACE entity.
 */
Dxf3dface *
dxf_3dface_set_thickness
(
        Dxf3dface *face,
                /*!< a pointer to a DXF \c 3DFACE entity. */
        double thickness
                /*!< the thickness to be set for the entity. */
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
                  (_("Error in %s () a negative thickness value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        face->thickness = thickness;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face);
}


/*!
 * \brief Get the linetype scale from a DXF \c 3DFACE entity.
 *
 * \return linetype scale.
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
                  (_("Error in %s () a negative value was found in the linetype scale member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face->linetype_scale);
}


/*!
 * \brief Set the linetype scale for a DXF \c 3DFACE entity.
 */
Dxf3dface *
dxf_3dface_set_linetype_scale
(
        Dxf3dface *face,
                /*!< a pointer to a DXF \c 3DFACE entity. */
        double linetype_scale
                /*!< the linetype scale to be set for the entity. */
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
                  (_("Error in %s () a negative linetype scale value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        face->linetype_scale = linetype_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face);
}


/*!
 * \brief Get the visibility from a DXF \c 3DFACE entity.
 *
 * \return visibility.
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
                  (_("Error in %s () a negative value was found in the visibility member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (face->visibility > 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was found in the visibility member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face->visibility);
}


/*!
 * \brief Set the visibility for a DXF \c 3DFACE entity.
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
        face->visibility = visibility;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face);
}


/*!
 * \brief Get the color from a DXF \c 3DFACE entity.
 *
 * \return color.
 */
int
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
                  (_("Warning in %s () a negative value was found in the color member.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face->color);
}


/*!
 * \brief Set the color for a DXF \c 3DFACE entity.
 */
Dxf3dface *
dxf_3dface_set_color
(
        Dxf3dface *face,
                /*!< a pointer to a DXF \c 3DFACE entity. */
        int color
                /*!< the color to be set for the entity. */
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
                  (_("Warning in %s () a negative color value was passed.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("\teffectively turning this entity it's visibility off.\n")));
        }
        face->color = color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face);
}


/*!
 * \brief Get the paperspace flag value from a DXF \c 3DFACE entity.
 *
 * \return paperspace flag value.
 */
int
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
                  (_("Warning in %s () a negative value was found in the paperspace member.\n")),
                  __FUNCTION__);
        }
        if (face->paperspace > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found in the paperspace member.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face->paperspace);
}


/*!
 * \brief Set the paperspace flag for a DXF \c 3DFACE entity.
 */
Dxf3dface *
dxf_3dface_set_paperspace
(
        Dxf3dface *face,
                /*!< a pointer to a DXF \c 3DFACE entity. */
        int paperspace
                /*!< the paperspace flag value to be set for the entity. */
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
        face->paperspace = paperspace;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face);
}


/*!
 * \brief Get the soft pointer to the dictionary owner from a DXF 
 * \c 3DFACE entity.
 *
 * \return soft pointer to the dictionary owner.
 *
 * \warning No checks are performed on the returned pointer (string).
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
                  (_("Error in %s () a NULL pointer was found in the dictionary_owner_soft member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (face->dictionary_owner_soft));
}


/*!
 * \brief Set the pointer to the dictionary_owner_soft for a DXF
 * \c 3DFACE entity.
 */
Dxf3dface *
dxf_3dface_set_dictionary_owner_soft
(
        Dxf3dface *face,
                /*!< a pointer to a DXF \c 3DFACE entity. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the
                 * dictionary_owner_soft for the entity. */
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
 * \brief Get the hard pointer to the dictionary owner from a DXF 
 * \c 3DFACE entity.
 *
 * \return hard pointer to the dictionary owner.
 *
 * \warning No checks are performed on the returned pointer (string).
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
                  (_("Error in %s () a NULL pointer was found in the dictionary_owner_hard member.\n")),
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
 * \brief Get the base point of a DXF \c 3DFACE entity.
 *
 * \return the base point.
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face->p0);
}


/*!
 * \brief Set the base point of a DXF \c 3DFACE entity.
 *
 * \return a pointer to a DXF \c 3DFACE entity.
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
 * \brief Get the X-value of the base point of a DXF \c 3DFACE entity.
 *
 * \return the X-value of the base point.
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
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face->p0->x0);
}


/*!
 * \brief Set the X-value of the base point of a DXF \c 3DFACE entity.
 *
 * \return a pointer to a DXF \c 3DFACE entity.
 */
Dxf3dface *
dxf_3dface_set_x0
(
        Dxf3dface *face,
                /*!< a pointer to a DXF \c 3DFACE entity. */
        double x0
                /*!< the X-value of the base point of a DXF \c 3DFACE
                 * entity. */
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
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        face->p0->x0 = x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face);
}


/*!
 * \brief Get the Y-value of the base point of a DXF \c 3DFACE entity.
 *
 * \return the Y-value of the base point.
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
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face->p0->y0);
}


/*!
 * \brief Set the Y-value of the base point of a DXF \c 3DFACE entity.
 *
 * \return a pointer to a DXF \c 3DFACE entity.
 */
Dxf3dface *
dxf_3dface_set_y0
(
        Dxf3dface *face,
                /*!< a pointer to a DXF \c 3DFACE entity. */
        double y0
                /*!< the Y-value of the base point of a DXF \c 3DFACE
                 * entity. */
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
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        face->p0->y0 = y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face);
}


/*!
 * \brief Get the first alignment point of a DXF \c 3DFACE entity.
 *
 * \return the first alignment point.
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face->p1);
}


/*!
 * \brief Set the first alignment point of a DXF \c 3DFACE entity.
 *
 * \return a pointer to a DXF \c 3DFACE entity.
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
 * \brief Get the X-value of the first alignment point of a DXF
 * \c 3DFACE entity.
 *
 * \return the base point.
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
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face->p1->x0);
}


/*!
 * \brief Set the X-value of the first alignment point of a DXF
 * \c 3DFACE entity.
 *
 * \return a pointer to a DXF \c 3DFACE entity.
 */
Dxf3dface *
dxf_3dface_set_x1
(
        Dxf3dface *face,
                /*!< a pointer to a DXF \c 3DFACE entity. */
        double x1
                /*!< the X-value of the first alignment point of a DXF
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
        if (face->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        face->p1->x0 = x1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face);
}


/*!
 * \brief Get the second alignment point of a DXF \c 3DFACE entity.
 *
 * \return the second alignment point.
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face->p2);
}


/*!
 * \brief Set the second alignment point of a DXF \c 3DFACE entity.
 *
 * \return a pointer to a DXF \c 3DFACE entity.
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
 * \brief Get the third alignment point of a DXF \c 3DFACE entity.
 *
 * \return the third alignment point.
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (face->p3);
}


/*!
 * \brief Set the third alignment point of a DXF \c 3DFACE entity.
 *
 * \return a pointer to a DXF \c 3DFACE entity.
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
 * \brief Test if the first edge of a DXF \c 3DFACE is invisible.
 *
 * \return \c TRUE when the edge is invisible, or \c FALSE when the edge is
 * visible.
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
 * \return \c TRUE when the edge is invisible, or \c FALSE when the edge is
 * visible.
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
 * \return \c TRUE when the edge is invisible, or \c FALSE when the edge is
 * visible.
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
 * \return \c TRUE when the edge is invisible, or \c FALSE when the edge is
 * visible.
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
 * \return a pointer to a DXF \c 3DFACE entity.
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
                 * <li value = "1"> Point p0.</li>
                 * <li value = "2"> Point p1.</li>
                 * <li value = "3"> Point p2.</li>
                 * <li value = "4"> Point p3.</li>
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
                 * 3dface (test of all four valid permutations). */
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
                  (_("Warning in %s () passed id_code is smaller than 0.\n")),
                __FUNCTION__);
        }
        if ((inheritance < 0) || (inheritance > 4))
        {
                fprintf (stderr,
                  (_("Error in %s () an illegal inherit value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        face = dxf_3dface_init (face);
        if (face == NULL)
        {
              fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a Dxf3dface struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        if (p1 != NULL)
        {
                face->p0 = (DxfPoint *) p0;
        }
        if (p2 != NULL)
        {
                face->p1 = (DxfPoint *) p1;
        }
        if (p3 != NULL)
        {
                face->p2 = (DxfPoint *) p2;
        }
        if (p3 != NULL)
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
                                break;
                        }
                        if (p0->linetype != NULL)
                        {
                                face->linetype = strdup (p0->linetype);
                        }
                        if (p0->layer != NULL)
                        {
                                face->layer = strdup (p0->layer);
                        }
                        face->thickness = p0->thickness;
                        face->linetype_scale = p0->linetype_scale;
                        face->visibility = p0->visibility;
                        face->color = p0->color;
                        face->paperspace = p0->paperspace;
                        if (p0->dictionary_owner_soft != NULL)
                        {
                                face->dictionary_owner_soft = strdup (p0->dictionary_owner_soft);
                        }
                        if (p0->dictionary_owner_hard != NULL)
                        {
                                face->dictionary_owner_hard = strdup (p0->dictionary_owner_hard);
                        }
                        break;
                case 2:
                        if (p1 == NULL)
                        {
                                break;
                        }
                        if (p1->linetype != NULL)
                        {
                                face->linetype = strdup (p1->linetype);
                        }
                        if (p1->layer != NULL)
                        {
                                face->layer = strdup (p1->layer);
                        }
                        face->thickness = p1->thickness;
                        face->linetype_scale = p1->linetype_scale;
                        face->visibility = p1->visibility;
                        face->color = p1->color;
                        face->paperspace = p1->paperspace;
                        if (p1->dictionary_owner_soft != NULL)
                        {
                                face->dictionary_owner_soft = strdup (p1->dictionary_owner_soft);
                        }
                        if (p1->dictionary_owner_hard != NULL)
                        {
                                face->dictionary_owner_hard = strdup (p1->dictionary_owner_hard);
                        }
                        break;
                case 3:
                        if (p2 == NULL)
                        {
                                break;
                        }
                        if (p2->linetype != NULL)
                        {
                                face->linetype = strdup (p2->linetype);
                        }
                        if (p2->layer != NULL)
                        {
                                face->layer = strdup (p2->layer);
                        }
                        face->thickness = p2->thickness;
                        face->linetype_scale = p2->linetype_scale;
                        face->visibility = p2->visibility;
                        face->color = p2->color;
                        face->paperspace = p2->paperspace;
                        if (p2->dictionary_owner_soft != NULL)
                        {
                                face->dictionary_owner_soft = strdup (p2->dictionary_owner_soft);
                        }
                        if (p2->dictionary_owner_hard != NULL)
                        {
                                face->dictionary_owner_hard = strdup (p2->dictionary_owner_hard);
                        }
                        break;
                case 4:
                        if (p3 == NULL)
                        {
                                break;
                        }
                        if (p3->linetype != NULL)
                        {
                                face->linetype = strdup (p3->linetype);
                        }
                        if (p3->layer != NULL)
                        {
                                face->layer = strdup (p3->layer);
                        }
                        face->thickness = p3->thickness;
                        face->linetype_scale = p3->linetype_scale;
                        face->visibility = p3->visibility;
                        face->color = p3->color;
                        face->paperspace = p3->paperspace;
                        if (p3->dictionary_owner_soft != NULL)
                        {
                                face->dictionary_owner_soft = strdup (p3->dictionary_owner_soft);
                        }
                        if (p3->dictionary_owner_hard != NULL)
                        {
                                face->dictionary_owner_hard = strdup (p3->dictionary_owner_hard);
                        }
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
                  (_("Error in %s () a NULL pointer was found in the next member.\n")),
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


/* EOF */
