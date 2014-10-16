/*!
 * \file global.h
 *
 * \author Copyright (C) 2008 ... 2014 by Bert Timmerman <bert.timmerman@xs4all.nl>.\n
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
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <math.h>
#include <errno.h>

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

#include "entity.h"

/*!
 * MS DOS - compilers
 *
 * use #define MSDOS if not defined by compiler or cases below.
 *
 * Microsoft C auto-defines MSDOS
 *
 * Borland C   auto-defines __MSDOS__
 *
 * DJGPP       auto-defines MSDOS
 */
#ifdef __MSDOS__
#  ifndef MSDOS
#    define MSDOS
#  endif
#endif

/*!
 * Increase Borland C compatibility in libraries.
 */
#ifdef __TURBOC__
#  define __MSC
#endif

#ifdef MSDOS
#  undef UNIX
#endif

 /*!
 * Verbose debugging output to \c stderr on/off toggle.
 *
 * If not already defined as a compiler directive the default value is
 * 0 (off).
 */
#ifndef DEBUG
#  define DEBUG 0
#endif

/*!
 * Toggle for an interactive prompt during run time.
 */
#define INTER_ACTIVE_PROMPT 1

/*!
 * True is 1.
 */
#ifndef TRUE
#  define TRUE 1
#endif

/*!
 * False is 0.
 */
#ifndef FALSE
#  define FALSE 0
#endif

/*!
 * \brief Verbose debugging output to \c stderr.
 *
 * Compile with -DDEBUG compiler directive enabled.
 */
#define DXF_DEBUG_BEGIN \
        fprintf (stderr, \
          (_("[File: %s: line: %d] Entering %s () function.\n")), \
          __FILE__, __LINE__, __FUNCTION__);

/*!
 * \brief Verbose debugging output to \c stderr.
 *
 * Compile with -DDEBUG compiler directive enabled.
 */
#define DXF_DEBUG_END \
        fprintf (stderr, \
          (_("[File: %s: line: %d] Leaving %s () function.\n")), \
          __FILE__, __LINE__, __FUNCTION__);


/*!
 * \brief DXF definition of a DXF file.
 */
typedef struct
dxf_file
{
    FILE *fp;
        /*!< File handle. */
    char *filename;
        /*!< Dxf filename. */
    int line_number;
        /*!< Last line read. */
    int acad_version_number;
        /*!< AutoCAD version number. */
} DxfFile, * DxfFilePtr;


/* AutoCAD(TM) versions by name */
#define AutoCAD_1_0 0
        /*!< AutoCAD Version 1.0. */
#define AutoCAD_1_2 120
        /*!< AutoCAD Version 1.2. */
#define AutoCAD_1_40 140
        /*!< AutoCAD Version 1.40. */
#define AutoCAD_1_50 150
        /*!< AutoCAD Version 2.05. */
#define AutoCAD_2_10 210
        /*!< AutoCAD Version 2.10. */
#define AutoCAD_2_21 221
        /*!< AutoCAD Version 2.21. */
/* 
#define AutoCAD_2_22 222
 */
#define AutoCAD_2_22 1001
        /*!< AutoCAD Version 2.22. */
#define AutoCAD_2_50 1002
        /*!< AutoCAD Version 2.50. */
#define AutoCAD_2_60 1003
        /*!< AutoCAD Version 2.60. */
#define AutoCAD_9 1004
        /*!< AutoCAD Release 9. */
#define AutoCAD_10 1006
        /*!< AutoCAD 10. */
#define AutoCAD_11 1009
        /*!< AutoCAD 11 & AutoCAD 12 == AutoCAD LT2. */
#define AutoCAD_12 1009
        /*!< AutoCAD 11 & AutoCAD 12 == AutoCAD LT2. */
#define AutoCAD_13 1012
        /*!< AutoCAD 13 == AutoCAD LT95. */
#define AutoCAD_14 1014
        /*!< AutoCAD 14 == AutoCAD LT97 & LT98. */
#define AutoCAD_2000 1015
        /*!< AutoCAD 2000. */
#define AutoCAD_2000i 1016
        /*!< AutoCAD 2000i. */
#define AutoCAD_2002 1017
        /*!< AutoCAD 2002. */
#define AutoCAD_2004 1018
        /*!< AutoCAD 2004. */
