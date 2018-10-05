/*!
 * \file mlinestyle.h
 *
 * \author Copyright (C) 2015, 2016, 2017, 2018
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF mlinestyle object (\c MLINESTYLE).
 *
 * \since The \c MLINESTYLE object was introduced in DXF R13.
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
 * For more details see http://www.autodesk.com .
 * <hr>
 */


#ifndef LIBDXF_SRC_MLINESTYLE_H
#define LIBDXF_SRC_MLINESTYLE_H


#include "global.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief DXF definition of an AutoCAD mlinestyle object.
 *
 * \warning The 2 group codes in mline entities and mlinestyle objects
 * are redundant fields.\n
 * These groups should not be modified under any circumstances, although
 * it is safe to read them and use their values.\n
 * The correct fields to modify are:\n
 * <b>Mline</b>: The 340 group in the same object, which indicates the
 * proper \c MLINESTYLE object.\n
 * <b>Mlinestyle</b>: The 3 group value in the \c MLINESTYLE dictionary,
 * which precedes the 350 group that has the handle or entity name of
 * the current \c MLINESTYLE. 
 */
typedef struct
dxf_mlinestyle_struct
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
        /* Specific members for a DXF mlinestyle. */
        char *name;
                /*!< Mline style name.\n
                 * Group code = 2. */
        char *description;
                /*!< Style description (string, 255 characters maximum).\n
                 * Group code = 3. */
        char *element_linetype[DXF_MAX_PARAM];
                /*!< Element linetype (string, default = BYLAYER).\n
                 * Multiple entries can exist; one entry for each
                 * element.\n
                 * Group code = 6. */
        double element_offset[DXF_MAX_PARAM];
                /*!< Element offset (real, no default).\n
                 * Multiple entries can exist; one entry for each
                 * element.\n
                 * Group code = 49. */
        double start_angle;
                /*!< Start angle (real, default is 90 degrees).\n
                 * Group code = 51. */
        double end_angle;
                /*!< End angle (real, default is 90 degrees).\n
                 * Group code = 52. */
        int color;
                /*!< Fill color (integer, default = 256).\n
                 * Group code = 62. */
        int element_color[DXF_MAX_PARAM];
                /*!< Element color (integer, default = 0).\n
                 * Multiple entries can exist; one entry for each
                 * element.\n
                 * Group code = 62. */
        int flags;
                /*!< Flags (bit-coded values):
                 * <ol>
                 * <li value = "1"> Fill on.</li>
                 * <li value = "2"> Display miters.</li>
                 * <li value = "16"> Start square end (line) cap.</li>
                 * <li value = "32"> Start inner arcs cap.</li>
                 * <li value = "64"> Start round (outer arcs) cap.</li>
                 * <li value = "256"> End square (line) cap.</li>
                 * <li value = "512"> End inner arcs.</li>
                 * <li value = "1024"> End round (outer arcs) cap.</li>
                 * </ol>
                 * Group code = 70. */
        int number_of_elements;
                /*!< Number of elements.\n
                 * Group code = 71. */
        struct DxfMlinestyle *next;
                /*!< pointer to the next DxfMlinestyle.\n
                 * \c NULL in the last DxfMlinestyle. */
} DxfMlinestyle;


