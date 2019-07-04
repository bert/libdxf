/*!
 * \file util.h
 *
 * \author Copyright (C) 2010 by Luis Matos <gass@otiliamatos.ath.cx>.
 *
 * \author Copyright (C) 2010, 2014, 2015, 2016, 2017, 2018, 2019
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for libDXF coding utilities.
 *
 * <hr>
 * <h1><b>Copyright Notices.</b></h1>\n
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.\n\n
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


#ifndef LIBDXF_SRC_UTIL_H
#define LIBDXF_SRC_UTIL_H

#include "global.h"
#include "file.h"


#ifdef __cplusplus
extern "C" {
#endif


/*! Macro to return if the expression is false */
#define dxf_return_val_if_fail(expr, val) if (!expr) return val;

/*! Macro to return according to the expression */
enum return_state { FAIL = 0, SUCCESS, FOUND };

#define dxf_return(expr) switch(expr) \
	{ \
	case FAIL: \
		return FAIL; \
		break; \
	case FOUND: \
		return FOUND; \
		break; \
	}


DxfChar *dxf_char_new ();
DxfChar *dxf_char_init (DxfChar *c);
char *dxf_char_get_value (DxfChar *c);
DxfChar *dxf_char_set_value (DxfChar *c, char *value);
int dxf_char_get_length (DxfChar *c);
DxfChar *dxf_char_set_length (DxfChar *c, int length);
DxfChar *dxf_char_get_next (DxfChar *c);
DxfChar *dxf_char_set_next (DxfChar *c, DxfChar *next);
DxfChar *dxf_char_get_last (DxfChar *c);
int dxf_char_free (DxfChar *c);
int dxf_char_free_list (DxfChar *chars);
DxfDouble *dxf_double_new ();
DxfDouble *dxf_double_init (DxfDouble *d);
double dxf_double_get_value (DxfDouble *d);
DxfDouble *dxf_double_set_value (DxfDouble *d, double value);
DxfDouble *dxf_double_get_next (DxfDouble *d);
DxfDouble *dxf_double_set_next (DxfDouble *d, DxfDouble *next);
DxfDouble *dxf_double_get_last (DxfDouble *d);
int dxf_double_free (DxfDouble *d);
int dxf_double_free_list (DxfDouble *doubles);
DxfInt *dxf_int_new ();
DxfInt *dxf_int_init (DxfInt *i);
int dxf_int_get_value (DxfInt *i);
DxfInt *dxf_int_set_value (DxfInt *i, int value);
DxfInt *dxf_int_get_next (DxfInt *i);
DxfInt *dxf_int_set_next (DxfInt *i, DxfInt *next);
DxfInt *dxf_int_get_last (DxfInt *i);
int dxf_int_free (DxfInt *i);
int dxf_int_free_list (DxfInt *ints);
DxfInt16 *dxf_int16_new ();
DxfInt16 *dxf_int16_init (DxfInt16 *i);
int16_t dxf_int16_get_value (DxfInt16 *i);
DxfInt16 *dxf_int16_set_value (DxfInt16 *i, int16_t value);
DxfInt16 *dxf_int16_get_next (DxfInt16 *i);
DxfInt16 *dxf_int16_set_next (DxfInt16 *i, DxfInt16 *next);
DxfInt16 *dxf_int16_get_last (DxfInt16 *i);
int dxf_int16_free (DxfInt16 *i);
int dxf_int16_free_list (DxfInt16 *ints);
DxfInt32 *dxf_int32_new ();
DxfInt32 *dxf_int32_init (DxfInt32 *i);
int32_t dxf_int32_get_value (DxfInt32 *i);
DxfInt32 *dxf_int32_set_value (DxfInt32 *i, int32_t value);
DxfInt32 *dxf_int32_get_next (DxfInt32 *i);
DxfInt32 *dxf_int32_set_next (DxfInt32 *i, DxfInt32 *next);
DxfInt32 *dxf_int32_get_last (DxfInt32 *i);
int dxf_int32_free (DxfInt32 *i);
int dxf_int32_free_list (DxfInt32 *ints);
DxfInt64 *dxf_int64_new ();
DxfInt64 *dxf_int64_init (DxfInt64 *i);
int64_t dxf_int64_get_value (DxfInt64 *i);
DxfInt64 *dxf_int64_set_value (DxfInt64 *i, int64_t value);
DxfInt64 *dxf_int64_get_next (DxfInt64 *i);
DxfInt64 *dxf_int64_set_next (DxfInt64 *i, DxfInt64 *next);
DxfInt64 *dxf_int64_get_last (DxfInt64 *i);
int dxf_read_is_double (int type);
int dxf_read_is_int (int type);
int dxf_read_is_int16_t (int type);
int dxf_read_is_int32_t (int type);
int dxf_read_is_int64_t (int type);
int dxf_read_is_string (int type);
int dxf_read_line (char * temp_string, DxfFile *fp);
int dxf_read_scanf (DxfFile *fp, const char *template, ...);
DxfFile *dxf_read_init (const char *filename);
void dxf_read_close (DxfFile *file);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_UTIL_H */


/* EOF */