#define AutoCAD_2005 1019
        /*!< AutoCAD 2005. */
#define AutoCAD_2006 1020
        /*!< AutoCAD 2006. */
#define AutoCAD_2007 1021
        /*!< AutoCAD 2007. */
#define AutoCAD_2008 1022
        /*!< AutoCAD 2008. */
#define AutoCAD_2009 1023
        /*!< AutoCAD 2009. */
#define AutoCAD_2010 1024
        /*!< AutoCAD 2010. */
#define AutoCAD_2011 1025
        /*!< AutoCAD 2011. */
#define AutoCAD_2012 1026
        /*!< AutoCAD 2012. */
#define AutoCAD_2013 1027
        /*!< AutoCAD 2013. */
#define AutoCAD_LT2 1009
        /*!< AutoCAD 11 & AutoCAD 12 == AutoCAD LT2. */
#define AutoCAD_LT95 1012
        /*!< AutoCAD 13 == AutoCAD LT95. */
#define AutoCAD_LT97 1014
        /*!< AutoCAD 14 == AutoCAD LT97 & LT98. */
#define AutoCAD_LT98 1014
        /*!< AutoCAD 14 == AutoCAD LT97 & LT98. */

/* AutoCAD(TM) versions by version string */
#define MC0_0 0
        /*!< AutoCAD Version 1.0. */
#define AC1_2 120
        /*!< AutoCAD Version 1.2. */
#define AC1_40 140
        /*!< AutoCAD Version 1.40. */
#define AC1_50 150
        /*!< AutoCAD Version 2.05. */
#define AC2_10 210
        /*!< AutoCAD Version 2.10. */
#define AC2_21 221
        /*!< AutoCAD Version 2.21. */
#define AC2_22 222
        /*!< AutoCAD Version 2.22. \n
         * AC2_22 is an ignored tag. */
#define AC1001 1001
        /*!< AutoCAD Version 2.22. */
#define AC1002 1002
        /*!< AutoCAD Version 2.50. */
#define AC1003 1003
        /*!< AutoCAD Version 2.60. */
#define AC1004 1004
        /*!< AutoCAD Release 9. */
#define AC1006 1006
        /*!< AutoCAD 10. */
#define AC1009 1009
        /*!< AutoCAD 11 & AutoCAD 12 == AutoCAD LT2. */
#define AC1012 1012
        /*!< AutoCAD 13 == AutoCAD LT95. */
#define AC1014 1014
        /*!< AutoCAD 14 == AutoCAD LT97 & LT98. */
#define AC1015 1015
        /*!< AutoCAD 2000. */
#define AC1016 1016
        /*!< AutoCAD 2000i. */
#define AC1017 1017
        /*!< AutoCAD 2002. */
#define AC1018 1018
        /*!< AutoCAD 2004. */
#define AC1019 1019
        /*!< AutoCAD 2005. */
#define AC1020 1020
        /*!< AutoCAD 2006. */
#define AC1021 1021
        /*!< AutoCAD 2007. */
#define AC1022 1022
        /*!< AutoCAD 2008. */
#define AC1023 1023
        /*!< AutoCAD 2009. */
#define AC1024 1024
        /*!< AutoCAD 2010. */
#define AC1025 1025
        /*!< AutoCAD 2011. */
#define AC1026 1026
        /*!< AutoCAD 2012. */
#define AC1027 1027
        /*!< AutoCAD 2013. */


/*!
 * The maximum of parameters in a \a DxfObject
 */
#define DXF_MAX_PARAM 2000

/*!
 * The maximum number of dash length items in a \a DxfLType
 */
#define DXF_MAX_NUMBER_OF_DASH_LENGTH_ITEMS 16

/*!
 * The maximum string length is 255 for DXF versions prior to DXF
 * release 2000 (also a MSDOS limit).\n
 * The maximum extended string length is 2049, as per DXF release 2000.
 */
#ifdef MSDOS
#  define DXF_MAX_STRING_LENGTH 255
#else
#  define DXF_MAX_STRING_LENGTH 2049
#endif

/*!
 * The maximum number of colors in a \c DxfColorIndex.
 */
#define DXF_COLOR_INDEX_MAX_NUMBER_OF_COLORS 256

/*!
 * \brief DXF color definition, entities with this color follow the color
 * definition of the block in which it lives.
 */
