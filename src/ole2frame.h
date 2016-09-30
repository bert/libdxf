/*!
 * \file ole2frame.h
 *
 * \author Copyright (C) 2015 ... 2016 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF ole2frame entity (\c OLE2FRAME).
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


#ifndef LIBDXF_SRC_OLE2FRAME_H
#define LIBDXF_SRC_OLE2FRAME_H


#include "global.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief DXF definition of an AutoCAD ole2frame entity (\c OLE2FRAME).
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
 * \version According to DXF R14.
 */
typedef struct
dxf_ole2frame
{
        /* Members common for all DXF drawable entities. */
        int id_code;
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file.\n
                 * Group code = 5. */
        char *linetype;
                /*!< The linetype of the entity.\n
                 * Defaults to \c BYLAYER if ommitted in the DXF file.\n
                 * Group code = 6. */
        char *layer;
                /*!< Layer on which the entity is drawn.\n
                 * Defaults to layer "0" if no valid layername is given.\n
                 * Group code = 8. */
        double elevation;
                /*!< Elevation of the arc in the local Z-direction.\n
                 * Defaults to 0.0 if omitted in the DXF file, or prior
                 * to DXF version R12, or DXF_FLATLAND equals 0 (default).\n
                 * Group code = 38. */
        double thickness;
                /*!< Thickness of the arc in the local Z-direction.\n
                 * Defaults to 0.0 if ommitted in the DXF file.\n
                 * Group code = 39. */
        double linetype_scale;
                /*!< Linetype scale (optional).\n
                 * Group code = 48. */
        int16_t visibility;
                /*!< Object visibility (optional):\n
                 * <ol>
                 * <li value = "0"> Visible.</li>
                 * <li value = "1"> Invisible.</li>
                 * </ol>
                 * Group code = 60. */
        int color;
                /*!< Color of the entity.\n
                 * Defaults to \c BYLAYER if ommitted in the DXF file.\n
                 * Note that entities encapsulated in a block with the
                 * color \c BYBLOCK are represented in the "native" color of
                 * the \c BLOCK entity.\n
                 * Group code = 62. */
        int paperspace;
                /*!< Entities are to be drawn on either \c PAPERSPACE or
                 * \c MODELSPACE.\n
                 * Optional, defaults to \c DXF_MODELSPACE (0).\n
                 * Group code = 67. */
        char *dictionary_owner_soft;
                /*!< Soft-pointer ID/handle to owner dictionary (optional).\n
                 * Group code = 330. */
        char *dictionary_owner_hard;
                /*!< Hard owner ID/handle to owner dictionary (optional).\n
                 * Group code = 360. */
        /* Specific members for a DXF ole2frame. */
        char *end_of_data;
                /*!< End of Ole data (the string "OLE").\n
                 * Group code = 1.  */
        char *length_of_binary_data;
                /*!< Length of binary data.\n
                 * Group code = 3.  */
        double x0;
                /*!< X-value of the insertion point coordinate.\n
                 * Group code = 10. */
        double y0;
                /*!< Y-value of the insertion point coordinate.\n
                 * Group code = 20. */
        double z0;
                /*!< Z-value of the insertion point coordinate.\n
                 * Group code = 30. */
        double x1;
                /*!< X-value of the direction vector.\n
                 * Group code = 11. */
        double y1;
                /*!< Y-value of the direction vector.\n
                 * Group code = 21. */
        double z1;
                /*!< Z-value of the direction vector.\n
                 * Group code = 31. */
        int ole_version_number ;
                /*!<  OLE version number.\n
                 * Group code = 70. */
        int ole_object_type;
                /*!< OLE object type, 1 = link, 2 = embedded, 3 = static.\n
                 * Group code = 71.*/
        int tilemode_descriptor;
                /*!< Tile mode descriptor:\n
                 * <ol>
                 * <li value = "0"> Object is in a tiled model space
                 * viewport.</li>
                 * <li value = "1"> Object is in a non-tiled viewport
                 * (paper space or  floating model space).</li>
                 * </ol>
                 * Group code = 72.*/
        long length;
                /*!< group code = 90\n
                 * Length of binary data.\n */
        char *binary_data[DXF_MAX_PARAM];
                /*!< group code = 310\n
                 * Binary data (multiple lines).*/
        struct DxfOle2Frame *next;
                /*!< pointer to the next DxfOle2Frame.\n
                 * \c NULL in the last DxfOle2Frame. */
} DxfOle2Frame;


DxfOle2Frame *
dxf_ole2frame_new ();
DxfOle2Frame *
dxf_ole2frame_init
(
        DxfOle2Frame *ole2frame
);
DxfOle2Frame *
dxf_ole2frame_read
(
        DxfFile *fp,
        DxfOle2Frame *ole2frame
);
int
dxf_ole2frame_write
(
        DxfFile *fp,
        DxfOle2Frame *ole2frame
);
int
dxf_ole2frame_free
(
        DxfOle2Frame *ole2frame
);
void
dxf_ole2frame_free_chain
(
        DxfOle2Frame *ole2frames
);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_OLE2FRAME_H */


/* EOF */
