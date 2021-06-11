/*!
 * \file mlinestyle.c
 *
 * \author Copyright (C) 2015, 2017, 2018, 2019, 2020, 2021
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF mlinestyle object (\c MLINESTYLE).
 *
 * \since The \c MLINESTYLE object was introduced in DXF R13.
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
 * For more details see http://www.autodesk.com .
 * <hr>
 */


#include "mlinestyle.h"


/*!
 * \brief Allocate memory for a \c DxfMlinestyle.
 *
 * Fill the memory contents with zeros.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfMlinestyle *
dxf_mlinestyle_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfMlinestyle *mlinestyle = NULL;
        size_t size;

        size = sizeof (DxfMlinestyle);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((mlinestyle = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfMlinestyle struct.\n")),
                  __FUNCTION__);
                mlinestyle = NULL;
        }
        else
        {
                memset (mlinestyle, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mlinestyle);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c MLINESTYLE
 * object.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfMlinestyle *
dxf_mlinestyle_init
(
        DxfMlinestyle *mlinestyle
                /*!< DXF \c MLINESTYLE object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        /* Do some basic checks. */
        if (mlinestyle == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                mlinestyle = dxf_mlinestyle_new ();
        }
        if (mlinestyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfMlinestyle struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dxf_mlinestyle_set_name (mlinestyle, strdup (""));
        dxf_mlinestyle_set_description (mlinestyle, strdup (""));
        dxf_mlinestyle_set_id_code (mlinestyle, 0);
        dxf_mlinestyle_set_dictionary_owner_soft (mlinestyle, strdup (""));
        dxf_mlinestyle_set_dictionary_owner_hard (mlinestyle, strdup (""));
        dxf_mlinestyle_set_start_angle (mlinestyle, 0.0);
        dxf_mlinestyle_set_end_angle (mlinestyle, 0.0);
        dxf_mlinestyle_set_color (mlinestyle, DXF_COLOR_BYLAYER);
        dxf_mlinestyle_set_flags (mlinestyle, 0);
        dxf_mlinestyle_set_number_of_elements (mlinestyle, 0);
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                dxf_mlinestyle_set_ith_element_linetype (mlinestyle, strdup (""), i);
                dxf_mlinestyle_set_ith_element_offset (mlinestyle, 0.0, i);
                dxf_mlinestyle_set_ith_element_color (mlinestyle, 0, i);
        }
        dxf_mlinestyle_set_next (mlinestyle, NULL);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mlinestyle);
}


/*!
 * \brief Read data from a DXF file into a DXF \c MLINESTYLE object.
 *
 * The last line read from file contained the string "MLINESTYLE". \n
 * Now follows some data for the \c MLINESTYLE, to be terminated with a
 * "  0" string announcing the following entity, or the end of the
 * \c ENTITY section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c mlinestyle. \n
 *
 * \return a pointer to \c mlinestyle.
 */
