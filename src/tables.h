/*!
 * \file tables.h
 *
 * \author Copyright (C) 2014, 2015, 2016, 2017 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for of a DXF tables section (\c TABLES).
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

#ifndef LIBDXF_SRC_TABLES_H
#define LIBDXF_SRC_TABLES_H


#include "global.h"
#include "appid.h"
#include "block_record.h"
#include "dimstyle.h"
#include "layer.h"
#include "ltype.h"
#include "style.h"
#include "ucs.h"
#include "view.h"
#include "vport.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief DXF definition of a tables section.
 */
typedef struct
dxf_tables_struct
{
        int max_table_entries;
                /*!< Maximum number of table entries that may follow.\n
                 * Group code = 70. */
        DxfAppid *appids;
                /*!< Pointer to the first \c APPID symbol table entry. */
        DxfBlockRecord *block_records;
                /*!< Pointer to the first \c BLOCK_RECORD symbol table entry. */
        DxfDimStyle *dimstyles;
                /*!< Pointer to the first \c DIMSTYLE symbol table entry. */
        DxfLayer *layers;
                /*!< Pointer to the first \c LAYER symbol table entry. */
        DxfLType *ltypes;
                /*!< Pointer to the first \c LTYPE symbol table entry. */
        DxfStyle *styles;
                /*!< Pointer to the first \c STYLE symbol table entry. */
        DxfUcs *ucss;
                /*!< Pointer to the first \c UCS symbol table entry. */
        DxfView *views;
                /*!< Pointer to the first \c VIEW symbol table entry. */
        DxfVPort *vports;
                /*!< Pointer to the first \c VPORT symbol table entry. */
} DxfTables;


DxfTables *dxf_tables_new ();
DxfTables *dxf_tables_init (DxfTables *tables);
int dxf_tables_write (DxfFile *fp, DxfTables *tables);
int dxf_tables_free (DxfTables *tables);
int dxf_tables_get_max_table_entries (DxfTables *tables);
DxfTables *dxf_tables_set_max_table_entries (DxfTables *tables, int max_table_entries);
DxfAppid *dxf_tables_get_appids (DxfTables *tables);
DxfTables *dxf_tables_set_appids (DxfTables *tables, DxfAppid *appids);
DxfBlockRecord *dxf_tables_get_block_records (DxfTables *tables);
DxfTables *dxf_tables_set_block_records (DxfTables *tables, DxfBlockRecord *block_records);
DxfDimStyle *dxf_tables_get_dimstyles (DxfTables *tables);
DxfTables *dxf_tables_set_dimstyles (DxfTables *tables, DxfDimStyle *dimstyles);
DxfLayer *dxf_tables_get_layers (DxfTables *tables);
DxfTables *dxf_tables_set_layers (DxfTables *tables, DxfLayer *layers);
DxfLType *dxf_tables_get_ltypes (DxfTables *tables);
DxfTables *dxf_tables_set_ltypes (DxfTables *tables, DxfLType *ltypes);
DxfStyle *dxf_tables_get_styles (DxfTables *tables);
DxfTables *dxf_tables_set_styles (DxfTables *tables, DxfStyle *styles);
DxfUcs *dxf_tables_get_ucss (DxfTables *tables);
DxfTables *dxf_tables_set_ucss (DxfTables *tables, DxfUcs *ucss);
DxfView *dxf_tables_get_views (DxfTables *tables);
DxfTables *dxf_tables_set_views (DxfTables *tables, DxfView *views);
DxfVPort *dxf_tables_get_vports (DxfTables *tables);
DxfTables *dxf_tables_set_vports (DxfTables *tables, DxfVPort *vports);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_TABLES_H */


/* EOF */
