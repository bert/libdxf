/*!
 * \file global.h
 *
 * \author Copyright (C) 2008, 2009, 2010, 2012, 2013, 2014, 2015, 2016,
 * 2017 by Bert Timmerman <bert.timmerman@xs4all.nl>.\n
 *
 * \author Copyright (C) 2010 by Luis Matos <gass@otiliamatos.ath.cx>.
 *
 * \author Copyright (C) 2012 by Paolo Caroni <kenren89@gmail.com>.
 *
 * \brief  This is a global header file for a library with functions to
 * generate a dxf file.
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


/* prevent following headers from being loaded a zillion times */
#ifndef LIBDXF_SRC_GLOBAL_H
#define LIBDXF_SRC_GLOBAL_H

#include <stdarg.h>
#include <stdio.h>
#include <stdint.h> /* not part of the C++ standard */
#include <stdlib.h>
#include <ctype.h>
#include <inttypes.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <math.h>
#include <errno.h>
#include <time.h>
#include <limits.h>

/*
 * Standard gettext macros.
 */
#ifdef ENABLE_NLS
#  include <libintl.h>
#  undef _
#  define _(String) dgettext (PACKAGE, String)
#  define Q_(String) g_strip_context ((String), gettext (String))
#  ifdef gettext_noop
#    define N_(String) gettext_noop (String)
#  else
#    define N_(String) (String)
#  endif
#else
#  define textdomain(String) (String)
#  define gettext(String) (String)
#  define dgettext(Domain,Message) (Message)
#  define dcgettext(Domain,Message,Type) (Message)
#  define bindtextdomain(Domain,Directory) (Domain)
#  define _(String) (String)
#  define Q_(String) g_strip_context ((String), (String))
#  define N_(String) (String)
#endif


#include "dbg.h"
#include "entity.h"


#ifdef __MSDOS__
#  ifndef MSDOS
#    define MSDOS
        /*!< \brief MS DOS - compilers.
         *
         * Use #define MSDOS if not defined by compiler or cases below.\n
         * Microsoft C: auto-defines MSDOS.\n
         * Borland C: auto-defines __MSDOS__.\n
         * DJGPP : auto-defines MSDOS. */
#  endif
#endif

#ifdef __TURBOC__
#  define __MSC
        /*!< \brief Increase Borland C compatibility in libraries. */
#endif

#ifdef MSDOS
#  undef UNIX
        /*!< \brief Decide if we have UNIX or MSDOS. */
#endif

/* In general it is possible to check for 64-bit with the architecture
 * builtins of GCC, e.g. with: */
#if defined (__alpha__)\
  || defined (__ia64__)\
  || defined (__ppc64__)\
  || defined (__s390x__)\
  || defined (__x86_64__)
#define BUILD_64 1
        /*!< For specific parts when building 64 bit targets. */
#endif

/* For other platforms check the length of word size: */
#if (__WORDSIZE == 64)
#define BUILD_64 1
        /*!< For specific parts when building 64 bit targets. */
#endif

#ifndef DEBUG
#  define DEBUG 0
        /*!< \brief Verbose debugging output to \c stderr on/off toggle.
         *
         * If not already defined as a compiler directive the default value is
         * 0 (off). */
#endif

#define INTER_ACTIVE_PROMPT 0
        /*!< \brief Toggle for an interactive prompt during run time.
         *
         * If not already defined as a compiler directive the default value is
         * 0 (off). */

#ifndef TRUE
#  define TRUE 1
        /*!< \brief True is 1. */
#endif

#ifndef OUTSIDE
#  define OUTSIDE 2
        /*!< \brief Outside is 2. */
#endif

#ifndef INSIDE
#  define INSIDE 3
        /*!< \brief Inside is 3. */
#endif

#ifndef ON_EDGE
#  define ON_EDGE 4
        /*!< \brief On the edge is 4. */
#endif

#ifndef FALSE
#  define FALSE 0
        /*!< \brief False is 0. */
#endif

