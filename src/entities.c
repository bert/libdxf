/*!
 * \file entities.c
 *
 * \author Copyright (C) 2012, 2014, 2017, 2018
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF entities section (/c ENTITIES).
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


#include "entities.h"


/*!
 * \brief Allocate memory for a DXF \c ENTITIES section.
 *
 * Fill the memory contents with zeros.
 */
DxfEntities *
dxf_entities_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfEntities *entities = NULL;
        size_t size;

        size = sizeof (DxfEntities);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((entities = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfEntities struct.\n")),
                  __FUNCTION__);
                entities = NULL;
        }
        else
        {
                memset (entities, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (entities);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF
 * \c ENTITIES section.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfEntities *
dxf_entities_init
(
        DxfEntities *entities
                /*!< DXF entities section. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (entities == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                entities = dxf_entities_new ();
        }
        if (entities == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory for a DxfEntities struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        entities->dface_list = NULL;
        entities->dsolid_list = NULL;
        entities->acad_proxy_entity_list = NULL;
        entities->arc_list = NULL;
        entities->attdef_list = NULL;
        entities->attrib_list = NULL;
        entities->body_list = NULL;
        entities->circle_list = NULL;
        entities->dimension_list = NULL;
        entities->ellipse_list = NULL;
        entities->hatch_list = NULL;
        entities->helix_list = NULL;
        entities->image_list = NULL;
        entities->insert_list = NULL;
        entities->leader_list = NULL;
        entities->light_list = NULL;
        entities->line_list = NULL;
        entities->lw_polyline_list = NULL;
        //entities->mesh_list = NULL;
        entities->mline_list = NULL;
        //entities->mleader_list = NULL;
        //entities->mleaderstyle_list = NULL;
        entities->mtext_list = NULL;
        entities->oleframe_list = NULL;
        entities->ole2frame_list = NULL;
        entities->point_list = NULL;
        entities->polyline_list = NULL;
        entities->ray_list = NULL;
        entities->region_list = NULL;
        //entities->section_list = NULL;
        entities->shape_list = NULL;
        entities->solid_list = NULL;
        entities->spline_list = NULL;
        //entities->sun_list = NULL;
        //entities->surface_list = NULL;
        entities->table_list = NULL;
        entities->text_list = NULL;
        entities->tolerance_list = NULL;
        entities->trace_list = NULL;
        //entities->underlay_list = NULL;
        entities->vertex_list = NULL;
        entities->viewport_list = NULL;
        //entities->wipeout_list = NULL;
        //entities->xline_list = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (entities);
}


/*!
 * \brief Read and parse the \c ENTITIES table from a DXF file.
 */
int
dxf_entities_read_table
(
        char *filename,
                /*!< filename of input file (or device). */
        FILE *fp,
                /*!< filepointer to the input file (or device). */
        int line_number,
                /*!< current line number in the input file (or device). */
        char *dxf_entities_list,
                /*!< pointer to a list of entities. */
        int acad_version_number
                /*!< AutoCAD DXF version number. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /*! \todo Add code here. */
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write DXF output to a file for a DXF \c ENTITIES table.
 */
int
dxf_entities_write_table
(
        char *dxf_entities_list,
                /*!< pointer to a list of entities. */
        int acad_version_number
                /*!< AutoCAD DXF version number. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /*! \todo Add code here. */
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c ENTITIES section and
 * all it's data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_entities_free
(
        DxfEntities *entities
                /*!< Pointer to the memory occupied by the DXF
                 * \c ENTITIES section. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (entities == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        dxf_3dface_free_list ((Dxf3dface *) entities->dface_list);
        dxf_3dsolid_free_list ((Dxf3dsolid *) entities->dsolid_list);
        dxf_acad_proxy_entity_free_list ((DxfAcadProxyEntity *) entities->acad_proxy_entity_list);
        dxf_arc_free_list ((DxfArc *) entities->arc_list);
        dxf_attdef_free_list ((DxfAttdef *) entities->attdef_list);
        dxf_attrib_free_list ((DxfAttrib *) entities->attrib_list);
        dxf_body_free_list ((DxfBody *) entities->body_list);
        dxf_circle_free_list ((DxfCircle *) entities->circle_list);
        dxf_dimension_free_list ((DxfDimension *) entities->dimension_list);
        dxf_ellipse_free_list ((DxfEllipse *) entities->ellipse_list);
        dxf_hatch_free_list ((DxfHatch *) entities->hatch_list);
        //dxf_helix_free_list ((DxfHelix *) entities->helix_list);
        dxf_image_free_list ((DxfImage *) entities->image_list);
        dxf_insert_free_list ((DxfInsert *) entities->insert_list);
        dxf_leader_free_list ((DxfLeader *) entities->leader_list);
        //dxf_light_free_list ((DxfLight *) entities->light_list);
        dxf_line_free_list ((DxfLine *) entities->line_list);
        dxf_lwpolyline_free_list ((DxfLWPolyline *) entities->lw_polyline_list);
        //dxf_light_free_list ((DxfLight *) entities->light_list);
        dxf_mline_free_list ((DxfMline *) entities->mline_list);
        //dxf_mleader_free_list ((DxfMLeader *) entities->mleader_list);
        //dxf_mleaderstyle_free_list ((DxfMLeaderStyle *) entities->mleaderstyle_list);
        dxf_mtext_free_list ((DxfMtext *) entities->mtext_list);
        dxf_oleframe_free_list ((DxfOleFrame *) entities->oleframe_list);
        dxf_ole2frame_free_list ((DxfOle2Frame *) entities->ole2frame_list);
        dxf_point_free_list ((DxfPoint *) entities->point_list);
        dxf_polyline_free_list ((DxfPolyline *) entities->polyline_list);
        dxf_ray_free_list ((DxfRay *) entities->ray_list);
        dxf_region_free_list ((DxfRegion *) entities->region_list);
        //dxf_section_free_list ((DxfSection *) entities->section_list);
        dxf_shape_free_list ((DxfShape *) entities->shape_list);
        dxf_solid_free_list ((DxfSolid *) entities->solid_list);
        //dxf_spline_free_list (DxfSpline *) entities->spline_list);
        //dxf_sun_free_list (DxfSun *) entities->sun_list);
        //dxf_surface_free_list (DxfSurface *) entities->surface_list);
        dxf_table_free_list ((DxfTable *) entities->table_list);
        dxf_text_free_list ((DxfText *) entities->text_list);
        dxf_tolerance_free_list ((DxfTolerance *) entities->tolerance_list);
        dxf_trace_free_list ((DxfTrace *) entities->trace_list);
        //dxf_underlay_free_list (DxfUnderlay *) entities->underlay_list);
        dxf_vertex_free_list ((DxfVertex *) entities->vertex_list);
        dxf_viewport_free_list ((DxfViewport *) entities->viewport_list);
        //dxf_wipeout_free_list (DxfWipeout *) entities->wipeout_list);
        //dxf_xline_free_list (DxfXLine *) entities->xline_list);
        free (entities);
        entities = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
