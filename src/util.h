/*!
 * \file util.h
 * \author Copyright (C) 2010 by Luis Matos <gass@otiliamatos.ath.cx>.\n
 * \brief LIBDXF coding utilities, header file.
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


#ifndef UTIL_H
#define UTIL_H

#include <stdarg.h>
#include "global.h"


/* macro to return if the expression is false */
#define dxf_return_val_if_fail(expr, val) if (!expr) return val;

#define __DXF_LINE_READ__ dxf_read_get_line_count ()

/* macro to return according to the expression */
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

int dxf_read_is_double (int type);
int dxf_read_is_int (int type);
int dxf_read_is_string (int type);
int dxf_read_line (char * temp_string, FILE *fp);
int dxf_read_scanf (FILE *fp, const char *template, ...);
void dxf_read_init(void);
int dxf_read_get_line_count(void);
#endif /* UTIL_H */


/* EOF */