#ifndef DXF_ERROR
#  define DXF_ERROR -1
        /*!< \brief A DXF error is -1. */
#endif

#define DXF_DEBUG_BEGIN \
        fprintf (stderr, \
          (_("[File: %s: line: %d] Entering %s () function.\n")), \
          __FILE__, __LINE__, __FUNCTION__);
        /*!< \brief Verbose debugging output to \c stderr.
         *
         * Compile with -DDEBUG compiler directive enabled. */

#define DXF_DEBUG_END \
        fprintf (stderr, \
          (_("[File: %s: line: %d] Leaving %s () function.\n")), \
          __FILE__, __LINE__, __FUNCTION__);
        /*!< \brief Verbose debugging output to \c stderr.
         *
         * Compile with -DDEBUG compiler directive enabled. */


/*!
 * \brief DXF definition of a DXF file.
 */
typedef struct
dxf_file_struct
{
    FILE *fp;
        /*!< File handle. */
    char *filename;
        /*!< Dxf filename. */
    int line_number;
        /*!< Last line read. */
    int last_id_code;
        /*!< Last id code written to, or read from, file. */
    int acad_version_number;
        /*!< AutoCAD version number. */
    int follow_strict_version_rules;
        /*!< follow strict rules when writing to file. */
} DxfFile;


/*!
 * \brief DXF definition of a single linked list of char.
 */
typedef struct
dxf_char_struct
{
    char *value;
        /*!< Store the char value (string) here. */
    int length;
        /*!< Length of the stored char value (string). */
    struct DxfChar *next;
        /*!< Pointer to the next DxfChar.\n
         * \c NULL if the last DxfChar. */
} DxfChar;


/*!
 * \brief DXF definition of a single linked list of double variables.
 */
typedef struct
dxf_double_struct
{
    double value;
        /*!< Store the double value (real) here. */
    struct DxfDouble *next;
        /*!< Pointer to the next DxfDouble.\n
         * \c NULL if the last DxfDouble. */
} DxfDouble;


/*!
 * \brief DXF definition of a single linked list of int.
 */
typedef struct
dxf_int_struct
{
    int value;
        /*!< Store the int value here. */
    struct DxfInt *next;
        /*!< Pointer to the next DxfInt.\n
         * \c NULL if the last DxfInt. */
} DxfInt;


/*!
 * \brief DXF definition of a single linked list of int16_t.
 */
typedef struct
dxf_int16_struct
{
    int16_t value;
        /*!< Store the int16_t value here. */
    struct DxfInt16 *next;
        /*!< Pointer to the next DxfInt16.\n
         * \c NULL if the last DxfInt16. */
} DxfInt16;


/*!
 * \brief DXF definition of a single linked list of int32_t.
 */
typedef struct
dxf_int32_struct
{
    int32_t value;
        /*!< Store the int32_t value here. */
    struct DxfInt32 *next;
        /*!< Pointer to the next DxfInt32.\n
         * \c NULL if the last DxfInt32. */
} DxfInt32;


/*!
 * \brief DXF definition of a single linked list of int64_t.
 */
typedef struct
dxf_int64_struct
{
    int64_t value;
        /*!< Store the int64_t value here. */
    struct DxfInt64 *next;
        /*!< Pointer to the next DxfInt64.\n
         * \c NULL if the last DxfInt64. */
} DxfInt64;


/* AutoCAD(TM) versions by name */
#define AutoCAD_1_0 0
        /*!< \brief AutoCAD Version 1.0. */
#define AutoCAD_1_2 120
        /*!< \brief AutoCAD Version 1.2. */
#define AutoCAD_1_40 140
        /*!< \brief AutoCAD Version 1.40. */
#define AutoCAD_1_50 150
        /*!< \brief AutoCAD Version 2.05. */
#define AutoCAD_2_10 210
        /*!< \brief AutoCAD Version 2.10. */
#define AutoCAD_2_21 221
        /*!< \brief AutoCAD Version 2.21. */
/* 
#define AutoCAD_2_22 222
 */
