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

static int line_number;

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
 * \brief Inits the line number counter.
 * 
 * Sets the line counting as 0.
 * 
 */
void
dxf_read_init(void)
{
        line_number = 0;
}
/*!
 * \brief Reads a line from a file.
 * 
 * Reads the next line from \c fp file and stores it into the temp_string.
 * 
 */
int
dxf_read_line (char * temp_string, FILE *fp)
{
    line_number++;
    return fscanf (fp, "%[^\n]\n", temp_string); 
}
/* EOF */

int
dxf_read_scanf (FILE *fp, const char *template, ...)
{
    int ret;
    char * search_result;

    va_list lst;
    va_start (lst, template);
    ret = vfscanf (fp, template, lst);
    va_end(lst);
    if (ret > 0)
    {
        /*
        * we have to find each \n from the template to know how many lines will we read;
        */
        search_result = (char *)template;
        while (TRUE)
        {
            search_result = strstr(search_result, "\n");
            if (search_result == NULL)
                break;
            line_number++;
            *search_result++;
        }
    }

    return ret;
}

/*!
 * \brief Returns the number of lines read;
 * 
 * Returns the number of lines read;
 * 
 */
int
dxf_read_get_line_count(void)
{
    return line_number;
}
