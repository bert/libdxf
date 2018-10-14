/*!
 * \file ucs.h
 *
 * \author Copyright (C) 2008, 2012, 2014, 2015, 2016, 2017, 2018
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF User Coordinate System entity (\c UCS).
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


#ifndef LIBDXF_SRC_UCS_H
#define LIBDXF_SRC_UCS_H


#include "global.h"
#include "point.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief DXF definition of an AutoCAD User Coordinate System entity
 * (\c UCS).
 */
typedef struct
dxf_ucs_struct
{
        int id_code;
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file.\n
                 * Group code = 5. */
        char *UCS_name;
                /*!< group code = 2. */
        DxfPoint *origin;
                /*!< Base point coordinate.\n
                 * Group codes = 10, 20 and 30.*/
        DxfPoint *X_dir;
                /*!< Reference point for the X-axis direction.\n
                 * Group codes = 11, 21 and 31.*/
        DxfPoint *Y_dir;
                /*!< Reference point for the Y-axis direction.\n
                 * Group codes = 12, 22 and 32.*/
        DxfPoint *orthographic_type_origin;
                /*!< Origin for this orthographic type relative to this
                 * UCS.\n
                 * Each 71 / 13,23,33 pair defines the UCS origin for a
                 * particular orthographic type relative to this UCS.\n
                 * For example, if the following pair is present, then
                 * invoking the UCS/LEFT command when UCSBASE is set to
                 * this UCS will cause the new UCS origin to become
                 * (1,2,3).\n
                 * <pre>
                 *   71:   5
                 *   13:   1.0
                 *   23:   2.0
                 *   33:   3.0
                 * </pre>
                 * If this pair were not present, then invoking the
                 * UCS/LEFT command would cause the new UCS origin to be
                 * set to this UCS's origin point.
                 * Group codes = 13, 23 and 33.\n
                 * \since Introduced in version R2000.\n */
        int flag;
                /*!< This flag is for the benefit of AutoCAD commands;
                 * it can be ignored by most programs that read DXF files,
                 * and need not be set by programs that write DXF files.\n
                 * bit coded:\n
                 * <ol>
                 * <li value = "16"> if set, table entry is externally
                 * dependent on an Xref.</li>
                 * <li value = "32"> if this bit and bit 16 are both set,
                 * the externally dependent Xref has been successfully
                 * resolved.</li>
                 * <li value = "64"> if set, the table entry was
                 * referenced by at least one entity in the drawing the
                 * last time the drawing was edited.</li>
                 * </ol>
                 * Group code = 70. */
        int orthographic_type;
                /*!< Orthographic type (optional);\n
                 * Always appears in pairs with the 13, 23, 33 codes):\n
                 * <ol>
                 * <li value = "1"> Top;</li>
                 * <li value = "2"> Bottom;</li>
                 * <li value = "3"> Front;</li>
                 * <li value = "4"> Back;</li>
                 * <li value = "5"> Left;</li>
                 * <li value = "6"> Right.</li>
                 * </ol>
                 * Group code = 71.\n
                 * \since Introduced in version R2000.\n */
        int other_base_UCS;
                /*!< Always 0.
                 * Group code = 79.\n
                 * \since Introduced in version R2000.\n */
        double elevation;
                /*!< Elevation.\n
                 * Group code = 146.\n
                 * \since Introduced in version R2000.\n */
        char *dictionary_owner_soft;
                /*!< Soft-pointer ID/handle to owner dictionary
                 * (optional).\n
                 * Group code = 330. */
        char *object_owner_soft;
                /*!< Soft-pointer ID/handle to owner object.\n
                 * Group code = 330.\n
                 * \since Introduced in version R2000.\n */
        char *base_UCS;
                /*!< ID/handle of base UCS if this is an orthographic.\n
                 * This code is not present if the 79 code is 0.\n
                 * If this code is not present and 79 code is non-zero,
                 * then base UCS is assumed to be WORLD.\n
                 * Group code = 346.\n
                 * \since Introduced in version R2000.\n */
        char *dictionary_owner_hard;
                /*!< Hard owner ID/handle to owner dictionary
                 * (optional).\n
                 * Group code = 360. */
        struct DxfUcs *next;
                /*!< Pointer to the next DxfUcs.\n
                 * \c NULL in the last DxfUcs. */
} DxfUcs;


