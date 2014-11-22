/*!
 * \file oleframe.c
 *
 * \author Copyright (C) 2013 ... 2014 by Bert Timmerman <bert.timmerman@xs4all.nl>.
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
        DxfOleFrame *dxf_oleframe = NULL;
        size_t size;

        size = sizeof (DxfOleFrame);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_oleframe = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfOleFrame struct.\n")),
                  __FUNCTION__);
                dxf_oleframe = NULL;
        }
        else
        {
                memset (dxf_oleframe, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_oleframe);
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
        DxfOleFrame *dxf_oleframe
                /*!< DXF \c OLEFRAME entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        /* Do some basic checks. */
        if (dxf_oleframe == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                dxf_oleframe = dxf_oleframe_new ();
        }
        if (dxf_oleframe == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory for a DxfOleFrame struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        dxf_oleframe->id_code = 0;
        dxf_oleframe->linetype = strdup (DXF_DEFAULT_LINETYPE);
        dxf_oleframe->layer = strdup (DXF_DEFAULT_LAYER);
        dxf_oleframe->elevation = 0.0;
        dxf_oleframe->thickness = 0.0;
        dxf_oleframe->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        dxf_oleframe->visibility = DXF_DEFAULT_VISIBILITY;
        dxf_oleframe->color = DXF_COLOR_BYLAYER;
        dxf_oleframe->paperspace = DXF_MODELSPACE;
        dxf_oleframe->dictionary_owner_soft = strdup ("");
        dxf_oleframe->dictionary_owner_hard = strdup ("");
        dxf_oleframe->ole_version_number = 1;
        dxf_oleframe->length = 0;
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                dxf_oleframe->binary_data[i] = strdup ("");
        }
        dxf_oleframe->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_oleframe);
}


/*!
 * \brief Read data from a DXF file into a DXF \c OLEFRAME entity.
 *
 * The last line read from file contained the string "OLEFRAME". \n
 * Now follows some data for the \c OLEFRAME, to be terminated with a "  0"
 * string announcing the following entity, or the end of the \c ENTITY
 * section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c dxf_oleframe. \n
 *
 * \return a pointer to \c dxf_oleframe.
 *
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfOleFrame *
dxf_oleframe_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfOleFrame *dxf_oleframe
                /*!< DXF \c OLEFRAME entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *temp_string = NULL;
        int i;

        /* Do some basic checks. */
        if (dxf_oleframe == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                dxf_oleframe = dxf_oleframe_new ();
                dxf_oleframe_init (dxf_oleframe);
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
                                  (_("Error in %s () found a bad End of Ole data marker in: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                        }
                }
                if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", &dxf_oleframe->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_oleframe->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_oleframe->layer);
                }
                else if ((fp->acad_version_number <= AutoCAD_11)
                        && (strcmp (temp_string, "38") == 0)
                        && (dxf_oleframe->elevation != 0.0))
                {
                        /* Now follows a string containing the
                         * elevation. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_oleframe->elevation);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_oleframe->thickness);
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing the linetype
                         * scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_oleframe->linetype_scale);
                }
                else if (strcmp (temp_string, "60") == 0)
                {
                        /* Now follows a string containing the
                         * visibility value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &dxf_oleframe->visibility);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_oleframe->color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_oleframe->paperspace);
                }
                else if (strcmp (temp_string, "70") == 0)
                {
                        /* Now follows a string containing the ole
                         * version number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_oleframe->ole_version_number);
                }
                else if (strcmp (temp_string, "90") == 0)
                {
                        /* Now follows a string containing the length of
                         * binary data. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%ld\n", &dxf_oleframe->length);
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
                        fscanf (fp->fp, "%s\n", dxf_oleframe->binary_data[i]);
                        i++;
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing Soft-pointer
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_oleframe->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_oleframe->dictionary_owner_hard);
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
        if (strcmp (dxf_oleframe->linetype, "") == 0)
        {
                dxf_oleframe->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (dxf_oleframe->layer, "") == 0)
        {
                dxf_oleframe->layer = strdup (DXF_DEFAULT_LAYER);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_oleframe);
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
        DxfOleFrame *dxf_oleframe
                /*!< DXF \c OLEFRAME entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("OLEFRAME");
        int i;

        /* Do some basic checks. */
        if (fp->acad_version_number < AutoCAD_13)
        {
                fprintf (stderr,
                  (_("Error in %s () illegal DXF version for this entity.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dxf_oleframe == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (strcmp (dxf_oleframe->linetype, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty linetype string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, dxf_oleframe->id_code);
                fprintf (stderr,
                  (_("\t%s entity is reset to default linetype")),
                  dxf_entity_name);
                dxf_oleframe->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (dxf_oleframe->layer, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, dxf_oleframe->id_code);
                fprintf (stderr,
                  (_("\t%s entity is relocated to layer 0")),
                  dxf_entity_name);
                dxf_oleframe->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (dxf_oleframe->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", dxf_oleframe->id_code);
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
        if ((strcmp (dxf_oleframe->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", dxf_oleframe->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (dxf_oleframe->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", dxf_oleframe->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
        }
        if (dxf_oleframe->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
        fprintf (fp->fp, "  8\n%s\n", dxf_oleframe->layer);
        if (strcmp (dxf_oleframe->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", dxf_oleframe->linetype);
        }
        if ((fp->acad_version_number <= AutoCAD_11)
          && DXF_FLATLAND
          && (dxf_oleframe->elevation != 0.0))
        {
                fprintf (fp->fp, " 38\n%f\n", dxf_oleframe->elevation);
        }
        if (dxf_oleframe->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", dxf_oleframe->color);
        }
        if (dxf_oleframe->linetype_scale != 1.0)
        {
                fprintf (fp->fp, " 48\n%f\n", dxf_oleframe->linetype_scale);
        }
        if (dxf_oleframe->visibility != 0)
        {
                fprintf (fp->fp, " 60\n%d\n", dxf_oleframe->visibility);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbOleFrame\n");
        }
        if (dxf_oleframe->thickness != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", dxf_oleframe->thickness);
        }
        fprintf (fp->fp, " 70\n%d\n", dxf_oleframe->ole_version_number);
        fprintf (fp->fp, " 90\n%ld\n", dxf_oleframe->length);
        i = 0;
        while (strlen (dxf_oleframe->binary_data[i]) > 0)
        {
                fprintf (fp->fp, "310\n%s\n", dxf_oleframe->binary_data[i]);
                i++;
        }
        fprintf (fp->fp, "  1\nOLE\n");
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
        DxfOleFrame *dxf_oleframe
                /*!< Pointer to the memory occupied by the DXF
                 * \c OLEFRAME entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        if (dxf_oleframe->next != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to next DxfOleFrame was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (dxf_oleframe->linetype);
        free (dxf_oleframe->layer);
        free (dxf_oleframe->dictionary_owner_soft);
        free (dxf_oleframe->dictionary_owner_hard);
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                free (dxf_oleframe->binary_data[i]);
        }
        free (dxf_oleframe);
        dxf_oleframe = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
