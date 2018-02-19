/*!
 * \file view.h
 *
 * \author Copyright (C) 2008, 2012, 2014, 2015, 2016, 2017, 2018
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF view symbol table entry (\c VIEW).
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
 * For more details see http://www.autodesk.com.
 * <hr>
 */

#ifndef LIBDXF_SRC_VIEW_H
#define LIBDXF_SRC_VIEW_H


#include "global.h"
#include "point.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief DXF definition of an AutoCAD view symbol table entry (\c VIEW).
 *
 * See chapter 2 of the "AutoLISP Programmer's Reference" for
 * information on DCS, the Display Coordinate System.
 */
typedef struct
dxf_view_struct
{
        int id_code;
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file.\n
                 * Group code = 5. */
        char *view_name;
                /*!< Name of view.\n
                 * Group code = 2. */
        DxfPoint *p0;
                /*!< View center point, in Display Coordinate System.\n
                 * Group codes = 10 and 20.*/
        double x_view;
                /*!< View center point, in Display Coordinate System.\n
                 * Group code = 10. */
        double y_view;
                /*!< View center point, in Display Coordinate System.\n
                 * Group code = 20. */
        DxfPoint *p1;
                /*!< View direction from target, in World Coordinate
                 * Group codes = 11, 21 and 31.*/
        double x_direction;
                /*!< View direction from target, in World Coordinate
                 * System.\n
                 * Group code = 11. */
        double y_direction;
                /*!< View direction from target, in World Coordinate
                 * System.\n
                 * Group code = 21. */
        double z_direction;
                /*!< View direction from target, in World Coordinate
                 * System.\n
                 * Group code = 31. */
        DxfPoint *p2;
                /*!< Target point, in WCS.\n
                 * Group codes = 12, 22 and 32.*/
        double x_target;
                /*!< Target point, in WCS.\n
                 * Group code = 12. */
        double y_target;
                /*!< Target point, in WCS.\n
                 * Group code = 22. */
        double z_target;
                /*!< Target point, in WCS.\n
                 * Group code = 32. */
        double view_height;
                /*!< View height in DCS.\n
                 * Group code = 40. */
        double view_width;
                /*!< View width in DCS.\n
                 * Group code = 41. */
        double lens_length;
                /*!< Lens length.\n
                 * Group code = 42. */
        double front_plane_offset;
                /*!< Front clipping plane - offset from target point.\n
                 * Group code = 43. */
        double back_plane_offset;
                /*!< Back clipping plane - offset from target point.\n
                 * Group code = 44. */
        double view_twist_angle;
                /*!< Twist angle.\n
                 * Group code = 50. */
        int flag;
                /*!< \n
                 * bit coded:\n
                 * <ol>
                 * <li value ="1"> If set, view is in paperspace.</li>
                 * <li value ="16"> If set, table entry is externally
                 * dependent on an Xref.</li>
                 * <li value = "32"> If this bit and bit 16 are both set,
                 * the externally dependent Xref has been successfully
                 * resolved.</li>
                 * <li value ="64"> If set, the table entry was
                 * referenced by at least one entity in the drawing the
                 * last time the drawing was edited.</li>
                 * </ol>
                 * This flag is for the benefit of AutoCAD commands;
                 * it can be ignored by most programs that read DXF files,
                 * and need not be set by programs that write DXF files.\n
                 * Group code = 70. */
        int view_mode;
                /*!< View mode (see \c VIEWMODE system variable).\n
                 * Group code = 71. */
        char *dictionary_owner_soft;
                /*!< Soft-pointer ID/handle to owner dictionary
                 * (optional).\n
                 * Group code = 330. */
        char *dictionary_owner_hard;
                /*!< Hard owner ID/handle to owner dictionary
                 * (optional).\n
                 * Group code = 360. */
        struct DxfView *next;
                /*!< Pointer to the next DxfView.\n
                 * \c NULL in the last DxfView. */
} DxfView;


DxfView *dxf_view_new ();
DxfView *dxf_view_init (DxfView *view);
DxfView *dxf_view_read (DxfFile *fp, DxfView *view);
int dxf_view_write (DxfFile *fp, DxfView *view);
int dxf_view_free (DxfView *view);
void dxf_view_free_chain (DxfView *views);
int dxf_view_get_id_code (DxfView *view);
DxfView *dxf_view_set_id_code (DxfView *view, int id_code);
char *dxf_view_get_view_name (DxfView *view);
DxfView *dxf_view_set_view_name (DxfView *view, char *view_name);
DxfPoint *dxf_view_get_p0 (DxfView *view);
DxfView *dxf_view_set_p0 (DxfView *view, DxfPoint *p0);
double dxf_view_get_x0 (DxfView *view);
DxfView *dxf_view_set_x0 (DxfView *view, double x0);
double dxf_view_get_y0 (DxfView *view);
DxfView *dxf_view_set_y0 (DxfView *view, double y0);
DxfPoint *dxf_view_get_p1 (DxfView *view);
DxfView *dxf_view_set_p1 (DxfView *view, DxfPoint *p1);
double dxf_view_get_x1 (DxfView *view);
DxfView *dxf_view_set_x1 (DxfView *view, double x1);
double dxf_view_get_y1 (DxfView *view);
DxfView *dxf_view_set_y1 (DxfView *view, double y1);
double dxf_view_get_z1 (DxfView *view);
DxfView *dxf_view_set_z1 (DxfView *view, double z1);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_VIEW_H */


/* EOF */
