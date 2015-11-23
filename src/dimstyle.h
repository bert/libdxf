/*!
 * \file dimstyle.h
 *
 * \author Copyright (C) 2012 ... 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Definition of a DXF dimension style table (\c DIMSTYLE).
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


#ifndef LIBDXF_SRC_DIMSTYLE_H
#define LIBDXF_SRC_DIMSTYLE_H


#include "global.h"


/*!
 * \brief DXF definition of an AutoCAD dimensioning style.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
typedef struct
dxf_dimstyle
{
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
                 * arrow block name, until R2000. */
        char *dimblk1;
                /*!< group code = 6\n
                 * first arrow block name, until R2000. */
        char *dimblk2;
                /*!< group code = 7\n
                 * second arrow block name, until R2000. */
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
                 * <ol>
                 * <li value = "16"> if set, table entry is externally dependent on an
                 *      Xref.</li>
                 * <li value = "32"> if this bit and bit 16 are both set, the externally
                 *      dependent Xref has been successfully resolved.</li>
                 * <li value = "64"> if set, the table entry was referenced by at least
                 *      one entity in the drawing the last time the drawing
                 *      was edited.</li>
                 * </ol>
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
        int id_code;
                /*!< group code = 105\n
                 * Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the
                 * DXF file. */
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
        int dimunit;
                /*!< group code = 270\n
                 * Units format for all dimension style family members
                 * except angular:\n
                 * <ol>
                 * <li value = "1"> Scientific,</li>
                 * <li value = "2"> Decimal,</li>
                 * <li value = "3"> Engineering,</li>
                 * <li value = "4"> Architectural.</li>
                 * </ol> */
        int dimdec;
                /*!< group code = 271\n
                 * Number of decimal places for the tolerance values of
                 * a primary units dimension. */
        int dimtdec;
                /*!< group code = 272\n
                 * Number of decimal places to display the tolerance
                 * values. */
        int dimaltu;
                /*!< group code = 273\n
                 * Units format for alternate units of all dimension
                 * style family members except angular:
                 * <ol>
                 * <li value = "1"> Scientific,</li>
                 * <li value = "2"> Decimal,</li>
                 * <li value = "3"> Engineering,</li>
                 * <li value = "4"> Architectural.</li>
                 * </ol> */
        int dimalttd;
                /*!< group code = 274\n
                 * Number of decimal places for tolerance values of an
                 * alternate units dimension. */
        int dimaunit;
                /*!< group code = 275\n
                 * Angle format for angular dimensions:\n
                 * <ol>
                 * <li value = "0"> Decimal degrees,</li>
                 * <li value = "1"> Degrees/minutes/seconds,</li>
                 * <li value = "2"> Gradians,</li>
                 * <li value = "3"> Radians,</li>
                 * <li value = "4"> Surveyor's units.</li>
                 * </ol> */
        int dimjust;
                /*!< group code = 280\n
                 * Horizontal dimension text position:\n
                 * <ol>
                 * <li value = "0"> above dimension line and
                 * center-justified between extension lines,</li>
                 * <li value = "1"> above dimension line and next to first
                 * extension line,</li>
                 * <li value = "2"> above dimension line and next to
                 * second extension line,</li>
                 * <li value = "3"> above and center-justified to first
                 * extension line,</li>
                 * <li value = "4"> above and center-justified to second
                 * extension line.</li>
                 * </ol> */
        int dimsd1;
                /*!< group code = 281\n
                 * Suppression of first extension line:\n
                 * <ol>
                 * <li value = "0"> not suppressed,</li>
                 * <li value = "1"> suppressed.</li>
                 * </ol> */
        int dimsd2;
                /*!< group code = 282\n
                 * Suppression of second extension line:\n
                 * <ol>
                 * <li value = "0"> not suppressed,</li>
                 * <li value = "1"> suppressed.</li>
                 * </ol> */
        int dimtolj;
                /*!< group code = 283\n
                 * Vertical justification for tolerance values:\n
                 * <ol>
                 * <li value = "0"> Top,</li>
                 * <li value = "1"> Middle,</li>
                 * <li value = "2"> Bottom.</li>
                 * </ol> */
        int dimtzin;
                /*!< group code = 284\n
                 * Suppression of zeros for tolerance values:\n
                 * <ol>
                 * <li value = "0"> not suppressed,</li>
                 * <li value = "1"> suppressed.</li>
                 * </ol> */
        int dimaltz;
                /*!< group code = 285\n
                 * Toggles suppression of zeros for alternate unit
                 * dimension values:\n
                 * <ol>
                 * <li value = "0"> zeros not suppressed,</li>
                 * <li value = "1"> zeros suppressed.</li>
                 * </ol> */
        int dimalttz;
                /*!< group code = 286\n
                 * Toggles suppression of zeros for tolerance values:\n
                 * <ol>
                 * <li value = "0"> zeros not suppressed,</li>
                 * <li value = "1"> zeros suppressed.</li>
                 * </ol> */
        int dimfit;
                /*!< group code = 287\n
                 * Placement of text and arrowheads; Possible values:\n
                 * 0 through 3 (see appendix A, "System Variables," in
                 * the AutoCAD Command Reference). */
        int dimupt;
                /*!< group code = 288\n
                 * Cursor functionality for user positioned text:\n
                 * <ol>
                 * <li value = "0"> controls only the dimension line
                 * location,</li>
                 * <li value = "1"> controls the text position as well as
                 * the dimension line location.</li>
                 * </ol> */
        int dimtxsty;
                /*!< group code = 340\n
                 * Dimension text style. */
        struct DxfDimStyle *next;
                /*!< pointer to the next DxfDimStyle.\n
                 * \c NULL in the last DxfDimStyle. */
} DxfDimStyle;


