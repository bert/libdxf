/*!
 * \file class.h
 *
 * \author Copyright (C) 2009, 2010, 2011, 2012, 2014, 2015, 2016, 2017,
 * 2018, 2019 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \author Copyright (C) 2010 by Luis Matos <gass@otiliamatos.ath.cx>.
 *
 * \brief Header file for a DXF class entity (\c CLASS).
 *
 * \htmlinclude "../doc/class.html"
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

#ifndef LIBDXF_SRC_CLASS_H
#define LIBDXF_SRC_CLASS_H


#include "global.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief DXF definition of a class entity (\c CLASS).
 *
 * Each entry in the CLASSES section contains the groups described
 * in the following table, as stated in the documentation for
 * AutoCAD DXF release 2000.
 */
typedef struct
dxf_class_struct
{
        char *record_type;
                /*!< group code  = 0.\n
                 * Record type (CLASS).\n
                 * Identifies the beginning of a CLASS record. */
        char *record_name;
                /*!< group code = 1.\n
                 * Class DXF record name.\n
                 * These should always be unique. */
        char *class_name;
                /*!< group code = 2.\n
                 * C++ class name.\n
                 * Used to bind with software that defines object class behavior.\n
                 * These are always unique. */  
        char *app_name;
                /*!< group code = 3.\n
                 * Application name.\n
                 * Posted in Alert box when a class definition listed in
                 * this section is not currently loaded. */ 
        int32_t proxy_cap_flag;
                /*!< group code = 90.\n
                 * Proxy capabilities flag.\n
                 * Bit coded value that indicates the capabilities of
                 * this object as a proxy.\n
                 * 0 = No operations allowed (0).\n
                 * 1 = Erase allowed (0x1).\n
                 * 2 = Transform allowed (0x2).\n
                 * 4 = Color change allowed (0x4).\n
                 * 8 = Layer change allowed (0x8).\n
                 * 16 = Linetype change allowed (0x10).\n
                 * 32 = Linetype scale change allowed (0x20).\n
                 * 64 = Visibility change allowed (0x40).\n
                 * 127 = All operations except cloning allowed (0x7F),
                 *       until R2000.\n
                 * 128 = Cloning allowed (0x80).\n
                 * 255 = All operations allowed (0xFF),
                 *       until R2000.\n
                 * 256 = Lineweight change allowed (0x100),
                 *       introduced in R2002.\n
                 * 512 = Plot Style Name change allowed (0x200),
                 *       introduced in R2002.\n
                 * 895 = All operations except cloning allowed (0x37F),
                 *       introduced in R2002.\n
                 * 1023 = All operations allowed (0x3FF),
                 *        introduced in R2002.\n
                 * 32768 = R13 format proxy (0x8000). */
        int16_t was_a_proxy_flag;
                /*!< group code = 280.\n
                 * Was-a-proxy flag.\n
                 * Set to 1 if class was not loaded when this DXF file was
                 * created, and 0 otherwise. */
        int16_t is_an_entity_flag;
                /*!< group code = 281.\n
                 * Is-an-entity flag.\n
                 * Set to 1 if class was derived from the AcDbEntity class and
                 * can reside in the BLOCKS or ENTITIES section.\n
                 * If 0, instances may appear only in the OBJECTS section. */
        struct DxfClass *next;
                /*!< pointer to the next DxfClass.\n
                 * \c NULL in the last DxfClass. */
} DxfClass;


DxfClass *dxf_class_new ();
DxfClass *dxf_class_init (DxfClass *class);
DxfClass *dxf_class_read (DxfFile *fp, DxfClass *class);
int dxf_class_write (DxfFile *fp, DxfClass *class);
int dxf_class_write_endclass (DxfFile *fp);
int dxf_class_free (DxfClass *class);
void dxf_class_free_list (DxfClass *classes);
char *dxf_class_get_record_type (DxfClass *class);
DxfClass *dxf_class_set_record_type (DxfClass *class, char *record_type);
char *dxf_class_get_record_name (DxfClass *class);
DxfClass *dxf_class_set_record_name (DxfClass *class, char *record_name);
char *dxf_class_get_class_name (DxfClass *class);
DxfClass *dxf_class_set_class_name (DxfClass *class, char *class_name);
char *dxf_class_get_app_name (DxfClass *class);
DxfClass *dxf_class_set_app_name (DxfClass *class, char *app_name);
int32_t dxf_class_get_proxy_cap_flag (DxfClass *class);
DxfClass *dxf_class_set_proxy_cap_flag (DxfClass *class, int32_t proxy_cap_flag);
int dxf_class_is_editable (DxfClass *class);
int dxf_class_erase_allowed (DxfClass *class);
int dxf_class_transform_allowed (DxfClass *class);
int dxf_class_color_change_allowed (DxfClass *class);
int dxf_class_layer_change_allowed (DxfClass *class);
int dxf_class_linetype_change_allowed (DxfClass *class);
int dxf_class_linetype_scale_change_allowed (DxfClass *class);
int dxf_class_visibility_change_allowed (DxfClass *class);
int dxf_class_cloning_allowed (DxfClass *class);
int dxf_class_lineweight_change_allowed (DxfClass *class);
int dxf_class_plot_style_name_change_allowed (DxfClass *class);
int dxf_class_is_R13_format_proxy (DxfClass *class);
int16_t dxf_class_get_was_a_proxy_flag (DxfClass *class);
DxfClass * dxf_class_set_was_a_proxy_flag (DxfClass *class, int16_t was_a_proxy_flag);
int16_t dxf_class_get_is_an_entity_flag (DxfClass *class);
DxfClass *dxf_class_set_is_an_entity_flag (DxfClass *class, int16_t is_an_entity_flag);
DxfClass *dxf_class_get_next (DxfClass *class);
DxfClass *dxf_class_set_next (DxfClass *class, DxfClass *next);
DxfClass *dxf_class_get_last (DxfClass *class);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_CLASS_H */


/* EOF */
