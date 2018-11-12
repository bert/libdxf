/*!
 * \file entities.h
 *
 * \author Copyright (C) 2012, 2014, 2016, 2018
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF entities section (\c ENTITIES).
 *
 * This section presents the group codes that apply to graphical
 * objects.\n
 * These codes are found in the ENTITIES section of a DXF file and are
 * used by AutoLISP and ARX applications in entity definition lists.\n
 * \n
 * The group codes shown in this section can apply to DXF files,
 * applications (AutoLISP or ARX), or both.\n
 * When the description of a code is different for applications and DXF
 * files (or only applies to one or the other), the description is
 * preceeded by the following indicators:\n
 * \n
 * APP      Application-specific description.\n
 * \n
 * DXF      DXF file-specific description.\n
 * \n
 * If the description is common to both DXF files and applications, no
 * indicator is provided.\n
 * Otherwise, the appropriate indicator is present.\n
 * \n
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
 * For more details see http://www.autodesk.com.\n\n
 * <hr>
 */


#ifndef LIBDXF_SRC_ENTITIES_H
#define LIBDXF_SRC_ENTITIES_H


#include "global.h"
#include "3dface.h"
#include "3dsolid.h"
#include "acad_proxy_entity.h"
#include "arc.h"
#include "attdef.h"
#include "attrib.h"
#include "body.h"
#include "circle.h"
#include "dimension.h"
#include "ellipse.h"
#include "hatch.h"
//#include "spline.h"
//#include "helix.h"
#include "image.h"
#include "insert.h"
#include "leader.h"
#include "light.h"
#include "line.h"
#include "lwpolyline.h"
//#include "mesh.h"
#include "mline.h"
//#include "mleader.h"
#include "mtext.h"
#include "oleframe.h"
#include "ole2frame.h"
#include "point.h"
#include "polyline.h"
#include "ray.h"
#include "region.h"
#include "section.h"
#include "shape.h"
#include "solid.h"
//#include "sun.h"
//#include "surface.h"
#include "table.h"
#include "text.h"
#include "tolerance.h"
#include "trace.h"
//#include "underlay.h"
#include "vertex.h"
#include "viewport.h"
//#include "wipeout.h"
#include "xline.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief Definition of a DXF entity container.
 */
typedef struct
dxf_entities_struct
{
    struct Dxf3dface *dface_list;
    struct Dxf3dsolid *dsolid_list;
    struct DxfAcadProxyEntity *acad_proxy_entity_list;
    struct DxfArc *arc_list;
    struct DxfAttdef *attdef_list;
    struct DxfAttrib *attrib_list;
    struct DxfBody *body_list;
    struct DxfCircle *circle_list;
    struct DxfDimension *dimension_list;
    struct DxfEllipse *ellipse_list;
    struct DxfHatch *hatch_list;
    struct DxfHelix *helix_list;
    struct DxfImage *image_list;
    struct DxfInsert *insert_list;
    struct DxfLeader *leader_list;
    struct DxfLight *light_list;
    struct DxfLine *line_list;
    struct DxfLWPolyline *lw_polyline_list;
    //struct DxfMesh *mesh_list;
    struct DxfMline *mline_list;
    //struct DxfMleader *mleader_list;
    //struct DxfMLeaderStyle *mleaderstyle_list;
    struct DxfMtext *mtext_list;
    struct DxfOleFrame *oleframe_list;
    struct DxfOle2Frame *ole2frame_list;
    struct DxfPoint *point_list;
    struct DxfPolyline *polyline_list;
    struct DxfRay *ray_list;
    struct DxfRegion *region_list;
    //struct DxfSection *section_list;
    struct DxfShape *shape_list;
    struct DxfSolid *solid_list;
    struct DxfSpline *spline_list;
    //struct DxfSun *sun_list;
    //struct DxfSurface *surface_list;
    struct DxfTable *table_list;
    struct DxfText *text_list;
    struct DxfTolerance *tolerance_list;
    struct DxfTrace *trace_list;
    //struct DxfUnderlay *underlay_list;
    struct DxfVertex *vertex_list;
    struct DxfViewport *viewport_list;
    //struct DxfWipeout *wipeout_list;
    //struct DxfXLine *xline_list;
} DxfEntities;


DxfEntities *dxf_entities_new ();
DxfEntities *dxf_entities_init (DxfEntities *entities);
int dxf_entities_read_table (char *filename, FILE *fp, int line_number, char *dxf_entities_list, int acad_version_number);
int dxf_entities_write_table (char *dxf_entities_list, int acad_version_number);
int dxf_entities_free (DxfEntities *entities);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_ENTITIES_H */


/* EOF */
