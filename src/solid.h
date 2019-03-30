/*!
 * \file solid.h
 *
 * \author Copyright (C) 2008, 2010, 2012, 2014, 2015, 2016, 2017, 2018
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF solid entity (\c SOLID).
 *
 * A DXF \c SOLID entity is a filled shape made with up to four point
 * (X, Y, Z)-coordinates.\n
 * A filled triangle can be formed by duplicating the third coordinate at the
 * fourth coordinate position.\n
 * A diabolo shaped solid can be formed by "twisting" the \c SOLID form in it's
 * plane, by "swapping" the third and fourth coordinate set.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
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
 * For more details see http://www.autodesk.com .
 * <hr>
 */


#ifndef LIBDXF_SRC_SOLID_H
#define LIBDXF_SRC_SOLID_H


#include "global.h"
#include "point.h"
#include "binary_graphics_data.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief DXF definition of an AutoCAD solid entity.
 *
 * If only three points are entered (forming a triangular \c SOLID), the
 * third and fourth points will coincide.
 */
typedef struct
dxf_solid_struct
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
                /*!< Elevation of the entity in the local Z-direction.\n
                 * Defaults to 0.0 if omitted in the DXF file, or prior
                 * to DXF version R12, or DXF_FLATLAND equals 0 (default).\n
                 * Group code = 38.\n
                 * \deprecated As of version R11. */
        double thickness;
                /*!< Thickness of the entity in the local Z-direction.\n
                 * Defaults to 0.0 if ommitted in the DXF file.\n
                 * Group code = 39. */
        double linetype_scale;
                /*!< Linetype scale (optional).\n
                 * Group code = 48.\n
                 * \since Introduced in version R13. */
        int16_t visibility;
                /*!< Object visibility (optional):\n
                 * <ol>
                 * <li value = "0"> Visible</li>
                 * <li value = "1"> Invisible</li>
                 * </ol>
                 * Group code = 60.\n
                 * \since Introduced in version R13. */
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
                 * Group code = 67.\n
                 * \since Introduced in version R13. */
        int graphics_data_size;
                /*!< Number of bytes in the proxy entity graphics
                 * represented in the sub-sequent 310 groups, which are
                 * binary chunk records (optional).\n
                 * Group code = 92.\n
                 * \since Introduced in version R2000.\n
                 * \warning On some 64 bit workstations output is
                 * generated with group code "160", thus omitting group
                 * code "92". */
        int16_t shadow_mode;
                /*!< Shadow mode:\n
                 * <ol>
                 * <li value = "0"> Casts and receives shadows.</li>
                 * <li value = "1"> Casts shadows.</li>
                 * <li value = "2"> Receives shadows.</li>
                 * <li value = "3"> Ignores shadows.</li>
                 * </ol>\n
                 * Group code = 284.\n
                 * \since Introduced in version R2009. */
        DxfBinaryGraphicsData *binary_graphics_data;
                /*!< Proxy entity graphics data.\n
                 * Multiple lines of 256 characters maximum per line
                 * (optional).\n
                 * Group code = 310.\n
                 * \since Introduced in version R2000. */
        char *dictionary_owner_soft;
                /*!< Soft-pointer ID/handle to owner dictionary (optional).\n
                 * Group code = 330.\n
                 * \since Introduced in version R14. */
        char *object_owner_soft;
                /*!< Soft-pointer ID/handle  to owner BLOCK_RECORD object.\n
                 * Group code = 330.\n
                 * \since Introduced in version R2000. */
        char *material;
                /*!< Hard-pointer ID/handle to material object (present if
                 * not BYLAYER).\n
                 * Group code = 347.\n
                 * \since Introduced in version R2008. */
        char *dictionary_owner_hard;
                /*!< Hard owner ID/handle to owner dictionary (optional).\n
                 * Group code = 360.\n
                 * \since Introduced in version R14. */
        int16_t lineweight;
                /*!< Lineweight enum value.\n
                 * Stored and moved around as a 16-bit integer.\n
                 * Group code = 370.\n
                 * \since Introduced in version R2002. */
        char *plot_style_name;
                /*!< Hard pointer ID / handle of PlotStyleName object.\n
                 * Group code = 390.\n
                 * \since Introduced in version R2009. */
        long color_value;
                /*!< A 24-bit color value that should be dealt with in
                 * terms of bytes with values of 0 to 255.\n
                 * The lowest byte is the blue value, the middle byte is
                 * the green value, and the third byte is the red value.\n
                 * The top byte is always 0.\n
                 * The group code cannot be used by custom entities for
                 * their own data because the group code is reserved for
                 * AcDbEntity, class-level color data and AcDbEntity,
                 * class-level transparency data.\n
                 * Group code = 420.\n
                 * \since Introduced in version R2004. */
        char *color_name;
                /*!< Color name.\n
                 * The group code cannot be used by custom entities for
                 * their own data because the group code is reserved for
                 * AcDbEntity, class-level color data and AcDbEntity,
                 * class-level transparency data.\n
                 * Group code = 430.\n
                 * \since Introduced in version R2004. */
        long transparency;
                /*!< Transparency value.\n
                 * The group code cannot be used by custom entities for
                 * their own data because the group code is reserved for
                 * AcDbEntity, class-level color data and AcDbEntity,
                 * class-level transparency data.\n
                 * Group code = 440.\n
                 * \since Introduced in version R2004. */
        /* Specific members for a DXF solid. */
        DxfPoint *p0;
                /*!< Base point.\n
                 * Group codes = 10, 20 and 30.*/
        double x0;
                /*!< group code = 10\n
                 * base point. */
        double y0;
                /*!< group code = 20\n
                 * base point. */
        double z0;
                /*!< group code = 30\n
                 * base point. */
        DxfPoint *p1;
                /*!< Alignment point.\n
                 * Group codes = 11, 21 and 31.*/
        double x1;
                /*!< group code = 11\n
                 * alignment point. */
        double y1;
                /*!< group code = 21\n
                 * alignment point. */
        double z1;
                /*!< group code = 31\n
                 * alignment point. */
        DxfPoint *p2;
                /*!< Alignment point.\n
                 * Group codes = 12, 22 and 32.*/
        double x2;
                /*!< group code = 12\n
                 * alignment point. */
        double y2;
                /*!< group code = 22\n
                 * alignment point. */
        double z2;
                /*!< group code = 32\n
                 * alignment point. */
        DxfPoint *p3;
                /*!< Alignment point.\n
                 * Group codes = 13, 23 and 33.*/
        double x3;
                /*!< group code = 13\n
                 * alignment point. */
        double y3;
                /*!< group code = 23\n
                 * alignment point. */
        double z3;
                /*!< group code = 33\n
                 * alignment point. */
        double extr_x0;
                /*!< X-value of the extrusion vector.\n
                 * Defaults to 0.0 if ommitted in the DXF file.\n
                 * Group code = 210. */
        double extr_y0;
                /*!< Y-value of the extrusion vector.\n
                 * Defaults to 0.0 if ommitted in the DXF file.\n
                 * Group code = 220. */
        double extr_z0;
                /*!< Z-value of the extrusion vector.\n
                 * Defaults to 1.0 if ommitted in the DXF file.\n
                 * Group code = 230. */
        struct DxfSolid *next;
                /*!< pointer to the next DxfSolid.\n
                 * \c NULL in the last DxfSolid. */

} DxfSolid;


