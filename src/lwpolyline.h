/*!
 * \file lwpolyline.h
 *
 * \author Copyright (C) 2010, 2012, 2014, 2015, 2016, 2017
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF light weight polyline entity (\c LWPOLYLINE).
 *
 * \warning This entity requires AutoCAD version R14 or higher.
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


#ifndef LIBDXF_SRC_LWPOLYLINE_H
#define LIBDXF_SRC_LWPOLYLINE_H


#include "global.h"
#include "vertex.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief Definition of a DXF light weight polyline entity.
 */
typedef struct
dxf_lwpolyline_struct
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
                 * to DXF version R12, or DXF_FLATLAND equals 0
                 * (default).\n
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
                 * </ol>\n
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
                /*!< group code = 330\n
                 * Soft-pointer ID/handle to owner dictionary (optional). */
        char *dictionary_owner_hard;
                /*!< group code = 360\n
                 * Hard owner ID/handle to owner dictionary (optional). */
        /* Specific members for a DXF lwpolyline. */
        double constant_width;
                /*!< Not used if variable width (codes 40 and/or 41) is
                 * set the default widths apply to any vertex that
                 * doesn't supply widths.\n
                 * Optional, defaults to 0.0.\n
                 * Group code = 43. */
        int flag;
                /*!< Polyline flag.\n
                 * Bit coded:\n
                 * <ol>
                 * <li value = "1"> Closed.</li>
                 * <li value = "128"> Plinegen.</li>
                 * </ol>
                 * Optional, defaults to 0.\n
                 * Group code = 70. */
        int number_vertices;
                /*!< Number of vertices.\n
                 * Group code = 90. */
        double extr_x0;
                /*!< Extrusion direction (optional; default = 0, 0, 1)\n
                 * DXF: X value;\n
                 * APP: 3D vector\n
                 * Defaults to 0.0 if ommitted in the DXF file.\n
                 * Group code = 210. */
        double extr_y0;
                /*!< DXF: Y value of extrusion direction (optional).\n
                 * Group code = 220. */
        double extr_z0;
                /*!< DXF: Z value of extrusion direction (optional).\n
                 * Group code = 230. */
        struct DxfVertex *vertices;
                /*!< Pointer to the first DxfVertex of the lwpolyline.\n
                 * \c NULL in the last DxfVertex.\n
                 * \note Not all members of the DxfVertex struct are
                 * used for lwpolylines. */
        struct DxfLWPolyline *next;
                /*!< Pointer to the next DxfLWPolyline.\n
                 * \c NULL in the last DxfLWPolyline. */
} DxfLWPolyline;


DxfLWPolyline *
dxf_lwpolyline_new ();
DxfLWPolyline *
dxf_lwpolyline_init
(
        DxfLWPolyline *lwpolyline
);
DxfLWPolyline *
dxf_lwpolyline_read
(
        DxfFile *fp,
        DxfLWPolyline *lwpolyline
);
int
dxf_lwpolyline_write
(
        DxfFile *fp,
        DxfLWPolyline *lwpolyline
);
int dxf_lwpolyline_free
(
        DxfLWPolyline *lwpolyline
);
void
dxf_lwpolyline_free_chain
(
        DxfLWPolyline *lwpolylines
);
int
dxf_lwpolyline_get_id_code
(
        DxfLWPolyline *lwpolyline
);
DxfLWPolyline *
dxf_lwpolyline_set_id_code
(
        DxfLWPolyline *lwpolyline,
        int id_code
);
char *
dxf_lwpolyline_get_linetype
(
        DxfLWPolyline *lwpolyline
);
DxfLWPolyline *
dxf_lwpolyline_set_linetype
(
        DxfLWPolyline *lwpolyline,
        char *linetype
);
char *
dxf_lwpolyline_get_layer
(
        DxfLWPolyline *lwpolyline
);
DxfLWPolyline *
dxf_lwpolyline_set_layer
(
        DxfLWPolyline *lwpolyline,
        char *layer
);
double
dxf_lwpolyline_get_elevation
(
        DxfLWPolyline *lwpolyline
);
DxfLWPolyline *
dxf_lwpolyline_set_elevation
(
        DxfLWPolyline *lwpolyline,
        double elevation
);
double
dxf_lwpolyline_get_thickness
(
        DxfLWPolyline *lwpolyline
);
DxfLWPolyline *
dxf_lwpolyline_set_thickness
(
        DxfLWPolyline *lwpolyline,
        double thickness
);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_LWPOLYLINE_H */


/* EOF */
