/*!
 * \file 3dsolid.c
 *
 * \author Copyright (C) 2012 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF 3D solid entity (\c 3DSOLID).
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


#include "3dsolid.h"


/*!
 * \brief Allocate memory for a \c Dxf3dsolid.
 *
 * Fill the memory contents with zeros.
 */
Dxf3dsolid *
dxf_3dsolid_new ()
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_3dsolid_new () function.\n",
                __FILE__, __LINE__);
#endif
        Dxf3dsolid *dxf_3dsolid = NULL;
        size_t size;

        size = sizeof (Dxf3dsolid);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_3dsolid = malloc (size)) == NULL)
        {
                fprintf (stderr, "ERROR in dxf_3dsolid_new () could not allocate memory for a Dxf3dsolid struct.\n");
                dxf_3dsolid = NULL;
        }
        else
        {
                memset (dxf_3dsolid, 0, size);
        }
/*!
 * \todo Allocate memory for data fields and fill with NULL pointers ?
 * <pre>
        int i;
        int j;

        if ((dxf_3dsolid->proprietary_data = malloc (DXF_MAX_STRING_LENGTH * DXF_MAX_PARAM)) == NULL)
        {
                fprintf (stderr, "ERROR in dxf_3dsolid_init () could not allocate memory for a Dxf3dsolid struct.\n");
                dxf_3dsolid = NULL;
        }
        if ((dxf_3dsolid->additional_proprietary_data = malloc (DXF_MAX_STRING_LENGTH * DXF_MAX_PARAM)) == NULL)
        {
                fprintf (stderr, "ERROR in dxf_3dsolid_init () could not allocate memory for a Dxf3dsolid struct.\n");
                dxf_3dsolid = NULL;
        }
        for (i = 0; i <= DXF_MAX_STRING_LENGTH; i++)
        {
                for (j = 0; j <= DXF_MAX_PARAM; j++)
                {
                        dxf_3dsolid->proprietary_data[i][j] = NULL;
                        dxf_3dsolid->additional_proprietary_data[i][j] = NULL;
                }
        }
 * </pre>
 */
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_3dsolid_new () function.\n",
                __FILE__, __LINE__);
#endif
        return (dxf_3dsolid);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c 3DSOLID
 * entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
