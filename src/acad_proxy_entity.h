/*!
 * \file acad_proxy_entity.h
 *
 * \author Copyright (C) 2008 ... 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF acad_proxy_entity entity
 * (\c ACAD_PROXY_ENTITY).
 *
 * \version The \c ACAD_ZOMBIE_ENTITY entity was introduced in DXF R13.
 * \version The \c ACAD_ZOMBIE_ENTITY entity was renamed to 
 * \c ACAD_PROXY_ENTITY in DXF R14.
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


#ifndef LIBDXF_SRC_ACAD_PROXY_ENTITY_H
#define LIBDXF_SRC_ACAD_PROXY_ENTITY_H


#include "global.h"


/*!
 * \brief DXF definition of an AutoCAD acad_proxy_entity entity
 * (\c ACAD_PROXY_ENTITY).
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 * \version According to DXF R2000.
 */
typedef struct
dxf_acad_proxy_entity
{
        /* Members common for all DXF drawable entities. */
        int id_code;
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file.\n
                 * Group code = 5. */
        char *linetype;
                /*!< The linetype of the entity.\n
                 * Defaults to \c BYLAYER if ommitted in the DXF file.\n
                 * Group code = 6. */
        char *layer;
                /*!< Layer on which the entity is drawn.\n
                 * Defaults to layer "0" if no valid layername is given.\n
                 * Group code = 8. */
        double linetype_scale;
                /*!< Linetype scale (optional).\n
                 * Group code = 48. */
        int visibility;
                /*!< Object visibility (optional):\n
                 * <ol>
                 * <li value = "0"> Visible</li>
                 * <li value = "1"> Invisible</li>
                 * </ol>
                 * Group code = 60. */
        int color;
                /*!< Color of the entity.\n
                 * Defaults to \c BYLAYER if ommitted in the DXF file.\n
                 * Note that entities encapsulated in a block with the
                 * color \c BYBLOCK are represented in the "native" color of
                 * the \c BLOCK entity.\n
                 * Group code = 62. */
        int paperspace;
                /*!< Entities are to be drawn on either \c PAPERSPACE or
                 * \c MODELSPACE.\n
                 * Optional, defaults to \c DXF_MODELSPACE (0).\n
                 * Group code = 67. */
        char *dictionary_owner_soft;
                /*!< Soft-pointer ID/handle to owner dictionary (optional).\n
                 * Group code = 330. */
        char *dictionary_owner_hard;
                /*!< Hard owner ID/handle to owner dictionary (optional).\n
                 * Group code = 360. */
        /* Specific members for a DXF acad_proxy_entity. */
        int original_custom_object_data_format;
                /*!< Original custom object data format:\n
                 * <ol>
                 * <li value = "0"> DWG format</li>
                 * <li value = "1"> DXF format</li>
                 * </ol>
                 * Added in AutoCAD release 2000.\n
                 * Group code = 70. */
        int proxy_entity_class_id;
                /*!< Always 498.\n
                 * Group code = 90. */
        int application_entity_class_id;
                /*!< Class IDs are based on the order of the class in the
                 * CLASSES section.\n
                 * The first class is given the ID of 500, the next is
                 * 501, and so on.\n
                 * Group code = 91. */
        int graphics_data_size;
                /*!< Size of graphics data in bytes.\n
                 * Group code = 92. */
        int entity_data_size;
                /*!< Size of entity data in bits.\n
                 * Group code = 93. */
        ulong object_drawing_format;
                /*!< Object drawing format when it becomes a proxy
                 * (a 32-bit unsigned integer):\n
                 * Low word is AcDbDwgVersion.\n
                 * High word is MaintenanceReleaseVersion.
                 * Added in AutoCAD release 2000.\n
                 * Group code = 95. */
        char *binary_graphics_data[DXF_MAX_PARAM];
                /*!< Binary graphics data (multiple entries can appear)
                 * (optional).\n
                 * Group code = 310. */
        char *object_id[DXF_MAX_PARAM];
                /*!< An object ID (multiple entries can appear).\n
                 * Group code = 330 or 340 or 350 or 360. */
        struct DxfAcadProxyEntity *next;
                /*!< Pointer to the next DxfAcadProxyEntity.\n
                 * \c NULL in the last DxfAcadProxyEntity. */
} DxfAcadProxyEntity;


