/*!
 * \file test_point.c
 *
 * \author Copyright (C) 2016, 2019, 2020
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Testing program for a DXF point entity (\c POINT).
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


#include <stdio.h>
#include "includes.h"


/*!
 * \brief Perform test functions for a DXF \c POINT entity.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
test_point (int argc, char** argv)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *filename;
        char temp_string[255];
        FILE *fp;
        DxfPoint *dxf_point_test_1;
        DxfPoint *dxf_point_test_2;

        dxf_point_test_1 = dxf_point_new ();
        dxf_point_test_1 = dxf_point_init (dxf_point_test_1);
        dxf_point_test_2 = dxf_point_new ();
        dxf_point_test_2 = dxf_point_init (dxf_point_test_2);
        filename = strdup ("dxf_point_test.dxf");
        fp = fopen (filename, "rw");
        if (!fp)
        {
                fprintf (stderr, "Error: could not open file: %s in read+write mode (NULL pointer).\n",
                        filename);
                exit (EXIT_FAILURE);
        }
        dxf_point_test_1->id_code = 1;
        dxf_point_test_1->layer = strdup ("0");
        dxf_point_test_1->x0 = 10.0;
        dxf_point_test_1->y0 = 20.0;
        dxf_point_test_1->z0 = 30.0;

        fclose (fp);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
