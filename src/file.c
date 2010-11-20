/*!
 * \file file.c
 * \author Copyright (C) 2008, 2009, 2010 by Bert Timmerman <bert.timmerman@xs4all.nl>.\n
 * \brief Functions for the handling of DXF files.
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


#include "global.h"
#include "class.h"
#include "header.h"
#include "section.h"
#include "table.h"
#include "block.h"
#include "entity.h"
#include "object.h"
#include "thumbnail.h"
#include "eof.h"
#include "file.h"
#include "util.h"


char *dxf_entities_list;
char *dxf_objects_list;
char *dxf_blocks_list;
DxfThumbnail *dxf_thumbnail;


/*!
 * \brief A adapted fscanf for reading text lines from a DXF file.
 * 
 * \return char* with the scanned data.
 */
char *dxf_fscanf
(
        FILE *fp,
        const char * template
)
{
        char temp_string[255];

        fscanf (fp, template, temp_string);
        return strdup (temp_string);
}


/*!
 * \brief Function opens and reads a DXF file.
 * 
 * After opening the DXF file with the name \c filename the file is read
 * line by line until a line containing the \c SECTION keyword is
 * encountered.\n
 * At this point a function which reads the \c SECTION until the
 * \c ENDSEC keyword is encountered and the invoked fuction returns here.
 */
int
dxf_read_file
(
        char *filename
                /*!< filename of input file (or device). */
)
{
        char temp_string[255];
        int line_number;
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_read_file () function.\n", __FILE__, __LINE__);
#endif
        if (!filename)
        {
                fprintf (stderr, "Error: filename is not initialised (NULL pointer).\n");
                return (EXIT_FAILURE);
        }
        if (strcmp (filename, "") == 0)
        {
                fprintf (stderr, "Error: filename contains an empty string.\n");
                return (EXIT_FAILURE);
        }
        FILE *fp;
        fp = fopen (filename, "r");
        if (!fp)
        {
                fprintf (stderr, "Error: could not open file: %s for reading (NULL pointer).\n",
                        filename);
                return (EXIT_FAILURE);
        }
        line_number = 1;
        while (!ferror (fp))
        {
                dxf_read_line (temp_string, fp);
                if (ferror (fp))
                {
                        fprintf (stderr, "Error: while reading from: %s in line: %d.\n",
                                filename, line_number);
                        fclose (fp);
                        return (EXIT_FAILURE);
                }
                if (strcmp (temp_string, "999") == 0)
                {
                        /* Flush dxf comments to stdout as some apps put meta
                         * data regarding the correct loading of libraries in
                         * front of dxf data (sections, tables, entities etc.
                         */
                        line_number++;
                        dxf_read_line (temp_string, fp);
                        fprintf (stdout, "DXF comment: %s\n", temp_string);
                }
                else if (strcmp (temp_string, "0") == 0)
                {
                /* Now follows some meaningfull dxf data. */
                        while (!feof (fp))
                        {
                                line_number++;
                                dxf_read_line (temp_string, fp);
                                if (ferror (fp))
                                {
                                        fprintf (stderr, "Error: while reading line %d from: %s.\n",
                                                line_number, filename);
                                        fclose (fp);
                                        return (EXIT_FAILURE);
                                }
                                if (strcmp (temp_string, "SECTION") == 0)
                                {
                                         /* We have found the beginning of a
                                          * SECTION. */
                                        dxf_read_section (filename, fp, line_number);
                                }
                                else
                                {
                                         /* We were expecting a dxf SECTION and
                                          * got something else. */
                                        fprintf (stderr, "Warning: in line %d \"SECTION\" was expected, \"%s\" was found.\n",
                                                line_number, temp_string);
                                }
                        }
                }
                else
                {
                        fprintf (stderr, "Warning: unexpected string encountered while reading line %d from: %s.\n",
                                line_number, filename);
                        return (EXIT_FAILURE);
                }
        }
        fclose (fp);
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_read_file () function.\n", __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Function generates dxf output to a file for a complete DXF file.
 */
int
dxf_write_file
(
        FILE *fp,
                /*!< file pointer to output file (or device). */
        DxfHeader dxf_header,
                /*!< a dxf header. */
        DxfClass dxf_classes_list,
                /*!< pointer to a list of CLASSES. */
        DxfTable dxf_tables_list,
                /*!< pointer to a list of TABLES. */
        int acad_version_number
                /*!< AutoCAD version number. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_write_file () function.\n", __FILE__, __LINE__);
#endif
        extern char *dxf_entities_list;
        extern char *dxf_objects_list;
        extern char *dxf_blocks_list;
        extern DxfThumbnail *dxf_thumbnail;
        dxf_init_header (dxf_header, acad_version_number);
        dxf_write_header (fp, dxf_header, acad_version_number);
        //dxf_write_classes (fp, dxf_classes_list, acad_version_number);
        //dxf_write_tables (fp, dxf_tables_list, acad_version_number);
        dxf_block_write_table (dxf_blocks_list, acad_version_number);
        dxf_write_entities (dxf_entities_list, acad_version_number);
        dxf_write_objects (dxf_objects_list, acad_version_number);
        dxf_write_thumbnail (dxf_thumbnail, acad_version_number);
        dxf_write_eof(fp);
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_write_file () function.\n", __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
