/*!
 * \file dim.h
 * \author Copyright (C) 2008 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 * \brief Definition of a DXF dimension entity (\c DIM).
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

#include "global.h"

/*!
 * \brief DXF definition of an AutoCAD dimensioning style.
 */
typedef struct
dxf_dimstyle
{
        int id_code;
                /*!< group code = 5. */
        char *dimstyle_name;
                /*!< group code = 2\n
                 * dimension style name. */
        char *dimpost;
                /*!< group code = 3\n
                 * general dimensioning suffix. */
        char *dimapost;
                /*!< group code = 4\n
                 * alternate dimensioning suffix. */
        char *dimblk;
                /*!< group code = 5\n
                 * arrow block name. */
        char *dimblk1;
                /*!< group code = 6\n
                 * first arrow block name. */
        char *dimblk2;
                /*!< group code = 7\n
                 * second arrow block name. */
        double dimscale;
                /*!< group code = 40\n
                 * overall dimensioning scale factor. */
        double dimasz;
                /*!< group code = 41\n
                 * dimensioning arrow size. */
        double dimexo;
                /*!< group code = 42\n
                 * extension line offset. */
        double dimdli;
                /*!< group code = 43\n
                 * dimension line increment. */
        double dimexe;
                /*!< group code = 44\n
                 * extension line extension. */
        double dimrnd;
                /*!< group code = 45\n
                 * rounding value for dimension distances. */
        double dimdle;
                /*!< group code = 46\n
                 * dimension line extension. */
        double dimtp;
                /*!< group code = 47\n
                 * plus tolerance. */
        double dimtm;
                /*!< group code = 48\n
                 * minus tolerance. */
        int flag;
                /*!< group code = 70\n
                 * bit coded:\n
                 * 16 = if set, table entry is externally dependent on an
                 *      Xref.\n
                 * 32 = if this bit and bit 16 are both set, the externally
                 *      dependent Xref has been successfully resolved.\n
                 * 64 = if set, the table entry was referenced by at least
                 *      one entity in the drawing the last time the drawing
                 *      was edited.\n
                 * This flag is for the benefit of AutoCAD commands; it can
                 * be ignored by most programs that read DXF files, and need
                 * not be set by programs that write DXF files. */
        int dimtol;
                /*!< group code = 71\n
                 * dimension tolerances generated if nonzero. */
        int dimlim;
                /*!< group code = 72\n
                 * dimension limits generated if nonzero. */
        int dimtih;
                /*!< group code = 73\n
                 * text inside horizontal if nonzero. */
        int dimtoh;
                /*!< group code = 74\n
                 * text outside horizontal if nonzero. */
        int dimse1;
                /*!< group code = 75\n
                 * first extension line suppressed if nonzero. */
        int dimse2;
                /*!< group code = 76\n
                 * second extension line suppressed if nonzero. */
        int dimtad;
                /*!< group code = 77\n
                 * text above dimension line if nonzero. */
        int dimzin;
                /*!< group code = 78\n
                 * zero suppression for "feet & inch" dimensions. */
        double dimtxt;
                /*!< group code = 140\n
                 * dimensioning text height. */
        double dimcen;
                /*!< group code = 141\n
                 * size of center mark/lines. */
        double dimtsz;
                /*!< group code = 142\n
                 * dimensioning tick size: 0 = no ticks. */
        double dimaltf;
                /*!< group code = 143\n
                 * alternate unit scale factor. */
        double dimlfac;
                /*!< group code = 144\n
                 * linear measurements scale factor. */
        double dimtvp;
                /*!< group code = 145\n
                 * text vertical position. */
        double dimtfac;
                /*!< group code = 146\n
                 * dimension tolerance display scale factor. */
        double dimgap;
                /*!< group code = 147\n
                 * dimension line gap. */
        int dimalt;
                /*!< group code = 170\n
                 * alternate unit dimensioning performed if nonzero. */
        int dimaltd;
                /*!< group code = 171\n
                 * alternate unit decimal places. */
        int dimtofl;
                /*!< group code = 172\n
                 * if text outside extensions, force line extensions between
                 * extensions if nonzero. */
        int dimsah;
                /*!< group code = 173\n
                 * use separate arrow blocks if nonzero. */
        int dimtix;
                /*!< group code = 174\n
                 * force text inside extensions if nonzero. */
        int dimsoxd;
                /*!< group code = 175\n
                 * suppress outside-extensions dimension lines if nonzero. */
        int dimclrd;
                /*!< group code = 176\n
                 * dimension line color. */
        int dimclre;
                /*!< group code = 177\n
                 * dimension extension line color. */
        int dimclrt;
                /*!< group code = 178\n
                 * dimension text color. */
} DxfDimStyle, * DxfDimStylePtr;

DxfDimStyle *dxf_dimstyle_new ();


/* EOF */
