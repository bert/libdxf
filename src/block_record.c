/*!
 * \file block_record.c
 *
 * \author Copyright (C) 2015, 2016, 2017, 2018
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF block record symbol table entry
 * (\c BLOCK_RECORD).
 *
 * \since The \c BLOCK_RECORD table was introduced in DXF R13.
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


#include "block_record.h"


/*!
 * \brief Allocate memory for a DXF \c BLOCK_RECORD symbol table entry.
 *
 * Fill the memory contents with zeros.
 */
DxfBlockRecord *
dxf_block_record_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfBlockRecord *block_record = NULL;
        size_t size;

        size = sizeof (DxfBlockRecord);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((block_record = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                block_record = NULL;
        }
        else
        {
                memset (block_record, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (block_record);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF
 * \c BLOCK_RECORD symbol table entry.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfBlockRecord *
dxf_block_record_init
(
        DxfBlockRecord *block_record
                /*!< DXF block record symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (block_record == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                block_record = dxf_block_record_new ();
        }
        if (block_record == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        block_record->id_code = 0;
        block_record->block_name = strdup ("");
        block_record->flag = 0;
        block_record->insert_units = 0;
        block_record->explodability = 0;
        block_record->scalability = 0;
        block_record->binary_graphics_data = (DxfBinaryGraphicsData *) dxf_binary_graphics_data_new ();
        block_record->binary_graphics_data = (DxfBinaryGraphicsData *) dxf_binary_graphics_data_init (block_record->binary_graphics_data);
        block_record->dictionary_owner_soft = strdup ("");
        block_record->object_owner_soft = strdup ("");
        block_record->dictionary_owner_hard = strdup ("");
        block_record->xdata_string_data = strdup ("DesignCenter Data");
        block_record->xdata_application_name = strdup ("ACAD");
        block_record->design_center_version_number = 0;
        block_record->insert_units = 0;
        block_record->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (block_record);
}


/*!
 * \brief Read data from a DXF file into a DXF \c BLOCK_RECORD symbol
 * table entry.
 *
 * The last line read from file contained the string "BLOCK_RECORD". \n
 * Now follows some data for the \c BLOCK_RECORD, to be terminated with
 * a "  0"  string announcing the following table record, or the end of
 * the \c TABLE section marker \c ENDTAB. \n
 * While parsing the DXF file store data in \c block_record. \n
 *
 * \return a pointer to \c block_record.
 */
DxfBlockRecord *
dxf_block_record_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfBlockRecord *block_record
                /*!< DXF block_record symbol table entry. */
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
        if (block_record == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                block_record = dxf_block_record_new ();
                block_record = dxf_block_record_init (block_record);
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
                if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", &block_record->id_code);
                }
                else if (strcmp (temp_string, "2") == 0)
                {
                        /* Now follows a string containing an application
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", block_record->block_name);
                }
                else if (strcmp (temp_string, "70") == 0)
                {
                        /* Now follows a string containing the
                         * standard flag value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &block_record->flag);
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing Soft-pointer
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", block_record->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", block_record->dictionary_owner_hard);
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
        /* Clean up. */
        free (temp_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (block_record);
}


/*!
 * \brief Write DXF output to a file for a DXF \c BLOCK_RECORD symbol table
 * entry.
 */
int
dxf_block_record_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfBlockRecord *block_record
                /*!< DXF \c BLOCK_RECORD symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("BLOCK_RECORD");

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
        if (fp->acad_version_number < AutoCAD_13)
        {
                fprintf (stderr,
                  (_("Error in %s () illegal DXF version for this entity.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (block_record == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if ((block_record->block_name == NULL)
          || (strcmp (block_record->block_name, "") == 0))
        {
                fprintf (stderr,
                  (_("Error in %s empty block name string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, block_record->id_code);
                fprintf (stderr,
                  (_("\t%s entity is discarded from output.\n")),
                  dxf_entity_name);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (block_record->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", block_record->id_code);
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
        if ((strcmp (block_record->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", block_record->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (block_record->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", block_record->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbSymbolTableRecord\n");
                fprintf (fp->fp, "100\nAcDbRegAppTableRecord\n");
        }
        fprintf (fp->fp, "  2\n%s\n", block_record->block_name);
        fprintf (fp->fp, " 70\n%d\n", block_record->flag);
        /* Clean up. */
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c BLOCK_RECORD and all
 * it's data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_block_record_free
(
        DxfBlockRecord *block_record
                /*!< DXF \c BLOCK_RECORD symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (block_record == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (block_record->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (block_record->block_name);
        free (block_record->dictionary_owner_soft);
        free (block_record->dictionary_owner_hard);
        free (block_record);
        block_record = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a chain of DXF \c BLOCK_RECORD
 * entities and all their data fields.
 */
void
dxf_block_record_free_chain
(
        DxfBlockRecord *block_records
                /*!< pointer to the chain of DXF \c BLOCK_RECORD entities. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (block_records == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (block_records != NULL)
        {
                struct DxfBlockRecord *iter= block_records->next;
                dxf_block_record_free (block_records);
                block_records = (DxfBlockRecord *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the ID code from a DXF \c BLOCK_RECORD symbol table entry.
 *
 * \return ID code.
 */
int
dxf_block_record_get_id_code
(
        DxfBlockRecord *block_record
                /*!< a pointer to a DXF \c BLOCK_RECORD symbol table
                 * entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (block_record == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (block_record->id_code < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the id-code member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (block_record->id_code);
}


/*!
 * \brief Set the ID code for a DXF \c BLOCK_RECORD symbol table entry.
 */
DxfBlockRecord *
dxf_block_record_set_id_code
(
        DxfBlockRecord *block_record,
                /*!< a pointer to a DXF \c BLOCK_RECORD symbol table
                 * entry. */
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
        if (block_record == NULL)
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
        block_record->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (block_record);
}


/*!
 * \brief Get the block name from a DXF \c BLOCK_RECORD symbol table
 * entry.
 *
 * \return block name when sucessful, \c NULL when an error occurred.
 */
char *
dxf_block_record_get_block_name
(
        DxfBlockRecord *block_record
                /*!< a pointer to a DXF \c BLOCK_RECORD symbol table
                 * entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (block_record == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (block_record->block_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the block_name member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (block_record->block_name));
}


/*!
 * \brief Set the block name for a DXF \c BLOCK_RECORD symbol table
 * entry.
 */
DxfBlockRecord *
dxf_block_record_set_block_name
(
        DxfBlockRecord *block_record,
                /*!< a pointer to a DXF \c BLOCK_RECORD symbol table
                 * entry. */
        char *block_name
                /*!< a string containing the block name for the symbol
                 * table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (block_record == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (block_name == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        block_record->block_name= strdup (block_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (block_record);
}


/*!
 * \brief Get the flag value from a DXF \c BLOCK_RECORD symbol table
 * entry.
 *
 * \return flag value.
 */
int
dxf_block_record_get_flag
(
        DxfBlockRecord *block_record
                /*!< a pointer to a DXF \c BLOCK_RECORD symbol table
                 * entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (block_record == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (block_record->flag < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the flag member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (block_record->flag > 64)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was found in the flag member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (block_record->flag);
}


/*!
 * \brief Set the flag value for a DXF \c BLOCK_RECORD symbol table
 * entry.
 */
DxfBlockRecord *
dxf_block_record_set_flag
(
        DxfBlockRecord *block_record,
                /*!< a pointer to a DXF \c BLOCK_RECORD symbol table
                 * entry. */
        int flag
                /*!< This flag is for the benefit of AutoCAD commands;
                 * it can be ignored by most programs that read DXF files,
                 * and need not be set by programs that write DXF files. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (block_record == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (flag < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative flag value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (flag > 64)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range flag value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        block_record->flag = flag;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (block_record);
}


/*!
 * \brief Test if this DXF \c BLOCK_RECORD is externally dependent on an
 * xref.
 *
 * \return \c TRUE when \c BLOCK_RECORD is externally dependent on an
 * xref, or \c FALSE when \c BLOCK_RECORD is not externally dependent on
 * an xref, or (-1) when an error occured.
 */
int
dxf_block_record_is_xreferenced
(
        DxfBlockRecord *block_record
                /*!< DXF \c BLOCK_RECORD symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (block_record == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (-1);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (DXF_CHECK_BIT (block_record->flag, 4));
}


/*!
 * \brief Test if this DXF \c BLOCK_RECORD is externally dependent on a
 * xref and has been successfully resolved.
 *
 * \return \c TRUE when \c BLOCK_RECORD is externally dependent on a
 * xref and has been successfully resolved, or \c FALSE when
 * \c BLOCK_RECORD is not externally dependent on a xref and has not
 * been successfully resolved, or (-1) when an error occured.
 */
int
dxf_block_record_is_xresolved
(
        DxfBlockRecord *block_record
                /*!< DXF \c BLOCK_RECORD symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (block_record == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (-1);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DXF_CHECK_BIT (block_record->flag, 4))
          && (DXF_CHECK_BIT (block_record->flag, 5)));
}


/*!
 * \brief Test if this DXF \c BLOCK_RECORD is internally referenced by
 * an entity.
 *
 * \return \c TRUE when \c BLOCK_RECORD is internally referenced by an
 * entity, or \c FALSE when \c BLOCK_RECORD is not internally referenced
 * by an entity, or (-1) when an error occured.
 */
int
dxf_block_record_is_referenced
(
        DxfBlockRecord *block_record
                /*!< DXF \c BLOCK_RECORD symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (block_record == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (-1);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (DXF_CHECK_BIT (block_record->flag, 6));
}


/*!
 * \brief Get the soft pointer to the dictionary owner from a DXF 
 * \c BLOCK_RECORD symbol table entry.
 *
 * \return soft pointer to the dictionary owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_block_record_get_dictionary_owner_soft
(
        DxfBlockRecord *block_record
                /*!< a pointer to a DXF \c BLOCK_RECORD symbol table
                 * entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (block_record == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (block_record->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the dictionary_owner_soft member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (block_record->dictionary_owner_soft));
}


/*!
 * \brief Set the pointer to the dictionary_owner_soft for a DXF
 * \c BLOCK_RECORD symbol table entry.
 */
DxfBlockRecord *
dxf_block_record_set_dictionary_owner_soft
(
        DxfBlockRecord *block_record,
                /*!< a pointer to a DXF \c BLOCK_RECORD symbol table
                 * entry. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the
                 * dictionary_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (block_record == NULL)
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
        block_record->dictionary_owner_soft = strdup (dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (block_record);
}


/*!
 * \brief Get the hard pointer to the dictionary owner from a DXF 
 * \c BLOCK_RECORD symbol table entry.
 *
 * \return hard pointer to the dictionary owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_block_record_get_dictionary_owner_hard
(
        DxfBlockRecord *block_record
                /*!< a pointer to a DXF \c BLOCK_RECORD symbol table
                 * entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (block_record == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (block_record->dictionary_owner_hard ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the dictionary_owner_hard member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (block_record->dictionary_owner_hard));
}


/*!
 * \brief Set the pointer to the dictionary_owner_hard for a DXF
 * \c BLOCK_RECORD symbol table entry.
 */
DxfBlockRecord *
dxf_block_record_set_dictionary_owner_hard
(
        DxfBlockRecord *block_record,
                /*!< a pointer to a DXF \c BLOCK_RECORD symbol table
                 * entry. */
        char *dictionary_owner_hard
                /*!< a string containing the pointer to the
                 * dictionary_owner_hard for the symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (block_record == NULL)
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
        block_record->dictionary_owner_hard = strdup (dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (block_record);
}


/*!
 * \brief Get the pointer to the next \c BLOCK_RECORD symbol table entry
 * from a DXF \c BLOCK_RECORD symbol table entry.
 *
 * \return pointer to the next \c BLOCK_RECORD symbol table entry.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfBlockRecord *
dxf_block_record_get_next
(
        DxfBlockRecord *block_record
                /*!< a pointer to a DXF \c BLOCK_RECORD symbol table
                 * entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (block_record == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (block_record->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the next member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfBlockRecord *) block_record->next);
}


/*!
 * \brief Set the pointer to the next \c BLOCK_RECORD symbol table entry
 * for a DXF \c BLOCK_RECORD symbol table entry.
 */
DxfBlockRecord *
dxf_block_record_set_next
(
        DxfBlockRecord *block_record,
                /*!< a pointer to a DXF \c BLOCK_RECORD symbol table entry. */
        DxfBlockRecord *next
                /*!< a pointer to the next \c BLOCK_RECORD symbol table
                 * entry for the symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (block_record == NULL)
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
        block_record->next = (struct DxfBlockRecord *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (block_record);
}


/*!
 * \brief Get the pointer to the last \c BLOCK_RECORD symbol table entry
 * from a linked list of DXF \c BLOCK_RECORD symbol table entries.
 *
 * \return pointer to the last \c BLOCK_RECORD symbol table entry.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfBlockRecord *
dxf_block_record_get_last
(
        DxfBlockRecord *block_record
                /*!< a pointer to a DXF \c BLOCK_RECORD symbol table
                 * entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (block_record == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (block_record->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found in the next member.\n")),
                  __FUNCTION__);
                return ((DxfBlockRecord *) block_record);
        }
        DxfBlockRecord *iter = (DxfBlockRecord *) block_record->next;
        while (iter->next != NULL)
        {
                iter = (DxfBlockRecord *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfBlockRecord *) iter);
}


/* EOF*/
