/*!
 * \file group.c
 *
 * \author Copyright (C) 2015, 2017, 2018, 2019, 2020, 2021
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF group object (\c GROUP).
 *
 * \since The \c GROUP object was introduced in DXF R13.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
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


#include "group.h"


/*!
 * \brief Allocate memory for a \c DxfGroup.
 *
 * Fill the memory contents with zeros.
 */
DxfGroup *
dxf_group_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfGroup *group = NULL;
        size_t size;

        size = sizeof (DxfGroup);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((group = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                group = NULL;
        }
        else
        {
                memset (group, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (group);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c GROUP
 * object.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfGroup *
dxf_group_init
(
        DxfGroup *group
                /*!< DXF \c GROUP object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (group == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                group = dxf_group_new ();
        }
        if (group == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        group->id_code = 0;
        group->description = strdup ("");
        group->handle_entity_in_group = strdup ("");
        group->unnamed_flag = 0;
        group->selectability_flag = 0;
        group->dictionary_owner_soft = strdup ("");
        group->dictionary_owner_hard = strdup ("");
        group->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (group);
}


/*!
 * \brief Read data from a DXF file into a DXF \c GROUP object.
 *
 * The last line read from file contained the string "GROUP". \n
 * Now follows some data for the \c GROUP object, to be terminated
 * with a "  0" string announcing the following object. \n
 * While parsing the DXF file store data in \c group. \n
 *
 * \return \c a pointer to \c group object.
 */
DxfGroup *
dxf_group_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfGroup *group
                /*!< DXF \c GROUP object. */
)
{
#if DEBUG
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
        if (fp->acad_version_number < AutoCAD_13)
        {
                fprintf (stderr,
                  (_("Warning in %s () illegal DXF version for this entity.\n")),
                  __FUNCTION__);
        }
        if (group == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                group = dxf_group_init (group);
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
                        fscanf (fp->fp, "%x\n", (uint *) &group->id_code);
                }
                else if (strcmp (temp_string, "70") == 0)
                {
                        /* Now follows a string containing the
                         * unnamed flag value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &group->unnamed_flag);
                }
                else if (strcmp (temp_string, "71") == 0)
                {
                        /* Now follows a string containing the
                         * selectability flag value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &group->selectability_flag);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if (strcmp (temp_string, "AcDbGroup") != 0)
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () found a bad subclass marker in: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                        }
                }
                else if (strcmp (temp_string, "300") == 0)
                {
                        /* Now follows a string containing a description. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, group->description);
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing Soft-pointer
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, group->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "340") == 0)
                {
                        /* Now follows a string containing a handle to an
                         * entry in group object. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, group->handle_entity_in_group);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, group->dictionary_owner_hard);
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
        /* Clean up. */
        free (temp_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (group);
}


/*!
 * \brief Write DXF output to a file for a DXF \c GROUP object.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_group_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfGroup *group
                /*!< DXF \c Group object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("GROUP");

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
        if (group == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (strcmp (group->description, "") == 0)
        {
                fprintf (stderr,
                  (_("Error in %s () empty description string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, group->id_code);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (strcmp (group->handle_entity_in_group, "") == 0)
        {
                fprintf (stderr,
                  (_("Error in %s () empty string for handle entity in group for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, group->id_code);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (fp->acad_version_number < AutoCAD_13)
        {
                fprintf (stderr,
                  (_("Warning in %s () illegal DXF version for this %s entity with id-code: %x.\n")),
                  __FUNCTION__, dxf_entity_name, group->id_code);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (group->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", group->id_code);
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
        if ((strcmp (group->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", group->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (group->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", group->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbGroup\n");
        }
        fprintf (fp->fp, "300\n%s\n", group->description);
        fprintf (fp->fp, " 70\n%d\n", group->unnamed_flag);
        fprintf (fp->fp, " 71\n%d\n", group->selectability_flag);
        fprintf (fp->fp, "340\n%s\n", group->handle_entity_in_group);
        /* Clean up. */
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c GROUP and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_group_free
(
        DxfGroup *group
                /*!< Pointer to the memory occupied by the DXF
                 * \c GROUP object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (group == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (group->next != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to next was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (group->dictionary_owner_soft);
        free (group->dictionary_owner_hard);
        free (group->description);
        free (group->handle_entity_in_group);
        free (group);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c GROUP objects and all their data fields.
 */
void
dxf_group_free_list
(
        DxfGroup *groups
                /*!< pointer to the single linked list of DXF \c GROUP
                 * objects. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (groups == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (groups != NULL)
        {
                DxfGroup *iter = (DxfGroup *) groups->next;
                dxf_group_free (groups);
                groups = (DxfGroup *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the ID code from a DXF \c GROUP object.
 *
 * \return ID code.
 */
int
dxf_group_get_id_code
(
        DxfGroup *group
                /*!< a pointer to a DXF \c GROUP object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (group == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (group->id_code < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (group->id_code);
}


/*!
 * \brief Set the ID code for a DXF \c GROUP object.
 */
DxfGroup *
dxf_group_set_id_code
(
        DxfGroup *group,
                /*!< a pointer to a DXF \c GROUP object. */
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
        if (group == NULL)
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
        group->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (group);
}


/*!
 * \brief Get the soft pointer to the dictionary owner from a DXF 
 * \c GROUP object.
 *
 * \return soft pointer to the dictionary owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_group_get_dictionary_owner_soft
(
        DxfGroup *group
                /*!< a pointer to a DXF \c GROUP object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (group == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (group->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (group->dictionary_owner_soft));
}


/*!
 * \brief Set the pointer to the dictionary_owner_soft for a DXF
 * \c GROUP object.
 */
DxfGroup *
dxf_group_set_dictionary_owner_soft
(
        DxfGroup *group,
                /*!< a pointer to a DXF \c GROUP object. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the
                 * dictionary_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (group == NULL)
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
        group->dictionary_owner_soft = strdup (dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (group);
}


/*!
 * \brief Get the soft pointer to the object owner from a DXF 
 * \c GROUP object.
 *
 * \return soft pointer to the object owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_group_get_object_owner_soft
(
        DxfGroup *group
                /*!< a pointer to a DXF \c GROUP object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (group == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (group->object_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (group->object_owner_soft));
}


/*!
 * \brief Set the pointer to the \c object_owner_soft for a DXF
 * \c GROUP object.
 */
DxfGroup *
dxf_group_set_object_owner_soft
(
        DxfGroup *group,
                /*!< a pointer to a DXF \c GROUP object. */
        char *object_owner_soft
                /*!< a string containing the pointer to the
                 * \c object_owner_soft for the object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (group == NULL)
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
        group->object_owner_soft = strdup (object_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (group);
}


/*!
 * \brief Get the hard pointer to the dictionary owner from a DXF 
 * \c GROUP object.
 *
 * \return hard pointer to the dictionary owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_group_get_dictionary_owner_hard
(
        DxfGroup *group
                /*!< a pointer to a DXF \c GROUP object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (group == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (group->dictionary_owner_hard ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (group->dictionary_owner_hard));
}


/*!
 * \brief Set the pointer to the dictionary_owner_hard for a DXF
 * \c GROUP object.
 */
DxfGroup *
dxf_group_set_dictionary_owner_hard
(
        DxfGroup *group,
                /*!< a pointer to a DXF \c GROUP object. */
        char *dictionary_owner_hard
                /*!< a string containing the pointer to the
                 * dictionary_owner_hard for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (group == NULL)
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
        group->dictionary_owner_hard = strdup (dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (group);
}


/*!
 * \brief Get the unnamed flag value from a DXF \c GROUP object.
 *
 * \return unnamed flag.
 */
int16_t
dxf_group_get_unnamed_flag
(
        DxfGroup *group
                /*!< a pointer to a DXF \c GROUP object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (group == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (group->unnamed_flag < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (group->unnamed_flag > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (group->unnamed_flag);
}


/*!
 * \brief Set the unnamed flag value for a DXF \c GROUP object.
 */
DxfGroup *
dxf_group_set_unnamed_flag
(
        DxfGroup *group,
                /*!< a pointer to a DXF \c GROUP object. */
        int16_t unnamed_flag
                /*!< the unnamed flag value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (group == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (unnamed_flag < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        group->unnamed_flag = unnamed_flag;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (group);
}


/*!
 * \brief Get the selectability flag value from a DXF \c GROUP object.
 *
 * \return selectability flag.
 */
int16_t
dxf_group_get_selectability_flag
(
        DxfGroup *group
                /*!< a pointer to a DXF \c GROUP object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (group == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (group->selectability_flag < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (group->selectability_flag > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (group->selectability_flag);
}


/*!
 * \brief Set the selectability flag value for a DXF \c GROUP object.
 */
DxfGroup *
dxf_group_set_selectability_flag
(
        DxfGroup *group,
                /*!< a pointer to a DXF \c GROUP object. */
        int16_t selectability_flag
                /*!< the selectability flag value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (group == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (selectability_flag < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (selectability_flag > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        group->selectability_flag = selectability_flag;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (group);
}


/*!
 * \brief Get the description from a DXF \c GROUP object.
 *
 * \return description when sucessful, \c NULL when an error occurred.
 */
char *
dxf_group_get_description
(
        DxfGroup *group
                /*!< a pointer to a DXF \c GROUP object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (group == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (group->description ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (group->description));
}


/*!
 * \brief Set the description for a DXF \c GROUP object.
 */
DxfGroup *
dxf_group_set_description
(
        DxfGroup *group,
                /*!< a pointer to a DXF \c GROUP object. */
        char *description
                /*!< a string containing the description for the object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (group == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (description == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        group->description = strdup (description);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (group);
}


/*!
 * \brief Get the handle of entity in group from a DXF \c GROUP object.
 *
 * \return Handle of entity in group when sucessful, \c NULL when an
 * error occurred.
 */
char *
dxf_group_get_handle_entity_in_group
(
        DxfGroup *group
                /*!< a pointer to a DXF \c GROUP object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (group == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (group->handle_entity_in_group ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (group->handle_entity_in_group));
}


/*!
 * \brief Set the handle of entity in group for a DXF \c GROUP object.
 */
DxfGroup *
dxf_group_set_handle_entity_in_group
(
        DxfGroup *group,
                /*!< a pointer to a DXF \c GROUP object. */
        char *handle_entity_in_group
                /*!< a string containing the handle of entity in group
                 * for the object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (group == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (handle_entity_in_group == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        group->handle_entity_in_group = strdup (handle_entity_in_group);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (group);
}


/*!
 * \brief Get the pointer to the next \c GROUP entity from a DXF 
 * \c GROUP object.
 *
 * \return pointer to the next \c GROUP object.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfGroup *
dxf_group_get_next
(
        DxfGroup *group
                /*!< a pointer to a DXF \c GROUP object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (group == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (group->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the next member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfGroup *) group->next);
}


/*!
 * \brief Set the pointer to the next \c GROUP for a DXF \c GROUP
 * object.
 */
DxfGroup *
dxf_group_set_next
(
        DxfGroup *group,
                /*!< a pointer to a DXF \c GROUP object. */
        DxfGroup *next
                /*!< a pointer to the next \c GROUP for the object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (group == NULL)
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
        group->next = (struct DxfGroup *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (group);
}


/*!
 * \brief Get the pointer to the last \c GROUP object from a linked list
 * of DXF \c GROUP objects.
 *
 * \return pointer to the last \c GROUP object.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfGroup *
dxf_group_get_last
(
        DxfGroup *group
                /*!< a pointer to a DXF \c GROUP object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (group == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (group->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfGroup *) group);
        }
        DxfGroup *iter = (DxfGroup *) group->next;
        while (iter->next != NULL)
        {
                iter = (DxfGroup *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfGroup *) iter);
}


/* EOF*/
