/*!
 * \file sortentstable.c
 *
 * \author Copyright (C) 2015, 2017 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF sortentstable object (\c SORTENTSTABLE).
 *
 * \version The \c SORTENTSTABLE object was introduced in DXF R14.
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
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
 * \version According to DXF R14.
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
 * allocated memory when succesful.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
 * \version According to DXF R14.
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
        int i;

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
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                sortentstable->entity_owner[i] = strdup ("");
                sortentstable->sort_handle[i] = 0;
        }
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
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
 * \version According to DXF R14.
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
                sortentstable = dxf_sortentstable_new ();
                sortentstable = dxf_sortentstable_init (sortentstable);
        }
        i = 0;
        j = 0;
        k = 0;
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
                        fscanf (fp->fp, "%x\n", &sortentstable->id_code);
                }
                if ((strcmp (temp_string, "5") == 0)
                  && (i > 0))
                {
                        /* Now follows a string containing a Sort handle
                         * (zero or more entries may exist). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", &sortentstable->sort_handle[i]);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
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
                        fscanf (fp->fp, "%s\n", sortentstable->dictionary_owner_soft);
                        j++;
                }
                else if ((strcmp (temp_string, "330") == 0)
                  && (j > 0))
                {
                        /* Now follows a string containing a soft pointer
                         * ID/handle to owner (currently only the
                         * *MODEL_SPACE or *PAPER_SPACE blocks). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", sortentstable->block_owner);
                        j++;
                        /*! \todo Check for overrun of array index. */
                }
                else if (strcmp (temp_string, "331") == 0)
                {
                        /* Now follows a string containing a soft pointer
                         * ID/handle to an entity (zero or more entries
                         * may exist). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", sortentstable->entity_owner[k]);
                        k++;
                        /*! \todo Check for overrun of array index. */
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", sortentstable->dictionary_owner_hard);
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
        return (sortentstable);
}


/*!
 * \brief Write DXF output to a file for a DXF \c SORTENTSTABLE object.
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
        int i;

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
        i = 0;
        while (strlen (sortentstable->entity_owner[i]) > 0)
        {
                fprintf (fp->fp, "331\n%s\n", sortentstable->entity_owner[i]);
                i++;
                /*! \todo Check for overrun of array index. */
        }
        for (i = 1; i < DXF_MAX_PARAM; i++)
        {
                /* For the stort_Handle index i has a range from 1 to
                 * (DXF_MAX_PARAM - 1). */
                fprintf (fp->fp, "  5\n%x\n", sortentstable->sort_handle[i]);
                /*! \bug We have to find a way to get an idea how many
                 * handles contain a valid value, this for-loop will
                 * lead to inflated DXF files and structures. */
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
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
 * \version According to DXF R14.
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
        int i;

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
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                free (sortentstable->entity_owner[i]);
        }
        free (sortentstable);
        sortentstable = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a chain of DXF \c SORTENTSTABLE
 * objects and all their data fields.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
 * \version According to DXF R14.
 */
void
dxf_sortentstable_free_chain
(
        DxfSortentsTable *sortentstables
                /*!< a pointer to the chain of DXF \c SORTENTSTABLE
                 * objects. */
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
                struct DxfSortentsTable *iter = sortentstables->next;
                dxf_sortentstable_free (sortentstables);
                sortentstables = (DxfSortentsTable *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/* EOF*/