#define AutoCAD_2_22 1001
        /*!< \brief AutoCAD Version 2.22. */
#define AutoCAD_2_50 1002
        /*!< \brief AutoCAD Version 2.50. */
#define AutoCAD_2_60 1003
        /*!< \brief AutoCAD Version 2.60. */
#define AutoCAD_9 1004
        /*!< \brief AutoCAD Release 9. */
#define AutoCAD_10 1006
        /*!< \brief AutoCAD 10. */
#define AutoCAD_11 1009
        /*!< \brief AutoCAD 11 & AutoCAD 12 == AutoCAD LT2. */
#define AutoCAD_12 1009
        /*!< \brief AutoCAD 11 & AutoCAD 12 == AutoCAD LT2. */
#define AutoCAD_13 1012
        /*!< \brief AutoCAD 13 == AutoCAD LT95. */
#define AutoCAD_14 1014
        /*!< \brief AutoCAD 14 == AutoCAD LT97 & LT98. */
#define AutoCAD_2000 1015
        /*!< \brief AutoCAD 2000. */
#define AutoCAD_2000i 1016
        /*!< \brief AutoCAD 2000i. */
#define AutoCAD_2002 1017
        /*!< \brief AutoCAD 2002. */
#define AutoCAD_2004 1018
        /*!< \brief AutoCAD 2004. */
#define AutoCAD_2005 1019
        /*!< \brief AutoCAD 2005. */
#define AutoCAD_2006 1020
        /*!< \brief AutoCAD 2006. */
#define AutoCAD_2007 1021
        /*!< \brief AutoCAD 2007. */
#define AutoCAD_2008 1022
        /*!< \brief AutoCAD 2008. */
#define AutoCAD_2009 1023
        /*!< \brief AutoCAD 2009. */
#define AutoCAD_2010 1024
        /*!< \brief AutoCAD 2010. */
#define AutoCAD_2011 1025
        /*!< \brief AutoCAD 2011. */
#define AutoCAD_2012 1026
        /*!< \brief AutoCAD 2012. */
#define AutoCAD_2013 1027
        /*!< \brief AutoCAD 2013. */
#define AutoCAD_LT2 1009
        /*!< \brief AutoCAD 11 & AutoCAD 12 == AutoCAD LT2. */
#define AutoCAD_LT95 1012
        /*!< \brief AutoCAD 13 == AutoCAD LT95. */
#define AutoCAD_LT97 1014
        /*!< \brief AutoCAD 14 == AutoCAD LT97 & LT98. */
#define AutoCAD_LT98 1014
        /*!< \brief AutoCAD 14 == AutoCAD LT97 & LT98. */

/* AutoCAD(TM) versions by version string */
#define MC0_0 0
        /*!< \brief AutoCAD Version 1.0. */
#define AC1_2 120
        /*!< \brief AutoCAD Version 1.2. */
#define AC1_40 140
        /*!< \brief AutoCAD Version 1.40. */
#define AC1_50 150
        /*!< \brief AutoCAD Version 2.05. */
#define AC2_10 210
        /*!< \brief AutoCAD Version 2.10. */
#define AC2_21 221
        /*!< \brief AutoCAD Version 2.21. */
#define AC2_22 222
        /*!< \brief AutoCAD Version 2.22.
         *
         * AC2_22 is an ignored tag. */
#define AC1001 1001
        /*!< \brief AutoCAD Version 2.22. */
#define AC1002 1002
        /*!< \brief AutoCAD Version 2.50. */
#define AC1003 1003
        /*!< \brief AutoCAD Version 2.60. */
#define AC1004 1004
        /*!< \brief AutoCAD Release 9. */
#define AC1006 1006
        /*!< \brief AutoCAD 10. */
#define AC1009 1009
        /*!< \brief AutoCAD 11 & AutoCAD 12 == AutoCAD LT2. */
#define AC1012 1012
        /*!< \brief AutoCAD 13 == AutoCAD LT95. */
