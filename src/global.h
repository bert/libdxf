/*!
 * \file global.h
 * \author Copyright (C) 2008, 2010 by Bert Timmerman <bert.timmerman@xs4all.nl>.\n
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
#ifndef _GLOBAL_H
#define _GLOBAL_H

#include <stdio.h>
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


/*!
 * Debugging on/off toggle.
 */
#define DEBUG 1

/*!
 * Toggle for an interactive prompt during run time.
 */
#define INTER_ACTIVE_PROMPT 1

#define TRUE 1

#define FALSE 0


/*!
 * \brief DXF definition of a DXF file.
 */
typedef struct
dxf_file
{
    FILE *fp; /*!< File handle */
    char *filename; /*!< Dxf filename */
    int line_number; /*!< Last line read */
} DxfFile, * DxfFilePtr;


/* AutoCAD(TM) versions by name */
#define AutoCAD_10 1006
#define AutoCAD_11 1009
#define AutoCAD_12 1009
#define AutoCAD_13 1012
#define AutoCAD_14 1014
#define AutoCAD_2000 1015
#define AutoCAD_2002 1016
#define AutoCAD_2004 1018
#define AutoCAD_2005 1019
#define AutoCAD_2006 1020
#define AutoCAD_2007 1021
#define AutoCAD_2008 1022
#define AutoCAD_2009 1023
#define AutoCAD_2010 1024
#define AutoCAD_2011 1025
#define AutoCAD_LT2 1009
#define AutoCAD_LT95 1012

/* AutoCAD(TM) versions by version string */
#define AC1006 1006
        /*!< AutoCAD 10. */
#define AC1009 1009
        /*!< AutoCAD 12 == AutoCAD LT2. */
#define AC1012 1012
        /*!< AutoCAD 13 == AutoCAD LT95. */
#define AC1014 1014
        /*!< AutoCAD 14. */
#define AC1015 1015
        /*!< AutoCAD 2000. */
#define AC1016 1016
        /*!< AutoCAD 2002. */
#define AC1017 1017
        /*!< AutoCAD version ?. */
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

/*!
 * The maximum of parameters in a \a DxfObject
 */
#define DXF_MAX_PARAM 2000

/*!
 * The maximum number of dash length items in a \a DxfLType
 */
#define DXF_MAX_NUMBER_OF_DASH_LENGTH_ITEMS 16

/*!
 * The maximum string length (it is a MSDOS limit).
 */
#define DXF_MAX_STRING_LENGTH 255

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
 * This field will always be the string "MVIEW".\n
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


#endif /* _GLOBAL_H */


/* EOF */
