/*!
 * \file layer.h
 *
 * \author Copyright (C) 2008, 2010, 2012, 2013,2014, 2015, 2016, 2017,
 * 2018 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF layer table (\c LAYER).
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
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


#ifndef LIBDXF_SRC_LAYER_H
#define LIBDXF_SRC_LAYER_H


#include "global.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief DXF definition of an AutoCAD layer entity.
 */
typedef struct
dxf_layer_struct
{
        int id_code;
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file.\n
                 * Group code = 5. */
        char *layer_name;
                /*!< Layer name.\n
                 * Group code = 2. */
        char *linetype;
                /*!< For these layers, the associated linetype name in the DXF
                 * file is always CONTINUOUS.\
                 * Group code = 6. */
        int color;
                /*!< Color.\n
                 * If negative, layer is off.\n
                 * Group code = 62. */
        int flag;
                /*!< Flag.\n
                 * Bit coded:\n
                 * <ol>
                 * <li value="0"> on and thawed</li>
                 * <li value="1"> if set, layer is frozen</li>
                 * <li value="2"> if set, layer is frozen by default in
                 *   new viewports</li>
                 * <li value="4"> if set, layer is locked</li>
                 * <li value="8"> unused</li>
                 * <li value="128"> unused</li>
                 * </ol>
                 * Group code = 70. */
        int plotting_flag;
                /*!< Plotting flag.\n
                 * Boolean, if set to 0, do not plot this layer.\n
                 * Group code = 290. */
        char *dictionary_owner_soft;
                /*!< Soft-pointer ID/handle to owner dictionary
                 * (optional).\n
                 * Group code = 330. */
        char *material;
                /*!< Hard-pointer ID / handle to Material object.\n
                 * Group code = 347. */
        char *dictionary_owner_hard;
                /*!< group code = 360\n
                 * Hard owner ID/handle to owner dictionary (optional). */
        int16_t lineweight;
                /*!< Lineweight enum value.\n
                 * Group code = 370. */
        char *plot_style_name;
                /*!< Hard pointer ID / handle of PlotStyleName object.\n
                 * Group code = 390. */
        struct DxfLayer *next;
                /*!< Pointer to the next DxfLayer.\n
                 * \c NULL in the last DxfLayer. */
} DxfLayer;


DxfLayer *dxf_layer_new ();
DxfLayer *dxf_layer_init (DxfLayer *layer);
DxfLayer *dxf_layer_read (DxfFile *fp, DxfLayer *layer);
int dxf_layer_write (DxfFile *fp, DxfLayer *layer);
int dxf_layer_free (DxfLayer *layer);
void dxf_layer_free_list (DxfLayer *layers);
int dxf_layer_get_id_code (DxfLayer *layer);
DxfLayer *dxf_layer_set_id_code (DxfLayer *layer, int id_code);
char *dxf_layer_get_layer_name (DxfLayer *layer);
DxfLayer *dxf_layer_set_layer_name (DxfLayer *layer, char *layer_name);
char *dxf_layer_get_linetype (DxfLayer *layer);
DxfLayer *dxf_layer_set_linetype (DxfLayer *layer, char *linetype);
int dxf_layer_get_color (DxfLayer *layer);
DxfLayer *dxf_layer_set_color (DxfLayer *layer, int color);
int dxf_layer_is_off (DxfLayer *layer);
int dxf_layer_get_flag (DxfLayer *layer);
DxfLayer *dxf_layer_set_flag (DxfLayer *layer, int flag);
int dxf_layer_is_frozen (DxfLayer *layer);
int dxf_layer_is_locked (DxfLayer *layer);
int dxf_layer_is_xreferenced (DxfLayer *layer);
int dxf_layer_is_xresolved (DxfLayer *layer);
int dxf_layer_is_referenced (DxfLayer *layer);
int dxf_layer_get_plotting_flag (DxfLayer *layer);
DxfLayer *dxf_layer_set_plotting_flag (DxfLayer *layer, int plotting_flag);
char *dxf_layer_get_dictionary_owner_soft (DxfLayer *layer);
DxfLayer *dxf_layer_set_dictionary_owner_soft (DxfLayer *layer, char *dictionary_owner_soft);
char *dxf_layer_get_material (DxfLayer *layer);
DxfLayer *dxf_layer_set_material (DxfLayer *layer, char *material);
char *dxf_layer_get_dictionary_owner_hard (DxfLayer *layer);
DxfLayer *dxf_layer_set_dictionary_owner_hard (DxfLayer *layer, char *dictionary_owner_hard);
int16_t dxf_layer_get_lineweight (DxfLayer *layer);
DxfLayer *dxf_layer_set_lineweight (DxfLayer *layer, int16_t lineweight);
char *dxf_layer_get_plot_style_name (DxfLayer *layer);
DxfLayer *dxf_layer_set_plot_style_name (DxfLayer *layer, char *plot_style_name);
DxfLayer *dxf_layer_get_next (DxfLayer *layer);
DxfLayer *dxf_layer_set_next (DxfLayer *layer, DxfLayer *next);
DxfLayer *dxf_layer_get_last (DxfLayer *layer);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_LAYER_H */


/* EOF */
