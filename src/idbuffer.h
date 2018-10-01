/*!
 * \file idbuffer.h
 *
 * \author Copyright (C) 2015, 2016, 2017, 2018
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF idbuffer object (\c IDBUFFER).
 *
 * The \c IDBUFFER object is a utility object that is just a list of
 * references to objects.
 *
 * \since The \c IDBUFFER object was introduced in DXF R14.
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


#ifndef LIBDXF_SRC_IDBUFFER_H
#define LIBDXF_SRC_IDBUFFER_H


#include "global.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief DXF definition of a single linked list of entity pointers.
 */
typedef struct
dxf_idbuffer_entity_pointer_struct
{
        char *soft_pointer;
                /*!< Soft pointer reference to entity (multiple entries
                 * may exist).\n
                 * Group code = 330. */
        struct DxfIdbufferEntityPointer *next;
                /*!< Pointer to the next DxfIdbufferEntityPointer.\n
                 * \c NULL in the last DxfIdbufferEntityPointer. */
} DxfIdbufferEntityPointer;


/*!
 * \brief DXF definition of an AutoCAD idbuffer object (\c IDBUFFER).
 */
typedef struct
dxf_idbuffer_struct
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
        char *object_owner_soft;
                /*!< Soft-pointer ID/handle  to owner BLOCK_RECORD object.\n
                 * Group code = 330.\n
                 * \since Introduced in version R2000. */
        char *dictionary_owner_hard;
                /*!< Hard owner ID/handle to owner dictionary (optional).\n
                 * Group code = 360. */
        /* Specific members for a DXF idbuffer. */
        DxfIdbufferEntityPointer *entity_pointer;
                /*!< Soft pointer reference to entity (multiple entries
                 * may exist).\n
                 * Pointer to the first entry of a single linked list.\n
                 * Group code = 330. */
        struct DxfIdbuffer *next;
                /*!< Pointer to the next DxfIdbuffer.\n
                 * \c NULL in the last DxfIdbuffer. */
} DxfIdbuffer;


DxfIdbuffer *dxf_idbuffer_new ();
DxfIdbuffer *dxf_idbuffer_init (DxfIdbuffer *idbuffer);
DxfIdbuffer *dxf_idbuffer_read (DxfFile *fp, DxfIdbuffer *idbuffer);
int dxf_idbuffer_write (DxfFile *fp, DxfIdbuffer *idbuffer);
int dxf_idbuffer_free (DxfIdbuffer *idbuffer);
void dxf_idbuffer_free_list (DxfIdbuffer *id_buffers);
int dxf_idbuffer_get_id_code (DxfIdbuffer *idbuffer);
DxfIdbuffer *dxf_idbuffer_set_id_code (DxfIdbuffer *idbuffer, int id_code);
char *dxf_idbuffer_get_dictionary_owner_soft (DxfIdbuffer *idbuffer);
DxfIdbuffer *dxf_idbuffer_set_dictionary_owner_soft (DxfIdbuffer *idbuffer, char *dictionary_owner_soft);
char *dxf_idbuffer_get_object_owner_soft (DxfIdbuffer *idbuffer);
DxfIdbuffer *dxf_idbuffer_set_object_owner_soft (DxfIdbuffer *idbuffer, char *object_owner_soft);
char *dxf_idbuffer_get_dictionary_owner_hard (DxfIdbuffer *idbuffer);
DxfIdbuffer *dxf_idbuffer_set_dictionary_owner_hard (DxfIdbuffer *idbuffer, char *dictionary_owner_hard);
DxfIdbufferEntityPointer *dxf_idbuffer_get_entity_pointer (DxfIdbuffer *idbuffer);
DxfIdbuffer *dxf_idbuffer_set_entity_pointer (DxfIdbuffer *idbuffer, DxfIdbufferEntityPointer *entity_pointer);
DxfIdbuffer *dxf_idbuffer_get_next (DxfIdbuffer *idbuffer);
DxfIdbuffer *dxf_idbuffer_set_next (DxfIdbuffer *idbuffer, DxfIdbuffer *next);
DxfIdbuffer *dxf_idbuffer_get_last (DxfIdbuffer *idbuffer);
DxfIdbufferEntityPointer *dxf_idbuffer_entity_pointer_new ();
DxfIdbufferEntityPointer *dxf_idbuffer_entity_pointer_init (DxfIdbufferEntityPointer *entity_pointer);
int dxf_idbuffer_entity_pointer_free (DxfIdbufferEntityPointer *entity_pointer);
void dxf_idbuffer_entity_pointer_free_list (DxfIdbufferEntityPointer *entity_pointers);
char *dxf_idbuffer_entity_pointer_get_soft_pointer (DxfIdbufferEntityPointer *entity_pointer);
DxfIdbufferEntityPointer *dxf_idbuffer_entity_pointer_set_soft_pointer (DxfIdbufferEntityPointer *entity_pointer, char *soft_pointer);
DxfIdbufferEntityPointer *dxf_idbuffer_entity_pointer_get_next (DxfIdbufferEntityPointer *entity_pointer);
DxfIdbufferEntityPointer *dxf_idbuffer_entity_pointer_set_next (DxfIdbufferEntityPointer *entity_pointer, DxfIdbufferEntityPointer *next);
DxfIdbufferEntityPointer *dxf_idbuffer_entity_pointer_get_last (DxfIdbufferEntityPointer *entity_pointer);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_IDBUFFER_H */


/* EOF */
