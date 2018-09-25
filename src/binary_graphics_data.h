/*!
 * \file binary_graphics_data.h
 *
 * \author Copyright (C) 2016 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF binary graphics data object.
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


#ifndef LIBDXF_SRC_BINARY_GRAPHICS_DATA_H
#define LIBDXF_SRC_BINARY_GRAPHICS_DATA_H


#include "global.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief DXF definition of an AutoCAD binary graphics data object.
 */
typedef struct
dxf_binary_graphics_data_struct
{
        char *data_line;
                /*!< Binary graphics data.\n
                 * Multiple lines of 256 characters maximum per line
                 * (optional).\n
                 * Group code = 310. */
        int length;
                /*!< Length of the data_line member. */
        struct DxfBinaryGraphicsData *next;
                /*!< Pointer to the next DxfBinaryGraphicsData.\n
                 * \c NULL if the last DxfBinaryGraphicsData. */
} DxfBinaryGraphicsData;


DxfBinaryGraphicsData *
dxf_binary_graphics_data_new ();
DxfBinaryGraphicsData *
dxf_binary_graphics_data_init
(
        DxfBinaryGraphicsData *data
);
int
dxf_binary_graphics_data_write
(
        DxfFile *fp,
        DxfBinaryGraphicsData *data
);
int
dxf_binary_graphics_data_free
(
        DxfBinaryGraphicsData *data
);
void
dxf_binary_graphics_data_free_list
(
        DxfBinaryGraphicsData *data
);
char *
dxf_binary_graphics_data_get_data_line
(
        DxfBinaryGraphicsData *data
);
DxfBinaryGraphicsData *
dxf_binary_graphics_data_set_data_line
(
        DxfBinaryGraphicsData *data,
        char *data_line
);
int
dxf_binary_graphics_data_get_length
(
        DxfBinaryGraphicsData *data
);
DxfBinaryGraphicsData *
dxf_binary_graphics_data_set_length
(
        DxfBinaryGraphicsData *data,
        int length
);
DxfBinaryGraphicsData *
dxf_binary_graphics_data_get_next
(
        DxfBinaryGraphicsData *data
);
DxfBinaryGraphicsData *
dxf_binary_graphics_data_set_next
(
        DxfBinaryGraphicsData *data,
        DxfBinaryGraphicsData *next
);
DxfBinaryGraphicsData *
dxf_binary_graphics_data_get_last
(
        DxfBinaryGraphicsData *data
);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_BINARY_GRAPHICS_DATA_H */


/* EOF */
