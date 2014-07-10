/*!
 * \file appid.c
 *
 * \author Copyright (C) 2009 ... 2014 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF application identity entity (\c APPID).
 *
 * A DXF \c APPID entity contains data concerning the application registered
 * with the drawing involved.\n
 * It is a table entry in the \c TABLES section of the DXF file.\n
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
 * \brief Allocate memory for a DXF \c APPID entity.
 *
 * Fill the memory contents with zeros.
 */
DxfAppid *
dxf_appid_new ()
{
#if DEBUG
        fprintf (stderr,
          (_("[File: %s: line: %d] ")),
          (_("Entering %s () function.\n")),
          __FILE__, __LINE__, __FUNCTION__);
#endif
        DxfAppid *dxf_appid = NULL;
        size_t size;

        size = sizeof (DxfAppid);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_appid = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("ERROR in %s () could not allocate memory for a DxfAppid struct.\n")),
                  __FUNCTION__);
                dxf_appid = NULL;
        }
        else
        {
                memset (dxf_appid, 0, size);
        }
#if DEBUG
        fprintf (stderr,
          (_("[File: %s: line: %d] ")),
          (_("Leaving %s () function.\n")),
          __FILE__, __LINE__, __FUNCTION__);
#endif
        return (dxf_appid);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c APPID
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
        fprintf (stderr,
          (_("[File: %s: line: %d] ")),
          (_("Entering %s () function.\n")),
          __FILE__, __LINE__, __FUNCTION__);
