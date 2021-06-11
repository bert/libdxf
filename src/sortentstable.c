/*!
 * \file sortentstable.c
 *
 * \author Copyright (C) 2015, 2017, 2018, 2019, 2020, 2021
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF sortentstable object (\c SORTENTSTABLE).
 *
 * If the SORTENTS Regen flag (bit-code value 16) is set, AutoCAD
 * regenerates entities in ascending handle order.
 * When the DRAWORDER command is used, a SORTENTSTABLE object is
 * attached to the *Model_Space or *Paper_Space block's extension
 * dictionary under the name ACAD_SORTENTS.
 * The SORTENTSTABLE object related to this dictionary associates a
 * different handle with each entity, which redefines the order in which
 * the entities are regenerated.
 *
 * \since The \c SORTENTSTABLE object was introduced in DXF R14.
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


#include "sortentstable.h"


/*!
 * \brief Allocate memory for a \c DxfSortentsTable.
 *
 * Fill the memory contents with zeros.
 */
DxfSortentsTable *
dxf_sortentstable_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfSortentsTable *sortentstable = NULL;
        size_t size;

        size = sizeof (DxfSortentsTable);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((sortentstable = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfSortentsTable struct.\n")),
                  __FUNCTION__);
                sortentstable = NULL;
        }
        else
        {
                memset (sortentstable, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sortentstable);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c SORTENTSTABLE
 * object.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfSortentsTable *
dxf_sortentstable_init
(
        DxfSortentsTable *sortentstable
                /*!< a pointer to the DXF \c SORTENTSTABLE object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sortentstable == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                sortentstable = dxf_sortentstable_new ();
        }
        if (sortentstable == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfSortentsTable struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        sortentstable->id_code = 0;
        sortentstable->dictionary_owner_soft = strdup ("");
        sortentstable->dictionary_owner_hard = strdup ("");
        sortentstable->block_owner = strdup ("");
        sortentstable->entity_owner = dxf_char_init (sortentstable->entity_owner);
        sortentstable->sort_handle->value = 0;
        sortentstable->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sortentstable);
}


/*!
 * \brief Read data from a DXF file into a DXF \c SORTENTSTABLE object.
 *
 * The last line read from file contained the string "SORTENTSTABLE". \n
 * Now follows some data for the \c SORTENTSTABLE, to be terminated with a
 * "  0" string announcing the following object, or the end of the
 * \c OBJECTS section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c sortentstable. \n
 *
 * \return a pointer to \c sortentstable.
 */
DxfSortentsTable *
dxf_sortentstable_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfSortentsTable *sortentstable
                /*!< a pointer to the DXF \c SORTENTSTABLE object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *temp_string = NULL;
        int i;
        int j;
        int k;
        DxfInt *iter_5 = NULL;
        DxfChar *iter_331 = NULL;

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
        if (sortentstable == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                sortentstable = dxf_sortentstable_init (sortentstable);
        }
        i = 0;
        j = 0;
        k = 0;
        iter_5 = (DxfInt *) sortentstable->sort_handle;
        iter_331 = (DxfChar *) sortentstable->entity_owner;
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
                if ((strcmp (temp_string, "5") == 0)
                  && (k == 0))
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", (uint *) &sortentstable->id_code);
                }
                if ((strcmp (temp_string, "5") == 0)
                  && (i > 0))
                {
                        /* Now follows a string containing a Sort handle
                         * (zero or more entries may exist). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", (uint *) &iter_5->value);
                        iter_5->next = (struct DxfInt *) dxf_int_init ((DxfInt *) iter_5->next);
                        iter_5 = (DxfInt *) iter_5->next;
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if (strcmp (temp_string, "AcDbSortentsTable") != 0)
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () found a bad subclass marker in: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                        }
                }
                else if ((strcmp (temp_string, "330") == 0)
                  && (j == 0))
                {
                        /* Now follows a string containing a soft-pointer
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, sortentstable->dictionary_owner_soft);
                        j++;
                }
                else if ((strcmp (temp_string, "330") == 0)
                  && (j > 0))
                {
                        /* Now follows a string containing a soft pointer
                         * ID/handle to owner (currently only the
                         * *MODEL_SPACE or *PAPER_SPACE blocks). */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, sortentstable->block_owner);
                        j++;
                        /*! \todo Check for overrun of array index. */
                }
                else if (strcmp (temp_string, "331") == 0)
                {
                        /* Now follows a string containing a soft pointer
                         * ID/handle to an entity (zero or more entries
                         * may exist). */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, iter_331->value);
                        iter_331->next = (struct DxfChar *) dxf_char_init ((DxfChar *) iter_331->next);
                        iter_331 = (DxfChar *) iter_331->next;
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, sortentstable->dictionary_owner_hard);
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
        return (sortentstable);
}