DxfMlinestyle *dxf_mlinestyle_new ();
DxfMlinestyle *dxf_mlinestyle_init (DxfMlinestyle *mlinestyle);
DxfMlinestyle *dxf_mlinestyle_read (DxfFile *fp, DxfMlinestyle *mlinestyle);
int dxf_mlinestyle_write (DxfFile *fp, DxfMlinestyle *mlinestyle);
int dxf_mlinestyle_free (DxfMlinestyle *mlinestyle);
void dxf_mlinestyle_free_list (DxfMlinestyle *mlinestyles);
int dxf_mlinestyle_get_id_code (DxfMlinestyle *mlinestyle);
DxfMlinestyle *dxf_mlinestyle_set_id_code (DxfMlinestyle *mlinestyle, int id_code);
char *dxf_mlinestyle_get_dictionary_owner_soft (DxfMlinestyle *mlinestyle);
DxfMlinestyle *dxf_mlinestyle_set_dictionary_owner_soft (DxfMlinestyle *mlinestyle, char *dictionary_owner_soft);
char *dxf_mlinestyle_get_dictionary_owner_hard (DxfMlinestyle *mlinestyle);
DxfMlinestyle *dxf_mlinestyle_set_dictionary_owner_hard (DxfMlinestyle *mlinestyle, char *dictionary_owner_hard);
char *dxf_mlinestyle_get_name (DxfMlinestyle *mlinestyle);
DxfMlinestyle *dxf_mlinestyle_set_name (DxfMlinestyle *mlinestyle, char *name);
char *dxf_mlinestyle_get_description (DxfMlinestyle *mlinestyle);
DxfMlinestyle *dxf_mlinestyle_set_description (DxfMlinestyle *mlinestyle, char *description);
char *dxf_mlinestyle_get_ith_element_linetype (DxfMlinestyle *mlinestyle, int i);
DxfMlinestyle *dxf_mlinestyle_set_ith_element_linetype (DxfMlinestyle *mlinestyle, char *element_linetype, int i);
double dxf_mlinestyle_get_element_offset (DxfMlinestyle *mlinestyle);
DxfMlinestyle *dxf_mlinestyle_set_element_offset (DxfMlinestyle *mlinestyle, double *element_offset);
double dxf_mlinestyle_get_ith_element_offset (DxfMlinestyle *mlinestyle, int i);
DxfMlinestyle *dxf_mlinestyle_set_ith_element_offset (DxfMlinestyle *mlinestyle, double element_offset, int i);
double dxf_mlinestyle_get_start_angle (DxfMlinestyle *mlinestyle);
DxfMlinestyle *dxf_mlinestyle_set_start_angle (DxfMlinestyle *mlinestyle, double start_angle);
double dxf_mlinestyle_get_end_angle (DxfMlinestyle *mlinestyle);
DxfMlinestyle *dxf_mlinestyle_set_end_angle (DxfMlinestyle *mlinestyle, double end_angle);
int dxf_mlinestyle_get_color (DxfMlinestyle *mlinestyle);
DxfMlinestyle *dxf_mlinestyle_set_color (DxfMlinestyle *mlinestyle, int color);
int dxf_mlinestyle_get_ith_element_color (DxfMlinestyle *mlinestyle, int i);
DxfMlinestyle *dxf_mlinestyle_set_ith_element_color (DxfMlinestyle *mlinestyle, int element_color, int i);
int dxf_mlinestyle_get_flags (DxfMlinestyle *mlinestyle);
DxfMlinestyle *dxf_mlinestyle_set_flags (DxfMlinestyle *mlinestyle, int flags);
int dxf_mlinestyle_flag_is_fill_on (DxfMlinestyle *mlinestyle);
int dxf_mlinestyle_flag_is_display_miters (DxfMlinestyle *mlinestyle);
int dxf_mlinestyle_flag_is_start_square_end_cap (DxfMlinestyle *mlinestyle);
int dxf_mlinestyle_flag_is_start_inner_arcs_cap (DxfMlinestyle *mlinestyle);
int dxf_mlinestyle_flag_is_start_round_outer_arcs_cap (DxfMlinestyle *mlinestyle);
int dxf_mlinestyle_flag_is_end_square_end_cap (DxfMlinestyle *mlinestyle);
int dxf_mlinestyle_flag_is_end_inner_arcs_cap (DxfMlinestyle *mlinestyle);
int dxf_mlinestyle_flag_is_end_round_outer_arcs_cap (DxfMlinestyle *mlinestyle);
int dxf_mlinestyle_get_number_of_elements (DxfMlinestyle *mlinestyle);
DxfMlinestyle *dxf_mlinestyle_set_number_of_elements (DxfMlinestyle *mlinestyle, int number_of_elements);
DxfMlinestyle *dxf_mlinestyle_get_next (DxfMlinestyle *mlinestyle);
DxfMlinestyle *dxf_mlinestyle_set_next (DxfMlinestyle *mlinestyle, DxfMlinestyle *next);
DxfMlinestyle *dxf_mlinestyle_get_last (DxfMlinestyle *mlinestyle);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_MLINESTYLE_H */


/* EOF */