Dxf3dsolid *
dxf_3dsolid_init
(
        Dxf3dsolid *dxf_3dsolid
                /*!< DXF \c 3DSOLID entity. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_3dsolid_init () function.\n",
                __FILE__, __LINE__);
#endif
        dxf_3dsolid = dxf_3dsolid_new ();
        if (dxf_3dsolid == NULL)
        {
              fprintf (stderr, "ERROR in dxf_3dsolid_init () could not allocate memory for a Dxf3dsolid struct.\n");
              return (NULL);
        }
        dxf_3dsolid->modeler_format_version_number = 0;
        dxf_3dsolid->id_code = 0;
        dxf_3dsolid->linetype = strdup (DXF_DEFAULT_LINETYPE);
        dxf_3dsolid->layer = strdup (DXF_DEFAULT_LAYER);
        dxf_3dsolid->thickness = 0.0;
        dxf_3dsolid->color = DXF_COLOR_BYLAYER;
        dxf_3dsolid->paperspace = DXF_MODELSPACE;
        dxf_3dsolid->modeler_format_version_number = 1;
        dxf_3dsolid->history = strdup ("");
        dxf_3dsolid->next = NULL;
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_3dsolid_init () function.\n",
                __FILE__, __LINE__);
#endif
        return (dxf_3dsolid);
}


/*!
 * \brief Read data from a DXF file into a DXF \c 3DSOLID entity.
 *
 * The last line read from file contained the string "3DSOLID". \n
 * Now follows some data for the \c 3DSOLID, to be terminated with a "  0"
 * string announcing the following entity, or the end of the \c ENTITY
 * section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c dxf_3dsolid. \n
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_3dsolid_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        Dxf3dsolid *dxf_3dsolid
                /*!< DXF \c 3DSOLID entity. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_3dsolid_read () function.\n",
                __FILE__, __LINE__);
#endif
        char *temp_string = NULL;

        if (!dxf_3dsolid)
        {
                dxf_3dsolid = dxf_3dsolid_new ();
        }
        (fp->line_number)++;
        fscanf (fp->fp, "%[^\n]", temp_string);
        while (strcmp (temp_string, "0") != 0)
        {
                if (ferror (fp->fp))
                {
                        fprintf (stderr, "Error in dxf_3dsolid_read () while reading from: %s in line: %d.\n",
                                fp->filename, fp->line_number);
                        fclose (fp->fp);
                        return (EXIT_FAILURE);
                }
                if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", &dxf_3dsolid->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_3dsolid->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_3dsolid->layer);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_3dsolid->thickness);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_3dsolid->color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_3dsolid->paperspace);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "70") == 0))
                {
                        /* Now follows a string containing the modeler
                         * format version number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_3dsolid->modeler_format_version_number);
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
                                fprintf (stderr, "Error in dxf_3dsolid_read () found a bad subclass marker in: %s in line: %d.\n",
                                        fp->filename, fp->line_number);
                        }
                }
                else if ((fp->acad_version_number >= AutoCAD_2008)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
                        if (strcmp (temp_string, "AcDb3dSolid") != 0)
                        {
                                fprintf (stderr, "Error in dxf_3dsolid_read () found a bad subclass marker in: %s in line: %d.\n",
                                        fp->filename, fp->line_number);
                        }
                }
                else if ((fp->acad_version_number >= AutoCAD_2008)
                        && (strcmp (temp_string, "350") == 0))
                {
                        /* Now follows a string containing a handle to a
                         * history object. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_3dsolid->history);
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
                        fprintf (stderr, "Warning: in dxf_3dsolid_read () unknown string tag found while reading from: %s in line: %d.\n",
                                fp->filename, fp->line_number);
                }
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_3dsolid_read () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write DXF output to a file for a DXF \c 3DSOLID entity.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred while reading from the input file.
 */
int
dxf_3dsolid_write_lowlevel
(
        FILE *fp,
                /*!< file pointer to output file (or device). */
        int id_code,
                /*!< group code = 5. */
        char *linetype,
                /*!< group code = 6\n
                 * optional, defaults to \c BYLAYER. */
        char *layer,
                /*!< group code = 8. */
        double thickness,
                /*!< group code = 39\n
                 * optional, defaults to 0.0. */
        int color,
                /*!< group code = 62\n
                 * optional, defaults to \c BYLAYER */
        int paperspace,
                /*!< group code = 67\n
                 * optional, defaults to 0 (modelspace). */
        char *proprietary_data[DXF_MAX_STRING_LENGTH][DXF_MAX_PARAM],
                /*!< group code = 1\n
                 * Proprietary data (multiple lines < 255 characters
                 * each).*/
        char *additional_proprietary_data[DXF_MAX_STRING_LENGTH][DXF_MAX_PARAM],
                /*!< group code = 3\n
                 * Additional lines of proprietary data if previous
                 * group 1 string is greater than 255 characters
                 * (optional).*/
        int modeler_format_version_number,
                /*!< group code = 70\n
                 * Modeler format version number (currently = 1).\n */
        char *history,
                /*!< group code = 350\n
                 * Soft-owner ID / handle to history object. */
        int acad_version_number
                /*!< AutoCAD version number. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_3dsolid_write_lowlevel () function.\n",
                __FILE__, __LINE__);
#endif
        int i;
        char *dxf_entity_name = strdup ("3DSOLID");

        if (strcmp (layer, "") == 0)
        {
                fprintf (stderr, "Warning in dxf_3dsolid_write_lowlevel () empty layer string for the %s entity with id-code: %x\n",
                        dxf_entity_name, id_code);
                fprintf (stderr, "    %s entity is relocated to layer 0",
                        dxf_entity_name);
                layer = strdup (DXF_DEFAULT_LAYER);
        }
        fprintf (fp, "  0\n%s\n", dxf_entity_name);
        if (id_code != -1)
        {
                fprintf (fp, "  5\n%x\n", id_code);
        }
        if (acad_version_number >= AutoCAD_13)
        {
                fprintf (fp, "100\nAcDbModelerGeometry\n");
        }
        if (acad_version_number >= AutoCAD_2008)
        {
                fprintf (fp, "100\nAcDb3dSolid\n");
        }
        if (strcmp (linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp, "  6\n%s\n", linetype);
        }
        fprintf (fp, "  8\n%s\n", layer);
        if (thickness != 0.0)
        {
                fprintf (fp, " 39\n%f\n", thickness);
        }
        if (color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp, " 62\n%d\n", color);
        }
        if (paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
        if (acad_version_number >= AutoCAD_13)
        {
                fprintf (fp, " 70\n%d\n", modeler_format_version_number);
        }
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                if (strcmp (proprietary_data[DXF_MAX_STRING_LENGTH][i], "") == 0)
                {
                        break;
                }
                else
                {
                        fprintf (fp, "  1\n%s\n", proprietary_data[DXF_MAX_STRING_LENGTH][i]);
                }
        }
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                if (strcmp (additional_proprietary_data[DXF_MAX_STRING_LENGTH][i], "") == 0)
                {
                        break;
                }
                else
                {
                        fprintf (fp, "  3\n%s\n", additional_proprietary_data[DXF_MAX_STRING_LENGTH][i]);
                }
        }
        if (acad_version_number >= AutoCAD_2008)
        {
                fprintf (fp, "350\n%s\n", history);
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_3dsolid_write_lowlevel () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write DXF output to a file for a DXF \c 3DSOLID entity.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred while reading from the input file.
 */
int
dxf_3dsolid_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        Dxf3dsolid *dxf_3dsolid
                /*!< DXF \c 3DSOLID entity. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_3dsolid_write_lowlevel () function.\n",
                __FILE__, __LINE__);
#endif
        int i;
        char *dxf_entity_name = strdup ("3DSOLID");

        if (strcmp (dxf_3dsolid->layer, "") == 0)
        {
                fprintf (stderr, "Warning in dxf_3dsolid_write_lowlevel () empty layer string for the %s entity with id-code: %x\n",
                        dxf_entity_name, dxf_3dsolid->id_code);
                fprintf (stderr, "    %s entity is relocated to layer 0",
                        dxf_entity_name);
                dxf_3dsolid->layer = strdup (DXF_DEFAULT_LAYER);
        }
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (dxf_3dsolid->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", dxf_3dsolid->id_code);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbModelerGeometry\n");
        }
        if (fp->acad_version_number >= AutoCAD_2008)
        {
                fprintf (fp->fp, "100\nAcDb3dSolid\n");
        }
        if (strcmp (dxf_3dsolid->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", dxf_3dsolid->linetype);
        }
        fprintf (fp->fp, "  8\n%s\n", dxf_3dsolid->layer);
        if (dxf_3dsolid->thickness != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", dxf_3dsolid->thickness);
        }
        if (dxf_3dsolid->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", dxf_3dsolid->color);
        }
        if (dxf_3dsolid->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, " 70\n%d\n", dxf_3dsolid->modeler_format_version_number);
        }
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                if (strcmp (dxf_3dsolid->proprietary_data[DXF_MAX_STRING_LENGTH][i], "") == 0)
                /*! \todo warning: array subscript is above array bounds.*/
                {
                        break;
                }
                else
                {
                        fprintf (fp->fp, "  1\n%s\n", dxf_3dsolid->proprietary_data[DXF_MAX_STRING_LENGTH][i]);
                }
        }
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                if (strcmp (dxf_3dsolid->additional_proprietary_data[DXF_MAX_STRING_LENGTH][i], "") == 0)
                /*! \todo warning: array subscript is above array bounds.*/
                {
                        break;
                }
                else
                {
                        fprintf (fp->fp, "  3\n%s\n", dxf_3dsolid->additional_proprietary_data[DXF_MAX_STRING_LENGTH][i]);
                }
        }
        if (fp->acad_version_number >= AutoCAD_2008)
        {
                fprintf (fp->fp, "350\n%s\n", dxf_3dsolid->history);
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_3dsolid_write_lowlevel () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c 3DSOLID and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_3dsolid_free
(
        Dxf3dsolid *dxf_3dsolid
                /*!< Pointer to the memory occupied by the DXF
                 * \c 3DSOLID entity. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_3dsolid_free () function.\n",
                __FILE__, __LINE__);
#endif
        if (dxf_3dsolid->next != NULL)
        {
              fprintf (stderr, "ERROR in dxf_3dsolid_free () pointer to next Dxf3dsolid was not NULL.\n");
              return (EXIT_FAILURE);
        }
        free (dxf_3dsolid->linetype);
        free (dxf_3dsolid->layer);
        free (dxf_3dsolid);
        dxf_3dsolid = NULL;
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_3dsolid_free () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
