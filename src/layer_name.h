/*!
 * \file layer_name.h
 *
 * \author Copyright (C) 2017, 2018 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF layer name object.
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


#ifndef LIBDXF_SRC_LAYER_NAME_H
#define LIBDXF_SRC_LAYER_NAME_H


#include "global.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief DXF definition of an AutoCAD layer name object.
 */
typedef struct
dxf_layer_name_struct
{
        char *name;
                /*!< Layer name.\n
                 * 256 characters maximum.\n
                 * Group code = 8. */
        int length;
                /*!< Length of the \c name member. */
        struct DxfLayerName *next;
                /*!< Pointer to the next DxfLayerName.\n
                 * \c NULL if the last DxfLayerName. */
} DxfLayerName;


DxfLayerName *dxf_layer_name_new ();
DxfLayerName *dxf_layer_name_init (DxfLayerName *layer_name);
int dxf_layer_name_free (DxfLayerName *layer_name);
void dxf_layer_name_free_list (DxfLayerName *layer_names);
char *dxf_layer_name_get_name (DxfLayerName *layer_name);
DxfLayerName *dxf_layer_name_set_name (DxfLayerName *layer_name, char *name);
int dxf_layer_name_get_length (DxfLayerName *layer_name);
DxfLayerName *dxf_layer_name_set_length (DxfLayerName *layer_name, int length);
DxfLayerName *dxf_layer_name_get_next (DxfLayerName *layer_name);
DxfLayerName *dxf_layer_name_set_next (DxfLayerName *layer_name, DxfLayerName *next);
DxfLayerName *dxf_layer_name_get_last (DxfLayerName *layer_name);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_LAYER_NAME_H */


/* EOF */
