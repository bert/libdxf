/*!
 * \file sortentstable.h
 *
 * \author Copyright (C) 2015, 2016, 2017 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF sortentstable object (\c SORTENTSTABLE).
 *
 * \since The \c SORTENTSTABLE object was introduced in DXF R14.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
 * \version According to DXF R14.
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


#ifndef LIBDXF_SRC_SORTENTSTABLE_H
#define LIBDXF_SRC_SORTENTSTABLE_H


#include "global.h"
#include "util.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief DXF definition of an AutoCAD DXF sortentstable object
 * (\c SORTENTSTABLE).
 */
typedef struct
dxf_sortentstable_struct
{
        /* Members common for all DXF objects. */
        int id_code;
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file.\n
                 * Group code = 5. */
        char *dictionary_owner_soft;
                /*!< Soft-pointer ID/handle to owner dictionary
                 * (ACAD_SORTENTS).\n
                 * Group code = 330. */
        char *dictionary_owner_hard;
                /*!< Hard owner ID/handle to owner dictionary (optional).\n
                 * Group code = 360. */
        /* Specific members for a DXF sortentstable. */
        char *block_owner;
                /*!< Soft pointer ID/handle to owner (currently only the
                 * *MODEL_SPACE or *PAPER_SPACE blocks).\n
                 * Group code = 330. */
        DxfChar *entity_owner;
                /*!< Soft pointer ID/handle to an entity (zero or more
                 * entries may exist).\n
                 * Implemented as a single linked list.\n
                 * Group code = 331. */
        DxfInt *sort_handle;
                /*!< Sort handle (zero or more entries may exist).\n
                 * Implemented as a single linked list.\n
                 * Group code = 5. */
        struct DxfSortentsTable *next;
                /*!< Pointer to the next DxfSortentsTable.\n
                 * \c NULL in the last DxfSortentsTable. */
} DxfSortentsTable;


DxfSortentsTable *dxf_sortentstable_new ();
DxfSortentsTable *dxf_sortentstable_init (DxfSortentsTable *sortentstable);
DxfSortentsTable *dxf_sortentstable_read (DxfFile *fp, DxfSortentsTable *sortentstable);
int dxf_sortentstable_write (DxfFile *fp, DxfSortentsTable *sortentstable);
int dxf_sortentstable_free (DxfSortentsTable *sortentstable);
void dxf_sortentstable_free_chain (DxfSortentsTable *sortentstables);
int dxf_sortentstable_get_id_code (DxfSortentsTable *sortentstable);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_SORTENTSTABLE_H */


/* EOF */
