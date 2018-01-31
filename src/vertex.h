/*!
 * \file vertex.h
 *
 * \author Copyright (C) 2008, 2010, 2012, 2013, 2014, 2015, 2016, 2017,
 * 2018 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF vertex entity (\c VERTEX).
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


#ifndef LIBDXF_SRC_VERTEX_H
#define LIBDXF_SRC_VERTEX_H


#include "global.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief DXF definition of an AutoCAD vertex entity.
 *
 * Every \c VERTEX that is part of a polyface mesh has the 128 bit set in its
 * Vertex flags (70) group.\n
 * If the entity specifies the coordinates of a \c VERTEX of the mesh, the
 * 64 bit is set as well and the 10, 20, and 30 groups give the vertex
 * coordinates.\n
 * The \c VERTEX indexes are determined by the order in which the \c VERTEX
 * entities appear within the \c POLYLINE, with the first numbered 1.\n
 * \n
 * If the \c VERTEX defines a face of the mesh, its \c VERTEX flags (70)
 * group has the 128 bit set but not the 64 bit.\n
 * The 10, 20, and 30 (location) groups of the \c FACE entity are irrelevant
 * and are always written as zero in a DXF file.\n
 * The \c VERTEX indexes that define the mesh are given by 71, 72, 73, and 74
 * groups, the values of which are integers specifying one of the previously
 * defined vertices by index.\n
 * If the index is negative, the edge that begins with that \c VERTEX is
 * invisible.\n
 * The first zero \c VERTEX marks the end of the vertices of the face.\n
 * Since the 71 through 74 groups are optional fields with default values of
 * zero, they are present in DXF only if nonzero.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
typedef struct
dxf_vertex_struct
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
        /* Specific members for a DXF vertex. */
        double x0;
                /*!< X value of the location point.\n
                 * Group code = 10. */
        double y0;
                /*!< Y value of the location point.\n
                 * Group code = 20. */
        double z0;
                /*!< Z value of the location point.\n
                 * Group code = 30. */
        double start_width;
                /*!< Starting width (optional, defaults to 0.0).\n
                 * Group code = 40. */
        double end_width;
                /*!< Ending width (optional, defaults to 0.0).\n
                 * Group code = 41. */
        double bulge;
                /*!< Bulge (optional, defaults to 0.0).\n
                 * The bulge is the tangent of 1/4 the included angle for an
                 * arc segment, made negative if the arc goes clockwise from
                 * the start point to the endpoint; a bulge of 0 indicates a
                 * straight segment, and a bulge of 1 is a semicircle.\n
                 * Group code = 42. */
        double curve_fit_tangent_direction;
                /*!< Curve fit tangent direction.\n
                 * Group code = 50. */
        int flag;
                /*!< Flag (optional, defaults to 0)\n
                 * Bit coded:\n
                 * <ol>
                 * <li value = "1"> Extra vertex created by curve-fitting.</li>
                 * <li value = "2"> Curve-fit tangent defined for this
                 *   vertex.\n
                 *   A curve-fit tangent direction of 0 may be omitted
                 *   from the DXF output, but is significant if this
                 *   bit is set.</li>
                 * <li value = "4"> Unused (never set in DXF files).</li>
                 * <li value = "8"> Spline vertex created by spline-fitting.</li>
                 * <li value = "16"> Spline frame control point.</li>
                 * <li value = "32"> 3D Polyline vertex.</li>
                 * <li value = "64"> 3D polygon mesh vertex.</li>
                 * <li value = "128"> Polyface mesh vertex.</li>
                 * </ol>
                 * Group code = 70. */
        int polyface_mesh_vertex_index_1;
                /*!< Polyface mesh vertex index.\n
                 * Optional.\n
                 * Present only if nonzero.\n
                 * Group code = 71. */
        int polyface_mesh_vertex_index_2;
                /*!< Polyface mesh vertex index.\n
                 * Optional.\n
                 * Present only if nonzero.\n
                 * Group code = 72. */
        int polyface_mesh_vertex_index_3;
                /*!< Polyface mesh vertex index.\n
                 * Optional.\n
                 * Present only if nonzero.\n
                 * Group code = 73. */
        int polyface_mesh_vertex_index_4;
                /*!< Polyface mesh vertex index.\n
                 * Optional.\n
                 * Present only if nonzero.\n
                 * Group code = 74. */
        struct DxfVertex *next;
                /*!< Pointer to the next DxfVertex.\n
                 * \c NULL in the last DxfVertex. */
} DxfVertex;


DxfVertex *dxf_vertex_new ();
DxfVertex *dxf_vertex_init (DxfVertex *vertex);
DxfVertex *dxf_vertex_read (DxfFile *fp, DxfVertex *vertex);
int dxf_vertex_write (DxfFile *fp, DxfVertex *vertex);
int dxf_vertex_free (DxfVertex *vertex);
void dxf_vertex_free_chain (DxfVertex *vertices);
int dxf_vertex_get_id_code (DxfVertex *vertex);
DxfVertex *dxf_vertex_set_id_code (DxfVertex *vertex, int id_code);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_VERTEX_H */


/* EOF */
