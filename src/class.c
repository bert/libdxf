/*!
 * \file class.c
 *
 * \author Copyright (C) 2009, 2010, 2011, 2012, 2014, 2015, 2016, 2017,
 * 2018, 2019, 2021 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \author Copyright (C) 2010 by Luis Matos <gass@otiliamatos.ath.cx>.
 *
 * \brief Functions for a DXF class entity (\c CLASS).
 *
 * \htmlinclude "../doc/class.html"
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


#include "class.h"


/*!
 * \brief Allocate memory for a DXF \c CLASS entity.
 *
 * Fill the memory contents with zeros.
 */
DxfClass *
dxf_class_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfClass *class = NULL;
        size_t size;

        size = sizeof (DxfClass);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((class = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfClass struct.\n")),
                  __FUNCTION__);
                class = NULL;
        }
        else
        {
                memset (class, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (class);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c CLASS
 * entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfClass *
dxf_class_init
(
        DxfClass *class
                /*!< DXF class entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (class == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                class = dxf_class_new ();
        }
        if (class == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory for a DxfClass struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        class->record_type = strdup ("");
        class->record_name = strdup ("");
        class->class_name = strdup ("");
        class->app_name = strdup ("");
        class->proxy_cap_flag = 0;
        class->was_a_proxy_flag = 0;
        class->is_an_entity_flag = 0;
        class->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (class);
}


/*!
 * \brief Read data from a DXF file into a DXF \c CLASS entity.
 *
 * The last line read from file contained the string "CLASS". \n
 * Now follows some data for the \c CLASS, to be terminated with a "  0"
 * string announcing the following entity, or the end of the \c ENTITY
 * section marker \c ENDCLASS. \n
 * While parsing the DXF file store data in \c class. \n
 *
 * \return a pointer to \c class.
 */
DxfClass *
dxf_class_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfClass *class
                /*!< DXF class entity. */
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
        if (class == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                class = dxf_class_init (class);
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
                        /* Clean up. */
                        free (temp_string);
                        return (NULL);
                }
                if (strcmp (temp_string, "0") == 0)
                {
                        /* Now follows a string containing a record type
                         * number. */
                        /*! \bug \c record_type has group code 0 which
                         * will cause a parsing error and \c record_type
                         * and other \c class variables  will not be
                         * read. See the while condition above.
                         */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, class->record_type);
                }
                else if (strcmp (temp_string, "1") == 0)
                {
                        /* Now follows a string containing a record
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, class->record_name);
                }
                else if (strcmp (temp_string, "2") == 0)
                {
                        /* Now follows a string containing a class name.
                         */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, class->class_name);
                }
                else if (strcmp (temp_string, "3") == 0)
                {
                        /* Now follows a string containing the
                         * application name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, class->app_name);
                }
                else if (strcmp (temp_string, "90") == 0)
                {
                        /* Now follows a string containing the
                         * proxy cap flag value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%" PRIi32 "\n", &class->proxy_cap_flag);
                }
                else if (strcmp (temp_string, "280") == 0)
                {
                        /* Now follows a string containing the
                         * was a proxy flag value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &class->was_a_proxy_flag);
                }
                else if (strcmp (temp_string, "281") == 0)
                {
                        /* Now follows a string containing the
                         * is an entity flag value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &class->is_an_entity_flag);
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
        /* Handle omitted members and/or illegal values. */
        if (strcmp (class->record_type, "") == 0)
        {
                fprintf (stderr,
                  (_("Error in %s () empty record type string after reading from: %s before line: %d.\n")),
                  __FUNCTION__, fp->filename, fp->line_number);
                return (NULL);

        }
        if (strcmp (class->record_name, "") == 0)
        {
                fprintf (stderr,
                  (_("Error in %s () empty record name string after reading from: %s before line: %d.\n")),
                  __FUNCTION__, fp->filename, fp->line_number);
                return (NULL);
        }
        if (strcmp (class->class_name, "") == 0)
        {
                fprintf (stderr,
                  (_("Error in %s () empty class name string after reading from: %s before line: %d.\n")),
                  __FUNCTION__, fp->filename, fp->line_number);
                return (NULL);
        }
        /* Clean up. */
        free (temp_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (class);
}


/*!
 * \brief Write DXF output to a file for a DXF \c CLASS entity.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_class_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfClass *class
                /*!< DXF class section. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("CLASS");

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
        if (class == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if ((!class->record_type)
                || (strcmp (class->record_type, "") == 0))
        {
                fprintf (stderr,
                  (_("Error in %s () empty record type string for the %s entity\n")),
                  __FUNCTION__, dxf_entity_name);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if ((!class->class_name)
                || (strcmp (class->class_name, "") == 0))
        {
                fprintf (stderr,
                  (_("Error in %s () empty class name string for the %s entity\n")),
                  __FUNCTION__, dxf_entity_name);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (!class->record_name)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty record name string for the %s entity\n")),
                  __FUNCTION__, dxf_entity_name);
                fprintf (stderr,
                  (_("\trecord_name of %s entity is reset to \"\"")),
                  dxf_entity_name );
                class->record_name = strdup ("");
        }
        if (!class->app_name)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty app name string for the %s entity\n")),
                  __FUNCTION__, dxf_entity_name);
                fprintf (stderr,
                  (_("\tapp_name of %s entity is reset to \"\"")),
                  dxf_entity_name );
                class->app_name = strdup ("");
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        fprintf (fp->fp, "  1\n%s\n", class->record_name);
        fprintf (fp->fp, "  2\n%s\n", class->class_name);
        if (fp->acad_version_number >= AutoCAD_14)
        {
                fprintf (fp->fp, "  3\n%s\n", class->app_name);
        }
        fprintf (fp->fp, " 90\n%" PRIi32 "\n", class->proxy_cap_flag);
        fprintf (fp->fp, "280\n%hd\n", class->was_a_proxy_flag);
        fprintf (fp->fp, "281\n%hd\n", class->is_an_entity_flag);
        /* Clean up. */
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write DXF output to a file for an end of \c CLASSES section
 * marker.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_class_write_endclass
(
        DxfFile *fp
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (fp == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL file pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\nENDSEC\n");
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c CLASS and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_class_free
(
        DxfClass *class
                /*!< Pointer to the memory occupied by the DXF \c CLASS
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (class == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (class->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (class->record_type);
        free (class->record_name);
        free (class->class_name);
        free (class->app_name);
        free (class);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c CLASS classes and all their data fields.
 */
void
dxf_class_free_list
(
        DxfClass *classes
                /*!< pointer to the single linked list of DXF \c CLASS
                 * classes. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (classes == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (classes != NULL)
        {
                DxfClass *iter = (DxfClass *) classes->next;
                dxf_class_free (classes);
                classes = (DxfClass *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the record type from a DXF \c CLASS entity.
 *
 * \return record type when sucessful, \c NULL when an error occurred.
 */
char *
dxf_class_get_record_type
(
        DxfClass *class
                /*!< a pointer to a DXF \c CLASS entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *result = NULL;

        /* Do some basic checks. */
        if (class == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (class->record_type ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the record type member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = strdup (class->record_type);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the record type for a DXF \c CLASS entity.
 */
DxfClass *
dxf_class_set_record_type
(
        DxfClass *class,
                /*!< a pointer to a DXF \c CLASS entity. */
        char *record_type
                /*!< a string containing the record type for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (class == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (record_type == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        class->record_type = strdup (record_type);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (class);
}


/*!
 * \brief Get the record name from a DXF \c CLASS entity.
 *
 * \return record name when sucessful, \c NULL when an error occurred.
 */
char *
dxf_class_get_record_name
(
        DxfClass *class
                /*!< a pointer to a DXF \c CLASS entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *result = NULL;

        /* Do some basic checks. */
        if (class == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (class->record_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the record name member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = strdup (class->record_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the record name for a DXF \c CLASS entity.
 */
DxfClass *
dxf_class_set_record_name
(
        DxfClass *class,
                /*!< a pointer to a DXF \c CLASS entity. */
        char *record_name
                /*!< a string containing the record name for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (class == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (record_name == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        class->record_name = strdup (record_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (class);
}


/*!
 * \brief Get the class name from a DXF \c CLASS entity.
 *
 * \return class name when sucessful, \c NULL when an error occurred.
 */
char *
dxf_class_get_class_name
(
        DxfClass *class
                /*!< a pointer to a DXF \c CLASS entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *result = NULL;

        /* Do some basic checks. */
        if (class == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (class->class_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the class name member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = strdup (class->class_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the class name for a DXF \c CLASS entity.
 */
DxfClass *
dxf_class_set_class_name
(
        DxfClass *class,
                /*!< a pointer to a DXF \c CLASS entity. */
        char *class_name
                /*!< a string containing the class name for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (class == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (class_name == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        class->class_name = strdup (class_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (class);
}


/*!
 * \brief Get the application name from a DXF \c CLASS entity.
 *
 * \return class name when sucessful, \c NULL when an error occurred.
 */
char *
dxf_class_get_app_name
(
        DxfClass *class
                /*!< a pointer to a DXF \c CLASS entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *result = NULL;

        /* Do some basic checks. */
        if (class == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (class->app_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the class name member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = strdup (class->app_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the application name for a DXF \c CLASS entity.
 */
DxfClass *
dxf_class_set_app_name
(
        DxfClass *class,
                /*!< a pointer to a DXF \c CLASS entity. */
        char *app_name
                /*!< a string containing the application name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (class == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (app_name == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        class->app_name = strdup (app_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (class);
}


/*!
 * \brief Get the proxy_cap_flag from a DXF \c CLASS entity.
 *
 * \return proxy_cap_flag.
 */
int32_t
dxf_class_get_proxy_cap_flag
(
        DxfClass *class
                /*!< a pointer to a DXF \c CLASS entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result;

        /* Do some basic checks. */
        if (class == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (class->proxy_cap_flag < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the proxy_cap_flag member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = class->proxy_cap_flag;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the proxy_cap_flag for a DXF \c CLASS entity.
 */
DxfClass *
dxf_class_set_proxy_cap_flag
(
        DxfClass *class,
                /*!< a pointer to a DXF \c CLASS entity. */
        int32_t proxy_cap_flag
                /*!< Proxy capabilities flag. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (class == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (proxy_cap_flag < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative proxy_cap_flag value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        class->proxy_cap_flag = proxy_cap_flag;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (class);
}


/*!
 * \brief Test if operations on this \c CLASS symbol table entry are
 * allowed.
 *
 * \return \c TRUE when operations on this \c CLASS symbol table entry
 * are allowed, or \c FALSE when operations on this \c CLASS symbol
 * table entry are not allowed.
 */
int
dxf_class_is_editable
(
        DxfClass *class
                /*!< DXF \c CLASS symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result = FALSE;

        /* Do some basic checks. */
        if (class == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        /* The result is TRUE if the bit test returns FALSE (0).*/
        result = !DXF_CHECK_BIT (class->proxy_cap_flag, 0);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Test if erasing on this \c CLASS symbol table entry is allowed.
 *
 * \return \c TRUE when erasing on this \c CLASS symbol table entry is
 * allowed, or \c FALSE when erasing on this \c CLASS symbol table entry
 * is not allowed.
 */
int
dxf_class_erase_allowed
(
        DxfClass *class
                /*!< DXF \c CLASS symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result = FALSE;

        /* Do some basic checks. */
        if (class == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = DXF_CHECK_BIT (class->proxy_cap_flag, 0);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Test if transforming on this \c CLASS symbol table entry is
 * allowed.
 *
 * \return \c TRUE when transforming on this \c CLASS symbol table entry
 * is allowed, or \c FALSE when transforming on this \c CLASS symbol
 * table entry is not allowed.
 */
int
dxf_class_transform_allowed
(
        DxfClass *class
                /*!< DXF \c CLASS symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result = FALSE;

        /* Do some basic checks. */
        if (class == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = DXF_CHECK_BIT (class->proxy_cap_flag, 1);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Test if changing the color in this \c CLASS symbol table entry
 * is allowed.
 *
 * \return \c TRUE when changing the color in this \c CLASS symbol table
 * entry is allowed, or \c FALSE when changing the color in this
 * \c CLASS symbol table entry is not allowed.
 */
int
dxf_class_color_change_allowed
(
        DxfClass *class
                /*!< DXF \c CLASS symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result = FALSE;

        /* Do some basic checks. */
        if (class == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = DXF_CHECK_BIT (class->proxy_cap_flag, 2);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Test if changing the layer in this \c CLASS symbol table entry
 * is allowed.
 *
 * \return \c TRUE when changing the layer in this \c CLASS symbol table
 * entry is allowed, or \c FALSE when changing the layer in this
 * \c CLASS symbol table entry is not allowed.
 */
int
dxf_class_layer_change_allowed
(
        DxfClass *class
                /*!< DXF \c CLASS symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result = FALSE;

        /* Do some basic checks. */
        if (class == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = DXF_CHECK_BIT (class->proxy_cap_flag, 3);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Test if changing the linetype in this \c CLASS symbol table entry
 * is allowed.
 *
 * \return \c TRUE when changing the linetype in this \c CLASS symbol table
 * entry is allowed, or \c FALSE when changing the linetype in this
 * \c CLASS symbol table entry is not allowed.
 */
int
dxf_class_linetype_change_allowed
(
        DxfClass *class
                /*!< DXF \c CLASS symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result = FALSE;

        /* Do some basic checks. */
        if (class == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = DXF_CHECK_BIT (class->proxy_cap_flag, 4);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Test if changing the linetype scale in this \c CLASS symbol
 * table entry is allowed.
 *
 * \return \c TRUE when changing the linetype scale in this \c CLASS
 * symbol table entry is allowed, or \c FALSE when changing the linetype
 * scale in this \c CLASS symbol table entry is not allowed.
 */
int
dxf_class_linetype_scale_change_allowed
(
        DxfClass *class
                /*!< DXF \c CLASS symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result = FALSE;

        /* Do some basic checks. */
        if (class == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = DXF_CHECK_BIT (class->proxy_cap_flag, 5);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Test if changing the visibility in this \c CLASS symbol table
 * entry is allowed.
 *
 * \return \c TRUE when changing the visibility in this \c CLASS symbol
 * table entry is allowed, or \c FALSE when changing the visibility in
 * this \c CLASS symbol table entry is not allowed.
 */
int
dxf_class_visibility_change_allowed
(
        DxfClass *class
                /*!< DXF \c CLASS symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result = FALSE;

        /* Do some basic checks. */
        if (class == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = DXF_CHECK_BIT (class->proxy_cap_flag, 6);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Test if cloning of this \c CLASS symbol table entry is allowed.
 *
 * \return \c TRUE when cloning of this \c CLASS symbol table entry is
 * allowed, or \c FALSE when cloning of this \c CLASS symbol table entry
 * is not allowed.
 */
int
dxf_class_cloning_allowed
(
        DxfClass *class
                /*!< DXF \c CLASS symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result = FALSE;

        /* Do some basic checks. */
        if (class == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = DXF_CHECK_BIT (class->proxy_cap_flag, 7);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Test if changing the line weight in this \c CLASS symbol table
 * entry is allowed.
 *
 * \return \c TRUE when changing the line weight in this \c CLASS symbol
 * table entry is allowed, or \c FALSE when changing the line weight in
 * this \c CLASS symbol table entry is not allowed.
 */
int
dxf_class_lineweight_change_allowed
(
        DxfClass *class
                /*!< DXF \c CLASS symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result = FALSE;

        /* Do some basic checks. */
        if (class == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = DXF_CHECK_BIT (class->proxy_cap_flag, 8);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Test if changing the plot style name in this \c CLASS symbol table
 * entry is allowed.
 *
 * \return \c TRUE when changing the plot style name in this \c CLASS
 * symbol table entry is allowed, or \c FALSE when changing the plot
 * style name in this \c CLASS symbol table entry is not allowed.
 */
int
dxf_class_plot_style_name_change_allowed
(
        DxfClass *class
                /*!< DXF \c CLASS symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result = FALSE;

        /* Do some basic checks. */
        if (class == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = DXF_CHECK_BIT (class->proxy_cap_flag, 9);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Test if changing the plot style name in this \c CLASS symbol table
 * entry is allowed.
 *
 * \return \c TRUE when this \c CLASS symbol table entry is a R13 format
 * proxy, or \c FALSE when this \c CLASS symbol table entry is not a R13
 * format proxy.
 */
int
dxf_class_is_R13_format_proxy
(
        DxfClass *class
                /*!< DXF \c CLASS symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result = FALSE;

        /* Do some basic checks. */
        if (class == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = DXF_CHECK_BIT (class->proxy_cap_flag, 15);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Get the was_a_proxy_flag from a DXF \c CLASS entity.
 *
 * \return was_a_proxy_flag.
 */
int16_t
dxf_class_get_was_a_proxy_flag
(
        DxfClass *class
                /*!< a pointer to a DXF \c CLASS entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result;

        /* Do some basic checks. */
        if (class == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (class->was_a_proxy_flag < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the was_a_proxy_flag member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (class->was_a_proxy_flag > 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an invalid value was found in the was_a_proxy_flag member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = class->was_a_proxy_flag;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the was_a_proxy_flag for a DXF \c CLASS entity.
 */
DxfClass *
dxf_class_set_was_a_proxy_flag
(
        DxfClass *class,
                /*!< a pointer to a DXF \c CLASS entity. */
        int16_t was_a_proxy_flag
                /*!< Was-a-proxy flag. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (class == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (was_a_proxy_flag < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative was_a_proxy_flag value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (was_a_proxy_flag > 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an invalid was_a_proxy_flag value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        class->was_a_proxy_flag = was_a_proxy_flag;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (class);
}


/*!
 * \brief Get the is_an_entity_flag value from a DXF \c CLASS entity.
 *
 * \return is_an_entity_flag value.
 */
int16_t
dxf_class_get_is_an_entity_flag
(
        DxfClass *class
                /*!< a pointer to a DXF \c CLASS entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result;

        /* Do some basic checks. */
        if (class == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (class->is_an_entity_flag < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the is_an_entity_flag member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (class->is_an_entity_flag > 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an invalid value was found in the is_an_entity_flag member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = class->is_an_entity_flag;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the is_an_entity_flag for a DXF \c CLASS entity.
 */
DxfClass *
dxf_class_set_is_an_entity_flag
(
        DxfClass *class,
                /*!< a pointer to a DXF \c CLASS entity. */
        int16_t is_an_entity_flag
                /*!< Is-an-entity flag. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (class == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (is_an_entity_flag < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative is_an_entity_flag value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (is_an_entity_flag > 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an invalid is_an_entity_flag value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        class->is_an_entity_flag = is_an_entity_flag;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (class);
}


/*!
 * \brief Get the pointer to the next \c CLASS entity from a DXF 
 * \c CLASS entity.
 *
 * \return pointer to the next \c CLASS entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfClass *
dxf_class_get_next
(
        DxfClass *class
                /*!< a pointer to a DXF \c CLASS entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfClass *result;

        /* Do some basic checks. */
        if (class == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (class->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the next member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = (DxfClass *) class->next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the pointer to the next \c CLASS for a DXF \c CLASS
 * entity.
 */
DxfClass *
dxf_class_set_next
(
        DxfClass *class,
                /*!< a pointer to a DXF \c CLASS entity. */
        DxfClass *next
                /*!< a pointer to the next \c CLASS for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (class == NULL)
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
        class->next = (struct DxfClass *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (class);
}


/*!
 * \brief Get the pointer to the last \c CLASS from a linked list of
 * DXF \c CLASS.
 *
 * \return pointer to the last \c CLASS.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfClass *
dxf_class_get_last
(
        DxfClass *class
                /*!< a pointer to a DXF \c CLASS. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (class == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (class->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found in the next member.\n")),
                  __FUNCTION__);
                return ((DxfClass *) class);
        }
        DxfClass *iter = (DxfClass *) class->next;
        while (iter->next != NULL)
        {
                iter = (DxfClass *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfClass *) iter);
}


/* EOF */
