/*!
 * \file mline.h
 *
 * \author Copyright (C) 2015, 2016, 2017 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF mline entity (\c MLINE).
 *
 * \since The \c MLINE entity was introduced in DXF R13.
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
 * For more details see http://www.autodesk.com .
 * <hr>
 */


#ifndef LIBDXF_SRC_MLINE_H
#define LIBDXF_SRC_MLINE_H


#include "global.h"
#include "point.h"
#include "binary_graphics_data.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief DXF definition of an AutoCAD mline entity.
 *
 * \warning The 2 group codes in mline entities and mlinestyle objects
 * are redundant fields.\n
 * These groups should not be modified under any circumstances, although
 * it is safe to read them and use their values.\n
 * The correct fields to modify are:\n
 * <b>Mline</b>: The 340 group in the same object, which indicates the
 * proper \c MLINESTYLE object.\n
 * <b>Mlinestyle</b>: The 3 group value in the \c MLINESTYLE dictionary,
 * which precedes the 350 group that has the handle or entity name of
 * the current \c MLINESTYLE. 
 */
typedef struct
dxf_mline_struct
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
                 * Group code = 38.\n
                 * \deprecated As of version R11. */
        double thickness;
                /*!< Thickness of the arc in the local Z-direction.\n
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
        /* Specific members for a DXF mline. */
        char *style_name;
                /*!< String of up to 32 characters.\n
                 * The name of the style used for this mline.\n
                 * An entry for this style must exist in the MLINESTYLE
                 * dictionary.\n
                 * Group code = 2. */
        double x0;
                /*!< X value of Start point (in WCS).\n
                 * Group code = 10. */
        double y0;
                /*!< Y value of Start point (in WCS).\n
                 * Group code = 20. */
        double z0;
                /*!< Z value of Start point (in WCS).\n
                 * Group code = 30. */
        double x1[DXF_MAX_PARAM];
                /*!< X value of Vertex coordinates (multiple entries;
                 * one entry for each vertex).\n
                 * Group code = 11. */
        double y1[DXF_MAX_PARAM];
                /*!< Y value of Vertex coordinates (multiple entries;
                 * one entry for each vertex).\n
                 * Group code = 21. */
        double z1[DXF_MAX_PARAM];
                /*!< Z value of Vertex coordinates (multiple entries;
                 * one entry for each vertex).\n
                 * Group code = 31. */
        double x2[DXF_MAX_PARAM];
                /*!< X value of the Direction vector of segment starting
                 * at this vertex (multiple entries; one for each vertex).\n
                 * Group code = 12. */
        double y2[DXF_MAX_PARAM];
                /*!< Y value of the Direction vector of segment starting
                 * at this vertex (multiple entries; one for each vertex).\n
                 * Group code = 22. */
        double z2[DXF_MAX_PARAM];
                /*!< Z value of the Direction vector of segment starting
                 * at this vertex (multiple entries; one for each vertex).\n
                 * Group code = 32. */
        double x3[DXF_MAX_PARAM];
                /*!< X value of the Direction vector of miter at this
                 * vertex (multiple entries: one for each vertex).\n
                 * Group code = 13. */
        double y3[DXF_MAX_PARAM];
                /*!< Y value of the Direction vector of miter at this
                 * vertex (multiple entries: one for each vertex).\n
                 * Group code = 23. */
        double z3[DXF_MAX_PARAM];
                /*!< Z value of the Direction vector of miter at this
                 * vertex (multiple entries: one for each vertex).\n
                 * Group code = 33. */
        double scale_factor;
                /*!< Scale factor.\n
                 * Group code = 40. */
        double element_parameters[DXF_MAX_PARAM];
                /*!< Element parameters (repeats based on previous
                 * code 74).\n
                 * Group code = 41. */
        double area_fill_parameters[DXF_MAX_PARAM];
                /*!< Area fill parameters (repeats based on previous
                 * code 75).\n
                 * Group code = 42. */
        int justification;
                /*!< Justification:
                 * <ol>
                 * <li value = "0"> top.</li>
                 * <li value = "1"> zero.</li>
                 * <li value = "2"> bottom.</li>
                 * </ol>
                 * Group code = 70. */
        int flags;
                /*!< Flags (bit-coded values):
                 * <ol>
                 * <li value = "1"> unlocked.</li>
                 * <li value = "2"> closed.</li>
                 * <li value = "4"> supress start caps.</li>
                 * <li value = "8"> supress end caps.</li>
                 * </ol>
                 * Group code = 71. */
        int number_of_vertices;
                /*!< Number of vertices.\n
                 * Group code = 72. */
        int number_of_elements;
                /*!< Number of elements in MLINESTYLE definition.\n
                 * Group code = 73. */
        int number_of_parameters;
                /*!< Number of parameters for this element (repeats for
                 * each element in segment).\n
                 * Group code = 74. */
        int number_of_area_fill_parameters;
                /*!< Number of area fill parameters for this element
                 * (repeats for each element in segment).\n
                 * Group code = 75. */
        double extr_x0;
                /*!< X value of the extrusion direction.\n
                 * Optional, if ommited defaults to 0.0.\n
                 * Group code = 210. */
        double extr_y0;
                /*!< Y value of the extrusion direction.\n
                 * Optional, if ommited defaults to 0.0.\n
                 * Group code = 220. */
        double extr_z0;
                /*!< Z value of the extrusion direction.\n
                 * Optional, if ommited defaults to 1.0.\n
                 * Group code = 230. */
        char *mlinestyle_dictionary;
                /*!< Pointer-handle/ID of MLINESTYLE dictionary.\n
                 * Group code = 340. */
        struct DxfMline *next;
                /*!< pointer to the next DxfMline.\n
                 * \c NULL in the last DxfMline. */
} DxfMline;


DxfMline *
dxf_mline_new ();
DxfMline *
dxf_mline_init
(
        DxfMline *mline
);
DxfMline *
dxf_mline_read
(
        DxfFile *fp,
        DxfMline *mline
);
int
dxf_mline_write
(
        DxfFile *fp,
        DxfMline *mline
);
int
dxf_mline_free
(
        DxfMline *mline
);
void
dxf_mline_free_chain
(
        DxfMline *mlines
);
int
dxf_mline_get_id_code
(
        DxfMline *mline
);
DxfMline *
dxf_mline_set_id_code
(
        DxfMline *mline,
        int id_code
);
char *
dxf_mline_get_linetype
(
        DxfMline *mline
);
DxfMline *
dxf_mline_set_linetype
(
        DxfMline *mline,
        char *linetype
);
char *
dxf_mline_get_layer
(
        DxfMline *mline
);
DxfMline *
dxf_mline_set_layer
(
        DxfMline *mline,
        char *layer
);
double
dxf_mline_get_elevation
(
        DxfMline *mline
);
DxfMline *
dxf_mline_set_elevation
(
        DxfMline *mline,
        double elevation
);
double
dxf_mline_get_thickness
(
        DxfMline *mline
);
DxfMline *
dxf_mline_set_thickness
(
        DxfMline *mline,
        double thickness
);
double
dxf_mline_get_linetype_scale
(
        DxfMline *mline
);
DxfMline *
dxf_mline_set_linetype_scale
(
        DxfMline *mline,
        double linetype_scale
);
int16_t
dxf_mline_get_visibility
(
        DxfMline *mline
);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_MLINE_H */


/* EOF */
