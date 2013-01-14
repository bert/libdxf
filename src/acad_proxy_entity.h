/*!
 * \file acad_proxy_entity.h
 *
 * \author Copyright (C) 2008 ... 2013 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Definition of a DXF acad_proxy_entity entity.
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


#ifndef _ACAD_PROXY_ENTITY_H
#define _ACAD_PROXY_ENTITY_H


#include "global.h"


/*!
 * \brief DXF definition of an AutoCAD acad_proxy_entity entity.
 */
typedef struct
dxf_acad_proxy_entity
{
        /* Members common for all DXF drawable entities. */
        int id_code;
                /*!< group code = 5\n
                 * Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file. */
        char *linetype;
                /*!< group code = 6\n
                 * The linetype of the entity.\n
                 * Defaults to \c BYLAYER if ommitted in the DXF file. */
        char *layer;
                /*!< group code = 8\n
                 * Layer on which the entity is drawn.\n
                 * Defaults to layer "0" if no valid layername is given. */
        double thickness;
                /*!< group code = 39\n
                 * Thickness of the arc in the local Z-direction.\n
                 * Defaults to 0.0 if ommitted in the DXF file. */
        double linetype_scale;
                /*!< group code = 48\n
                 * Linetype scale (optional). */
        int object_visability;
                /*!< group code = 60\n
                 * Object visibility (optional):\n
                 * 0 = visible, 1 = invisible. */
        int color;
                /*!< group code = 62\n
                 * Color of the entity.\n
                 * Defaults to \c BYLAYER if ommitted in the DXF file.\n
                 * Note that entities encapsulated in a block with the
                 * color \c BYBLOCK are represented in the "native" color of
                 * the \c BLOCK entity. */
        int paperspace;
                /*!< group code = 67\n
                 * Entities are to be drawn on either \c PAPERSPACE or
                 * \c MODELSPACE.\n
                 * Optional, defaults to \c DXF_MODELSPACE (0). */
        /* Specific members for a DXF acad_proxy_entity. */
        int original_custom_object_data_format;
                /*!< group code = 70\n
                 * Original custom object data format:\n
                 * 0 = DWG format\n
                 * 1 = DXF format.
                 * Added in AutoCAD release 2000. */
        int proxy_entity_class_id;
                /*!< group code = 90\n
                 * Always 498. */
        int application_entity_class_id;
                /*!< group code = 91\n
                 * Class IDs are based on the order of the class in the
                 * CLASSES section.\n
                 * The first class is given the ID of 500, the next is
                 * 501, and so on. */
        int graphics_data_size;
                /*!< group code = 92\n
                 * Size of graphics data in bytes. */
        int entity_data_size;
                /*!< group code = 93\n
                 * Size of entity data in bits. */
        ulong object_drawing_format;
                /*!< group code = 95\n
                 * Object drawing format when it becomes a proxy
                 * (a 32-bit unsigned integer):\n
                 * Low word is AcDbDwgVersion.\n
                 * High word is MaintenanceReleaseVersion.
                 * Added in AutoCAD release 2000. */
        char *binary_graphics_data[DXF_MAX_PARAM];
                /*!< group code = 310\n
                 * Binary graphics data (multiple entries can appear)
                 * (optional). */
        char *object_id[DXF_MAX_PARAM];
                /*!< group code = 330 or 340 or 350 or 360\n
                 * An object ID (multiple entries can appear). */
        struct DxfAcadProxyEntity *next;
                /*!< pointer to the next DxfLayer.\n
                 * \c NULL in the last DxfLayer. */
} DxfAcadProxyEntity, * DxfAcadProxyEntityPtr;


DxfAcadProxyEntity *
dxf_acad_proxy_entity_new ();
DxfAcadProxyEntity *
dxf_acad_proxy_entity_init
(
        DxfAcadProxyEntity *dxf_acad_proxy_entity
);
int
dxf_acad_proxy_entity_read
(
        DxfFile *fp,
        DxfAcadProxyEntity *dxf_acad_proxy_entity
);
int
dxf_acad_proxy_entity_write
(
        DxfFile *fp,
        DxfAcadProxyEntity *dxf_acad_proxy_entity
);
int
dxf_acad_proxy_entity_free
(
        DxfAcadProxyEntity *dxf_acad_proxy_entity
);


#endif /* _ACAD_PROXY_ENTITY_H */


/* EOF */
