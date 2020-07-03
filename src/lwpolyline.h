/*!
 * \file lwpolyline.h
 *
 * \author Copyright (C) 2010, 2012, 2014, 2015, 2016, 2017, 2018, 2020
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF light weight polyline entity (\c LWPOLYLINE).
 *
 * \warning This entity requires AutoCAD version R14 or higher.
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
 * For more details see http://www.autodesk.com .
 * <hr>
 */


#ifndef LIBDXF_SRC_LWPOLYLINE_H
#define LIBDXF_SRC_LWPOLYLINE_H


#include "global.h"
#include "point.h"
#include "binary_data.h"
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
                /*!< Elevation of the lwpolyline in the local Z-direction.\n
                 * Defaults to 0.0 if omitted in the DXF file, or prior
                 * to DXF version R12, or DXF_FLATLAND equals 0 (default).\n
                 * Group code = 38.\n
                 * \deprecated As of version R11. */
        double thickness;
                /*!< Thickness of the lwpolyline in the local Z-direction.\n
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
        int32_t graphics_data_size;
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
        DxfBinaryData *binary_graphics_data;
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
        int32_t color_value;
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
        int32_t transparency;
                /*!< Transparency value.\n
                 * The group code cannot be used by custom entities for
                 * their own data because the group code is reserved for
                 * AcDbEntity, class-level color data and AcDbEntity,
                 * class-level transparency data.\n
                 * Group code = 440.\n
                 * \since Introduced in version R2004. */
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


