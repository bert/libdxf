/*!
 * \file layer_index.c
 *
 * \author Copyright (C) 2015, 2017, 2018, 2019, 2020, 2021
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF layer_index object (\c LAYER_INDEX).
 *
 * A layer index is a list showing which objects are on which layers.
 *
 * This list is used when the program is referencing the drawing in
 * conjunction with demand loading to determine which objects need to be
 * read in and displayed.
 *
 * Objects on frozen layers in a referenced drawing are not read in if
 * the referenced drawing has a layer index and is being demand loaded.
 *
 * Layer indexes are best used in drawings that will be used as xrefs in
 * other drawings where demand loading is enabled.
 *
 * Drawings that are not going to be used as xrefs or partially opened
 * will not benefit from layer and spatial indexing or demand loading.
 *
 * \note To receive the maximum benefit of demand loading, it is
 * recommended that you save any drawings that are used as xrefs with
 * layer and spatial indexes.
 *
 * \since The \c LAYER_INDEX object was introduced in DXF R14.
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


#include "layer_index.h"


/*!
 * \brief Allocate memory for a \c DxfLayerIndex.
 *
 * Fill the memory contents with zeros.
 */
DxfLayerIndex *
dxf_layer_index_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfLayerIndex *layer_index = NULL;
        size_t size;

        size = sizeof (DxfLayerIndex);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((layer_index = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfLayerIndex struct.\n")),
                  __FUNCTION__);
                layer_index = NULL;
        }
        else
        {
                memset (layer_index, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (layer_index);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c LAYER_INDEX
 * object.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfLayerIndex *
dxf_layer_index_init
(
        DxfLayerIndex *layer_index
                /*!< DXF \c LAYER_INDEX object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (layer_index == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                layer_index = dxf_layer_index_new ();
        }
        if (layer_index == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfLayerIndex struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        layer_index->id_code = 0;
        layer_index->dictionary_owner_soft = strdup ("");
        layer_index->dictionary_owner_hard = strdup ("");
        layer_index->time_stamp = 0;
        /* Initialize new structs for the following members later,
         * when they are required and when we have content. */
        /*! \todo Proper implementation \c number_of_entries and
         * \c hard_owner_reference required. */ 
        layer_index->layer_name = NULL;
        layer_index->number_of_entries = NULL;
        layer_index->hard_owner_reference = NULL;
        layer_index->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (layer_index);
}


/*!
 * \brief Read data from a DXF file into a DXF \c LAYER_INDEX object.
 *
 * The last line read from file contained the string "LAYER_INDEX". \n
 * Now follows some data for the \c LAYER_INDEX, to be terminated with a
 * "  0" string announcing the following entity, or the end of the
 * \c ENTITY section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c layer_index. \n
 *
 * \return a pointer to \c layer_index.
 *
 * \todo Proper implementation \c number_of_entries and
 * \c hard_owner_reference required.
 */
DxfLayerIndex *
dxf_layer_index_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfLayerIndex *layer_index
                /*!< DXF \c LAYER_INDEX object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *temp_string = NULL;
        DxfLayerName *iter;
        int i;
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
        if (layer_index == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                layer_index = dxf_layer_index_init (layer_index);
        }
        i = 0;
        k = 0;
        iter = (DxfLayerName *) layer_index->layer_name; /* Pointer to first entry. */
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
                        fscanf (fp->fp, "%x\n", (uint *) &layer_index->id_code);
                }
                if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name
                         * (multiple entries may exist). */
                        if (i > 0) /* Create a pointer for the next entry. */
                        {
                                dxf_layer_name_init ((DxfLayerName *) iter->next);
                                iter = (DxfLayerName *) iter->next;
                        }
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, iter->name);
                        i++; /* Increase number of entries. */
                }
                if (strcmp (temp_string, "40") == 0)
                {
                        /* Now follows a string containing a time stamp. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &layer_index->time_stamp);
                }
                if (strcmp (temp_string, "90") == 0)
                {
                        /* Now follows a string containing a number of
                         * entries in the LAYER_INDEX list (multiple
                         * entries may exist). */
                        (fp->line_number)++;
                        /*! \todo Implement reading of \c number_of_entries
                         * properly.
                        fscanf (fp->fp, "%d\n", &layer_index->number_of_entries);
                         */
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if ((strcmp (temp_string, "AcDbIndex") != 0)
                          && (strcmp (temp_string, "AcDbLayerIndex") != 0))
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
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, layer_index->dictionary_owner_soft);
                }
                else if ((strcmp (temp_string, "360") == 0)
                  && (k == 0))
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, layer_index->dictionary_owner_hard);
                        k++;
                }
                else if ((strcmp (temp_string, "360") == 0)
                  && (k > 0))
                {
                        /* Now follows a string containing a Hard owner
                         * reference LAYER_INDEX (multiple entries may
                         * exist). */
                        (fp->line_number)++;
                        /*! \todo Implement reading of \c hard_owner_reference
                         * properly.
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, layer_index->hard_owner_reference);
                         */
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
        return (layer_index);
}


