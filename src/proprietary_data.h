/*!
 * \file proprietary_data.h
 *
 * \author Copyright (C) 2016, 2017, 2018
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF proprietary data entity.
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


#ifndef LIBDXF_SRC_PROPRIETARY_DATA_H
#define LIBDXF_SRC_PROPRIETARY_DATA_H


#include "global.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief DXF definition of an AutoCAD Proprietary data entity.
 */
typedef struct
dxf_proprietary_data_struct
{
        int order;
                /*!< Incremental counter for storing order of data lines. */
        char *line;
                /*!< Proprietary data.\n
                 * Multiple lines of 256 characters maximum per line
                 * (optional).\n
                 * Group code = 1. */
        int length;
                /*!< Length of the line of characters.\n
                 * May not exceed \c DXF_MAX_STRING_LENGTH . */
        struct DxfProprietaryData *next;
                /*!< Pointer to the next DxfProprietaryData.\n
                 * \c NULL if the last DxfProprietaryData. */
} DxfProprietaryData;


DxfProprietaryData *dxf_proprietary_data_new ();
DxfProprietaryData *dxf_proprietary_data_init (DxfProprietaryData *data);
int dxf_proprietary_data_free (DxfProprietaryData *data);
void dxf_proprietary_data_free_list (DxfProprietaryData *datas);
int dxf_proprietary_data_get_order (DxfProprietaryData *data);
DxfProprietaryData *dxf_proprietary_data_set_order (DxfProprietaryData *data, int order);
char *dxf_proprietary_data_get_line (DxfProprietaryData *data);
DxfProprietaryData *dxf_proprietary_data_set_line (DxfProprietaryData *data, char *line);
int dxf_proprietary_data_get_length (DxfProprietaryData *data);
int dxf_proprietary_data_test_length (DxfProprietaryData *data);
DxfProprietaryData *dxf_proprietary_data_set_length (DxfProprietaryData *data, int length);
DxfProprietaryData *dxf_proprietary_data_get_next (DxfProprietaryData *data);
DxfProprietaryData *dxf_proprietary_data_set_next (DxfProprietaryData *data, DxfProprietaryData *next);
DxfProprietaryData *dxf_proprietary_data_get_last (DxfProprietaryData *data);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_PROPRIETARY_DATA_H */


/* EOF */
