/*!
 * \file ole2frame.c
 *
 * \author Copyright (C) 2015, 2017 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF ole2frame entity (\c OLE2FRAME).
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


#include "ole2frame.h"


/*!
 * \brief Allocate memory for a \c DxfOle2Frame.
 *
 * Fill the memory contents with zeros.
 */
DxfOle2Frame *
dxf_ole2frame_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfOle2Frame *ole2frame = NULL;
        size_t size;

        size = sizeof (DxfOle2Frame);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((ole2frame = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfOle2Frame struct.\n")),
                  __FUNCTION__);
                ole2frame = NULL;
        }
        else
        {
                memset (ole2frame, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ole2frame);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c OLE2FRAME
 * entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfOle2Frame *
dxf_ole2frame_init
(
        DxfOle2Frame *ole2frame
                /*!< a pointer to the DXF \c OLEFRAME entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        /* Do some basic checks. */
        if (ole2frame == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                ole2frame = dxf_ole2frame_new ();
        }
        if (ole2frame == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory for a DxfOle2Frame struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        ole2frame->id_code = 0;
        ole2frame->linetype = strdup (DXF_DEFAULT_LINETYPE);
        ole2frame->layer = strdup (DXF_DEFAULT_LAYER);
        ole2frame->elevation = 0.0;
        ole2frame->thickness = 0.0;
        ole2frame->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        ole2frame->visibility = DXF_DEFAULT_VISIBILITY;
        ole2frame->color = DXF_COLOR_BYLAYER;
        ole2frame->paperspace = DXF_MODELSPACE;
        ole2frame->dictionary_owner_soft = strdup ("");
        ole2frame->dictionary_owner_hard = strdup ("");
        ole2frame->end_of_data = strdup ("OLE");
        ole2frame->length_of_binary_data = strdup ("");
        ole2frame->x0 = 0.0;
        ole2frame->y0 = 0.0;
        ole2frame->z0 = 0.0;
        ole2frame->x1 = 0.0;
        ole2frame->y1 = 0.0;
        ole2frame->z1 = 0.0;
        ole2frame->ole_version_number = 1;
        ole2frame->ole_object_type = 0;
        ole2frame->tilemode_descriptor = 0;
        ole2frame->length = 0;
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                ole2frame->binary_data[i] = strdup ("");
        }
        ole2frame->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ole2frame);
}


/*!
 * \brief Read data from a DXF file into a DXF \c OLE2FRAME entity.
 *
 * The last line read from file contained the string "OLE2FRAME". \n
 * Now follows some data for the \c OLE2FRAME, to be terminated with a "  0"
 * string announcing the following entity, or the end of the \c ENTITY
 * section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c ole2frame. \n
 *
 * \return a pointer to \c ole2frame.
 */