DxfLWPolyline *dxf_lwpolyline_new ();
DxfLWPolyline *dxf_lwpolyline_init (DxfLWPolyline *lwpolyline);
DxfLWPolyline *dxf_lwpolyline_read (DxfFile *fp, DxfLWPolyline *lwpolyline);
int dxf_lwpolyline_write (DxfFile *fp, DxfLWPolyline *lwpolyline);
int dxf_lwpolyline_free (DxfLWPolyline *lwpolyline);
void dxf_lwpolyline_free_list (DxfLWPolyline *lwpolylines);
int dxf_lwpolyline_get_id_code (DxfLWPolyline *lwpolyline);
DxfLWPolyline *dxf_lwpolyline_set_id_code (DxfLWPolyline *lwpolyline, int id_code);
char *dxf_lwpolyline_get_linetype (DxfLWPolyline *lwpolyline);
DxfLWPolyline *dxf_lwpolyline_set_linetype (DxfLWPolyline *lwpolyline, char *linetype);
char *dxf_lwpolyline_get_layer (DxfLWPolyline *lwpolyline);
DxfLWPolyline *dxf_lwpolyline_set_layer (DxfLWPolyline *lwpolyline, char *layer);
double dxf_lwpolyline_get_elevation (DxfLWPolyline *lwpolyline);
DxfLWPolyline *dxf_lwpolyline_set_elevation (DxfLWPolyline *lwpolyline, double elevation);
double dxf_lwpolyline_get_thickness (DxfLWPolyline *lwpolyline);
DxfLWPolyline *dxf_lwpolyline_set_thickness (DxfLWPolyline *lwpolyline, double thickness);
double dxf_lwpolyline_get_linetype_scale (DxfLWPolyline *lwpolyline);
DxfLWPolyline *dxf_lwpolyline_set_linetype_scale (DxfLWPolyline *lwpolyline, double linetype_scale);
int16_t dxf_lwpolyline_get_visibility (DxfLWPolyline *lwpolyline);
DxfLWPolyline *dxf_lwpolyline_set_visibility (DxfLWPolyline *lwpolyline, int16_t visibility);
int dxf_lwpolyline_get_color (DxfLWPolyline *lwpolyline);
DxfLWPolyline *dxf_lwpolyline_set_color (DxfLWPolyline *lwpolyline, int color);
int dxf_lwpolyline_get_paperspace (DxfLWPolyline *lwpolyline);
DxfLWPolyline *dxf_lwpolyline_set_paperspace (DxfLWPolyline *lwpolyline, int paperspace);
int32_t dxf_lwpolyline_get_graphics_data_size (DxfLWPolyline *lwpolyline);
DxfLWPolyline *dxf_lwpolyline_set_graphics_data_size (DxfLWPolyline *lwpolyline, int32_t graphics_data_size);
int16_t dxf_lwpolyline_get_shadow_mode (DxfLWPolyline *lwpolyline);
DxfLWPolyline *dxf_lwpolyline_set_shadow_mode (DxfLWPolyline *lwpolyline, int16_t shadow_mode);
DxfBinaryData *dxf_lwpolyline_get_binary_graphics_data (DxfLWPolyline *lwpolyline);
DxfLWPolyline *dxf_lwpolyline_set_binary_graphics_data (DxfLWPolyline *lwpolyline, DxfBinaryData *data);
char *dxf_lwpolyline_get_dictionary_owner_soft (DxfLWPolyline *lwpolyline);
DxfLWPolyline *dxf_lwpolyline_set_dictionary_owner_soft (DxfLWPolyline *lwpolyline, char *dictionary_owner_soft);
char *dxf_lwpolyline_get_material (DxfLWPolyline *lwpolyline);
DxfLWPolyline *dxf_lwpolyline_set_material (DxfLWPolyline *lwpolyline, char *material);
char *dxf_lwpolyline_get_dictionary_owner_hard (DxfLWPolyline *lwpolyline);
DxfLWPolyline *dxf_lwpolyline_set_dictionary_owner_hard (DxfLWPolyline *lwpolyline, char *dictionary_owner_hard);
int16_t dxf_lwpolyline_get_lineweight (DxfLWPolyline *lwpolyline);
DxfLWPolyline *dxf_lwpolyline_set_lineweight (DxfLWPolyline *lwpolyline, int16_t lineweight);
char *dxf_lwpolyline_get_plot_style_name (DxfLWPolyline *lwpolyline);
DxfLWPolyline *dxf_lwpolyline_set_plot_style_name (DxfLWPolyline *lwpolyline, char *plot_style_name);
int32_t dxf_lwpolyline_get_color_value (DxfLWPolyline *lwpolyline);
DxfLWPolyline *dxf_lwpolyline_set_color_value (DxfLWPolyline *lwpolyline, int32_t color_value);
char *dxf_lwpolyline_get_color_name (DxfLWPolyline *lwpolyline);
DxfLWPolyline *dxf_lwpolyline_set_color_name (DxfLWPolyline *lwpolyline, char *color_name);
int32_t dxf_lwpolyline_get_transparency (DxfLWPolyline *lwpolyline);
DxfLWPolyline *dxf_lwpolyline_set_transparency (DxfLWPolyline *lwpolyline, int32_t transparency);
double dxf_lwpolyline_get_constant_width (DxfLWPolyline *lwpolyline);
DxfLWPolyline *dxf_lwpolyline_set_constant_width (DxfLWPolyline *lwpolyline, double constant_width);
int dxf_lwpolyline_get_flag (DxfLWPolyline *lwpolyline);
DxfLWPolyline *dxf_lwpolyline_set_flag (DxfLWPolyline *lwpolyline, int flag);
int dxf_lwpolyline_get_number_vertices (DxfLWPolyline *lwpolyline);
DxfLWPolyline *dxf_lwpolyline_set_number_vertices (DxfLWPolyline *lwpolyline, int number_vertices);
double dxf_lwpolyline_get_extr_x0 (DxfLWPolyline *lwpolyline);
DxfLWPolyline *dxf_lwpolyline_set_extr_x0 (DxfLWPolyline *lwpolyline, double extr_x0);
double dxf_lwpolyline_get_extr_y0 (DxfLWPolyline *lwpolyline);
DxfLWPolyline *dxf_lwpolyline_set_extr_y0 (DxfLWPolyline *lwpolyline, double extr_y0);
double dxf_lwpolyline_get_extr_z0 (DxfLWPolyline *lwpolyline);
DxfLWPolyline *dxf_lwpolyline_set_extr_z0 (DxfLWPolyline *lwpolyline, double extr_z0);
DxfVertex *dxf_lwpolyline_get_vertices (DxfLWPolyline *lwpolyline);
DxfLWPolyline *dxf_lwpolyline_set_vertices (DxfLWPolyline *lwpolyline, DxfVertex *vertices);
DxfLWPolyline *dxf_lwpolyline_get_next (DxfLWPolyline *lwpolyline);
DxfLWPolyline *dxf_lwpolyline_set_next (DxfLWPolyline *lwpolyline, DxfLWPolyline *next);
DxfLWPolyline *dxf_lwpolyline_get_last (DxfLWPolyline *lwpolyline);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_LWPOLYLINE_H */


/* EOF */
