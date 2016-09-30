/*!
 * \file dimstyle.h
 *
 * \author Copyright (C) 2012 ... 2016 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Definition of a DXF dimension style table (\c DIMSTYLE).
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
 * For more details see http://www.autodesk.com.
 * <hr>
 */


#ifndef LIBDXF_SRC_DIMSTYLE_H
#define LIBDXF_SRC_DIMSTYLE_H


#include "global.h"


#ifdef __cplusplus
extern "C" {
#endif


/*!
 * \brief DXF definition of an AutoCAD dimensioning style.
 */
typedef struct
dxf_dimstyle_struct
{
        char *dimstyle_name;
                /*!< Dimension style name.\n
                 * Group code = 2. */
        char *dimpost;
                /*!< General dimensioning suffix.\n
                 * Group code = 3. */
        char *dimapost;
                /*!< Alternate dimensioning suffix.\n
                 * Group code = 4. */
        char *dimblk;
                /*!< Arrow block name, until R2000.\n
                 * Group code = 5. */
        char *dimblk1;
                /*!< First arrow block name, until R2000.\n
                 * Group code = 6. */
        char *dimblk2;
                /*!< Second arrow block name, until R2000.\n
                 * Group code = 7. */
        double dimscale;
                /*!< Overall dimensioning scale factor.\n
                 * Group code = 40. */
        double dimasz;
                /*!< Dimensioning arrow size.\n
                 * Group code = 41. */
        double dimexo;
                /*!< Extension line offset.\n
                 * Group code = 42. */
        double dimdli;
                /*!< Dimension line increment.\n
                 * Group code = 43. */
        double dimexe;
                /*!< Extension line extension.\n
                 * Group code = 44. */
        double dimrnd;
                /*!< Rounding value for dimension distances.\n
                 * Group code = 45. */
        double dimdle;
                /*!< Dimension line extension.\n
                 * Group code = 46. */
        double dimtp;
                /*!< Plus tolerance.\n
                 * Group code = 47. */
        double dimtm;
                /*!< Minus tolerance.\n
                 * Group code = 48. */
        int flag;
                /*!< This flag is for the benefit of AutoCAD commands;
                 * it can be ignored by most programs that read DXF
                 * files, and need not be set by programs that write DXF
                 * files.\n
                 * Bit coded:\n
                 * <ol>
                 * <li value = "16"> if set, table entry is externally dependent on an
                 *      Xref.</li>
                 * <li value = "32"> if this bit and bit 16 are both set, the externally
                 *      dependent Xref has been successfully resolved.</li>
                 * <li value = "64"> if set, the table entry was referenced by at least
                 *      one entity in the drawing the last time the drawing
                 *      was edited.</li>
                 * </ol>
                 * Group code = 70. */
        int dimtol;
                /*!< Dimension tolerances generated if nonzero.\n
                 * Group code = 71. */
        int dimlim;
                /*!< Dimension limits generated if nonzero.\n
                 * Group code = 72. */
        int dimtih;
                /*!< Text inside horizontal if nonzero.\n
                 * Group code = 73. */
        int dimtoh;
                /*!< Text outside horizontal if nonzero.\n
                 * Group code = 74. */
        int dimse1;
                /*!< First extension line suppressed if nonzero.\n
                 * Group code = 75. */
        int dimse2;
                /*!< Second extension line suppressed if nonzero.\n
                 * Group code = 76. */
        int dimtad;
                /*!< Text above dimension line if nonzero.\n
                 * Group code = 77. */
        int dimzin;
                /*!< Zero suppression for "feet & inch" dimensions.\n
                 * Group code = 78. */
        int id_code;
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the
                 * DXF file.\n
                 * Group code = 105. */
        double dimtxt;
                /*!< Dimensioning text height.\n
                 * Group code = 140. */
        double dimcen;
                /*!< Size of center mark/lines.\n
                 * Group code = 141. */
        double dimtsz;
                /*!< Dimensioning tick size: 0 = no ticks.\n
                 * Group code = 142. */
        double dimaltf;
                /*!< Alternate unit scale factor.\n
                 * Group code = 143. */
        double dimlfac;
                /*!< Linear measurements scale factor.\n
                 * Group code = 144. */
        double dimtvp;
                /*!< Text vertical position.\n
                 * Group code = 145. */
        double dimtfac;
                /*!< Dimension tolerance display scale factor.\n
                 * Group code = 146. */
        double dimgap;
                /*!< Dimension line gap.\n
                 * Group code = 147. */
        int dimalt;
                /*!< Alternate unit dimensioning performed if nonzero.\n
                 * Group code = 170. */
        int dimaltd;
                /*!< Alternate unit decimal places.\n
                 * Group code = 171. */
        int dimtofl;
                /*!< If text outside extensions, force line extensions
                 * between extensions if nonzero.\n
                 * Group code = 172. */
        int dimsah;
                /*!< Use separate arrow blocks if nonzero.\n
                 * Group code = 173. */
        int dimtix;
                /*!< Force text inside extensions if nonzero.\n
                 * Group code = 174. */
        int dimsoxd;
                /*!< Suppress outside-extensions dimension lines if
                 * nonzero.\n
                 * Group code = 175. */
        int dimclrd;
                /*!< Dimension line color.\n
                 * Group code = 176. */
        int dimclre;
                /*!< Dimension extension line color.\n
                 * Group code = 177. */
        int dimclrt;
                /*!< Dimension text color.\n
                 * Group code = 178. */
        int dimunit;
                /*!< Units format for all dimension style family members
                 * except angular:\n
                 * <ol>
                 * <li value = "1"> Scientific,</li>
                 * <li value = "2"> Decimal,</li>
                 * <li value = "3"> Engineering,</li>
                 * <li value = "4"> Architectural.</li>
                 * </ol>
                 * Group code = 270. */
        int dimdec;
                /*!< Number of decimal places for the tolerance values
                 * of a primary units dimension.\n
                 * Group code = 271. */
        int dimtdec;
                /*!< Number of decimal places to display the tolerance
                 * values.\n
                 * Group code = 272. */
        int dimaltu;
                /*!< Units format for alternate units of all dimension
                 * style family members except angular:
                 * <ol>
                 * <li value = "1"> Scientific,</li>
                 * <li value = "2"> Decimal,</li>
                 * <li value = "3"> Engineering,</li>
                 * <li value = "4"> Architectural.</li>
                 * </ol>
                 * Group code = 273. */
        int dimalttd;
                /*!< Number of decimal places for tolerance values of an
                 * alternate units dimension.\n
                 * Group code = 274. */
        int dimaunit;
                /*!< Angle format for angular dimensions:\n
                 * <ol>
                 * <li value = "0"> Decimal degrees,</li>
                 * <li value = "1"> Degrees/minutes/seconds,</li>
                 * <li value = "2"> Gradians,</li>
                 * <li value = "3"> Radians,</li>
                 * <li value = "4"> Surveyor's units.</li>
                 * </ol>
                 * Group code = 275. */
        int dimjust;
                /*!< Horizontal dimension text position:\n
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
                 * </ol>
                 * Group code = 280. */
        int dimsd1;
                /*!< Suppression of first extension line:\n
                 * <ol>
                 * <li value = "0"> not suppressed,</li>
                 * <li value = "1"> suppressed.</li>
                 * </ol>
                 * Group code = 281. */
        int dimsd2;
                /*!< Suppression of second extension line:\n
                 * <ol>
                 * <li value = "0"> not suppressed,</li>
                 * <li value = "1"> suppressed.</li>
                 * </ol>
                 * Group code = 282. */
        int dimtolj;
                /*!< Vertical justification for tolerance values:\n
                 * <ol>
                 * <li value = "0"> Top,</li>
                 * <li value = "1"> Middle,</li>
                 * <li value = "2"> Bottom.</li>
                 * </ol>
                 * Group code = 283. */
        int dimtzin;
                /*!< Suppression of zeros for tolerance values:\n
                 * <ol>
                 * <li value = "0"> not suppressed,</li>
                 * <li value = "1"> suppressed.</li>
                 * </ol>
                 * Group code = 284. */
        int dimaltz;
                /*!< Toggles suppression of zeros for alternate unit
                 * dimension values:\n
                 * <ol>
                 * <li value = "0"> zeros not suppressed,</li>
                 * <li value = "1"> zeros suppressed.</li>
                 * </ol>
                 * Group code = 285. */
        int dimalttz;
                /*!< Toggles suppression of zeros for tolerance values:\n
                 * <ol>
                 * <li value = "0"> zeros not suppressed,</li>
                 * <li value = "1"> zeros suppressed.</li>
                 * </ol>
                 * Group code = 286. */
        int dimfit;
                /*!< Placement of text and arrowheads; Possible values:\n
                 * 0 through 3 (see appendix A, "System Variables," in
                 * the AutoCAD Command Reference).\n
                 * Group code = 287. */
        int dimupt;
                /*!< Cursor functionality for user positioned text:\n
                 * <ol>
                 * <li value = "0"> controls only the dimension line
                 * location,</li>
                 * <li value = "1"> controls the text position as well as
                 * the dimension line location.</li>
                 * </ol>
                 * Group code = 288. */
        char *dimtxsty;
                /*!< Dimension text style.\n
                 * Group code = 340. */
        struct DxfDimStyle *next;
                /*!< Pointer to the next DxfDimStyle.\n
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
double
dxf_dimstyle_get_dimexo
(
        DxfDimStyle *dimstyle
);
DxfDimStyle *
dxf_dimstyle_set_dimexo
(
        DxfDimStyle *dimstyle,
        double dimexo
);
double
dxf_dimstyle_get_dimdli
(
        DxfDimStyle *dimstyle
);
DxfDimStyle *
dxf_dimstyle_set_dimdli
(
        DxfDimStyle *dimstyle,
        double dimdli
);
double
dxf_dimstyle_get_dimexe
(
        DxfDimStyle *dimstyle
);
DxfDimStyle *
dxf_dimstyle_set_dimexe
(
        DxfDimStyle *dimstyle,
        double dimexe
);
double
dxf_dimstyle_get_dimrnd
(
        DxfDimStyle *dimstyle
);
DxfDimStyle *
dxf_dimstyle_set_dimrnd
(
        DxfDimStyle *dimstyle,
        double dimrnd
);
double
dxf_dimstyle_get_dimdle
(
        DxfDimStyle *dimstyle
);
DxfDimStyle *
dxf_dimstyle_set_dimdle
(
        DxfDimStyle *dimstyle,
        double dimdle
);
double
dxf_dimstyle_get_dimtp
(
        DxfDimStyle *dimstyle
);
DxfDimStyle *
dxf_dimstyle_set_dimtp
(
        DxfDimStyle *dimstyle,
        double dimtp
);
double
dxf_dimstyle_get_dimtm
(
        DxfDimStyle *dimstyle
);
DxfDimStyle *
dxf_dimstyle_set_dimtm
(
        DxfDimStyle *dimstyle,
        double dimtm
);
int
dxf_dimstyle_get_flag
(
        DxfDimStyle *dimstyle
);
DxfDimStyle *
dxf_dimstyle_set_flag
(
        DxfDimStyle *dimstyle,
        int flag
);
int
dxf_dimstyle_get_dimtol
(
        DxfDimStyle *dimstyle
);
DxfDimStyle *
dxf_dimstyle_set_dimtol
(
        DxfDimStyle *dimstyle,
        int dimtol
);
int
dxf_dimstyle_get_dimlim
(
        DxfDimStyle *dimstyle
);
DxfDimStyle *
dxf_dimstyle_set_dimlim
(
        DxfDimStyle *dimstyle,
        int dimlim
);
int
dxf_dimstyle_get_dimtih
(
        DxfDimStyle *dimstyle
);
DxfDimStyle *
dxf_dimstyle_set_dimtih
(
        DxfDimStyle *dimstyle,
        int dimtih
);
int
dxf_dimstyle_get_dimtoh
(
        DxfDimStyle *dimstyle
);
DxfDimStyle *
dxf_dimstyle_set_dimtoh
(
        DxfDimStyle *dimstyle,
        int dimtoh
);
int
dxf_dimstyle_get_dimse1
(
        DxfDimStyle *dimstyle
);
DxfDimStyle *
dxf_dimstyle_set_dimse1
(
        DxfDimStyle *dimstyle,
        int dimse1
);
int
dxf_dimstyle_get_dimse2
(
        DxfDimStyle *dimstyle
);
DxfDimStyle *
dxf_dimstyle_set_dimse2
(
        DxfDimStyle *dimstyle,
        int dimse2
);
int
dxf_dimstyle_get_dimtad
(
        DxfDimStyle *dimstyle
);
DxfDimStyle *
dxf_dimstyle_set_dimtad
(
        DxfDimStyle *dimstyle,
        int dimtad
);
int
dxf_dimstyle_get_dimzin
(
        DxfDimStyle *dimstyle
);
DxfDimStyle *
dxf_dimstyle_set_dimzin
(
        DxfDimStyle *dimstyle,
        int dimzin
);
int
dxf_dimstyle_get_id_code
(
        DxfDimStyle *dimstyle
);
DxfDimStyle *
dxf_dimstyle_set_id_code
(
        DxfDimStyle *dimstyle,
        int id_code
);
double
dxf_dimstyle_get_dimtxt
(
        DxfDimStyle *dimstyle
);
DxfDimStyle *
dxf_dimstyle_set_dimtxt
(
        DxfDimStyle *dimstyle,
        double dimtxt
);
double
dxf_dimstyle_get_dimcen
(
        DxfDimStyle *dimstyle
);
DxfDimStyle *
dxf_dimstyle_set_dimcen
(
        DxfDimStyle *dimstyle,
        double dimcen
);
double
dxf_dimstyle_get_dimtsz
(
        DxfDimStyle *dimstyle
);
DxfDimStyle *
dxf_dimstyle_set_dimtsz
(
        DxfDimStyle *dimstyle,
        double dimtsz
);
double
dxf_dimstyle_get_dimaltf
(
        DxfDimStyle *dimstyle
);
DxfDimStyle *
dxf_dimstyle_set_dimaltf
(
        DxfDimStyle *dimstyle,
        double dimaltf
);
double
dxf_dimstyle_get_dimlfac
(
        DxfDimStyle *dimstyle
);
DxfDimStyle *
dxf_dimstyle_set_dimlfac
(
        DxfDimStyle *dimstyle,
        double dimlfac
);
double
dxf_dimstyle_get_dimtvp
(
        DxfDimStyle *dimstyle
);
DxfDimStyle *
dxf_dimstyle_set_dimtvp
(
        DxfDimStyle *dimstyle,
        double dimtvp
);
double
dxf_dimstyle_get_dimtfac
(
        DxfDimStyle *dimstyle
);
DxfDimStyle *
dxf_dimstyle_set_dimtfac
(
        DxfDimStyle *dimstyle,
        double dimtfac
);
double
dxf_dimstyle_get_dimgap
(
        DxfDimStyle *dimstyle
);
DxfDimStyle *
dxf_dimstyle_set_dimgap
(
        DxfDimStyle *dimstyle,
        double dimgap
);
int
dxf_dimstyle_get_dimalt
(
        DxfDimStyle *dimstyle
);
DxfDimStyle *
dxf_dimstyle_set_dimalt
(
        DxfDimStyle *dimstyle,
        int dimalt
);
int
dxf_dimstyle_get_dimaltd
(
        DxfDimStyle *dimstyle
);
DxfDimStyle *
dxf_dimstyle_set_dimaltd
(
        DxfDimStyle *dimstyle,
        int dimaltd
);
int
dxf_dimstyle_get_dimtofl
(
        DxfDimStyle *dimstyle
);
DxfDimStyle *
dxf_dimstyle_set_dimtofl
(
        DxfDimStyle *dimstyle,
        int dimtofl
);
int
dxf_dimstyle_get_dimsah
(
        DxfDimStyle *dimstyle
);
DxfDimStyle *
dxf_dimstyle_set_dimsah
(
        DxfDimStyle *dimstyle,
        int dimsah
);
int
dxf_dimstyle_get_dimtix
(
        DxfDimStyle *dimstyle
);
DxfDimStyle *
dxf_dimstyle_set_dimtix
(
        DxfDimStyle *dimstyle,
        int dimtix
);
int
dxf_dimstyle_get_dimsoxd
(
        DxfDimStyle *dimstyle
);
DxfDimStyle *
dxf_dimstyle_set_dimsoxd
(
        DxfDimStyle *dimstyle,
        int dimsoxd
);
int
dxf_dimstyle_get_dimclrd
(
        DxfDimStyle *dimstyle
);
DxfDimStyle *
dxf_dimstyle_set_dimclrd
(
        DxfDimStyle *dimstyle,
        int dimclrd
);
int
dxf_dimstyle_get_dimclre
(
        DxfDimStyle *dimstyle
);
DxfDimStyle *
dxf_dimstyle_set_dimclre
(
        DxfDimStyle *dimstyle,
        int dimclre
);
int
dxf_dimstyle_get_dimclrt
(
        DxfDimStyle *dimstyle
);
DxfDimStyle *
dxf_dimstyle_set_dimclrt
(
        DxfDimStyle *dimstyle,
        int dimclrt
);
int
dxf_dimstyle_get_dimunit
(
        DxfDimStyle *dimstyle
);
DxfDimStyle *
dxf_dimstyle_set_dimunit
(
        DxfDimStyle *dimstyle,
        int dimunit
);
int
dxf_dimstyle_get_dimdec
(
        DxfDimStyle *dimstyle
);
DxfDimStyle *
dxf_dimstyle_set_dimdec
(
        DxfDimStyle *dimstyle,
        int dimdec
);
int
dxf_dimstyle_get_dimtdec
(
        DxfDimStyle *dimstyle
);
DxfDimStyle *
dxf_dimstyle_set_dimtdec
(
        DxfDimStyle *dimstyle,
        int dimtdec
);
int
dxf_dimstyle_get_dimaltu
(
        DxfDimStyle *dimstyle
);
DxfDimStyle *
dxf_dimstyle_set_dimaltu
(
        DxfDimStyle *dimstyle,
        int dimaltu
);
int
dxf_dimstyle_get_dimalttd
(
        DxfDimStyle *dimstyle
);
DxfDimStyle *
dxf_dimstyle_set_dimalttd
(
        DxfDimStyle *dimstyle,
        int dimalttd
);
int
dxf_dimstyle_get_dimaunit
(
        DxfDimStyle *dimstyle
);
DxfDimStyle *
dxf_dimstyle_set_dimaunit
(
        DxfDimStyle *dimstyle,
        int dimaunit
);
int
dxf_dimstyle_get_dimjust
(
        DxfDimStyle *dimstyle
);
DxfDimStyle *
dxf_dimstyle_set_dimjust
(
        DxfDimStyle *dimstyle,
        int dimjust
);
int
dxf_dimstyle_get_dimsd1
(
        DxfDimStyle *dimstyle
);
DxfDimStyle *
dxf_dimstyle_set_dimsd1
(
        DxfDimStyle *dimstyle,
        int dimsd1
);
int
dxf_dimstyle_get_dimsd2
(
        DxfDimStyle *dimstyle
);
DxfDimStyle *
dxf_dimstyle_set_dimsd2
(
        DxfDimStyle *dimstyle,
        int dimsd2
);
int
dxf_dimstyle_get_dimtolj
(
        DxfDimStyle *dimstyle
);
DxfDimStyle *
dxf_dimstyle_set_dimtolj
(
        DxfDimStyle *dimstyle,
        int dimtolj
);
int
dxf_dimstyle_get_dimtzin
(
        DxfDimStyle *dimstyle
);
DxfDimStyle *
dxf_dimstyle_set_dimtzin
(
        DxfDimStyle *dimstyle,
        int dimtzin
);
int
dxf_dimstyle_get_dimaltz
(
        DxfDimStyle *dimstyle
);
DxfDimStyle *
dxf_dimstyle_set_dimaltz
(
        DxfDimStyle *dimstyle,
        int dimaltz
);
int
dxf_dimstyle_get_dimalttz
(
        DxfDimStyle *dimstyle
);
DxfDimStyle *
dxf_dimstyle_set_dimalttz
(
        DxfDimStyle *dimstyle,
        int dimalttz
);
int
dxf_dimstyle_get_dimfit
(
        DxfDimStyle *dimstyle
);
DxfDimStyle *
dxf_dimstyle_set_dimfit
(
        DxfDimStyle *dimstyle,
        int dimfit
);
int
dxf_dimstyle_get_dimupt
(
        DxfDimStyle *dimstyle
);
DxfDimStyle *
dxf_dimstyle_set_dimupt
(
        DxfDimStyle *dimstyle,
        int dimupt
);
char *
dxf_dimstyle_get_dimtxsty
(
        DxfDimStyle *dimstyle
);
DxfDimStyle *
dxf_dimstyle_set_dimtxsty
(
        DxfDimStyle *dimstyle,
        char *dimtxsty
);
DxfDimStyle *
dxf_dimstyle_get_next
(
        DxfDimStyle *dimstyle
);
DxfDimStyle *
dxf_dimstyle_set_next
(
        DxfDimStyle *dimstyle,
        DxfDimStyle *next
);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_DIMSTYLE_H */


/* EOF */
