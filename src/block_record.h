/*!
 * \file block_record.h
 *
 * \author Copyright (C) 2015, 2016, 2017, 2018, 2019
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF block record symbol table entry
 * (\c BLOCK_RECORD).
 *
 * \since The \c BLOCK_RECORD table was introduced in DXF R13.
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


#ifndef LIBDXF_SRC_BLOCK_RECORD_H
#define LIBDXF_SRC_BLOCK_RECORD_H


#include "global.h"
#include "binary_data.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief Definition of an AutoCAD block record symbol table entry
 * (\c BLOCK_RECORD).
 *
 * This table entry contains an entry to a block registered within a
 * drawing.
 */
typedef struct
dxf_block_record_struct
{
        int id_code;
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file.\n
                 * Group code = 5. */
        char *block_name;
                /*!< Name of the block registered within the drawing.\n
                 * Group code = 2. */
        int16_t flag;
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
        int16_t insertion_units;
                 /*!< Block insertion units.\n
                  * Group code = 70. */
        int16_t explodability;
                 /*!< Block explodability.\n
                  * Group code = 280. */
        int16_t scalability;
                 /*!< Block scalability.\n
                  * Group code = 281. */
        DxfBinaryData *binary_graphics_data;
                /*!< Binary data for bitmap preview (optional).\n
                 * Multiple lines of 256 characters maximum per line
                 * (optional).\n
                 * Group code = 310.\n
                 * \since Introduced in version R2000. */
        char *dictionary_owner_soft;
                /*!< Soft-pointer ID/handle to owner dictionary
                 * (optional).\n
                 * Group code = 330. */
        char *object_owner_soft;
                /*!< Soft-pointer ID/handle to owner object (optional).\n
                 * Group code = 330. */
        char *associated_layout_hard;
                /*!< Hard-pointer ID/handle to associated LAYOUT object.\n
                 * Group code = 340. */
        char *dictionary_owner_hard;
                /*!< Hard owner ID/handle to owner dictionary
                 * (optional).\n
                 * Group code = 360. */
        char *xdata_string_data;
                /*!< Xdata string data “DesignCenter Data” (optional).\n
                 * Group code = 1000. */
        char *xdata_application_name;
                /*!< Xdata application name “ACAD” (optional).\n
                 * Group code = 1001. */
        int16_t design_center_version_number;
                /*!< Autodesk Design Center version number.\n
                 * Group code = 1070.*/
        int16_t insert_units;
                /*!< Insert units:\n
                 * <ol>
                 *   <li value = "0"> Unitless,</li>
                 *   <li value = "1"> Inches,</li>
                 *   <li value = "2"> Feet,</li>
                 *   <li value = "3"> Miles,</li>
                 *   <li value = "4"> Millimeters,</li>
                 *   <li value = "5"> Centimeters,</li>
                 *   <li value = "6"> Meters,</li>
                 *   <li value = "7"> Kilometers,</li>
                 *   <li value = "8"> Microinches,</li>
                 *   <li value = "9"> Mils,</li>
                 *   <li value = "10"> Yards,</li>
                 *   <li value = "11"> Angstroms,</li>
                 *   <li value = "12"> Nanometers,</li>
                 *   <li value = "13"> Microns,</li>
                 *   <li value = "14"> Decimeters,</li>
                 *   <li value = "15"> Decameters,</li>
                 *   <li value = "16"> Hectometers,</li>
                 *   <li value = "17"> Gigameters,</li>
                 *   <li value = "18"> Astronomical units,</li>
                 *   <li value = "19"> Light years,</li>
                 *   <li value = "20"> Parsecs.</li>
                 * </ol>
                 * Group code = 1070.*/
        struct DxfBlockRecord *next;
                /*!< Pointer to the next DxfAppid.\n
                 * \c NULL in the last DxfAppid. */
} DxfBlockRecord;


