/*!
 * \file appid.c
 * \author Copyright (C) 2009 ... 2012 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 * \brief Functions for a DXF application identity entity (\c APPID).
 *
 * A DXF \c APPID entity contains data concerning the application registered
 * with the drawing involved.\n
 * It is a table entry in the \c TABLES section of the DXF file.
 * These table entries maintain a set of names for all applications
 * registered with a drawing.
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


#include "appid.h"


/*!
 * \brief Allocate memory for a \c DxfAppid.
 *
 * Fill the memory contents with zeros.
 */
DxfAppid *
dxf_appid_new ()
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_appid_new () function.\n",
                __FILE__, __LINE__);
#endif
        DxfAppid *dxf_appid = NULL;
        size_t size;

        size = sizeof (DxfAppid);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_appid = malloc (size)) == NULL)
        {
                fprintf (stderr, "ERROR in dxf_appid_new () could not allocate memory for a DxfAppid struct.\n");
                dxf_appid = NULL;
        }
        else
        {
                memset (dxf_appid, 0, size);
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_appid_new () function.\n",
                __FILE__, __LINE__);
#endif
        return (dxf_appid);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c APPID
 * entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfAppid *
dxf_appid_init
(
        DxfAppid *dxf_appid
                /*!< DXF application id entity. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_appid_init () function.\n",
                __FILE__, __LINE__);
#endif
        dxf_appid = dxf_appid_new ();
        if (dxf_appid == NULL)
        {
              fprintf (stderr, "ERROR in dxf_appid_init () could not allocate memory for a DxfAppid struct.\n");
              return (NULL);
        }
        dxf_appid->id_code = 0;
        dxf_appid->application_name = strdup ("");
        dxf_appid->standard_flag = 0;
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_appid_init () function.\n",
                __FILE__, __LINE__);
#endif
        return (dxf_appid);
}


/*!
 * \brief Read data from a DXF file into an \c APPID entity.
 *
 * The last line read from file contained the string "APPID". \n
 * Now follows some data for the \c ARC, to be terminated with a "  0"
 * string announcing the following entity, or the end of the \c ENTITY
 * section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c dxf_appid. \n
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_appid_read
(
        char *filename,
                /*!< filename of input file (or device). */
        FILE *fp,
                /*!< filepointer to the input file (or device). */
        int *line_number,
                /*!< current line number in the input file (or device). */
        DxfAppid *dxf_appid,
                /*!< DXF appid entity. */
        int acad_version_number
                /*!< AutoCAD version number. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_appid_read () function.\n",
                __FILE__, __LINE__);
#endif
        char *temp_string = NULL;

        if (!dxf_appid)
        {
                dxf_appid = dxf_appid_new ();
        }
        (*line_number)++;
        fscanf (fp, "%[^\n]", temp_string);
        while (strcmp (temp_string, "0") != 0)
        {
                if (ferror (fp))
                {
                        fprintf (stderr, "Error in dxf_appid_read () while reading from: %s in line: %d.\n",
                                filename, *line_number);
                        fclose (fp);
                        return (EXIT_FAILURE);
                }
                if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (*line_number)++;
                        fscanf (fp, "%x\n", &dxf_appid->id_code);
                }
                else if (strcmp (temp_string, "2") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (*line_number)++;
                        fscanf (fp, "%s\n", dxf_appid->application_name);
                }
                else if (strcmp (temp_string, "70") == 0)
                {
                        /* Now follows a string containing the
                         * standard flag value. */
                        (*line_number)++;
                        fscanf (fp, "%d\n", &dxf_appid->standard_flag);
                }
                else if (strcmp (temp_string, "999") == 0)
                {
                        /* Now follows a string containing a comment. */
                        (*line_number)++;
                        fscanf (fp, "%s\n", temp_string);
                        fprintf (stdout, "DXF comment: %s\n", temp_string);
                }
                else
                {
                        fprintf (stderr, "Warning: in dxf_appid_read () unknown string tag found while reading from: %s in line: %d.\n",
                                filename, *line_number);
                }
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_appid_read () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write DXF output for an \c APPID entity.
 */
static int
dxf_appid_write_lowlevel
(
        FILE *fp,
                /*!< File pointer to output file (or device). */
        int acad_version_number,
                /*!< AutoCAD version number. */
        int id_code,
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file.\n
                 * Group code = 5. */
        char *application_name,
                /*!< Name of the application registered with the drawing.\n
                 * Group code = 2. */
        int standard_flag
                /*!< This flag is for the benefit of AutoCAD commands;
                 * it can be ignored by most programs that read DXF files,
                 * and need not be set by programs that write DXF files.\n
                 * bit coded:\n
                 * 16 = if set, table entry is externally dependent on an
                 *      Xref.\n
                 * 32 = if this bit and bit 16 are both set, the externally
                 *      dependent Xref has been successfully resolved.\n
                 * 64 = if set, the table entry was referenced by at least
                 *      one entity in the drawing the last time the drawing
                 *      was edited.\n
                 * Group code = 70. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_appid_write_lowlevel () function.\n",
                __FILE__, __LINE__);
#endif
        char *dxf_entity_name = strdup ("APPID");

        if (strcmp (application_name, "") == 0)
        {
                fprintf (stderr, "Warning: empty application name string for the %s entity with id-code: %x\n",
                        dxf_entity_name, id_code);
                fprintf (stderr, "    %s entity is discarded from output.\n",
                        dxf_entity_name);
                return (EXIT_FAILURE);
        }
        fprintf (fp, "  0\n%s\n", dxf_entity_name);
        if (id_code != -1)
        {
                fprintf (fp, "  5\n%x\n", id_code);
        }
        fprintf (fp, "  2\n%s\n", application_name);
        fprintf (fp, " 70\n%d\n", standard_flag);
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_appid_write_lowlevel () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write DXF output to a file for an \c APPID entity.
 */
int
dxf_appid_write
(
        FILE *fp,
                /*!< file pointer to output file (or device). */
        DxfAppid dxf_appid
                /*!< DXF appid entity. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_appid_write () function.\n",
                __FILE__, __LINE__);
#endif
        char *dxf_entity_name = strdup ("APPID");
        if (dxf_appid.application_name == NULL)
        {
                fprintf (stderr, "Warning: empty block name string for the %s entity with id-code: %x\n",
                        dxf_entity_name, dxf_appid.id_code);
                fprintf (stderr, "         %s entity is discarded from output.\n",
                        dxf_entity_name);
                return (EXIT_FAILURE);
        }
        fprintf (fp, "  0\n%s\n", dxf_entity_name);
        if (dxf_appid.id_code != -1)
        {
                fprintf (fp, "  5\n%x\n", dxf_appid.id_code);
        }
        fprintf (fp, "  2\n%s\n", dxf_appid.application_name);
        fprintf (fp, " 70\n%d\n", dxf_appid.standard_flag);
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_appid_write () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocate memory for a DXF \c APPID and all it's
 * members.
 */
int
dxf_appid_free
(
        DxfAppid *dxf_appid
                /*!< DXF \c APPID entity. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_appid_free () function.\n",
                __FILE__, __LINE__);
#endif
        free (dxf_appid->application_name);
        free (dxf_appid);
        dxf_appid = NULL;
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_appid_free () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/* EOF*/
