/*!
 * \file idbuffer.c
 *
 * \author Copyright (C) 2015, 2016, 2017, 2018, 2019, 2020, 2021
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF idbuffer object (\c IDBUFFER).
 *
 * The \c IDBUFFER object is a utility object that is just a list of
 * references to objects.
 *
 * \since The \c IDBUFFER object was introduced in DXF R14.
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


#include "idbuffer.h"


/*!
 * \brief Allocate memory for a \c DxfIdbuffer.
 *
 * Fill the memory contents with zeros.
 */
DxfIdbuffer *
dxf_idbuffer_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfIdbuffer *idbuffer = NULL;
        size_t size;

        size = sizeof (DxfIdbuffer);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((idbuffer = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                idbuffer = NULL;
        }
        else
        {
                memset (idbuffer, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (idbuffer);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c IDBUFFER
 * object.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfIdbuffer *
dxf_idbuffer_init
(
        DxfIdbuffer *idbuffer
                /*!< DXF \c IDBUFFER object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (idbuffer == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                idbuffer = dxf_idbuffer_new ();
        }
        if (idbuffer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        /* Assign initial values to members. */
        idbuffer->id_code = 0;
        idbuffer->dictionary_owner_soft = strdup ("");
        idbuffer->object_owner_soft = strdup ("");
        idbuffer->dictionary_owner_hard = strdup ("");
        /* Initialize new structs for the following members later,
         * when they are required and when we have content. */
        idbuffer->entity_pointer = NULL;
        idbuffer->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (idbuffer);
}


/*!
 * \brief Read data from a DXF file into a DXF \c IDBUFFER object.
 *
 * The last line read from file contained the string "IDBUFFER". \n
 * Now follows some data for the \c IDBUFFER, to be terminated with a
 * "  0" string announcing the following object, or the end of the
 * \c OBJECTS section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c idbuffer. \n
 *
 * \return a pointer to \c idbuffer.
 */
DxfIdbuffer *
dxf_idbuffer_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfIdbuffer *idbuffer
                /*!< DXF \c IDBUFFER object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *temp_string = NULL;
        int i;
        DxfIdbufferEntityPointer *entity_pointer = NULL;
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
        if (fp->acad_version_number < AutoCAD_14)
        {
                fprintf (stderr,
                  (_("Warning in %s () illegal DXF version for this entity.\n")),
                  __FUNCTION__);
        }
        if (idbuffer == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                idbuffer = dxf_idbuffer_init (idbuffer);
        }
        i = 0;
        entity_pointer = (DxfIdbufferEntityPointer *) dxf_idbuffer_entity_pointer_init (entity_pointer);
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
                        /* Clean up. */
                        free (temp_string);
                        fclose (fp->fp);
                        return (NULL);
                }
                if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", (uint *) &idbuffer->id_code);
                }
                else if (strcmp (temp_string, "100") == 0)
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if (strcmp (temp_string, "AcDbIdBuffer") != 0)
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () found a bad subclass marker in: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                        }
                }
                else if ((strcmp (temp_string, "330") == 0)
                  && (i == 0))
                {
                        if (iter330 == 0)
                        {
                                /* Now follows a string containing a soft-pointer
                                 * ID/handle to owner dictionary. */
                                (fp->line_number)++;
                                fscanf (fp->fp, DXF_MAX_STRING_FORMAT, idbuffer->dictionary_owner_soft);
                                i++;
                        }
                        if (iter330 == 1)
                        {
                                /* Now follows a string containing a soft-pointer
                                 * ID/handle to owner object. */
                                (fp->line_number)++;
                                fscanf (fp->fp, DXF_MAX_STRING_FORMAT, idbuffer->object_owner_soft);
                        }
                        iter330++;
                }
                else if ((strcmp (temp_string, "330") == 0)
                  && (i > 0))
                {
                        /* Now follows a string containing a Soft
                         * pointer reference to entity. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, entity_pointer->soft_pointer);
                        dxf_idbuffer_entity_pointer_init ((DxfIdbufferEntityPointer *) entity_pointer->next);
                        entity_pointer = (DxfIdbufferEntityPointer *) entity_pointer->next;
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, idbuffer->dictionary_owner_hard);
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
        return (idbuffer);
}


/*!
 * \brief Write DXF output to a file for a DXF \c IDBUFFER object.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_idbuffer_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfIdbuffer *idbuffer
                /*!< DXF \c IDBUFFER object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("IDBUFFER");
        DxfIdbufferEntityPointer * entity_pointer = NULL;

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
        if (idbuffer == NULL)
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
                  __FUNCTION__, dxf_entity_name, dxf_idbuffer_get_id_code (idbuffer));
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (dxf_idbuffer_get_id_code (idbuffer) != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", dxf_idbuffer_get_id_code (idbuffer));
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
        if ((strcmp (idbuffer->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", dxf_idbuffer_get_dictionary_owner_soft (idbuffer));
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (idbuffer->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", dxf_idbuffer_get_dictionary_owner_hard (idbuffer));
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (idbuffer->object_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_2000))
        {
                fprintf (fp->fp, "330\n%s\n", idbuffer->object_owner_soft);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbIdBuffer\n");
        }
        entity_pointer = (DxfIdbufferEntityPointer *) idbuffer->entity_pointer;
        while (entity_pointer != NULL)
        {
                fprintf (fp->fp, "330\n%s\n", entity_pointer->soft_pointer);
                entity_pointer = (DxfIdbufferEntityPointer *) entity_pointer->next;
        }
        /* Clean up. */
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c IDBUFFER object and all
 * it's data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_idbuffer_free
(
        DxfIdbuffer *idbuffer
                /*!< Pointer to the memory occupied by the DXF
                 * \c IDBUFFER object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (idbuffer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (idbuffer->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (idbuffer->dictionary_owner_soft);
        free (idbuffer->object_owner_soft);
        free (idbuffer->dictionary_owner_hard);
        dxf_idbuffer_entity_pointer_free_list ((DxfIdbufferEntityPointer *) idbuffer->entity_pointer);
        free (idbuffer);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c IDBUFFER objects and all their data fields.
 */
void
dxf_idbuffer_free_list
(
        DxfIdbuffer *id_buffers
                /*!< pointer to the single linked list of DXF
                 * \c IDBUFFER objects. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (id_buffers == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (id_buffers != NULL)
        {
                DxfIdbuffer *iter = (DxfIdbuffer *) dxf_idbuffer_get_next (id_buffers);
                dxf_idbuffer_free (id_buffers);
                id_buffers = (DxfIdbuffer *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the \c id_code from a DXF \c IDBUFFER object.
 *
 * \return \c id_code when successful, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_idbuffer_get_id_code
(
        DxfIdbuffer *idbuffer
                /*!< a pointer to a DXF \c IDBUFFER. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (idbuffer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (idbuffer->id_code < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (idbuffer->id_code);
}


/*!
 * \brief Set the \c id_code for a DXF \c IDBUFFER object.
 *
 * \return a pointer to \c idbuffer when successful, or \c NULL when an
 * error occurred.
 */
DxfIdbuffer *
dxf_idbuffer_set_id_code
(
        DxfIdbuffer *idbuffer,
                /*!< a pointer to a DXF \c IDBUFFER. */
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
        if (idbuffer == NULL)
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
        idbuffer->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (idbuffer);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_soft from a DXF
 * \c IDBUFFER object.
 *
 * \return a pointer to \c dictionary_owner_soft when successful, or
 * \c NULL when an error occurred.
 *
 * \warning No checks are performed on the returned pointer.
 */
char *
dxf_idbuffer_get_dictionary_owner_soft
(
        DxfIdbuffer *idbuffer
                /*!< a pointer to a DXF \c IDBUFFER object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (idbuffer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (idbuffer->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (idbuffer->dictionary_owner_soft));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_soft for a DXF
 * \c IDBUFFER object.
 *
 * \return a pointer to \c idbuffer when successful, or \c NULL when an
 * error occurred.
 */
DxfIdbuffer *
dxf_idbuffer_set_dictionary_owner_soft
(
        DxfIdbuffer *idbuffer,
                /*!< a pointer to a DXF \c IDBUFFER object. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the \c
                 * dictionary_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (idbuffer == NULL)
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
        idbuffer->dictionary_owner_soft = strdup (dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (idbuffer);
}


/*!
 * \brief Get the soft pointer to the object owner from a DXF 
 * \c IDBUFFER object.
 *
 * \return soft pointer to the object owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_idbuffer_get_object_owner_soft
(
        DxfIdbuffer *idbuffer
                /*!< a pointer to a DXF \c IDBUFFER object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (idbuffer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (idbuffer->object_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (idbuffer->object_owner_soft));
}


/*!
 * \brief Set the pointer to the \c object_owner_soft for a DXF
 * \c IDBUFFER object.
 */
DxfIdbuffer *
dxf_idbuffer_set_object_owner_soft
(
        DxfIdbuffer *idbuffer,
                /*!< a pointer to a DXF \c IDBUFFER object. */
        char *object_owner_soft
                /*!< a string containing the pointer to the
                 * \c object_owner_soft for the object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (idbuffer == NULL)
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
        idbuffer->object_owner_soft = strdup (object_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (idbuffer);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_hard from a DXF
 * \c IDBUFFER object.
 *
 * \return a pointer to \c dictionary_owner_hard when successful, or
 * \c NULL when an error occurred.
 *
 * \warning No checks are performed on the returned pointer.
 */
char *
dxf_idbuffer_get_dictionary_owner_hard
(
        DxfIdbuffer *idbuffer
                /*!< a pointer to a DXF \c IDBUFFER object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (idbuffer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (idbuffer->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (idbuffer->dictionary_owner_hard));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_hard for a DXF
 * \c IDBUFFER object.
 *
 * \return a pointer to \c idbuffer when successful, or \c NULL when an
 * error occurred.
 */
DxfIdbuffer *
dxf_idbuffer_set_dictionary_owner_hard
(
        DxfIdbuffer *idbuffer,
                /*!< a pointer to a DXF \c IDBUFFER object. */
        char *dictionary_owner_hard
                /*!< a string containing the pointer to the \c
                 * dictionary_owner_hard for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (idbuffer == NULL)
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
        idbuffer->dictionary_owner_hard = strdup (dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (idbuffer);
}


/*!
 * \brief Get the pointer to the first entity_pointer of a linked list
 * of \c entity_pointer from a DXF \c IDBUFFER object.
 *
 * \return pointer to the first \c entity_pointer of a linked list.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfIdbufferEntityPointer *
dxf_idbuffer_get_entity_pointer
(
        DxfIdbuffer *idbuffer
                /*!< a pointer to a DXF \c IDBUFFER object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (idbuffer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (idbuffer->entity_pointer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfIdbufferEntityPointer *) idbuffer->entity_pointer);
}


/*!
 * \brief Set the pointer to the first \c entity_pointer of a linked
 * list for a DXF \c IDBUFFER object.
 *
 * \return a pointer to \c idbuffer when successful, or \c NULL when an
 * error occurred.
 */
DxfIdbuffer *
dxf_idbuffer_set_entity_pointer
(
        DxfIdbuffer *idbuffer,
                /*!< a pointer to a DXF \c IDBUFFER object. */
        DxfIdbufferEntityPointer *entity_pointer
                /*!< a pointer to the first \c entity_pointer of a
                 * linked list for the object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (idbuffer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (entity_pointer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        idbuffer->entity_pointer = (DxfIdbufferEntityPointer *) entity_pointer;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (idbuffer);
}


/*!
 * \brief Get the pointer to the next \c HELIX entity from a DXF 
 * \c IDBUFFER object.
 *
 * \return pointer to the next \c IDBUFFER object.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfIdbuffer *
dxf_idbuffer_get_next
(
        DxfIdbuffer *idbuffer
                /*!< a pointer to a DXF \c IDBUFFER object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (idbuffer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (idbuffer->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfIdbuffer *) idbuffer->next);
}


/*!
 * \brief Set the pointer to the next \c IDBUFFER for a DXF \c IDBUFFER
 * object.
 *
 * \return a pointer to \c idbuffer when successful, or \c NULL when an
 * error occurred.
 */
DxfIdbuffer *
dxf_idbuffer_set_next
(
        DxfIdbuffer *idbuffer,
                /*!< a pointer to a DXF \c IDBUFFER object. */
        DxfIdbuffer *next
                /*!< a pointer to the next \c IDBUFFER for the object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (idbuffer == NULL)
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
        idbuffer->next = (struct DxfIdbuffer *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (idbuffer);
}


/*!
 * \brief Get the pointer to the last \c IDBUFFER object from a linked
 * list of DXF \c IDBUFFER objects.
 *
 * \return pointer to the last \c IDBUFFER object.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfIdbuffer *
dxf_idbuffer_get_last
(
        DxfIdbuffer *idbuffer
                /*!< a pointer to a DXF \c IDBUFFER object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (idbuffer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (idbuffer->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfIdbuffer *) idbuffer);
        }
        DxfIdbuffer *iter = (DxfIdbuffer *) idbuffer->next;
        while (iter->next != NULL)
        {
                iter = (DxfIdbuffer *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfIdbuffer *) iter);
}


/*!
 * \brief Allocate memory for a \c DxfIdbufferEntityPointer.
 *
 * Fill the memory contents with zeros.
 */
DxfIdbufferEntityPointer *
dxf_idbuffer_entity_pointer_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfIdbufferEntityPointer *entity_pointer = NULL;
        size_t size;

        size = sizeof (DxfIdbufferEntityPointer);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((entity_pointer = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                entity_pointer = NULL;
        }
        else
        {
                memset (entity_pointer, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (entity_pointer);
}


/*!
 * \brief Allocate memory and initialize data fields in a
 * \c DxfIdbufferEntityPointer struct.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfIdbufferEntityPointer *
dxf_idbuffer_entity_pointer_init
(
        DxfIdbufferEntityPointer *entity_pointer
                /*!< DXF \c DxfIdbufferEntityPointer struct. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (entity_pointer == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                entity_pointer = dxf_idbuffer_entity_pointer_new ();
        }
        if (entity_pointer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        entity_pointer->soft_pointer = strdup ("");
        entity_pointer->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (entity_pointer);
}


/*!
 * \brief Free the allocated memory for a DXF
 * \c DxfIdbufferEntityPointer struct and all it's data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_idbuffer_entity_pointer_free
(
        DxfIdbufferEntityPointer *entity_pointer
                /*!< Pointer to the memory occupied by the DXF
                 * \c DxfIdbufferEntityPointer struct. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (entity_pointer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (entity_pointer->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (entity_pointer->soft_pointer);
        free (entity_pointer);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c DxfIdbufferEntityPointer structs and all their data fields.
 */
void
dxf_idbuffer_entity_pointer_free_list
(
        DxfIdbufferEntityPointer *entity_pointers
                /*!< pointer to the single linked list of DXF
                 * \c DxfIdbufferEntityPointer structs. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (entity_pointers == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (entity_pointers != NULL)
        {
                DxfIdbufferEntityPointer *iter = (DxfIdbufferEntityPointer *) entity_pointers->next;
                dxf_idbuffer_entity_pointer_free (entity_pointers);
                entity_pointers = (DxfIdbufferEntityPointer *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the pointer to the \c soft_pointer from a DXF
 * \c DxfIdbufferEntityPointer object.
 *
 * \return a pointer to \c soft_pointer when successful, or
 * \c NULL when an error occurred.
 *
 * \warning No checks are performed on the returned pointer.
 */
char *
dxf_idbuffer_entity_pointer_get_soft_pointer
(
        DxfIdbufferEntityPointer *entity_pointer
                /*!< a pointer to a DXF \c IDBUFFER object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (entity_pointer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (entity_pointer->soft_pointer ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (entity_pointer->soft_pointer));
}


/*!
 * \brief Set the pointer to the \c soft_pointer for a DXF
 * \c DxfIdbufferEntityPointer object.
 *
 * \return a pointer to \c entity_pointer when successful, or \c NULL when an
 * error occurred.
 */
DxfIdbufferEntityPointer *
dxf_idbuffer_entity_pointer_set_soft_pointer
(
        DxfIdbufferEntityPointer *entity_pointer,
                /*!< a pointer to a DXF \c DxfIdbufferEntityPointer object. */
        char *soft_pointer
                /*!< a string containing the pointer to the \c
                 * soft_pointer for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (entity_pointer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (soft_pointer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        entity_pointer->soft_pointer = strdup (soft_pointer);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (entity_pointer);
}


/*!
 * \brief Get the pointer to the next \c DxfIdbufferEntityPointer object
 * from a DXF \c DxfIdbufferEntityPointer object.
 *
 * \return pointer to the next \c DxfIdbufferEntityPointer object.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfIdbufferEntityPointer *
dxf_idbuffer_entity_pointer_get_next
(
        DxfIdbufferEntityPointer *entity_pointer
                /*!< a pointer to a DXF \c DxfIdbufferEntityPointer object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (entity_pointer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (entity_pointer->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfIdbufferEntityPointer *) entity_pointer->next);
}


/*!
 * \brief Set the pointer to the next \c DxfIdbufferEntityPointer object
 * for a DXF \c DxfIdbufferEntityPointer object.
 *
 * \return a pointer to \c entity_pointer when successful, or \c NULL when an
 * error occurred.
 */
DxfIdbufferEntityPointer*
dxf_idbuffer_entity_pointer_set_next
(
        DxfIdbufferEntityPointer *entity_pointer,
                /*!< a pointer to a DXF \c DxfIdbufferEntityPointer
                 * object. */
        DxfIdbufferEntityPointer *next
                /*!< a pointer to the next \c DxfIdbufferEntityPointer
                 * object for the DxfIdbufferEntityPointer object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (entity_pointer == NULL)
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
        entity_pointer->next = (struct DxfIdbufferEntityPointer *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (entity_pointer);
}


/*!
 * \brief Get the pointer to the last \c DxfIdbufferEntityPointer object
 * from a linked list of DXF \c DxfIdbufferEntityPointer objects.
 *
 * \return pointer to the last \c DxfIdbufferEntityPointer object.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfIdbufferEntityPointer *
dxf_idbuffer_entity_pointer_get_last
(
        DxfIdbufferEntityPointer *entity_pointer
                /*!< a pointer to a DXF \c DxfIdbufferEntityPointer
                 * object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (entity_pointer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (entity_pointer->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfIdbufferEntityPointer *) entity_pointer);
        }
        DxfIdbufferEntityPointer *iter = (DxfIdbufferEntityPointer *) entity_pointer->next;
        while (iter->next != NULL)
        {
                iter = (DxfIdbufferEntityPointer *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfIdbufferEntityPointer *) iter);
}


/* EOF*/