DxfAcadProxyEntity *
dxf_acad_proxy_entity_new ();
DxfAcadProxyEntity *
dxf_acad_proxy_entity_init
(
        DxfAcadProxyEntity *acad_proxy_entity
);
DxfAcadProxyEntity *
dxf_acad_proxy_entity_read
(
        DxfFile *fp,
        DxfAcadProxyEntity *acad_proxy_entity
);
int
dxf_acad_proxy_entity_write
(
        DxfFile *fp,
        DxfAcadProxyEntity *acad_proxy_entity
);
int
dxf_acad_proxy_entity_free
(
        DxfAcadProxyEntity *acad_proxy_entity
);
void
dxf_acad_proxy_entity_free_chain
(
        DxfAcadProxyEntity *acad_proxy_entities
);
int
dxf_acad_proxy_entity_get_id_code
(
        DxfAcadProxyEntity *acad_proxy_entity
);
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_id_code
(
        DxfAcadProxyEntity *acad_proxy_entity,
        int id_code
);
char *
dxf_acad_proxy_entity_get_linetype
(
        DxfAcadProxyEntity *acad_proxy_entity
);
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_linetype
(
        DxfAcadProxyEntity *acad_proxy_entity,
        char *linetype
);
char *
dxf_acad_proxy_entity_get_layer
(
        DxfAcadProxyEntity *acad_proxy_entity
);
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_layer
(
        DxfAcadProxyEntity *acad_proxy_entity,
        char *layer
);
double
dxf_acad_proxy_entity_get_linetype_scale
(
        DxfAcadProxyEntity *acad_proxy_entity
);
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_linetype_scale
(
        DxfAcadProxyEntity *acad_proxy_entity,
        double linetype_scale
);
int16_t
dxf_acad_proxy_entity_get_visibility
(
        DxfAcadProxyEntity *acad_proxy_entity
);
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_visibility
(
        DxfAcadProxyEntity *acad_proxy_entity,
        int16_t visibility
);
int
dxf_acad_proxy_entity_get_color
(
        DxfAcadProxyEntity *acad_proxy_entity
);
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_color
(
        DxfAcadProxyEntity *acad_proxy_entity,
        int color
);
int
dxf_acad_proxy_entity_get_paperspace
(
        DxfAcadProxyEntity *acad_proxy_entity
);
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_paperspace
(
        DxfAcadProxyEntity *acad_proxy_entity,
        int paperspace
);
char *
dxf_acad_proxy_entity_get_dictionary_owner_soft
(
        DxfAcadProxyEntity *acad_proxy_entity
);
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_dictionary_owner_soft
(
        DxfAcadProxyEntity *acad_proxy_entity,
        char *dictionary_owner_soft
);
char *
dxf_acad_proxy_entity_get_dictionary_owner_hard
(
        DxfAcadProxyEntity *acad_proxy_entity
);
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_dictionary_owner_hard
(
        DxfAcadProxyEntity *acad_proxy_entity,
        char *dictionary_owner_hard
);
int
dxf_acad_proxy_entity_get_original_custom_object_data_format
(
        DxfAcadProxyEntity *acad_proxy_entity
);
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_original_custom_object_data_format
(
        DxfAcadProxyEntity *acad_proxy_entity,
        int original_custom_object_data_format
);
int
dxf_acad_proxy_entity_get_proxy_entity_class_id
(
        DxfAcadProxyEntity *acad_proxy_entity
);
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_proxy_entity_class_id
(
        DxfAcadProxyEntity *acad_proxy_entity,
        int proxy_entity_class_id
);
int
dxf_acad_proxy_entity_get_application_entity_class_id
(
        DxfAcadProxyEntity *acad_proxy_entity
);
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_application_entity_class_id
(
        DxfAcadProxyEntity *acad_proxy_entity,
        int application_entity_class_id
);
int
dxf_acad_proxy_entity_get_graphics_data_size
(
        DxfAcadProxyEntity *acad_proxy_entity
);
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_graphics_data_size
(
        DxfAcadProxyEntity *acad_proxy_entity,
        int graphics_data_size
);
int
dxf_acad_proxy_entity_get_entity_data_size
(
        DxfAcadProxyEntity *acad_proxy_entity
);
DxfAcadProxyEntity *
dxf_acad_proxy_entity_set_entity_data_size
(
        DxfAcadProxyEntity *acad_proxy_entity,
        int entity_data_size
);


#endif /* LIBDXF_SRC_ACAD_PROXY_ENTITY_H */


/* EOF */
