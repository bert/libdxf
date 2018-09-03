/*!
 * \file drawing.h
 *
 * \author Copyright (C) 2016, 2017, 2018
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Prototypes for a libDXF drawing.
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


#ifndef LIBDXF_SRC_DRAWING_H
#define LIBDXF_SRC_DRAWING_H


#include "global.h"
#include "header.h"
#include "class.h"
#include "tables.h"
#include "block.h"
#include "global.h"
#include "entities.h"
#include "object.h"
#include "thumbnail.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief Definition of a DXF drawing.
 */
typedef struct
dxf_drawing_struct
{
    struct DxfHeader *header;
        /*!< Header data.*/
    struct DxfClass *class_list;
        /*!< Classes section data (single linked list).*/
    struct DxfTables *tables_list;
        /*!< Tables section data (single linked list).*/
    struct DxfBlock *block_list;
        /*!< Blocks section data (single linked list).*/
    struct DxfEntities *entities_list;
        /*!< Entities section data (single linked list).*/
    struct DxfObject *object_list;
        /*!< Objects section data (single linked list).*/
    struct DxfThumbnail *thumbnail;
        /*!< Thumbnail data.*/
    struct DxfDrawing *next;
                /*!< Pointer to the next DxfDrawing.\n
                 * \c NULL in the last DxfDrawing. */
} DxfDrawing;


DxfDrawing *dxf_drawing_new ();
DxfDrawing *dxf_drawing_init (DxfDrawing *drawing, int acad_version_number);
int dxf_drawing_free (DxfDrawing *drawing);
DxfHeader *dxf_drawing_get_header (DxfDrawing *drawing);
DxfDrawing *dxf_drawing_set_header (DxfDrawing *drawing, DxfHeader *header);
DxfClass *dxf_drawing_get_class_list (DxfDrawing *drawing);
DxfDrawing *dxf_drawing_set_class_list (DxfDrawing *drawing, DxfClass *class_list);
DxfTables *dxf_drawing_get_tables_list (DxfDrawing *drawing);
DxfDrawing *dxf_drawing_set_tables_list (DxfDrawing *drawing, DxfTables *tables_list);
DxfBlock *dxf_drawing_get_block_list (DxfDrawing *drawing);
DxfDrawing *dxf_drawing_set_block_list (DxfDrawing *drawing, DxfBlock *block_list);
DxfEntities *dxf_drawing_get_entities_list (DxfDrawing *drawing);
DxfDrawing *dxf_drawing_set_entities_list (DxfDrawing *drawing, DxfEntities *entities_list);
DxfObject *dxf_drawing_get_object_list (DxfDrawing *drawing);
DxfDrawing *dxf_drawing_set_object_list (DxfDrawing *drawing, DxfObject *object_list);
DxfThumbnail *dxf_drawing_get_thumbnail (DxfDrawing *drawing);
DxfDrawing *dxf_drawing_set_thumbnail (DxfDrawing *drawing, DxfThumbnail *thumbnail);
DxfDrawing *dxf_drawing_get_next (DxfDrawing *drawing);
DxfDrawing *dxf_drawing_set_next (DxfDrawing *drawing, DxfDrawing *next);
DxfDrawing *dxf_drawing_get_last (DxfDrawing *drawing);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_DRAWING_H */


/* EOF */
