/*!
 * \file leader.h
 *
 * \author Copyright (C) 2015, 2016, 2017 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Definition of a DXF leader entity (\c LEADER).
 *
 * \since The \c LEADER entity was introduced in DXF R13.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
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
 * For more details see http://www.autodesk.com.
 * <hr>
 */


#ifndef LIBDXF_SRC_LEADER_H
#define LIBDXF_SRC_LEADER_H


#include "global.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief DXF definition of an AutoCAD leader entity (\c LEADER).
 */
typedef struct
dxf_leader_struct
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
        char *dimension_style_name;
                /*!< Dimension style name.\n
                 * Group code = 3. */
        double x0[DXF_MAX_PARAM];
                /*!< X-value of the Vertex coordinates (one entry for
                 * each vertex).\n
                 * Group code = 10. */
        double y0[DXF_MAX_PARAM];
                /*!< Y-value of the Vertex coordinates (one entry for
                 * each vertex).\n
                 * Group code = 20. */
        double z0[DXF_MAX_PARAM];
                /*!< Z-value of the Vertex coordinates (one entry for
                 * each vertex).\n
                 * Group code = 30. */
        double text_annotation_height;
                /*!< Text annotation height.\n
                 * Group code = 40. */
        double text_annotation_width;
                /*!< Text annotation width.\n
                 * Group code = 41. */
        int arrow_head_flag;
                /*!< Arrow head flag.\n
                 * Bit coded:\n
                 * <ol>
                 * <li value = "0"> Disabled.</li>
                 * <li value = "1"> Enabled.</li>
                 * </ol>
                 * Group code = 71. */
        int path_type;
                /*!< Leader path type.\n
                 * Bit coded:\n
                 * <ol>
                 * <li value = "0"> Straight line segments.</li>
                 * <li value = "1"> Spline.</li>
                 * </ol>
                 * Group code = 72. */
        int creation_flag;
                /*!< Leader creation flag (default = 3).\n
                 * Not bit coded:\n
                 * <ol>
                 * <li value = "0"> Leader created with text annotation.</li>
                 * <li value = "1"> Created with tolerance annotation.</li>
                 * <li value = "2"> Created with block reference annotation.</li>
                 * <li value = "3"> Created without any annotation.</li>
                 * </ol>
                 * Group code = 73. */
        int hookline_direction_flag;
                /*!< Hookline direction flag.\n
                 * Not bit coded:\n
                 * <ol>
                 * <li value = "0"> Hookline (or end of tangent for a
                 * splined leader) is the opposite direction from the
                 * horizontal vector.</li>
                 * <li value = "1"> Hookline (or end of tangent for a
                 * splined leader) is the same direction as horizontal
                 * vector (see Group code 75).</li>
                 * </ol>
                 * Group code = 74. */
        int hookline_flag;
                /*!< Hookline flag.\n
                 * Bit coded:\n
                 * <ol>
                 * <li value = "0"> No hookline.</li>
                 * <li value = "1"> Has a hookline.</li>
                 * </ol>
                 * Group code = 75. */
        int number_vertices;
                /*!< Number of vertices in leader (ignored for DXFIN).\n
                 * Group code = 76. */
        int leader_color;
                /*!< Color to use if leader's DIMCLRD=BYBLOCK.\n
                 * Group code = 77. */
        double x_extr;
                /*!< X-value of the extrusion vector.\n
                 * Defaults to 0.0 if omitted in the DXF file.\n
                 * Group code = 210. */
        double y_extr;
                /*!< Y-value of the extrusion vector.\n
                 * Defaults to 0.0 if omitted in the DXF file.\n
                 * Group code = 220. */
        double z_extr;
                /*!< Z-value of the extrusion vector.\n
                 * Defaults to 1.0 if omitted in the DXF file.\n
                 * Group code = 230. */
        double x1;
                /*!< X-value of the "Horizontal" direction for leader.\n
                 * Group code = 211. */
        double y1;
                /*!< Y-value of the "Horizontal" direction for leader.\n
                 * Group code = 221. */
        double z1;
                /*!< Z-value of the "Horizontal" direction for leader.\n
                 * Group code = 231. */
        double x2;
                /*!< X-value of the Block reference insertion point
                 * offset from last leader vertex.\n
                 * Group code = 212. */
        double y2;
                /*!< Y-value of the Block reference insertion point
                 * offset from last leader vertex.\n
                 * Group code = 222. */
        double z2;
                /*!< Z-value of the Block reference insertion point
                 * offset from last leader vertex.\n
                 * Group code = 232. */
        double x3;
                /*!< X-value of the Annotation placement point offset
                 * from last leader vertex.\n
                 * Group code = 213. */
        double y3;
                /*!< Y-value of the Annotation placement point offset
                 * from last leader vertex.\n
                 * Group code = 223. */
        double z3;
                /*!< Z-value of the Annotation placement point offset
                 * from last leader vertex.\n
                 * Group code = 233. */
        char *annotation_reference_hard;
                /*!< Hard reference to associated annotation (mtext,
                 * tolerance, or insert entity).\n
                 * Group code = 340. */
        struct DxfLeader *next;
                /*!< Pointer to the next DxfLeader.\n
                 * \c NULL in the last DxfLeader. */
} DxfLeader;


DxfLeader *
dxf_leader_new ();
DxfLeader *
dxf_leader_init
(
        DxfLeader *leader
);
DxfLeader *
dxf_leader_read
(
        DxfFile *fp,
        DxfLeader *leader
);
int
dxf_leader_write
(
        DxfFile *fp,
        DxfLeader *leader
);
int
dxf_leader_free
(
        DxfLeader *leader
);
void
dxf_leader_free_chain
(
        DxfLeader *leaders
);
int
dxf_leader_get_id_code
(
        DxfLeader *leader
);
DxfLeader *
dxf_leader_set_id_code
(
        DxfLeader *leader,
        int id_code
);
char *
dxf_leader_get_linetype
(
        DxfLeader *leader
);
DxfLeader *
dxf_leader_set_linetype
(
        DxfLeader *leader,
        char *linetype
);
char *
dxf_leader_get_layer
(
        DxfLeader *leader
);
DxfLeader *
dxf_leader_set_layer
(
        DxfLeader *leader,
        char *layer
);
double
dxf_leader_get_elevation
(
        DxfLeader *leader
);
DxfLeader *
dxf_leader_set_elevation
(
        DxfLeader *leader,
        double elevation
);
double
dxf_leader_get_thickness
(
        DxfLeader *leader
);
DxfLeader *
dxf_leader_set_thickness
(
        DxfLeader *leader,
        double thickness
);
double
dxf_leader_get_linetype_scale
(
        DxfLeader *leader
);
DxfLeader *
dxf_leader_set_linetype_scale
(
        DxfLeader *leader,
        double linetype_scale
);
int16_t
dxf_leader_get_visibility
(
        DxfLeader *leader
);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_LEADER_H */


/* EOF */
