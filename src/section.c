/*!
 * \file section.c
 * \author Copyright (C) 2008, 2009, 2010 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 * \brief DXF section entity (\c SECTION).
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
#include "header.h"
#include "util.h"


/*!
 * \brief Function reads a SECTION in a DXF file.
 */
int
dxf_read_section
(
        char *filename,
                /*!< filename of input file (or device). */
        FILE *fp
                /*!< filepointer to the input file (or device). */
)
{
        char temp_string[255];
        DxfHeader dxf_header;
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_read_section () function.\n", __FILE__, __LINE__);
#endif
        if (!fp)
        {
                fprintf (stderr, "Error: could not open file: %s for reading (NULL pointer).\n",
                        filename);
                return (EXIT_FAILURE);
        }
        dxf_read_line (temp_string, fp);
        if (ferror (fp))
        {
                fprintf (stderr, "Error: while reading from: %s in line: %d.\n",
                        filename, __DXF_LINE_READ__);
                fclose (fp);
                return (EXIT_FAILURE);
        }
        if (strcmp (temp_string, "2") == 0)
        {
                while (!feof (fp))
                {
                        dxf_read_line (temp_string, fp);
                        if (ferror (fp))
                        {
                                fprintf (stderr, "Error: while reading line %d from: %s.\n",
                                        __DXF_LINE_READ__, filename);
                                fclose (fp);
                                return (EXIT_FAILURE);
                        }
                        if (strcmp (temp_string, "HEADER") == 0)
                        {
                                /* We have found the begin of the HEADER section. */
                                dxf_read_header (fp, dxf_header);
                        }
                        else if (strcmp (temp_string, "CLASSES") == 0)
                        {
                                /* We have found the begin of the CLASSES sction. */
                                /*! \todo Invoke a function for parsing the \c CLASSES section. */ 
                        }
                        else if (strcmp (temp_string, "TABLES") == 0)
                        {
                                /* We have found the begin of the TABLES sction. */
                                /*! \todo Invoke a function for parsing the \c TABLES section. */ 
                        }
                        else if (strcmp (temp_string, "BLOCKS") == 0)
                        {
                                /* We have found the begin of the BLOCKS sction. */
                                /*! \todo Invoke a function for parsing the \c BLOCKS section. */ 
                        }
                        else if (strcmp (temp_string, "ENTITIES") == 0)
                        {
                                /* We have found the begin of the ENTITIES sction. */
                                /*! \todo Invoke a function for parsing the \c ENTITIES section. */ 
                        }
                        else if (strcmp (temp_string, "OBJECTS") == 0)
                        {
                                /* We have found the begin of the OBJECTS sction. */
                                /*! \todo Invoke a function for parsing the \c OBJECTS section. */ 
                        }
                        else if (strcmp (temp_string, "THUMBNAIL") == 0)
                        {
                                /* We have found the begin of the THUMBNAIL sction. */
                                /*! \todo Invoke a function for parsing the \c THUMBNAIL section. */ 
                        }
                }
        }
        else
        {
                fprintf (stderr, "Warning: unexpected string encountered while reading line %d from: %s.\n",
                        __DXF_LINE_READ__, filename);
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_read_section () function.\n", __FILE__, __LINE__);
#endif
        return EXIT_SUCCESS;
}


/*!
 * \brief Write DXF output to a file for a section marker.
 */
int
dxf_write_section
(
        FILE *fp,
        char *section_name
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_write_section () function.\n", __FILE__, __LINE__);
#endif
        fprintf (fp, "  0\nSECTION\n  2\n%s\n", section_name);
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_write_section () function.\n", __FILE__, __LINE__);
#endif
		return (EXIT_SUCCESS);
}

/*!
 * \brief Write DXF output to a file for an end of section marker.
 */
int
dxf_write_endsection
(
        FILE *fp
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_write_endsection () function.\n", __FILE__, __LINE__);
#endif
        fprintf (fp, "  0\nENDSEC\n");
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_write_endsection () function.\n", __FILE__, __LINE__);
#endif
		return (EXIT_SUCCESS);
}

/* EOF */
