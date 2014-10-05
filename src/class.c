/*!
 * \file class.c
 *
 * \author Copyright (C) 2009 ... 2014 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF class entity (\c CLASS).
 *
 * \htmlinclude "../doc/class.html"
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
        DxfClass *dxf_class = NULL;
        size_t size;

        size = sizeof (DxfClass);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_class = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("ERROR in %s () could not allocate memory for a DxfClass struct.\n")),
                  __FUNCTION__);
                dxf_class = NULL;
        }
        else
        {
                memset (dxf_class, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_class);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c CLASS
 * entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfClass *
dxf_class_init
(
        DxfClass *dxf_class
                /*!< DXF class entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dxf_class == NULL)
        {
                fprintf (stderr,
                  (_("WARNING in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                dxf_class = dxf_class_new ();
        }
        if (dxf_class == NULL)
        {
              fprintf (stderr,
                (_("ERROR in %s () could not allocate memory for a DxfClass struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        dxf_class->record_type = strdup ("");
        dxf_class->record_name = strdup ("");
        dxf_class->class_name = strdup ("");
        dxf_class->app_name = strdup ("");
        dxf_class->proxy_cap_flag = 0;
        dxf_class->was_a_proxy_flag = 0;
        dxf_class->is_an_entity_flag = 0;
        dxf_class->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_class);
}


/*!
 * \brief Read data from a DXF file into a DXF \c CLASS entity.
 *
 * The last line read from file contained the string "CLASS". \n
 * Now follows some data for the \c CLASS, to be terminated with a "  0"
 * string announcing the following entity, or the end of the \c ENTITY
 * section marker \c ENDCLASS. \n
 * While parsing the DXF file store data in \c dxf_class. \n
 *
 * \return a pointer to \c dxf_class.
 */
DxfClass *
dxf_class_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfClass *dxf_class
                /*!< DXF class entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *temp_string = NULL;

        /* Do some basic checks. */
        if (dxf_class == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                dxf_class = dxf_class_new ();
                dxf_class_init (dxf_class);
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
                        fscanf (fp->fp, "%s\n", dxf_class->record_type);
                }
                else if (strcmp (temp_string, "1") == 0)
                {
                        /* Now follows a string containing a record
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_class->record_name);
                }
                else if (strcmp (temp_string, "2") == 0)
                {
                        /* Now follows a string containing a class name.
                         */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_class->class_name);
                }
                else if (strcmp (temp_string, "3") == 0)
                {
                        /* Now follows a string containing the
                         * application name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_class->app_name);
                }
                else if (strcmp (temp_string, "90") == 0)
                {
                        /* Now follows a string containing the
                         * proxy cap flag value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_class->proxy_cap_flag);
                }
                else if (strcmp (temp_string, "280") == 0)
                {
                        /* Now follows a string containing the
                         * was a proxy flag value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_class->was_a_proxy_flag);
                }
                else if (strcmp (temp_string, "281") == 0)
                {
                        /* Now follows a string containing the
                         * is an entity flag value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_class->is_an_entity_flag);
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
        /* Handle omitted members and/or illegal values. */
        if (strcmp (dxf_class->record_type, "") == 0)
        {
                fprintf (stderr,
                  (_("Error in %s () empty record type string after reading from: %s before line: %d.\n")),
                  __FUNCTION__, fp->filename, fp->line_number);
                return (NULL);

        }
        if (strcmp (dxf_class->record_name, "") == 0)
        {
                fprintf (stderr,
                  (_("Error in %s () empty record name string after reading from: %s before line: %d.\n")),
                  __FUNCTION__, fp->filename, fp->line_number);
                return (NULL);
        }
        if (strcmp (dxf_class->class_name, "") == 0)
        {
                fprintf (stderr,
                  (_("Error in %s () empty class name string after reading from: %s before line: %d.\n")),
                  __FUNCTION__, fp->filename, fp->line_number);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_class);
}


/*!
 * \brief Write DXF output to a file for a DXF \c CLASS entity.
 */
int
dxf_class_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfClass *dxf_class
                /*!< DXF class section. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("CLASS");

        /* Do some basic checks. */
        if (dxf_class == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (!dxf_class->record_type
                || (strcmp (dxf_class->record_type, "") == 0))
        {
                fprintf (stderr,
                  (_("Error in %s () empty record type string for the %s entity\n")),
                  __FUNCTION__, dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (!dxf_class->record_name)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty record name string for the %s entity\n")),
                  __FUNCTION__, dxf_entity_name);
                fprintf (stderr,
                  (_("    record_name of %s entity is reset to \"\"")),
                  dxf_entity_name );
                dxf_class->record_name = strdup ("");
        }
        if (!dxf_class->class_name
                || (strcmp (dxf_class->class_name, "") == 0))
        {
                fprintf (stderr,
                  (_("Error in %s () empty class name string for the %s entity\n")),
                  __FUNCTION__, dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (!dxf_class->app_name)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty app name string for the %s entity\n")),
                  __FUNCTION__, dxf_entity_name);
                fprintf (stderr,
                  (_("    app_name of %s entity is reset to \"\"")),
                  dxf_entity_name );
                dxf_class->app_name = strdup ("");
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        fprintf (fp->fp, "  1\n%s\n", dxf_class->record_name);
        fprintf (fp->fp, "  2\n%s\n", dxf_class->class_name);
        if (fp->acad_version_number >= AutoCAD_14)
        {
                fprintf (fp->fp, "  3\n%s\n", dxf_class->app_name);
        }
        fprintf (fp->fp, " 90\n%d\n", dxf_class->proxy_cap_flag);
        fprintf (fp->fp, "280\n%d\n", dxf_class->was_a_proxy_flag);
        fprintf (fp->fp, "281\n%d\n", dxf_class->is_an_entity_flag);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write DXF output to a file for an end of \c CLASSES section
 * marker.
 */
int
dxf_class_write_endclass
(
        FILE *fp
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        fprintf (fp, "  0\nENDSEC\n");
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c CLASS and all it's
 * data fields.
 */
int
dxf_class_free
(
        DxfClass *dxf_class
                /*!< Pointer to the memory occupied by the DXF \c CLASS
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (dxf_class->next != NULL)
        {
              fprintf (stderr,
                (_("ERROR in %s () pointer to next DxfClass was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (dxf_class->record_type);
        free (dxf_class->record_name);
        free (dxf_class->class_name);
        free (dxf_class->app_name);
        free (dxf_class);
        dxf_class = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
