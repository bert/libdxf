/*!
 * \file util.c
 * \author Copyright (C) 2010 by Luis Matos <gass@otiliamatos.ath.cx>.\n
 * \brief LIBDXF coding utilities.
 *
 * <hr>
 * <h1><b>Copyright Notices.</b></h1>\n
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.\n\n
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


#include <stdarg.h>
#include "util.h"


int
dxf_read_is_double (int type)
{
        if (type >=10 && type < 60)
                return TRUE;
        else
                return FALSE;
}


int
dxf_read_is_int (int type)
{
        if (type >= 60 && type < 80)
                return TRUE;
        else
                return FALSE;
}


int
dxf_read_is_string (int type)
{
        if (type >= 0 && type <= 9)
                return TRUE;
        else
                return FALSE;
}

/*!
 * \brief Opens a DxfFile, does error checking and resets the line number
 * counter.
 * 
 * Reset the line counting to 0.
 * 
 */
DxfFile *
dxf_read_init (const char *filename)
{
        DxfFile * dxf_file = NULL;
        FILE *fp;
        if (!filename)
        {
                fprintf (stderr, "Error: filename is not initialised (NULL pointer).\n");
                return (NULL);
        }
        if (strcmp (filename, "") == 0)
        {
                fprintf (stderr, "Error: filename contains an empty string.\n");
                return (NULL);
        }
        fp = fopen (filename, "r");
        if (!fp)
        {
                fprintf (stderr, "Error: could not open file: %s for reading (NULL pointer).\n",
                        filename);
                return (NULL);
        }
        dxf_file = malloc (sizeof(DxfFile));
        dxf_file->fp = fp;
        dxf_file->filename = strdup(filename);
        dxf_file->line_number = 0;
        /*! \todo FIXME: dxf header and blocks need initialized ?
        dxf_header_init (dxf_file->dxf_header);
        dxf_block_init (dxf_file->dxf_block);
        */
        return dxf_file;
}


void
dxf_read_close (DxfFile *dxf_file)
{
        /*! \todo FIXME: how to free other sub structures */
        if (dxf_file != NULL)
        {
                fclose (dxf_file->fp);
                free (dxf_file->filename);
                free (dxf_file);
                dxf_file = NULL;
        }
}


/*!
 * \brief Reads a line from a file.
 * 
 * Reads the next line from \c fp file and stores it into the temp_string.
 * 
 */
int
dxf_read_line (char * temp_string, DxfFile *fp)
{
        int ret;

        ret = fscanf (fp->fp, "%[^\n]\n", temp_string);
        if (ferror (fp->fp))
        {
                fprintf (stderr, "Error: while reading from: %s in line: %d.\n",
                        fp->filename, fp->line_number);
                return (EXIT_FAILURE);
        }
        if (ret)
        {
                fp->line_number++;
        }
        return ret;
}

/*!
 * \brief Uses of fscanf with other features.
 * 
 * Uses fscanf for file parsing, but also tracks the lines it reads;
 * 
 */
int
dxf_read_scanf (DxfFile *fp, const char *template, ...)
{
        int ret;
        char * search_result;
        va_list lst;
        va_start (lst, template);
        ret = vfscanf (fp->fp, template, lst);
        if (ferror (fp->fp))
        {
                fprintf (stderr, "Error: while reading from: %s in line: %d.\n",
                        fp->filename, fp->line_number);
                return (EXIT_FAILURE);
        }
        va_end (lst);
        if (ret)
        {
                /*
                 * we have to find each \n from the template to know how many lines will we read;
                 */
                search_result = (char *) template;
                while (TRUE)
                {
                        search_result = strstr (search_result, "\n");
                        if (search_result == NULL)
                                break;
                        fp->line_number++;
                        *++search_result;
                }
        }
        return ret;
}


/* EOF */
