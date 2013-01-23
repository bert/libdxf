/*!
 * \file body.c
 *
 * \author Copyright (C) 2013 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF body entity (\c BODY).
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


#include "body.h"


/*!
 * \brief Allocate memory for a \c DxfBody.
 *
 * Fill the memory contents with zeros.
 */
DxfBody *
dxf_body_new ()
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_body_new () function.\n",
                __FILE__, __LINE__);
#endif
        DxfBody *dxf_body = NULL;
        size_t size;

        size = sizeof (DxfBody);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_body = malloc (size)) == NULL)
        {
                fprintf (stderr, "ERROR in dxf_body_new () could not allocate memory for a DxfBody struct.\n");
                dxf_body = NULL;
        }
        else
        {
                memset (dxf_body, 0, size);
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_body_new () function.\n",
                __FILE__, __LINE__);
#endif
        return (dxf_body);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c BODY
 * entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfBody *
dxf_body_init
(
        DxfBody *dxf_body
                /*!< DXF \c BODY entity. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_body_init () function.\n",
                __FILE__, __LINE__);
#endif
        int i;

        dxf_body = dxf_body_new ();
        if (dxf_body == NULL)
        {
              fprintf (stderr, "ERROR in dxf_body_init () could not allocate memory for a DxfBody struct.\n");
              return (NULL);
        }
        dxf_body->modeler_format_version_number = 0;
        dxf_body->id_code = 0;
        dxf_body->linetype = strdup (DXF_DEFAULT_LINETYPE);
        dxf_body->layer = strdup (DXF_DEFAULT_LAYER);
        dxf_body->thickness = 0.0;
        dxf_body->color = DXF_COLOR_BYLAYER;
        dxf_body->paperspace = DXF_MODELSPACE;
        dxf_body->modeler_format_version_number = 1;
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                dxf_body->proprietary_data[i] = strdup ("");
                dxf_body->additional_proprietary_data[i] = strdup ("");
        }
        dxf_body->next = NULL;
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_body_init () function.\n",
                __FILE__, __LINE__);
#endif
        return (dxf_body);
}


/*!
 * \brief Read data from a DXF file into a DXF \c BODY entity.
 *
 * The last line read from file contained the string "BODY". \n
 * Now follows some data for the \c BODY, to be terminated with a "  0"
 * string announcing the following entity, or the end of the \c ENTITY
 * section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c dxf_body. \n
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_body_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfBody *dxf_body
                /*!< DXF \c BODY entity. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_body_read () function.\n",
                __FILE__, __LINE__);
#endif
        char *temp_string = NULL;
        int i;
        int j;

        if (!dxf_body)
        {
                dxf_body = dxf_body_new ();
        }
        i = 0;
        j = 0;
        (fp->line_number)++;
        fscanf (fp->fp, "%[^\n]", temp_string);
        while (strcmp (temp_string, "0") != 0)
        {
                if (ferror (fp->fp))
                {
                        fprintf (stderr, "Error in dxf_body_read () while reading from: %s in line: %d.\n",
                                fp->filename, fp->line_number);
                        fclose (fp->fp);
                        return (EXIT_FAILURE);
                }
                else if (strcmp (temp_string, "  1") == 0)
                {
                        /* Now follows a string containing proprietary
                         * data. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_body->proprietary_data[i]);
                        i++;
                }
                else if (strcmp (temp_string, "  3") == 0)
                {
                        /* Now follows a string containing additional
                         * proprietary data. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_body->additional_proprietary_data[j]);
                        i++;
                }
                if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", &dxf_body->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_body->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_body->layer);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_body->thickness);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_body->color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_body->paperspace);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "70") == 0))
                {
                        /* Now follows a string containing the modeler
                         * format version number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_body->modeler_format_version_number);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
                        if (strcmp (temp_string, "AcDbModelerGeometry") != 0)
                        {
                                fprintf (stderr, "Error in dxf_body_read () found a bad subclass marker in: %s in line: %d.\n",
                                        fp->filename, fp->line_number);
                        }
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
                        fprintf (stderr, "Warning: in dxf_body_read () unknown string tag found while reading from: %s in line: %d.\n",
                                fp->filename, fp->line_number);
                }
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_body_read () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write DXF output to a file for a DXF \c BODY entity.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred while reading from the input file.
 */
int
dxf_body_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfBody *dxf_body
                /*!< DXF \c BODY entity. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_body_write_lowlevel () function.\n",
                __FILE__, __LINE__);
#endif
        char *dxf_entity_name = strdup ("BODY");
        int i;

        if (strcmp (dxf_body->layer, "") == 0)
        {
                fprintf (stderr, "Warning in dxf_body_write_lowlevel () empty layer string for the %s entity with id-code: %x\n",
                        dxf_entity_name, dxf_body->id_code);
                fprintf (stderr, "    %s entity is relocated to layer 0",
                        dxf_entity_name);
                dxf_body->layer = strdup (DXF_DEFAULT_LAYER);
        }
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (dxf_body->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", dxf_body->id_code);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
                fprintf (fp->fp, "100\nAcDbModelerGeometry\n");
        }
        if (strcmp (dxf_body->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", dxf_body->linetype);
        }
        fprintf (fp->fp, "  8\n%s\n", dxf_body->layer);
        if (dxf_body->thickness != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", dxf_body->thickness);
        }
        if (dxf_body->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", dxf_body->color);
        }
        if (dxf_body->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, " 70\n%d\n", dxf_body->modeler_format_version_number);
        }
        i = 0;
        while (strlen (dxf_body->proprietary_data[i]) > 0)
        {
                fprintf (fp->fp, "  1\n%s\n", dxf_body->proprietary_data[i]);
                i++;
        }
        i = 0;
        while (strlen (dxf_body->additional_proprietary_data[i]) > 0)
        {
                fprintf (fp->fp, "  3\n%s\n", dxf_body->additional_proprietary_data[i]);
                i++;
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_body_write_lowlevel () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c BODY and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_body_free
(
        DxfBody *dxf_body
                /*!< Pointer to the memory occupied by the DXF
                 * \c BODY entity. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_body_free () function.\n",
                __FILE__, __LINE__);
#endif
        int i;

        if (dxf_body->next != NULL)
        {
              fprintf (stderr, "ERROR in dxf_body_free () pointer to next DxfBody was not NULL.\n");
              return (EXIT_FAILURE);
        }
        free (dxf_body->linetype);
        free (dxf_body->layer);
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                free (dxf_body->proprietary_data[i]);
                free (dxf_body->additional_proprietary_data[i]);
        }
        free (dxf_body);
        dxf_body = NULL;
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_body_free () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
