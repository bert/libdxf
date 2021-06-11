/*!
 * \file oleframe.c
 *
 * \author Copyright (C) 2013, 2014, 2015, 2017, 2018, 2019, 2020, 2021
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF oleframe entity (\c OLEFRAME).
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


#include "oleframe.h"


/*!
 * \brief Allocate memory for a \c DxfOleFrame.
 *
 * Fill the memory contents with zeros.
 */
DxfOleFrame *
dxf_oleframe_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfOleFrame *oleframe = NULL;
        size_t size;

        size = sizeof (DxfOleFrame);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((oleframe = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfOleFrame struct.\n")),
                  __FUNCTION__);
                oleframe = NULL;
        }
        else
        {
                memset (oleframe, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (oleframe);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c OLEFRAME
 * entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfOleFrame *
dxf_oleframe_init
(
        DxfOleFrame *oleframe
                /*!< a pointer to the DXF \c OLEFRAME entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (oleframe == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                oleframe = dxf_oleframe_new ();
        }
        if (oleframe == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory for a DxfOleFrame struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        oleframe->id_code = 0;
        oleframe->linetype = strdup (DXF_DEFAULT_LINETYPE);
        oleframe->layer = strdup (DXF_DEFAULT_LAYER);
        oleframe->elevation = 0.0;
        oleframe->thickness = 0.0;
        oleframe->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        oleframe->visibility = DXF_DEFAULT_VISIBILITY;
        oleframe->color = DXF_COLOR_BYLAYER;
        oleframe->paperspace = DXF_MODELSPACE;
        oleframe->dictionary_owner_soft = strdup ("");
        oleframe->dictionary_owner_hard = strdup ("");
        oleframe->ole_version_number = 1;
        oleframe->length = 0;
        oleframe->binary_data = dxf_char_new ();
        oleframe->binary_data = dxf_char_init (oleframe->binary_data);
        oleframe->binary_data->value = strdup ("");
        oleframe->binary_data->length = 0;
        oleframe->binary_data->next = NULL;
        oleframe->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (oleframe);
}


/*!
 * \brief Read data from a DXF file into a DXF \c OLEFRAME entity.
 *
 * The last line read from file contained the string "OLEFRAME". \n
 * Now follows some data for the \c OLEFRAME, to be terminated with a "  0"
 * string announcing the following entity, or the end of the \c ENTITY
 * section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c oleframe. \n
 *
 * \return a pointer to \c oleframe.
 */
DxfOleFrame *
dxf_oleframe_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfOleFrame *oleframe
                /*!< a pointer to the DXF \c OLEFRAME entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *temp_string = NULL;
        DxfChar *iter = NULL;

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
        if (oleframe == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                oleframe = dxf_oleframe_init (oleframe);
        }
        iter = (DxfChar *) oleframe->binary_data;
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
                if (strcmp (temp_string, "1") == 0)
                {
                        /* Now follows a string containing a End of Ole
                         * data marker. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if (strcmp (temp_string, "OLE") != 0)
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () found a bad End of Ole data marker in: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                        }
                }
                if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", (uint *) &oleframe->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, oleframe->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, oleframe->layer);
                }
                else if ((fp->acad_version_number <= AutoCAD_11)
                        && (strcmp (temp_string, "38") == 0)
                        && (oleframe->elevation != 0.0))
                {
                        /* Now follows a string containing the
                         * elevation. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &oleframe->elevation);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &oleframe->thickness);
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing the linetype
                         * scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &oleframe->linetype_scale);
                }
                else if (strcmp (temp_string, "60") == 0)
                {
                        /* Now follows a string containing the
                         * visibility value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &oleframe->visibility);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &oleframe->color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &oleframe->paperspace);
                }
                else if (strcmp (temp_string, "70") == 0)
                {
                        /* Now follows a string containing the ole
                         * version number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &oleframe->ole_version_number);
                }
                else if (strcmp (temp_string, "90") == 0)
                {
                        /* Now follows a string containing the length of
                         * binary data. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%ld\n", &oleframe->length);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if ((strcmp (temp_string, "AcDbEntity") != 0)
                        && ((strcmp (temp_string, "AcDbOleFrame") != 0)))
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () found a bad subclass marker in: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                        }
                }
                else if (strcmp (temp_string, "310") == 0)
                {
                        /* Now follows a string containing binary data. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, iter->value);
                        iter->next = (struct DxfChar *) dxf_char_init ((DxfChar *) iter->next);
                        iter = (DxfChar *) iter->next;
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing Soft-pointer
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, oleframe->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, oleframe->dictionary_owner_hard);
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
        if (strcmp (oleframe->linetype, "") == 0)
        {
                oleframe->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (oleframe->layer, "") == 0)
        {
                oleframe->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Clean up. */
        free (temp_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (oleframe);
}


/*!
 * \brief Write DXF output to a file for a DXF \c OLEFRAME entity.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred while reading from the input file.
 */
int
dxf_oleframe_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfOleFrame *oleframe
                /*!< a pointer to the DXF \c OLEFRAME entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("OLEFRAME");
        DxfChar *iter = NULL;

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
        if (oleframe == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (fp->acad_version_number < AutoCAD_13)
        {
                fprintf (stderr,
                  (_("Warning in %s () illegal DXF version for this entity.\n")),
                  __FUNCTION__);
        }
        if (strcmp (oleframe->linetype, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty linetype string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, oleframe->id_code);
                fprintf (stderr,
                  (_("\t%s entity is reset to default linetype")),
                  dxf_entity_name);
                oleframe->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (oleframe->layer, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, oleframe->id_code);
                fprintf (stderr,
                  (_("\t%s entity is relocated to layer 0")),
                  dxf_entity_name);
                oleframe->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (oleframe->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", oleframe->id_code);
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
        if ((strcmp (oleframe->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", oleframe->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (oleframe->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", oleframe->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
        }
        if (oleframe->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%d\n", (int16_t) DXF_PAPERSPACE);
        }
        fprintf (fp->fp, "  8\n%s\n", oleframe->layer);
        if (strcmp (oleframe->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", oleframe->linetype);
        }
        if ((fp->acad_version_number <= AutoCAD_11)
          && DXF_FLATLAND
          && (oleframe->elevation != 0.0))
        {
                fprintf (fp->fp, " 38\n%f\n", oleframe->elevation);
        }
        if (oleframe->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", oleframe->color);
        }
        if (oleframe->linetype_scale != 1.0)
        {
                fprintf (fp->fp, " 48\n%f\n", oleframe->linetype_scale);
        }
        if (oleframe->visibility != 0)
        {
                fprintf (fp->fp, " 60\n%d\n", oleframe->visibility);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbOleFrame\n");
        }
        if (oleframe->thickness != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", oleframe->thickness);
        }
        fprintf (fp->fp, " 70\n%d\n", oleframe->ole_version_number);
        fprintf (fp->fp, " 90\n%ld\n", oleframe->length);
        if (oleframe->binary_data != NULL)
        {
                iter = (DxfChar*) oleframe->binary_data;
                while ((iter != NULL) && (iter->value != NULL))
                {
                        fprintf (fp->fp, "310\n%s\n", iter->value);
                        iter = (DxfChar*) iter->next;
                }
        }
        else
        {
                fprintf (fp->fp, "310\n\n");
        }
        fprintf (fp->fp, "  1\nOLE\n");
        /* Clean up. */
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c OLEFRAME and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_oleframe_free
(
        DxfOleFrame *oleframe
                /*!< a pointer to the  memory occupied by the DXF
                 * \c OLEFRAME entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (oleframe == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (oleframe->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (oleframe->linetype);
        free (oleframe->layer);
        free (oleframe->dictionary_owner_soft);
        free (oleframe->dictionary_owner_hard);
        dxf_char_free_list (oleframe->binary_data);
        free (oleframe);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c OLEFRAME entities and all their data fields.
 */
void
dxf_oleframe_free_list
(
        DxfOleFrame *oleframes
                /*!< a pointer to the single linked list of DXF
                 * \c OLEFRAME entities. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (oleframes == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (oleframes != NULL)
        {
                DxfOleFrame *iter = (DxfOleFrame *) oleframes->next;
                dxf_oleframe_free (oleframes);
                oleframes = (DxfOleFrame *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the \c id_code from a DXF \c OLEFRAME entity.
 *
 * \return \c id_code.
 */
int
dxf_oleframe_get_id_code
(
        DxfOleFrame *oleframe
                /*!< a pointer to a DXF \c OLEFRAME entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (oleframe == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (oleframe->id_code < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (oleframe->id_code);
}


/*!
 * \brief Set the \c id_code for a DXF \c OLEFRAME entity.
 */
DxfOleFrame *
dxf_oleframe_set_id_code
(
        DxfOleFrame *oleframe,
                /*!< a pointer to a DXF \c OLEFRAME entity. */
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
        if (oleframe == NULL)
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
        oleframe->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (oleframe);
}


/*!
 * \brief Get the \c linetype from a DXF \c OLEFRAME entity.
 *
 * \return \c linetype when sucessful, \c NULL when an error occurred.
 */
char *
dxf_oleframe_get_linetype
(
        DxfOleFrame *oleframe
                /*!< a pointer to a DXF \c OLEFRAME entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (oleframe == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (oleframe->linetype ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (oleframe->linetype));
}


/*!
 * \brief Set the \c linetype for a DXF \c OLEFRAME entity.
 */
DxfOleFrame *
dxf_oleframe_set_linetype
(
        DxfOleFrame *oleframe,
                /*!< a pointer to a DXF \c OLEFRAME entity. */
        char *linetype
                /*!< a string containing the \c linetype for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (oleframe == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (linetype == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        oleframe->linetype = strdup (linetype);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (oleframe);
}


/*!
 * \brief Get the \c layer from a DXF \c OLEFRAME entity.
 *
 * \return \c layer when sucessful, \c NULL when an error occurred.
 */
char *
dxf_oleframe_get_layer
(
        DxfOleFrame *oleframe
                /*!< a pointer to a DXF \c OLEFRAME entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (oleframe == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (oleframe->layer ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (oleframe->layer));
}


/*!
 * \brief Set the \c layer for a DXF \c OLEFRAME entity.
 */
DxfOleFrame *
dxf_oleframe_set_layer
(
        DxfOleFrame *oleframe,
                /*!< a pointer to a DXF \c OLEFRAME entity. */
        char *layer
                /*!< a string containing the \c layer for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (oleframe == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (layer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        oleframe->layer = strdup (layer);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (oleframe);
}


/*!
 * \brief Get the \c elevation from a DXF \c OLEFRAME entity.
 *
 * \return \c elevation.
 */
double
dxf_oleframe_get_elevation
(
        DxfOleFrame *oleframe
                /*!< a pointer to a DXF \c OLEFRAME entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (oleframe == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (oleframe->elevation);
}


/*!
 * \brief Set the \c elevation for a DXF \c OLEFRAME entity.
 */
DxfOleFrame *
dxf_oleframe_set_elevation
(
        DxfOleFrame *oleframe,
                /*!< a pointer to a DXF \c OLEFRAME entity. */
        double elevation
                /*!< the \c elevation to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (oleframe == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        oleframe->elevation = elevation;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (oleframe);
}


/*!
 * \brief Get the \c thickness from a DXF \c OLEFRAME entity.
 *
 * \return \c thickness.
 */
double
dxf_oleframe_get_thickness
(
        DxfOleFrame *oleframe
                /*!< a pointer to a DXF \c OLEFRAME entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (oleframe == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (oleframe->thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (oleframe->thickness);
}


/*!
 * \brief Set the \c thickness for a DXF \c OLEFRAME entity.
 */
DxfOleFrame *
dxf_oleframe_set_thickness
(
        DxfOleFrame *oleframe,
                /*!< a pointer to a DXF \c OLEFRAME entity. */
        double thickness
                /*!< the \c thickness to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (oleframe == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        oleframe->thickness = thickness;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (oleframe);
}


/*!
 * \brief Get the \c linetype_scale from a DXF \c OLEFRAME entity.
 *
 * \return \c linetype_scale.
 */
double
dxf_oleframe_get_linetype_scale
(
        DxfOleFrame *oleframe
                /*!< a pointer to a DXF \c OLEFRAME entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (oleframe == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (oleframe->linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (oleframe->linetype_scale);
}


/*!
 * \brief Set the \c linetype_scale for a DXF \c OLEFRAME entity.
 */
DxfOleFrame *
dxf_oleframe_set_linetype_scale
(
        DxfOleFrame *oleframe,
                /*!< a pointer to a DXF \c OLEFRAME entity. */
        double linetype_scale
                /*!< the \c linetype_scale to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (oleframe == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        oleframe->linetype_scale = linetype_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (oleframe);
}


/*!
 * \brief Get the \c visibility from a DXF \c OLEFRAME entity.
 *
 * \return \c visibility.
 */
int16_t
dxf_oleframe_get_visibility
(
        DxfOleFrame *oleframe
                /*!< a pointer to a DXF \c OLEFRAME entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (oleframe == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (oleframe->visibility < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (oleframe->visibility > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (oleframe->visibility);
}


/*!
 * \brief Set the \c visibility for a DXF \c OLEFRAME entity.
 */
DxfOleFrame *
dxf_oleframe_set_visibility
(
        DxfOleFrame *oleframe,
                /*!< a pointer to a DXF \c OLEFRAME entity. */
        int16_t visibility
                /*!< the \c visibility to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (oleframe == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (visibility < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (visibility > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        oleframe->visibility = visibility;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (oleframe);
}


/*!
 * \brief Get the \c color from a DXF \c OLEFRAME entity.
 *
 * \return \c color.
 */
int
dxf_oleframe_get_color
(
        DxfOleFrame *oleframe
                /*!< a pointer to a DXF \c OLEFRAME entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (oleframe == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (oleframe->color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (oleframe->color);
}


/*!
 * \brief Set the \c color for a DXF \c OLEFRAME entity.
 */
DxfOleFrame *
dxf_oleframe_set_color
(
        DxfOleFrame *oleframe,
                /*!< a pointer to a DXF \c OLEFRAME entity. */
        int color
                /*!< the \c color to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (oleframe == NULL)
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
        oleframe->color = color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (oleframe);
}


/*!
 * \brief Get the \c paperspace flag value from a DXF \c OLEFRAME entity.
 *
 * \return \c paperspace flag value.
 */
int
dxf_oleframe_get_paperspace
(
        DxfOleFrame *oleframe
                /*!< a pointer to a DXF \c OLEFRAME entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (oleframe == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (oleframe->paperspace < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (oleframe->paperspace > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (oleframe->paperspace);
}


/*!
 * \brief Set the \c paperspace flag for a DXF \c OLEFRAME entity.
 */
DxfOleFrame *
dxf_oleframe_set_paperspace
(
        DxfOleFrame *oleframe,
                /*!< a pointer to a DXF \c OLEFRAME entity. */
        int paperspace
                /*!< the \c paperspace flag value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (oleframe == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (paperspace < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (paperspace > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        oleframe->paperspace = paperspace;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (oleframe);
}


/*!
 * \brief Get the \c graphics_data_size value from a DXF \c OLEFRAME
 * entity.
 *
 * \return \c graphics_data_size value when successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
int
dxf_oleframe_get_graphics_data_size
(
        DxfOleFrame *oleframe
                /*!< a pointer to a DXF \c OLEFRAME entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (oleframe == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (oleframe->graphics_data_size < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (oleframe->graphics_data_size == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (oleframe->graphics_data_size);
}


/*!
 * \brief Set the \c graphics_data_size value for a DXF \c OLEFRAME entity.
 *
 * \return a pointer to \c oleframe when successful, or \c NULL when an
 * error occurred.
 */
DxfOleFrame *
dxf_oleframe_set_graphics_data_size
(
        DxfOleFrame *oleframe,
                /*!< a pointer to a DXF \c OLEFRAME entity. */
        int graphics_data_size
                /*!< the \c graphics_data_size value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (oleframe == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (graphics_data_size < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (graphics_data_size == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero value was passed.\n")),
                  __FUNCTION__);
        }
        oleframe->graphics_data_size = graphics_data_size;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (oleframe);
}


/*!
 * \brief Get the \c shadow_mode from a DXF \c OLEFRAME entity.
 *
 * \return \c shadow_mode when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_oleframe_get_shadow_mode
(
        DxfOleFrame *oleframe
                /*!< a pointer to a DXF \c OLEFRAME entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (oleframe == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (oleframe->shadow_mode < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (oleframe->shadow_mode > 3)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (oleframe->shadow_mode);
}


/*!
 * \brief Set the \c shadow_mode for a DXF \c OLEFRAME entity.
 *
 * \return a pointer to \c oleframe when successful, or \c NULL when an
 * error occurred.
 */
DxfOleFrame *
dxf_oleframe_set_shadow_mode
(
        DxfOleFrame *oleframe,
                /*!< a pointer to a DXF \c OLEFRAME entity. */
        int16_t shadow_mode
                /*!< the shadow mode to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (oleframe == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (shadow_mode < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (shadow_mode > 3)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        oleframe->shadow_mode = shadow_mode;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (oleframe);
}


/*!
 * \brief Get the pointer to the \c binary_graphics_data from a DXF
 * \c OLEFRAME entity.
 *
 * \return pointer to the \c binary_graphics_data.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfBinaryGraphicsData *
dxf_oleframe_get_binary_graphics_data
(
        DxfOleFrame *oleframe
                /*!< a pointer to a DXF \c OLEFRAME entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (oleframe == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (oleframe->binary_graphics_data ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfBinaryGraphicsData *) oleframe->binary_graphics_data);
}


/*!
 * \brief Set the pointer to the \c binary_graphics_data for a DXF
 * \c OLEFRAME entity.
 */
DxfOleFrame *
dxf_oleframe_set_binary_graphics_data
(
        DxfOleFrame *oleframe,
                /*!< a pointer to a DXF \c OLEFRAME entity. */
        DxfBinaryGraphicsData *data
                /*!< a string containing the pointer to the
                 * \c binary_graphics_data for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (oleframe == NULL)
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
        oleframe->binary_graphics_data = (DxfBinaryGraphicsData *) data;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (oleframe);
}


/*!
 * \brief Get the soft pointer to the dictionary owner from a DXF 
 * \c OLEFRAME entity.
 *
 * \return soft pointer to the dictionary owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_oleframe_get_dictionary_owner_soft
(
        DxfOleFrame *oleframe
                /*!< a pointer to a DXF \c OLEFRAME entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (oleframe == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (oleframe->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (oleframe->dictionary_owner_soft));
}


/*!
 * \brief Set the pointer to the dictionary_owner_soft for a DXF
 * \c OLEFRAME entity.
 */
DxfOleFrame *
dxf_oleframe_set_dictionary_owner_soft
(
        DxfOleFrame *oleframe,
                /*!< a pointer to a DXF \c OLEFRAME entity. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the
                 * dictionary_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (oleframe == NULL)
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
        oleframe->dictionary_owner_soft = strdup (dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (oleframe);
}


/*!
 * \brief Get the pointer to the \c material from a DXF \c OLEFRAME entity.
 *
 * \return a pointer to \c material when successful, or \c NULL when an
 * error occurred.
 *
 * \warning No checks are performed on the returned pointer.
 */
char *
dxf_oleframe_get_material
(
        DxfOleFrame *oleframe
                /*!< a pointer to a DXF \c OLEFRAME entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (oleframe == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (oleframe->material ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (oleframe->material));
}


/*!
 * \brief Set the pointer to the \c material for a DXF \c OLEFRAME
 * entity.
 *
 * \return a pointer to \c oleframe when successful, or \c NULL when an
 * error occurred.
 */
DxfOleFrame *
dxf_oleframe_set_material
(
        DxfOleFrame *oleframe,
                /*!< a pointer to a DXF \c OLEFRAME entity. */
        char *material
                /*!< a string containing the pointer to the \c
                 * material for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (oleframe == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (material == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        oleframe->material = strdup (material);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (oleframe);
}


/*!
 * \brief Get the hard pointer to the dictionary owner from a DXF 
 * \c OLEFRAME entity.
 *
 * \return hard pointer to the dictionary owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_oleframe_get_dictionary_owner_hard
(
        DxfOleFrame *oleframe
                /*!< a pointer to a DXF \c OLEFRAME entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (oleframe == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (oleframe->dictionary_owner_hard ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (oleframe->dictionary_owner_hard));
}


/*!
 * \brief Set the pointer to the dictionary_owner_hard for a DXF
 * \c OLEFRAME entity.
 */
DxfOleFrame *
dxf_oleframe_set_dictionary_owner_hard
(
        DxfOleFrame *oleframe,
                /*!< a pointer to a DXF \c OLEFRAME entity. */
        char *dictionary_owner_hard
                /*!< a string containing the pointer to the
                 * dictionary_owner_hard for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (oleframe == NULL)
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
        oleframe->dictionary_owner_hard = strdup (dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (oleframe);
}


/*!
 * \brief Get the \c lineweight from a DXF \c OLEFRAME entity.
 *
 * \return \c lineweight when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_oleframe_get_lineweight
(
        DxfOleFrame *oleframe
                /*!< a pointer to a DXF \c OLEFRAME entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (oleframe == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (oleframe->lineweight);
}


/*!
 * \brief Set the \c lineweight for a DXF \c OLEFRAME entity.
 *
 * \return a pointer to \c oleframe when successful, or \c NULL when an
 * error occurred.
 */
DxfOleFrame *
dxf_oleframe_set_lineweight
(
        DxfOleFrame *oleframe,
                /*!< a pointer to a DXF \c OLEFRAME entity. */
        int16_t lineweight
                /*!< the \c lineweight to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (oleframe == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        oleframe->lineweight = lineweight;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (oleframe);
}


/*!
 * \brief Get the \c plot_style_name from a DXF \c OLEFRAME entity.
 *
 * \return a pointer to \c plot_style_name when sucessful, or \c NULL
 * when an error occurred.
 */
char *
dxf_oleframe_get_plot_style_name
(
        DxfOleFrame *oleframe
                /*!< a pointer to a DXF \c OLEFRAME entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (oleframe == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (oleframe->plot_style_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (oleframe->plot_style_name));
}


/*!
 * \brief Set the \c plot_style_name for a DXF \c OLEFRAME entity.
 *
 * \return a pointer to \c oleframe when successful, or \c NULL when an
 * error occurred.
 */
DxfOleFrame *
dxf_oleframe_set_plot_style_name
(
        DxfOleFrame *oleframe,
                /*!< a pointer to a DXF \c OLEFRAME entity. */
        char *plot_style_name
                /*!< a string containing the \c plot_style_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (oleframe == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (plot_style_name == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        oleframe->plot_style_name = strdup (plot_style_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (oleframe);
}


/*!
 * \brief Get the \c color_value from a DXF \c OLEFRAME entity.
 *
 * \return \c color_value when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
long
dxf_oleframe_get_color_value
(
        DxfOleFrame *oleframe
                /*!< a pointer to a DXF \c OLEFRAME entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (oleframe == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (oleframe->color_value);
}


/*!
 * \brief Set the \c color_value for a DXF \c OLEFRAME entity.
 *
 * \return a pointer to \c oleframe when successful, or \c NULL when an
 * error occurred.
 */
DxfOleFrame *
dxf_oleframe_set_color_value
(
        DxfOleFrame *oleframe,
                /*!< a pointer to a DXF \c OLEFRAME entity. */
        long color_value
                /*!< the \c color_value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (oleframe == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        oleframe->color_value = color_value;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (oleframe);
}


/*!
 * \brief Get the \c color_name from a DXF \c OLEFRAME entity.
 *
 * \return \c color_name when sucessful, or \c NULL when an error
 * occurred.
 */
char *
dxf_oleframe_get_color_name
(
        DxfOleFrame *oleframe
                /*!< a pointer to a DXF \c OLEFRAME entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (oleframe == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (oleframe->color_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (oleframe->color_name));
}


/*!
 * \brief Set the \c color_name for a DXF \c OLEFRAME entity.
 *
 * \return a pointer to \c oleframe when successful, or \c NULL when an
 * error occurred.
 */
DxfOleFrame *
dxf_oleframe_set_color_name
(
        DxfOleFrame *oleframe,
                /*!< a pointer to a DXF \c OLEFRAME entity. */
        char *color_name
                /*!< a string containing the \c color_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (oleframe == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (color_name == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        oleframe->color_name = strdup (color_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (oleframe);
}


/*!
 * \brief Get the \c transparency from a DXF \c OLEFRAME entity.
 *
 * \return \c transparency when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
long
dxf_oleframe_get_transparency
(
        DxfOleFrame *oleframe
                /*!< a pointer to a DXF \c OLEFRAME entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (oleframe == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (oleframe->transparency);
}


/*!
 * \brief Set the \c transparency for a DXF \c OLEFRAME entity.
 *
 * \return a pointer to \c oleframe when successful, or \c NULL when an
 * error occurred.
 */
DxfOleFrame *
dxf_oleframe_set_transparency
(
        DxfOleFrame *oleframe,
                /*!< a pointer to a DXF \c OLEFRAME entity. */
        long transparency
                /*!< the \c transparency to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (oleframe == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        oleframe->transparency = transparency;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (oleframe);
}


/*!
 * \brief Get the \c ole_version_number from a DXF \c OLEFRAME entity.
 *
 * \return \c ole_version_number.
 */
int
dxf_oleframe_get_ole_version_number
(
        DxfOleFrame *oleframe
                /*!< a pointer to a DXF \c OLEFRAME entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (oleframe == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (oleframe->ole_version_number < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (oleframe->ole_version_number);
}


/*!
 * \brief Set the \c ole_version_number for a DXF \c OLEFRAME entity.
 */
DxfOleFrame *
dxf_oleframe_set_ole_version_number
(
        DxfOleFrame *oleframe,
                /*!< a pointer to a DXF \c OLEFRAME entity. */
        int ole_version_number
                /*!< the \c ole_version_number for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (oleframe == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ole_version_number < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        oleframe->ole_version_number = ole_version_number;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (oleframe);
}


/*!
 * \brief Get the \c length from a DXF \c OLEFRAME entity.
 *
 * \return \c length when successful, or \c EXIT_FAILURE when an error
 * occurred.
 */
long
dxf_oleframe_get_length
(
        DxfOleFrame *oleframe
                /*!< a pointer to a DXF \c OLEFRAME entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (oleframe == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (oleframe->length);
}


/*!
 * \brief Set the \c length for a DXF \c OLEFRAME entity.
 *
 * \return a pointer to \c oleframe when successful, or \c NULL when an
 * error occurred.
 */
DxfOleFrame *
dxf_oleframe_set_length
(
        DxfOleFrame *oleframe,
                /*!< a pointer to a DXF \c OLEFRAME entity. */
        long length
                /*!< the \c length to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (oleframe == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        oleframe->length = length;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (oleframe);
}


/*!
 * \brief Get the \c binary_data from a DXF \c OLEFRAME entity.
 *
 * \return \c binary_data when sucessful, or \c NULL when an error
 * occurred.
 *
 * \warning No deep copy of the returned pointer is made.
 */
DxfChar *
dxf_oleframe_get_binary_data
(
        DxfOleFrame *oleframe
                /*!< a pointer to a DXF \c OLEFRAME entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (oleframe == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (oleframe->binary_data ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (oleframe->binary_data);
}


/*!
 * \brief Set the \c binary_data for a DXF \c OLEFRAME entity.
 *
 * \return a pointer to \c oleframe when successful, or \c NULL when an
 * error occurred.
 *
 * \warning No deep copy of the passed pointer is made.
 */
DxfOleFrame *
dxf_oleframe_set_binary_data
(
        DxfOleFrame *oleframe,
                /*!< a pointer to a DXF \c OLEFRAME entity. */
        DxfChar *binary_data
                /*!< the \c binary_data for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (oleframe == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (binary_data == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        oleframe->binary_data = binary_data;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (oleframe);
}


/*!
 * \brief Get the pointer to the next \c OLEFRAME entity from a DXF
 * \c OLEFRAME entity.
 *
 * \return pointer to the next \c OLEFRAME entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfOleFrame *
dxf_oleframe_get_next
(
        DxfOleFrame *oleframe
                /*!< a pointer to a DXF \c OLEFRAME entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (oleframe == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (oleframe->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfOleFrame *) oleframe->next);
}


/*!
 * \brief Set the pointer to the next \c OLEFRAME for a DXF \c OLEFRAME
 * entity.
 */
DxfOleFrame *
dxf_oleframe_set_next
(
        DxfOleFrame *oleframe,
                /*!< a pointer to a DXF \c OLEFRAME entity. */
        DxfOleFrame *next
                /*!< a pointer to the next \c OLEFRAME for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (oleframe == NULL)
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
        oleframe->next = (struct DxfOleFrame *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (oleframe);
}


/*!
 * \brief Get the pointer to the last \c OLEFRAME entity from a linked
 * list of DXF \c OLEFRAME entities.
 *
 * \return pointer to the last \c OLEFRAME entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfOleFrame *
dxf_oleframe_get_last
(
        DxfOleFrame *oleframe
                /*!< a pointer to a DXF \c OLEFRAME entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (oleframe == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (oleframe->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfOleFrame *) oleframe);
        }
        DxfOleFrame *iter = (DxfOleFrame *) oleframe->next;
        while (iter->next != NULL)
        {
                iter = (DxfOleFrame *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfOleFrame *) iter);
}


/* EOF */