#define DXF_COLOR_BYBLOCK 0

/*!
 * \brief DXF color definition, pen number "1" in the virtual pen-plotter.
 */
#define DXF_COLOR_RED 1

/*!
 * \brief DXF color definition, pen number "2" in the virtual pen-plotter.
 */
#define DXF_COLOR_YELLOW 2

/*!
 * \brief DXF color definition, pen number "3" in the virtual pen-plotter.
 */
#define DXF_COLOR_GREEN 3

/*!
 * \brief DXF color definition, pen number "4" in the virtual pen-plotter.
 */
#define DXF_COLOR_CYAN 4

/*!
 * \brief DXF color definition, pen number "5" in the virtual pen-plotter.
 */
#define DXF_COLOR_BLUE 5

/*!
 * \brief DXF color definition, pen number "6" in the virtual pen-plotter.
 */
#define DXF_COLOR_MAGENTA 6

/*!
 * \brief DXF color definition, pen number "7" in the virtual pen-plotter.
 */
#define DXF_COLOR_WHITE 7

/*!
 * \brief DXF color definition, pen number "8" in the virtual pen-plotter.
 */
#define DXF_COLOR_GREY 8

/*!
 * \brief DXF color definition, color of the entity follows the color
 * definition of the layer on which it lives.
 */
#define DXF_COLOR_BYLAYER 256

/*!
 * \brief Force compatibility with older versions (prior to DXF R12) if
 * nonzero, default value is 0.
 */
#define DXF_FLATLAND 0

/*!
 * \brief This is where our hardware is going to live, default value, can be
 * ommitted in dxf output.
 */
#define DXF_MODELSPACE 0

/*!
 * \brief This is where your annotation (papersheet templates, fab notes and
 * such) should live, has to be included in dxf output for entity to live on
 * paperspace.
 */
#define DXF_PAPERSPACE 1

/*!
 * \brief There is <b>always</b> a layer "0" defined, it's reasonably safe to
 * assume that this is a valid layername.
 */
#define DXF_DEFAULT_LAYER "0"

/*!
 * \brief There is <b>always</b> a linetype "BYLAYER" defined, it's
 * reasonably safe to assume that this is a valid linetype.
 */
#define DXF_DEFAULT_LINETYPE "BYLAYER"

/*!
 * \brief The default linetype scale.
 */
#define DXF_DEFAULT_LINETYPE_SCALE 1.0

/*!
 * \brief The default visibility.
 */
#define DXF_DEFAULT_VISIBILITY 0

/*!
 * \brief The default proxy entity class id.
 */
#define DXF_DEFAULT_PROXY_ENTITY_ID 498

/*!
 * \brief There is <b>always</b> a textstyle "STANDARD" defined, it's
 * reasonably safe to assume that this is a valid text style.
 */
#define DXF_DEFAULT_TEXTSTYLE "STANDARD"

/*!
 * \brief The maximum number of layers in a dxf drawing file.
 */
#define DXF_MAX_LAYERS 2048

/*!
 * \brief Application name.\n
 * This field will always be the string "ACAD".
 */
#define DXF_VIEWPORT_APP_NAME "ACAD"

/*!
 * \brief Begin viewport data.\n
 * This field will always be the string "MVIEW".
 */
#define DXF_VIEWPORT_DATA "MVIEW"

/*!
 * \brief Begin window data descriptor token.\n
 * This field will always be the string "{".
 */
#define DXF_VIEWPORT_WINDOW_BEGIN "{"

/*!
 * \brief End window data descriptor token.\n
 * This field will always be the string "}".
 */
#define DXF_VIEWPORT_WINDOW_END "}"

/*!
 * \brief Begin token of the frozen layer list.\n
 * This field will always be the string "{".
 */
#define DXF_VIEWPORT_FROZEN_LAYER_LIST_BEGIN "{"

/*!
 * \brief End token of the frozen layer list.\n
 * This field will always be the string "}".
 */
#define DXF_VIEWPORT_FROZEN_LAYER_LIST_END "}"

/*!
 * \brief Test bit is set.
 */
#define DXF_CHECK_BIT(var,pos) ((var & (1 << pos)) == (1 << pos))


#endif /* LIBDXF_SRC_GLOBAL_H */


/* EOF */
