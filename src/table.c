/*!
 * \file table.c
 * \author Copyright (C) 2009 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 * \brief DXF table entity (\c TABLE).
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
#include "table.h"
#include "section.c"


/*!
 * \brief Write DXF output to a file for a table section.
 *
 * \param [FILE *fp]: the file pointer to write to.
 * \return none.
 */
int
dxf_write_table
(
        FILE *fp,
                /*!< file pointer to output file (or device). */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_write_table () function.\n", __FILE__, __LINE__);
#endif
        char *dxf_entity_name = strdup ("TABLE");
        
        /*! \todo Add code here */
        
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_write_table () function.\n", __FILE__, __LINE__);
#endif
}


/*!
 * \brief Write DXF output to a file for a table section.
 * 
 * \param [FILE *fp]: the file pointer to write to.
 * \param [DxfTable dxf_table]: the table to write to file.
 * \return none.
 */
int
dxf_write_table_struct
(
        FILE *fp,
                /*!< file pointer to output file (or device). */
        DxfTable dxf_table
                /*!< DXF table section. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_write_table_struct () function.\n", __FILE__, __LINE__);
#endif
        char *dxf_entity_name = strdup ("TABLE");
        
        /*! \todo Add code here */
        
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_write_table_struct () function.\n", __FILE__, __LINE__);
#endif
}


/*!
 * \brief Write DXF output to a file for an end of class section.
 * 
 * \param [FILE *fp]: the file pointer to write to.
 * \return none.
 */
int
dxf_write_endtable
(
        FILE *fp
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_write_endtable () function.\n", __FILE__, __LINE__);
#endif
        fprintf (fp, "  0\nENDTAB\n");
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_write_endtable () function.\n", __FILE__, __LINE__);
#endif
}


/*!
 * \brief Function generates dxf output to a file for tables entities.
 * 
 * \param [FILE *fp]: the file pointer to write to.
 * \param [int *dxf_tables_list]: pointer to a list of dxf tables.
 * \param [int acad_version_number]: the AutoCAD version number.
 * \return none.
 */
int
dxf_write_tables
(
        FILE *fp,
                /*!< file pointer to output file (or device). */
        int *dxf_tables_list,
                /*!< pointer to list of TABLES. */
        int acad_version_number
                /*!< AutoCAD version number. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_write_tables () function.\n", __FILE__, __LINE__);
#endif
        char *dxf_section_name = strdup ("TABLES");
        int dxf_tables_list_iter;
        int dxf_tables_list_last_iter;

        dxf_write_section (fp, dxf_section_name);
        dxf_tables_list_iter = 1;
        dxf_tables_list_last_iter = find_last_iter (dxf_tables_list);
        while (dxf_tables_list_iter !=  dxf_tables_list_last_iter)
        {
                dxf_write_table
                        (
                        fp,
                        *dxf_tables_list,
                        dxf_tables_list_iter,
                        acad_version_number
                        );
                dxf_tables_list_iter++;
        }
        dxf_write_endtab ();
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_write_tables () function.\n", __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
