/*!
 * \file imagedef.h
 *
 * \author Copyright (C) 2015, 2016, 2017, 2018, 2019, 2020
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF imagedef object (\c IMAGEDEF).
 *
 * \since The \c IMAGEDEF object was introduced in DXF R14.
 *
 * \warning The \c IMAGEDEF object requires AutoCAD version R14 or higher.
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


#ifndef LIBDXF_SRC_IMAGEDEF_H
#define LIBDXF_SRC_IMAGEDEF_H


#include "global.h"
#include "point.h"
#include "imagedef_reactor.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief DXF definition of an AutoCAD imagedef object (\c IMAGEDEF).
 */
typedef struct
dxf_imagedef_struct
{
        /* Members common for all DXF group objects. */
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
        /* Specific members for a DXF imagedef. */
        char *file_name;
                /*!< File name of image.\n
                 * Group code = 1. */
        DxfPoint *p0;
                /*!< Image size in pixels (U and V values).\n
                 * Group codes = 10 and 20.*/
        DxfPoint *p1;
                /*!< Default size of one pixel in AutoCAD units (U and V
                 * values).\n
                 * Group codes = 11 and 21.*/
        int32_t class_version;
                /*!< Class version.\n
                 * 0 = R14 version.\n
                 * Group code = 90. */
        int16_t image_is_loaded_flag;
                /*!< Image-is-loaded flag.\n
                 * <ol>
                 * <li value = "0"> Unloaded.</li>
                 * <li value = "1"> Loaded.</li>
                 * </ol>
                 * Group code = 280.
                 */
        int16_t resolution_units;
                /*!< Resolution units.\n
                 * <ol>
                 * <li value = "0"> No units.</li>
                 * <li value = "2"> Centimeters.</li>
                 * <li value = "5"> Inch.</li>
                 * </ol>
                 * Group code = 281. */
        char *acad_image_dict_soft;
                /*!< Soft-pointer ID/handle to the ACAD_IMAGE_DICT
                 * dictionary.\n
                 * Group code = 330. */
        char *imagedef_reactor_soft[DXF_MAX_PARAM];
                /*!< Soft-pointer ID/handle to IMAGEDEF_REACTOR object
                 * (multiple entries; one for each instance).\n
                 * Group code = 330. */
        DxfImagedefReactor *imagedef_reactor;
                /*!< Pointer to the first DxfImagedefReactor in a linked
                 * list.\n
                 * Multiple entries; one for each instance.\n
                 * Group code = 330. */
        struct DxfImagedef *next;
                /*!< Pointer to the next DxfImagedef.\n
                 * \c NULL in the last DxfImagedef. */
} DxfImagedef;


DxfImagedef *dxf_imagedef_new ();
DxfImagedef *dxf_imagedef_init (DxfImagedef *imagedef);
DxfImagedef *dxf_imagedef_read (DxfFile *fp, DxfImagedef *imagedef);
int dxf_imagedef_write (DxfFile *fp, DxfImagedef *imagedef);
int dxf_imagedef_free (DxfImagedef *imagedef);
void dxf_imagedef_free_list (DxfImagedef *imagedefs);
int dxf_imagedef_get_id_code (DxfImagedef *imagedef);
DxfImagedef *dxf_imagedef_set_id_code (DxfImagedef *imagedef, int id_code);
char *dxf_imagedef_get_dictionary_owner_soft (DxfImagedef *imagedef);
DxfImagedef *dxf_imagedef_set_dictionary_owner_soft (DxfImagedef *imagedef, char *dictionary_owner_soft);
char *dxf_imagedef_get_dictionary_owner_hard (DxfImagedef *imagedef);
DxfImagedef *dxf_imagedef_set_dictionary_owner_hard (DxfImagedef *imagedef, char *dictionary_owner_hard);
char *dxf_imagedef_get_file_name (DxfImagedef *imagedef);
DxfImagedef *dxf_imagedef_set_file_name (DxfImagedef *imagedef, char *file_name);
DxfPoint *dxf_imagedef_get_p0 (DxfImagedef *imagedef);
DxfImagedef *dxf_imagedef_set_p0 (DxfImagedef *imagedef, DxfPoint *p0);
double dxf_imagedef_get_x0 (DxfImagedef *imagedef);
DxfImagedef *dxf_imagedef_set_x0 (DxfImagedef *imagedef, double x0);
double dxf_imagedef_get_y0 (DxfImagedef *imagedef);
DxfImagedef *dxf_imagedef_set_y0 (DxfImagedef *imagedef, double y0);
DxfPoint *dxf_imagedef_get_p1 (DxfImagedef *imagedef);
DxfImagedef *dxf_imagedef_set_p1 (DxfImagedef *imagedef, DxfPoint *p1);
double dxf_imagedef_get_x1 (DxfImagedef *imagedef);
DxfImagedef *dxf_imagedef_set_x1 (DxfImagedef *imagedef, double x1);
double dxf_imagedef_get_y1 (DxfImagedef *imagedef);
DxfImagedef *dxf_imagedef_set_y1 (DxfImagedef *imagedef, double y1);
int32_t dxf_imagedef_get_class_version (DxfImagedef *imagedef);
DxfImagedef *dxf_imagedef_set_class_version (DxfImagedef *imagedef, int32_t class_version);
int16_t dxf_imagedef_get_image_is_loaded_flag (DxfImagedef *imagedef);
DxfImagedef *dxf_imagedef_set_image_is_loaded_flag (DxfImagedef *imagedef, int16_t image_is_loaded_flag);
int16_t dxf_imagedef_get_resolution_units (DxfImagedef *imagedef);
DxfImagedef *dxf_imagedef_set_resolution_units (DxfImagedef *imagedef, int16_t resolution_units);
char *dxf_imagedef_get_acad_image_dict_soft (DxfImagedef *imagedef);
DxfImagedef *dxf_imagedef_set_acad_image_dict_soft (DxfImagedef *imagedef, char *acad_image_dict_soft);
DxfImagedefReactor *dxf_imagedef_get_imagedef_reactor (DxfImagedef *imagedef);
DxfImagedef *dxf_imagedef_set_imagedef_reactor (DxfImagedef *imagedef, DxfImagedefReactor *imagedef_reactor);
DxfImagedef *dxf_imagedef_get_next (DxfImagedef *imagedef);
DxfImagedef *dxf_imagedef_set_next (DxfImagedef *imagedef, DxfImagedef *next);
DxfImagedef *dxf_imagedef_get_last (DxfImagedef *imagedef);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_IMAGEDEF_H */


/* EOF */
