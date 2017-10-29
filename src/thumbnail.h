/*!
 * \file thumbnail.h
 *
 * \author Copyright (C) 2010, 2012, 2014, 2015, 2016, 2017
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \author Copyright (C) 2010 by Luis Matos <gass@otiliamatos.ath.cx>.
 *
 * \brief Header file for DXF thumbnail (\c THUMBNAIL).
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


#ifndef LIBDXF_SRC_THUMBNAIL_H
#define LIBDXF_SRC_THUMBNAIL_H


#include "global.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief DXF definition of an AutoCAD arc entity (\c THUMBNAILIMAGE).
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
 * \version According to DXF R14 (backward compatibility).
 * \version According to DXF R2000.
 * \version According to DXF R2000i.
 * \version According to DXF R2002.
 * \version According to DXF R2004.
 * \version According to DXF R2005.
 * \version According to DXF R2006.
 * \version According to DXF R2008.
 * \version According to DXF R2009.
 * \version According to DXF R2010.
 * \version According to DXF R2011.
 * \version According to DXF R2012.
 * \version According to DXF R2013.
 * \version According to DXF R2014.
 */
typedef struct
dxf_thumbnail
{
        int number_of_bytes;
                /*!< group code = 90\n
                 * The number of bytes in the image (and subsequent binary
                 * chunk records). */
        char *preview_image_data[DXF_MAX_PARAM];
                /*!< group code = 310\n
                 * multiple lines (256 characters maximum per line). */
} DxfThumbnail;


DxfThumbnail *
dxf_thumbnail_new ();
DxfThumbnail *
dxf_thumbnail_init
(
        DxfThumbnail *thumbnail
);
DxfThumbnail *
dxf_thumbnail_read
(
        DxfFile *fp,
        DxfThumbnail *thumbnail
);
int
dxf_thumbnail_write
(
        DxfFile *fp,
        DxfThumbnail *thumbnail
);
int
dxf_thumbnail_free
(
        DxfThumbnail *thumbnail
);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_THUMBNAIL_H */


/* EOF */
