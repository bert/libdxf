/*!
 * \file ucs.h
 *
 * \author Copyright (C) 2008, 2012, 2014, 2015, 2016, 2017
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF User Coordinate System entity (\c UCS).
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


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief DXF definition of an AutoCAD User Coordinate System entity
 * (\c UCS).
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
typedef struct
dxf_ucs
{
        int id_code;
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file.\n
                 * Group code = 5. */
        char *UCS_name;
                /*!< group code = 2. */
        double x_origin;
                /*!< X-value of the base point coordinate.\n
                 * Group code = 10. */
        double y_origin;
                /*!< Y-value of the base point coordinate.\n
                 * Group code = 20. */
        double z_origin;
                /*!< Z-value of the base point coordinate.\n
                 * Group code = 30. */
        double x_X_dir;
                /*!< X-value of the reference point for the X-axis
                 * direction.\n
                 * Group code = 11. */
        double y_X_dir;
                /*!< Y-value of the reference point for the X-axis
                 * direction.\n
                 * Group code = 21. */
        double z_X_dir;
                /*!< Z-value of the reference point for the X-axis
                 * direction.\n
                 * Group code = 31. */
        double x_Y_dir;
                /*!< X-value of the reference point for the Y-axis
                 * direction.\n
                 * Group code = 12. */
        double y_Y_dir;
                /*!< Y-value of the reference point for the Y-axis
                 * direction.\n
                 * Group code = 22. */
        double z_Y_dir;
                /*!< Z-value of the reference point for the Y-axis
                 * direction.\n
                 * Group code = 32. */
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
        char *dictionary_owner_soft;
                /*!< Soft-pointer ID/handle to owner dictionary
                 * (optional).\n
                 * Group code = 330. */
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
void dxf_ucs_free_chain (DxfUcs *ucss);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_UCS_H */


/* EOF */
