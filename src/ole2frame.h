/*!
 * \file ole2frame.h
 *
 * \author Copyright (C) 2015, 2016, 2017, 2018
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF ole2frame entity (\c OLE2FRAME).
 *
 * \since The \c OLE2FRAME entity was introduced in DXF R14.
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


#ifndef LIBDXF_SRC_OLE2FRAME_H
#define LIBDXF_SRC_OLE2FRAME_H


#include "global.h"
#include "util.h"
#include "point.h"
#include "binary_graphics_data.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief DXF definition of an AutoCAD ole2frame entity (\c OLE2FRAME).
 */
typedef struct
dxf_ole2frame_struct
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
                 * <li value = "0"> Visible.</li>
                 * <li value = "1"> Invisible.</li>
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
                 * Group code = 330. */
        char *material;
                /*!< Hard-pointer ID/handle to material object (present if
                 * not BYLAYER).\n
                 * Group code = 347.\n
                 * \since Introduced in version R2008. */
        char *dictionary_owner_hard;
                /*!< Hard owner ID/handle to owner dictionary (optional).\n
                 * Group code = 360. */
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
        /* Specific members for a DXF ole2frame. */
        char *end_of_data;
                /*!< End of Ole data (the string "OLE").\n
                 * Group code = 1.  */
        char *length_of_binary_data;
                /*!< Length of binary data.\n
                 * Group code = 3.  */
        DxfPoint *p0;
                /*!< Insertion point.\n
                 * Group codes = 10, 20 and 30.*/
        DxfPoint *p1;
                /*!< Direction vector.\n
                 * Group codes = 11, 21 and 31.*/
        int ole_version_number ;
                /*!<  OLE version number.\n
                 * Group code = 70. */
        int ole_object_type;
                /*!< OLE object type, 1 = link, 2 = embedded, 3 = static.\n
                 * Group code = 71.*/
        int tilemode_descriptor;
                /*!< Tile mode descriptor:\n
                 * <ol>
                 * <li value = "0"> Object is in a tiled model space
                 * viewport.</li>
                 * <li value = "1"> Object is in a non-tiled viewport
                 * (paper space or  floating model space).</li>
                 * </ol>
                 * Group code = 72.*/
        long length;
                /*!< group code = 90\n
                 * Length of binary data.\n */
        DxfChar *binary_data;
                /*!< group code = 310\n
                 * Binary data (multiple lines).*/
        struct DxfOle2Frame *next;
                /*!< pointer to the next DxfOle2Frame.\n
                 * \c NULL in the last DxfOle2Frame. */
} DxfOle2Frame;


