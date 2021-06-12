/*!
 * \file thumbnail.c
 *
 * \author Copyright (C) 2010, 2012, 2014, 2015, 2017, 2019, 2021
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \author Copyright (C) 2010 by Luis Matos <gass@otiliamatos.ath.cx>.
 *
 * \brief Functions for a DXF thumbnail (\c THUMBNAIL).
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
 * \version According to DXF R14 (backward compatibility).
 * \version According to DXF R2000.
 * \version According to DXF R2000i.
 * \version According to DXF R2002.
 * \version According to DXF R2004.
 * \version According to DXF R2005.
 * \version According to DXF R2006.
 * \version According to DXF R2008.
 * \version According to DXF R2009.
 * \version According to DXF R2010.
 * \version According to DXF R2011.
 * \version According to DXF R2012.
 * \version According to DXF R2013.
 * \version According to DXF R2014.
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


#include "thumbnail.h"


/*!
 * \brief Allocate memory for a DXF \c THUMBNAILIMAGE.
 *
 * Fill the memory contents with zeros.
 *
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfThumbnail *
dxf_thumbnail_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfThumbnail *thumbnail = NULL;
        size_t size;

        size = sizeof (DxfThumbnail);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((thumbnail = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfThumbnail struct.\n")),
                  __FUNCTION__);
                thumbnail = NULL;
        }
        else
        {
                memset (thumbnail, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (thumbnail);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF
 * \c THUMBNAILIMAGE entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfThumbnail *
dxf_thumbnail_init
(
        DxfThumbnail *thumbnail
                /*!< DXF thumbnailimage entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (thumbnail == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                thumbnail = dxf_thumbnail_new ();
        }
        if (thumbnail == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfThumbnail struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        thumbnail->number_of_bytes = 0;
        thumbnail->preview_image_data = NULL;
        thumbnail->preview_image_data->length = 0;
        thumbnail->preview_image_data->value = strdup ("");
#if DEBUG
        DXF_DEBUG_END
#endif
        return (thumbnail);
}


/*!
 * \brief Read data from a DXF file into a DXF \c THUMBNAILIMAGE entity.
 *
 * The last line read from file contained the string "THUMBNAILIMAGE". \n
 * Now follows some data for the \c THUMBNAILIMAGE, to be terminated
 * with a "  0" string announcing the following entity, or the end of
 * the \c ENTITY section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c thumbnail. \n
 *
 * \return a pointer to \c thumbnail.
 */