DxfDimStyle *dxf_dimstyle_new ();
DxfDimStyle *dxf_dimstyle_init
(
        DxfDimStyle *dimstyle
);
int dxf_dimstyle_write
(
        DxfFile *fp,
        DxfDimStyle *dimstyle
);
DxfDimStyle *dxf_dimstyle_read
(
        DxfFile *fp,
        DxfDimStyle *dimstyle
);
int dxf_dimstyle_free
(
        DxfDimStyle *dimstyle
);
void
dxf_dimstyle_free_chain
(
        DxfDimStyle *dimstyles
);
char *
dxf_dimstyle_get_dimstyle_name
(
        DxfDimStyle *dimstyle
);
DxfDimStyle *
dxf_dimstyle_set_dimstyle_name
(
        DxfDimStyle *dimstyle,
        char *dimstyle_name
);
char *
dxf_dimstyle_get_dimpost
(
        DxfDimStyle *dimstyle
);
DxfDimStyle *
dxf_dimstyle_set_dimpost
(
        DxfDimStyle *dimstyle,
        char *dimpost
);
char *
dxf_dimstyle_get_dimapost
(
        DxfDimStyle *dimstyle
);
DxfDimStyle *
dxf_dimstyle_set_dimapost
(
        DxfDimStyle *dimstyle,
        char *dimapost
);
char *
dxf_dimstyle_get_dimblk
(
        DxfDimStyle *dimstyle
);
DxfDimStyle *
dxf_dimstyle_set_dimblk
(
        DxfDimStyle *dimstyle,
        char *dimblk
);
char *
dxf_dimstyle_get_dimblk1
(
        DxfDimStyle *dimstyle
);
DxfDimStyle *
dxf_dimstyle_set_dimblk1
(
        DxfDimStyle *dimstyle,
        char *dimblk1
);
char *
dxf_dimstyle_get_dimblk2
(
        DxfDimStyle *dimstyle
);
DxfDimStyle *
dxf_dimstyle_set_dimblk2
(
        DxfDimStyle *dimstyle,
        char *dimblk2
);
double
dxf_dimstyle_get_dimscale
(
        DxfDimStyle *dimstyle
);
DxfDimStyle *
dxf_dimstyle_set_dimscale
(
        DxfDimStyle *dimstyle,
        double dimscale
);
double
dxf_dimstyle_get_dimasz
(
        DxfDimStyle *dimstyle
);
DxfDimStyle *
dxf_dimstyle_set_dimasz
(
        DxfDimStyle *dimstyle,
        double dimasz
);


#endif /* LIBDXF_SRC_DIMSTYLE_H */


/* EOF */
