/*!
 * \file spatial_index.c
 *
 * \author Copyright (C) 2015, 2017, 2018, 2019, 2020, 2021
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF spatial_index object (\c SPATIAL_INDEX).
 *
 * The SPATIAL_INDEX is always written out empty to a DXF file.\n
 * This object can be ignored.
 *
 * \since The \c SPATIAL_INDEX object was introduced in DXF R14.
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


#include "spatial_index.h"


/*!
 * \brief Allocate memory for a \c DxfSpatialIndex.
 *
 * Fill the memory contents with zeros.
 */
DxfSpatialIndex *
dxf_spatial_index_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfSpatialIndex *spatial_index = NULL;
        size_t size;

        size = sizeof (DxfSpatialIndex);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((spatial_index = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfSpatialIndex struct.\n")),
                  __FUNCTION__);
                spatial_index = NULL;
        }
        else
        {
                memset (spatial_index, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spatial_index);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c SPATIAL_INDEX
 * object.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfSpatialIndex *
dxf_spatial_index_init
(
        DxfSpatialIndex *spatial_index
                /*!< a pointer to the DXF \c SPATIAL_INDEX object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        time_t now;

        /* Do some basic checks. */
        if (spatial_index == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                spatial_index = dxf_spatial_index_new ();
        }
        if (spatial_index == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfSpatialIndex struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        spatial_index->id_code = 0;
        spatial_index->dictionary_owner_soft = strdup ("");
        spatial_index->dictionary_owner_hard = strdup ("");
        if (time (&now) != (time_t)(-1))
        {
                float fraction_day;
                int JD;
                struct tm *current_time = localtime (&now);

                /* Transform the current local gregorian date in a julian date.*/
                JD = current_time->tm_mday - 32075 + 1461 * (current_time->tm_year + 6700 + (current_time->tm_mon - 13) / 12) / 4 + 367 * (current_time->tm_mon - 1 - (current_time->tm_mon - 13) / 12 * 12) / 12 - 3 * ((current_time->tm_year + 6800 + (current_time->tm_mon - 13) / 12) / 100) / 4;
                /* Transform the current local clock time in fraction of day.*/
                fraction_day = (current_time->tm_hour + (current_time->tm_min / 60.0) + (current_time->tm_sec / 3600.0)) / 24.0;
                spatial_index->time_stamp = (double) (JD + fraction_day);
        }
        else spatial_index->time_stamp = 0.0;
        spatial_index->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spatial_index);
}


/*!
 * \brief Read data from a DXF file into a DXF \c SPATIAL_INDEX object.
 *
 * The last line read from file contained the string "SPATIAL_INDEX". \n
 * Now follows some data for the \c SPATIAL_INDEX, to be terminated with a
 * "  0" string announcing the following object, or the end of the
 * \c OBJECTS section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c spatial_index. \n
 *
 * \return a pointer to \c spatial_index.
 */
DxfSpatialIndex *
dxf_spatial_index_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfSpatialIndex *spatial_index
                /*!< a pointer to the DXF \c SPATIAL_INDEX object. */
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
        if (fp->acad_version_number < AutoCAD_14)
        {
                fprintf (stderr,
                  (_("Warning in %s () illegal DXF version for this entity.\n")),
                  __FUNCTION__);
        }
        if (spatial_index == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                spatial_index = dxf_spatial_index_init (spatial_index);
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
                        fscanf (fp->fp, "%x\n", (uint *) &spatial_index->id_code);
                }
                if (strcmp (temp_string, "40") == 0)
                {
                        /* Now follows a string containing a timestamp
                         * (Julian date). */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &spatial_index->time_stamp);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if ((strcmp (temp_string, "AcDbIndex") != 0)
                          && (strcmp (temp_string, "AcDbSpatialIndex") != 0))
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
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, spatial_index->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, spatial_index->dictionary_owner_hard);
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
        return (spatial_index);
}


/*!
 * \brief Write DXF output to a file for a DXF \c SPATIAL_INDEX object.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 *
 * \warning The SPATIAL_INDEX is always written out empty to a DXF file.\n
 * This object can be ignored.
 */
