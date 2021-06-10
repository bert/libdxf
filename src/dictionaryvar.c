/*!
 * \file dictionaryvar.c
 *
 * \author Copyright (C) 2015, 2016, 2017, 2018, 2019, 2020, 2021
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF dictionaryvar object (\c DICTIONARYVAR).
 *
 * \since The \c DICTIONARYVAR object was introduced in DXF R14.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
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


#include "dictionaryvar.h"


/*!
 * \brief Allocate memory for a DXF \c DICTIONARYVAR object.
 *
 * Fill the memory contents with zeros.
 */
DxfDictionaryVar *
dxf_dictionaryvar_new ()
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfDictionaryVar *dictionaryvar = NULL;
        size_t size;

        size = sizeof (DxfDictionaryVar);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dictionaryvar = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                dictionaryvar = NULL;
        }
        else
        {
                memset (dictionaryvar, 0, size);
        }
#ifdef DEBUG
        DXF_DEBUG_END
#endif
        return (dictionaryvar);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c DICTIONARYVAR
 * object.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfDictionaryVar *
dxf_dictionaryvar_init
(
        DxfDictionaryVar *dictionaryvar
                /*!< DXF \c DICTIONARYVAR object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dictionaryvar == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                dictionaryvar = dxf_dictionaryvar_new ();
        }
        if (dictionaryvar == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dxf_dictionaryvar_set_id_code (dictionaryvar, 0);
        dxf_dictionaryvar_set_value (dictionaryvar, strdup (""));
        dxf_dictionaryvar_set_object_schema_number (dictionaryvar, strdup (""));
        dxf_dictionaryvar_set_dictionary_owner_soft (dictionaryvar, strdup (""));
        dxf_dictionaryvar_set_dictionary_owner_hard (dictionaryvar, strdup (""));
        dxf_dictionaryvar_set_next (dictionaryvar, NULL);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dictionaryvar);
}


/*!
 * \brief Read data from a DXF file into a DXF \c DICTIONARYVAR object.
 *
 * The last line read from file contained the string "DICTIONARYVAR". \n
 * Now follows some data for the \c DICTIONARYVAR object, to be terminated
 * with a "  0" string announcing the following object. \n
 * While parsing the DXF file store data in \c dictionaryvar. \n
 *
 * \return \c a pointer to \c dictionaryvar.
 */
DxfDictionaryVar *
dxf_dictionaryvar_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfDictionaryVar *dictionaryvar
                /*!< DXF \c DICTIONARYVAR object. */
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
        if (fp->acad_version_number < AutoCAD_14)
        {
                fprintf (stderr,
                  (_("Warning in %s () illegal DXF version for this entity.\n")),
                  __FUNCTION__);
        }
        if (dictionaryvar == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                dictionaryvar = dxf_dictionaryvar_init (dictionaryvar);
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
                else if (strcmp (temp_string, "1") == 0)
                {
                        /* Now follows a string containing additional
                         * proprietary data. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, dictionaryvar->value);
                }
                if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", (uint *) &dictionaryvar->id_code);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if (strcmp (temp_string, "DictionaryVariables") != 0)
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () found a bad subclass marker in: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                        }
                }
                else if (strcmp (temp_string, "280") == 0)
                {
                        /* Now follows a string containing a handle to ae
                         * entry object. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, dictionaryvar->object_schema_number);
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing Soft-pointer
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, dictionaryvar->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, dictionaryvar->dictionary_owner_hard);
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
        return (dictionaryvar);
}


/*!
 * \brief Write DXF output to a file for a DXF \c DICTIONARYVAR object.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_dictionaryvar_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfDictionaryVar *dictionaryvar
                /*!< DXF \c DICTIONARYVAR object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("DICTIONARYVAR");

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
        if (dictionaryvar == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (strcmp (dxf_dictionaryvar_get_value (dictionaryvar), "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty value string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, dxf_dictionaryvar_get_id_code (dictionaryvar));
        }
        if (strcmp (dxf_dictionaryvar_get_object_schema_number (dictionaryvar), "0") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty object schema number string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, dxf_dictionaryvar_get_id_code (dictionaryvar));
        }
        if (fp->acad_version_number < AutoCAD_14)
        {
                fprintf (stderr,
                  (_("Warning in %s () illegal DXF version for this %s entity with id-code: %x.\n")),
                  __FUNCTION__, dxf_entity_name, dxf_dictionaryvar_get_id_code (dictionaryvar));
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (dxf_dictionaryvar_get_id_code (dictionaryvar) != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", dxf_dictionaryvar_get_id_code (dictionaryvar));
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
        if ((strcmp (dxf_dictionaryvar_get_dictionary_owner_soft (dictionaryvar), "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", dxf_dictionaryvar_get_dictionary_owner_soft (dictionaryvar));
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (dxf_dictionaryvar_get_dictionary_owner_hard (dictionaryvar), "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", dxf_dictionaryvar_get_dictionary_owner_hard (dictionaryvar));
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nDictionaryVariables\n");
        }
        fprintf (fp->fp, "280\n%s\n", dxf_dictionaryvar_get_object_schema_number (dictionaryvar));
        fprintf (fp->fp, "  1\n%s\n", dxf_dictionaryvar_get_value (dictionaryvar));
        /* Clean up. */
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c DICTIONARYVAR and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_dictionaryvar_free
(
        DxfDictionaryVar *dictionaryvar
                /*!< Pointer to the memory occupied by the DXF
                 * \c DICTIONARYVAR object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dictionaryvar == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dxf_dictionaryvar_get_next (dictionaryvar) != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (dxf_dictionaryvar_get_dictionary_owner_soft (dictionaryvar));
        free (dxf_dictionaryvar_get_dictionary_owner_hard (dictionaryvar));
        free (dxf_dictionaryvar_get_value (dictionaryvar));
        free (dxf_dictionaryvar_get_object_schema_number (dictionaryvar));
        free (dictionaryvar);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c DICTIONARYVAR objects and all their data fields.
 */
void
dxf_dictionaryvar_free_list
(
        DxfDictionaryVar *dictionaryvars
                /*!< pointer to the single linked list of DXF
                 * \c DICTIONARYVAR objects. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (dictionaryvars == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (dictionaryvars != NULL)
        {
                DxfDictionaryVar *iter = (DxfDictionaryVar *) dictionaryvars->next;
                dxf_dictionaryvar_free (dictionaryvars);
                dictionaryvars = (DxfDictionaryVar *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the ID code from a DXF \c DICTIONARYVAR object.
 *
 * \return ID code.
 */
int
dxf_dictionaryvar_get_id_code
(
        DxfDictionaryVar *dictionaryvar
                /*!< a pointer to a DXF \c DICTIONARYVAR object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dictionaryvar == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dictionaryvar->id_code < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dictionaryvar->id_code);
}


/*!
 * \brief Set the ID code for a DXF \c DICTIONARYVAR object.
 */
DxfDictionaryVar *
dxf_dictionaryvar_set_id_code
(
        DxfDictionaryVar *dictionaryvar,
                /*!< a pointer to a DXF \c DICTIONARYVAR object. */
        int id_code
                /*!< Identification number for the object.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dictionaryvar == NULL)
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
        dictionaryvar->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dictionaryvar);
}


/*!
 * \brief Get the soft pointer to the dictionary owner from a DXF 
 * \c DICTIONARYVAR object.
 *
 * \return soft pointer to the dictionary owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_dictionaryvar_get_dictionary_owner_soft
(
        DxfDictionaryVar *dictionaryvar
                /*!< a pointer to a DXF \c DICTIONARYVAR object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dictionaryvar == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dictionaryvar->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (dictionaryvar->dictionary_owner_soft));
}


/*!
 * \brief Set the pointer to the dictionary_owner_soft for a DXF
 * \c DICTIONARYVAR object.
 */
DxfDictionaryVar *
dxf_dictionaryvar_set_dictionary_owner_soft
(
        DxfDictionaryVar *dictionaryvar,
                /*!< a pointer to a DXF \c DICTIONARYVAR object. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the
                 * dictionary_owner_soft for the object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dictionaryvar == NULL)
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
        dictionaryvar->dictionary_owner_soft = strdup (dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dictionaryvar);
}


/*!
 * \brief Get the hard pointer to the dictionary owner from a DXF 
 * \c DICTIONARYVAR object.
 *
 * \return hard pointer to the dictionary owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_dictionaryvar_get_dictionary_owner_hard
(
        DxfDictionaryVar *dictionaryvar
                /*!< a pointer to a DXF \c DICTIONARYVAR object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dictionaryvar == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dictionaryvar->dictionary_owner_hard ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (dictionaryvar->dictionary_owner_hard));
}


/*!
 * \brief Set the pointer to the dictionary_owner_hard for a DXF
 * \c DICTIONARYVAR object.
 */
DxfDictionaryVar *
dxf_dictionaryvar_set_dictionary_owner_hard
(
        DxfDictionaryVar *dictionaryvar,
                /*!< a pointer to a DXF \c DICTIONARYVAR object. */
        char *dictionary_owner_hard
                /*!< a string containing the pointer to the
                 * dictionary_owner_hard for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dictionaryvar == NULL)
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
        dictionaryvar->dictionary_owner_hard = strdup (dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dictionaryvar);
}


/*!
 * \brief Get the value from a DXF \c DICTIONARYVAR object.
 *
 * \return value when sucessful, \c NULL when an error occurred.
 */
char *
dxf_dictionaryvar_get_value
(
        DxfDictionaryVar *dictionaryvar
                /*!< a pointer to a DXF \c DICTIONARYVAR object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dictionaryvar == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dictionaryvar->value ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (dictionaryvar->value));
}


/*!
 * \brief Set the entry name for a DXF \c DICTIONARYVAR object.
 */
DxfDictionaryVar *
dxf_dictionaryvar_set_value
(
        DxfDictionaryVar *dictionaryvar,
                /*!< a pointer to a DXF \c DICTIONARYVAR object. */
        char *value
                /*!< a string containing the value for the object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dictionaryvar == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (value == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dictionaryvar->value = strdup (value);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dictionaryvar);
}


/*!
 * \brief Get the object schema number from a DXF \c DICTIONARYVAR
 * object.
 *
 * \return object schema number when sucessful, \c NULL when an error
 * occurred.
 */
char *
dxf_dictionaryvar_get_object_schema_number
(
        DxfDictionaryVar *dictionaryvar
                /*!< a pointer to a DXF \c DICTIONARYVAR object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dictionaryvar == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dictionaryvar->object_schema_number ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (dictionaryvar->object_schema_number));
}


/*!
 * \brief Set the object schema number for a DXF \c DICTIONARYVAR object.
 */
DxfDictionaryVar *
dxf_dictionaryvar_set_object_schema_number
(
        DxfDictionaryVar *dictionaryvar,
                /*!< a pointer to a DXF \c DICTIONARYVAR object. */
        char *object_schema_number
                /*!< a string containing the object schema number for
                 * the object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dictionaryvar == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (object_schema_number == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dictionaryvar->object_schema_number = strdup (object_schema_number);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dictionaryvar);
}


/*!
 * \brief Get the pointer to the next \c DICTIONARYVAR object from a DXF 
 * \c DICTIONARYVAR object.
 *
 * \return pointer to the next \c DICTIONARYVAR object.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfDictionaryVar *
dxf_dictionaryvar_get_next
(
        DxfDictionaryVar *dictionaryvar
                /*!< a pointer to a DXF \c DICTIONARYVAR object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dictionaryvar == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dictionaryvar->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfDictionaryVar *) dictionaryvar->next);
}


/*!
 * \brief Set the pointer to the next \c DICTIONARYVAR object for a DXF
 * \c DICTIONARYVAR object.
 */
DxfDictionaryVar *
dxf_dictionaryvar_set_next
(
        DxfDictionaryVar *dictionaryvar,
                /*!< a pointer to a DXF \c DICTIONARYVAR object. */
        DxfDictionaryVar *next
                /*!< a pointer to the next \c DICTIONARYVAR object for the
                 * object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dictionaryvar == NULL)
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
        dictionaryvar->next = (struct DxfDictionaryVar *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dictionaryvar);
}


/*!
 * \brief Get the pointer to the last \c DICTIONARYVAR object from a
 * linked list of DXF \c DICTIONARYVAR objects.
 *
 * \return pointer to the last \c DICTIONARYVAR object.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfDictionaryVar *
dxf_dictionaryvar_get_last
(
        DxfDictionaryVar *dictionaryvar
                /*!< a pointer to a DXF \c DICTIONARYVAR object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dictionaryvar == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dictionaryvar->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfDictionaryVar *) dictionaryvar);
        }
        DxfDictionaryVar *iter = (DxfDictionaryVar *) dictionaryvar->next;
        while (iter->next != NULL)
        {
                iter = (DxfDictionaryVar *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfDictionaryVar *) iter);
}


/* EOF*/
