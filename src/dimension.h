/*!
 * \file dimension.h
 *
 * \author Copyright (C) 2008 ... 2014 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF dimension entity (\c DIMENSION).
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


#ifndef _DIMENSION_H
#define _DIMENSION_H


#include "global.h"


/*!
 * \brief DXF definition of an AutoCAD dimension.
 */
typedef struct
dxf_dimension
{
        /* Members common for all DXF drawable entities. */
        int id_code;
                /*!< group code = 5\n
                 * Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file. */
        char *linetype;
                /*!< group code = 6\n
                 * The linetype of the entity.\n
                 * Defaults to \c BYLAYER if ommitted in the DXF file. */
        char *layer;
                /*!< group code = 8\n
                 * Layer on which the entity is drawn.\n
                 * Defaults to layer "0" if no valid layername is given. */
        double elevation;
                /*!< group code = 38\n
                 * Elevation of the arc in the local Z-direction.\n
                 * Defaults to 0.0 if omitted in the DXF file, or prior
                 * to DXF version R12, or DXF_FLATLAND equals 0 (default). */
        double thickness;
                /*!< group code = 39\n
                 * Thickness of the arc in the local Z-direction.\n
                 * Defaults to 0.0 if ommitted in the DXF file. */
        double linetype_scale;
                /*!< group code = 48\n
                 * Linetype scale (optional). */
        int16_t visibility;
                /*!< group code = 60\n
                 * Object visibility (optional): 0 = Visible; 1 = Invisible. */
        int color;
                /*!< group code = 62\n
                 * Color of the entity.\n
                 * Defaults to \c BYLAYER if ommitted in the DXF file.\n
                 * Note that entities encapsulated in a block with the
                 * color \c BYBLOCK are represented in the "native" color of
                 * the \c BLOCK entity. */
        int paperspace;
                /*!< group code = 67\n
                 * Entities are to be drawn on either \c PAPERSPACE or
                 * \c MODELSPACE.\n
                 * Optional, defaults to \c DXF_MODELSPACE (0). */
        char *dictionary_owner_soft;
                /*!< group code = 330\n
                 * Soft-pointer ID/handle to owner dictionary (optional). */
        char *dictionary_owner_hard;
                /*!< group code = 360\n
                 * Hard owner ID/handle to owner dictionary (optional). */
        /* Specific members for a DXF dimension. */
        char *dim_text;
                /*!< Dimension text explicitly entered by the user.\n
                 * If null or "<>", the dimension measurement is drawn
                 * as the text, if " " [one blank space], the text is
                 * suppressed.\n
                 * Anything else is drawn as the text.\n
                 * Group code = 1. */
        char *dimblock_name;
                /*!< Name of pseudo-Block containing the current
                 * dimension entity geometry.\n
                 * Group code = 2. */
        char *dimstyle_name;
                /*!< Dimension style name.\n
                 * Group code = 3.  */
        double x0;
                /*!< X-value of the definition point for all dimension
                 * types.\n
                 * Group code = 10. */
        double y0;
                /*!< Y-value of the definition point for all dimension
                 * types.\n
                 * Group code = 20. */
        double z0;
                /*!< Z-value of the definition point for all dimension
                 * types.\n
                 * Group code = 30. */
        double x1;
                /*!< X-value of the middle point of dimension text.\n
                 * Group code = 11. */
        double y1;
                /*!< Y-value of the middle point of dimension text.\n
                 * Group code = 21. */
        double z1;
                /*!< Z-value of the middle point of dimension text.\n
                 * Group code = 31. */
        double x2;
                /*!< X-value of the dimension block translation vector.\n
                 * Group code = 12. */
        double y2;
                /*!< Y-value of the dimension block translation vector.\n
                 * Group code = 22. */
        double z2;
                /*!< Z-value of the dimension block translation vector.\n
                 * Group code = 32. */
        double x3;
                /*!< X-value of the definition point for linear and
                 * angular dimensions.\n
                 * Group code = 13. */
        double y3;
                /*!< Y-value of the definition point for linear and
                 * angular dimensions.\n
                 * Group code = 23. */
        double z3;
                /*!< Z-value of the definition point for linear and
                 * angular dimensions.\n
                 * Group code = 33. */
        double x4;
                /*!< X-value of the definition point for linear and
                 * angular dimensions.\n
                 * Group code = 14. */
        double y4;
                /*!< Y-value of the definition point for linear and
                 * angular dimensions.\n
                 * Group code = 24. */
        double z4;
                /*!< Z-value of the definition point for linear and
                 * angular dimensions.\n
                 * Group code = 34. */
        double x5;
                /*!< X-value of the definition point for diameter,
                 * radius, and angular dimensions.\n
                 * Group code = 15. */
        double y5;
                /*!< Y-value of the definition point for diameter,
                 * radius, and angular dimensions.\n
                 * Group code = 25. */
        double z5;
                /*!< Z-value of the definition point for diameter,
                 * radius, and angular dimensions.\n
                 * Group code = 35. */
        double x6;
                /*!< X-value of the point defining dimension arc for
                 * angular dimensions.\n
                 * Group code = 16. */
        double y6;
                /*!< Y-value of the point defining dimension arc for
                 * angular dimensions.\n
                 * Group code = 26. */
        double z6;
                /*!< Z-value of the point defining dimension arc for
                 * angular dimensions.\n
                 * Group code = 36. */
        double leader_length;
                /*!< Leader length for radius and diameter dimensions.\n
                 * Group code = 40. */
        double text_line_spacing_factor;
                /*!< Dimension text line spacing factor (optional):\n
                 * Percentage of default (3-on-5) line spacing to be
                 * applied.\n
                 * Valid values range from 0.25 to 4.00.\n
                 * Group code = 41. */
        double actual_measurement;
                /*!< Actual measurement (optional; read-only value).\n
                 * Group code = 42. */
        double angle;
                /*!< Angle of rotated, horizontal, or vertical linear
                 * dimensions.\n
                 * Group code = 50. */
        double hor_dir;
                /*!< In addition, all dimension types have an optional
                 * group (group code 51) that indicates the horizontal
                 * direction for the Dimension entity.\n
                 * This determines the orientation of dimension text and
                 * dimension lines for horizontal, vertical, and rotated
                 * linear dimensions.\n
                 * The group value is the negative of the Entity
                 * Coordinate Systems (ECS) angle of the UCS X axis in
                 * effect when the Dimension was drawn.\n
                 * The X axis of the UCS in effect when the Dimension
                 * was drawn is always parallel to the XY plane for the
                 * Dimension's ECS, and the angle between the UCS X axis
                 * and the ECS X axis is a single 2D angle.\n
                 * The value in group code 51 is the angle from
                 * horizontal (the effective X axis) to the ECS X axis.\n
                 * Entity Coordinate Systems (ECS) are described
                 * elsewhere in this documentation.\n
                 * Group code = 51. */
        double obl_angle;
                /*!< Linear dimension types with an oblique angle have
                 * an optional group (group code 52).\n
                 * When added to the rotation angle of the linear
                 * dimension (group code 50) this gives the angle of the
                 * extension lines.\n
                 * Group code = 52. */
        double text_angle;
                /*!< The optional group code 53 is the rotation angle of
                 * the dimension text away from its default orientation
                 * (the direction of the dimension line).\n
                 * Group code = 53. */
        int flag;
                /*!< Dimension type.\n
                 * Values 0–6 are integer values that represent the
                 * dimension type.\n
                 * Values 32, 64, and 128 are bit values, which are
                 * added to the integer values (value 32 is always set
                 * in R13 and later releases).\n
                 * 0 = Rotated, horizontal, or vertical.\n
                 * 1 = Aligned.\n
                 * 2 = Angular.\n
                 * 3 = Diameter.\n
                 * 4 = Radius.\n
                 * 5 = Angular 3-point.\n
                 * 6 = Ordinate.\n
                 * 32 = Indicates that the block reference (group code
                 *      2) is referenced by this dimension only.\n
                 * 64 = Ordinate type.\n
                 *      This is a bit value (bit 7) used only with
                 *      integer value 6.\n
                 *      If set, ordinate is X-type; if not set, ordinate
                 *      is Y-type.\n
                 * 128 = This is a bit value (bit 8) added to the other
                 *       group 70 values if the dimension text has been
                 *       positioned at a user-defined location rather
                 *       than at the default location.\n
                 * Group code = 70. */
        int attachment_point;
                /*!< Attachment point:\n
                 * 1 = Top left;\n
                 * 2 = Top center;\n
                 * 3 = Top right;\n
                 * 4 = Middle left;\n
                 * 5 = Middle center;\n
                 * 6 = Middle right;\n
                 * 7 = Bottom left;\n
                 * 8 = Bottom center;\n
                 * 9 = Bottom right.\n
                 * Group code = 71. */
        int text_line_spacing;
                /*!< Dimension text line spacing style (optional):\n
                 * 1 (or missing) = At least (taller characters will
                 *   override);\n
                 * 2 = Exact (taller characters will not override).\n
                 * Group code = 72. */
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
        struct DxfDimension *next;
                /*!< pointer to the next DxfDimension.\n
                 * \c NULL in the last DxfDimension. */
} DxfDimension, * DxfDimensionPtr;


DxfDimension *dxf_dimension_new ();
DxfDimension *
dxf_dimension_init
(
        DxfDimension *dxf_dimension
);
DxfDimension *
dxf_dimension_read
(
        DxfFile *fp,
        DxfDimension *dxf_dimension
);
int
dxf_dimension_write
(
        DxfFile *fp,
        DxfDimension *dxf_dimension
);
int
dxf_dimension_free
(
        DxfDimension *dxf_dimension
);


#endif /* _DIMENSION_H */


/* EOF */
