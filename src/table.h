/*!
 * \file table.h
 *
 * \author Copyright (C) 2009 ... 2014 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for of a DXF table entry (\c TABLE).
 *
 * The TABLES section contains several tables, each of which contain a
 * variable number of table entries.\n
 * \n
 * The order of the tables may change, but the LTYPE table will always
 * precede the LAYER table. Each table is introduced with a 0 group
 * with the label TABLE.\n
 * This is followed by a 2 group identifying the particular table
 * (VPORT, LTYPE, LAYER, STYLE, VIEW, DIMSTYLE, UCS or APPID) and a 70
 * group that specifies the maximum number of table entries that may
 * follow.\n
 * Table names are always output in uppercase characters.\n
 * \n
 * The tables in a drawing can contain deleted items, but these are not
 * written to the DXF file.\n
 * Thus, fewer table entries may follow the table header than are
 * indicated by the 70 group, so don't use the count in the 70 group as
 * an index to read in the table.\n
 * This group is provided so that a program which reads DXF files can
 * allocate an array large enough to hold all the table entries that
 * follow.\n
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

#ifndef LIBDXF_SRC_TABLE_H
#define LIBDXF_SRC_TABLE_H


#include "global.h"


/*!
 * \brief DXF definition of a table entity.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
typedef struct
dxf_table
{
        int id_code;
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file.\n
                 * Group code = 5. */
        char *table_name;
                /*!< Table name.\n
                 * Group code = 2. */
        int max_table_entries;
                /*!< Maximum number of table entries that may follow.\n
                 * Group code = 70. */
} DxfTable;


DxfTable *
dxf_table_new ();
DxfTable *
dxf_table_init
(
        DxfTable *dxf_table
);
int
dxf_table_write
(
        DxfFile *fp,
        DxfTable *dxf_table
);
int
dxf_table_write_tables
(
        DxfFile *fp,
        int *dxf_tables_list
);
int
dxf_table_free
(
        DxfTable *dxf_table
);


#endif /* LIBDXF_SRC_TABLE_H */


/* EOF */