/*!
 * \brief Write DXF output to a file for a DXF \c SORTENTSTABLE object.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_sortentstable_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfSortentsTable *sortentstable
                /*!< a pointer to the DXF \c SORTENTSTABLE object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("SORTENTSTABLE");
        DxfInt *iter_5 = NULL;
        DxfChar *iter_331 = NULL;

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
        if (sortentstable == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (fp->acad_version_number < AutoCAD_14)
        {
                fprintf (stderr,
                  (_("Warning in %s () illegal DXF version for this %s entity with id-code: %x.\n")),
                  __FUNCTION__, dxf_entity_name, sortentstable->id_code);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (sortentstable->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", sortentstable->id_code);
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
        if ((strcmp (sortentstable->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", sortentstable->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (sortentstable->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", sortentstable->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbSortentsTable\n");
        }
        fprintf (fp->fp, "330\n%s\n", sortentstable->block_owner);
        if (sortentstable->entity_owner != NULL)
        {
                iter_331 = (DxfChar*) sortentstable->entity_owner;
                while ((iter_331 != NULL) && (iter_331->value != NULL))
                {
                        fprintf (fp->fp, "331\n%s\n", iter_331->value);
                        iter_331 = (DxfChar*) iter_331->next;
                }
        }
        if (sortentstable->sort_handle != NULL)
        {
                iter_5 = (DxfInt*) sortentstable->sort_handle;
                while (iter_5 != NULL)
                {
                        fprintf (fp->fp, "  5\n%x\n", iter_5->value);
                        iter_5 = (DxfInt*) iter_5->next;
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
 * \brief Free the allocated memory for a DXF \c SORTENTSTABLE and all
 * it's data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_sortentstable_free
(
        DxfSortentsTable *sortentstable
                /*!< a pointer to the memory occupied by the DXF
                 * \c SORTENTSTABLE object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sortentstable == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (sortentstable->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (sortentstable->dictionary_owner_soft);
        free (sortentstable->dictionary_owner_hard);
        free (sortentstable->block_owner);
        dxf_char_free_list (sortentstable->entity_owner);
        free (sortentstable);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c SORTENTSTABLE objects and all their data fields.
 */
