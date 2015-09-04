/*!
 * \file 3dface.h
 *
 * \author Copyright (C) 2010 ... 2014 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF 3D face entity (\c 3DFACE).
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


#ifndef LIBDXF_SRC_3DFACE_H
#define LIBDXF_SRC_3DFACE_H


#include "global.h"
#include "point.h"


/*!
 * \brief DXF definition of an AutoCAD 3D face entity (\c 3DFACE).
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
typedef struct
dxf_3dface
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
        /* Specific members for a DXF 3D face. */
        double x0;
                /*!< X-value of the base point.\n
                 * Group code = 10. */
        double y0;
                /*!< Y-value of the base point.\n
                 * Group code = 20. */
        double z0;
                /*!< Z-value of the base point.\n
                 * Group code = 30. */
        double x1;
                /*!< X-value of the first alignment point.\n
                 * Group code = 11. */
        double y1;
                /*!< Y-value of the first alignment point.\n
                 * Group code = 21. */
        double z1;
                /*!< Z-value of the first alignment point.\n
                 * Group code = 31. */
        double x2;
                /*!< X-value of the second alignment point.\n
                 * Group code = 12. */
        double y2;
                /*!< Y-value of the second alignment point.\n
                 * Group code = 22. */
        double z2;
                /*!< Z-value of the second alignment point.\n
                 * Group code = 32. */
        double x3;
                /*!< X-value of the third alignment point.\n
                 * Group code = 13. */
        double y3;
                /*!< Y-value of the third alignment point.\n
                 * Group code = 23. */
        double z3;
                /*!< Z-value of the third alignment point.\n
                 * Group code = 33. */
        int flag;
                /*!< Optional, defaults to 0.\n
                 * Bit coded:\n
                 * <ol>
                 * <li value = "1"> First edge is invisible.</li>
                 * <li value = "2"> Second edge is invisible.</li>
                 * <li value = "4"> Third edge is invisible.</li>
                 * <li value = "8"> Fourth edge is invisible.</li>
                 * </ol>
                 * Group code = 70. */
        struct Dxf3dface *next;
                /*!< Pointer to the next Dxf3dface.\n
                 * \c NULL in the last Dxf3dface. */
} Dxf3dface;


Dxf3dface *
dxf_3dface_new ();
Dxf3dface *
dxf_3dface_init
(
        Dxf3dface *face
);
Dxf3dface *
dxf_3dface_read
(
        DxfFile *fp,
        Dxf3dface *face
);
int
dxf_3dface_write
(
        DxfFile *fp,
        Dxf3dface *face
);
Dxf3dface *
dxf_3dface_free
(
        Dxf3dface *face
);
void
dxf_3dface_free_chain
(
        Dxf3dface *faces
);
int
dxf_3dface_get_id_code
(
        Dxf3dface *face
);
Dxf3dface *
dxf_3dface_set_id_code
(
        Dxf3dface *face,
        int id_code
);
char *
dxf_3dface_get_linetype
(
        Dxf3dface *face
);
Dxf3dface *
dxf_3dface_set_linetype
(
        Dxf3dface *face,
        char *linetype
);
char *
dxf_3dface_get_layer
(
        Dxf3dface *face
);
Dxf3dface *
dxf_3dface_set_layer
(
        Dxf3dface *face,
        char *layer
);
double
dxf_3dface_get_elevation
(
        Dxf3dface *face
);
Dxf3dface *
dxf_3dface_set_elevation
(
        Dxf3dface *face,
        double elevation
);
double
dxf_3dface_get_thickness
(
        Dxf3dface *face
);
Dxf3dface *
dxf_3dface_set_thickness
(
        Dxf3dface *face,
        double thickness
);
double
dxf_3dface_get_linetype_scale
(
        Dxf3dface *face
);
Dxf3dface *
dxf_3dface_set_linetype_scale
(
        Dxf3dface *face,
        double linetype_scale
);
int16_t
dxf_3dface_get_visibility
(
        Dxf3dface *face
);
Dxf3dface *
dxf_3dface_set_visibility
(
        Dxf3dface *face,
        int16_t visibility
);
int
dxf_3dface_get_color
(
        Dxf3dface *face
);
Dxf3dface *
dxf_3dface_set_color
(
        Dxf3dface *face,
        int color
);
int
dxf_3dface_get_paperspace
(
        Dxf3dface *face
);
Dxf3dface *
dxf_3dface_set_paperspace
(
        Dxf3dface *face,
        int paperspace
);
char *
dxf_3dface_get_dictionary_owner_soft
(
        Dxf3dface *face
);
Dxf3dface *
dxf_3dface_set_dictionary_owner_soft
(
        Dxf3dface *face,
        char *dictionary_owner_soft
);
char *
dxf_3dface_get_dictionary_owner_hard
(
        Dxf3dface *face
);
Dxf3dface *
dxf_3dface_set_dictionary_owner_hard
(
        Dxf3dface *face,
        char *dictionary_owner_hard
);
DxfPoint *
dxf_3dface_get_base_point
(
        Dxf3dface *face,
        int id_code,
        int inheritance
);
Dxf3dface *
dxf_3dface_set_base_point
(
        Dxf3dface *face,
        DxfPoint *point
);
DxfPoint *
dxf_3dface_get_first_alignment_point
(
        Dxf3dface *face,
        int id_code,
        int inheritance
);
Dxf3dface *
dxf_3dface_set_first_alignment_point
(
        Dxf3dface *face,
        DxfPoint *point
);
DxfPoint *
dxf_3dface_get_second_alignment_point
(
        Dxf3dface *face,
        int id_code,
        int inheritance
);
Dxf3dface *
dxf_3dface_set_second_alignment_point
(
        Dxf3dface *face,
        DxfPoint *point
);
DxfPoint *
dxf_3dface_get_third_alignment_point
(
        Dxf3dface *face,
        int id_code,
        int inheritance
);
Dxf3dface *
dxf_3dface_set_third_alignment_point
(
        Dxf3dface *face,
        DxfPoint *point
);
int
dxf_3dface_is_first_edge_invisible
(
        Dxf3dface *face
);
int
dxf_3dface_is_second_edge_invisible
(
        Dxf3dface *face
);
int
dxf_3dface_is_third_edge_invisible
(
        Dxf3dface *face
);
int
dxf_3dface_is_fourth_edge_invisible
(
        Dxf3dface *face
);
Dxf3dface *
dxf_3dface_create_from_points
(
        DxfPoint *p1,
        DxfPoint *p2,
        DxfPoint *p3,
        DxfPoint *p4,
        int id_code,
        int inheritance
);


#endif /* LIBDXF_SRC_3DFACE_H */


/* EOF */
