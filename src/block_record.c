/*!
 * \file block_record.c
 *
 * \author Copyright (C) 2015, 2016, 2017, 2018, 2019, 2020, 2021
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
 * allocated memory when successful.
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
        /* Assign initial values to members. */
        block_record->id_code = 0;
        block_record->block_name = strdup ("");
        block_record->flag = 0;
        block_record->insert_units = 0;
        block_record->explodability = 0;
        block_record->scalability = 0;
        block_record->dictionary_owner_soft = strdup ("");
        block_record->object_owner_soft = strdup ("");
        block_record->dictionary_owner_hard = strdup ("");
        block_record->xdata_string_data = strdup ("DesignCenter Data");
        block_record->xdata_application_name = strdup ("ACAD");
        block_record->design_center_version_number = 0;
        block_record->insert_units = 0;
        /* Initialize new structs for the following members later,
         * when they are required and when we have content. */
        block_record->binary_graphics_data = NULL;
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
        DxfBinaryData *iter310 = NULL;
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
        if (block_record == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                block_record = dxf_block_record_init (block_record);
        }
        if (block_record->binary_graphics_data == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfBinaryData struct.\n")));
                block_record->binary_graphics_data = dxf_binary_data_init (block_record->binary_graphics_data);
                if (block_record->binary_graphics_data == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        iter310 = (DxfBinaryData *) block_record->binary_graphics_data;
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
                        fscanf (fp->fp, "%x\n", (uint *) &block_record->id_code);
                }
                else if (strcmp (temp_string, "2") == 0)
                {
                        /* Now follows a string containing an application
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, block_record->block_name);
                }
/*! \todo Implement Group Code = 70 in a proper way. */
                else if (strcmp (temp_string, "70") == 0)
                {
                        /* Now follows a string containing the
                         * standard flag value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &block_record->flag);
                }
                else if (strcmp (temp_string, "280") == 0)
                {
                        /* Now follows a string containing the block
                         * explodability value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &block_record->explodability);
                }
                else if (strcmp (temp_string, "281") == 0)
                {
                        /* Now follows a string containing the block
                         * scalability value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &block_record->scalability);
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
                                fscanf (fp->fp, DXF_MAX_STRING_FORMAT, block_record->dictionary_owner_soft);
                        }
                        if (iter330 == 1)
                        {
                                /* Now follows a string containing a soft-pointer
                                 * ID/handle to owner object. */
                                (fp->line_number)++;
                                fscanf (fp->fp, DXF_MAX_STRING_FORMAT, block_record->object_owner_soft);
                        }
                        iter330++;
                }
                else if (strcmp (temp_string, "340") == 0)
                {
                        /* Now follows a string containing Hard-pointer
                         * ID/handle to associated LAYOUT object. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, block_record->associated_layout_hard);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, block_record->dictionary_owner_hard);
                }
                else if (strcmp (temp_string, "999") == 0)
                {
                        /* Now follows a string containing a comment. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        fprintf (stdout, "DXF comment: %s\n", temp_string);
                }
                else if (strcmp (temp_string, "1000") == 0)
                {
                        /* Now follows a string containing the Xdata
                         * string data. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, block_record->xdata_string_data);
                        if (strcmp (block_record->xdata_string_data, "DesignCenter Data") != 0)
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () unfamiliar string found while reading from: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                        }
                }
                else if (strcmp (temp_string, "1001") == 0)
                {
                        /* Now follows a string containing the Xdata
                         * application name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, block_record->xdata_application_name);
                        if (strcmp (block_record->xdata_application_name, "ACAD") != 0)
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () unfamiliar string found while reading from: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                        }
                }
/*! \todo Implement Group Code = 1070 in a proper way. */
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
        if ((strcmp (block_record->object_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "330\n%s\n", block_record->object_owner_soft);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbSymbolTableRecord\n");
                fprintf (fp->fp, "100\nAcDbRegAppTableRecord\n");
        }
        fprintf (fp->fp, "  2\n%s\n", block_record->block_name);
        fprintf (fp->fp, " 70\n%hd\n", block_record->flag);
        if (fp->acad_version_number >= AutoCAD_2000)
        {
                fprintf (fp->fp, "340\n%s\n", block_record->associated_layout_hard);
        }
        if (fp->acad_version_number >= AutoCAD_2007)
        {
                fprintf (fp->fp, "280\n%hd\n", block_record->explodability);
                fprintf (fp->fp, "281\n%hd\n", block_record->scalability);
        }
        if (fp->acad_version_number >= AutoCAD_2000)
        {
                if (block_record->binary_graphics_data != NULL)
                {
                        DxfBinaryData *iter;
                        iter = (DxfBinaryData *) block_record->binary_graphics_data;
                        while (iter != NULL)
                        {
                                fprintf (fp->fp, "310\n%s\n", iter->data_line);
                                iter = (DxfBinaryData *) iter->next;
                        }
                }
                if (block_record->xdata_application_name != NULL)
                {
                        fprintf (fp->fp, "1001\n%s\n", block_record->xdata_application_name);
                }
                if (block_record->xdata_string_data != NULL)
                {
                        fprintf (fp->fp, "1000\n%s\n", block_record->xdata_string_data);
                        fprintf (fp->fp, "1002\n{\n");
                        fprintf (fp->fp, "1070\n%hd\n", block_record->design_center_version_number);
                        fprintf (fp->fp, "1070\n%hd\n", block_record->insert_units);
                        fprintf (fp->fp, "1002\n}\n");
                }
        }
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
        dxf_binary_data_free_list (block_record->binary_graphics_data);
        free (block_record->dictionary_owner_soft);
        free (block_record->dictionary_owner_hard);
        free (block_record);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c BLOCK_RECORD entities and all their data fields.
 */
void
dxf_block_record_free_list
(
        DxfBlockRecord *block_records
                /*!< pointer to the single linked list of DXF
                 * \c BLOCK_RECORD entities. */
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
                DxfBlockRecord *iter= (DxfBlockRecord *) block_records->next;
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
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
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
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
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
                  (_("Error in %s () a NULL pointer was found.\n")),
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
int16_t
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
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (block_record->flag > 64)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
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
        int16_t flag
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
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (flag > 64)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
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
 * \brief Get the \c insertion_units value from a DXF \c BLOCK_RECORD
 * symbol table entry.
 *
 * \return \c insertion_units value.
 */
int16_t
dxf_block_record_get_insertion_units
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
        if (block_record->insertion_units < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (block_record->insertion_units > 20)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (block_record->insertion_units);
}


/*!
 * \brief Set the \c insertion_units value for a DXF \c BLOCK_RECORD
 * symbol table entry.
 */
DxfBlockRecord *
dxf_block_record_set_insertion_units
(
        DxfBlockRecord *block_record,
                /*!< a pointer to a DXF \c BLOCK_RECORD symbol table
                 * entry. */
        int16_t insertion_units
                /*!< Block insertion units. */
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
        if (insertion_units < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (insertion_units > 20)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        block_record->insertion_units = insertion_units;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (block_record);
}


/*!
 * \brief Get the \c explodability value from a DXF \c BLOCK_RECORD
 * symbol table entry.
 *
 * Specifies whether block references associated with this block table
 * record can be exploded.
 *
 * \return \c explodability value: \c true if the block can be exploded
 * or \c false if it cannot.
 */
int16_t
dxf_block_record_get_explodability
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
        if (block_record->explodability < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (block_record->explodability > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (block_record->explodability);
}


/*!
 * \brief Set the \c explodability value for a DXF \c BLOCK_RECORD
 * symbol table entry.
 */
DxfBlockRecord *
dxf_block_record_set_explodability
(
        DxfBlockRecord *block_record,
                /*!< a pointer to a DXF \c BLOCK_RECORD symbol table
                 * entry. */
        int16_t explodability
                /*!< Block explodability. */
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
        if (explodability < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (explodability > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        block_record->explodability = explodability;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (block_record);
}


/*!
 * \brief Get the \c scalability value from a DXF \c BLOCK_RECORD
 * symbol table entry.
 *
 * \return \c scalability value.
 */
int16_t
dxf_block_record_get_scalability
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
        if (block_record->scalability < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (block_record->scalability > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (block_record->scalability);
}


/*!
 * \brief Set the \c scalability value for a DXF \c BLOCK_RECORD
 * symbol table entry.
 */
DxfBlockRecord *
dxf_block_record_set_scalability
(
        DxfBlockRecord *block_record,
                /*!< a pointer to a DXF \c BLOCK_RECORD symbol table
                 * entry. */
        int16_t scalability
                /*!< Block scalability. */
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
        if (scalability < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (scalability > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        block_record->scalability = scalability;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (block_record);
}


/*!
 * \brief Get the pointer to the \c binary_graphics_data from a DXF
 * \c BLOCK_RECORD symbol table entry.
 *
 * \return pointer to the \c binary_graphics_data.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfBinaryData *
dxf_block_record_get_binary_graphics_data
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
        if (block_record->binary_graphics_data ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfBinaryData *) block_record->binary_graphics_data);
}


/*!
 * \brief Set the pointer to the \c binary_graphics_data for a DXF
 * \c BLOCK_RECORD symbol table entry.
 */
DxfBlockRecord *
dxf_block_record_set_binary_graphics_data
(
        DxfBlockRecord *block_record,
                /*!< a pointer to a DXF \c BLOCK_RECORD symbol table
                 * entry. */
        DxfBinaryData *data
                /*!< a string containing the pointer to the
                 * \c binary_graphics_data for the entity. */
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
        if (data == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        block_record->binary_graphics_data = (DxfBinaryData *) data;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (block_record);
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
                  (_("Error in %s () a NULL pointer was found.\n")),
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
 * \brief Get the soft pointer to the object owner from a DXF 
 * \c BLOCK_RECORD symbol table entry.
 *
 * \return soft pointer to the object owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_block_record_get_object_owner_soft
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
        if (block_record->object_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (block_record->object_owner_soft));
}


/*!
 * \brief Set the pointer to the \c object_owner_soft for a DXF
 * \c BLOCK_RECORD symbol table entry.
 */
DxfBlockRecord *
dxf_block_record_set_object_owner_soft
(
        DxfBlockRecord *block_record,
                /*!< a pointer to a DXF \c BLOCK_RECORD symbol table
                 * entry. */
        char *object_owner_soft
                /*!< a string containing the pointer to the
                 * \c object_owner_soft for the entity. */
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
        if (object_owner_soft == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        block_record->object_owner_soft = strdup (object_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (block_record);
}


/*!
 * \brief Get the hard pointer to the associated layout object from a
 * DXF \c BLOCK_RECORD symbol table entry.
 *
 * \return hard pointer to the associated layout object.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_block_record_get_associated_layout_hard
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
        if (block_record->associated_layout_hard ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (block_record->associated_layout_hard));
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
                  (_("Error in %s () a NULL pointer was found.\n")),
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
 * \brief Get the \c xdata_string_data string from a DXF 
 * \c BLOCK_RECORD symbol table entry.
 *
 * \return \c xdata_string_data string.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_block_record_get_xdata_string_data
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
        if (block_record->xdata_string_data ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (block_record->xdata_string_data));
}


/*!
 * \brief Set the pointer to the \c xdata_string_data for a DXF
 * \c BLOCK_RECORD symbol table entry.
 */
DxfBlockRecord *
dxf_block_record_set_xdata_string_data
(
        DxfBlockRecord *block_record,
                /*!< a pointer to a DXF \c BLOCK_RECORD symbol table
                 * entry. */
        char *xdata_string_data
                /*!< a string containing the pointer to the
                 * \c xdata_string_data for the symbol table entry. */
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
        if (xdata_string_data == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        block_record->xdata_string_data = strdup (xdata_string_data);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (block_record);
}


/*!
 * \brief Get the \c xdata_application_name string from a DXF 
 * \c BLOCK_RECORD symbol table entry.
 *
 * \return \c xdata_application_name string.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_block_record_get_xdata_application_name
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
        if (block_record->xdata_application_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (block_record->xdata_application_name));
}


/*!
 * \brief Set the pointer to the \c xdata_application_name for a DXF
 * \c BLOCK_RECORD symbol table entry.
 */
DxfBlockRecord *
dxf_block_record_set_xdata_application_name
(
        DxfBlockRecord *block_record,
                /*!< a pointer to a DXF \c BLOCK_RECORD symbol table
                 * entry. */
        char *xdata_application_name
                /*!< a string containing the pointer to the
                 * \c xdata_application_name for the symbol table entry. */
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
        if (xdata_application_name == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        block_record->xdata_application_name = strdup (xdata_application_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (block_record);
}


/*!
 * \brief Get the \c design_center_version_number from a DXF
 * \c BLOCK_RECORD symbol table entry.
 *
 * \return \c design_center_version_number.
 */
int16_t
dxf_block_record_get_design_center_version_number
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
        if (block_record->design_center_version_number < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (block_record->design_center_version_number);
}


/*!
 * \brief Set the \c design_center_version_number for a DXF
 * \c BLOCK_RECORD symbol table entry.
 */
DxfBlockRecord *
dxf_block_record_set_design_center_version_number
(
        DxfBlockRecord *block_record,
                /*!< a pointer to a DXF \c BLOCK_RECORD symbol table
                 * entry. */
        int16_t design_center_version_number
                /*!< The \c design_center_version_number for the DXF
                 * \c BLOCK_RECORD symbol table entry. */
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
        if (design_center_version_number < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        block_record->design_center_version_number = design_center_version_number;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (block_record);
}


/*!
 * \brief Get the \c insert_units from a DXF \c BLOCK_RECORD symbol
 * table entry.
 *
 * \return \c insert_units.
 */
int16_t
dxf_block_record_get_insert_units
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
        if (block_record->insert_units < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (block_record->insert_units > 20)
        {
                fprintf (stderr,
                  (_("Warning in %s () an invalid value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (block_record->insert_units);
}


/*!
 * \brief Set the \c insert_units for a DXF \c BLOCK_RECORD symbol table
 * entry.
 */
DxfBlockRecord *
dxf_block_record_set_insert_units
(
        DxfBlockRecord *block_record,
                /*!< a pointer to a DXF \c BLOCK_RECORD symbol table
                 * entry. */
        int16_t insert_units
                /*!< The \c insert_units for the DXF \c BLOCK_RECORD
                 * symbol table entry. */
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
        if (insert_units < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (insert_units > 20)
        {
                fprintf (stderr,
                  (_("Warning in %s () an invalid value was passed.\n")),
                  __FUNCTION__);
        }
        block_record->insert_units = insert_units;
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