void
dxf_sortentstable_free_list
(
        DxfSortentsTable *sortentstables
                /*!< a pointer to the single linked list of DXF
                 * \c SORTENTSTABLE objects. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (sortentstables == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (sortentstables != NULL)
        {
                DxfSortentsTable *iter = (DxfSortentsTable *) sortentstables->next;
                dxf_sortentstable_free (sortentstables);
                sortentstables = (DxfSortentsTable *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the \c id_code from a DXF \c SORTENTSTABLE object.
 *
 * \return \c id_code.
 */
int
dxf_sortentstable_get_id_code
(
        DxfSortentsTable *sortentstable
                /*!< a pointer to a DXF \c SORTENTSTABLE object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sortentstable == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (sortentstable->id_code < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sortentstable->id_code);
}


/*!
 * \brief Set the \c id_code for a DXF \c SORTENTSTABLE object.
 */
DxfSortentsTable *
dxf_sortentstable_set_id_code
(
        DxfSortentsTable *sortentstable,
                /*!< a pointer to a DXF \c SORTENTSTABLE object. */
        int id_code
                /*!< the \c id_code to be set for the entity.\n
                 * This is to be an unique (sequential) number in the
                 * DXF file. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sortentstable == NULL)
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
        sortentstable->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sortentstable);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_soft from a DXF 
 * \c SORTENTSTABLE object.
 *
 * \return pointer to the \c dictionary_owner_soft.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_sortentstable_get_dictionary_owner_soft
(
        DxfSortentsTable *sortentstable
                /*!< a pointer to a DXF \c SORTENTSTABLE object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sortentstable == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (sortentstable->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (sortentstable->dictionary_owner_soft));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_soft for a DXF
 * \c SORTENTSTABLE object.
 */
DxfSortentsTable *
dxf_sortentstable_set_dictionary_owner_soft
(
        DxfSortentsTable *sortentstable,
                /*!< a pointer to a DXF \c SORTENTSTABLE object. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the \c
                 * dictionary_owner_soft for the object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sortentstable == NULL)
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
        sortentstable->dictionary_owner_soft = strdup (dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sortentstable);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_hard from a DXF 
 * \c SORTENTSTABLE object.
 *
 * \return pointer to the \c dictionary_owner_hard.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_sortentstable_get_dictionary_owner_hard
(
        DxfSortentsTable *sortentstable
                /*!< a pointer to a DXF \c SORTENTSTABLE object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sortentstable == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (sortentstable->dictionary_owner_hard ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (sortentstable->dictionary_owner_hard));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_hard for a DXF
 * \c SORTENTSTABLE object.
 */
DxfSortentsTable *
dxf_sortentstable_set_dictionary_owner_hard
(
        DxfSortentsTable *sortentstable,
                /*!< a pointer to a DXF \c SORTENTSTABLE object. */
        char *dictionary_owner_hard
                /*!< a string containing the pointer to the \c
                 * dictionary_owner_hard for the object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sortentstable == NULL)
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
        sortentstable->dictionary_owner_hard = strdup (dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sortentstable);
}


/*!
 * \brief Get the pointer to the \c block_owner from a DXF 
 * \c SORTENTSTABLE object.
 *
 * \return pointer to the \c block_owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_sortentstable_get_block_owner
(
        DxfSortentsTable *sortentstable
                /*!< a pointer to a DXF \c SORTENTSTABLE object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sortentstable == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (sortentstable->block_owner ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (sortentstable->block_owner));
}


/*!
 * \brief Set the pointer to the \c block_owner for a DXF
 * \c SORTENTSTABLE object.
 */
DxfSortentsTable *
dxf_sortentstable_set_block_owner
(
        DxfSortentsTable *sortentstable,
                /*!< a pointer to a DXF \c SORTENTSTABLE object. */
        char *block_owner
                /*!< a string containing the pointer to the \c
                 * block_owner for the object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sortentstable == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (block_owner == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        sortentstable->block_owner = strdup (block_owner);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sortentstable);
}


/*!
 * \brief Get the pointer to the \c entity_owner from a DXF 
 * \c SORTENTSTABLE object.
 *
 * \return pointer to the \c entity_owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
DxfChar *
dxf_sortentstable_get_entity_owner
(
        DxfSortentsTable *sortentstable
                /*!< a pointer to a DXF \c SORTENTSTABLE object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sortentstable == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (sortentstable->entity_owner ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (sortentstable->entity_owner->value ==  NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found in a member.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sortentstable->entity_owner);
}


/*!
 * \brief Set the pointer to the \c entity_owner for a DXF
 * \c SORTENTSTABLE object.
 */
DxfSortentsTable *
dxf_sortentstable_set_entity_owner
(
        DxfSortentsTable *sortentstable,
                /*!< a pointer to a DXF \c SORTENTSTABLE object. */
        DxfChar *entity_owner
                /*!< a pointer to the \c entity_owner for the object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sortentstable == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (entity_owner == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (entity_owner->value == NULL)
        {
                fprintf (stderr,
                  (_("warning in %s () a NULL pointer was found in a member.\n")),
                  __FUNCTION__);
        }
        sortentstable->entity_owner = entity_owner;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sortentstable);
}


/*!
 * \brief Get the pointer to the last \c entity_owner from a linked list
 * of \c entity_owner.
 *
 * \return pointer to the last \c entity_owner.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfChar *
dxf_sortentstable_get_last_entity_owner
(
        DxfChar *entity_owner
                /*!< a pointer to a \c entity_owner. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (entity_owner == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (entity_owner->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfChar *) entity_owner);
        }
        DxfChar *iter = (DxfChar *) entity_owner->next;
        while (iter->next != NULL)
        {
                iter = (DxfChar *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfChar *) iter);
}


/*!
 * \brief Get the pointer to the \c value stored in a \c entity_owner
 * from a DXF \c SORTENTSTABLE object.
 *
 * \return pointer to the \c value in the \c entity_owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_sortentstable_get_entity_owner_value
(
        DxfChar *entity_owner
                /*!< a pointer to a \c entity_owner of a DXF
                 * \c SORTENTSTABLE object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (entity_owner == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (entity_owner->value ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in a member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (entity_owner->value));
}


/*!
 * \brief Set the pointer to a \c value in a particular \c entity_owner
 * for a DXF \c SORTENTSTABLE object.
 */
DxfChar *
dxf_sortentstable_set_entity_owner_value
(
        DxfChar *entity_owner,
                /*!< a pointer to a particular \c entity_owner for the
                 * object (a single linked list). */
        char *value
                /*!< a pointer to a \c value (string). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (entity_owner == NULL)
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
        entity_owner->value = value;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (entity_owner);
}


/*!
 * \brief Get the \c length of the \c value stored in a \c entity_owner
 * from a DXF \c SORTENTSTABLE object.
 *
 * \return \c length the \c value in the \c entity_owner.
 */
int
dxf_sortentstable_get_entity_owner_length
(
        DxfChar *entity_owner
                /*!< a pointer to a DXF \c SORTENTSTABLE object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (entity_owner == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (entity_owner->length);
}


/*!
 * \brief Set the \c length of a \c value in a particular
 * \c entity_owner for a DXF \c SORTENTSTABLE object.
 */
DxfChar *
dxf_sortentstable_set_entity_owner_length
(
        DxfChar *entity_owner,
                /*!< a pointer to a particular \c entity_owner for the
                 * object (a single linked list). */
        int length
                /*!< \c length. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (entity_owner == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        entity_owner->length = length;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (entity_owner);
}


/*!
 * \brief Get the pointer to the next \c entity_owner from a
 * \c entity_owner.
 *
 * \return pointer to the next \c entity_owner.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfChar *
dxf_sortentstable_get_next_entity_owner
(
        DxfChar *entity_owner
                /*!< a pointer to a \c entity_owner. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (entity_owner == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (entity_owner->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfChar *) entity_owner->next);
}


/*!
 * \brief Set the pointer to the next \c entity_owner for a
 * \c entity_owner.
 */
DxfChar *
dxf_sortentstable_set_next_entity_owner
(
        DxfChar *entity_owner,
                /*!< a pointer to a \c entity_owner. */
        DxfChar *next
                /*!< a pointer to the next \c entity_owner. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (entity_owner == NULL)
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
        entity_owner->next = (struct DxfChar *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (entity_owner);
}


/*!
 * \brief Get the \c sort_handle from a DXF \c SORTENTSTABLE object.
 *
 * \return \c sort_handle.
 */
DxfInt *
dxf_sortentstable_get_sort_handle
(
        DxfSortentsTable *sortentstable
                /*!< a pointer to a DXF \c SORTENTSTABLE object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sortentstable == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (sortentstable->sort_handle == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sortentstable->sort_handle);
}


/*!
 * \brief Set the \c sort_handle for a DXF \c SORTENTSTABLE object.
 */
DxfSortentsTable *
dxf_sortentstable_set_sort_handle
(
        DxfSortentsTable *sortentstable,
                /*!< a pointer to a DXF \c SORTENTSTABLE object. */
        DxfInt *sort_handle
                /*!< the \c sort_handle to be set for the object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sortentstable == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (sort_handle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        sortentstable->sort_handle = sort_handle;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sortentstable);
}


/*!
 * \brief Get the \c value from the \c sort_handle member of a DXF
 * \c SORTENTSTABLE object.
 *
 * \return \c value from the \c sort_handle.
 */
int
dxf_sortentstable_get_sort_handle_value
(
        DxfInt *sort_handle
                /*!< a pointer to a \c sort_handle member. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sort_handle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sort_handle->value);
}


/*!
 * \brief Set the \c value of a \c sort_handle for a DXF
 * \c SORTENTSTABLE object.
 */
DxfInt *
dxf_sortentstable_set_sort_handle_value
(
        DxfInt *sort_handle,
                /*!< the \c sort_handle to be set for the object. */
        int value
                /*!< the \c value to be set. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sort_handle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        sort_handle->value = value;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sort_handle);
}


/*!
 * \brief Get the pointer to the next \c sort_handle from a
 * \c sort_handle.
 *
 * \return pointer to the next \c sort_handle.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfInt *
dxf_sortentstable_get_next_sort_handle
(
        DxfInt *sort_handle
                /*!< a pointer to a DXF \c sort_handle. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sort_handle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (sort_handle->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfInt *) sort_handle->next);
}


/*!
 * \brief Set the pointer to the next \c sort_handle for a
 * \c sort_handle.
 */
DxfInt *
dxf_sortentstable_set_next_sort_handle
(
        DxfInt *sort_handle,
                /*!< a pointer to a \c sort_handle entity. */
        DxfInt *next
                /*!< a pointer to the next \c sort_handle. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sort_handle == NULL)
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
        sort_handle->next = (struct DxfInt *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sort_handle);
}


/*!
 * \brief Get the pointer to the last \c sort_handle from a linked list
 * of \c sort_handles.
 *
 * \return pointer to the last \c sort_handle.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfInt *
dxf_sortentstable_get_last_sort_handle
(
        DxfInt *sort_handle
                /*!< a pointer to a \c sort_handle. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sort_handle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (sort_handle->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfInt *) sort_handle);
        }
        DxfInt *iter = (DxfInt *) sort_handle->next;
        while (iter->next != NULL)
        {
                iter = (DxfInt *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfInt *) iter);
}


/*!
 * \brief Get the pointer to the next \c SORTENTSTABLE object from a DXF
 * \c ARC SORTENTSTABLE object
 *
 * \return pointer to the next \c SORTENTSTABLE object.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfSortentsTable *
dxf_sortentstable_get_next
(
        DxfSortentsTable *sortentstable
                /*!< a pointer to a DXF \c SORTENTSTABLE object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sortentstable == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (sortentstable->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfSortentsTable *) sortentstable->next);
}


/*!
 * \brief Set the pointer to the next \c SORTENTSTABLE object for a DXF
 * \c SORTENTSTABLE object.
 */
DxfSortentsTable *
dxf_sortentstable_set_next
(
        DxfSortentsTable *sortentstable,
                /*!< a pointer to a DXF \c SORTENTSTABLE object. */
        DxfSortentsTable *next
                /*!< a pointer to the next \c SORTENTSTABLE object for
                 * the \c SORTENTSTABLE object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sortentstable == NULL)
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
        sortentstable->next = (struct DxfSortentsTable *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (sortentstable);
}


/*!
 * \brief Get the pointer to the last \c SORTENTSTABLE object from a
 * linked list of DXF \c SORTENTSTABLE objects.
 *
 * \return pointer to the last \c SORTENTSTABLE object.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfSortentsTable *
dxf_sortentstable_get_last
(
        DxfSortentsTable *sortentstable
                /*!< a pointer to a DXF \c SORTENTSTABLE object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (sortentstable == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (sortentstable->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfSortentsTable *) sortentstable);
        }
        DxfSortentsTable *iter = (DxfSortentsTable *) sortentstable->next;
        while (iter->next != NULL)
        {
                iter = (DxfSortentsTable *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfSortentsTable *) iter);
}


/* EOF*/
