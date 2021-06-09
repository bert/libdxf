/*!
 * \file acad_proxy_entity.c
 *
 * \author Copyright (C) 2013, 2014, 2015, 2016, 2017, 2018, 2019, 2020,
 * 2021 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF acad_proxy_entity entity
 * (\c ACAD_PROXY_ENTITY).
 *
 * \version The \c ACAD_ZOMBIE_ENTITY entity was introduced in DXF R13.
 * \version The \c ACAD_ZOMBIE_ENTITY entity was renamed to 
 * \c ACAD_PROXY_ENTITY in DXF R14.
 *
 * \warning dxf_acad_proxy_entity_new(), dxf_acad_proxy_entity_init(),
 * dxf_acad_proxy_entity_read() and dxf_acad_proxy_entity_free() are
 * backward compatible with versions R10 .. R12 to allow for reading DXF
 * data generated with other CAD software. \n
 * When writing DXF data to file with versions before DXF R13 a warning
 * message is given.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 * \version According to DXF R2000.
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
 * allocated memory when successful.
 */
DxfAcadProxyEntity *
dxf_acad_proxy_entity_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfAcadProxyEntity *acad_proxy_entity = NULL;
        size_t size;

        size = sizeof (DxfAcadProxyEntity);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((acad_proxy_entity = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                acad_proxy_entity = NULL;
        }
        else
        {
                memset (acad_proxy_entity, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (acad_proxy_entity);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c ACAD_PROXY_ENTITY
 * table.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfAcadProxyEntity *
dxf_acad_proxy_entity_init
(
        DxfAcadProxyEntity *acad_proxy_entity
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                acad_proxy_entity = dxf_acad_proxy_entity_new ();
        }
        if (acad_proxy_entity == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        /* Assign initial values to members. */
        acad_proxy_entity->id_code = 0;
        acad_proxy_entity->linetype = strdup (DXF_DEFAULT_LINETYPE);
        acad_proxy_entity->layer = strdup (DXF_DEFAULT_LAYER);
        acad_proxy_entity->elevation = 0.0;
        acad_proxy_entity->thickness = 0.0;
        acad_proxy_entity->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        acad_proxy_entity->visibility = 0;
        acad_proxy_entity->color = DXF_COLOR_BYLAYER;
        acad_proxy_entity->paperspace = DXF_PAPERSPACE;
        acad_proxy_entity->shadow_mode = 0;
        acad_proxy_entity->dictionary_owner_soft = strdup ("");
        acad_proxy_entity->object_owner_soft = strdup ("");
        acad_proxy_entity->material = strdup ("");
        acad_proxy_entity->dictionary_owner_hard = strdup ("");
        acad_proxy_entity->lineweight = 0;
        acad_proxy_entity->plot_style_name = strdup ("");
        acad_proxy_entity->color_value = 0;
        acad_proxy_entity->color_name = strdup ("");
        acad_proxy_entity->transparency = 0;
        acad_proxy_entity->original_custom_object_data_format = 1;
        acad_proxy_entity->proxy_entity_class_id = DXF_DEFAULT_PROXY_ENTITY_ID;
        acad_proxy_entity->application_entity_class_id = 0;
        acad_proxy_entity->graphics_data_size = 0;
        acad_proxy_entity->entity_data_size = 0;
        acad_proxy_entity->object_drawing_format = 0;
        acad_proxy_entity->object_id->group_code = 0;
        acad_proxy_entity->object_id->data = strdup ("");
        acad_proxy_entity->object_id->length = 0;
        /* Initialize new structs for the following members later,
         * when they are required and when we have content. */
        acad_proxy_entity->binary_graphics_data = NULL;
        acad_proxy_entity->binary_entity_data = NULL;
        acad_proxy_entity->object_id = NULL;
        acad_proxy_entity->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (acad_proxy_entity);
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
 * \return a pointer to \c acad_proxy_entity.
 */
DxfAcadProxyEntity *
dxf_acad_proxy_entity_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfAcadProxyEntity *acad_proxy_entity
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *temp_string = NULL;
        DxfBinaryData *iter310 = NULL;
        int iter330;
        int i; /* flags whether group code 330, 340, 350 or 360 has been
                * parsed for a first time. */

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
        if (!acad_proxy_entity)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                acad_proxy_entity = dxf_acad_proxy_entity_init (acad_proxy_entity);
        }
        if (acad_proxy_entity->binary_graphics_data == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfBinaryData struct.\n")));
                acad_proxy_entity->binary_graphics_data = dxf_binary_data_init (acad_proxy_entity->binary_graphics_data);
                if (acad_proxy_entity->binary_graphics_data == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        if (acad_proxy_entity->binary_entity_data == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfBinaryData struct.\n")));
                acad_proxy_entity->binary_entity_data = dxf_binary_data_init (acad_proxy_entity->binary_entity_data);
                if (acad_proxy_entity->binary_entity_data == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        iter310 = (DxfBinaryData *) acad_proxy_entity->binary_graphics_data;
        iter330 = 0;
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
                else if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", (uint *) &acad_proxy_entity->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing the linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, acad_proxy_entity->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing the layer
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, acad_proxy_entity->layer);
                }
                else if ((fp->acad_version_number <= AutoCAD_11)
                  && DXF_FLATLAND
                  && (strcmp (temp_string, "38") == 0)
                  && (acad_proxy_entity->elevation != 0.0))
                {
                        /* Now follows a string containing the
                         * elevation. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &acad_proxy_entity->elevation);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &acad_proxy_entity->thickness);
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing the linetype
                         * scale value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &acad_proxy_entity->linetype_scale);
                }
                else if (strcmp (temp_string, "60") == 0)
                {
                        /* Now follows a string containing the object
                         * visability value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &acad_proxy_entity->visibility);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &acad_proxy_entity->color);
                }
                else if ((fp->acad_version_number >= AutoCAD_2000)
                  && (strcmp (temp_string, "70") == 0))
                {
                        /* Now follows a string containing the original
                         * custom object data format value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &acad_proxy_entity->original_custom_object_data_format);
                        if (acad_proxy_entity->original_custom_object_data_format != 1)
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
                        fscanf (fp->fp, "%" PRIi32 "\n", &acad_proxy_entity->proxy_entity_class_id);
                        if (acad_proxy_entity->proxy_entity_class_id != DXF_DEFAULT_PROXY_ENTITY_ID)
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () found a bad proxy entity class ID in: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                        }
                }
                else if (strcmp (temp_string, "91") == 0)
                {
                        /* Now follows a string containing the application
                         * entity ID value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%" PRIi32 "\n", &acad_proxy_entity->application_entity_class_id);
                        if (acad_proxy_entity->application_entity_class_id < 500)
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () found a bad value in application entity class ID in: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                        }
                }
                else if (strcmp (temp_string, "92") == 0)
                {
                        /* Now follows a string containing the graphics
                         * data size value (bytes). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%" PRIi32 "\n", &acad_proxy_entity->graphics_data_size);
                }
                else if (strcmp (temp_string, "93") == 0)
                {
                        /* Now follows a string containing the entity
                         * data size value (bits). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%" PRIi32 "\n", &acad_proxy_entity->entity_data_size);
                }
                else if ((fp->acad_version_number >= AutoCAD_2000)
                  && (strcmp (temp_string, "95") == 0))
                {
                        /* Now follows a string containing the object
                         * drawing format value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%" PRIi32 "\n", &acad_proxy_entity->object_drawing_format);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                  && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if ((strcmp (temp_string, "AcDbEntity") != 0)
                          && ((strcmp (temp_string, "AcDbZombieEntity") != 0))
                          && ((strcmp (temp_string, "AcDbProxyEntity") != 0)))
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () found a bad subclass marker in: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                        }
                }
                else if (strcmp (temp_string, "284") == 0)
                {
                        /* Now follows a string containing the shadow
                         * mode value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &acad_proxy_entity->shadow_mode);
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
                                fscanf (fp->fp, DXF_MAX_STRING_FORMAT, acad_proxy_entity->dictionary_owner_soft);
                        }
                        if (iter330 == 1)
                        {
                                /* Now follows a string containing a soft-pointer
                                 * ID/handle to owner object. */
                                (fp->line_number)++;
                                fscanf (fp->fp, DXF_MAX_STRING_FORMAT, acad_proxy_entity->object_owner_soft);
                        }
                        iter330++;
                }
                else if ((strcmp (temp_string, "330") == 0)
                  || (strcmp (temp_string, "340") == 0)
                  || (strcmp (temp_string, "350") == 0)
                  || (strcmp (temp_string, "360") == 0))
                {
                        if (!i) /* For the very first object_id. */
                        {
                                dxf_object_id_set_group_code (acad_proxy_entity->object_id, atoi (temp_string));
                                /* Now follows a string containing an object id line of data. */
                                (fp->line_number)++;
                                fscanf (fp->fp, DXF_MAX_STRING_FORMAT, acad_proxy_entity->object_id->data);
                        }
                        else /* For following object_id's. */
                        {
                                DxfObjectId *iter = dxf_object_id_get_last ((DxfObjectId *) acad_proxy_entity->object_id);
                                iter = dxf_object_id_init ((DxfObjectId *) iter->next);
                                dxf_object_id_set_group_code (iter, atoi (temp_string));
                                /* Now follows a string containing an object id line of data. */
                                (fp->line_number)++;
                                fscanf (fp->fp, DXF_MAX_STRING_FORMAT, iter->data);
                        }
                        i++;
                }
                else if (strcmp (temp_string, "347") == 0)
                {
                        /* Now follows a string containing a
                         * hard-pointer ID/handle to material object. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, acad_proxy_entity->material);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, acad_proxy_entity->dictionary_owner_hard);
                }
                else if (strcmp (temp_string, "370") == 0)
                {
                        /* Now follows a string containing the lineweight
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &acad_proxy_entity->lineweight);
                }
                else if (strcmp (temp_string, "390") == 0)
                {
                        /* Now follows a string containing a plot style
                         * name value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, acad_proxy_entity->plot_style_name);
                }
                else if (strcmp (temp_string, "420") == 0)
                {
                        /* Now follows a string containing a color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%" PRIi32 "\n", &acad_proxy_entity->color_value);
                }
                else if (strcmp (temp_string, "430") == 0)
                {
                        /* Now follows a string containing a color
                         * name value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, acad_proxy_entity->color_name);
                }
                else if (strcmp (temp_string, "440") == 0)
                {
                        /* Now follows a string containing a transparency
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%" PRIi32 "\n", &acad_proxy_entity->transparency);
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
        /* Clean up. */
        free (temp_string);
#if DEBUG
        fprintf (stderr,
          (_("Information from %s() read %d object_id's from %s.\n")),
          __FUNCTION__, i, fp->filename);
        DXF_DEBUG_END
#endif
        return (acad_proxy_entity);
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
        DxfAcadProxyEntity *acad_proxy_entity
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = NULL;

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
        if (acad_proxy_entity == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (fp->acad_version_number < AutoCAD_13)
        {
                if (fp->follow_strict_version_rules)
                {
                        fprintf (stderr,
                          (_("Error in %s () illegal DXF version for this entity.\n")),
                          __FUNCTION__);
                        fprintf (stderr,
                          (_("\t entity %s with ID code %d is omitted from output.\n")),
                          dxf_entity_name, acad_proxy_entity->id_code);
                        return (EXIT_FAILURE);
                }
                else
                {
                        fprintf (stderr,
                          (_("Warning in %s () illegal DXF version for this entity.\n")),
                          __FUNCTION__);
                }
        }
        if (fp->acad_version_number <= AutoCAD_13)
        {
                dxf_entity_name = strdup ("ACAD_ZOMBIE_ENTITY");
        }
        else if (fp->acad_version_number >= AutoCAD_14)
        {
                dxf_entity_name = strdup ("ACAD_PROXY_ENTITY");
        }
        if ((strcmp (acad_proxy_entity->layer, "") == 0)
          || (acad_proxy_entity->layer == NULL))
        {
                fprintf (stderr,
                  (_("Warning in %s () invalid layer string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, acad_proxy_entity->id_code);
                fprintf (stderr,
                  (_("    %s entity is relocated to layer 0\n")),
                  dxf_entity_name);
                acad_proxy_entity->layer = strdup (DXF_DEFAULT_LAYER);
        }
        if (acad_proxy_entity->linetype == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () invalid linetype string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, acad_proxy_entity->id_code);
                fprintf (stderr,
                  (_("\t%s linetype is set to %s\n")),
                  dxf_entity_name, DXF_DEFAULT_LINETYPE);
                acad_proxy_entity->linetype = strdup(DXF_DEFAULT_LINETYPE);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (acad_proxy_entity->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", acad_proxy_entity->id_code);
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
        if ((strcmp (acad_proxy_entity->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", acad_proxy_entity->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (acad_proxy_entity->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", acad_proxy_entity->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (acad_proxy_entity->object_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_2000))
        {
                fprintf (fp->fp, "330\n%s\n", acad_proxy_entity->object_owner_soft);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
        }
        if (acad_proxy_entity->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%hd\n", (int16_t) DXF_PAPERSPACE);
        }
        fprintf (fp->fp, "  8\n%s\n", acad_proxy_entity->layer);
        if (strcmp (acad_proxy_entity->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", acad_proxy_entity->linetype);
        }
        if ((fp->acad_version_number >= AutoCAD_2008)
          && (strcmp (acad_proxy_entity->material, "") != 0))
        {
                fprintf (fp->fp, "347\n%s\n", acad_proxy_entity->material);
        }
        if (acad_proxy_entity->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%hd\n", acad_proxy_entity->color);
        }
        if (fp->acad_version_number >= AutoCAD_2002)
        {
                fprintf (fp->fp, "370\n%d\n", acad_proxy_entity->lineweight);
        }
        if ((fp->acad_version_number <= AutoCAD_11)
          && DXF_FLATLAND
          && (acad_proxy_entity->elevation != 0.0))
        {
                fprintf (fp->fp, " 38\n%f\n", acad_proxy_entity->elevation);
        }
        if ((fp->acad_version_number <= AutoCAD_13)
          && (acad_proxy_entity->thickness != 0.0))
        {
                fprintf (fp->fp, " 39\n%f\n", acad_proxy_entity->thickness);
        }
        fprintf (fp->fp, " 48\n%f\n", acad_proxy_entity->linetype_scale);
        fprintf (fp->fp, " 60\n%hd\n", acad_proxy_entity->visibility);
        if (fp->acad_version_number >= AutoCAD_2004)
        {
                fprintf (fp->fp, "420\n%" PRIi32 "\n", acad_proxy_entity->color_value);
                fprintf (fp->fp, "430\n%s\n", acad_proxy_entity->color_name);
                fprintf (fp->fp, "440\n%" PRIi32 "\n", acad_proxy_entity->transparency);
        }
        if (fp->acad_version_number >= AutoCAD_2009)
        {
                fprintf (fp->fp, "390\n%s\n", acad_proxy_entity->plot_style_name);
                fprintf (fp->fp, "284\n%d\n", acad_proxy_entity->shadow_mode);
        }
        if (fp->acad_version_number == AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbZombieEntity\n");
        }
        if (fp->acad_version_number >= AutoCAD_14)
        {
                fprintf (fp->fp, "100\nAcDbProxyEntity\n");
        }
        if (fp->acad_version_number >= AutoCAD_2000)
        {
                fprintf (fp->fp, " 70\n%hd\n", acad_proxy_entity->original_custom_object_data_format);
        }
        fprintf (fp->fp, " 90\n%" PRIi32 "\n", acad_proxy_entity->proxy_entity_class_id);
        fprintf (fp->fp, " 91\n%" PRIi32 "\n", acad_proxy_entity->application_entity_class_id);
        if (fp->acad_version_number >= AutoCAD_14)
        {
#ifdef BUILD_64
                fprintf (fp->fp, "160\n%" PRIi32 "\n", acad_proxy_entity->graphics_data_size);
#else
                fprintf (fp->fp, " 92\n%" PRIi32 "\n", acad_proxy_entity->graphics_data_size);
#endif
                if (acad_proxy_entity->binary_graphics_data != NULL)
                {
                        DxfBinaryData *iter310a;
                        iter310a = (DxfBinaryData *) acad_proxy_entity->binary_graphics_data;
                        while (iter310a != NULL)
                        {
                                fprintf (fp->fp, "310\n%s\n", iter310a->data_line);
                                iter310a = (DxfBinaryData *) iter310a->next;
                        }
                }
                fprintf (fp->fp, " 93\n%" PRIi32 "\n", acad_proxy_entity->entity_data_size);
                if (acad_proxy_entity->binary_entity_data != NULL)
                {
                        DxfBinaryData *iter310b;
                        iter310b = (DxfBinaryData *) acad_proxy_entity->binary_entity_data;
                        while (iter310b != NULL)
                        {
                                fprintf (fp->fp, "310\n%s\n", iter310b->data_line);
                                iter310b = (DxfBinaryData *) iter310b->next;
                        }
                }
        }
        DxfObjectId *iter330;
        iter330 = (DxfObjectId *) acad_proxy_entity->object_id;
        while (iter330)
        {
                fprintf (fp->fp, "330\n%s\n", iter330->data);
                iter330 = (DxfObjectId *) iter330->next;
        }
        fprintf (fp->fp, " 94\n  0\n");
        if (fp->acad_version_number >= AutoCAD_2000)
        {
                fprintf (fp->fp, " 95\n%" PRIi32 "\n", acad_proxy_entity->object_drawing_format);
        }
        if (fp->acad_version_number >= AutoCAD_2000)
        {
                fprintf (fp->fp, " 70\n%hd\n", acad_proxy_entity->original_custom_object_data_format);
        }
        /* Clean up. */
        free (dxf_entity_name);
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
        DxfAcadProxyEntity *acad_proxy_entity
                /*!< a pointer to the memory occupied by the DXF
                 * \c ACAD_PROXY_ENTITY table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (acad_proxy_entity == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (acad_proxy_entity->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (acad_proxy_entity->linetype);
        free (acad_proxy_entity->layer);
        free (acad_proxy_entity->dictionary_owner_soft);
        free (acad_proxy_entity->object_owner_soft);
        free (acad_proxy_entity->material);
        free (acad_proxy_entity->dictionary_owner_hard);
        free (acad_proxy_entity->plot_style_name);
        free (acad_proxy_entity->color_name);
        dxf_binary_data_free_list (acad_proxy_entity->binary_graphics_data);
        dxf_binary_data_free_list (acad_proxy_entity->binary_entity_data);
        dxf_object_id_free_list (acad_proxy_entity->object_id);
        free (acad_proxy_entity);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c ACAD_PROXY_ENTITY entities and all their data fields.
 */
void
dxf_acad_proxy_entity_free_list
(
        DxfAcadProxyEntity *acad_proxy_entities
                /*!< a pointer to the single linked list of DXF
                 * \c ACAD_PROXY_ENTITY entities. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (acad_proxy_entities == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (acad_proxy_entities != NULL)
        {
                DxfAcadProxyEntity *iter = (DxfAcadProxyEntity *) acad_proxy_entities->next;
                dxf_acad_proxy_entity_free (acad_proxy_entities);
                acad_proxy_entities = (DxfAcadProxyEntity *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the ID code from a DXF \c ACAD_PROXY_ENTITY entity.
 *
 * \return ID code.
 */
int
dxf_acad_proxy_entity_get_id_code
(
        DxfAcadProxyEntity *acad_proxy_entity
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (acad_proxy_entity->id_code < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (acad_proxy_entity->id_code);
}


/*!
 * \brief Set the ID code for a DXF \c ACAD_PROXY_ENTITY entity.
 */
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_id_code
(
        DxfAcadProxyEntity *acad_proxy_entity,
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
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
        if (acad_proxy_entity == NULL)
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
        acad_proxy_entity->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (acad_proxy_entity);
}


/*!
 * \brief Get the linetype from a DXF \c ACAD_PROXY_ENTITY entity.
 *
 * \return linetype when sucessful, \c NULL when an error occurred.
 */
char *
dxf_acad_proxy_entity_get_linetype
(
        DxfAcadProxyEntity *acad_proxy_entity
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (acad_proxy_entity->linetype ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the linetype member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (acad_proxy_entity->linetype));
}


/*!
 * \brief Set the linetype for a DXF \c ACAD_PROXY_ENTITY entity.
 */
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_linetype
(
        DxfAcadProxyEntity *acad_proxy_entity,
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
        char *linetype
                /*!< a string containing the linetype for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
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
        acad_proxy_entity->linetype = strdup (linetype);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (acad_proxy_entity);
}


/*!
 * \brief Get the layer from a DXF \c ACAD_PROXY_ENTITY entity.
 *
 * \return layer when sucessful, \c NULL when an error occurred.
 */
char *
dxf_acad_proxy_entity_get_layer
(
        DxfAcadProxyEntity *acad_proxy_entity
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (acad_proxy_entity->layer ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the layer member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (acad_proxy_entity->layer));
}


/*!
 * \brief Set the layer for a DXF \c ACAD_PROXY_ENTITY entity.
 */
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_layer
(
        DxfAcadProxyEntity *acad_proxy_entity,
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
        char *layer
                /*!< a string containing the layer for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
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
        acad_proxy_entity->layer = strdup (layer);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (acad_proxy_entity);
}


/*!
 * \brief Get the \c elevation a this DXF \c ACAD_PROXY_ENTITY entity.
 *
 * \return \c elevation.
 */
double
dxf_acad_proxy_entity_get_elevation
(
        DxfAcadProxyEntity *acad_proxy_entity
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (acad_proxy_entity->elevation);
}


/*!
 * \brief Set the \c elevation for a DXF \c ACAD_PROXY_ENTITY entity.
 *
 * \return a pointer to \c acad_proxy_entity when sucessful, \c NULL
 * when an error occurred.
 */
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_elevation
(
        DxfAcadProxyEntity *acad_proxy_entity,
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
        double elevation
                /*!< the \c elevation to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        acad_proxy_entity->elevation = elevation;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (acad_proxy_entity);
}


/*!
 * \brief Get the \c thickness from a DXF \c ACAD_PROXY_ENTITY entity.
 *
 * \return \c thickness.
 */
double
dxf_acad_proxy_entity_get_thickness
(
        DxfAcadProxyEntity *acad_proxy_entity
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (acad_proxy_entity->thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (acad_proxy_entity->thickness);
}


/*!
 * \brief Set the \c thickness for a DXF \c ACAD_PROXY_ENTITY entity.
 *
 * \return a pointer to \c acad_proxy_entity when sucessful, \c NULL
 * when an error occurred.
 */
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_thickness
(
        DxfAcadProxyEntity *acad_proxy_entity,
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
        double thickness
                /*!< the \c thickness to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
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
        acad_proxy_entity->thickness = thickness;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (acad_proxy_entity);
}


/*!
 * \brief Get the linetype scale from a DXF \c ACAD_PROXY_ENTITY entity.
 *
 * \return linetype scale.
 */
double
dxf_acad_proxy_entity_get_linetype_scale
(
        DxfAcadProxyEntity *acad_proxy_entity
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (acad_proxy_entity->linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (acad_proxy_entity->linetype_scale);
}


/*!
 * \brief Set the linetype scale for a DXF \c ACAD_PROXY_ENTITY entity.
 */
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_linetype_scale
(
        DxfAcadProxyEntity *acad_proxy_entity,
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
        double linetype_scale
                /*!< the linetype scale to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
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
        acad_proxy_entity->linetype_scale = linetype_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (acad_proxy_entity);
}


/*!
 * \brief Get the object visibility from a DXF \c ACAD_PROXY_ENTITY entity.
 *
 * \return object visibility.
 */
int16_t
dxf_acad_proxy_entity_get_visibility
(
        DxfAcadProxyEntity *acad_proxy_entity
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (acad_proxy_entity->visibility < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (acad_proxy_entity->visibility > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (acad_proxy_entity->visibility);
}


/*!
 * \brief Set the visibility for a DXF \c ACAD_PROXY_ENTITY entity.
 */
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_visibility
(
        DxfAcadProxyEntity *acad_proxy_entity,
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
        int16_t visibility
                /*!< the visibility to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
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
        acad_proxy_entity->visibility = visibility;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (acad_proxy_entity);
}


/*!
 * \brief Get the color from a DXF \c ACAD_PROXY_ENTITY entity.
 *
 * \return color.
 */
int16_t
dxf_acad_proxy_entity_get_color
(
        DxfAcadProxyEntity *acad_proxy_entity
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (acad_proxy_entity->color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (acad_proxy_entity->color);
}


/*!
 * \brief Set the color for a DXF \c ACAD_PROXY_ENTITY entity.
 */
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_color
(
        DxfAcadProxyEntity *acad_proxy_entity,
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
        int16_t color
                /*!< the color to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
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
                fprintf (stderr,
                  (_("\teffectively turning this entity it's visibility off.\n")));
        }
        acad_proxy_entity->color = color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (acad_proxy_entity);
}


/*!
 * \brief Get the paperspace flag value from a DXF \c ACAD_PROXY_ENTITY
 * entity.
 *
 * \return paperspace flag value.
 */
int16_t
dxf_acad_proxy_entity_get_paperspace
(
        DxfAcadProxyEntity *acad_proxy_entity
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (acad_proxy_entity->paperspace < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (acad_proxy_entity->paperspace > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (acad_proxy_entity->paperspace);
}


/*!
 * \brief Set the paperspace flag for a DXF \c ACAD_PROXY_ENTITY entity.
 */
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_paperspace
(
        DxfAcadProxyEntity *acad_proxy_entity,
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
        int16_t paperspace
                /*!< the paperspace flag value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
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
        acad_proxy_entity->paperspace = paperspace;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (acad_proxy_entity);
}


/*!
 * \brief Get the \c shadow_mode from a DXF \c ACAD_PROXY_ENTITY entity.
 *
 * \return \c shadow_mode when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_acad_proxy_entity_get_shadow_mode
(
        DxfAcadProxyEntity *acad_proxy_entity
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (acad_proxy_entity->shadow_mode < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (acad_proxy_entity->shadow_mode > 3)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (acad_proxy_entity->shadow_mode);
}


/*!
 * \brief Set the \c shadow_mode for a DXF \c ACAD_PROXY_ENTITY entity.
 *
 * \return a pointer to \c acad_proxy_entity when successful, or \c NULL
 * when an error occurred.
 */
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_shadow_mode
(
        DxfAcadProxyEntity *acad_proxy_entity,
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
        int16_t shadow_mode
                /*!< the shadow mode to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
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
        acad_proxy_entity->shadow_mode = shadow_mode;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (acad_proxy_entity);
}


/*!
 * \brief Get the soft pointer to the dictionary owner from a DXF 
 * \c ACAD_PROXY_ENTITY entity.
 *
 * \return soft pointer to the dictionary owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_acad_proxy_entity_get_dictionary_owner_soft
(
        DxfAcadProxyEntity *acad_proxy_entity
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (acad_proxy_entity->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (acad_proxy_entity->dictionary_owner_soft));
}


/*!
 * \brief Set the pointer to the dictionary_owner_soft for a DXF
 * \c ACAD_PROXY_ENTITY entity.
 */
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_dictionary_owner_soft
(
        DxfAcadProxyEntity *acad_proxy_entity,
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the
                 * dictionary_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
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
        acad_proxy_entity->dictionary_owner_soft = strdup (dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (acad_proxy_entity);
}


/*!
 * \brief Get the soft pointer to the object owner from a DXF 
 * \c ACAD_PROXY_ENTITY entity.
 *
 * \return soft pointer to the object owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_acad_proxy_entity_get_object_owner_soft
(
        DxfAcadProxyEntity *acad_proxy_entity
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (acad_proxy_entity->object_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (acad_proxy_entity->object_owner_soft));
}


/*!
 * \brief Set the pointer to the \c object_owner_soft for a DXF
 * \c ACAD_PROXY_ENTITY entity.
 */
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_object_owner_soft
(
        DxfAcadProxyEntity *acad_proxy_entity,
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
        char *object_owner_soft
                /*!< a string containing the pointer to the
                 * \c object_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
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
        acad_proxy_entity->object_owner_soft = strdup (object_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (acad_proxy_entity);
}


/*!
 * \brief Get the pointer to the \c material from a DXF \c ACAD_PROXY_ENTITY entity.
 *
 * \return a pointer to \c material when successful, or \c NULL when an
 * error occurred.
 *
 * \warning No checks are performed on the returned pointer.
 */
char *
dxf_acad_proxy_entity_get_material
(
        DxfAcadProxyEntity *acad_proxy_entity
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (acad_proxy_entity->material ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (acad_proxy_entity->material));
}


/*!
 * \brief Set the pointer to the \c material for a DXF
 * \c ACAD_PROXY_ENTITY entity.
 *
 * \return a pointer to \c acad_proxy_entity when successful, or \c NULL
 * when an error occurred.
 */
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_material
(
        DxfAcadProxyEntity *acad_proxy_entity,
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
        char *material
                /*!< a string containing the pointer to the \c
                 * material for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
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
        acad_proxy_entity->material = strdup (material);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (acad_proxy_entity);
}


/*!
 * \brief Get the hard pointer to the dictionary owner from a DXF 
 * \c ACAD_PROXY_ENTITY entity.
 *
 * \return hard pointer to the dictionary owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_acad_proxy_entity_get_dictionary_owner_hard
(
        DxfAcadProxyEntity *acad_proxy_entity
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (acad_proxy_entity->dictionary_owner_hard ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (acad_proxy_entity->dictionary_owner_hard));
}


/*!
 * \brief Set the pointer to the dictionary_owner_hard for a DXF
 * \c ACAD_PROXY_ENTITY entity.
 */
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_dictionary_owner_hard
(
        DxfAcadProxyEntity *acad_proxy_entity,
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
        char *dictionary_owner_hard
                /*!< a string containing the pointer to the
                 * dictionary_owner_hard for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
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
        acad_proxy_entity->dictionary_owner_hard = strdup (dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (acad_proxy_entity);
}


/*!
 * \brief Get the \c lineweight from a DXF \c ACAD_PROXY_ENTITY entity.
 *
 * \return \c lineweight when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_acad_proxy_entity_get_lineweight
(
        DxfAcadProxyEntity *acad_proxy_entity
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (acad_proxy_entity->lineweight);
}


/*!
 * \brief Set the \c lineweight for a DXF \c ACAD_PROXY_ENTITY entity.
 *
 * \return a pointer to \c face when successful, or \c NULL when an
 * error occurred.
 */
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_lineweight
(
        DxfAcadProxyEntity *acad_proxy_entity,
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
        int16_t lineweight
                /*!< the \c lineweight to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        acad_proxy_entity->lineweight = lineweight;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (acad_proxy_entity);
}


/*!
 * \brief Get the \c plot_style_name from a DXF \c ACAD_PROXY_ENTITY
 * entity.
 *
 * \return a pointer to \c plot_style_name when sucessful, or \c NULL
 * when an error occurred.
 */
char *
dxf_acad_proxy_entity_get_plot_style_name
(
        DxfAcadProxyEntity *acad_proxy_entity
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (acad_proxy_entity->plot_style_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (acad_proxy_entity->plot_style_name));
}


/*!
 * \brief Set the \c plot_style_name for a DXF \c ACAD_PROXY_ENTITY entity.
 *
 * \return a pointer to \c acad_proxy_entity when successful, or \c NULL
 * when an error occurred.
 */
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_plot_style_name
(
        DxfAcadProxyEntity *acad_proxy_entity,
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
        char *plot_style_name
                /*!< a string containing the \c plot_style_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
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
        acad_proxy_entity->plot_style_name = strdup (plot_style_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (acad_proxy_entity);
}


/*!
 * \brief Get the \c color_value from a DXF \c ACAD_PROXY_ENTITY entity.
 *
 * \return \c color_value when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int32_t
dxf_acad_proxy_entity_get_color_value
(
        DxfAcadProxyEntity *acad_proxy_entity
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (acad_proxy_entity->color_value);
}


/*!
 * \brief Set the \c color_value for a DXF \c ACAD_PROXY_ENTITY entity.
 *
 * \return a pointer to \c face when successful, or \c NULL when an
 * error occurred.
 */
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_color_value
(
        DxfAcadProxyEntity *acad_proxy_entity,
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
        int32_t color_value
                /*!< the \c color_value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        acad_proxy_entity->color_value = color_value;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (acad_proxy_entity);
}


/*!
 * \brief Get the \c color_name from a DXF \c ACAD_PROXY_ENTITY entity.
 *
 * \return \c color_name when sucessful, or \c NULL when an error
 * occurred.
 */
char *
dxf_acad_proxy_entity_get_color_name
(
        DxfAcadProxyEntity *acad_proxy_entity
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (acad_proxy_entity->color_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (acad_proxy_entity->color_name));
}


/*!
 * \brief Set the \c color_name for a DXF \c ACAD_PROXY_ENTITY entity.
 *
 * \return a pointer to \c acad_proxy_entity when successful, or \c NULL when an
 * error occurred.
 */
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_color_name
(
        DxfAcadProxyEntity *acad_proxy_entity,
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
        char *color_name
                /*!< a string containing the \c color_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
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
        acad_proxy_entity->color_name = strdup (color_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (acad_proxy_entity);
}


/*!
 * \brief Get the \c transparency from a DXF \c ACAD_PROXY_ENTITY entity.
 *
 * \return \c transparency when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int32_t
dxf_acad_proxy_entity_get_transparency
(
        DxfAcadProxyEntity *acad_proxy_entity
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (acad_proxy_entity->transparency);
}


/*!
 * \brief Set the \c transparency for a DXF \c ACAD_PROXY_ENTITY entity.
 *
 * \return a pointer to \c acad_proxy_entity when successful, or \c NULL when an
 * error occurred.
 */
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_transparency
(
        DxfAcadProxyEntity *acad_proxy_entity,
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
        int32_t transparency
                /*!< the \c transparency to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        acad_proxy_entity->transparency = transparency;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (acad_proxy_entity);
}


/*!
 * \brief Get the original custom object data format value from a DXF
 * \c ACAD_PROXY_ENTITY entity.
 *
 * \return original custom object data format value.
 */
int16_t
dxf_acad_proxy_entity_get_original_custom_object_data_format
(
        DxfAcadProxyEntity *acad_proxy_entity
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (acad_proxy_entity->original_custom_object_data_format < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (acad_proxy_entity->original_custom_object_data_format > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (acad_proxy_entity->original_custom_object_data_format);
}


/*!
 * \brief Set the original custom object data format value for a DXF
 * \c ACAD_PROXY_ENTITY entity.
 */
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_original_custom_object_data_format
(
        DxfAcadProxyEntity *acad_proxy_entity,
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
        int16_t original_custom_object_data_format
                /*!< the original custom object data format value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (original_custom_object_data_format < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (original_custom_object_data_format > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        acad_proxy_entity->original_custom_object_data_format = original_custom_object_data_format;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (acad_proxy_entity);
}


/*!
 * \brief Get the proxy entity class id value from a DXF
 * \c ACAD_PROXY_ENTITY entity.
 *
 * \return proxy entity class id value.
 */
int32_t
dxf_acad_proxy_entity_get_proxy_entity_class_id
(
        DxfAcadProxyEntity *acad_proxy_entity
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (acad_proxy_entity->proxy_entity_class_id != 498)
        {
                fprintf (stderr,
                  (_("Warning in %s () an invalid value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (acad_proxy_entity->proxy_entity_class_id);
}


/*!
 * \brief Set the proxy entity class id value for a DXF
 * \c ACAD_PROXY_ENTITY entity.
 */
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_proxy_entity_class_id
(
        DxfAcadProxyEntity *acad_proxy_entity,
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
        int32_t proxy_entity_class_id
                /*!< the proxy entity class id value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (proxy_entity_class_id != 498)
        {
                fprintf (stderr,
                  (_("Warning in %s () an invalid value was passed.\n")),
                  __FUNCTION__);
        }
        acad_proxy_entity->proxy_entity_class_id = proxy_entity_class_id;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (acad_proxy_entity);
}


/*!
 * \brief Get the application entity class id value from a DXF
 * \c ACAD_PROXY_ENTITY entity.
 *
 * \return application entity class id value.
 */
int32_t
dxf_acad_proxy_entity_get_application_entity_class_id
(
        DxfAcadProxyEntity *acad_proxy_entity
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (acad_proxy_entity->application_entity_class_id < 500)
        {
                fprintf (stderr,
                  (_("Warning in %s () an invalid value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (acad_proxy_entity->application_entity_class_id);
}


/*!
 * \brief Set the application entity class id value for a DXF
 * \c ACAD_PROXY_ENTITY entity.
 */
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_application_entity_class_id
(
        DxfAcadProxyEntity *acad_proxy_entity,
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
        int32_t application_entity_class_id
                /*!< the application entity class id value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (application_entity_class_id < 500)
        {
                fprintf (stderr,
                  (_("Warning in %s () an invalid value was passed.\n")),
                  __FUNCTION__);
        }
        acad_proxy_entity->application_entity_class_id = application_entity_class_id;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (acad_proxy_entity);
}


/*!
 * \brief Get the graphics data size value from a DXF
 * \c ACAD_PROXY_ENTITY entity.
 *
 * \return graphics data size value.
 */
int
dxf_acad_proxy_entity_get_graphics_data_size
(
        DxfAcadProxyEntity *acad_proxy_entity
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (acad_proxy_entity->graphics_data_size < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () an invalid value was passed.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (acad_proxy_entity->graphics_data_size);
}


/*!
 * \brief Set the graphics data size value for a DXF
 * \c ACAD_PROXY_ENTITY entity.
 */
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_graphics_data_size
(
        DxfAcadProxyEntity *acad_proxy_entity,
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
        int graphics_data_size
                /*!< the graphics data size value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (graphics_data_size < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () an invalid value was passed.\n")),
                  __FUNCTION__);
        }
        acad_proxy_entity->graphics_data_size = graphics_data_size;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (acad_proxy_entity);
}


/*!
 * \brief Get the entity data size value from a DXF
 * \c ACAD_PROXY_ENTITY entity.
 *
 * \return entity data size value.
 */
int32_t
dxf_acad_proxy_entity_get_entity_data_size
(
        DxfAcadProxyEntity *acad_proxy_entity
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (acad_proxy_entity->entity_data_size < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () an invalid value was passed.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (acad_proxy_entity->entity_data_size);
}


/*!
 * \brief Set the entity data size value for a DXF
 * \c ACAD_PROXY_ENTITY entity.
 */
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_entity_data_size
(
        DxfAcadProxyEntity *acad_proxy_entity,
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
        int32_t entity_data_size
                /*!< the entity data size value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (entity_data_size < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () an invalid value was passed.\n")),
                  __FUNCTION__);
        }
        acad_proxy_entity->entity_data_size = entity_data_size;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (acad_proxy_entity);
}


/*!
 * \brief Get the object drawing format value from a DXF
 * \c ACAD_PROXY_ENTITY entity.
 *
 * \return object drawing format value.
 */
uint32_t
dxf_acad_proxy_entity_get_object_drawing_format
(
        DxfAcadProxyEntity *acad_proxy_entity
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (acad_proxy_entity->object_drawing_format);
}


/*!
 * \brief Set the \c object_drawing_format value for a DXF
 * \c ACAD_PROXY_ENTITY entity.
 */
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_object_drawing_format
(
        DxfAcadProxyEntity *acad_proxy_entity,
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
        uint32_t object_drawing_format
                /*!< the \c object_drawing_format value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        acad_proxy_entity->object_drawing_format = object_drawing_format;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (acad_proxy_entity);
}


/*!
 * \brief Get the pointer to the \c binary_graphics_data from a DXF 
 * \c ACAD_PROXY_ENTITY entity.
 *
 * \return pointer to the \c binary_graphics_data.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfBinaryData *
dxf_acad_proxy_entity_get_binary_graphics_data
(
        DxfAcadProxyEntity *acad_proxy_entity
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (acad_proxy_entity->binary_graphics_data ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfBinaryData *) acad_proxy_entity->binary_graphics_data);
}


/*!
 * \brief Set the pointer to the \c binary_graphics_data for a DXF
 * \c ACAD_PROXY_ENTITY entity.
 */
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_binary_graphics_data
(
        DxfAcadProxyEntity *acad_proxy_entity,
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
        DxfBinaryData *data
                /*!< a string containing the pointer to the
                 * \c binary_graphics_data for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
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
        if (acad_proxy_entity->binary_graphics_data == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfBinaryData struct.\n")));
                acad_proxy_entity->binary_graphics_data = dxf_binary_data_init (acad_proxy_entity->binary_graphics_data);
                if (acad_proxy_entity->binary_graphics_data == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        acad_proxy_entity->binary_graphics_data = (DxfBinaryData *) data;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (acad_proxy_entity);
}


/*!
 * \brief Get the pointer to the \c binary_entity_data from a DXF 
 * \c ACAD_PROXY_ENTITY entity.
 *
 * \return pointer to the \c binary_entity_data.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfBinaryData *
dxf_acad_proxy_entity_get_binary_entity_data
(
        DxfAcadProxyEntity *acad_proxy_entity
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (acad_proxy_entity->binary_entity_data ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfBinaryData *) acad_proxy_entity->binary_entity_data);
}


/*!
 * \brief Set the pointer to the \c binary_entity_data for a DXF
 * \c ACAD_PROXY_ENTITY entity.
 */
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_binary_entity_data
(
        DxfAcadProxyEntity *acad_proxy_entity,
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
        DxfBinaryData *data
                /*!< a string containing the pointer to the
                 * \c binary_entity_data for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
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
        acad_proxy_entity->binary_entity_data = (DxfBinaryData *) data;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (acad_proxy_entity);
}


/*!
 * \brief Get the pointer to the first \c object_id from a DXF 
 * \c ACAD_PROXY_ENTITY entity.
 *
 * \return pointer to the first \c object_id (single linked list).
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfObjectId *
dxf_acad_proxy_entity_get_object_id
(
        DxfAcadProxyEntity *acad_proxy_entity
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (acad_proxy_entity->object_id ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfObjectId *) acad_proxy_entity->object_id);
}


/*!
 * \brief Set the pointer to the first \c object_id for a DXF
 * \c ACAD_PROXY_ENTITY entity.
 */
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_object_id
(
        DxfAcadProxyEntity *acad_proxy_entity,
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
        DxfObjectId *object_id
                /*!< a string containing the pointer to the
                 * \c object_id for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (object_id == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        acad_proxy_entity->object_id = (DxfObjectId *) object_id;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (acad_proxy_entity);
}


/*!
 * \brief Get the pointer to the next \c ACAD_PROXY_ENTITY entity from a
 * DXF \c ACAD_PROXY_ENTITY entity.
 *
 * \return pointer to the next \c ACAD_PROXY_ENTITY entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfAcadProxyEntity *
dxf_acad_proxy_entity_get_next
(
        DxfAcadProxyEntity *acad_proxy_entity
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (acad_proxy_entity->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfAcadProxyEntity *) acad_proxy_entity->next);
}


/*!
 * \brief Set the pointer to the next \c ACAD_PROXY_ENTITY for a DXF
 * \c ACAD_PROXY_ENTITY entity.
 */
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_next
(
        DxfAcadProxyEntity *acad_proxy_entity,
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
        DxfAcadProxyEntity *next
                /*!< a pointer to the next \c ACAD_PROXY_ENTITY for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
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
        acad_proxy_entity->next = (struct DxfAcadProxyEntity *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (acad_proxy_entity);
}


/*!
 * \brief Get the pointer to the last \c ACAD_PROXY_ENTITY entity from a
 * linked list of DXF \c ACAD_PROXY_ENTITY entities.
 *
 * \return pointer to the last \c ACAD_PROXY_ENTITY entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfAcadProxyEntity *
dxf_acad_proxy_entity_get_last
(
        DxfAcadProxyEntity *acad_proxy_entity
                /*!< a pointer to a DXF \c ACAD_PROXY_ENTITY entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (acad_proxy_entity == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (acad_proxy_entity->next == NULL)
        {
                return ((DxfAcadProxyEntity *) acad_proxy_entity);
        }
        DxfAcadProxyEntity *iter = (DxfAcadProxyEntity *) acad_proxy_entity->next;
        while (iter->next != NULL)
        {
                iter = (DxfAcadProxyEntity *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfAcadProxyEntity *) iter);
}


/* EOF */