DxfMlinestyle *
dxf_mlinestyle_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfMlinestyle *mlinestyle
                /*!< DXF \c MLINESTYLE object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *temp_string = NULL;
        int i;

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
        if (mlinestyle == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                mlinestyle = dxf_mlinestyle_init (mlinestyle);
        }
        i = 0;
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
                if (strcmp (temp_string, "2") == 0)
                {
                        /* Now follows a string containing a mlinestyle
                         * name string. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, mlinestyle->name);
                }
                if (strcmp (temp_string, "3") == 0)
                {
                        /* Now follows a string containing a description
                         * string. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, mlinestyle->description);
                }
                if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", (uint *) &mlinestyle->id_code);
                }
                if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing an element
                         * linetype. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, mlinestyle->element_linetype[i]);
                        i++;
                }
                if (strcmp (temp_string, "49") == 0)
                {
                        /* Now follows a string containing an element
                         * offset value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mlinestyle->element_offset[i]);
                }
                if (strcmp (temp_string, "51") == 0)
                {
                        /* Now follows a string containing a start angle
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mlinestyle->start_angle);
                }
                if (strcmp (temp_string, "52") == 0)
                {
                        /* Now follows a string containing a end angle
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &mlinestyle->end_angle);
                }
                if ((strcmp (temp_string, "62") == 0)
                  && (i == 0))
                {
                        /* Now follows a string containing a fill color
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &mlinestyle->color);
                        i++;
                }
                if ((strcmp (temp_string, "62") == 0)
                  && (i > 0))
                {
                        /* Now follows a string containing an element
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &mlinestyle->element_color[i]);
                }
                if (strcmp (temp_string, "70") == 0)
                {
                        /* Now follows a string containing a flags
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &mlinestyle->flags);
                }
                if (strcmp (temp_string, "71") == 0)
                {
                        /* Now follows a string containing a number of
                         * elements value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &mlinestyle->number_of_elements);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if (strcmp (temp_string, "AcDbMlineStyle") != 0)
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
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, mlinestyle->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, mlinestyle->dictionary_owner_hard);
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
        return (mlinestyle);
}


/*!
 * \brief Write DXF output to a file for a DXF \c MLINESTYLE object.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 *
 * \warning This entity requires AutoCAD version R13 or higher.
 * When the \c follow_strict_version_rules flag is set to \c TRUE in the
 * \c DxfFile struct, this entity will be skipped from file.
 * When the \c follow_strict_version_rules flag is set to \c FALSE in the
 * \c DxfFile struct, libdxf will write this entity to file and report
 * with a warning message to \c stderr.
 */