DxfBlockRecord *dxf_block_record_new ();
DxfBlockRecord *dxf_block_record_init (DxfBlockRecord *block_record);
DxfBlockRecord *dxf_block_record_read (DxfFile *fp, DxfBlockRecord *block_record);
int dxf_block_record_write (DxfFile *fp, DxfBlockRecord *block_record);
int dxf_block_record_free (DxfBlockRecord *block_record);
void dxf_block_record_free_list (DxfBlockRecord *block_records);
int dxf_block_record_get_id_code (DxfBlockRecord *block_record);
DxfBlockRecord *dxf_block_record_set_id_code (DxfBlockRecord *block_record, int id_code);
char *dxf_block_record_get_block_name (DxfBlockRecord *block_record);
DxfBlockRecord *dxf_block_record_set_block_name (DxfBlockRecord *block_record, char *block_name);
int16_t dxf_block_record_get_flag (DxfBlockRecord *block_record);
DxfBlockRecord *dxf_block_record_set_flag (DxfBlockRecord *block_record, int16_t flag);
int dxf_block_record_is_xreferenced (DxfBlockRecord *block_record);
int dxf_block_record_is_xresolved (DxfBlockRecord *block_record);
int dxf_block_record_is_referenced (DxfBlockRecord *block_record);
int16_t dxf_block_record_get_insertion_units (DxfBlockRecord *block_record);
DxfBlockRecord *dxf_block_record_set_insertion_units (DxfBlockRecord *block_record, int16_t insertion_units);
int16_t dxf_block_record_get_explodability (DxfBlockRecord *block_record);
DxfBlockRecord *dxf_block_record_set_explodability (DxfBlockRecord *block_record, int16_t explodability);
int16_t dxf_block_record_get_scalability (DxfBlockRecord *block_record);
DxfBlockRecord *dxf_block_record_set_scalability (DxfBlockRecord *block_record, int16_t scalability);
DxfBinaryData *dxf_block_record_get_binary_graphics_data (DxfBlockRecord *block_record);
DxfBlockRecord *dxf_block_record_set_binary_graphics_data (DxfBlockRecord *block_record, DxfBinaryData *data);
char *dxf_block_record_get_dictionary_owner_soft (DxfBlockRecord *block_record);
DxfBlockRecord *dxf_block_record_set_dictionary_owner_soft (DxfBlockRecord *block_record, char *dictionary_owner_soft);
char *dxf_block_record_get_object_owner_soft (DxfBlockRecord *block_record);
DxfBlockRecord *dxf_block_record_set_object_owner_soft (DxfBlockRecord *block_record, char *object_owner_soft);
char *dxf_block_record_get_associated_layout_hard (DxfBlockRecord *block_record);
char *dxf_block_record_get_dictionary_owner_hard (DxfBlockRecord *block_record);
DxfBlockRecord *dxf_block_record_set_dictionary_owner_hard (DxfBlockRecord *block_record, char *dictionary_owner_hard);
char *dxf_block_record_get_xdata_string_data (DxfBlockRecord *block_record);
DxfBlockRecord *dxf_block_record_set_xdata_string_data (DxfBlockRecord *block_record, char *xdata_string_data);
char *dxf_block_record_get_xdata_application_name (DxfBlockRecord *block_record);
DxfBlockRecord *dxf_block_record_set_xdata_application_name (DxfBlockRecord *block_record, char *xdata_application_name);
int16_t dxf_block_record_get_design_center_version_number (DxfBlockRecord *block_record);
DxfBlockRecord *dxf_block_record_set_design_center_version_number (DxfBlockRecord *block_record, int16_t design_center_version_number);
int16_t dxf_block_record_get_insert_units (DxfBlockRecord *block_record);
DxfBlockRecord *dxf_block_record_set_insert_units (DxfBlockRecord *block_record, int16_t insert_units);
DxfBlockRecord *dxf_block_record_get_next (DxfBlockRecord *block_record);
DxfBlockRecord *dxf_block_record_set_next (DxfBlockRecord *block_record, DxfBlockRecord *next);
DxfBlockRecord *dxf_block_record_get_last (DxfBlockRecord *block_record);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_BLOCK_RECORD_H */


/* EOF */
