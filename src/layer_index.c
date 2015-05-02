/*!
 * \file layer_index.c
 *
 * \author Copyright (C) 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF layer_index object (\c LAYER_INDEX).
 *
 * \version The \c LAYER_INDEX object was introduced in DXF R14.
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
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
 * \version According to DXF R14.
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
 * allocated memory when succesful.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
 * \version According to DXF R14.
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
        int i;

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
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                layer_index->layer_name[i] = strdup ("");
                layer_index->number_of_entries[i] = 0;
                layer_index->hard_owner_reference[i] = strdup ("");
        }
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
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
 * \version According to DXF R14.
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
        if (layer_index == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                layer_index = dxf_layer_index_new ();
                layer_index = dxf_layer_index_init (layer_index);
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
                if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", &layer_index->id_code);
                }
                if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name
                         * (multiple entries may exist). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", layer_index->layer_name[i]);
                        i++;
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
                         * entries in the IDBUFFER list (multiple
                         * entries may exist). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &layer_index->number_of_entries[j]);
                        j++;
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
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
                        fscanf (fp->fp, "%s\n", layer_index->dictionary_owner_soft);
                }
                else if ((strcmp (temp_string, "360") == 0)
                  && (k == 0))
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", layer_index->dictionary_owner_hard);
                        k++;
                }
                else if ((strcmp (temp_string, "360") == 0)
                  && (k > 0))
                {
                        /* Now follows a string containing a Hard owner
                         * reference IDBUFFER (multiple entries may
                         * exist). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", layer_index->hard_owner_reference[k]);
                        k++;
                        /*! \todo Check for overrun of array index. */
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
        return (layer_index);
}


/*!
 * \brief Free the allocated memory for a DXF \c LAYER_INDEX and all it's
 * data fields.
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
        int i;

        /* Do some basic checks. */
        if (layer_index->next != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to next DxfLayerIndex was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (layer_index->dictionary_owner_soft);
        free (layer_index->dictionary_owner_hard);
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                free (layer_index->layer_name[i]);
                free (layer_index->hard_owner_reference[i]);
        }
        free (layer_index);
        layer_index = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/* EOF*/
