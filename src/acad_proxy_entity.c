/*!
 * \file acad_proxy_entity.c
 *
 * \author Copyright (C) 2008 ... 2014 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief DXF acad_proxy_entity entity.
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


#include "acad_proxy_entity.h"


/*!
 * \brief Allocate memory for a DXF \c ACAD_PROXY_ENTITY.
 *
 * Fill the memory contents with zeros.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfAcadProxyEntity *
dxf_acad_proxy_entity_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfAcadProxyEntity *dxf_acad_proxy_entity = NULL;
        size_t size;

        size = sizeof (DxfAcadProxyEntity);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_acad_proxy_entity = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("ERROR in %s () could not allocate memory for a DxfAcadProxyEntity struct.\n")),
                  __FUNCTION__);
                dxf_acad_proxy_entity = NULL;
        }
        else
        {
                memset (dxf_acad_proxy_entity, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_acad_proxy_entity);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c ACAD_PROXY_ENTITY
 * table.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfAcadProxyEntity *
dxf_acad_proxy_entity_init
(
        DxfAcadProxyEntity *dxf_acad_proxy_entity
                /*!< DXF ACAD_PROXY_ENTITY table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        dxf_acad_proxy_entity = dxf_acad_proxy_entity_new ();
        if (dxf_acad_proxy_entity == NULL)
        {
              fprintf (stderr,
                (_("ERROR in %s () could not allocate memory for a DxfAcadProxyEntity struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        dxf_acad_proxy_entity->id_code = 0;
        dxf_acad_proxy_entity->linetype = strdup (DXF_DEFAULT_LINETYPE);
        dxf_acad_proxy_entity->layer = strdup (DXF_DEFAULT_LAYER);
        dxf_acad_proxy_entity->color = DXF_COLOR_BYLAYER;
        dxf_acad_proxy_entity->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        dxf_acad_proxy_entity->object_visability = 0;
        dxf_acad_proxy_entity->original_custom_object_data_format = 1;
        dxf_acad_proxy_entity->proxy_entity_class_id = DXF_DEFAULT_PROXY_ENTITY_ID;
        dxf_acad_proxy_entity->application_entity_class_id = 0;
        dxf_acad_proxy_entity->graphics_data_size = 0;
        dxf_acad_proxy_entity->object_drawing_format = 0;
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                dxf_acad_proxy_entity->binary_graphics_data[i] = strdup ("");
                dxf_acad_proxy_entity->object_id[i] = strdup ("");
        }
        dxf_acad_proxy_entity->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_acad_proxy_entity);
}


/*!
 * \brief Read data from a DXF file into a DXF \c ACAD_PROXY_ENTITY
 * entity.
 *
 * The last line read from file contained the string "ACAD_PROXY_ENTITY". \n
 * Now follows some data for the \c ACAD_PROXY_ENTITY, to be terminated
 * with a "  0" string announcing the following entity, or the end of
 * the \c ENTITY section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c dxf_acad_proxy_entity. \n
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_acad_proxy_entity_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfAcadProxyEntity *dxf_acad_proxy_entity
                /*!< DXF ACAD_PROXY_ENTITY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *temp_string = NULL;
        int i;
        int j;

        if (!dxf_acad_proxy_entity)
        {
                dxf_acad_proxy_entity = dxf_acad_proxy_entity_new ();
        }
        i = 0;
        j = 0;
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
                        return (EXIT_FAILURE);
                }
                else if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", &dxf_acad_proxy_entity->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing the linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_acad_proxy_entity->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing the layer
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_acad_proxy_entity->layer);
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing the linetype
                         * scale value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_acad_proxy_entity->linetype_scale);
                }
                else if (strcmp (temp_string, "60") == 0)
                {
                        /* Now follows a string containing the object
                         * visability value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_acad_proxy_entity->object_visability);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_acad_proxy_entity->color);
                }
                else if ((fp->acad_version_number >= AutoCAD_2000)
                && (strcmp (temp_string, "70") == 0))
                {
                        /* Now follows a string containing the original
                         * custom object data format value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_acad_proxy_entity->original_custom_object_data_format);
                        if (dxf_acad_proxy_entity->original_custom_object_data_format != 1)
                        {
                                fprintf (stderr,
                                  (_("Error in %s () found a bad original custom object data format value in: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                        }
                }
                else if (strcmp (temp_string, "90") == 0)
                {
                        /* Now follows a string containing the proxy
                         * entity ID value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_acad_proxy_entity->proxy_entity_class_id);
                        if (dxf_acad_proxy_entity->proxy_entity_class_id != DXF_DEFAULT_PROXY_ENTITY_ID)
                        {
                                fprintf (stderr,
                                  (_("Error in %s () found a bad proxy entity class ID in: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                        }
                }
                else if (strcmp (temp_string, "91") == 0)
                {
                        /* Now follows a string containing the application
                         * entity ID value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_acad_proxy_entity->application_entity_class_id);
                        if (dxf_acad_proxy_entity->application_entity_class_id < 500)
                        {
                                fprintf (stderr,
                                  (_("Error in %s () found a bad value in application entity class ID in: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                        }
                }
                else if (strcmp (temp_string, "92") == 0)
                {
                        /* Now follows a string containing the graphics
                         * data size value (bytes). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_acad_proxy_entity->graphics_data_size);
                }
                else if (strcmp (temp_string, "93") == 0)
                {
                        /* Now follows a string containing the entity
                         * data size value (bits). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_acad_proxy_entity->graphics_data_size);
                }
                else if ((fp->acad_version_number >= AutoCAD_2000)
                && (strcmp (temp_string, "95") == 0))
                {
                        /* Now follows a string containing the object
                         * drawing format value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%ld\n", &dxf_acad_proxy_entity->object_drawing_format);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
                        if ((strcmp (temp_string, "AcDbEntity") != 0)
                        && ((strcmp (temp_string, "AcDbProxyEntity") != 0)))
                        {
                                fprintf (stderr,
                                  (_("Error in %s () found a bad subclass marker in: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                        }
                }
                else if (strcmp (temp_string, "310") == 0)
                {
                        /* Now follows a string containing binary
                         * graphics data. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_acad_proxy_entity->binary_graphics_data[i]);
                        i++;
                }
                else if ((strcmp (temp_string, "330") == 0)
                || (strcmp (temp_string, "340") == 0)
                || (strcmp (temp_string, "350") == 0)
                || (strcmp (temp_string, "360") == 0))
                {
                        /* Now follows a string containing an object id. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_acad_proxy_entity->object_id[j]);
                        j++;
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
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write DXF output for a DXF \c ACAD_PROXY_ENTITY entity.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_acad_proxy_entity_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfAcadProxyEntity *dxf_acad_proxy_entity
                /*!< DXF \c ACAD_PROXY_ENTITY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = NULL;
        int i;

        if (dxf_acad_proxy_entity == NULL)
        {
                fprintf (stderr, "Error in dxf_acad_proxy_entity_write () a NULL pointer was passed.\n");
                return (EXIT_FAILURE);
        }
        if (fp->acad_version_number < AutoCAD_13)
        {
                fprintf (stderr, "Error in dxf_acad_proxy_entity_write () using DXF version before AutoCAD R13.\n");
                return (EXIT_FAILURE);
        }
        if (fp->acad_version_number == AutoCAD_13)
        {
                dxf_entity_name = strdup ("ACAD_ZOMBIE_ENTITY");
        }
        else
        {
                dxf_entity_name = strdup ("ACAD_PROXY_ENTITY");
        }
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (fp->acad_version_number >= AutoCAD_14)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
                fprintf (fp->fp, "100\nAcDbProxyEntity\n");
        }
        if (dxf_acad_proxy_entity->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", dxf_acad_proxy_entity->id_code);
        }
        if (strcmp (dxf_acad_proxy_entity->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", dxf_acad_proxy_entity->linetype);
        }
        fprintf (fp->fp, "  8\n%s\n", dxf_acad_proxy_entity->layer);
        if (dxf_acad_proxy_entity->thickness != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", dxf_acad_proxy_entity->thickness);
        }
        fprintf (fp->fp, " 48\n%f\n", dxf_acad_proxy_entity->linetype_scale);
        fprintf (fp->fp, " 60\n%d\n", dxf_acad_proxy_entity->object_visability);
        if (dxf_acad_proxy_entity->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", dxf_acad_proxy_entity->color);
        }
        if (dxf_acad_proxy_entity->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
        if (fp->acad_version_number >= AutoCAD_2000)
        {
                fprintf (fp->fp, " 70\n%d\n", dxf_acad_proxy_entity->original_custom_object_data_format);
        }
        fprintf (fp->fp, " 90\n%d\n", dxf_acad_proxy_entity->proxy_entity_class_id);
        fprintf (fp->fp, " 91\n%d\n", dxf_acad_proxy_entity->application_entity_class_id);
        fprintf (fp->fp, " 92\n%d\n", dxf_acad_proxy_entity->graphics_data_size);
        fprintf (fp->fp, " 93\n%d\n", dxf_acad_proxy_entity->entity_data_size);
        if (fp->acad_version_number >= AutoCAD_2000)
        {
                fprintf (fp->fp, " 95\n%ld\n", dxf_acad_proxy_entity->object_drawing_format);
        }
        i = 0;
        while (strlen (dxf_acad_proxy_entity->binary_graphics_data[i]) > 0)
        {
                fprintf (fp->fp, "310\n%s\n", dxf_acad_proxy_entity->binary_graphics_data[i]);
                i++;
        }
        i = 0;
        while (strlen (dxf_acad_proxy_entity->object_id[i]) > 0)
        {
                fprintf (fp->fp, "330\n%s\n", dxf_acad_proxy_entity->object_id[i]);
                i++;
        }
        fprintf (fp->fp, " 94\n  0\n");
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c ACAD_PROXY_ENTITY and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_acad_proxy_entity_free
(
        DxfAcadProxyEntity *dxf_acad_proxy_entity
                /*!< Pointer to the memory occupied by the DXF \c ACAD_PROXY_ENTITY
                 * table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        if (dxf_acad_proxy_entity->next != NULL)
        {
              fprintf (stderr, "ERROR in dxf_acad_proxy_entity_free () pointer to next DxfAcadProxyEntity was not NULL.\n");
              return (EXIT_FAILURE);
        }
        free (dxf_acad_proxy_entity->linetype);
        free (dxf_acad_proxy_entity->layer);
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                free (dxf_acad_proxy_entity->binary_graphics_data[i]);
                free (dxf_acad_proxy_entity->object_id[i]);
        }
        free (dxf_acad_proxy_entity);
        dxf_acad_proxy_entity = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