#define AC1014 1014
        /*!< \brief AutoCAD 14 == AutoCAD LT97 & LT98. */
#define AC1015 1015
        /*!< \brief AutoCAD 2000. */
#define AC1016 1016
        /*!< \brief AutoCAD 2000i. */
#define AC1017 1017
        /*!< \brief AutoCAD 2002. */
#define AC1018 1018
        /*!< \brief AutoCAD 2004. */
#define AC1019 1019
        /*!< \brief AutoCAD 2005. */
#define AC1020 1020
        /*!< \brief AutoCAD 2006. */
#define AC1021 1021
        /*!< \brief AutoCAD 2007. */
#define AC1022 1022
        /*!< \brief AutoCAD 2008. */
#define AC1023 1023
        /*!< \brief AutoCAD 2009. */
#define AC1024 1024
        /*!< \brief AutoCAD 2010. */
#define AC1025 1025
        /*!< \brief AutoCAD 2011. */
#define AC1026 1026
        /*!< \brief AutoCAD 2012. */
#define AC1027 1027
        /*!< \brief AutoCAD 2013. */


#define DXF_MAX_PARAM 2000
        /*!< \brief The maximum of parameters in a \a DxfObject. */

#define DXF_MAX_NUMBER_OF_DASH_LENGTH_ITEMS 16
        /*!< \brief The maximum number of dash length items in a
         * \c DxfLType. */

#ifdef MSDOS
#  define DXF_MAX_STRING_LENGTH 255
        /*!< \brief The maximum string length.
         *
         * The maximum string length is 255 for DXF versions prior to
         * DXF release 2000 (also a MSDOS limit). */
#  define DXF_MAX_STRING_FORMAT "%254s\n"
        /*!< \brief The maximum string length format string.
         *
         * The maximum string length is 255 for DXF versions prior to
         * DXF release 2000 (also a MSDOS limit).
         *
         * \note one (1) char is reserved for '\0'. */
#else
#  define DXF_MAX_STRING_LENGTH 2049
        /*!< \brief The maximum string length.
         *
         * The maximum string length is 2049, as per DXF release 2000. */
#  define DXF_MAX_STRING_FORMAT "%2048s\n"
        /*!< \brief The maximum string length format string.
         *
         * The maximum string length is 2049, as per DXF release 2000.
         *
         * \note one (1) char is reserved for '\0'. */
#endif

#define DXF_COLOR_INDEX_MAX_NUMBER_OF_COLORS 256
        /*!< \brief The maximum number of colors in a \c DxfColorIndex. */

#define DXF_COLOR_BYBLOCK 0
        /*!< \brief DXF color definition, entities with this color
         * follow the color definition of the block in which it lives. */

#define DXF_COLOR_RED 1
        /*!< \brief DXF color definition, pen number "1" in the virtual
         * pen-plotter. */

#define DXF_COLOR_YELLOW 2
        /*!< \brief DXF color definition, pen number "2" in the virtual
         * pen-plotter. */

#define DXF_COLOR_GREEN 3
        /*!< \brief DXF color definition, pen number "3" in the virtual
         * pen-plotter. */

#define DXF_COLOR_CYAN 4
        /*!< \brief DXF color definition, pen number "4" in the virtual
         * pen-plotter. */

#define DXF_COLOR_BLUE 5
        /*!< \brief DXF color definition, pen number "5" in the virtual
         * pen-plotter. */

#define DXF_COLOR_MAGENTA 6
        /*!< \brief DXF color definition, pen number "6" in the virtual
         * pen-plotter. */

#define DXF_COLOR_WHITE 7
        /*!< \brief DXF color definition, pen number "7" in the virtual
         * pen-plotter. */

#define DXF_COLOR_GREY 8
        /*!< \brief DXF color definition, pen number "8" in the virtual
         * pen-plotter. */

#define DXF_COLOR_BYLAYER 256
        /*!< \brief DXF color definition, color of the entity follows
         * the color definition of the layer on which it lives. */

