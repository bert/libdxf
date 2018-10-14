/*!
 * \file trace.h
 *
 * \author Copyright (C) 2008, 2012, 2014, 2015, 2016, 2017, 2018
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Definition of a DXF trace entity (\c TRACE).
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


#ifndef LIBDXF_SRC_TRACE_H
#define LIBDXF_SRC_TRACE_H


#include "global.h"
#include "point.h"
#include "binary_graphics_data.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief DXF definition of an AutoCAD trace entity.
 */
typedef struct
dxf_trace_struct
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
        /* Specific members for a DXF trace. */
        DxfPoint *p0;
                /*!< Base point.\n
                 * Group codes = 10, 20 and 30. */
        DxfPoint *p1;
                /*!< Alignment point.\n
                 * Group codes = 11, 21 and 31. */
        DxfPoint *p2;
                /*!< Alignment point.\n
                 * Group codes = 12, 22 and 32. */
        DxfPoint *p3;
                /*!< Alignment point.\n
                 * Group codes = 13, 23 and 33. */
        double extr_x0;
                /*!< X-value of the extrusion vector.\n
                 * Defaults to 0.0 if omitted in the DXF file.\n
                 * Group code = 210. */
        double extr_y0;
                /*!< Y-value of the extrusion vector.\n
                 * Defaults to 0.0 if omitted in the DXF file.\n
                 * Group code = 220. */
        double extr_z0;
                /*!< Z-value of the extrusion vector.\n
                 * Defaults to 1.0 if omitted in the DXF file.\n
                 * Group code = 230. */
        struct DxfTrace *next;
                /*!< pointer to the next DxfTrace.\n
                 * \c NULL in the last DxfTrace. */
} DxfTrace;