int
dxf_mlinestyle_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfMlinestyle *mlinestyle
                /*!< DXF \c MLINESTYLE object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("MLINESTYLE");
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
        if (mlinestyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if ((fp->acad_version_number < AutoCAD_13)
          && (fp->follow_strict_version_rules))
        {
                fprintf (stderr,
                  (_("Error in %s () illegal DXF version for this %s entity with id-code: %x.\n")),
                  __FUNCTION__, dxf_entity_name, dxf_mlinestyle_get_id_code (mlinestyle));
                return (EXIT_FAILURE);
        }
        else
        {
                fprintf (stderr,
                  (_("Warning in %s () illegal DXF version for this %s entity with id-code: %x.\n")),
                  __FUNCTION__, dxf_entity_name, dxf_mlinestyle_get_id_code (mlinestyle));
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (dxf_mlinestyle_get_id_code (mlinestyle) != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", dxf_mlinestyle_get_id_code (mlinestyle));
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
        if ((strcmp (dxf_mlinestyle_get_dictionary_owner_soft (mlinestyle), "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", dxf_mlinestyle_get_dictionary_owner_soft (mlinestyle));
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (dxf_mlinestyle_get_dictionary_owner_hard (mlinestyle), "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", dxf_mlinestyle_get_dictionary_owner_hard (mlinestyle));
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbMlineStyle\n");
        }
        fprintf (fp->fp, "  2\n%s\n", dxf_mlinestyle_get_name (mlinestyle));
        fprintf (fp->fp, " 70\n%d\n", dxf_mlinestyle_get_flags (mlinestyle));
        fprintf (fp->fp, "  3\n%s\n", dxf_mlinestyle_get_description (mlinestyle));
        fprintf (fp->fp, " 62\n%d\n", dxf_mlinestyle_get_color (mlinestyle));
        fprintf (fp->fp, " 51\n%lf\n", dxf_mlinestyle_get_start_angle (mlinestyle));
        fprintf (fp->fp, " 52\n%lf\n", dxf_mlinestyle_get_end_angle (mlinestyle));
        fprintf (fp->fp, " 71\n%d\n", dxf_mlinestyle_get_number_of_elements (mlinestyle));
        for (i = 1; i < DXF_MAX_PARAM; i++)
        {
                fprintf (fp->fp, " 49\n%lf\n", dxf_mlinestyle_get_ith_element_offset (mlinestyle, i));
                fprintf (fp->fp, " 62\n%d\n", dxf_mlinestyle_get_ith_element_color (mlinestyle, i));
                fprintf (fp->fp, "  6\n%s\n", dxf_mlinestyle_get_ith_element_linetype (mlinestyle, i));
        }
        /* Clean up. */
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c MLINESTYLE and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_mlinestyle_free
(
        DxfMlinestyle *mlinestyle
                /*!< Pointer to the memory occupied by the DXF
                 * \c MLINESTYLE object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        /* Do some basic checks. */
        if (mlinestyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mlinestyle->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (dxf_mlinestyle_get_dictionary_owner_soft (mlinestyle));
        free (dxf_mlinestyle_get_dictionary_owner_hard (mlinestyle));
        free (dxf_mlinestyle_get_name (mlinestyle));
        free (dxf_mlinestyle_get_description (mlinestyle));
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                free (dxf_mlinestyle_get_ith_element_linetype (mlinestyle, 1));
        }
        free (mlinestyle);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c MLINESTYLE objects and all their data fields.
 */
void
dxf_mlinestyle_free_list
(
        DxfMlinestyle *mlinestyles
                /*!< a pointer to the single linked list of DXF
                 * \c MLINESTYLE objects. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (mlinestyles == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (mlinestyles != NULL)
        {
                DxfMlinestyle *iter = (DxfMlinestyle *) mlinestyles->next;
                dxf_mlinestyle_free (mlinestyles);
                mlinestyles = (DxfMlinestyle *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the ID code from a DXF \c MLINESTYLE object.
 *
 * \return \c id_code.
 */
int
dxf_mlinestyle_get_id_code
(
        DxfMlinestyle *mlinestyle
                /*!< a pointer to a DXF \c MLINESTYLE object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mlinestyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mlinestyle->id_code < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mlinestyle->id_code);
}


/*!
 * \brief Set the \c id_code for a DXF \c MLINESTYLE object.
 */
DxfMlinestyle *
dxf_mlinestyle_set_id_code
(
        DxfMlinestyle *mlinestyle,
                /*!< a pointer to a DXF \c MLINESTYLE object. */
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
        if (mlinestyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (id_code < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mlinestyle->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mlinestyle);
}


/*!
 * \brief Get the soft pointer to the dictionary owner from a DXF 
 * \c MLINESTYLE object.
 *
 * \return soft pointer to the dictionary owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_mlinestyle_get_dictionary_owner_soft
(
        DxfMlinestyle *mlinestyle
                /*!< a pointer to a DXF \c MLINESTYLE object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mlinestyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mlinestyle->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mlinestyle->dictionary_owner_soft));
}


/*!
 * \brief Set the pointer to the dictionary_owner_soft for a DXF
 * \c MLINESTYLE object.
 */
DxfMlinestyle *
dxf_mlinestyle_set_dictionary_owner_soft
(
        DxfMlinestyle *mlinestyle,
                /*!< a pointer to a DXF \c MLINESTYLE object. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the
                 * dictionary_owner_soft for the object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mlinestyle == NULL)
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
        mlinestyle->dictionary_owner_soft = strdup (dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mlinestyle);
}


/*!
 * \brief Get the hard pointer to the dictionary owner from a DXF 
 * \c MLINESTYLE object.
 *
 * \return hard pointer to the dictionary owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_mlinestyle_get_dictionary_owner_hard
(
        DxfMlinestyle *mlinestyle
                /*!< a pointer to a DXF \c MLINESTYLE object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mlinestyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mlinestyle->dictionary_owner_hard ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mlinestyle->dictionary_owner_hard));
}


/*!
 * \brief Set the pointer to the dictionary_owner_hard for a DXF
 * \c MLINESTYLE object.
 */
DxfMlinestyle *
dxf_mlinestyle_set_dictionary_owner_hard
(
        DxfMlinestyle *mlinestyle,
                /*!< a pointer to a DXF \c MLINESTYLE object. */
        char *dictionary_owner_hard
                /*!< a string containing the pointer to the
                 * dictionary_owner_hard for the object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mlinestyle == NULL)
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
        mlinestyle->dictionary_owner_hard = strdup (dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mlinestyle);
}


/*!
 * \brief Get the \c name from a DXF \c MLINESTYLE object.
 *
 * \return \c name.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_mlinestyle_get_name
(
        DxfMlinestyle *mlinestyle
                /*!< a pointer to a DXF \c MLINESTYLE object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mlinestyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mlinestyle->name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mlinestyle->name));
}


/*!
 * \brief Set the \c name for a DXF \c MLINESTYLE object.
 */
DxfMlinestyle *
dxf_mlinestyle_set_name
(
        DxfMlinestyle *mlinestyle,
                /*!< a pointer to a DXF \c MLINESTYLE object. */
        char *name
                /*!< a string containing the \c name for the object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mlinestyle == NULL)
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
        mlinestyle->name = strdup (name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mlinestyle);
}


/*!
 * \brief Get the \c description from a DXF \c MLINESTYLE object.
 *
 * \return \c description.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_mlinestyle_get_description
(
        DxfMlinestyle *mlinestyle
                /*!< a pointer to a DXF \c MLINESTYLE object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mlinestyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mlinestyle->description ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mlinestyle->description));
}


/*!
 * \brief Set the \c description for a DXF \c MLINESTYLE object.
 */
DxfMlinestyle *
dxf_mlinestyle_set_description
(
        DxfMlinestyle *mlinestyle,
                /*!< a pointer to a DXF \c MLINESTYLE object. */
        char *description
                /*!< a string containing the \c description for the
                 * object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mlinestyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (description == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mlinestyle->description = strdup (description);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mlinestyle);
}


/*!
 * \brief Get the \c element_linetype from a DXF \c MLINESTYLE object.
 *
 * \return \c element_linetype.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_mlinestyle_get_ith_element_linetype
(
        DxfMlinestyle *mlinestyle,
                /*!< a pointer to a DXF \c MLINESTYLE object. */
        int i
                /*!< an index for the array of element linetypes. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mlinestyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (i < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative array index was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (i > DXF_MAX_PARAM)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range array index was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mlinestyle->element_linetype[i] ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mlinestyle->element_linetype[i]));
}


/*!
 * \brief Set the \c element_linetype for a DXF \c MLINESTYLE object.
 */
DxfMlinestyle *
dxf_mlinestyle_set_ith_element_linetype
(
        DxfMlinestyle *mlinestyle,
                /*!< a pointer to a DXF \c MLINESTYLE object. */
        char *element_linetype,
                /*!< a string containing the \c element_linetype for the
                 * object. */
        int i
                /*!< an index for the array of element linetypes. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mlinestyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (element_linetype == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (i < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative array index was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (i > DXF_MAX_PARAM)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range array index was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mlinestyle->element_linetype[i] = strdup (element_linetype);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mlinestyle);
}


/*!
 * \brief Get the \c element_offset array of a DXF \c MLINESTYLE object.
 *
 * \return pointer to the \c element_offset array.
 */
double
dxf_mlinestyle_get_element_offset
(
        DxfMlinestyle *mlinestyle
                /*!< a pointer to a DXF \c MLINESTYLE object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (mlinestyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mlinestyle->element_offset == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (*(mlinestyle->element_offset));
}


/*!
 * \brief Set the pointer of \c element_parameters array of a DXF
 * \c MLINESTYLE object.
 *
 * \return a pointer to \c mline when successful, or \c NULL when an
 * error occurred.
 */
DxfMlinestyle *
dxf_mlinestyle_set_element_offset
(
        DxfMlinestyle *mlinestyle,
                /*!< a pointer to a DXF \c MLINESTYLE object. */
        double *element_offset
                /*!< the pointer to the \c element_offset array to
                 * be set for the object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mlinestyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (element_offset == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        *(mlinestyle->element_offset) = *element_offset;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mlinestyle);
}


/*!
 * \brief Get the i-th \c element_offset from a DXF \c MLINESTYLE object.
 *
 * \return \c element_offset.
 */
double
dxf_mlinestyle_get_ith_element_offset
(
        DxfMlinestyle *mlinestyle,
                /*!< a pointer to a DXF \c MLINESTYLE object. */
        int i
                /*!< an index for the array of element offsets. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mlinestyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (i < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative array index was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (i > DXF_MAX_PARAM)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range array index was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mlinestyle->element_offset[i]);
}


/*!
 * \brief Set the i-th \c element_offset for a DXF \c MLINESTYLE object.
 */
DxfMlinestyle *
dxf_mlinestyle_set_ith_element_offset
(
        DxfMlinestyle *mlinestyle,
                /*!< a pointer to a DXF \c MLINESTYLE object. */
        double element_offset,
                /*!< a double containing the i-th \c element_offset for
                 * the object. */
        int i
                /*!< an index for the array of element offsets. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mlinestyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (i < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative array index was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (i > DXF_MAX_PARAM)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range array index was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mlinestyle->element_offset[i] = element_offset;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mlinestyle);
}


/*!
 * \brief Get the \c start_angle from a DXF \c MLINESTYLE object.
 *
 * \return \c start_angle.
 */
double
dxf_mlinestyle_get_start_angle
(
        DxfMlinestyle *mlinestyle
                /*!< a pointer to a DXF \c MLINESTYLE object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mlinestyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mlinestyle->start_angle);
}


/*!
 * \brief Set the \c start_angle for a DXF \c MLINESTYLE object.
 */
DxfMlinestyle *
dxf_mlinestyle_set_start_angle
(
        DxfMlinestyle *mlinestyle,
                /*!< a pointer to a DXF \c MLINESTYLE object. */
        double start_angle
                /*!< the \c start_angle to be set for the object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mlinestyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mlinestyle->start_angle = start_angle;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mlinestyle);
}


/*!
 * \brief Get the \c end_angle from a DXF \c MLINESTYLE object.
 *
 * \return \c end_angle.
 */
double
dxf_mlinestyle_get_end_angle
(
        DxfMlinestyle *mlinestyle
                /*!< a pointer to a DXF \c MLINESTYLE object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mlinestyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mlinestyle->end_angle);
}


/*!
 * \brief Set the \c end_angle for a DXF \c MLINESTYLE object.
 */
DxfMlinestyle *
dxf_mlinestyle_set_end_angle
(
        DxfMlinestyle *mlinestyle,
                /*!< a pointer to a DXF \c MLINESTYLE object. */
        double end_angle
                /*!< the \c end_angle to be set for the object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mlinestyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mlinestyle->end_angle = end_angle;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mlinestyle);
}


/*!
 * \brief Get the \c color from a DXF \c MLINESTYLE object.
 *
 * \return \c color.
 */
int
dxf_mlinestyle_get_color
(
        DxfMlinestyle *mlinestyle
                /*!< a pointer to a DXF \c MLINESTYLE object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mlinestyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mlinestyle->color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mlinestyle->color);
}


/*!
 * \brief Set the color for a DXF \c MLINESTYLE object.
 */
DxfMlinestyle *
dxf_mlinestyle_set_color
(
        DxfMlinestyle *mlinestyle,
                /*!< a pointer to a DXF \c MLINESTYLE object. */
        int color
                /*!< the color to be set for the object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mlinestyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        mlinestyle->color = color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mlinestyle);
}


/*!
 * \brief Get the i-th \c element_color from a DXF \c MLINESTYLE object.
 *
 * \return \c element_color.
 */
int
dxf_mlinestyle_get_ith_element_color
(
        DxfMlinestyle *mlinestyle,
                /*!< a pointer to a DXF \c MLINESTYLE object. */
        int i
                /*!< an index for the array of element colors. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mlinestyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (i < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative array index was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (i > DXF_MAX_PARAM)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range array index was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mlinestyle->element_color[i]);
}


/*!
 * \brief Set the i-th \c element_color for a DXF \c MLINESTYLE object.
 */
DxfMlinestyle *
dxf_mlinestyle_set_ith_element_color
(
        DxfMlinestyle *mlinestyle,
                /*!< a pointer to a DXF \c MLINESTYLE object. */
        int element_color,
                /*!< an integer containing the \c color for the object. */
        int i
                /*!< an index for the array of element colors. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mlinestyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (element_color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (i < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative array index was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (i > DXF_MAX_PARAM)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range array index was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mlinestyle->element_color[i] = element_color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mlinestyle);
}


/*!
 * \brief Get the \c flags from a DXF \c MLINESTYLE object.
 *
 * \return \c flags.
 */
int
dxf_mlinestyle_get_flags
(
        DxfMlinestyle *mlinestyle
                /*!< a pointer to a DXF \c MLINESTYLE object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mlinestyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mlinestyle->flags < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mlinestyle->flags > 2047)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mlinestyle->flags);
}


/*!
 * \brief Set the \c flags for a DXF \c MLINESTYLE object.
 */
DxfMlinestyle *
dxf_mlinestyle_set_flags
(
        DxfMlinestyle *mlinestyle,
                /*!< a pointer to a DXF \c MLINESTYLE object. */
        int flags
                /*!< the \c flags to be set for the object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mlinestyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (flags < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (flags > 2047)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mlinestyle->flags = flags;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mlinestyle);
}


/*!
 * \brief Test if the \c mlinestyle has its \c flag set to fill on.
 *
 * \return \c TRUE when the \c flag is set to fill on,
 * or \c FALSE when the \c flag is not set to fill on.
 */
int
dxf_mlinestyle_flag_is_fill_on
(
        DxfMlinestyle *mlinestyle
                /*!< DXF \c MLINESTYLE object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mlinestyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (DXF_CHECK_BIT (mlinestyle->flags, 0));
}


/*!
 * \brief Test if the \c mlinestyle has its \c flag set to display
 * miters.
 *
 * \return \c TRUE when the \c flag is set to display miters,
 * or \c FALSE when the \c flag is not set to dispaly miters.
 */
int
dxf_mlinestyle_flag_is_display_miters
(
        DxfMlinestyle *mlinestyle
                /*!< DXF \c MLINESTYLE object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mlinestyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (DXF_CHECK_BIT (mlinestyle->flags, 1));
}


/*!
 * \brief Test if the \c mlinestyle has its \c flag set to
 * \c start_square_end_cap.
 *
 * \return \c TRUE when the \c flag is set to \c start_square_end_cap,
 * or \c FALSE when the \c flag is not set to \c start_square_end_cap.
 */
int
dxf_mlinestyle_flag_is_start_square_end_cap
(
        DxfMlinestyle *mlinestyle
                /*!< DXF \c MLINESTYLE object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mlinestyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (DXF_CHECK_BIT (mlinestyle->flags, 4));
}


/*!
 * \brief Test if the \c mlinestyle has its \c flag set to
 * \c start_inner_arcs_cap.
 *
 * \return \c TRUE when the \c flag is set to \c start_inner_arcs_cap,
 * or \c FALSE when the \c flag is not set to \c start_inner_arcs_cap.
 */
int
dxf_mlinestyle_flag_is_start_inner_arcs_cap
(
        DxfMlinestyle *mlinestyle
                /*!< DXF \c MLINESTYLE object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mlinestyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (DXF_CHECK_BIT (mlinestyle->flags, 5));
}


/*!
 * \brief Test if the \c mlinestyle has its \c flag set to
 * \c start_round_outer_arcs_cap.
 *
 * \return \c TRUE when the \c flag is set to \c start_round_outer_arcs_cap,
 * or \c FALSE when the \c flag is not set to \c start_roundouter_arcs_cap.
 */
int
dxf_mlinestyle_flag_is_start_round_outer_arcs_cap
(
        DxfMlinestyle *mlinestyle
                /*!< DXF \c MLINESTYLE object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mlinestyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (DXF_CHECK_BIT (mlinestyle->flags, 6));
}


/*!
 * \brief Test if the \c mlinestyle has its \c flag set to
 * \c end_square_end_cap.
 *
 * \return \c TRUE when the \c flag is set to \c end_square_end_cap,
 * or \c FALSE when the \c flag is not set to \c end_square_end_cap.
 */
int
dxf_mlinestyle_flag_is_end_square_end_cap
(
        DxfMlinestyle *mlinestyle
                /*!< DXF \c MLINESTYLE object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mlinestyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (DXF_CHECK_BIT (mlinestyle->flags, 8));
}


/*!
 * \brief Test if the \c mlinestyle has its \c flag set to
 * \c end_inner_arcs_cap.
 *
 * \return \c TRUE when the \c flag is set to \c end_inner_arcs_cap,
 * or \c FALSE when the \c flag is not set to \c end_inner_arcs_cap.
 */
int
dxf_mlinestyle_flag_is_end_inner_arcs_cap
(
        DxfMlinestyle *mlinestyle
                /*!< DXF \c MLINESTYLE object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mlinestyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (DXF_CHECK_BIT (mlinestyle->flags, 9));
}


/*!
 * \brief Test if the \c mlinestyle has its \c flag set to
 * \c end_round_outer_arcs_cap.
 *
 * \return \c TRUE when the \c flag is set to \c end_round_outer_arcs_cap,
 * or \c FALSE when the \c flag is not set to \c end_roundouter_arcs_cap.
 */
int
dxf_mlinestyle_flag_is_end_round_outer_arcs_cap
(
        DxfMlinestyle *mlinestyle
                /*!< DXF \c MLINESTYLE object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mlinestyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (DXF_CHECK_BIT (mlinestyle->flags, 10));
}


/*!
 * \brief Get the \c number_of_elements from a DXF \c MLINESTYLE object.
 *
 * \return \c number_of_elements.
 */
int
dxf_mlinestyle_get_number_of_elements
(
        DxfMlinestyle *mlinestyle
                /*!< a pointer to a DXF \c MLINESTYLE object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mlinestyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mlinestyle->number_of_elements < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mlinestyle->number_of_elements);
}


/*!
 * \brief Set the \c number_of_elements for a DXF \c MLINESTYLE object.
 */
DxfMlinestyle *
dxf_mlinestyle_set_number_of_elements
(
        DxfMlinestyle *mlinestyle,
                /*!< a pointer to a DXF \c MLINESTYLE object. */
        int number_of_elements
                /*!< the \c number_of_elements to be set for the object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mlinestyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (number_of_elements < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mlinestyle->number_of_elements = number_of_elements;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mlinestyle);
}


/*!
 * \brief Get the pointer to the next \c MLINESTYLE object from a DXF 
 * \c MLINESTYLE object.
 *
 * \return pointer to the next \c MLINESTYLE object.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfMlinestyle *
dxf_mlinestyle_get_next
(
        DxfMlinestyle *mlinestyle
                /*!< a pointer to a DXF \c MLINESTYLE object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mlinestyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mlinestyle->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfMlinestyle *) mlinestyle->next);
}


/*!
 * \brief Set the pointer to the next \c MLINE for a DXF \c MLINESTYLE
 * object.
 */
DxfMlinestyle *
dxf_mlinestyle_set_next
(
        DxfMlinestyle *mlinestyle,
                /*!< a pointer to a DXF \c MLINESTYLE object. */
        DxfMlinestyle *next
                /*!< a pointer to the next \c MLINESTYLE for the object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mlinestyle == NULL)
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
        mlinestyle->next = (struct DxfMlinestyle *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mlinestyle);
}


/*!
 * \brief Get the pointer to the last \c MLINESTYLE object from a linked
 * list of DXF \c MLINESTYLE object.
 *
 * \return pointer to the last \c MLINESTYLE object.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfMlinestyle *
dxf_mlinestyle_get_last
(
        DxfMlinestyle *mlinestyle
                /*!< a pointer to a DXF \c MLINESTYLE object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mlinestyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mlinestyle->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfMlinestyle *) mlinestyle);
        }
        DxfMlinestyle *iter = (DxfMlinestyle *) mlinestyle->next;
        while (iter->next != NULL)
        {
                iter = (DxfMlinestyle *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfMlinestyle *) iter);
}


/* EOF */