DxfSolid *dxf_solid_new ();
DxfSolid *dxf_solid_init (DxfSolid *solid);
DxfSolid *dxf_solid_read (DxfFile *fp, DxfSolid *solid);
int dxf_solid_write (DxfFile *fp, DxfSolid *solid);
int dxf_solid_free (DxfSolid *solid);
void dxf_solid_free_list (DxfSolid *solids);
int dxf_solid_get_id_code (DxfSolid *solid);
DxfSolid *dxf_solid_set_id_code (DxfSolid *solid, int id_code);
char *dxf_solid_get_linetype (DxfSolid *solid);
DxfSolid *dxf_solid_set_linetype (DxfSolid *solid, char *linetype);
char *dxf_solid_get_layer (DxfSolid *solid);
DxfSolid *dxf_solid_set_layer (DxfSolid *solid, char *layer);
double dxf_solid_get_elevation (DxfSolid *solid);
DxfSolid *dxf_solid_set_elevation (DxfSolid *solid, double elevation);
double dxf_solid_get_thickness (DxfSolid *solid);
DxfSolid *dxf_solid_set_thickness (DxfSolid *solid, double thickness);
double dxf_solid_get_linetype_scale (DxfSolid *solid);
DxfSolid *dxf_solid_set_linetype_scale (DxfSolid *solid, double linetype_scale);
int16_t dxf_solid_get_visibility (DxfSolid *solid);
DxfSolid *dxf_solid_set_visibility (DxfSolid *solid, int16_t visibility);
int dxf_solid_get_color (DxfSolid *solid);
DxfSolid *dxf_solid_set_color (DxfSolid *solid, int color);
int dxf_solid_get_paperspace (DxfSolid *solid);
DxfSolid *dxf_solid_set_paperspace (DxfSolid *solid, int paperspace);
int dxf_solid_get_graphics_data_size (DxfSolid *solid);
DxfSolid *dxf_solid_set_graphics_data_size (DxfSolid *solid, int graphics_data_size);
int16_t dxf_solid_get_shadow_mode (DxfSolid *solid);
DxfSolid *dxf_solid_set_shadow_mode (DxfSolid *solid, int16_t shadow_mode);
DxfBinaryGraphicsData *dxf_solid_get_binary_graphics_data (DxfSolid *solid);
DxfSolid *dxf_solid_set_binary_graphics_data (DxfSolid *solid, DxfBinaryGraphicsData *data);
char *dxf_solid_get_dictionary_owner_soft (DxfSolid *solid);
DxfSolid *dxf_solid_set_dictionary_owner_soft (DxfSolid *solid, char *dictionary_owner_soft);
char *dxf_solid_get_object_owner_soft (DxfSolid *solid);
DxfSolid *dxf_solid_set_object_owner_soft (DxfSolid *solid, char *object_owner_soft);
char *dxf_solid_get_material (DxfSolid *solid);
DxfSolid *dxf_solid_set_material (DxfSolid *solid, char *material);
char *dxf_solid_get_dictionary_owner_hard (DxfSolid *solid);
DxfSolid *dxf_solid_set_dictionary_owner_hard (DxfSolid *solid, char *dictionary_owner_hard);
int16_t dxf_solid_get_lineweight (DxfSolid *solid);
DxfSolid *dxf_solid_set_lineweight (DxfSolid *solid, int16_t lineweight);
char *dxf_solid_get_plot_style_name (DxfSolid *solid);
DxfSolid *dxf_solid_set_plot_style_name (DxfSolid *solid, char *plot_style_name);
long dxf_solid_get_color_value (DxfSolid *solid);
DxfSolid *dxf_solid_set_color_value (DxfSolid *solid, long color_value);
char *dxf_solid_get_color_name (DxfSolid *solid);
DxfSolid *dxf_solid_set_color_name (DxfSolid *solid, char *color_name);
long dxf_solid_get_transparency (DxfSolid *solid);
DxfSolid *dxf_solid_set_transparency (DxfSolid *solid, long transparency);
DxfPoint *dxf_solid_get_p0 (DxfSolid *solid);
DxfSolid *dxf_solid_set_p0 (DxfSolid *solid, DxfPoint *p0);
double dxf_solid_get_x0 (DxfSolid *solid);
DxfSolid *dxf_solid_set_x0 (DxfSolid *solid, double x0);
double dxf_solid_get_y0 (DxfSolid *solid);
DxfSolid *dxf_solid_set_y0 (DxfSolid *solid, double y0);
double dxf_solid_get_z0 (DxfSolid *solid);
DxfSolid *dxf_solid_set_z0 (DxfSolid *solid, double z0);
DxfPoint *dxf_solid_get_p1 (DxfSolid *solid);
DxfSolid *dxf_solid_set_p1 (DxfSolid *solid, DxfPoint *p1);
double dxf_solid_get_x1 (DxfSolid *solid);
DxfSolid *dxf_solid_set_x1 (DxfSolid *solid, double x1);
double dxf_solid_get_y1 (DxfSolid *solid);
DxfSolid *dxf_solid_set_y1 (DxfSolid *solid, double y1);
double dxf_solid_get_z1 (DxfSolid *solid);
DxfSolid *dxf_solid_set_z1 (DxfSolid *solid, double z1);
DxfPoint *dxf_solid_get_p2 (DxfSolid *solid);
DxfSolid *dxf_solid_set_p2 (DxfSolid *solid, DxfPoint *p2);
double dxf_solid_get_x2 (DxfSolid *solid);
DxfSolid *dxf_solid_set_x2 (DxfSolid *solid, double x2);
double dxf_solid_get_y2 (DxfSolid *solid);
DxfSolid *dxf_solid_set_y2 (DxfSolid *solid, double y2);
double dxf_solid_get_z2 (DxfSolid *solid);
DxfSolid *dxf_solid_set_z2 (DxfSolid *solid, double z2);
DxfPoint *dxf_solid_get_p3 (DxfSolid *solid);
DxfSolid *dxf_solid_set_p3 (DxfSolid *solid, DxfPoint *p3);
double dxf_solid_get_x3 (DxfSolid *solid);
DxfSolid *dxf_solid_set_x3 (DxfSolid *solid, double x3);
double dxf_solid_get_y3 (DxfSolid *solid);
DxfSolid *dxf_solid_set_y3 (DxfSolid *solid, double y3);
double dxf_solid_get_z3 (DxfSolid *solid);
DxfSolid *dxf_solid_set_z3 (DxfSolid *solid, double z3);
DxfPoint *dxf_solid_get_extrusion_vector_as_point (DxfSolid *solid);
DxfSolid *dxf_solid_set_extrusion_vector_from_point (DxfSolid *solid, DxfPoint *point);
DxfSolid *dxf_solid_set_extrusion_vector (DxfSolid *solid, double extr_x0, double extr_y0, double extr_z0);
double dxf_solid_get_extr_x0 (DxfSolid *solid);
DxfSolid *dxf_solid_set_extr_x0 (DxfSolid *solid, double extr_x0);
double dxf_solid_get_extr_y0 (DxfSolid *solid);
DxfSolid *dxf_solid_set_extr_y0 (DxfSolid *solid, double extr_y0);
double dxf_solid_get_extr_z0 (DxfSolid *solid);
DxfSolid *dxf_solid_set_extr_z0 (DxfSolid *solid, double extr_z0);
DxfSolid *dxf_solid_get_next (DxfSolid *solid);
DxfSolid *dxf_solid_set_next (DxfSolid *solid, DxfSolid *next);
DxfSolid *dxf_solid_get_last (DxfSolid *solid);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_SOLID_H */


/* EOF */
