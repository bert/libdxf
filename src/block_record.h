/*!
 * \file block_record.h
 *
 * \author Copyright (C) 2015 .. 2016 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF block record symbol table entry
 * (\c BLOCK_RECORD).
 *
 * \since The \c BLOCK_RECORD table was introduced in DXF R13.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
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


#ifndef LIBDXF_SRC_BLOCK_RECORD_H
#define LIBDXF_SRC_BLOCK_RECORD_H


#include "global.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief Definition of an AutoCAD block record symbol table entry
 * (\c BLOCK_RECORD).
 *
 * This table entry contains an entry to a block registered within a
 * drawing.
 */
typedef struct
dxf_block_record_struct
{
        int id_code;
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file.\n
                 * Group code = 5. */
        char *block_name;
                /*!< Name of the block registered within the drawing.\n
                 * Group code = 2. */
        int flag;
                /*!< This flag is for the benefit of AutoCAD commands;
                 * it can be ignored by most programs that read DXF files,
                 * and need not be set by programs that write DXF files.\n
                 * bit coded:\n
                 * <ol>
                 * <li value = "16"> if set, table entry is externally
                 * dependent on an Xref.</li>
                 * <li value = "32"> if this bit and bit 16 are both set,
                 * the externally dependent Xref has been successfully
                 * resolved.</li>
                 * <li value = "64"> if set, the table entry was
                 * referenced by at least one entity in the drawing the
                 * last time the drawing was edited.</li>
                 * </ol>
                 * Group code = 70. */
        char *dictionary_owner_soft;
                /*!< Soft-pointer ID/handle to owner dictionary
                 * (optional).\n
                 * Group code = 330. */
        char *dictionary_owner_hard;
                /*!< Hard owner ID/handle to owner dictionary
                 * (optional).\n
                 * Group code = 360. */
        struct DxfBlockRecord *next;
                /*!< Pointer to the next DxfAppid.\n
                 * \c NULL in the last DxfAppid. */
} DxfBlockRecord;


DxfBlockRecord *
dxf_block_record_new ();
DxfBlockRecord *
dxf_block_record_init
(
        DxfBlockRecord *block_record
);
DxfBlockRecord *
dxf_block_record_read
(
        DxfFile *fp,
        DxfBlockRecord *block_record
);
int
dxf_block_record_write
(
        DxfFile *fp,
        DxfBlockRecord *block_record
);
int
dxf_block_record_free
(
        DxfBlockRecord *block_record
);
void
dxf_block_record_free_chain
(
        DxfBlockRecord *block_records
);
int
dxf_block_record_get_id_code
(
        DxfBlockRecord *block_record
);
DxfBlockRecord *
dxf_block_record_set_id_code
(
        DxfBlockRecord *block_record,
        int id_code
);
char *
dxf_block_record_get_block_name
(
        DxfBlockRecord *block_record
);
DxfBlockRecord *
dxf_block_record_set_block_name
(
        DxfBlockRecord *block_record,
        char *block_name
);
int
dxf_block_record_get_flag
(
        DxfBlockRecord *block_record
);
DxfBlockRecord *
dxf_block_record_set_flag
(
        DxfBlockRecord *block_record,
        int flag
);
int
dxf_block_record_is_xreferenced
(
        DxfBlockRecord *block_record
);
int
dxf_block_record_is_xresolved
(
        DxfBlockRecord *block_record
);
int
dxf_block_record_is_referenced
(
        DxfBlockRecord *block_record
);
char *
dxf_block_record_get_dictionary_owner_soft
(
        DxfBlockRecord *block_record
);
DxfBlockRecord *
dxf_block_record_set_dictionary_owner_soft
(
        DxfBlockRecord *block_record,
        char *dictionary_owner_soft
);
char *
dxf_block_record_get_dictionary_owner_hard
(
        DxfBlockRecord *block_record
);
DxfBlockRecord *
dxf_block_record_set_dictionary_owner_hard
(
        DxfBlockRecord *block_record,
        char *dictionary_owner_hard
);
DxfBlockRecord *
dxf_block_record_get_next
(
        DxfBlockRecord *block_record
);
DxfBlockRecord *
dxf_block_record_set_next
(
        DxfBlockRecord *block_record,
        DxfBlockRecord *next
);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_BLOCK_RECORD_H */


/* EOF */
