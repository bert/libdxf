/*!
 * \file appid.h
 *
 * \author Copyright (C) 2008, 2009, 2011, 2012, 2014, 2015, 2016, 2017,
 * 2018, 2019 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF application identity symbol table entry
 * (\c APPID).
 *
 * \since The \c APPID table was introduced in DXF R12.
 *
 * A DXF \c APPID symbol table entry contains data concerning the
 * application registered with the drawing involved.\n
 * It is a table entry in the \c TABLES section of the DXF file.
 * These table entries maintain a set of names for all applications
 * registered with a drawing.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
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


#ifndef LIBDXF_SRC_APPID_H
#define LIBDXF_SRC_APPID_H


#include "global.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief DXF Definition of an AutoCAD application identification
 * (\c APPID).
 *
 * This table entry contains a name for an application
 * registered with a drawing.
 */
typedef struct
dxf_appid_struct
{
        int id_code;
                /*!< Identification number for the entry.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file.\n
                 * Group code = 5. */
        char *application_name;
                /*!< Name of the application registered with the drawing.\n
                 * Group code = 2. */
        int16_t flag;
                /*!< This flag is for the benefit of AutoCAD commands;
                 * it can be ignored by most programs that read DXF files,
                 * and need not be set by programs that write DXF files.\n
                 * bit coded:\n
                 * <ol>
                 * <li value = "16"> if set, table entry is externally
                 * dependent on an Xref.</li>
                 * <li value = "32"> if this bit and bit 16 are both set,
                 * the externally dependent Xref has been successfully
                 * resolved.</li>
                 * <li value = "64"> if set, the table entry was
                 * referenced by at least one entity in the drawing the
                 * last time the drawing was edited.</li>
                 * </ol>
                 * Group code = 70. */
        char *dictionary_owner_soft;
                /*!< Soft-pointer ID/handle to owner dictionary
                 * (optional).\n
                 * Group code = 330. */
        char *object_owner_soft;
                /*!< Soft-pointer ID/handle  to owner BLOCK_RECORD object.\n
                 * Group code = 330.\n
                 * \since Introduced in version R2000. */
        char *dictionary_owner_hard;
                /*!< Hard owner ID/handle to owner dictionary
                 * (optional).\n
                 * Group code = 360. */
        struct DxfAppid *next;
                /*!< Pointer to the next DxfAppid.\n
                 * \c NULL in the last DxfAppid. */
} DxfAppid;


DxfAppid *dxf_appid_new ();
DxfAppid *dxf_appid_init (DxfAppid *appid);
DxfAppid *dxf_appid_read (DxfFile *fp, DxfAppid *appid);
int dxf_appid_write (DxfFile *fp, DxfAppid* appid);
int dxf_appid_free (DxfAppid *appid);
void dxf_appid_free_list (DxfAppid *appids);
int dxf_appid_get_id_code (DxfAppid *appid);
DxfAppid *dxf_appid_set_id_code (DxfAppid *appid, int id_code);
char *dxf_appid_get_application_name (DxfAppid *appid);
DxfAppid *dxf_appid_set_application_name (DxfAppid *appid, char *name);
int16_t dxf_appid_get_flag (DxfAppid *appid);
DxfAppid *dxf_appid_set_flag (DxfAppid *appid, int16_t flag);
int dxf_appid_is_xreferenced (DxfAppid *appid);
int dxf_appid_is_xresolved (DxfAppid *appid);
int dxf_appid_is_referenced (DxfAppid *appid);
int dxf_appid_is_no_save_xdata (DxfAppid *appid);
char *dxf_appid_get_dictionary_owner_soft (DxfAppid *appid);
DxfAppid *dxf_appid_set_dictionary_owner_soft (DxfAppid *appid, char *dictionary_owner_soft);
char *dxf_appid_get_object_owner_soft (DxfAppid *appid);
DxfAppid *dxf_appid_set_object_owner_soft (DxfAppid *appid, char *object_owner_soft);
char *dxf_appid_get_dictionary_owner_hard (DxfAppid *appid);
DxfAppid *dxf_appid_set_dictionary_owner_hard (DxfAppid *appid, char *dictionary_owner_hard);
DxfAppid *dxf_appid_get_next (DxfAppid *appid);
DxfAppid *dxf_appid_set_next (DxfAppid *appid, DxfAppid *next);
DxfAppid *dxf_appid_get_last (DxfAppid *appid);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_APPID_H */


/* EOF */
