/*!
 * \file oleframe.c
 *
 * \author Copyright (C) 2013, 2014, 2015, 2017
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF oleframe entity (\c OLEFRAME).
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
 *
 * \version According to DXF R13.
 * \version According to DXF R14.
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
 * allocated memory when succesful.
 *
 * \version According to DXF R13.
 * \version According to DXF R14.
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
        int i;

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
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                oleframe->binary_data[i] = strdup ("");
        }
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
 *
 * \version According to DXF R13.
 * \version According to DXF R14.
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
        if (oleframe == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                oleframe = dxf_oleframe_new ();
                oleframe = dxf_oleframe_init (oleframe);
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
                        fscanf (fp->fp, "%s\n", temp_string);
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
                        fscanf (fp->fp, "%x\n", &oleframe->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", oleframe->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", oleframe->layer);
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
                        fscanf (fp->fp, "%s\n", temp_string);
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
                        fscanf (fp->fp, "%s\n", oleframe->binary_data[i]);
                        i++;
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing Soft-pointer
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", oleframe->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", oleframe->dictionary_owner_hard);
                }
                else if (strcmp (temp_string, "999") == 0)
                {
                        /* Now follows a string containing a comment. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
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
 *
 * \version According to DXF R13.
 * \version According to DXF R14.
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
                fprintf (fp->fp, " 67\n%d\n", DXF_PAPERSPACE);
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
        i = 0;
        while (strlen (oleframe->binary_data[i]) > 0)
        {
                fprintf (fp->fp, "310\n%s\n", oleframe->binary_data[i]);
                i++;
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
 *
 * \version According to DXF R13.
 * \version According to DXF R14.
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
        int i;

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
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                free (oleframe->binary_data[i]);
        }
        free (oleframe);
        oleframe = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a chain of DXF \c OLEFRAME
 * entities and all their data fields.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
void
dxf_oleframe_free_chain
(
        DxfOleFrame *oleframes
                /*!< a pointer to the chain of DXF \c OLEFRAME entities. */
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
                struct DxfOleFrame *iter = oleframes->next;
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


/* EOF */