DxfOle2Frame *dxf_ole2frame_new ();
DxfOle2Frame *dxf_ole2frame_init (DxfOle2Frame *ole2frame);
DxfOle2Frame *dxf_ole2frame_read (DxfFile *fp, DxfOle2Frame *ole2frame);
int dxf_ole2frame_write (DxfFile *fp, DxfOle2Frame *ole2frame);
int dxf_ole2frame_free (DxfOle2Frame *ole2frame);
void dxf_ole2frame_free_list (DxfOle2Frame *ole2frames);
int dxf_ole2frame_get_id_code (DxfOle2Frame *ole2frame);
DxfOle2Frame *dxf_ole2frame_set_id_code (DxfOle2Frame *ole2frame, int id_code);
char *dxf_ole2frame_get_linetype (DxfOle2Frame *ole2frame);
DxfOle2Frame *dxf_ole2frame_set_linetype (DxfOle2Frame *ole2frame, char *linetype);
char *dxf_ole2frame_get_layer (DxfOle2Frame *ole2frame);
DxfOle2Frame *dxf_ole2frame_set_layer (DxfOle2Frame *ole2frame, char *layer);
double dxf_ole2frame_get_elevation (DxfOle2Frame *ole2frame);
DxfOle2Frame *dxf_ole2frame_set_elevation (DxfOle2Frame *ole2frame, double elevation);
double dxf_ole2frame_get_thickness (DxfOle2Frame *ole2frame);
DxfOle2Frame *dxf_ole2frame_set_thickness (DxfOle2Frame *ole2frame, double thickness);
double dxf_ole2frame_get_linetype_scale (DxfOle2Frame *ole2frame);
DxfOle2Frame *dxf_ole2frame_set_linetype_scale (DxfOle2Frame *ole2frame, double linetype_scale);
int16_t dxf_ole2frame_get_visibility (DxfOle2Frame *ole2frame);
DxfOle2Frame *dxf_ole2frame_set_visibility (DxfOle2Frame *ole2frame, int16_t visibility);
int dxf_ole2frame_get_color (DxfOle2Frame *ole2frame);
DxfOle2Frame *dxf_ole2frame_set_color (DxfOle2Frame *ole2frame, int color);
int dxf_ole2frame_get_paperspace (DxfOle2Frame *ole2frame);
DxfOle2Frame *dxf_ole2frame_set_paperspace (DxfOle2Frame *ole2frame, int paperspace);
int dxf_ole2frame_get_graphics_data_size (DxfOle2Frame *ole2frame);
DxfOle2Frame *dxf_ole2frame_set_graphics_data_size (DxfOle2Frame *ole2frame, int graphics_data_size);
int16_t dxf_ole2frame_get_shadow_mode (DxfOle2Frame *ole2frame);
DxfOle2Frame *dxf_ole2frame_set_shadow_mode (DxfOle2Frame *ole2frame, int16_t shadow_mode);
DxfBinaryGraphicsData *dxf_ole2frame_get_binary_graphics_data (DxfOle2Frame *ole2frame);
DxfOle2Frame *dxf_ole2frame_set_binary_graphics_data (DxfOle2Frame *ole2frame, DxfBinaryGraphicsData *data);
char *dxf_ole2frame_get_dictionary_owner_soft (DxfOle2Frame *ole2frame);
DxfOle2Frame *dxf_ole2frame_set_dictionary_owner_soft (DxfOle2Frame *ole2frame, char *dictionary_owner_soft);
char *dxf_ole2frame_get_material (DxfOle2Frame *ole2frame);
DxfOle2Frame *dxf_ole2frame_set_material (DxfOle2Frame *ole2frame, char *material);
char *dxf_ole2frame_get_dictionary_owner_hard (DxfOle2Frame *ole2frame);
DxfOle2Frame *dxf_ole2frame_set_dictionary_owner_hard (DxfOle2Frame *ole2frame, char *dictionary_owner_hard);
int16_t dxf_ole2frame_get_lineweight (DxfOle2Frame *ole2frame);
DxfOle2Frame *dxf_ole2frame_set_lineweight (DxfOle2Frame *ole2frame, int16_t lineweight);
char *dxf_ole2frame_get_plot_style_name (DxfOle2Frame *ole2frame);
DxfOle2Frame *dxf_ole2frame_set_plot_style_name (DxfOle2Frame *ole2frame, char *plot_style_name);
long dxf_ole2frame_get_color_value (DxfOle2Frame *ole2frame);
DxfOle2Frame *dxf_ole2frame_set_color_value (DxfOle2Frame *ole2frame, long color_value);
char *dxf_ole2frame_get_color_name (DxfOle2Frame *ole2frame);
DxfOle2Frame *dxf_ole2frame_set_color_name (DxfOle2Frame *ole2frame, char *color_name);
long dxf_ole2frame_get_transparency (DxfOle2Frame *ole2frame);
DxfOle2Frame *dxf_ole2frame_set_transparency (DxfOle2Frame *ole2frame, long transparency);
char *dxf_ole2frame_get_end_of_data (DxfOle2Frame *ole2frame);
DxfOle2Frame *dxf_ole2frame_set_end_of_data (DxfOle2Frame *ole2frame, char *end_of_data);
char *dxf_ole2frame_get_length_of_binary_data (DxfOle2Frame *ole2frame);
DxfOle2Frame *dxf_ole2frame_set_length_of_binary_data (DxfOle2Frame *ole2frame, char *length_of_binary_data);
DxfPoint *dxf_ole2frame_get_p0 (DxfOle2Frame *ole2frame);
DxfOle2Frame *dxf_ole2frame_set_p0 (DxfOle2Frame *ole2frame, DxfPoint *p0);
double dxf_ole2frame_get_x0 (DxfOle2Frame *ole2frame);
DxfOle2Frame *dxf_ole2frame_set_x0 (DxfOle2Frame *ole2frame, double x0);
double dxf_ole2frame_get_y0 (DxfOle2Frame *ole2frame);
DxfOle2Frame *dxf_ole2frame_set_y0 (DxfOle2Frame *ole2frame, double y0);
double dxf_ole2frame_get_z0 (DxfOle2Frame *ole2frame);
DxfOle2Frame *dxf_ole2frame_set_z0 (DxfOle2Frame *ole2frame, double z0);
DxfPoint *dxf_ole2frame_get_p1 (DxfOle2Frame *ole2frame);
DxfOle2Frame *dxf_ole2frame_set_p1 (DxfOle2Frame *ole2frame, DxfPoint *p1);
double dxf_ole2frame_get_x1 (DxfOle2Frame *ole2frame);
DxfOle2Frame *dxf_ole2frame_set_x1 (DxfOle2Frame *ole2frame, double x1);
double dxf_ole2frame_get_y1 (DxfOle2Frame *ole2frame);
DxfOle2Frame *dxf_ole2frame_set_y1 (DxfOle2Frame *ole2frame, double y1);
double dxf_ole2frame_get_z1 (DxfOle2Frame *ole2frame);
DxfOle2Frame *dxf_ole2frame_set_z1 (DxfOle2Frame *ole2frame, double z1);
int dxf_ole2frame_get_ole_version_number (DxfOle2Frame *ole2frame);
DxfOle2Frame *dxf_ole2frame_set_ole_version_number (DxfOle2Frame *ole2frame, int ole_version_number);
int dxf_ole2frame_get_ole_object_type (DxfOle2Frame *ole2frame);
DxfOle2Frame *dxf_ole2frame_set_ole_object_type (DxfOle2Frame *ole2frame, int ole_object_type);
int dxf_ole2frame_get_tilemode_descriptor (DxfOle2Frame *ole2frame);
DxfOle2Frame *dxf_ole2frame_set_tilemode_descriptor (DxfOle2Frame *ole2frame, int tilemode_descriptor);
long dxf_ole2frame_get_length (DxfOle2Frame *ole2frame);
DxfOle2Frame *dxf_ole2frame_set_length (DxfOle2Frame *ole2frame, long length);
DxfChar *dxf_ole2frame_get_binary_data (DxfOle2Frame *ole2frame);
DxfOle2Frame *dxf_ole2frame_set_binary_data (DxfOle2Frame *ole2frame, DxfChar *binary_data);
DxfOle2Frame *dxf_ole2frame_get_next (DxfOle2Frame *ole2frame);
DxfOle2Frame *dxf_ole2frame_set_next (DxfOle2Frame *ole2frame, DxfOle2Frame *next);
DxfOle2Frame *dxf_ole2frame_get_last (DxfOle2Frame *ole2frame);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_OLE2FRAME_H */


/* EOF */
