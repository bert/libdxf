/*!
 * \file object_id.h
 *
 * \author Copyright (C) 2016, 2017, 2018
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF object id functions.
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
 * For more details see http://www.autodesk.com .
 * <hr>
 */


#ifndef LIBDXF_SRC_OBJECT_ID_H
#define LIBDXF_SRC_OBJECT_ID_H


#include "global.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief DXF definition of an object id.
 */
typedef struct
dxf_object_id_struct
{
        int group_code;
                /*!< Group code of the id.\n
                 * Group code can be 330 or 340 or 350 or 360. */
        char *data;
                /*!< Pointer to the id. */
        int length;
                /*!< Length of the data member. */
        struct DxfObjectId *next;
                /*!< Pointer to the next DxfObjectId.\n
                 * \c NULL in the last DxfObjectId. */
} DxfObjectId;


DxfObjectId *dxf_object_id_new ();
DxfObjectId *dxf_object_id_init (DxfObjectId *object_id);
int dxf_object_id_free (DxfObjectId *object_id);
void dxf_object_id_free_list (DxfObjectId *object_ids);
int dxf_object_id_get_group_code (DxfObjectId *object_id);
DxfObjectId *dxf_object_id_set_group_code (DxfObjectId *object_id, int group_code);
char *dxf_object_id_get_data (DxfObjectId *object_id);
DxfObjectId *dxf_object_id_set_data (DxfObjectId *object_id, char *data);
int dxf_object_id_get_length (DxfObjectId *object_id);
DxfObjectId *dxf_object_id_set_length (DxfObjectId *object_id, int length);
DxfObjectId *dxf_object_id_get_next (DxfObjectId *object_id);
DxfObjectId *dxf_object_id_set_next (DxfObjectId *object_id, DxfObjectId *next);
DxfObjectId *dxf_object_id_get_last (DxfObjectId *object_id);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_OBJECT_ID_H */


/* EOF */