DxfUcs *dxf_ucs_new ();
DxfUcs *dxf_ucs_init (DxfUcs *ucs);
DxfUcs *dxf_ucs_read (DxfFile *fp, DxfUcs *ucs);
int dxf_ucs_write (DxfFile *fp, DxfUcs *ucs);
int dxf_ucs_free (DxfUcs *ucs);
void dxf_ucs_free_list (DxfUcs *ucss);
int dxf_ucs_get_id_code (DxfUcs *ucs);
DxfUcs *dxf_ucs_set_id_code (DxfUcs *ucs, int id_code);
char *dxf_ucs_get_UCS_name (DxfUcs *ucs);
DxfUcs *dxf_ucs_set_UCS_name (DxfUcs *ucs, char *UCS_name);
DxfPoint *dxf_ucs_get_origin (DxfUcs *ucs);
DxfUcs *dxf_ucs_set_origin (DxfUcs *ucs, DxfPoint *origin);
double dxf_ucs_get_origin_x (DxfUcs *ucs);
DxfUcs *dxf_ucs_set_origin_x (DxfUcs *ucs, double x);
double dxf_ucs_get_origin_y (DxfUcs *ucs);
DxfUcs *dxf_ucs_set_origin_y (DxfUcs *ucs, double y);
double dxf_ucs_get_origin_z (DxfUcs *ucs);
DxfUcs *dxf_ucs_set_origin_z (DxfUcs *ucs, double z);
DxfPoint *dxf_ucs_get_X_dir (DxfUcs *ucs);
DxfUcs *dxf_ucs_set_X_dir (DxfUcs *ucs, DxfPoint *X_dir);
double dxf_ucs_get_X_dir_x (DxfUcs *ucs);
DxfUcs *dxf_ucs_set_X_dir_x (DxfUcs *ucs, double x);
double dxf_ucs_get_X_dir_y (DxfUcs *ucs);
DxfUcs *dxf_ucs_set_X_dir_y (DxfUcs *ucs, double y);
double dxf_ucs_get_X_dir_z (DxfUcs *ucs);
DxfUcs *dxf_ucs_set_X_dir_z (DxfUcs *ucs, double z);
DxfPoint *dxf_ucs_get_Y_dir (DxfUcs *ucs);
DxfUcs *dxf_ucs_set_Y_dir (DxfUcs *ucs, DxfPoint *Y_dir);
double dxf_ucs_get_Y_dir_x (DxfUcs *ucs);
DxfUcs *dxf_ucs_set_Y_dir_x (DxfUcs *ucs, double x);
double dxf_ucs_get_Y_dir_y (DxfUcs *ucs);
DxfUcs *dxf_ucs_set_Y_dir_y (DxfUcs *ucs, double y);
double dxf_ucs_get_Y_dir_z (DxfUcs *ucs);
DxfUcs *dxf_ucs_set_Y_dir_z (DxfUcs *ucs, double z);
DxfPoint *dxf_ucs_get_orthographic_type_origin (DxfUcs *ucs);
DxfUcs *dxf_ucs_set_orthographic_type_origin (DxfUcs *ucs, DxfPoint *orthographic_type_origin);
double dxf_ucs_get_orthographic_type_origin_x (DxfUcs *ucs);
DxfUcs *dxf_ucs_set_orthographic_type_origin_x (DxfUcs *ucs, double x);
double dxf_ucs_get_orthographic_type_origin_y (DxfUcs *ucs);
DxfUcs *dxf_ucs_set_orthographic_type_origin_y (DxfUcs *ucs, double y);
double dxf_ucs_get_orthographic_type_origin_z (DxfUcs *ucs);
DxfUcs *dxf_ucs_set_orthographic_type_origin_z (DxfUcs *ucs, double z);
int dxf_ucs_get_other_base_UCS (DxfUcs *ucs);
DxfUcs *dxf_ucs_set_other_base_UCS (DxfUcs *ucs, int other_base_UCS);
double dxf_ucs_get_elevation (DxfUcs *ucs);
DxfUcs *dxf_ucs_set_elevation (DxfUcs *ucs, double elevation);
char *dxf_ucs_get_dictionary_owner_soft (DxfUcs *ucs);
DxfUcs *dxf_ucs_set_dictionary_owner_soft (DxfUcs *ucs, char *dictionary_owner_soft);
char *dxf_ucs_get_object_owner_soft (DxfUcs *ucs);
DxfUcs *dxf_ucs_set_object_owner_soft (DxfUcs *ucs, char *object_owner_soft);
char *dxf_ucs_get_base_UCS (DxfUcs *ucs);
DxfUcs *dxf_ucs_set_object_base_UCS (DxfUcs *ucs, char *base_UCS);
char *dxf_ucs_get_dictionary_owner_hard (DxfUcs *ucs);
DxfUcs *dxf_ucs_set_dictionary_owner_hard (DxfUcs *ucs, char *dictionary_owner_hard);
DxfUcs *dxf_ucs_get_next (DxfUcs *ucs);
DxfUcs *dxf_ucs_set_next (DxfUcs *ucs, DxfUcs *next);
DxfUcs *dxf_ucs_get_last (DxfUcs *ucs);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_UCS_H */


/* EOF */
