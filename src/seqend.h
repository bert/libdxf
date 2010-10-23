/*!
 * \file seqend.h
 * \author Copyright (C) 2010 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 * \brief Header file for a DXF end of sequence marker (\c ENDSEQ).
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


#ifndef _SEQEND_H
#define _SEQEND_H


#include "global.h"


/*!
 * \brief DXF definition of an AutoCAD sequence end entity (\c SEQEND).
 */
typedef struct
dxf_seqend
{
        char *app_name;
                /*!< APP: name of entity that began the sequence.\n
                 * This entity marks the end of vertex
                 * (vertex type name) for a polyline,
                 * or the end of attribute entities (attrib type name)
                 * for an insert entity that has attributes
                 * (indicated by 66 group present and nonzero in insert
                 * entity).\n
                 * This code is not saved in a DXF file.\n
                 * Group code = 2. */
} DxfSeqend, * DxfSeqendPtr;


#endif /* _SEQEND_H */


/* EOF */
