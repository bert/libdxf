/*!
 * \file class.h
 *
 * \author Copyright (C) 2009 ... 2012 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF class entity (\c CLASS).
 *
 * The group codes described in this chapter are found only in DXF files.\n
 * The CLASSES section holds the information for application-defined classes
 * whose instances appear in the BLOCKS, ENTITIES, and OBJECTS sections of
 * the database.\n
 * It is assumed that a class definition is permanently fixed in the class
 * hierarchy.\n
 * All fields are required.\n
 * \n
 * AutoCAD registers the classes listed in the following table.\n
 * (This may not be a complete list of the classes found in a DXF file.\n
 * It depends on the applications currently in use by AutoCAD.)\n
 * \n
 * Default class values:\n
 * DXF Record Name      C++ Class Name             Code  Code  Code \n
 * Code 1               Code 2                     90    280   281 \n
 * ACDBDICTIONARYWDFLT  AcDbDictionaryWithDefault  0     0     0 \n
 * ACDBPLACEHOLDER      AcDbPlaceHolder            0     0     0 \n
 * ARCALIGNEDTEXT       AcDbArcAlignedText         0     0     1 \n
 * DICTIONARYVAR        AcDbDictionaryVar          0     0     0 \n
 * HATCH                AcDbHatch                  0     0     1 \n
 * IDBUFFER             AcDbIdBuffer               0     0     0 \n
 * IMAGE                AcDbRasterImage            127   0     1 \n
 * IMAGEDEF             AcDbRasterImageDef         0     0     0 \n
 * IMAGEDEF_REACTOR     AcDbRasterImageDefReactor  1     0     0 \n
 * LAYER_INDEX          AcDbLayerIndex             0     0     0 \n
 * LAYOUT               AcDbLayout                 0     0     0 \n
 * LWPOLYLINE           AcDbPolyline               0     0     1 \n
 * OBJECT_PTR           CAseDLPNTableRecord        1     0     0 \n
 * OLE2FRAME            AcDbOle2Frame              0     0     1 \n
 * RASTERVARIABLES      AcDbRasterVariables        0     0     0 \n
 * RTEXT                RText                      0     0     1 \n
 * SORTENTSTABLE        AcDbSortentsTable          0     0     0 \n
 * SPATIAL_INDEX        AcDbSpatialIndex           0     0     0 \n
 * SPATIAL_FILTER       AcDbSpatialFilter          0     0     0 \n
 * WIPEOUT              AcDbWipeout                127   0     1 \n
 * WIPEOUTVARIABLES     AcDbWipeoutVariables       0     0     0 \n
 * \n
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

#ifndef CLASS_H
#define CLASS_H


#include "global.h"

/*!
 * \brief DXF definition of a class entity (\c CLASS).
 *
 * Each entry in the CLASSES section contains the groups described
 * in the following table, as stated in the documentation for
 * AutoCAD DXF release 2000.
 */
typedef struct
dxf_class
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
                 * Posted in Alert box when a class definition listed in this
                 * section is not currently loaded. */ 
        int proxy_cap_flag;
                /*!< group code = 90.\n
                 * Proxy capabilities flag.\n
                 * Bit coded value that indicates the capabilities of this object as a proxy.\n
                 * 0 = No operations allowed (0)\n
                 * 1 = Erase allowed (0x1)\n
                 * 2 = Transform allowed (0x2)\n
                 * 4 = Color change allowed (0x4)\n
                 * 8 = Layer change allowed (0x8)\n
                 * 16 = Linetype change allowed (0x10)\n
                 * 32 = Linetype scale change allowed (0x20)\n
                 * 64 = Visibility change allowed (0x40)\n
                 * 127 = All operations except cloning allowed (0x7F)\n
                 * 128 = Cloning allowed (0x80)\n
                 * 255 = All operations allowed (0xFF)\n
                 * 32768 = R13 format proxy (0x8000). */
        int was_a_proxy_flag;
                /*!< group code = 280.\n
                 * Was-a-proxy flag.\n
                 * Set to 1 if class was not loaded when this DXF file was
                 * created, and 0 otherwise. */
        int is_an_entity_flag;
                /*!< group code = 281.\n
                 * Is-an-entity flag.\n
                 * Set to 1 if class was derived from the AcDbEntity class and
                 * can reside in the BLOCKS or ENTITIES section.\n
                 * If 0, instances may appear only in the OBJECTS section. */
        struct DxfClass *next;
                /*!< pointer to the next DxfClass.\n
                 * \c NULL in the last DxfClass. */
} DxfClass, * DxfClassPtr;


DxfClass *
dxf_class_new ();
DxfClass *
dxf_class_init
(
        DxfClass *dxf_class
);
int
dxf_class_read
(
        char *filename,
        FILE *fp,
        int *line_number,
        DxfClass *dxf_class,
        int acad_version_number
);
int
dxf_class_write_lowlevel
(
        FILE *fp,
        char *record_name,
        char *class_name,
        char *app_name,
        int proxy_cap_flag,
        int was_a_proxy_flag,
        int is_an_entity_flag
);
int
dxf_class_write
(
        FILE *fp,
        DxfClass dxf_class
);
int
dxf_class_write_endclass
(
        FILE *fp
);
int
dxf_class_free
(
        DxfClass *dxf_class
);


#endif /* CLASS_H */


/* EOF */