#endif
        dxf_appid = dxf_appid_new ();
        if (dxf_appid == NULL)
        {
              fprintf (stderr,
                (_("ERROR in %s () could not allocate memory for a DxfAppid struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        dxf_appid->id_code = 0;
        dxf_appid->application_name = strdup ("");
        dxf_appid->standard_flag = 0;
        dxf_appid->soft_owner_object = strdup ("");
        dxf_appid->hard_owner_object = strdup ("");
        dxf_appid->next = NULL;
#if DEBUG
        fprintf (stderr,
          (_("[File: %s: line: %d] ")),
          (_("Leaving %s () function.\n")),
          __FILE__, __LINE__, __FUNCTION__);
#endif
        return (dxf_appid);
}


/*!
 * \brief Read data from a DXF file into a DXF \c APPID entity.
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
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfAppid *dxf_appid
                /*!< DXF appid entity. */
)
{
#if DEBUG
        fprintf (stderr,
          (_("[File: %s: line: %d] ")),
          (_("Entering %s () function.\n")),
          __FILE__, __LINE__, __FUNCTION__);
#endif
        char *temp_string = NULL;

        if (!dxf_appid)
        {
                dxf_appid = dxf_appid_new ();
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
                        return (EXIT_FAILURE);
                }
                if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", &dxf_appid->id_code);
                }
                else if (strcmp (temp_string, "2") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_appid->application_name);
                }
                else if (strcmp (temp_string, "70") == 0)
                {
                        /* Now follows a string containing the
                         * standard flag value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_appid->standard_flag);
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing Soft-pointer
                         * ID/handle to owner object. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_appid->soft_owner_object);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_appid->hard_owner_object);
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
#if DEBUG
        fprintf (stderr,
          (_("[File: %s: line: %d] ")),
          (_("Leaving %s () function.\n")),
          __FILE__, __LINE__, __FUNCTION__);
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write DXF output for a DXF \c APPID entity.
 */
int
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
        int standard_flag,
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
        char *soft_owner_object,
                /*!< Soft-pointer ID/handle to owner object.\n
                 * Group code = 330. */
        char *hard_owner_object
                /*!< Hard owner ID/handle to owner dictionary
                 * (optional).\n
                 * Group code = 360. */
)
{
#if DEBUG
        fprintf (stderr,
          (_("[File: %s: line: %d] ")),
          (_("Entering %s () function.\n")),
          __FILE__, __LINE__, __FUNCTION__);
#endif
        char *dxf_entity_name = strdup ("APPID");

        if (strcmp (application_name, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning: empty application name string for the %s entity with id-code: %x\n")),
                  dxf_entity_name, id_code);
                fprintf (stderr,
                  (_("    %s entity is discarded from output.\n")),
                  dxf_entity_name);
                return (EXIT_FAILURE);
        }
        fprintf (fp, "  0\n%s\n", dxf_entity_name);
        if (id_code != -1)
        {
                fprintf (fp, "  5\n%x\n", id_code);
        }
        if (acad_version_number >= AutoCAD_13)
        {
                fprintf (fp, "100\nAcDbSymbolTableRecord\n");
                fprintf (fp, "100\nAcDbRegAppTableRecord\n");
        }
        fprintf (fp, "  2\n%s\n", application_name);
        fprintf (fp, " 70\n%d\n", standard_flag);
        if (strcmp (soft_owner_object, "") != 0)
        {
                fprintf (fp, "330\n%s\n", soft_owner_object);
        }
        if (strcmp (hard_owner_object, "") != 0)
        {
                fprintf (fp, "360\n%s\n", hard_owner_object);
        }
#if DEBUG
        fprintf (stderr,
          (_("[File: %s: line: %d] ")),
          (_("Leaving %s () function.\n")),
          __FILE__, __LINE__, __FUNCTION__);
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write DXF output to a file for a DXF \c APPID entity.
 */
int
dxf_appid_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfAppid *dxf_appid
                /*!< DXF appid entity. */
)
{
#if DEBUG
        fprintf (stderr,
          (_("[File: %s: line: %d] ")),
          (_("Entering %s () function.\n")),
          __FILE__, __LINE__, __FUNCTION__);
#endif
        char *dxf_entity_name = strdup ("APPID");
        if (dxf_appid == NULL)
        {
                return (EXIT_FAILURE);
                fprintf (stderr, "Error in dxf_appid_write () a NULL pointer was passed.\n");
        }
        if (dxf_appid->application_name == NULL)
        {
                fprintf (stderr,
                  (_("Warning: empty block name string for the %s entity with id-code: %x\n")),
                  dxf_entity_name, dxf_appid->id_code);
                fprintf (stderr,
                  (_("         %s entity is discarded from output.\n")),
                  dxf_entity_name);
                return (EXIT_FAILURE);
        }
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (dxf_appid->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", dxf_appid->id_code);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbSymbolTableRecord\n");
                fprintf (fp->fp, "100\nAcDbRegAppTableRecord\n");
        }
        fprintf (fp->fp, "  2\n%s\n", dxf_appid->application_name);
        fprintf (fp->fp, " 70\n%d\n", dxf_appid->standard_flag);
        if (strcmp (dxf_appid->soft_owner_object, "") != 0)
        {
                fprintf (fp->fp, "330\n%s\n", dxf_appid->soft_owner_object);
        }
        if (strcmp (dxf_appid->hard_owner_object, "") != 0)
        {
                fprintf (fp->fp, "360\n%s\n", dxf_appid->hard_owner_object);
        }
#if DEBUG
        fprintf (stderr,
          (_("[File: %s: line: %d] ")),
          (_("Leaving %s () function.\n")),
          __FILE__, __LINE__, __FUNCTION__);
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocate memory for a DXF \c APPID and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_appid_free
(
        DxfAppid *dxf_appid
                /*!< DXF \c APPID entity. */
)
{
#if DEBUG
        fprintf (stderr,
          (_("[File: %s: line: %d] ")),
          (_("Entering %s () function.\n")),
          __FILE__, __LINE__, __FUNCTION__);
#endif
        if (dxf_appid->next != NULL)
        {
              fprintf (stderr,
                (_("ERROR in %s () pointer to next DxfAppid was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (dxf_appid->application_name);
        free (dxf_appid->soft_owner_object);
        free (dxf_appid->hard_owner_object);
        free (dxf_appid);
        dxf_appid = NULL;
#if DEBUG
        fprintf (stderr,
          (_("[File: %s: line: %d] ")),
          (_("Leaving %s () function.\n")),
          __FILE__, __LINE__, __FUNCTION__);
#endif
        return (EXIT_SUCCESS);
}


/* EOF*/
