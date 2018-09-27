/*!
 * \file dictionaryvar.h
 *
 * \author Copyright (C) 2015, 2016, 2017, 2018
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF dictionaryvar object (\c DICTIONARYVAR).
 *
 * \since The \c DICTIONARYVAR object was introduced in DXF R14.
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


#ifndef LIBDXF_SRC_DICTIONARYVAR_H
#define LIBDXF_SRC_DICTIONARYVAR_H


#include "global.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief DXF definition of an AutoCAD dictionaryvar object (\c DICTIONARYVAR).
 */
typedef struct
dxf_dictionaryvar_struct
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
        /* Specific members for a DXF dictionaryvar. */
        char *value;
                /*!< Value of variable.\n
                 * Group code = 1. */
        char *object_schema_number;
                /*!< Object schema number (currently set to 0).\n
                 * Group code = 280. */
        struct DxfDictionaryVar *next;
                /*!< Pointer to the next DxfDictionaryVar.\n
                 * \c NULL in the last DxfDictionaryVar. */
} DxfDictionaryVar;


DxfDictionaryVar *dxf_dictionaryvar_new ();
DxfDictionaryVar *dxf_dictionaryvar_init (DxfDictionaryVar *dictionaryvar);
DxfDictionaryVar *dxf_dictionaryvar_read (DxfFile *fp, DxfDictionaryVar *dictionaryvar);
int dxf_dictionaryvar_write (DxfFile *fp, DxfDictionaryVar *dictionaryvar);
int dxf_dictionaryvar_free (DxfDictionaryVar *dictionaryvar);
void dxf_dictionaryvar_free_list (DxfDictionaryVar *dictionaryvars);
int dxf_dictionaryvar_get_id_code (DxfDictionaryVar *dictionaryvar);
DxfDictionaryVar *dxf_dictionaryvar_set_id_code (DxfDictionaryVar *dictionaryvar, int id_code);
char *dxf_dictionaryvar_get_dictionary_owner_soft (DxfDictionaryVar *dictionaryvar);
DxfDictionaryVar *dxf_dictionaryvar_set_dictionary_owner_soft (DxfDictionaryVar *dictionaryvar, char *dictionary_owner_soft);
char *dxf_dictionaryvar_get_dictionary_owner_hard (DxfDictionaryVar *dictionaryvar);
DxfDictionaryVar *dxf_dictionaryvar_set_dictionary_owner_hard (DxfDictionaryVar *dictionaryvar, char *dictionary_owner_hard);
char *dxf_dictionaryvar_get_value (DxfDictionaryVar *dictionaryvar);
DxfDictionaryVar *dxf_dictionaryvar_set_value (DxfDictionaryVar *dictionaryvar, char *value);
char *dxf_dictionaryvar_get_object_schema_number (DxfDictionaryVar *dictionaryvar);
DxfDictionaryVar *dxf_dictionaryvar_set_object_schema_number (DxfDictionaryVar *dictionaryvar, char *object_schema_number);
DxfDictionaryVar *dxf_dictionaryvar_get_next (DxfDictionaryVar *dictionaryvar);
DxfDictionaryVar *dxf_dictionaryvar_set_next (DxfDictionaryVar *dictionaryvar, DxfDictionaryVar *next);
DxfDictionaryVar *dxf_dictionaryvar_get_last (DxfDictionaryVar *dictionaryvar);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_DICTIONARYVAR_H */


/* EOF */