DxfThumbnail *
dxf_thumbnail_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfThumbnail *thumbnail
                /*!< DXF thumbnailimage entity. */
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
        if (thumbnail == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                thumbnail = dxf_thumbnail_init (thumbnail);
        }
        if (fp->acad_version_number < AutoCAD_2000)
        {
                fprintf (stderr,
                  (_("Warning in %s () illegal DXF version for this entity.\n")),
                  __FUNCTION__);
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
                else if (strcmp (temp_string, "90") == 0)
                {
                        /* Now follows a string containing the
                         * number of bytes value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &thumbnail->number_of_bytes);
                }
                else if (strcmp (temp_string, "310") == 0)
                {
                        /* Now follows a string containing additional
                         * proprietary data. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, thumbnail->preview_image_data->value);
                        /*! \todo preview_image_data needs a proper implementation. */
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
        /* Handle omitted members and/or illegal values. */
        /*! \todo preview_image_data needs a proper checking for data length. */
        /* Clean up. */
        free (temp_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (thumbnail);
}


/*!
 * \brief Write a thumbnail to a DXF file.
 */
int
dxf_thumbnail_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfThumbnail *thumbnail
                /*!< the thumbnail to write to the output file. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("THUMBNAILIMAGE");

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
        if (thumbnail == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (thumbnail->number_of_bytes < 1)
        {
                fprintf (stderr,
                  (_("Error in %s () number of bytes was 0 or less.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (fp->acad_version_number < AutoCAD_2000)
        {
                fprintf (stderr,
                  (_("Warning in %s () illegal DXF version for this entity.\n")),
                  __FUNCTION__);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        fprintf (fp->fp, " 90\n%d\n", thumbnail->number_of_bytes);
        fprintf (fp->fp, "310\n%s\n", thumbnail->preview_image_data->value);
        /*! \todo preview_image_data needs a proper implementation. */
        /* Clean up. */
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c THUMBNAILIMAGE and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_thumbnail_free
(
        DxfThumbnail *thumbnail
                /*!< Pointer to the memory occupied by the DXF
                 * \c THUMBNAILIMAGE entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (thumbnail == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (thumbnail->preview_image_data->value);
        free (thumbnail->preview_image_data);
        /*! \todo preview_image_data needs a proper implementation. */
        free (thumbnail);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Get the \c number_of_bytes from a DXF \c THUMBNAILIMAGE object.
 *
 * \return \c number_of_bytes.
 */
int
dxf_thumbnail_get_number_of_bytes
(
        DxfThumbnail *thumbnail
                /*!< a pointer to a DXF \c THUMBNAILIMAGE object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (thumbnail == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (thumbnail->number_of_bytes < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (thumbnail->number_of_bytes);
}


/*!
 * \brief Set the \c number_of_bytes for a DXF \c THUMBNAILIMAGE object.
 */
DxfThumbnail *
dxf_thumbnail_set_number_of_bytes
(
        DxfThumbnail *thumbnail,
                /*!< a pointer to a DXF \c THUMBNAILIMAGE object. */
        int number_of_bytes
                /*!< the \c number_of_bytes to be set for the object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (thumbnail == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (number_of_bytes < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        thumbnail->number_of_bytes = number_of_bytes;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (thumbnail);
}


/*!
 * \brief Get the \c preview_image_data from a DXF \c THUMBNAILIMAGE
 * object.
 *
 * \return \c preview_image_data when sucessful, \c NULL when an error
 * occurred.
 */
DxfChar *
dxf_thumbnail_get_preview_image_data
(
        DxfThumbnail *thumbnail
                /*!< a pointer to a DXF \c THUMBNAILIMAGE object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (thumbnail == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (thumbnail->preview_image_data ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (thumbnail->preview_image_data);
}


/*!
 * \brief Set the \c preview_image_data for a DXF \c THUMBNAILIMAGE
 * object.
 */
DxfThumbnail *
dxf_thumbnail_set_preview_image_data
(
        DxfThumbnail *thumbnail,
                /*!< a pointer to a DXF \c THUMBNAILIMAGE object. */
        DxfChar *preview_image_data
                /*!< a pointer to the \c preview_image_data to be set
                 * for the object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (thumbnail == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (preview_image_data == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        thumbnail->preview_image_data = preview_image_data;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (thumbnail);
}


/*!
 * \brief Get the \c preview_image_data value from a DXF
 * \c THUMBNAILIMAGE object.
 *
 * \return \c preview_image_data value when sucessful, \c NULL when an
 * error occurred.
 */
char *
dxf_thumbnail_get_preview_image_data_value
(
        DxfChar *preview_image_data
                /*!< a pointer to a DXF \c preview_image_data object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (preview_image_data ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (preview_image_data->value ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (preview_image_data->value);
}


/*!
 * \brief Set the \c value for a DXF \c preview_image_data of a DXF
 * \c THUMBNAILIMAGE object.
 */
DxfChar *
dxf_thumbnail_set_preview_image_data_value
(
        DxfChar *preview_image_data,
                /*!< a pointer to a DXF \c preview_image_data. */
        char *value
                /*!< a pointer to the \c preview_image_data value to be
                 * set for the object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (preview_image_data == NULL)
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
        preview_image_data->value = value;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (preview_image_data);
}


/*!
 * \brief Get the \c length of a \c preview_image_data \c value from a
 * DXF \c THUMBNAILIMAGE object.
 *
 * \return \c length when sucessful, \c NULL when an error occurred.
 */
int
dxf_thumbnail_get_preview_image_data_length
(
        DxfChar *preview_image_data
                /*!< a pointer to a DXF \c preview_image_data object
                 * (linked list). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (preview_image_data == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (preview_image_data->length);
}


/*!
 * \brief Set the \c length of the \c value for a DXF
 * \c preview_image_data of a DXF \c THUMBNAILIMAGE object.
 */
DxfChar *
dxf_thumbnail_set_preview_image_data_length
(
        DxfChar *preview_image_data,
                /*!< a pointer to a DXF \c preview_image_data. */
        int length
                /*!< the \c length of the \c preview_image_data value to
                 * be set for the object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (preview_image_data == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (length < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        preview_image_data->length = length;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (preview_image_data);
}


/*!
 * \brief Get the \c next \c preview_image_data \c (linked list) from a
 * DXF \c THUMBNAILIMAGE object.
 *
 * \return \c next when sucessful, \c NULL when an error occurred.
 */
DxfChar *
dxf_thumbnail_get_preview_image_data_next
(
        DxfChar *preview_image_data
                /*!< a pointer to a DXF \c preview_image_data object
                 * (linked list). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (preview_image_data == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (preview_image_data->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfChar *) preview_image_data->next);
}


/*!
 * \brief Set the pointer to the \c next DXF \c preview_image_data
 * (linked list) for a DXF \c THUMBNAILIMAGE object.
 */
DxfChar *
dxf_thumbnail_set_preview_image_data_next
(
        DxfChar *preview_image_data,
                /*!< a pointer to a DXF \c preview_image_data. */
        DxfChar *next
                /*!< a pointer to the the \c next \c preview_image_data
                 * to be set for the object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (preview_image_data == NULL)
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
        preview_image_data->next = (struct DxfChar *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (preview_image_data);
}


/*!
 * \brief Get the pointer to the last \c preview_image_data object from a linked list
 * of DXF \c preview_image_data objects.
 *
 * \return pointer to the last \c preview_image_data object.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfChar *
dxf_thumbnail_get_preview_image_data_last
(
        DxfChar *preview_image_data
                /*!< a pointer to a DXF \c preview_image_data object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (preview_image_data == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (preview_image_data->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfChar *) preview_image_data);
        }
        DxfChar *iter = (DxfChar *) preview_image_data->next;
        while (iter->next != NULL)
        {
                iter = (DxfChar *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfChar *) iter);
}


/* EOF */
