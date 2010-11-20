/*!
 * \file tests.c
 * \author Copyright (C) 2010 by Luis Matos <gass@otiliamatos.ath.cx>.\n
 * \brief Tests for libdxf.
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

#include <string.h>
#include "../src/file.h"

int main (void)
{
    /*
     * Reads a dxf file using libdxf form examples dir.
     */
    /* Version 2000 */
    if (dxf_read_file ("../examples/qcad-example_R2000.dxf"))
        fprintf (stdout, "TESTS: R2000 exited with error\n");
    else
        fprintf (stdout, "TESTS: R2000 exited with no error\n");
    
    return 1;
}