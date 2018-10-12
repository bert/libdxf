/*!
 * \file spatial_index.h
 *
 * \author Copyright (C) 2015, 2016, 2017, 2018
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF spatial_index object (\c SPATIAL_INDEX).
 *
 * The SPATIAL_INDEX is always written out empty to a DXF file.\n
 * This object can be ignored.
 *
 * \since The \c SPATIAL_INDEX object was introduced in DXF R14.
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


#ifndef LIBDXF_SRC_SPATIAL_INDEX_H
#define LIBDXF_SRC_SPATIAL_INDEX_H


#include "global.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief DXF definition of an AutoCAD spatial_index object (\c SPATIAL_INDEX).
 */
typedef struct
dxf_spatial_index_struct
{
        /* Members common for all DXF objects. */
        int id_code;
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file.\n
                 * Group code = 5. */
        char *dictionary_owner_soft;
                /*!< Soft-pointer ID/handle to owner dictionary.\n
                 * Group code = 330. */
        char *dictionary_owner_hard;
                /*!< Hard owner ID/handle to owner dictionary (optional).\n
                 * Group code = 360. */
        /* Specific members for a DXF spatial_index. */
        double time_stamp;
                /*!< Timestamp (Julian date).\n
                 * Group code = 40. */
        struct DxfSpatialIndex *next;
                /*!< Pointer to the next DxfSpatialIndex.\n
                 * \c NULL in the last DxfSpatialIndex. */
} DxfSpatialIndex;


DxfSpatialIndex *dxf_spatial_index_new ();
DxfSpatialIndex *dxf_spatial_index_init (DxfSpatialIndex *spatial_index);
DxfSpatialIndex *dxf_spatial_index_read (DxfFile *fp, DxfSpatialIndex *spatial_index);
int dxf_spatial_index_write (DxfFile *fp, DxfSpatialIndex *spatial_index);
int dxf_spatial_index_free (DxfSpatialIndex *spatial_index);
void dxf_spatial_index_free_list (DxfSpatialIndex *spatial_indices);
int dxf_spatial_index_get_id_code (DxfSpatialIndex *spatial_index);
DxfSpatialIndex *dxf_spatial_index_set_id_code (DxfSpatialIndex *spatial_index, int id_code);
char *dxf_spatial_index_get_dictionary_owner_soft (DxfSpatialIndex *spatial_index);
DxfSpatialIndex *dxf_spatial_index_set_dictionary_owner_soft (DxfSpatialIndex *spatial_index, char *dictionary_owner_soft);
char *dxf_spatial_index_get_dictionary_owner_hard (DxfSpatialIndex *spatial_index);
DxfSpatialIndex *dxf_spatial_index_set_dictionary_owner_hard (DxfSpatialIndex *spatial_index, char *dictionary_owner_hard);
double dxf_spatial_index_get_time_stamp (DxfSpatialIndex *spatial_index);
DxfSpatialIndex *dxf_spatial_index_set_time_stamp (DxfSpatialIndex *spatial_index, double time_stamp);
DxfSpatialIndex *dxf_spatial_index_get_next (DxfSpatialIndex *spatial_index);
DxfSpatialIndex *dxf_spatial_index_set_next (DxfSpatialIndex *spatial_index, DxfSpatialIndex *next);
DxfSpatialIndex *dxf_spatial_index_get_last (DxfSpatialIndex *spatial_index);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_SPATIAL_INDEX_H */


/* EOF */
