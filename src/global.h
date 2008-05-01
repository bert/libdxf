/*!
 * \file global.h
 * \author Copyright (C) 2008 by Bert Timmerman <bert.timmerman@xs4all.nl>.\n
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

#endif /* _GLOBAL_H */

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

/* AutoCAD(TM) versions by name */
#define AutoCAD_12 1009
#define AutoCAD_13 1012
#define AutoCAD_14 1014
#define AutoCAD_2000 1015
//#define AutoCAD_2002 101?
#define AutoCAD_2004 1018
#define AutoCAD_LT2 1009
#define AutoCAD_LT95 1012

/* AutoCAD(TM) versions by version string */
#define AC1009 1009
        /*!< AutoCAD 12 == AutoCAD LT2. */
#define AC1012 1012
        /*!< AutoCAD 13 == AutoCAD LT95. */
#define AC1014 1014
        /*!< AutoCAD 14. */
#define AC1015 1015
        /*!< AutoCAD 2000. */
#define AC1016 1016
#define AC1017 1017
#define AC1018 1018
        /*!< AutoCAD 2004. */

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

/* EOF */
