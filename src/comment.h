/*!
 * \file comment.h
 *
 * \author Copyright (C) 2008 ... 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF comment entity (\c COMMENT).
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


/*!
 * \brief DXF definition of an AutoCAD comment entity (\c COMMENT).
 */
typedef struct
dxf_comment
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


DxfComment *
dxf_comment_new ();
DxfComment *
dxf_comment_init
(
        DxfComment *comment
);
int
dxf_comment_write
(
        DxfFile *fp,
        DxfComment *comment
);
int
dxf_comment_free
(
        DxfComment *comment
);
void
dxf_comment_free_chain
(
        DxfComment *comments
);
DxfComment *
dxf_comment_set_value
(
        char *value,
        DxfComment *comment
);
char *
dxf_comment_get_value
(
        DxfComment *comment
);


#endif /* LIBDXF_SRC_COMMENT_H */


/* EOF */
