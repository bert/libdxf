/*!
 * \file appid.c
 *
 * \author Copyright (C) 2009, 2011, 2012, 2014, 2015, 2016, 2017, 2018,
 * 2019, 2021 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \author Copyright (C) 2010 by Luis Matos <gass@otiliamatos.ath.cx>
 *
 * \brief Functions for a DXF application identity symbol table entry
 * (\c APPID).
 *
 * \since The \c APPID table was introduced in DXF R12.
 *
 * A DXF \c APPID symbol table entry contains data concerning the
 * application registered with the drawing involved.\n
 * It is a table entry in the \c TABLES section of the DXF file.\n
 * These table entries maintain a set of names for all applications
 * registered with a drawing.
 *
 * \warning dxf_appid_new(), dxf_appid_init(), dxf_appid_read() and
 * dxf_appid_free() are backward compatible with versions R10 and R11 to
 * allow for reading DXF data generated with other CAD software. \n
 * When writing DXF data to file with versions before DXF R12 a warning
 * message is given.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
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


#include "appid.h"


/*!
 * \brief Allocate memory for a DXF \c APPID symbol table entry.
 *
 * Fill the memory contents with zeros.
 */
DxfAppid *
dxf_appid_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfAppid *appid = NULL;
        size_t size;

        size = sizeof (DxfAppid);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((appid = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                appid = NULL;
        }
        else
        {
                memset (appid, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (appid);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c APPID
 * symbol table entry.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfAppid *
dxf_appid_init
(
        DxfAppid *appid
                /*!< a pointer to a DXF \c APPID symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (appid == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                appid = dxf_appid_new ();
        }
        if (appid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        appid->id_code = 0;
        appid->application_name = strdup ("");
        appid->flag = 0;
        appid->dictionary_owner_soft = strdup ("");
        appid->object_owner_soft = strdup ("");
        appid->dictionary_owner_hard = strdup ("");
        appid->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (appid);
}


/*!
 * \brief Read data from a DXF file into a DXF \c APPID symbol table
 * entry.
 *
 * The last line read from file contained the string "APPID". \n
 * Now follows some data for the \c APPID, to be terminated with a "  0"
 * string announcing the following table record, or the end of the
 * \c TABLE section marker \c ENDTAB. \n
 * While parsing the DXF file store data in \c appid. \n
 *
 * \return a pointer to \c appid.
 */
DxfAppid *
dxf_appid_read
(
        DxfFile *fp,
                /*!< a DXF file pointer to an input file (or device). */
        DxfAppid *appid
                /*!< a pointer to a DXF \c APPID symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *temp_string = NULL;
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
        if (appid == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                appid = dxf_appid_init (appid);
        }
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
                        fclose (fp->fp);
                        /* Clean up. */
                        free (temp_string);
                        return (NULL);
                }
                if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", (uint *) &appid->id_code);
                }
                else if (strcmp (temp_string, "2") == 0)
                {
                        /* Now follows a string containing an application
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, appid->application_name);
                }
                else if (strcmp (temp_string, "70") == 0)
                {
                        /* Now follows a string containing the
                         * standard flag value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &appid->flag);
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        if (iter330 == 0)
                        {
                                /* Now follows a string containing a soft-pointer
                                 * ID/handle to owner dictionary. */
                                (fp->line_number)++;
                                fscanf (fp->fp, DXF_MAX_STRING_FORMAT, appid->dictionary_owner_soft);
                        }
                        if (iter330 == 1)
                        {
                                /* Now follows a string containing a soft-pointer
                                 * ID/handle to owner object. */
                                (fp->line_number)++;
                                fscanf (fp->fp, DXF_MAX_STRING_FORMAT, appid->object_owner_soft);
                        }
                        iter330++;
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, appid->dictionary_owner_hard);
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
        DXF_DEBUG_END
#endif
        return (appid);
}


/*!
 * \brief Write DXF output to a file for a DXF \c APPID symbol table
 * entry.
 */
int
dxf_appid_write
(
        DxfFile *fp,
                /*!< a DXF file pointer to an output file (or device). */
        DxfAppid *appid
                /*!< a pointer to a DXF \c APPID symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("APPID");

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
        if (appid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if ((appid->application_name == NULL)
          || (strcmp (appid->application_name, "") == 0))
        {
                fprintf (stderr,
                  (_("Error in %s empty block name string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, appid->id_code);
                fprintf (stderr,
                  (_("\t%s entity is discarded from output.\n")),
                  dxf_entity_name);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (fp->acad_version_number < AutoCAD_12)
        {
                fprintf (stderr,
                  (_("Warning in %s () illegal DXF version for this entity.\n")),
                  __FUNCTION__);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (appid->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", appid->id_code);
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
        if ((strcmp (appid->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", appid->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (appid->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", appid->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (appid->object_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_2000))
        {
                fprintf (fp->fp, "330\n%s\n", appid->object_owner_soft);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbSymbolTableRecord\n");
                fprintf (fp->fp, "100\nAcDbRegAppTableRecord\n");
        }
        fprintf (fp->fp, "  2\n%s\n", appid->application_name);
        fprintf (fp->fp, " 70\n%hd\n", appid->flag);
        /* Clean up. */
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c APPID and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_appid_free
(
        DxfAppid *appid
                /*!< a pointer to a DXF \c APPID symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (appid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (appid->next != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to next was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (appid->application_name);
        free (appid->dictionary_owner_soft);
        free (appid->object_owner_soft);
        free (appid->dictionary_owner_hard);
        free (appid);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c APPID symbol table entries and all their data fields.
 */
void
dxf_appid_free_list
(
        DxfAppid *appids
                /*!< a pointer to a single linked list of DXF
                 * \c APPID symbol table entries. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (appids == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (appids != NULL)
        {
                DxfAppid *iter = (DxfAppid *) appids->next;
                dxf_appid_free (appids);
                appids = (DxfAppid *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the ID code from this DXF \c APPID symbol table entry.
 *
 * \return ID code.
 */
int
dxf_appid_get_id_code
(
        DxfAppid *appid
                /*!< a pointer to a DXF \c APPID symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (appid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (appid->id_code < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (appid->id_code);
}


/*!
 * \brief Set the ID code for this DXF \c APPID symbol table entry.
 */
DxfAppid *
dxf_appid_set_id_code
(
        DxfAppid *appid,
                /*!< a pointer to a DXF \c APPID symbol table entry. */
        int id_code
                /*!< Identification number for the symbol table entry.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (appid == NULL)
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
        appid->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (appid);
}


/*!
 * \brief Get the application name from this DXF \c APPID symbol table
 * entry.
 *
 * \return application name.
 */
char *
dxf_appid_get_application_name
(
        DxfAppid *appid
                /*!< a pointer to a DXF \c APPID symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (appid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (appid->application_name == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (appid->application_name));
}


/*!
 * \brief Set the application name for this DXF \c APPID symbol table
 * entry.
 *
 * \return a pointer to the DXF \c APPID symbol table entry if
 * successful, a \c NULL when an error occurred.
 *
 * \warning No testing for the contents of the \c application_name
 * member of the \c DxfAppid struct is performed.\n
 *
 * \warning The passed \c name variable is not freed by this function
 * and needs to be freed by the caller.
 */
DxfAppid *
dxf_appid_set_application_name
(
        DxfAppid *appid,
                /*!< a pointer to a DXF \c APPID symbol table entry. */
        char *name
                /*!< application name. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (appid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (name == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        appid->application_name = strdup (name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (appid);
}


/*!
 * \brief Get the flag value from this DXF \c APPID symbol table entry.
 *
 * \return flag value.
 */
int16_t
dxf_appid_get_flag
(
        DxfAppid *appid
                /*!< a pointer to a DXF \c APPID symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (appid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (appid->flag < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (appid->flag > 0x111111)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (appid->flag);
}


/*!
 * \brief Set the flag for this DXF \c APPID symbol table entry.
 */
DxfAppid *
dxf_appid_set_flag
(
        DxfAppid *appid,
                /*!< a pointer to a DXF \c APPID symbol table entry. */
        int16_t flag
                /*!< the flag value to be set. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (appid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (flag < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (flag > 0x111111)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        appid->flag = flag;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (appid);
}


/*!
 * \brief Test if xdata associated with this DXF \c APPID is not to be
 * written when \c SAVEASR12 is performed.
 *
 * \return \c TRUE when not to be written,
 * or \c FALSE when to be written.
 */
int
dxf_appid_is_no_save_xdata
(
        DxfAppid *appid
                /*!< a pointer to a DXF \c APPID symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (appid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (DXF_CHECK_BIT (appid->flag, 0));
}


/*!
 * \brief Test if this DXF \c APPID is externally dependent on an xref.
 *
 * \return \c TRUE when \c APPID is externally dependent on an xref,
 * or \c FALSE when \c APPID is not externally dependent on an xref.
 */
int
dxf_appid_is_xreferenced
(
        DxfAppid *appid
                /*!< a pointer to a DXF \c APPID symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (appid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (DXF_CHECK_BIT (appid->flag, 4));
}


/*!
 * \brief Test if this DXF \c APPID is externally dependent on a xref
 * and has been successfully resolved.
 *
 * \return \c TRUE when \c APPID is externally dependent on a xref and
 * has been successfully resolved, or \c FALSE when \c APPID is not
 * externally dependent on a xref and has not been successfully resolved.
 */
int
dxf_appid_is_xresolved
(
        DxfAppid *appid
                /*!< a pointer to a DXF \c APPID symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (appid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DXF_CHECK_BIT (appid->flag, 4))
          && (DXF_CHECK_BIT (appid->flag, 5)));
}


/*!
 * \brief Test if this DXF \c APPID is internally referenced by an
 * entity.
 *
 * \return \c TRUE when \c APPID is internally referenced by an entity,
 * or \c FALSE when \c APPID is not internally referenced by an entity.
 */
int
dxf_appid_is_referenced
(
        DxfAppid *appid
                /*!< a pointer to a DXF \c APPID symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (appid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (DXF_CHECK_BIT (appid->flag, 6));
}


/*!
 * \brief Get the soft pointer to the dictionary owner from this DXF 
 * \c APPID symbol table entry.
 *
 * \return soft pointer to the dictionary owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_appid_get_dictionary_owner_soft
(
        DxfAppid *appid
                /*!< a pointer to a DXF \c APPID symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (appid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (appid->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (appid->dictionary_owner_soft));
}


/*!
 * \brief Set the pointer to the dictionary_owner_soft for a DXF
 * \c APPID symbol table entry.
 */
DxfAppid *
dxf_appid_set_dictionary_owner_soft
(
        DxfAppid *appid,
                /*!< a pointer to a DXF \c APPID symbol table entry. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the
                 * dictionary_owner_soft for the symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (appid == NULL)
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
        appid->dictionary_owner_soft = strdup (dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (appid);
}


/*!
 * \brief Get the soft pointer to the object owner from a DXF 
 * \c APPID symbol table entry.
 *
 * \return soft pointer to the object owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_appid_get_object_owner_soft
(
        DxfAppid *appid
                /*!< a pointer to a DXF \c APPID symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (appid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (appid->object_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (appid->object_owner_soft));
}


/*!
 * \brief Set the pointer to the \c object_owner_soft for a DXF
 * \c APPID symbol table entry.
 */
DxfAppid *
dxf_appid_set_object_owner_soft
(
        DxfAppid *appid,
                /*!< a pointer to a DXF \c APPID symbol table entry. */
        char *object_owner_soft
                /*!< a string containing the pointer to the
                 * \c object_owner_soft for the symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (appid == NULL)
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
        appid->object_owner_soft = strdup (object_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (appid);
}


/*!
 * \brief Get the hard pointer to the dictionary owner from this DXF 
 * \c APPID symbol table entry.
 *
 * \return hard pointer to the dictionary owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_appid_get_dictionary_owner_hard
(
        DxfAppid *appid
                /*!< a pointer to a DXF \c APPID symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (appid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (appid->dictionary_owner_hard ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (appid->dictionary_owner_hard));
}


/*!
 * \brief Set the pointer to the dictionary_owner_hard for a DXF
 * \c APPID symbol table entry.
 */
DxfAppid *
dxf_appid_set_dictionary_owner_hard
(
        DxfAppid *appid,
                /*!< a pointer to a DXF \c APPID symbol table entry. */
        char *dictionary_owner_hard
                /*!< a string containing the pointer to the
                 * dictionary_owner_hard for the symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (appid == NULL)
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
        appid->dictionary_owner_hard = strdup (dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (appid);
}


/*!
 * \brief Get the pointer to the next \c APPID symbol table entry from a DXF 
 * \c APPID symbol table entry.
 *
 * \return pointer to the next \c APPID symbol table entry.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfAppid *
dxf_appid_get_next
(
        DxfAppid *appid
                /*!< a pointer to a DXF \c APPID symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (appid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (appid->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfAppid *) appid->next);
}


/*!
 * \brief Set the pointer to the next \c APPID for a DXF \c APPID
 * symbol table entry.
 */
DxfAppid *
dxf_appid_set_next
(
        DxfAppid *appid,
                /*!< a pointer to a DXF \c APPID symbol table entry. */
        DxfAppid *next
                /*!< a pointer to the next \c APPID for the symbol table
                 * entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (appid == NULL)
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
        appid->next = (struct DxfAppid *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (appid);
}


/*!
 * \brief Get the pointer to the last \c APPID symbol table entry from
 * a linked list of DXF \c APPID symbol table entries.
 *
 * \return pointer to the last \c APPID symbol table entry.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfAppid *
dxf_appid_get_last
(
        DxfAppid *appid
                /*!< a pointer to a DXF \c APPID symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (appid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (appid->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfAppid *) appid);
        }
        DxfAppid *iter = (DxfAppid *) appid->next;
        while (iter->next != NULL)
        {
                iter = (DxfAppid *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfAppid *) iter);
}


/* EOF*/