DxfOle2Frame *
dxf_ole2frame_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfOle2Frame *ole2frame
                /*!< a pointer to the DXF \c OLE2FRAME entity. */
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
        if (ole2frame == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                ole2frame = dxf_ole2frame_new ();
                ole2frame = dxf_ole2frame_init (ole2frame);
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
                if (strcmp (temp_string, "3") == 0)
                {
                        /* Now follows a string containing the length of
                         * binary data. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", ole2frame->length_of_binary_data);
                }
                if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", &ole2frame->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", ole2frame->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", ole2frame->layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the insertion point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &ole2frame->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the insertion point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &ole2frame->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the insertion point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &ole2frame->z0);
                }
                else if (strcmp (temp_string, "11") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the direction vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &ole2frame->x1);
                }
                else if (strcmp (temp_string, "21") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the direction vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &ole2frame->y1);
                }
                else if (strcmp (temp_string, "31") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the direction vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &ole2frame->z1);
                }
                else if ((fp->acad_version_number <= AutoCAD_11)
                        && (strcmp (temp_string, "38") == 0))
                {
                        /* Now follows a string containing the
                         * elevation. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &ole2frame->elevation);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &ole2frame->thickness);
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing the linetype
                         * scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &ole2frame->linetype_scale);
                }
                else if (strcmp (temp_string, "60") == 0)
                {
                        /* Now follows a string containing the
                         * visibility value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &ole2frame->visibility);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &ole2frame->color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &ole2frame->paperspace);
                }
                else if (strcmp (temp_string, "70") == 0)
                {
                        /* Now follows a string containing the ole
                         * version number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &ole2frame->ole_version_number);
                }
                else if (strcmp (temp_string, "71") == 0)
                {
                        /* Now follows a string containing the ole
                         * object type. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &ole2frame->ole_object_type);
                }
                else if (strcmp (temp_string, "72") == 0)
                {
                        /* Now follows a string containing the tilemode
                         * descriptor. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &ole2frame->tilemode_descriptor);
                }
                else if (strcmp (temp_string, "90") == 0)
                {
                        /* Now follows a string containing the length of
                         * binary data. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%ld\n", &ole2frame->length);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
                        if ((strcmp (temp_string, "AcDbEntity") != 0)
                        && ((strcmp (temp_string, "AcDbOle2Frame") != 0)))
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
                        fscanf (fp->fp, "%s\n", ole2frame->binary_data[i]);
                        i++;
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing Soft-pointer
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", ole2frame->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", ole2frame->dictionary_owner_hard);
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
        if (strcmp (ole2frame->linetype, "") == 0)
        {
                ole2frame->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (ole2frame->layer, "") == 0)
        {
                ole2frame->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Clean up. */
        free (temp_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ole2frame);
}


/*!
 * \brief Write DXF output to a file for a DXF \c OLE2FRAME entity.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred while reading from the input file.
 */
int
dxf_ole2frame_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfOle2Frame *ole2frame
                /*!< a pointer to the DXF \c OLE2FRAME entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("OLE2FRAME");
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
        if (ole2frame == NULL)
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
                  (_("Warning in %s () illegal DXF version for this entity.\n")),
                  __FUNCTION__);
        }
        if (strcmp (ole2frame->linetype, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty linetype string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, ole2frame->id_code);
                fprintf (stderr,
                  (_("\t%s entity is reset to default linetype")),
                  dxf_entity_name);
                ole2frame->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (ole2frame->layer, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, ole2frame->id_code);
                fprintf (stderr,
                  (_("\t%s entity is relocated to layer 0")),
                  dxf_entity_name);
                ole2frame->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (ole2frame->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", ole2frame->id_code);
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
        if ((strcmp (ole2frame->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", ole2frame->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (ole2frame->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", ole2frame->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
        }
        if (ole2frame->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
        fprintf (fp->fp, "  8\n%s\n", ole2frame->layer);
        if (strcmp (ole2frame->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", ole2frame->linetype);
        }
        if ((fp->acad_version_number <= AutoCAD_11)
          && DXF_FLATLAND
          && (ole2frame->elevation != 0.0))
        {
                fprintf (fp->fp, " 38\n%f\n", ole2frame->elevation);
        }
        if (ole2frame->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", ole2frame->color);
        }
        if (ole2frame->linetype_scale != 1.0)
        {
                fprintf (fp->fp, " 48\n%f\n", ole2frame->linetype_scale);
        }
        if (ole2frame->visibility != 0)
        {
                fprintf (fp->fp, " 60\n%d\n", ole2frame->visibility);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbOle2Frame\n");
        }
        if (ole2frame->thickness != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", ole2frame->thickness);
        }
        fprintf (fp->fp, " 70\n%d\n", ole2frame->ole_version_number);
        fprintf (fp->fp, "  3\n%s\n", ole2frame->length_of_binary_data);
        fprintf (fp->fp, " 10\n%f\n", ole2frame->x0);
        fprintf (fp->fp, " 20\n%f\n", ole2frame->y0);
        fprintf (fp->fp, " 30\n%f\n", ole2frame->z0);
        fprintf (fp->fp, " 11\n%f\n", ole2frame->x1);
        fprintf (fp->fp, " 21\n%f\n", ole2frame->y1);
        fprintf (fp->fp, " 31\n%f\n", ole2frame->z1);
        fprintf (fp->fp, " 71\n%d\n", ole2frame->ole_object_type);
        fprintf (fp->fp, " 72\n%d\n", ole2frame->tilemode_descriptor);
        fprintf (fp->fp, " 90\n%ld\n", ole2frame->length);
        i = 0;
        while (strlen (ole2frame->binary_data[i]) > 0)
        {
                fprintf (fp->fp, "310\n%s\n", ole2frame->binary_data[i]);
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
 * \brief Free the allocated memory for a DXF \c OLE2FRAME and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_ole2frame_free
(
        DxfOle2Frame *ole2frame
                /*!< a pointer to the memory occupied by the DXF
                 * \c OLE2FRAME entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        if (ole2frame->next != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to next DxfOle2Frame was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (ole2frame->end_of_data);
        free (ole2frame->length_of_binary_data);
        free (ole2frame->linetype);
        free (ole2frame->layer);
        free (ole2frame->dictionary_owner_soft);
        free (ole2frame->dictionary_owner_hard);
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                free (ole2frame->binary_data[i]);
        }
        free (ole2frame);
        ole2frame = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a chain of DXF \c OLE2FRAME
 * entities and all their data fields.
 */
void
dxf_ole2frame_free_chain
(
        DxfOle2Frame *ole2frames
                /*!< a pointer to the chain of DXF \c OLE2FRAME entities. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (ole2frames == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (ole2frames != NULL)
        {
                struct DxfOle2Frame *iter = ole2frames->next;
                dxf_ole2frame_free (ole2frames);
                ole2frames = (DxfOle2Frame *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the \c id_code from a DXF \c OLE2FRAME entity.
 *
 * \return \c id_code.
 */
int
dxf_ole2frame_get_id_code
(
        DxfOle2Frame *ole2frame
                /*!< a pointer to a DXF \c OLE2FRAME entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ole2frame == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ole2frame->id_code < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ole2frame->id_code);
}


/*!
 * \brief Set the \c id_code for a DXF \c OLE2FRAME entity.
 */
DxfOle2Frame *
dxf_ole2frame_set_id_code
(
        DxfOle2Frame *ole2frame,
                /*!< a pointer to a DXF \c OLE2FRAME entity. */
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
        if (ole2frame == NULL)
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
        ole2frame->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ole2frame);
}


/*!
 * \brief Get the \c linetype from a DXF \c OLE2FRAME entity.
 *
 * \return \c linetype when sucessful, \c NULL when an error occurred.
 */
char *
dxf_ole2frame_get_linetype
(
        DxfOle2Frame *ole2frame
                /*!< a pointer to a DXF \c OLE2FRAME entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ole2frame == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ole2frame->linetype ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (ole2frame->linetype));
}


/*!
 * \brief Set the linetype for a DXF \c OLE2FRAME entity.
 */
DxfOle2Frame *
dxf_ole2frame_set_linetype
(
        DxfOle2Frame *ole2frame,
                /*!< a pointer to a DXF \c ARC entity. */
        char *linetype
                /*!< a string containing the linetype for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ole2frame == NULL)
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
        ole2frame->linetype = strdup (linetype);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ole2frame);
}


/*!
 * \brief Get the layer from a DXF \c OLE2FRAME entity.
 *
 * \return layer when sucessful, \c NULL when an error occurred.
 */
char *
dxf_ole2frame_get_layer
(
        DxfOle2Frame *ole2frame
                /*!< a pointer to a DXF \c OLE2FRAME entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ole2frame == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ole2frame->layer ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (ole2frame->layer));
}


/*!
 * \brief Set the layer for a DXF \c OLE2FRAME entity.
 */
DxfOle2Frame *
dxf_ole2frame_set_layer
(
        DxfOle2Frame *ole2frame,
                /*!< a pointer to a DXF \c OLE2FRAME entity. */
        char *layer
                /*!< a string containing the layer for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ole2frame == NULL)
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
        ole2frame->layer = strdup (layer);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ole2frame);
}


/*!
 * \brief Get the \c elevation from a DXF \c OLE2FRAME entity.
 *
 * \return \c elevation.
 */
double
dxf_ole2frame_get_elevation
(
        DxfOle2Frame *ole2frame
                /*!< a pointer to a DXF \c OLE2FRAME entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ole2frame == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ole2frame->elevation);
}


/*!
 * \brief Set the \c elevation for a DXF \c OLE2FRAME entity.
 */
DxfOle2Frame *
dxf_ole2frame_set_elevation
(
        DxfOle2Frame *ole2frame,
                /*!< a pointer to a DXF \c OLE2FRAME entity. */
        double elevation
                /*!< the elevation to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ole2frame == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ole2frame->elevation = elevation;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ole2frame);
}


/*!
 * \brief Get the \c thickness from a DXF \c OLE2FRAME entity.
 *
 * \return \c thickness.
 */
double
dxf_ole2frame_get_thickness
(
        DxfOle2Frame *ole2frame
                /*!< a pointer to a DXF \c OLE2FRAME entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ole2frame == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ole2frame->thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ole2frame->thickness);
}


/*!
 * \brief Set the \c thickness for a DXF \c OLE2FRAME entity.
 */
DxfOle2Frame *
dxf_ole2frame_set_thickness
(
        DxfOle2Frame *ole2frame,
                /*!< a pointer to a DXF \c OLE2FRAME entity. */
        double thickness
                /*!< the \c thickness to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ole2frame == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ole2frame->thickness = thickness;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ole2frame);
}


/*!
 * \brief Get the \c linetype_scale from a DXF \c OLE2FRAME entity.
 *
 * \return \c linetype_scale.
 */
double
dxf_ole2frame_get_linetype_scale
(
        DxfOle2Frame *ole2frame
                /*!< a pointer to a DXF \c OLE2FRAME entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ole2frame == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ole2frame->linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ole2frame->linetype_scale);
}


/*!
 * \brief Set the linetype scale for a DXF \c OLE2FRAME entity.
 */
DxfOle2Frame *
dxf_ole2frame_set_linetype_scale
(
        DxfOle2Frame *ole2frame,
                /*!< a pointer to a DXF \c OLE2FRAME entity. */
        double linetype_scale
                /*!< the linetype scale to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ole2frame == NULL)
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
        ole2frame->linetype_scale = linetype_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ole2frame);
}


/*!
 * \brief Get the visibility from a DXF \c OLE2FRAME entity.
 *
 * \return visibility.
 */
int16_t
dxf_ole2frame_get_visibility
(
        DxfOle2Frame *ole2frame
                /*!< a pointer to a DXF \c OLE2FRAME entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ole2frame == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ole2frame->visibility < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (ole2frame->visibility > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ole2frame->visibility);
}


/*!
 * \brief Set the visibility for a DXF \c OLE2FRAME entity.
 */
DxfOle2Frame *
dxf_ole2frame_set_visibility
(
        DxfOle2Frame *ole2frame,
                /*!< a pointer to a DXF \c OLE2FRAME entity. */
        int16_t visibility
                /*!< the visibility to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ole2frame == NULL)
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
        ole2frame->visibility = visibility;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ole2frame);
}


/*!
 * \brief Get the \c color from a DXF \c OLE2FRAME entity.
 *
 * \return \c color.
 */
int
dxf_ole2frame_get_color
(
        DxfOle2Frame *ole2frame
                /*!< a pointer to a DXF \c OLE2FRAME entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ole2frame == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ole2frame->color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ole2frame->color);
}


/*!
 * \brief Set the color for a DXF \c OLE2FRAME entity.
 */
DxfOle2Frame *
dxf_ole2frame_set_color
(
        DxfOle2Frame *ole2frame,
                /*!< a pointer to a DXF \c OLE2FRAME entity. */
        int color
                /*!< the color to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ole2frame == NULL)
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
        ole2frame->color = color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ole2frame);
}


/*!
 * \brief Get the \c paperspace flag value from a DXF \c OLE2FRAME entity.
 *
 * \return \c paperspace flag value.
 */
int
dxf_ole2frame_get_paperspace
(
        DxfOle2Frame *ole2frame
                /*!< a pointer to a DXF \c OLE2FRAME entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ole2frame == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ole2frame->paperspace < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (ole2frame->paperspace > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ole2frame->paperspace);
}


/*!
 * \brief Set the \c paperspace flag for a DXF \c OLE2FRAME entity.
 */
DxfOle2Frame *
dxf_ole2frame_set_paperspace
(
        DxfOle2Frame *ole2frame,
                /*!< a pointer to a DXF \c OLE2FRAME entity. */
        int paperspace
                /*!< the \c paperspace flag value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ole2frame == NULL)
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
        ole2frame->paperspace = paperspace;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ole2frame);
}


/*!
 * \brief Get the \c graphics_data_size value from a DXF \c OLE2FRAME
 * entity.
 *
 * \return \c graphics_data_size value when successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
int
dxf_ole2frame_get_graphics_data_size
(
        DxfOle2Frame *ole2frame
                /*!< a pointer to a DXF \c OLE2FRAME entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ole2frame == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ole2frame->graphics_data_size < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (ole2frame->graphics_data_size == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ole2frame->graphics_data_size);
}


/*!
 * \brief Set the \c graphics_data_size value for a DXF \c OLE2FRAME
 * entity.
 *
 * \return a pointer to \c ole2frame when successful, or \c NULL when an
 * error occurred.
 */
DxfOle2Frame *
dxf_ole2frame_set_graphics_data_size
(
        DxfOle2Frame *ole2frame,
                /*!< a pointer to a DXF \c OLE2FRAME entity. */
        int graphics_data_size
                /*!< the \c graphics_data_size value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ole2frame == NULL)
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
        ole2frame->graphics_data_size = graphics_data_size;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ole2frame);
}


/*!
 * \brief Get the \c shadow_mode from a DXF \c OLE2FRAME entity.
 *
 * \return \c shadow_mode when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_ole2frame_get_shadow_mode
(
        DxfOle2Frame *ole2frame
                /*!< a pointer to a DXF \c OLE2FRAME entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ole2frame == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ole2frame->shadow_mode < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (ole2frame->shadow_mode > 3)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ole2frame->shadow_mode);
}


/*!
 * \brief Set the \c shadow_mode for a DXF \c OLE2FRAME entity.
 *
 * \return a pointer to \c ole2frame when successful, or \c NULL when an
 * error occurred.
 */
DxfOle2Frame *
dxf_ole2frame_set_shadow_mode
(
        DxfOle2Frame *ole2frame,
                /*!< a pointer to a DXF \c OLE2FRAME entity. */
        int16_t shadow_mode
                /*!< the shadow mode to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ole2frame == NULL)
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
        ole2frame->shadow_mode = shadow_mode;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ole2frame);
}


/*!
 * \brief Get the pointer to the \c binary_graphics_data from a DXF
 * \c OLE2FRAME entity.
 *
 * \return pointer to the \c binary_graphics_data.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfBinaryGraphicsData *
dxf_ole2frame_get_binary_graphics_data
(
        DxfOle2Frame *ole2frame
                /*!< a pointer to a DXF \c OLE2FRAME entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ole2frame == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ole2frame->binary_graphics_data ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfBinaryGraphicsData *) ole2frame->binary_graphics_data);
}


/*!
 * \brief Set the pointer to the \c binary_graphics_data for a DXF
 * \c OLE2FRAME entity.
 */
DxfOle2Frame *
dxf_ole2frame_set_binary_graphics_data
(
        DxfOle2Frame *ole2frame,
                /*!< a pointer to a DXF \c OLE2FRAME entity. */
        DxfBinaryGraphicsData *data
                /*!< a string containing the pointer to the
                 * \c binary_graphics_data for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ole2frame == NULL)
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
        ole2frame->binary_graphics_data = (DxfBinaryGraphicsData *) data;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ole2frame);
}


/*!
 * \brief Get the soft pointer to the dictionary owner from a DXF 
 * \c OLE2FRAME entity.
 *
 * \return soft pointer to the dictionary owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_ole2frame_get_dictionary_owner_soft
(
        DxfOle2Frame *ole2frame
                /*!< a pointer to a DXF \c OLE2FRAME entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ole2frame == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ole2frame->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (ole2frame->dictionary_owner_soft));
}


/*!
 * \brief Set the pointer to the dictionary_owner_soft for a DXF
 * \c OLE2FRAME entity.
 */
DxfOle2Frame *
dxf_ole2frame_set_dictionary_owner_soft
(
        DxfOle2Frame *ole2frame,
                /*!< a pointer to a DXF \c OLE2FRAME entity. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the
                 * dictionary_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ole2frame == NULL)
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
        ole2frame->dictionary_owner_soft = strdup (dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ole2frame);
}


/*!
 * \brief Get the pointer to the \c material from a DXF \c OLE2FRAME
 * entity.
 *
 * \return a pointer to \c material when successful, or \c NULL when an
 * error occurred.
 *
 * \warning No checks are performed on the returned pointer.
 */
char *
dxf_ole2frame_get_material
(
        DxfOle2Frame *ole2frame
                /*!< a pointer to a DXF \c OLE2FRAME entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ole2frame == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ole2frame->material ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (ole2frame->material));
}


/*!
 * \brief Set the pointer to the \c material for a DXF \c OLE2FRAME
 * entity.
 *
 * \return a pointer to \c ole2frame when successful, or \c NULL when an
 * error occurred.
 */
DxfOle2Frame *
dxf_ole2frame_set_material
(
        DxfOle2Frame *ole2frame,
                /*!< a pointer to a DXF \c OLE2FRAME entity. */
        char *material
                /*!< a string containing the pointer to the \c
                 * material for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ole2frame == NULL)
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
        ole2frame->material = strdup (material);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ole2frame);
}


/*!
 * \brief Get the hard pointer to the dictionary owner from a DXF 
 * \c OLE2FRAME entity.
 *
 * \return hard pointer to the dictionary owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_ole2frame_get_dictionary_owner_hard
(
        DxfOle2Frame *ole2frame
                /*!< a pointer to a DXF \c OLE2FRAME entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ole2frame == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ole2frame->dictionary_owner_hard ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (ole2frame->dictionary_owner_hard));
}


/*!
 * \brief Set the pointer to the dictionary_owner_hard for a DXF
 * \c OLE2FRAME entity.
 */
DxfOle2Frame *
dxf_ole2frame_set_dictionary_owner_hard
(
        DxfOle2Frame *ole2frame,
                /*!< a pointer to a DXF \c OLE2FRAME entity. */
        char *dictionary_owner_hard
                /*!< a string containing the pointer to the
                 * dictionary_owner_hard for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ole2frame == NULL)
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
        ole2frame->dictionary_owner_hard = strdup (dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ole2frame);
}


/*!
 * \brief Get the \c lineweight from a DXF \c OLE2FRAME entity.
 *
 * \return \c lineweight when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_ole2frame_get_lineweight
(
        DxfOle2Frame *ole2frame
                /*!< a pointer to a DXF \c OLE2FRAME entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ole2frame == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ole2frame->lineweight);
}


/*!
 * \brief Set the \c lineweight for a DXF \c OLE2FRAME entity.
 *
 * \return a pointer to \c ole2frame when successful, or \c NULL when an
 * error occurred.
 */
DxfOle2Frame *
dxf_ole2frame_set_lineweight
(
        DxfOle2Frame *ole2frame,
                /*!< a pointer to a DXF \c OLE2FRAME entity. */
        int16_t lineweight
                /*!< the \c lineweight to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ole2frame == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ole2frame->lineweight = lineweight;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ole2frame);
}


/*!
 * \brief Get the \c plot_style_name from a DXF \c OLE2FRAME entity.
 *
 * \return a pointer to \c plot_style_name when sucessful, or \c NULL
 * when an error occurred.
 */
char *
dxf_ole2frame_get_plot_style_name
(
        DxfOle2Frame *ole2frame
                /*!< a pointer to a DXF \c OLE2FRAME entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ole2frame == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ole2frame->plot_style_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (ole2frame->plot_style_name));
}


/*!
 * \brief Set the \c plot_style_name for a DXF \c OLE2FRAME entity.
 *
 * \return a pointer to \c ole2frame when successful, or \c NULL when an
 * error occurred.
 */
DxfOle2Frame *
dxf_ole2frame_set_plot_style_name
(
        DxfOle2Frame *ole2frame,
                /*!< a pointer to a DXF \c OLE2FRAME entity. */
        char *plot_style_name
                /*!< a string containing the \c plot_style_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ole2frame == NULL)
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
        ole2frame->plot_style_name = strdup (plot_style_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ole2frame);
}


/*!
 * \brief Get the \c color_value from a DXF \c OLE2FRAME entity.
 *
 * \return \c color_value when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
long
dxf_ole2frame_get_color_value
(
        DxfOle2Frame *ole2frame
                /*!< a pointer to a DXF \c OLE2FRAME entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ole2frame == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ole2frame->color_value);
}


/*!
 * \brief Set the \c color_value for a DXF \c OLE2FRAME entity.
 *
 * \return a pointer to \c ole2frame when successful, or \c NULL when an
 * error occurred.
 */
DxfOle2Frame *
dxf_ole2frame_set_color_value
(
        DxfOle2Frame *ole2frame,
                /*!< a pointer to a DXF \c OLE2FRAME entity. */
        long color_value
                /*!< the \c color_value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ole2frame == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ole2frame->color_value = color_value;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ole2frame);
}


/*!
 * \brief Get the \c color_name from a DXF \c OLE2FRAME entity.
 *
 * \return \c color_name when sucessful, or \c NULL when an error
 * occurred.
 */
char *
dxf_ole2frame_get_color_name
(
        DxfOle2Frame *ole2frame
                /*!< a pointer to a DXF \c OLE2FRAME entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ole2frame == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ole2frame->color_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (ole2frame->color_name));
}


/*!
 * \brief Set the \c color_name for a DXF \c OLE2FRAME entity.
 *
 * \return a pointer to \c ole2frame when successful, or \c NULL when an
 * error occurred.
 */
DxfOle2Frame *
dxf_ole2frame_set_color_name
(
        DxfOle2Frame *ole2frame,
                /*!< a pointer to a DXF \c OLE2FRAME entity. */
        char *color_name
                /*!< a string containing the \c color_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ole2frame == NULL)
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
        ole2frame->color_name = strdup (color_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ole2frame);
}


/*!
 * \brief Get the \c transparency from a DXF \c OLE2FRAME entity.
 *
 * \return \c transparency when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
long
dxf_ole2frame_get_transparency
(
        DxfOle2Frame *ole2frame
                /*!< a pointer to a DXF \c OLE2FRAME entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ole2frame == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ole2frame->transparency);
}


/*!
 * \brief Set the \c transparency for a DXF \c OLE2FRAME entity.
 *
 * \return a pointer to \c ole2frame when successful, or \c NULL when an
 * error occurred.
 */
DxfOle2Frame *
dxf_ole2frame_set_transparency
(
        DxfOle2Frame *ole2frame,
                /*!< a pointer to a DXF \c OLE2FRAME entity. */
        long transparency
                /*!< the \c transparency to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ole2frame == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ole2frame->transparency = transparency;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ole2frame);
}


/*!
 * \brief Get the \c end_of_data from a DXF \c OLE2FRAME entity.
 *
 * \return \c end_of_data when sucessful, or \c NULL when an error
 * occurred.
 */
char *
dxf_ole2frame_get_end_of_data
(
        DxfOle2Frame *ole2frame
                /*!< a pointer to a DXF \c OLE2FRAME entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ole2frame == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ole2frame->end_of_data ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (ole2frame->end_of_data));
}


/*!
 * \brief Set the \c end_of_data for a DXF \c OLE2FRAME entity.
 *
 * \return a pointer to \c ole2frame when successful, or \c NULL when an
 * error occurred.
 */
DxfOle2Frame *
dxf_ole2frame_set_end_of_data
(
        DxfOle2Frame *ole2frame,
                /*!< a pointer to a DXF \c OLE2FRAME entity. */
        char *end_of_data
                /*!< a string containing the \c end_of_data for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ole2frame == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (end_of_data == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ole2frame->end_of_data = strdup (end_of_data);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ole2frame);
}


/*!
 * \brief Get the \c length_of_binary_data from a DXF \c OLE2FRAME entity.
 *
 * \return \c length_of_binary_data when sucessful, or \c NULL when an error
 * occurred.
 */
char *
dxf_ole2frame_get_length_of_binary_data
(
        DxfOle2Frame *ole2frame
                /*!< a pointer to a DXF \c OLE2FRAME entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ole2frame == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ole2frame->length_of_binary_data ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (ole2frame->length_of_binary_data));
}


/*!
 * \brief Set the \c length_of_binary_data for a DXF \c OLE2FRAME entity.
 *
 * \return a pointer to \c ole2frame when successful, or \c NULL when an
 * error occurred.
 */
DxfOle2Frame *
dxf_ole2frame_set_length_of_binary_data
(
        DxfOle2Frame *ole2frame,
                /*!< a pointer to a DXF \c OLE2FRAME entity. */
        char *length_of_binary_data
                /*!< a string containing the \c length_of_binary_data
                 * for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ole2frame == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (length_of_binary_data == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ole2frame->length_of_binary_data = strdup (length_of_binary_data);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ole2frame);
}


/*!
 * \brief Get the insertion point \c p0 of a DXF \c OLE2FRAME entity.
 *
 * \return the insertion point \c p0.
 */
DxfPoint *
dxf_ole2frame_get_p0
(
        DxfOle2Frame *ole2frame
                /*!< a pointer to a DXF \c OLE2FRAME entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ole2frame == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ole2frame->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ole2frame->p0);
}


/*!
 * \brief Set the insertion point \c p0 of a DXF \c OLE2FRAME entity.
 *
 * \return a pointer to a DXF \c OLE2FRAME entity.
 */
DxfOle2Frame *
dxf_ole2frame_set_p0
(
        DxfOle2Frame *ole2frame,
                /*!< a pointer to a DXF \c OLE2FRAME entity. */
        DxfPoint *p0
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ole2frame == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ole2frame->p0 = p0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ole2frame);
}


/*!
 * \brief Get the X-value of the insertion point \c x0 of a DXF
 * \c OLE2FRAME entity.
 *
 * \return the X-value of the insertion point \c x0.
 */
double
dxf_ole2frame_get_x0
(
        DxfOle2Frame *ole2frame
                /*!< a pointer to a DXF \c OLE2FRAME entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (ole2frame == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ole2frame->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ole2frame->p0->x0);
}


/*!
 * \brief Set the X-value of the insertion point \c x0 of a DXF
 * \c OLE2FRAME entity.
 *
 * \return a pointer to \c ole2frame when successful, or \c NULL when an
 * error occurred.
 */
DxfOle2Frame *
dxf_ole2frame_set_x0
(
        DxfOle2Frame *ole2frame,
                /*!< a pointer to a DXF \c OLE2FRAME entity. */
        double x0
                /*!< the X-value of the insertion point \c x0 of a DXF
                 * \c OLE2FRAME entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ole2frame == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ole2frame->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ole2frame->p0->x0 = x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ole2frame);
}


/*!
 * \brief Get the Y-value of the insertion point \c y0 of a DXF
 * \c OLE2FRAME entity.
 *
 * \return the Y-value of the insertion point \c y0.
 */
double
dxf_ole2frame_get_y0
(
        DxfOle2Frame *ole2frame
                /*!< a pointer to a DXF \c OLE2FRAME entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (ole2frame == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ole2frame->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ole2frame->p0->y0);
}


/*!
 * \brief Set the Y-value of the insertion point \c y0 of a DXF
 * \c OLE2FRAME entity.
 *
 * \return a pointer to \c ole2frame when successful, or \c NULL when an
 * error occurred.
 */
DxfOle2Frame *
dxf_ole2frame_set_y0
(
        DxfOle2Frame *ole2frame,
                /*!< a pointer to a DXF \c OLE2FRAME entity. */
        double y0
                /*!< the Y-value of the insertion point \c y0 of a DXF
                 * \c OLE2FRAME entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ole2frame == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ole2frame->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ole2frame->p0->y0 = y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ole2frame);
}


/*!
 * \brief Get the Z-value of the insertion point \c z0 of a DXF
 * \c OLE2FRAME entity.
 *
 * \return the Z-value of the insertion point \c z0.
 */
double
dxf_ole2frame_get_z0
(
        DxfOle2Frame *ole2frame
                /*!< a pointer to a DXF \c OLE2FRAME entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (ole2frame == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (ole2frame->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ole2frame->p0->z0);
}


/*!
 * \brief Set the Z-value of the insertion point \c z0 of a DXF
 * \c OLE2FRAME entity.
 *
 * \return a pointer to \c ole2frame when successful, or \c NULL when an
 * error occurred.
 */
DxfOle2Frame *
dxf_ole2frame_set_z0
(
        DxfOle2Frame *ole2frame,
                /*!< a pointer to a DXF \c OLE2FRAME entity. */
        double z0
                /*!< the Z-value of the insertion point \c z0 of a DXF
                 * \c OLE2FRAME entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ole2frame == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ole2frame->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        ole2frame->p0->z0 = z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ole2frame);
}


/*!
 * \brief Get the direction vector \c p1 of a DXF \c OLE2FRAME entity.
 *
 * \return the direction vector \c p1.
 */
DxfPoint *
dxf_ole2frame_get_p1
(
        DxfOle2Frame *ole2frame
                /*!< a pointer to a DXF \c OLE2FRAME entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (ole2frame == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ole2frame->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (ole2frame->p1);
}


/* EOF */
