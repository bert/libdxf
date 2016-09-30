/*!
 * \file layer.h
 *
 * \author Copyright (C) 2008 ... 2016 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF layer table (\c LAYER).
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


#ifndef LIBDXF_SRC_LAYER_H
#define LIBDXF_SRC_LAYER_H


#include "global.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief DXF definition of an AutoCAD layer entity.
 *
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
typedef struct
dxf_layer
{
        int id_code;
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file.\n
                 * Group code = 5. */
        char *layer_name;
                /*!< group code = 2. */
        char *linetype;
                /*!< group code = 6\n
                 * For these layers, the associated linetype name in the DXF
                 * file is always CONTINUOUS. */
        int color;
                /*!< group code = 62\n
                 * if negative, layer is off. */
        int flag;
                /*!< group code = 70\n
                 * bit coded:\n
                 * 0 = on and thawed\n
                 * 1 = if set, layer is frozen\n
                 * 2 = if set, layer is frozen by default in new viewports\n
                 * 4 = if set, layer is locked\n
                 * 8 = unused\n
                 * 128 = unused. */
        int plotting_flag;
                /*!< group code = 290\n
                 * Boolean, if set to 0, do not plot this layer. */
        char *dictionary_owner_soft;
                /*!< group code = 330\n
                 * Soft-pointer ID/handle to owner dictionary (optional). */
        char *material;
                /*!< group code = 347\n
                 * Hard-pointer ID / handle to Material object */
        char *dictionary_owner_hard;
                /*!< group code = 360\n
                 * Hard owner ID/handle to owner dictionary (optional). */
        int16_t lineweight;
                /*!< group code = 370\n
                 * Lineweight enum value. */
        char *plot_style_name;
                /*!< group code = 390\n
                 * Hard pointer ID / handle of PlotStyleName object. */
        struct DxfLayer *next;
                /*!< pointer to the next DxfLayer.\n
                 * \c NULL in the last DxfLayer. */
} DxfLayer;


DxfLayer *
dxf_layer_new ();
DxfLayer *
dxf_layer_init
(
        DxfLayer *layer
);
DxfLayer *
dxf_layer_read
(
        DxfFile *fp,
        DxfLayer *layer
);
int
dxf_layer_write
(
        DxfFile *fp,
        DxfLayer *layer
);
int
dxf_layer_free
(
        DxfLayer *layer
);
void
dxf_layer_free_chain
(
        DxfLayer *layers
);
int
dxf_layer_is_frozen
(
        DxfLayer *layer
);
int
dxf_layer_is_locked
(
        DxfLayer *layer
);
int
dxf_layer_is_xreferenced
(
        DxfLayer *layer
);
int
dxf_layer_is_xresolved
(
        DxfLayer *layer
);
int
dxf_layer_is_referenced
(
        DxfLayer *layer
);
int
dxf_layer_is_off
(
        DxfLayer *layer
);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_LAYER_H */


/* EOF */
