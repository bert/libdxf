/*!
 * \file comment.h
 *
 * \author Copyright (C) 2012, 2014, 2015, 2016, 2017, 2018
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF comment entity (\c COMMENT).
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
 * For more details see http://www.autodesk.com.\n\n
 * <hr>
 */


#ifndef LIBDXF_SRC_COMMENT_H
#define LIBDXF_SRC_COMMENT_H


#include "global.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief DXF definition of an AutoCAD comment entity (\c COMMENT).
 */
typedef struct
dxf_comment_struct
{
        int id_code;
                /*!< group code = 5\n
                 * Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file. */
        char *value;
                /*!< group code = 999\n
                 * The comment text string. */
        struct DxfComment *next;
                /*!< pointer to the next DxfComment.\n
                 * \c NULL in the last DxfComment. */
} DxfComment;


DxfComment *dxf_comment_new ();
DxfComment *dxf_comment_init (DxfComment *comment);
int dxf_comment_write (DxfFile *fp, DxfComment *comment);
int dxf_comment_free (DxfComment *comment);
void dxf_comment_free_list (DxfComment *comments);
int dxf_comment_get_id_code (DxfComment *comment);
DxfComment *dxf_comment_set_id_code (DxfComment *comment, int id_code);
char *dxf_comment_get_value (DxfComment *comment);
DxfComment *dxf_comment_set_value (DxfComment *comment, char *value);
DxfComment *dxf_comment_get_next (DxfComment *comment);
DxfComment *dxf_comment_set_next (DxfComment *comment, DxfComment *next);
DxfComment *dxf_comment_get_last (DxfComment *comment);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_COMMENT_H */


/* EOF */