DxfTrace *dxf_trace_new ();
DxfTrace *dxf_trace_init (DxfTrace *trace);
DxfTrace *dxf_trace_read (DxfFile *fp, DxfTrace *trace);
int dxf_trace_write (DxfFile *fp, DxfTrace *trace);
int dxf_trace_free (DxfTrace *trace);
void dxf_trace_free_list (DxfTrace *traces);
int dxf_trace_get_id_code (DxfTrace *trace);
DxfTrace *dxf_trace_set_id_code (DxfTrace *trace, int id_code);
char *dxf_trace_get_linetype (DxfTrace *trace);
DxfTrace *dxf_trace_set_linetype (DxfTrace *trace, char *linetype);
char *dxf_trace_get_layer (DxfTrace *trace);
DxfTrace *dxf_trace_set_layer (DxfTrace *trace, char *layer);
double dxf_trace_get_elevation (DxfTrace *trace);
DxfTrace *dxf_trace_set_elevation (DxfTrace *trace, double elevation);
double dxf_trace_get_thickness (DxfTrace *trace);
DxfTrace *dxf_trace_set_thickness (DxfTrace *trace, double thickness);
double dxf_trace_get_linetype_scale (DxfTrace *trace);
DxfTrace *dxf_trace_set_linetype_scale (DxfTrace *trace, double linetype_scale);
int16_t dxf_trace_get_visibility (DxfTrace *trace);
DxfTrace *dxf_trace_set_visibility (DxfTrace *trace, int16_t visibility);
int dxf_trace_get_color (DxfTrace *trace);
DxfTrace *dxf_trace_set_color (DxfTrace *trace, int color);
int dxf_trace_get_paperspace (DxfTrace *trace);
DxfTrace *dxf_trace_set_paperspace (DxfTrace *trace, int paperspace);
int dxf_trace_get_graphics_data_size (DxfTrace *trace);
DxfTrace *dxf_trace_set_graphics_data_size (DxfTrace *trace, int graphics_data_size);
int16_t dxf_trace_get_shadow_mode (DxfTrace *trace);
DxfTrace *dxf_trace_set_shadow_mode (DxfTrace *trace, int16_t shadow_mode);
DxfBinaryGraphicsData *dxf_trace_get_binary_graphics_data (DxfTrace *trace);
DxfTrace *dxf_trace_set_binary_graphics_data (DxfTrace *trace, DxfBinaryGraphicsData *data);
char *dxf_trace_get_dictionary_owner_soft (DxfTrace *trace);
DxfTrace *dxf_trace_set_dictionary_owner_soft (DxfTrace *trace, char *dictionary_owner_soft);
char *dxf_trace_get_material (DxfTrace *trace);
DxfTrace *dxf_trace_set_material (DxfTrace *trace, char *material);
char *dxf_trace_get_dictionary_owner_hard (DxfTrace *trace);
DxfTrace *dxf_trace_set_dictionary_owner_hard (DxfTrace *trace, char *dictionary_owner_hard);
int16_t dxf_trace_get_lineweight (DxfTrace *trace);
DxfTrace *dxf_trace_set_lineweight (DxfTrace *trace, int16_t lineweight);
char *dxf_trace_get_plot_style_name (DxfTrace *trace);
DxfTrace *dxf_trace_set_plot_style_name (DxfTrace *trace, char *plot_style_name);
long dxf_trace_get_color_value (DxfTrace *trace);
DxfTrace *dxf_trace_set_color_value (DxfTrace *trace, long color_value);
char *dxf_trace_get_color_name (DxfTrace *trace);
DxfTrace *dxf_trace_set_color_name (DxfTrace *trace, char *color_name);
long dxf_trace_get_transparency (DxfTrace *trace);
DxfTrace *dxf_trace_set_transparency (DxfTrace *trace, long transparency);
DxfPoint *dxf_trace_get_p0 (DxfTrace *trace);
DxfTrace *dxf_trace_set_p0 (DxfTrace *trace, DxfPoint *p0);
double dxf_trace_get_x0 (DxfTrace *trace);
DxfTrace *dxf_trace_set_x0 (DxfTrace *trace, double x0);
double dxf_trace_get_y0 (DxfTrace *trace);
DxfTrace *dxf_trace_set_y0 (DxfTrace *trace, double y0);
double dxf_trace_get_z0 (DxfTrace *trace);
DxfTrace *dxf_trace_set_z0 (DxfTrace *trace, double z0);
DxfPoint *dxf_trace_get_p1 (DxfTrace *trace);
DxfTrace *dxf_trace_set_p1 (DxfTrace *trace, DxfPoint *p1);
double dxf_trace_get_x1 (DxfTrace *trace);
DxfTrace *dxf_trace_set_x1 (DxfTrace *trace, double x1);
double dxf_trace_get_y1 (DxfTrace *trace);
DxfTrace *dxf_trace_set_y1 (DxfTrace *trace, double y1);
double dxf_trace_get_z1 (DxfTrace *trace);
DxfTrace *dxf_trace_set_z1 (DxfTrace *trace, double z1);
DxfPoint *dxf_trace_get_p2 (DxfTrace *trace);
DxfTrace *dxf_trace_set_p2 (DxfTrace *trace, DxfPoint *p2);
double dxf_trace_get_x2 (DxfTrace *trace);
DxfTrace *dxf_trace_set_x2 (DxfTrace *trace, double x2);
double dxf_trace_get_y2 (DxfTrace *trace);
DxfTrace *dxf_trace_set_y2 (DxfTrace *trace, double y2);
double dxf_trace_get_z2 (DxfTrace *trace);
DxfTrace *dxf_trace_set_z2 (DxfTrace *trace, double z2);
DxfPoint *dxf_trace_get_p3 (DxfTrace *trace);
DxfTrace *dxf_trace_set_p3 (DxfTrace *trace, DxfPoint *p3);
double dxf_trace_get_x3 (DxfTrace *trace);
DxfTrace *dxf_trace_set_x3 (DxfTrace *trace, double x3);
double dxf_trace_get_y3 (DxfTrace *trace);
DxfTrace *dxf_trace_set_y3 (DxfTrace *trace, double y3);
double dxf_trace_get_z3 (DxfTrace *trace);
DxfTrace *dxf_trace_set_z3 (DxfTrace *trace, double z3);
DxfPoint *dxf_trace_get_extrusion_vector_as_point (DxfTrace *trace);
DxfTrace *dxf_trace_set_extrusion_vector_from_point (DxfTrace *trace, DxfPoint *point);
DxfTrace *dxf_trace_set_extrusion_vector (DxfTrace *trace, double extr_x0, double extr_y0, double extr_z0);
double dxf_trace_get_extr_x0 (DxfTrace *trace);
DxfTrace *dxf_trace_set_extr_x0 (DxfTrace *trace, double extr_x0);
double dxf_trace_get_extr_y0 (DxfTrace *trace);
DxfTrace *dxf_trace_set_extr_y0 (DxfTrace *trace, double extr_y0);
double dxf_trace_get_extr_z0 (DxfTrace *trace);
DxfTrace *dxf_trace_set_extr_z0 (DxfTrace *trace, double extr_z0);
DxfTrace *dxf_trace_get_next (DxfTrace *trace);
DxfTrace *dxf_trace_set_next (DxfTrace *trace, DxfTrace *next);
DxfTrace *dxf_trace_get_last (DxfTrace *trace);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_TRACE_H */


/* EOF */
