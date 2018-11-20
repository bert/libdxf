/*!
 * \file file.c
 *
 * \author Copyright (C) 2008, 2009, 2010, 2011, 2012, 2014, 2015, 2018
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.\n
 *
 * \author Copyright (C) 2010 by Luis Matos <gass@otiliamatos.ath.cx>.
 *
 * \author Copyright (C) 2018 Calvin Tower <Calvin@CorianderDesigns.com>
 *
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


#include "file.h"


char *dxf_entities_list;
char *dxf_objects_list;
char *dxf_blocks_list;
DxfThumbnail *dxf_thumbnail;


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
dxf_file_read
(
        char *filename
                /*!< filename of input file (or device). */
)
{
        char temp_string[DXF_MAX_STRING_LENGTH];
        DxfFile *fp;
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* open the file */
        fp = dxf_read_init (filename);
        if (fp == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL file pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        while (fp)
        {
                memset(temp_string, 0, sizeof(temp_string));
                dxf_read_line (temp_string, fp);
                if (strcmp (temp_string, "999") == 0)
                {
                        /* Flush dxf comments to stdout as some apps put meta
                         * data regarding the correct loading of libraries in
                         * front of dxf data (sections, tables, entities etc.
                         */
                        dxf_read_line (temp_string, fp);
                        fprintf (stdout, "DXF comment: %s\n", temp_string);
                }
                else if (strcmp (temp_string, "0") == 0)
                {
                /* Now follows some meaningfull dxf data. */
                        while (!feof (fp->fp))
                        {
                                dxf_read_line (temp_string, fp);
                                if (strcmp (temp_string, "SECTION") == 0)
                                {
                                         /* We have found the beginning of a
                                          * SECTION. */
                                        dxf_section_read (fp);
                                }
                                else
                                {
                                         /* We were expecting a dxf SECTION and
                                          * got something else. */
                                        fprintf (stderr,
                                          (_("Warning: in line %d \"SECTION\" was expected, \"%s\" was found.\n")),
                                          fp->line_number, temp_string);
                                }
                        }
                }
                else
                {
                        fprintf (stderr,
                          (_("Warning: unexpected string encountered while reading line %d from: %s.\n")),
                          fp->line_number , fp->filename);
                        return (EXIT_FAILURE);
                }
        }
        dxf_read_close (fp);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Function generates dxf output to a file for a complete DXF file.
 */
int
dxf_file_write
(
        DxfFile *fp,
                /*!< file pointer to output file (or device). */
        DxfHeader dxf_header,
                /*!< a dxf header. */
        DxfClass dxf_classes_list,
                /*!< pointer to a list of CLASSES. */
        DxfTable dxf_tables_list
                /*!< pointer to a list of TABLES. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        extern char *dxf_entities_list;
        extern char *dxf_objects_list;
//        DxfBlock *dxf_blocks_list;
        extern DxfThumbnail *dxf_thumbnail;

        /* Do some basic checks. */
        if (fp == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL file pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
//        dxf_header_init (dxf_header);
//        dxf_header_write (fp, dxf_header);
//        dxf_write_classes (fp, dxf_classes_list);
//        dxf_write_tables (fp, dxf_tables_list);
//        dxf_block_write_table (fp, dxf_blocks_list);
//        dxf_entities_write_table (fp, dxf_entities_list);
//        dxf_object_write_objects (fp, dxf_objects_list);
//        dxf_thumbnail_write (fp, dxf_thumbnail);
//        dxf_file_write_eof (fp);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write DXF output for an End Of File marker.
 */
int
dxf_file_write_eof
(
        DxfFile *fp
                /*!< file pointer to output file (or device). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (fp == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL file pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\nEOF\n");
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
