/*!
 * \file param.h
 *
 * \author Copyright (C) 2008, 2012, 2014, 2016, 2017
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Definition of a DXF parameter entity.
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


#ifndef LIBDXF_SRC_PARAM_H
#define LIBDXF_SRC_PARAM_H


#include "global.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief DXF parameter definition.
 */
typedef union
dxf_param
{
        int group_code;
                /*!< parameter group code. */
        int I;
                /*!< integer value. */
        double D;
                /*!< double value. */
        char S[DXF_MAX_STRING_LENGTH];
                /*!< string value. */
} DxfParam;


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_PARAM_H */


/* EOF */