#define DXF_FLATLAND 0
        /*!< \brief Force compatibility with older versions (prior to
         * DXF R12) if nonzero, default value is 0. */

#define DXF_MODELER_FORMAT_CURRENT_VERSION 1
        /*!< \brief The current modeler format version. */

#define DXF_MODELSPACE (int16_t) 0
        /*!< \brief Model space.
         *
         * This is where our hardware is going to live, default
         * value, can be ommitted in dxf output. */

#define DXF_PAPERSPACE (int16_t) 1
        /*!< \brief Paper space.
         *
         * This is where your annotation (papersheet templates,
         * fab notes and such) should live, has to be included in DXF
         * output for entity to live on paperspace. */

#define DXF_DEFAULT_LAYER "0"
        /*!< \brief Default layer.
         *
         * There is <b>always</b> a layer "0" defined, it's
         * reasonably safe to assume that this is a valid layername. */

#define DXF_DEFAULT_LINETYPE "BYLAYER"
        /*!< \brief Default linetype.
         *
         * There is <b>always</b> a linetype "BYLAYER" defined,
         * it's reasonably safe to assume that this is a valid linetype. */

#define DXF_DEFAULT_LINETYPE_SCALE 1.0
        /*!< \brief The default linetype scale. */

#define DXF_DEFAULT_VISIBILITY 0
        /*!< \brief The default visibility. */

#define DXF_DEFAULT_PROXY_ENTITY_ID 498
        /*!< \brief The default proxy entity class id. */

#define DXF_DEFAULT_TEXTSTYLE "STANDARD"
        /*!< \brief Default text style name.
         *
         * There is <b>always</b> a textstyle "STANDARD" defined, it's
         * reasonably safe to assume that this is a valid text style. */

#define DXF_MAX_LAYERS 2048
        /*!< \brief The maximum number of layers in a dxf drawing file. */

#define DXF_IMAGEDEF_RESOLUTION_UNITS_MAX 5

#define DXF_IMAGEDEF_RESOLUTION_UNITS_MIN 0

#define DXF_VIEWPORT_APP_NAME "ACAD"
        /*!< \brief Application name.
         *
         * This field will always be the string "ACAD". */

#define DXF_VIEWPORT_DATA "MVIEW"
        /*!< \brief Begin viewport data.
         *
         * This field will always be the string "MVIEW". */

#define DXF_VIEWPORT_WINDOW_BEGIN "{"
        /*!< \brief Begin window data descriptor token.
         *
         * This field will always be the string "{". */

#define DXF_VIEWPORT_WINDOW_END "}"
        /*!< \brief End window data descriptor token.
         *
         * This field will always be the string "}". */

#define DXF_VIEWPORT_FROZEN_LAYER_LIST_BEGIN "{"
        /*!< \brief Begin token of the frozen layer list.
         *
         * This field will always be the string "{". */

#define DXF_VIEWPORT_FROZEN_LAYER_LIST_END "}"
        /*!< \brief End token of the frozen layer list.
         *
         * This field will always be the string "}". */

#define DXF_CHECK_BIT(var,pos) ((var & (1 << pos)) == (1 << pos))
        /*!< \brief Test bit is set. */

#define DXF_SYMBOL_TABLE_ENTRY_IS_EXTERNALLY_DEPENDANT 16
        /*!< \brief The symbol table entry is externally dependant on an
         * xref. */

#define DXF_SYMBOL_TABLE_ENTRY_DEPENDENCY_IS_RESOLVED 32
        /*!< \brief The symbol table entry external dependency on an
         * xref has been successfully resolved. */

#define DXF_SYMBOL_TABLE_ENTRY_IS_REFERENCED 64
        /*!< \brief The symbol table entry is referenced by at least one
         * entity in the drawing the last time the drawing was edited. */

#define DXF_VPORT_STANDARD_FLAG_MAX_VALUE 0x1111111
        /*!< \brief The maximum value for the standard flag in the VPORT
         * symbol table entry. */


#endif /* LIBDXF_SRC_GLOBAL_H */


/* EOF */
