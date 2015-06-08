/*!
 * \file attdef.h
 *
 * \author Copyright (C) 2008 ... 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF attribute definition entity (\c ATTDEF).
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


#ifndef LIBDXF_SRC_ATTDEF_H
#define LIBDXF_SRC_ATTDEF_H


/*!
 * \brief DXF definition of an AutoCAD attribute definition entity
 * (\c ATTDEF).
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
typedef struct
dxf_attdef
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
        /* Specific members for a DXF attdef. */
        char *default_value;
                /*!< Default value for the attribute.\n
                 * Group code = 1. */
        char *tag_value;
                /*!< Tagname for the attribute.\n
                 * Group code = 2. */
        char *prompt_value;
                /*!< Prompt text for the value to be stored in the
                 * attribute.\n
                 * Group code = 3. */
        char *text_style;
                /*!< The style used for the presentation of the value of
                 * the attribute.\n
                 * Defaults to \c STANDARD if  omitted in the DXF file.\n
                 * Group code = 7. */
        double x0;
                /*!< X-value of the starting point coordinate.\n
                 * Group code = 10. */
        double y0;
                /*!< Y-value of the starting point coordinate.\n
                 * Group code = 20. */
        double z0;
                /*!< Z-value of the starting point coordinate.\n
                 * Group code = 30. */
        double x1;
                /*!< X-value of the alignment point coordinate.\n
                 * Group code = 11. */
        double y1;
                /*!< Y-value of the alignment point coordinate.\n
                 * Group code = 21. */
        double z1;
                /*!< Z-value of the alignment point coordinate.\n
                 * Group code = 31. */
        double height;
                /*!< Character height of the attribute value.\n
                 * Group code = 40. */
        double rel_x_scale;
                /*!< Relative scale in the X-direction.\n
                 * Defaults to 1.0 if omitted from DXF file.\n
                 * Group code = 41. */
        double rot_angle;
                /*!< Rotation angle of the attribute value.\n
                 * Defaults to 0.0 if omitted from DXF file.\n
                 * Group code = 50. */
        double obl_angle;
                /*!< Oblique angle of the attribute value.\n
                 * Defaults to 0.0 if omitted from DXF file.\n
                 * Group code = 51. */
        int attr_flags;
                /*!< Attribute flags.\n
                 * Bit coded:\n
                 * <ol>
                 * <li value = "1"> attribute is invisible (does not display).</li>
                 * <li value = "2"> this is a constant attribute.</li>
                 * <li value = "4"> verification is required on input of this attribute.</li>
                 * <li value = "8"> attribute is preset (no prompt during insertion).</li>
                 * </ol>
                 * Group code = 70.
                 */
        int text_flags;
                /*!< Text flags.\n
                 * Bit coded:\n
                 * <ol>
                 * <li value = "2"> text is backward (mirrored in X).</li>
                 * <li value = "4"> text is upside down (mirrored in Y).</li>
                 * </ol>
                 * Defaults to 0 if ommited from DXF file.\n
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
        struct DxfAttdef *next;
                /*!< Pointer to the next DxfAttdef.\n
                 * \c NULL in the last DxfAttdef. */
} DxfAttdef;


DxfAttdef *
dxf_attdef_new ();
DxfAttdef *
dxf_attdef_init
(
        DxfAttdef *attdef
);
DxfAttdef *
dxf_attdef_read
(
        DxfFile *fp,
        DxfAttdef *attdef
);
int
dxf_attdef_write
(
        DxfFile *fp,
        DxfAttdef *attdef
);
int
dxf_attdef_free
(
        DxfAttdef *attdef
);
void
dxf_attdef_free_chain
(
        DxfAttdef *attdefs
);
int
dxf_attdef_is_invisible
(
        DxfAttdef *attdef
);
int
dxf_attdef_is_constant
(
        DxfAttdef *attdef
);
int
dxf_attdef_is_verification_required
(
        DxfAttdef *attdef
);
int
dxf_attdef_is_preset
(
        DxfAttdef *attdef
);


#endif /* LIBDXF_SRC_ATTDEF_H */


/* EOF */
