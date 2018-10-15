/*!
 * \file xrecord.h
 *
 * \author Copyright (C) 2015, 2016, 2017, 2018
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF xrecord object (\c XRECORD).
 *
 * \since The \c XRECORD object was introduced in DXF R13.
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
 * For more details see http://www.autodesk.com.
 * <hr>
 */


#ifndef LIBDXF_SRC_XRECORD_H
#define LIBDXF_SRC_XRECORD_H


#include "global.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief DXF definition of an AutoCAD xrecord object (\c XRECORD).
 */
typedef struct
dxf_xrecord_struct
{
        /* Members common for all DXF objects. */
        int id_code;
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file.\n
                 * Group code = 5. */
        char *dictionary_owner_soft;
                /*!< Soft-pointer ID/handle to owner dictionary (optional).\n
                 * Group code = 330. */
        char *dictionary_owner_hard;
                /*!< Hard owner ID/handle to owner dictionary (optional).\n
                 * Group code = 360. */
        /* Specific members for a DXF xrecord. */
        int group_code;
                /*!< Group code for the xrecord value (determines type). */
        int8_t I8;
                /*!< 8-bit integer value.\n
                 * Group codes = 280 ... 289. */
        int16_t I16;
                /*!< 16-bit integer value.\n
                 * Group codes = 60 ... 79, 170 ... 175. */
        int32_t I32;
                /*!< 32-bit integer value.\n
                 * Group codes = 90 ... 99. */
        double D;
                /*!< double value.\n
                 * Group codes = 10 ... 59. */
        float F;
                /*!< .\n
                 * Group codes = 140 ... 147. */
        char *S;
                /*!< string value.\n
                 * Group codes = 0 ... 9, 100, 102, 105, 300 ... 369. */
        struct DxfXrecord *next;
                /*!< Pointer to the next DxfXrecord.\n
                 * \c NULL in the last DxfXrecord. */
} DxfXrecord;


DxfXrecord *dxf_xrecord_new ();
DxfXrecord *dxf_xrecord_init (DxfXrecord *xrecord);
DxfXrecord *dxf_xrecord_read (DxfFile *fp, DxfXrecord *xrecord);
int dxf_xrecord_write (DxfFile *fp, DxfXrecord *xrecord);
int dxf_xrecord_free (DxfXrecord *xrecord);
void dxf_xrecord_free_list (DxfXrecord *xrecords);
int dxf_xrecord_get_id_code (DxfXrecord *xrecord);
DxfXrecord *dxf_xrecord_set_id_code (DxfXrecord *xrecord, int id_code);
char *dxf_xrecord_get_dictionary_owner_soft (DxfXrecord *xrecord);
DxfXrecord *dxf_xrecord_set_dictionary_owner_soft (DxfXrecord *xrecord, char *dictionary_owner_soft);
char *dxf_xrecord_get_dictionary_owner_hard (DxfXrecord *xrecord);
DxfXrecord *dxf_xrecord_set_dictionary_owner_hard (DxfXrecord *xrecord, char *dictionary_owner_hard);
int dxf_xrecord_get_group_code (DxfXrecord *xrecord);
DxfXrecord *dxf_xrecord_set_group_code (DxfXrecord *xrecord, int group_code);
int8_t dxf_xrecord_get_I8 (DxfXrecord *xrecord);
DxfXrecord *dxf_xrecord_set_I8 (DxfXrecord *xrecord, int8_t I8);
int16_t dxf_xrecord_get_I16 (DxfXrecord *xrecord);
DxfXrecord *dxf_xrecord_set_I16 (DxfXrecord *xrecord, int16_t I16);
int32_t dxf_xrecord_get_I32 (DxfXrecord *xrecord);
DxfXrecord *dxf_xrecord_set_I32 (DxfXrecord *xrecord, int32_t I32);
double dxf_xrecord_get_D (DxfXrecord *xrecord);
DxfXrecord *dxf_xrecord_set_D (DxfXrecord *xrecord, double D);
float dxf_xrecord_get_F (DxfXrecord *xrecord);
DxfXrecord *dxf_xrecord_set_F (DxfXrecord *xrecord, float F);
char *dxf_xrecord_get_S (DxfXrecord *xrecord);
DxfXrecord *dxf_xrecord_set_S (DxfXrecord *xrecord, char *S);
DxfXrecord *dxf_xrecord_get_next (DxfXrecord *xrecord);
DxfXrecord *dxf_xrecord_set_next (DxfXrecord *xrecord, DxfXrecord *next);
DxfXrecord *dxf_xrecord_get_last (DxfXrecord *xrecord);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_XRECORD_H */


/* EOF */
