/*!
 * \file rastervariables.h
 *
 * \author Copyright (C) 2015, 2016, 2017, 2018
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF rastervariables object (\c RASTERVARIABLES).
 *
 * \since The \c RASTERVARIABLES object was introduced in DXF R14.
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


#ifndef LIBDXF_SRC_RASTERVARIABLES_H
#define LIBDXF_SRC_RASTERVARIABLES_H


#include "global.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief DXF definition of an AutoCAD rastervariables object
 * (\c RASTERVARIABLES).
 */
typedef struct
dxf_rastervariables_struct
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
        /* Specific members for a DXF rastervariables. */
        int display_image_frame;
                /*!< Display-image-frame flag.\n
                 * <ol>
                 * <li value = "0"> No frame.</li>
                 * <li value = "1"> Display frame.</li>
                 * </ol>
                 * Group code = 70. */
        int display_quality;
                /*!< Image display quality (screen only).\n
                 * <ol>
                 * <li value = "0"> Draft.</li>
                 * <li value = "1"> High.</li>
                 * </ol>
                 * Group code = 71. */
        int units;
                /*!< AutoCAD units for inserting images.\n
                 * This is what one AutoCAD unit is equal to for the
                 * purpose of inserting and scaling images with an
                 * associated resolution.\n
                 * <ol>
                 * <li value = "0"> None.</li>
                 * <li value = "1"> Millimeter.</li>
                 * <li value = "2"> Centimeter.</li>
                 * <li value = "3"> Meter.</li>
                 * <li value = "4"> Kilometer.</li>
                 * <li value = "5"> Inch.</li>
                 * <li value = "6"> Foot.</li>
                 * <li value = "7"> Yard.</li>
                 * <li value = "8"> Mile.</li>
                 * </ol>
                 * Group code = 72. */
        int32_t class_version;
                /*!< Class version.\n
                 * 0 = R14 version.\n
                 * Group code = 90. */
        struct DxfRasterVariables *next;
                /*!< Pointer to the next DxfRasterVariables.\n
                 * \c NULL in the last DxfRasterVariables. */
} DxfRasterVariables;


DxfRasterVariables *dxf_rastervariables_new ();
DxfRasterVariables *dxf_rastervariables_init (DxfRasterVariables *rastervariables);
DxfRasterVariables *dxf_rastervariables_read (DxfFile *fp, DxfRasterVariables *rastervariables);
int dxf_rastervariables_write (DxfFile *fp, DxfRasterVariables *rastervariables);
int dxf_rastervariables_free (DxfRasterVariables *rastervariables);
void dxf_rastervariables_free_list (DxfRasterVariables *rastervariables);
int dxf_rastervariables_get_id_code (DxfRasterVariables *rastervariables);
DxfRasterVariables *dxf_rastervariables_set_id_code (DxfRasterVariables *rastervariables, int id_code);
char *dxf_rastervariables_get_dictionary_owner_soft (DxfRasterVariables *rastervariables);
DxfRasterVariables *dxf_rastervariables_set_dictionary_owner_soft (DxfRasterVariables *rastervariables, char *dictionary_owner_soft);
char *dxf_rastervariables_get_dictionary_owner_hard (DxfRasterVariables *rastervariables);
DxfRasterVariables *dxf_rastervariables_set_dictionary_owner_hard (DxfRasterVariables *rastervariables, char *dictionary_owner_hard);
int dxf_rastervariables_get_display_image_frame (DxfRasterVariables *rastervariables);
DxfRasterVariables *dxf_rastervariables_set_display_image_frame (DxfRasterVariables *rastervariables, int display_image_frame);
int dxf_rastervariables_get_display_quality (DxfRasterVariables *rastervariables);
DxfRasterVariables *dxf_rastervariables_set_display_quality (DxfRasterVariables *rastervariables, int display_quality);
int dxf_rastervariables_get_units (DxfRasterVariables *rastervariables);
DxfRasterVariables *dxf_rastervariables_set_units (DxfRasterVariables *rastervariables, int units);
int32_t dxf_rastervariables_get_class_version (DxfRasterVariables *rastervariables);
DxfRasterVariables *dxf_rastervariables_set_class_version (DxfRasterVariables *rastervariables, int32_t class_version);
DxfRasterVariables *dxf_rastervariables_get_next (DxfRasterVariables *rastervariables);
DxfRasterVariables *dxf_rastervariables_set_next (DxfRasterVariables *rastervariables, DxfRasterVariables *next);
DxfRasterVariables *dxf_rastervariables_get_last (DxfRasterVariables *rastervariables);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_RASTERVARIABLES_H */


/* EOF */
