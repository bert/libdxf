/*!
 * \file mlinestyle.c
 *
 * \author Copyright (C) 2015, 2017 by Bert Timmerman <bert.timmerman@xs4all.nl>.
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
 * allocated memory when succesful.
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
 * allocated memory when succesful.
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
        mlinestyle->name = strdup ("");
        mlinestyle->description = strdup ("");
        mlinestyle->id_code = 0;
        mlinestyle->dictionary_owner_soft = strdup ("");
        mlinestyle->dictionary_owner_hard = strdup ("");
        mlinestyle->start_angle = 0.0;
        mlinestyle->end_angle = 0.0;
        mlinestyle->color = 256;
        mlinestyle->flags = 0;
        mlinestyle->number_of_elements = 0;
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                mlinestyle->element_linetype[i] = strdup ("");
                mlinestyle->element_offset[i] = 0.0;
                mlinestyle->element_color[i] = 0;
        }
        mlinestyle->next = NULL;
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
                mlinestyle = dxf_mlinestyle_new ();
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
                        fscanf (fp->fp, "%s\n", mlinestyle->name);
                }
                if (strcmp (temp_string, "3") == 0)
                {
                        /* Now follows a string containing a description
                         * string. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", mlinestyle->description);
                }
                if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", &mlinestyle->id_code);
                }
                if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing an element
                         * linetype. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", mlinestyle->element_linetype[i]);
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
                        fscanf (fp->fp, "%s\n", temp_string);
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
                        fscanf (fp->fp, "%s\n", mlinestyle->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", mlinestyle->dictionary_owner_hard);
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
                  __FUNCTION__, dxf_entity_name, mlinestyle->id_code);
                return (EXIT_FAILURE);
        }
        else
        {
                fprintf (stderr,
                  (_("Warning in %s () illegal DXF version for this %s entity with id-code: %x.\n")),
                  __FUNCTION__, dxf_entity_name, mlinestyle->id_code);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (mlinestyle->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", mlinestyle->id_code);
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
        if ((strcmp (mlinestyle->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", mlinestyle->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (mlinestyle->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", mlinestyle->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbMlineStyle\n");
        }
        fprintf (fp->fp, "  2\n%s\n", mlinestyle->name);
        fprintf (fp->fp, " 70\n%d\n", mlinestyle->flags);
        fprintf (fp->fp, "  3\n%s\n", mlinestyle->description);
        fprintf (fp->fp, " 62\n%d\n", mlinestyle->color);
        fprintf (fp->fp, " 51\n%lf\n", mlinestyle->start_angle);
        fprintf (fp->fp, " 52\n%lf\n", mlinestyle->end_angle);
        fprintf (fp->fp, " 71\n%d\n", mlinestyle->number_of_elements);
        for (i = 1; i < DXF_MAX_PARAM; i++)
        {
                fprintf (fp->fp, " 49\n%lf\n", mlinestyle->element_offset[i]);
                fprintf (fp->fp, " 62\n%d\n", mlinestyle->element_color[i]);
                fprintf (fp->fp, "  6\n%s\n", mlinestyle->element_linetype[i]);
                /*! \todo Check for overrun of array index. */
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
        if (mlinestyle->next != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to next DxfMlinestyle was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (mlinestyle->dictionary_owner_soft);
        free (mlinestyle->dictionary_owner_hard);
        free (mlinestyle->name);
        free (mlinestyle->description);
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                free (mlinestyle->element_linetype[i]);
        }
        free (mlinestyle);
        mlinestyle = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a chain of DXF \c MLINESTYLE
 * objects and all their data fields.
 */
void
dxf_mlinestyle_free_chain
(
        DxfMlinestyle *mlinestyles
                /*!< a pointer to the chain of DXF \c MLINESTYLE objects. */
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
                struct DxfMlinestyle *iter = mlinestyles->next;
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


/* EOF */
