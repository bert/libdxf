/*!
 * \file dictionaryvar.c
 *
 * \author Copyright (C) 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF dictionaryvar object (\c DICTIONARYVAR).
 *
 * \version The \c DICTIONARYVAR object was introduced in DXF R14.
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
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
 * \version According to DXF R14.
 */
DxfDictionaryVar *
dxf_dictionary_var_new ()
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfDictionaryVar *dictionary_var = NULL;
        size_t size;

        size = sizeof (DxfDictionaryVar);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dictionary_var = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfDictionaryVar struct.\n")),
                  __FUNCTION__);
                dictionary_var = NULL;
        }
        else
        {
                memset (dictionary_var, 0, size);
        }
#ifdef DEBUG
        DXF_DEBUG_END
#endif
        return (dictionary_var);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c DICTIONARYVAR
 * object.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
 * \version According to DXF R14.
 */
DxfDictionaryVar *
dxf_dictionary_var_init
(
        DxfDictionaryVar *dictionary_var
                /*!< DXF \c DICTIONARYVAR object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dictionary_var == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                dictionary_var = dxf_dictionary_var_new ();
        }
        if (dictionary_var == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfDictionaryVar struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dictionary_var->id_code = 0;
        dictionary_var->value = strdup ("");
        dictionary_var->object_schema_number = strdup ("");
        dictionary_var->dictionary_owner_soft = strdup ("");
        dictionary_var->dictionary_owner_hard = strdup ("");
        dictionary_var->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dictionary_var);
}


/*!
 * \brief Read data from a DXF file into a DXF \c DICTIONARYVAR object.
 *
 * The last line read from file contained the string "DICTIONARYVAR". \n
 * Now follows some data for the \c DICTIONARYVAR object, to be terminated
 * with a "  0" string announcing the following object. \n
 * While parsing the DXF file store data in \c dictionary_var. \n
 *
 * \return \c a pointer to \c dictionary_var.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
 * \version According to DXF R14.
 */
DxfDictionaryVar *
dxf_dictionary_var_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfDictionaryVar *dictionary_var
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
        if (dictionary_var == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                dictionary_var = dxf_dictionary_var_new ();
                dictionary_var = dxf_dictionary_var_init (dictionary_var);
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
                        fscanf (fp->fp, "%s\n", dictionary_var->value);
                }
                if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", &dictionary_var->id_code);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
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
                        fscanf (fp->fp, "%s\n", dictionary_var->object_schema_number);
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing Soft-pointer
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dictionary_var->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dictionary_var->dictionary_owner_hard);
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
        /* Clean up. */
        free (temp_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dictionary_var);
}


/*!
 * \brief Write DXF output to a file for a DXF \c DICTIONARYVAR object.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
 * \version According to DXF R14.
 */
int
dxf_dictionary_var_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfDictionaryVar *dictionary_var
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
        if (dictionary_var == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (strcmp (dictionary_var->value, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty value string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, dictionary_var->id_code);
        }
        if (strcmp (dictionary_var->object_schema_number, "0") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty object schema number string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, dictionary_var->id_code);
        }
        if (fp->acad_version_number < AutoCAD_14)
        {
                fprintf (stderr,
                  (_("Warning in %s () illegal DXF version for this %s entity with id-code: %x.\n")),
                  __FUNCTION__, dxf_entity_name, dictionary_var->id_code);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (dictionary_var->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", dictionary_var->id_code);
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
        if ((strcmp (dictionary_var->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", dictionary_var->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (dictionary_var->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", dictionary_var->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nDictionaryVariables\n");
        }
        fprintf (fp->fp, "280\n%s\n", dictionary_var->object_schema_number);
        fprintf (fp->fp, "  1\n%s\n", dictionary_var->value);
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
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
 * \version According to DXF R14.
 */
int
dxf_dictionary_var_free
(
        DxfDictionaryVar *dictionary_var
                /*!< Pointer to the memory occupied by the DXF
                 * \c DICTIONARYVAR object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dictionary_var->next != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to next DxfDictionaryVar was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (dictionary_var->dictionary_owner_soft);
        free (dictionary_var->dictionary_owner_hard);
        free (dictionary_var->value);
        free (dictionary_var->object_schema_number);
        free (dictionary_var);
        dictionary_var = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/* EOF*/
