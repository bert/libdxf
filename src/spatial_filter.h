/*!
 * \file spatial_filter.h
 *
 * \author Copyright (C) 2015, 2016, 2017, 2018
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF spatial_filter object (\c SPATIAL_FILTER).
 *
 * \since The \c SPATIAL_FILTER object was introduced in DXF R14.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
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


#ifndef LIBDXF_SRC_SPATIAL_FILTER_H
#define LIBDXF_SRC_SPATIAL_FILTER_H


#include "global.h"
#include "point.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief DXF definition of an AutoCAD spatial_filter object (\c SPATIAL_FILTER).
 */
typedef struct
dxf_spatial_filter_struct
{
        /* Members common for all DXF objects. */
        int id_code;
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file.\n
                 * Group code = 5. */
        char *dictionary_owner_soft;
                /*!< Soft-pointer ID/handle to owner dictionary (SPATIAL).\n
                 * Group code = 330. */
        char *dictionary_owner_hard;
                /*!< Hard owner ID/handle to owner dictionary (optional).\n
                 * Group code = 360. */
        /* Specific members for a DXF spatial_filter. */
        DxfPoint *p0;
                /*!< The clip boundary definition point (in OCS) (always
                 * 2 or more) based on an xref scale of 1.\n
                 * Group codes = 10 and 20. */
        double x0[DXF_MAX_PARAM];
                /*!< X-value of the clip boundary definition point (in
                 * OCS) (always 2 or more) based on an xref scale of 1.\n
                 * Group code = 10. */
        double y0[DXF_MAX_PARAM];
                /*!< Y-value of the clip boundary definition point (in
                 * OCS) (always 2 or more) based on an xref scale of 1.\n
                 * Group code = 20. */
        DxfPoint *p1;
                /*!< The origin used to define the local coordinate
                 * system of the clip boundary.\n
                 * Group code = 11, 21 and 31. */
        double x1;
                /*!< X-value of the origin used to define the local
                 * coordinate system of the clip boundary.\n
                 * Group code = 11. */
        double y1;
                /*!< Y-value of the origin used to define the local
                 * coordinate system of the clip boundary.\n
                 * Group code = 21. */
        double z1;
                /*!< Z-value of the origin used to define the local
                 * coordinate system of the clip boundary.\n
                 * Group code = 31. */
        double inverse_block_transformation[12];
                /*!< 4x3 transformation matrix written out in column
                 * major order.\n
                 * This matrix is the inverse of the original block
                 * reference (insert entity) transformation.\n
                 * The original block reference transformation is the
                 * one that is applied to all entities in the block when
                 * the block reference is regenerated. (always 12
                 * entries).\n
                 * Group code = 40. */
        double block_transformation[12];
                /*!< 4x3 transformation matrix written out in column
                 * major order that transforms points into the
                 * coordinate system of the clip boundary (12 entries).\n
                 * Group code = 40. */
        double front_clipping_plane_distance;
                /*!< Front clipping plane distance (if code 72 = 1).\n
                 * Group code = 40. */
        double back_clipping_plane_distance;
                /*!< Front clipping plane distance (if code 73 = 1).\n
                 * Group code = 41. */
        int number_of_points;
                /*!< Number of points on the clip boundary.\n
                 * 2 = Rectangular clip boundary (lower-left and
                 * upper-right).\n
                 * Greater than 2 = Polyline clip boundary.\n
                 * Group code = 70. */
        int clip_boundary_display_flag;
                /*!< Clip boundary display enabled flag.\n
                 * <ol>
                 * <li value = "0"> disabled.</li>
                 * <li value = "1"> enabled.</li>
                 * </ol>
                 * Group code = 71. */
        int front_clipping_plane_flag;
                /*!< Front clipping plane flag.\n
                 * <ol>
                 * <li value = "0"> no.</li>
                 * <li value = "1"> yes.</li>
                 * </ol>
                 * Group code = 72. */
        int back_clipping_plane_flag;
                /*!< Back clipping plane flag.\n
                 * <ol>
                 * <li value = "0"> no.</li>
                 * <li value = "1"> yes.</li>
                 * </ol>
                 * Group code = 73. */
        double extr_x0;
                /*!< X-value of the normal to the plane containing the
                 * clip boundary.\n
                 * Group code = 210. */
        double extr_y0;
                /*!< Y-value of the normal to the plane containing the
                 * clip boundary.\n
                 * Group code = 220. */
        double extr_z0;
                /*!< Z-value of the normal to the plane containing the
                 * clip boundary.\n
                 * Group code = 230. */
        struct DxfSpatialFilter *next;
                /*!< Pointer to the next DxfSpatialFilter.\n
                 * \c NULL in the last DxfSpatialFilter. */
} DxfSpatialFilter;


