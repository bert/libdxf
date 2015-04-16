/*!
 * \file dictionary.c
 *
 * \author Copyright (C) 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF dictionary object (\c DICTIONAY).
 *
 * \version The \c DICTIONARY object was introduced in DXF R13.
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


#include "dictionary.h"


/*!
 * \brief Allocate memory for a DXF \c DICTIONARY object.
 *
 * Fill the memory contents with zeros.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfDictionary *
dxf_dictionary_new ()
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfDictionary *dictionary = NULL;
        size_t size;

        size = sizeof (DxfDictionary);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dictionary = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfDictionary struct.\n")),
                  __FUNCTION__);
                dictionary = NULL;
        }
        else
        {
                memset (dictionary, 0, size);
        }
#ifdef DEBUG
        DXF_DEBUG_END
#endif
        return (dictionary);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c DICTIONARY
 * object.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfDictionary *
dxf_dictionary_init
(
        DxfDictionary *dictionary
                /*!< DXF \c DICTIONARY object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dictionary == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                dictionary = dxf_dictionary_new ();
        }
        if (dictionary == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfDictionary struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dictionary->id_code = 0;
        dictionary->entry_name = strdup ("");
        dictionary->entry_object_handle = strdup ("");
        dictionary->dictionary_owner_soft = strdup ("");
        dictionary->dictionary_owner_hard = strdup ("");
        dictionary->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dictionary);
}


/*!
 * \brief Read data from a DXF file into a DXF \c DICTIONARY object.
 *
 * The last line read from file contained the string "DICTIONARY". \n
 * Now follows some data for the \c DICTIONARY object, to be terminated
 * with a "  0" string announcing the following object. \n
 * While parsing the DXF file store data in \c dictionary. \n
 *
 * \return \c a pointer to \c dictionary.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfDictionary *
dxf_dictionary_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfDictionary *dictionary
                /*!< DXF \c DICTIONARY object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *temp_string = NULL;
        int i;
        int j;

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
        if (dictionary == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                dictionary = dxf_dictionary_new ();
                dictionary = dxf_dictionary_init (dictionary);
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
                        /* Clean up. */
                        free (temp_string);
                        fclose (fp->fp);
                        return (NULL);
                }
                else if (strcmp (temp_string, "  3") == 0)
                {
                        /* Now follows a string containing additional
                         * proprietary data. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dictionary->entry_name);
                        j++;
                }
                if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", &dictionary->id_code);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
                        if (strcmp (temp_string, "AcDbDictionary") != 0)
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () found a bad subclass marker in: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                        }
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing Soft-pointer
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dictionary->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "350") == 0)
                {
                        /* Now follows a string containing a handle to ae
                         * entry object. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dictionary->entry_object_handle);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dictionary->dictionary_owner_hard);
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
        return (dictionary);
}


/*!
 * \brief Free the allocated memory for a DXF \c DICTIONARY and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
int
dxf_dictionary_free
(
        DxfDictionary *dictionary
                /*!< Pointer to the memory occupied by the DXF
                 * \c DICTIONARY object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dictionary->next != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to next DxfDictionary was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (dictionary->entry_name);
        free (dictionary->entry_object_handle);
        free (dictionary);
        dictionary = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/* EOF*/
