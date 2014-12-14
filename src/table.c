/*!
 * \file table.c
 * \author Copyright (C) 2009 ... 2014 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 * \brief Functions for a DXF table entity (\c TABLE).
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
#include "section.h"


/*!
 * \brief Allocate memory for a DXF \c TABLE.
 *
 * Fill the memory contents with zeros.
 *
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfTable *
dxf_table_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfTable *dxf_table = NULL;
        size_t size;

        size = sizeof (DxfTable);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_table = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfTable struct.\n")),
                  __FUNCTION__);
                dxf_table = NULL;
        }
        else
        {
                memset (dxf_table, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_table);
}


/*!
 * \brief Write DXF output to a file for a table section.
 * 
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_table_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfTable dxf_table
                /*!< DXF table section. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        //char *dxf_entity_name = strdup ("TABLE");
        
        /*! \todo Add code here */
        
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write DXF output to a file for an end of class section.
 * 
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_table_write_endtable
(
        DxfFile *fp
                /*!< DXF file pointer to an output file (or device). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        fprintf (fp->fp, "  0\nENDTAB\n");
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Function generates dxf output to a file for all tables entities.
 * 
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_table_write_tables
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        int *dxf_tables_list
                /*!< pointer to list of TABLES. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_section_name = strdup ("TABLES");
        int dxf_tables_list_iter;
        int dxf_tables_list_last_iter = 0;

        dxf_section_write (fp->fp, dxf_section_name);
        dxf_tables_list_iter = 1;
        /* \FIXME
         * find_last_iter does not exist
        dxf_tables_list_last_iter = find_last_iter (dxf_tables_list);
         */
        while (dxf_tables_list_iter !=  dxf_tables_list_last_iter)
        {
                dxf_table_write_lowlevel
                        (
                        fp->fp,
                        *dxf_tables_list,
                        dxf_tables_list_iter,
                        fp->acad_version_number
                        );
                dxf_tables_list_iter++;
        }
        dxf_table_write_endtable (fp->fp);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
