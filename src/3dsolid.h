/*!
 * \file 3dsolid.h
 *
 * \author Copyright (C) 2012 ... 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF 3D solid entity (\c 3DSOLID).
 *
 * \version The \c 3DSOLID entity was introduced in DXF R13.
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


#ifndef LIBDXF_SRC_3DSOLID_H
#define LIBDXF_SRC_3DSOLID_H


#include "global.h"


/*!
 * \brief DXF definition of an AutoCAD 3D solid entity (\c 3DSOLID).
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
typedef struct
dxf_3dsolid
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
                 * <li value = "0"> Visible</li>
                 * <li value = "1"> Invisible</li>
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
        /* Specific members for a DXF 3D solid. */
        char *proprietary_data[DXF_MAX_PARAM];
                /*!< Proprietary data (multiple lines < 255 characters
                 * each).\n
                 * Group code = 1. */
        char *additional_proprietary_data[DXF_MAX_PARAM];
                /*!< Additional lines of proprietary data if previous
                 * group 1 string is greater than 255 characters
                 * (optional).\n
                 * Group code = 3. */
        int modeler_format_version_number;
                /*!< Modeler format version number (currently = 1).\n
                 * Group code = 70. */
        char *history;
                /*!< Soft-owner ID / handle to history object.\n
                 * Group code = 350. */
        struct Dxf3dsolid *next;
                /*!< Pointer to the next Dxf3dsolid.\n
                 * \c NULL in the last Dxf3dsolid. */
} Dxf3dsolid;


Dxf3dsolid *
dxf_3dsolid_new ();
Dxf3dsolid *
dxf_3dsolid_init
(
        Dxf3dsolid *solid
);
Dxf3dsolid *
dxf_3dsolid_read
(
        DxfFile *fp,
        Dxf3dsolid *solid
);
int
dxf_3dsolid_write
(
        DxfFile *fp,
        Dxf3dsolid *solid
);
int
dxf_3dsolid_free
(
        Dxf3dsolid *solid
);
void
dxf_3dsolid_free_chain
(
        Dxf3dsolid *solids
);
int
dxf_3dsolid_get_id_code
(
        Dxf3dsolid *solid
);
Dxf3dsolid *
dxf_3dsolid_set_id_code
(
        Dxf3dsolid *solid,
        int id_code
);
char *
dxf_3dsolid_get_linetype
(
        Dxf3dsolid *solid
);
Dxf3dsolid *
dxf_3dsolid_set_linetype
(
        Dxf3dsolid *solid,
        char *linetype
);
char *
dxf_3dsolid_get_layer
(
        Dxf3dsolid *solid
);
Dxf3dsolid *
dxf_3dsolid_set_layer
(
        Dxf3dsolid *solid,
        char *layer
);
double
dxf_3dsolid_get_elevation
(
        Dxf3dsolid *solid
);
Dxf3dsolid *
dxf_3dsolid_set_elevation
(
        Dxf3dsolid *solid,
        double elevation
);
double
dxf_3dsolid_get_thickness
(
        Dxf3dsolid *solid
);
Dxf3dsolid *
dxf_3dsolid_set_thickness
(
        Dxf3dsolid *solid,
        double thickness
);
double
dxf_3dsolid_get_linetype_scale
(
        Dxf3dsolid *solid
);
Dxf3dsolid *
dxf_3dsolid_set_linetype_scale
(
        Dxf3dsolid *solid,
        double linetype_scale
);
int16_t
dxf_3dsolid_get_visibility
(
        Dxf3dsolid *solid
);
Dxf3dsolid *
dxf_3dsolid_set_visibility
(
        Dxf3dsolid *solid,
        int16_t visibility
);
int
dxf_3dsolid_get_color
(
        Dxf3dsolid *solid
);
Dxf3dsolid *
dxf_3dsolid_set_color
(
        Dxf3dsolid *solid,
        int color
);
int
dxf_3dsolid_get_paperspace
(
        Dxf3dsolid *solid
);


#endif /* LIBDXF_SRC_3DSOLID_H */


/* EOF */
