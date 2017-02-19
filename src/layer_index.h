/*!
 * \file layer_index.h
 *
 * \author Copyright (C) 2015, 2016, 2017 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF layer index object (\c LAYER_INDEX).
 *
 * \version The \c LAYER_INDEX object was introduced in DXF R14.
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


#ifndef LIBDXF_SRC_LAYER_INDEX_H
#define LIBDXF_SRC_LAYER_INDEX_H


#include "global.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief DXF definition of an AutoCAD idbuffer object (\c LAYER_INDEX).
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
 * \version According to DXF R14.
 */
typedef struct
dxf_layer_index_struct
{
        /* Members common for all DXF group objects. */
        int id_code;
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file.\n
                 * Group code = 5. */
        char *dictionary_owner_soft;
                /*!< Soft-pointer ID/handle to owner dictionary (optional).\n
                 * Group code = 330. */
        char *dictionary_owner_hard;
                /*!< Hard owner ID/handle to owner dictionary (optional).\n
                 * Group code = 360. */
        /* Specific members for a DXF idbuffer. */
        char *layer_name[DXF_MAX_PARAM];
                /*!< Layer name (multiple entries may exist).\n
                 * Group code = 8. */
        double time_stamp;
                /*!< Time stamp (Julian date).\n
                 * Group code = 40. */
        int32_t number_of_entries[DXF_MAX_PARAM];
                /*!< Number of entries in the IDBUFFER list (multiple
                 * entries may exist).\n
                 * Group code = 90. */
        char *hard_owner_reference[DXF_MAX_PARAM];
                /*!< Hard owner reference to IDBUFFER (multiple entries
                 * may exist).\n
                 * Group code = 360. */
        struct DxfLayerIndex *next;
                /*!< Pointer to the next DxfLayerIndex.\n
                 * \c NULL in the last DxfLayerIndex. */
} DxfLayerIndex;


DxfLayerIndex *
dxf_layer_index_new ();
DxfLayerIndex *
dxf_layer_index_init
(
        DxfLayerIndex *layer_index
);
DxfLayerIndex *
dxf_layer_index_read
(
        DxfFile *fp,
        DxfLayerIndex *layer_index
);
int
dxf_layer_index_write
(
        DxfFile *fp,
        DxfLayerIndex *layer_index
);
int
dxf_layer_index_free
(
        DxfLayerIndex *layer_index
);
void
dxf_layer_index_free_chain
(
        DxfLayerIndex *layer_indices
);
int
dxf_layer_index_get_id_code
(
        DxfLayerIndex *layer_index
);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_LAYER_INDEX_H */


/* EOF */