DxfSpatialFilter *dxf_spatial_filter_new ();
DxfSpatialFilter *dxf_spatial_filter_init (DxfSpatialFilter *spatial_filter);
DxfSpatialFilter *dxf_spatial_filter_read (DxfFile *fp, DxfSpatialFilter *spatial_filter);
int dxf_spatial_filter_write (DxfFile *fp, DxfSpatialFilter *spatial_filter);
int dxf_spatial_filter_free (DxfSpatialFilter *spatial_filter);
void dxf_spatial_filter_free_list (DxfSpatialFilter *spatial_filters);
int dxf_spatial_filter_get_id_code (DxfSpatialFilter *spatial_filter);
DxfSpatialFilter *dxf_spatial_filter_set_id_code (DxfSpatialFilter *spatial_filter, int id_code);
char *dxf_spatial_filter_get_dictionary_owner_soft (DxfSpatialFilter *spatial_filter);
DxfSpatialFilter *dxf_spatial_filter_set_dictionary_owner_soft (DxfSpatialFilter *spatial_filter, char *dictionary_owner_soft);
char *dxf_spatial_filter_get_dictionary_owner_hard (DxfSpatialFilter *spatial_filter);
DxfSpatialFilter *dxf_spatial_filter_set_dictionary_owner_hard (DxfSpatialFilter *spatial_filter, char *dictionary_owner_hard);
DxfPoint *dxf_spatial_filter_get_p0 (DxfSpatialFilter *spatial_filter);
DxfSpatialFilter *dxf_spatial_filter_set_p0 (DxfSpatialFilter *spatial_filter, DxfPoint *p0);
double dxf_spatial_filter_get_x0 (DxfSpatialFilter *spatial_filter);
DxfSpatialFilter *dxf_spatial_filter_set_x0 (DxfSpatialFilter *spatial_filter, double x0);
double dxf_spatial_filter_get_y0 (DxfSpatialFilter *spatial_filter);
DxfSpatialFilter *dxf_spatial_filter_set_y0 (DxfSpatialFilter *spatial_filter, double y0);
DxfPoint *dxf_spatial_filter_get_p0_next (DxfPoint *p0);
DxfPoint *dxf_spatial_filter_set_p0_next (DxfPoint *p0, DxfPoint *next);
DxfPoint *dxf_spatial_filter_get_p1 (DxfSpatialFilter *spatial_filter);
DxfSpatialFilter *dxf_spatial_filter_set_p1 (DxfSpatialFilter *spatial_filter, DxfPoint *p1);
double dxf_spatial_filter_get_x1 (DxfSpatialFilter *spatial_filter);
DxfSpatialFilter *dxf_spatial_filter_set_x1 (DxfSpatialFilter *spatial_filter, double x1);
double dxf_spatial_filter_get_y1 (DxfSpatialFilter *spatial_filter);
DxfSpatialFilter *dxf_spatial_filter_set_y1 (DxfSpatialFilter *spatial_filter, double y1);
double dxf_spatial_filter_get_z1 (DxfSpatialFilter *spatial_filter);
DxfSpatialFilter *dxf_spatial_filter_set_z1 (DxfSpatialFilter *spatial_filter, double z1);
double dxf_spatial_filter_get_front_clipping_plane_distance (DxfSpatialFilter *spatial_filter);
DxfSpatialFilter *dxf_spatial_filter_set_front_clipping_plane_distance (DxfSpatialFilter *spatial_filter, double front_clipping_plane_distance);
double dxf_spatial_filter_get_back_clipping_plane_distance (DxfSpatialFilter *spatial_filter);
DxfSpatialFilter *dxf_spatial_filter_set_back_clipping_plane_distance (DxfSpatialFilter *spatial_filter, double back_clipping_plane_distance);
int dxf_spatial_filter_get_number_of_points (DxfSpatialFilter *spatial_filter);
DxfSpatialFilter *dxf_spatial_filter_set_number_of_points (DxfSpatialFilter *spatial_filter, int number_of_points);
int dxf_spatial_filter_get_clip_boundary_display_flag (DxfSpatialFilter *spatial_filter);
DxfSpatialFilter *dxf_spatial_filter_set_clip_boundary_display_flag (DxfSpatialFilter *spatial_filter, int clip_boundary_display_flag);
int dxf_spatial_filter_get_front_clipping_plane_flag (DxfSpatialFilter *spatial_filter);
DxfSpatialFilter *dxf_spatial_filter_set_front_clipping_plane_flag (DxfSpatialFilter *spatial_filter, int front_clipping_plane_flag);
int dxf_spatial_filter_get_back_clipping_plane_flag (DxfSpatialFilter *spatial_filter);
DxfSpatialFilter *dxf_spatial_filter_set_back_clipping_plane_flag (DxfSpatialFilter *spatial_filter, int back_clipping_plane_flag);
DxfPoint *dxf_spatial_filter_get_extrusion_vector_as_point (DxfSpatialFilter *spatial_filter);
double dxf_spatial_filter_get_extr_x0 (DxfSpatialFilter *spatial_filter);
DxfSpatialFilter *dxf_spatial_filter_set_extr_x0 (DxfSpatialFilter *spatial_filter, double extr_x0);
double dxf_spatial_filter_get_extr_y0 (DxfSpatialFilter *spatial_filter);
DxfSpatialFilter *dxf_spatial_filter_set_extr_y0 (DxfSpatialFilter *spatial_filter, double extr_y0);
double dxf_spatial_filter_get_extr_z0 (DxfSpatialFilter *spatial_filter);
DxfSpatialFilter *dxf_spatial_filter_set_extr_z0 (DxfSpatialFilter *spatial_filter, double extr_z0);
DxfSpatialFilter *dxf_spatial_filter_get_next (DxfSpatialFilter *spatial_filter);
DxfSpatialFilter *dxf_spatial_filter_set_next (DxfSpatialFilter *spatial_filter, DxfSpatialFilter *next);
DxfSpatialFilter *dxf_spatial_filter_get_last (DxfSpatialFilter *spatial_filter);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_SPATIAL_FILTER_H */


/* EOF */