/*!
 * \brief Write DXF output to a file for a DXF \c LAYER_INDEX object.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 *
 * \todo Proper implementation \c number_of_entries and
 * \c hard_owner_reference required.
 */
int
dxf_layer_index_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfLayerIndex *layer_index
                /*!< DXF \c LAYER_INDEX object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("LAYER_INDEX");
        DxfLayerName *iter;
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
        if (layer_index == NULL)
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
                  __FUNCTION__, dxf_entity_name, layer_index->id_code);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (layer_index->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", layer_index->id_code);
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
        if ((strcmp (layer_index->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", layer_index->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (layer_index->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", layer_index->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbIndex\n");
        }
        fprintf (fp->fp, " 40\n%lf\n", layer_index->time_stamp);
        iter = (DxfLayerName *) layer_index->layer_name;
        i = 0;
        while (strlen (iter->name) > 0)
        {
                fprintf (fp->fp, "  8\n%s\n", iter->name);
                iter = (DxfLayerName *) iter->next;
                i++;
        }
        /*! \todo Implement reading of \c hard_owner_reference and
         * \c number_of_entries  properly.
        while (strlen (layer_index->layer_name->name) > 0)
        {
                fprintf (fp->fp, "360\n%s\n", layer_index->hard_owner_reference);
                fprintf (fp->fp, " 90\n%d\n", layer_index->number_of_entries);
        }
         */
        /* Clean up. */
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c LAYER_INDEX and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_layer_index_free
(
        DxfLayerIndex *layer_index
                /*!< Pointer to the memory occupied by the DXF
                 * \c LAYER_INDEX object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (layer_index == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (layer_index->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (layer_index->dictionary_owner_soft);
        free (layer_index->dictionary_owner_hard);
        dxf_char_free_list (layer_index->layer_name);
        dxf_char_free_list (layer_index->hard_owner_reference);
        free (layer_index);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c LAYER_INDEX objects and all their data fields.
 */
void
dxf_layer_index_free_list
(
        DxfLayerIndex *layer_indices
                /*!< pointer to the single linked list of DXF
                 * \c LAYER_INDEX objects. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (layer_indices == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (layer_indices != NULL)
        {
                DxfLayerIndex *iter = (DxfLayerIndex *) layer_indices->next;
                dxf_layer_index_free (layer_indices);
                layer_indices = (DxfLayerIndex *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the ID code from a DXF \c LAYER_INDEX object.
 *
 * \return \c id_code if successful, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_layer_index_get_id_code
(
        DxfLayerIndex *layer_index
                /*!< a pointer to a DXF \c LAYER_INDEX object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (layer_index == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (layer_index->id_code < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (layer_index->id_code);
}


/*!
 * \brief Set the ID code for a DXF \c LAYER_INDEX object.
 *
 * \return a pointer to \c layer_index if successful, or \c NULL when an
 * error occurred.
 */
DxfLayerIndex *
dxf_layer_index_set_id_code
(
        DxfLayerIndex *layer_index,
                /*!< a pointer to a DXF \c LAYER_INDEX object. */
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
        if (layer_index == NULL)
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
        layer_index->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (layer_index);
}


/*!
 * \brief Get the soft pointer to the dictionary owner from a DXF 
 * \c LAYER_INDEX object.
 *
 *
 * \return a pointer to \c dictionary_owner_soft if successful,
 * or \c EXIT_FAILURE when an error occurred.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_layer_index_get_dictionary_owner_soft
(
        DxfLayerIndex *layer_index
                /*!< a pointer to a DXF \c LAYER_INDEX object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (layer_index == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (layer_index->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (layer_index->dictionary_owner_soft));
}


/*!
 * \brief Set the pointer to the dictionary_owner_soft for a DXF
 * \c LAYER_INDEX object.
 *
 * \return a pointer to \c layer_index if successful, or \c NULL when an
 * error occurred.
 */
DxfLayerIndex *
dxf_layer_index_set_dictionary_owner_soft
(
        DxfLayerIndex *layer_index,
                /*!< a pointer to a DXF \c LAYER_INDEX object. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the
                 * dictionary_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (layer_index == NULL)
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
        layer_index->dictionary_owner_soft = strdup (dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (layer_index);
}


/*!
 * \brief Get the hard pointer to the dictionary owner from a DXF 
 * \c LAYER_INDEX object.
 *
 * \return a pointer to \c dictionary_owner_hard, or \c NULL when an
 * error occurred.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_layer_index_get_dictionary_owner_hard
(
        DxfLayerIndex *layer_index
                /*!< a pointer to a DXF \c LAYER_INDEX object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (layer_index == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (layer_index->dictionary_owner_hard ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (layer_index->dictionary_owner_hard));
}


/*!
 * \brief Set the pointer to the dictionary_owner_hard for a DXF
 * \c LAYER_INDEX object.
 *
 * \return a pointer to \c layer_index if successful, or \c NULL when an
 * error occurred.
 */
DxfLayerIndex *
dxf_layer_index_set_dictionary_owner_hard
(
        DxfLayerIndex *layer_index,
                /*!< a pointer to a DXF \c LAYER_INDEX object. */
        char *dictionary_owner_hard
                /*!< a string containing the pointer to the
                 * dictionary_owner_hard for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (layer_index == NULL)
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
        layer_index->dictionary_owner_hard = strdup (dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (layer_index);
}


/*!
 * \brief Get the \c time_stamp from a DXF \c LAYER_INDEX object.
 *
 *
 * \return \c time_stamp, or \c EXIT_FAILURE when an error occurred.
 */
double
dxf_layer_index_get_time_stamp
(
        DxfLayerIndex *layer_index
                /*!< a pointer to a DXF \c LAYER_INDEX object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (layer_index == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (layer_index->time_stamp < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (layer_index->time_stamp);
}


/*!
 * \brief Set the radius for a DXF \c LAYER_INDEX object.
 *
 * \return a pointer to \c layer_index, or \c NULL when an error
 * occurred.
 */
DxfLayerIndex *
dxf_layer_index_set_time_stamp
(
        DxfLayerIndex *layer_index,
                /*!< a pointer to a DXF \c LAYER_INDEX object. */
        double time_stamp
                /*!< the time_stamp to be set for the object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (layer_index == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (time_stamp < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        layer_index->time_stamp = time_stamp;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (layer_index);
}


/*!
 * \brief Get the pointer to the next \c LAYER_INDEX object from a DXF 
 * \c LAYER_INDEX object.
 *
 * \return pointer to the next \c LAYER_INDEX object, or \c NULL when an
 * error occurred.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfLayerIndex *
dxf_layer_index_get_next
(
        DxfLayerIndex *layer_index
                /*!< a pointer to a DXF \c LAYER_INDEX object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (layer_index == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (layer_index->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfLayerIndex *) layer_index->next);
}


/*!
 * \brief Set the pointer to the next \c LAYER_INDEX object for a DXF
 * \c LAYER_INDEX object.
 *
 * \return a pointer to \c layer_index, or \c NULL when an error
 * occurred.
 */
DxfLayerIndex *
dxf_layer_index_set_next
(
        DxfLayerIndex *layer_index,
                /*!< a pointer to a DXF \c LAYER_INDEX object. */
        DxfLayerIndex *next
                /*!< a pointer to the next \c LAYER_INDEX object for the
                 * object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (layer_index == NULL)
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
        layer_index->next = (struct DxfLayerIndex *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (layer_index);
}


/*!
 * \brief Get the pointer to the last \c LAYER_INDEX object from a
 * linked list of DXF \c LAYER_INDEX object.
 *
 * \return pointer to the last \c LAYER_INDEX object, or \c NULL when an
 * error occurred.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfLayerIndex *
dxf_layer_index_get_last
(
        DxfLayerIndex *layer_index
                /*!< a pointer to a DXF \c LAYER_INDEX object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (layer_index == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (layer_index->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfLayerIndex *) layer_index);
        }
        DxfLayerIndex *iter = (DxfLayerIndex *) layer_index->next;
        while (iter->next != NULL)
        {
                iter = (DxfLayerIndex *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfLayerIndex *) iter);
}


/* EOF*/