int
dxf_spatial_index_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfSpatialIndex *spatial_index
                /*!< a pointer to the DXF \c SPATIAL_INDEX object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("SPATIAL_INDEX");

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
        if (spatial_index == NULL)
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
                  __FUNCTION__, dxf_entity_name, spatial_index->id_code);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (spatial_index->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", spatial_index->id_code);
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
        if ((strcmp (spatial_index->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", spatial_index->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (spatial_index->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", spatial_index->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbIndex\n");
        }
        fprintf (fp->fp, " 40\n%f\n", spatial_index->time_stamp);
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbSpatialIndex\n");
        }
        /* Clean up. */
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c SPATIAL_INDEX and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_spatial_index_free
(
        DxfSpatialIndex *spatial_index
                /*!< a pointer to the memory occupied by the DXF
                 * \c SPATIAL_INDEX object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spatial_index == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (spatial_index->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (spatial_index->dictionary_owner_soft);
        free (spatial_index->dictionary_owner_hard);
        free (spatial_index);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c SPATIAL_INDEX objects and all their data fields.
 */
void
dxf_spatial_index_free_list
(
        DxfSpatialIndex *spatial_indices
                /*!< a pointer to the single linked list of DXF
                 * \c SPATIAL_INDEX objects. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (spatial_indices == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (spatial_indices != NULL)
        {
                DxfSpatialIndex *iter = (DxfSpatialIndex *) spatial_indices->next;
                dxf_spatial_index_free (spatial_indices);
                spatial_indices = (DxfSpatialIndex *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the \c id_code from a DXF \c SPATIAL_INDEX object.
 *
 * \return \c id_code.
 */
int
dxf_spatial_index_get_id_code
(
        DxfSpatialIndex *spatial_index
                /*!< a pointer to a DXF \c SPATIAL_INDEX object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spatial_index == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (spatial_index->id_code < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spatial_index->id_code);
}


/*!
 * \brief Set the \c id_code for a DXF \c SPATIAL_INDEX object.
 */
DxfSpatialIndex *
dxf_spatial_index_set_id_code
(
        DxfSpatialIndex *spatial_index,
                /*!< a pointer to a DXF \c SPATIAL_INDEX object. */
        int id_code
                /*!< the \c id_code to be set for the object.\n
                 * This is to be an unique (sequential) number in the
                 * DXF file. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spatial_index == NULL)
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
        spatial_index->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spatial_index);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_soft from a DXF 
 * \c SPATIAL_INDEX object.
 *
 * \return pointer to the \c dictionary_owner_soft.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_spatial_index_get_dictionary_owner_soft
(
        DxfSpatialIndex *spatial_index
                /*!< a pointer to a DXF \c SPATIAL_INDEX object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spatial_index == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (spatial_index->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (spatial_index->dictionary_owner_soft));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_soft for a DXF
 * \c SPATIAL_INDEX object.
 */
DxfSpatialIndex *
dxf_spatial_index_set_dictionary_owner_soft
(
        DxfSpatialIndex *spatial_index,
                /*!< a pointer to a DXF \c SPATIAL_INDEX object. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the \c
                 * dictionary_owner_soft for the object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spatial_index == NULL)
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
        spatial_index->dictionary_owner_soft = strdup (dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spatial_index);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_hard from a DXF 
 * \c SPATIAL_INDEX object.
 *
 * \return pointer to the \c dictionary_owner_hard.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_spatial_index_get_dictionary_owner_hard
(
        DxfSpatialIndex *spatial_index
                /*!< a pointer to a DXF \c SPATIAL_INDEX object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spatial_index == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (spatial_index->dictionary_owner_hard ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (spatial_index->dictionary_owner_hard));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_hard for a DXF
 * \c SPATIAL_INDEX object.
 */
DxfSpatialIndex *
dxf_spatial_index_set_dictionary_owner_hard
(
        DxfSpatialIndex *spatial_index,
                /*!< a pointer to a DXF \c SPATIAL_INDEX object. */
        char *dictionary_owner_hard
                /*!< a string containing the pointer to the \c
                 * dictionary_owner_hard for the object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spatial_index == NULL)
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
        spatial_index->dictionary_owner_hard = strdup (dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spatial_index);
}


/*!
 * \brief Get the time stamp \c time_stamp of a DXF \c SPATIAL_INDEX
 * object.
 *
 * \return the time stamp \c time_stamp.
 */
double
dxf_spatial_index_get_time_stamp
(
        DxfSpatialIndex *spatial_index
                /*!< a pointer to a DXF \c SPATIAL_INDEX object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (spatial_index == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spatial_index->time_stamp);
}


/*!
 * \brief Set the time stamp \c time_stamp of a DXF \c SPATIAL_INDEX
 * object.
 *
 * \return a pointer to \c spatial_index when successful, or \c NULL
 * when an error occurred.
 */
DxfSpatialIndex *
dxf_spatial_index_set_time_stamp
(
        DxfSpatialIndex *spatial_index,
                /*!< a pointer to a DXF \c SPATIAL_FILTER object. */
        double time_stamp
                /*!< the time stamp \c time_stamp to be set for a DXF
                 * \c SPATIAL_INDEX object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spatial_index == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        spatial_index->time_stamp = time_stamp;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spatial_index);
}


/*!
 * \brief Get the pointer to the next \c SPATIAL_INDEX object from a
 * DXF \c SPATIAL_INDEX object.
 *
 * \return pointer to the next \c SPATIAL_INDEX object.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfSpatialIndex *
dxf_spatial_index_get_next
(
        DxfSpatialIndex *spatial_index
                /*!< a pointer to a DXF \c SPATIAL_INDEX object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spatial_index == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (spatial_index->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfSpatialIndex *) spatial_index->next);
}


/*!
 * \brief Set the pointer to the next \c SPATIAL_INDEX object for a DXF
 * \c SPATIAL_INDEX object.
 */
DxfSpatialIndex *
dxf_spatial_index_set_next
(
        DxfSpatialIndex *spatial_index,
                /*!< a pointer to a DXF \c SPATIAL_INDEX object. */
        DxfSpatialIndex *next
                /*!< a pointer to the next \c SPATIAL_INDEX object for
                 * the object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spatial_index == NULL)
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
        spatial_index->next = (struct DxfSpatialIndex *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (spatial_index);
}


/*!
 * \brief Get the pointer to the last \c SPATIAL_INDEX object from a
 * linked list of DXF \c SPATIAL_INDEX objects.
 *
 * \return pointer to the last \c SPATIAL_INDEX object.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfSpatialIndex *
dxf_spatial_index_get_last
(
        DxfSpatialIndex *spatial_index
                /*!< a pointer to a DXF \c SPATIAL_INDEX object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (spatial_index == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (spatial_index->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfSpatialIndex *) spatial_index);
        }
        DxfSpatialIndex *iter = (DxfSpatialIndex *) spatial_index->next;
        while (iter->next != NULL)
        {
                iter = (DxfSpatialIndex *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfSpatialIndex *) iter);
}


/* EOF*/
