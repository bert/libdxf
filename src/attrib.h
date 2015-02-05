/*!
 * \file attrib.h
 *
 * \author Copyright (C) 2008 ... 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Definition of a DXF attribute entity (\c ATTRIB).
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


#include "global.h"


#ifndef LIBDXF_SRC_ATTRIB_H
#define LIBDXF_SRC_ATTRIB_H


/*!
 * \brief DXF definition of an AutoCAD attribute entity (\c ATTRIB).
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
typedef struct
dxf_attrib
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
        int16_t line_weight;
                /*!< Lineweight enum value.\n
                 * Stored and moved around as a 16-bit integer.\n
                 * Group code = 370. */
        /* Specific members for a DXF attrib. */
        char *value;
                /*!< Default value (string).\n
                 * Group code = 1. */
        char *tag_value;
                /*!< Attribute tag (string).\n
                 * Group code = 2. */
        char *text_style;
                /*!< Text style name (optional, default = STANDARD).\n
                 * Group code = 7. */
        double x0;
                /*!< X-value of text start point (in OCS).\n
                 * Group code = 10. */
        double y0;
                /*!< Y-value of text start point (in OCS).\n
                 * Group code = 20. */
        double z0;
                /*!< Z-value of text start point (in OCS).\n
                 * Group code = 30. */
        double x1;
                /*!< X-value of alignment point (in OCS).\n
                 * Present only if 72 or 74 group is present and
                 * nonzero.\n
                 * Group code = 11. */
        double y1;
                /*!< Y-value of alignment point (in OCS).\n
                 * Present only if 72 or 74 group is present and
                 * nonzero.\n
                 * Group code = 21. */
        double z1;
                /*!< Z-value of alignment point (in OCS).\n
                 * Present only if 72 or 74 group is present and
                 * nonzero.\n
                 * Group code = 31. */
        double height;
                /*!< Text height.\n
                 * Group code = 40. */
        double rel_x_scale;
                /*!< Relative X scale factor (width) (optional;
                 * default = 1.0).\n
                 * This value is also adjusted when fit-type text is
                 * used.\n
                 * Group code = 41. */
        double rot_angle;
                /*!< Text rotation (optional; default = 0.0).\n
                 * Group code = 50. */
        double obl_angle;
                /*!< Oblique angle (optional; default = 0.0).\n
                 * Group code = 51. */
        int attr_flags;
                /*!< Attribute flags.\n
                 * Bit coded:\n
                 * <ol>
                 * <li value = "1"> Attribute is invisible (does not
                 * appear).</li>
                 * <li value = "2"> This is a constant attribute.</li>
                 * <li value = "4"> Verification is required on input of
                 * this attribute.</li>
                 * <li value = "8"> Attribute is preset (no prompt
                 * during insertion).</li>
                 * </ol>
                 * Group code = 70. */
        int text_flags;
                /*!< Text generation flags (optional, default = 0).\n
                 * See \c TEXT.\n
                 * Optional, defaults to 0\n
                 * Bit coded:\n
                 * <ol>
                 * <li value = "2"> Text is backward (mirrored in X).</li>
                 * <li value = "4"> Text is upside down (mirrored in Y).</li>
                 * </ol>
                 * Group code = 71. */
        int hor_align;
                /*!< Horizontal text justification type (optional,
                 * default = 0).\n
                 * See \c TEXT.\n
                 * Not bit coded:
                 * <ol>
                 * <li value = "0"> Left.</li>
                 * <li value = "1"> Center.</li>
                 * <li value = "2"> Right.</li>
                 * <li value = "3"> Aligned, only when vert_align = 0.</li>
                 * <li value = "4"> Middle, only when vert_align = 0.</li>
                 * <li value = "5"> Fit, only when vert_align = 0.</li>
                 * </ol>
                 * Group code = 72. */
        int field_length;
                /*!< Field length (optional; default = 0) (not currently
                 * used in DXF R14).\n
                 * Group code = 73. */
        int vert_align;
                /*!< Vertical text justification type (optional,
                 * default = 0).\n
                 * See group code 73 in \c TEXT.\n
                 * Not bit coded:\n
                 * <ol>
                 * <li value = "0"> Baseline.</li>
                 * <li value = "1"> Bottom.</li>
                 * <li value = "2"> Middle.</li>
                 * <li value = "3"> Top.</li>
                 * </ol>
                 * Group code = 74.\n
                 * \version Added in DXF R12. */
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
        struct DxfAttrib *next;
                /*!< Pointer to the next DxfAttrib.\n
                 * \c NULL in the last DxfAttrib. */
} DxfAttrib;


DxfAttrib *
dxf_attrib_new ();
DxfAttrib *
dxf_attrib_init
(
        DxfAttrib *attrib
);
DxfAttrib *
dxf_attrib_read
(
        DxfFile *fp,
        DxfAttrib *attrib
);
int
dxf_attrib_write
(
        DxfFile *fp,
        DxfAttrib *attrib
);
int
dxf_attrib_free
(
        DxfAttrib *attrib
);


#endif /* LIBDXF_SRC_ATTRIB_H */


/* EOF */
