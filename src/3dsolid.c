/*!
 * \file 3dsolid.c
 *
 * \author Copyright (C) 2012 ... 2014 by Bert Timmerman <bert.timmerman@xs4all.nl>.
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
        DXF_DEBUG_BEGIN
#endif
        Dxf3dsolid *dxf_3dsolid = NULL;
        size_t size;

        size = sizeof (Dxf3dsolid);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_3dsolid = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("ERROR in %s () could not allocate memory for a Dxf3dsolid struct.\n")),
                  __FUNCTION__);
                dxf_3dsolid = NULL;
        }
        else
        {
                memset (dxf_3dsolid, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
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
        DXF_DEBUG_BEGIN
#endif
        int i;

        dxf_3dsolid = dxf_3dsolid_new ();
        if (dxf_3dsolid == NULL)
        {
              fprintf (stderr,
                (_("ERROR in %s () could not allocate memory for a Dxf3dsolid struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        dxf_3dsolid->modeler_format_version_number = 0;
        dxf_3dsolid->id_code = 0;
        dxf_3dsolid->linetype = strdup (DXF_DEFAULT_LINETYPE);
        dxf_3dsolid->layer = strdup (DXF_DEFAULT_LAYER);
        dxf_3dsolid->thickness = 0.0;
        dxf_3dsolid->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        dxf_3dsolid->visibility = DXF_DEFAULT_VISIBILITY;
        dxf_3dsolid->color = DXF_COLOR_BYLAYER;
        dxf_3dsolid->paperspace = DXF_MODELSPACE;
        dxf_3dsolid->modeler_format_version_number = 1;
        dxf_3dsolid->history = strdup ("");
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                dxf_3dsolid->proprietary_data[i] = strdup ("");
                dxf_3dsolid->additional_proprietary_data[i] = strdup ("");
        }
        dxf_3dsolid->next = NULL;
#if DEBUG
        DXF_DEBUG_END
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
        DXF_DEBUG_BEGIN
#endif
        char *temp_string = NULL;
        int i;
        int j;

        if (!dxf_3dsolid)
        {
                dxf_3dsolid = dxf_3dsolid_new ();
        }
        i = 0;
        j = 0;
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
                        return (EXIT_FAILURE);
                }
                else if (strcmp (temp_string, "  1") == 0)
                {
                        /* Now follows a string containing proprietary
                         * data. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_3dsolid->proprietary_data[i]);
                        i++;
                }
                else if (strcmp (temp_string, "  3") == 0)
                {
                        /* Now follows a string containing additional
                         * proprietary data. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_3dsolid->additional_proprietary_data[j]);
                        j++;
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
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing the linetype
                         * scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_3dsolid->linetype_scale);
                }
                else if (strcmp (temp_string, "60") == 0)
                {
                        /* Now follows a string containing the
                         * visibility value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &dxf_3dsolid->visibility);
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
                                fprintf (stderr,
                                  (_("Error in %s () found a bad subclass marker in: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
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
                                fprintf (stderr,
                                  (_("Error in %s () found a bad subclass marker in: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
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
                        fprintf (stdout, (_("DXF comment: %s\n")), temp_string);
                }
                else
                {
                        fprintf (stderr,
                          (_("Warning in %s () unknown string tag found while reading from: %s in line: %d.\n")),
                          __FUNCTION__, fp->filename, fp->line_number);
                }
        }
#if DEBUG
        DXF_DEBUG_END
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
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("3DSOLID");
        int i;

        /* Do some basic checks. */
        if (dxf_3dsolid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (strcmp (dxf_3dsolid->layer, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, dxf_3dsolid->id_code);
                fprintf (stderr,
                  (_("    %s entity is relocated to layer 0")),
                  dxf_entity_name);
                dxf_3dsolid->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (dxf_3dsolid->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", dxf_3dsolid->id_code);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
        }
        if (dxf_3dsolid->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
        fprintf (fp->fp, "  8\n%s\n", dxf_3dsolid->layer);
        if (strcmp (dxf_3dsolid->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", dxf_3dsolid->linetype);
        }
        if (dxf_3dsolid->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", dxf_3dsolid->color);
        }
        if (dxf_3dsolid->thickness != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", dxf_3dsolid->thickness);
        }
        if (dxf_3dsolid->linetype_scale != 1.0)
        {
                fprintf (fp->fp, " 48\n%f\n", dxf_3dsolid->linetype_scale);
        }
        if (dxf_3dsolid->visibility != 0)
        {
                fprintf (fp->fp, " 60\n%d\n", dxf_3dsolid->visibility);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbModelerGeometry\n");
        }
        if (fp->acad_version_number >= AutoCAD_2008)
        {
                fprintf (fp->fp, "100\nAcDb3dSolid\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, " 70\n%d\n", dxf_3dsolid->modeler_format_version_number);
        }
        i = 0;
        while (strlen (dxf_3dsolid->proprietary_data[i]) > 0)
        {
                fprintf (fp->fp, "  1\n%s\n", dxf_3dsolid->proprietary_data[i]);
                i++;
        }
        i = 0;
        while (strlen (dxf_3dsolid->additional_proprietary_data[i]) > 0)
        {
                fprintf (fp->fp, "  3\n%s\n", dxf_3dsolid->additional_proprietary_data[i]);
                i++;
        }
        if (fp->acad_version_number >= AutoCAD_2008)
        {
                fprintf (fp->fp, "350\n%s\n", dxf_3dsolid->history);
        }
#if DEBUG
        DXF_DEBUG_END
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
        DXF_DEBUG_BEGIN
#endif
        int i;

        if (dxf_3dsolid->next != NULL)
        {
              fprintf (stderr,
                (_("ERROR in %s () pointer to next Dxf3dsolid was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (dxf_3dsolid->linetype);
        free (dxf_3dsolid->layer);
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                free (dxf_3dsolid->proprietary_data[i]);
                free (dxf_3dsolid->additional_proprietary_data[i]);
        }
        free (dxf_3dsolid);
        dxf_3dsolid = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
