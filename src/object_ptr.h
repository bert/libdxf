/*!
 * \file object_ptr.h
 *
 * \author Copyright (C) 2015, 2016, 2017, 2018
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF object_ptr object (\c OBJECT_PTR).
 *
 * \since The \c OBJECT_PTR object was introduced in DXF R14.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
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


#ifndef LIBDXF_SRC_OBJECT_PTR_H
#define LIBDXF_SRC_OBJECT_PTR_H


#include "global.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief DXF definition of an AutoCAD object_ptr object (\c OBJECT_PTR).
 */
typedef struct
dxf_object_ptr_struct
{
        /* Members common for all DXF objects. */
        int id_code;
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file.\n
                 * Group code = 5. */
        char *dictionary_owner_soft;
                /*!< Soft-pointer ID/handle to owner dictionary (optional).\n
                 * Group code = 330. */
        char *dictionary_owner_hard;
                /*!< Hard owner ID/handle to owner dictionary (optional).\n
                 * Group code = 360. */
        /* Specific members for a DXF object_ptr. */
        DxfChar *xdata;
                /*!< Begin ASE xdata (ACADASER13).\n
                 * Group code = 1001. */
        struct DxfObjectPtr *next;
                /*!< Pointer to the next DxfObjectPtr.\n
                 * \c NULL in the last DxfObjectPtr. */
} DxfObjectPtr;


DxfObjectPtr *dxf_object_ptr_new ();
DxfObjectPtr *dxf_object_ptr_init (DxfObjectPtr *object_ptr);
DxfObjectPtr *dxf_object_ptr_read (DxfFile *fp, DxfObjectPtr *object_ptr);
int dxf_object_ptr_write (DxfFile *fp, DxfObjectPtr *object_ptr);
int dxf_object_ptr_free (DxfObjectPtr *object_ptr);
void dxf_object_ptr_free_list (DxfObjectPtr *objectptrs);
int dxf_object_ptr_get_id_code (DxfObjectPtr *object_ptr);
DxfObjectPtr *dxf_object_ptr_set_id_code (DxfObjectPtr *object_ptr, int id_code);
char *dxf_object_ptr_get_dictionary_owner_soft (DxfObjectPtr *object_ptr);
DxfObjectPtr *dxf_object_ptr_set_dictionary_owner_soft (DxfObjectPtr *object_ptr, char *dictionary_owner_soft);
char *dxf_object_ptr_get_dictionary_owner_hard (DxfObjectPtr *object_ptr);
DxfObjectPtr *dxf_object_ptr_set_dictionary_owner_hard (DxfObjectPtr *object_ptr, char *dictionary_owner_hard);
DxfObjectPtr *dxf_object_ptr_get_next (DxfObjectPtr *object_ptr);
DxfObjectPtr *dxf_object_ptr_set_next (DxfObjectPtr *object_ptr, DxfObjectPtr *next);
DxfObjectPtr *dxf_object_ptr_get_last (DxfObjectPtr *object_ptr);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_OBJECT_PTR_H */


/* EOF */
