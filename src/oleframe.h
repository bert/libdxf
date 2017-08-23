/*!
 * \file oleframe.h
 *
 * \author Copyright (C) 2013 ... 2016, 2017 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF oleframe entity (\c OLEFRAME).
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


#ifndef LIBDXF_SRC_OLEFRAME_H
#define LIBDXF_SRC_OLEFRAME_H


#include "global.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief DXF definition of an AutoCAD oleframe entity (\c OLEFRAME).
 *
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
typedef struct
dxf_oleframe
{
        /* Members common for all DXF drawable entities. */
        int id_code;
                /*!< group code = 5\n
                 * Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file. */
        char *linetype;
                /*!< group code = 6\n
                 * The linetype of the entity.\n
                 * Defaults to \c BYLAYER if ommitted in the DXF file. */
        char *layer;
                /*!< group code = 8\n
                 * Layer on which the entity is drawn.\n
                 * Defaults to layer "0" if no valid layername is given. */
        double elevation;
                /*!< group code = 38\n
                 * Elevation of the arc in the local Z-direction.\n
                 * Defaults to 0.0 if omitted in the DXF file, or prior
                 * to DXF version R12, or DXF_FLATLAND equals 0 (default). */
        double thickness;
                /*!< group code = 39\n
                 * Thickness of the arc in the local Z-direction.\n
                 * Defaults to 0.0 if ommitted in the DXF file. */
        double linetype_scale;
                /*!< group code = 48\n
                 * Linetype scale (optional). */
        int16_t visibility;
                /*!< group code = 60\n
                 * Object visibility (optional): 0 = Visible; 1 = Invisible. */
        int color;
                /*!< group code = 62\n
                 * Color of the entity.\n
                 * Defaults to \c BYLAYER if ommitted in the DXF file.\n
                 * Note that entities encapsulated in a block with the
                 * color \c BYBLOCK are represented in the "native" color of
                 * the \c BLOCK entity. */
        int paperspace;
                /*!< group code = 67\n
                 * Entities are to be drawn on either \c PAPERSPACE or
                 * \c MODELSPACE.\n
                 * Optional, defaults to \c DXF_MODELSPACE (0). */
        char *dictionary_owner_soft;
                /*!< group code = 330\n
                 * Soft-pointer ID/handle to owner dictionary (optional). */
        char *dictionary_owner_hard;
                /*!< group code = 360\n
                 * Hard owner ID/handle to owner dictionary (optional). */
        /* Specific members for a DXF oleframe. */
        int ole_version_number ;
                /*!< group code = 70\n
                 * OLE version number ).\n */
        long length;
                /*!< group code = 90\n
                 * Length of binary data.\n */
        char *binary_data[DXF_MAX_PARAM];
                /*!< group code = 310\n
                 * Binary data (multiple lines).*/
        struct DxfOleFrame *next;
                /*!< pointer to the next DxfOleFrame.\n
                 * \c NULL in the last DxfOleFrame. */
} DxfOleFrame;


DxfOleFrame *dxf_oleframe_new ();
DxfOleFrame *dxf_oleframe_init (DxfOleFrame *oleframe);
DxfOleFrame *dxf_oleframe_read (DxfFile *fp, DxfOleFrame *oleframe);
int dxf_oleframe_write (DxfFile *fp, DxfOleFrame *oleframe);
int dxf_oleframe_free (DxfOleFrame *oleframe);
void dxf_oleframe_free_chain (DxfOleFrame *oleframes);
int dxf_oleframe_get_id_code (DxfOleFrame *oleframe);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_OLEFRAME_H */


/* EOF */
