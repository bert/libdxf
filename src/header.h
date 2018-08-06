/*!
 * \file header.h
 *
 * \author Copyright (C) 2008, 2009, 2010, 2014, 2015, 2016, 2017, 2018
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.\n
 *
 * \author Copyright (C) 2010 by Luis Matos <gass@otiliamatos.ath.cx>.
 *
 * \brief Definition of a DXF header section.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
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


#ifndef LIBDXF_SRC_HEADER_H
#define LIBDXF_SRC_HEADER_H


#include "global.h"
#include "point.h"
#include "endsec.h"


#ifdef __cplusplus
extern "C" {
#endif


typedef struct
dxf_header_struct
{
        int id_code;
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file.\n
                 * Group code = 5. */
        char *AcadVer;
                /*!< */
        int _AcadVer;
                /*!< The AutoCAD drawing database version number:
                 * <ul>
                 *   <li>AC1006 = R10.</li>
                 *   <li>AC1009 = R11 and R12.</li>
                 *   <li>AC1012 = R13.</li>
                 *   <li>AC1014 = R14.</li>
                 *   <li>AC1015 = AutoCAD 2000.</li>
                 *   <li>AC1018 = AutoCAD 2004.</li>
                 *   <li>AC1021 = AutoCAD 2007.</li>
                 *   <li>AC1024 = AutoCAD 2010.</li>
                 *   <li>AC1027 = AutoCAD 2013.</li>
                 * </ul>
                 * Group code = 1. */
        int AcadMaintVer;
                /*!< Maintenance version number (should be ignored).\n
                 * Group code = 70. */
        char *DWGCodePage;
                /*!< Drawing code page.\n
                 * Set to the system code page when a new drawing is
                 * created, but not otherwise maintained by AutoCAD.\n
                 * Group code =  */
        DxfPoint InsBase;
                /*!< */
        DxfPoint ExtMin;
                /*!< */
        DxfPoint ExtMax;
                /*!< */
        DxfPoint LimMin;
                /*!< */
        DxfPoint LimMax;
                /*!< */
        int OrthoMode;
                /*!< */
        int RegenMode;
                /*!< */
        int FillMode;
                /*!< */
        int QTextMode;
                /*!< */
        int MirrText;
                /*!< */
        int DragMode;
                /*!< */
        double LTScale;
                /*!< */
        int OSMode;
                /*!< */
        int AttMode;
                /*!< Attribute visibility:
                 * <ol>
                 *   <li value = 0> None.</li>
                 *   <li value = 1> Normal.</li>
                 *   <li value = 2> All.</li>
                 * </ol>
                 * Group code = 70. */
        double TextSize;
                /*!< */
        double TraceWid;
                /*!< */
        char *TextStyle;
                /*!< */
        char *CLayer;
                /*!< Current layer name.\n
                 * Group code = 8. */
        char *CELType;
                /*!< Entity linetype name, or BYBLOCK or BYLAYER.\n
                 * Group code = 6. */
        int CEColor;
                /*!< Current entity color number:
                 * <ol>
                 *   <li value = 0> BYBLOCK.</li>
                 *   <li value = 256> BYLAYER. </li>
                 * </ol>
                 * Group code = 62. */
        double CELTScale;
                /*!< Current entity linetype scale.\n
                 * Group code = 40. */
        int16_t CShadow;
                /*!< Shadow mode for a 3D object:\n
                 * <ol>
                 * <li value = "0"> Casts and receives shadows.</li>
                 * <li value = "1"> Casts shadows.</li>
                 * <li value = "2"> Receives shadows.</li>
                 * <li value = "3"> Ignores shadows.</li>
                 * </ol>\n
                 * Group code = 284.\n */
        int DelObj;
                /*!< */
        int DimASSOC;
                /*!< Controls the associativity of dimension objects:
                 * <ol>
                 *   <li value = 0> Creates exploded dimensions;
                 *     there is no association between elements of the
                 *     dimension, and the lines, arcs, arrowheads, and
                 *     text of a dimension are drawn as separate objects.</li>
                 *   <li value = 1> Creates non-associative dimension
                 *     objects; the elements of the dimension are formed
                 *     into a single object, and if the definition point
                 *     on the object moves, then the dimension value is
                 *     updated.</li>
                 *   <li value = 2> Creates associative dimension
                 *     objects; the elements of the dimension are formed
                 *     into a single object and one or more definition
                 *     points of the dimension are coupled with
                 *     association points on geometric objects.</li>
                 * </ol>
                 * Group code = 280. */
        double DimSCALE;
                /*!< Overall dimensioning scale factor.\n
                 * Group code = 40. */
        double DimASZ;
                /*!< Dimensioning arrow size.\n
                 * Group code = 40. */
        double DimEXO;
                /*!< Extension line offset.\n
                 * Group code = 40. */
        double DimDLI;
                /*!< Dimension line increment.\n
                 * Group code = 40. */
        double DimRND;
                /*!< Rounding value for dimension distances.\n
                 * Group code = 40. */
        double DimDLE;
                /*!< Dimension line extension.\n
                 * Group code = 40. */
        double DimEXE;
                /*!< Extension line extension.\n
                 * Group code = 40. */
        double DimFAC;
                /*!< Scale factor used to calculate the height of text
                 * for dimension fractions and tolerances.\n
                 * AutoCAD multiplies DIMTXT by DIMTFAC to set the
                 * fractional or tolerance text height.\n
                 * Group code = 40. */
        double DimTP; /*!< */
        double DimTM;
                /*!< Minus tolerance.\n
                 * Group code = 40. */
        double DimTXT; /*!< */
        double DimCEN;
                /*!< Size of center mark/lines.\n
                 * Group code = 40. */
        double DimTSZ; /*!< */
        int DimTOL; /*!< */
        int DimLIM;
                /*!< Dimension limits generated if nonzero.\n
                 * Group code = 70. */
        int DimTIH;
                /*!< Text inside horizontal if nonzero.\n
                 * Group code = 70. */
        int DimTOH; /*!< */
        int DimSE1;
                /*!< First extension line suppressed if nonzero.\n
                 * Group code = 70. */
        int DimSE2;
                /*!< Second extension line suppressed if nonzero.\n
                 * Group code = 70. */
        int DimTAD;
                /*!< Text above dimension line if nonzero.\n
                 * Group code = 70. */
        int DimZIN; /*!< */
        char *DimBLK;
                /*!< Arrow block name.\n
                 * Group code = 1. */
        char *DimBLK1;
                /*!< First arrow block name.\n
                 * Group code = 1. */
        char *DimBLK2;
                /*!< Second arrow block name.\n
                 * Group code = 1. */
        int DimASO;
                /*!< Create associative dimensions:
                 * <ol>
                 *   <li value = 0> Draw individual entities.</li>
                 *   <li value = 1> Create associative dimensioning.</li>
                 * </ol>
                 * Group code = 70. */
        int DimSHO;
                /*!< Recompute dimensions while dragging:
                 * <ol>
                 *   <li value = 0> Drag original image.</li>
                 *   <li value = 1> Recompute dimensions while dragging.</li>
                 * </ol>
                 * Group code = 70. */
        char *DimPOST;
                /*!< General dimensioning suffix.\n
                 * Group code = 1. */
        char *DimAPOST;
                /*!< Alternate dimensioning suffix.\n
                 * Group code = 1. */
        int DimALT;
                /*!< Alternate unit dimensioning performed if nonzero.\n
                 * Group code = 70. */
        int DimALTD;
                /*!< Alternate unit decimal places.\n
                 * Group code = 70. */
        double DimALTF;
                /*!< Alternate unit scale factor.\n
                 * Group code = 40. */
        double DimLFAC;
                /*!< Linear measurements scale factor.\n
                 * Group code = 40. */
        int DimTOFL;
                /*!< If text is outside extensions, force line
                 * extensions between extensions if nonzero.\n
                 * Group code = 70. */
        double DimTVP; /*!< */
        int DimTIX;
                /*!< Force text inside extensions if nonzero.\n
                 * Group code = 70. */
        int DimSOXD;
                /*!< Suppress outside-extensions dimension lines if
                 * nonzero.\n
                 * Group code = 70. */
        int DimSAH;
                /*!< Use separate arrow blocks if nonzero.\n
                 * Group code = 70. */
        char *DimSTYLE;
                /*!< Dimension style name.\n
                 * Group code = 2.*/
        int DimCLRD;
                /*!< Dimension line color, range is:
                 * <ol>
                 *   <li value = 0> BYBLOCK.</li>
                 *   <li value = 256> BYLAYER.</li>
                 * </ol>
                 * Group code = 70. */
        int DimCLRE;
                /*!< Dimension extension line color, range is:
                 * <ol>
                 *   <li value = 0> BYBLOCK.</li>
                 *   <li value = 256> BYLAYER.</li>
                 * </ol>
                 * Group code = 70. */
        int DimCLRT;
                /*!< Dimension text color, range is:
                 * <ol>
                 *   <li value = 0> BYBLOCK.</li>
                 *   <li value = 256> BYLAYER.</li>
                 * </ol>
                 * Group code = 70. */
        double DimTFAC;
                /*!< Dimension tolerance display scale factor.\n
                 * Group code = 40. */
        double DimGAP;
                /*!< Dimension line gap.\n
                 * Group code = 40. */
        int DimJUST;
                /*!< Horizontal dimension text position:
                 * <ol>
                 *   <li value = 0> Above dimension line and center-
                 *     justified between extension lines.</li>
                 *   <li value = 1> Above dimension line and next to
                 *     first extension line.</li>
                 *   <li value = 2> Above dimension line and next to
                 *     second extension line.</li>
                 *   <li value = 3> Above and center-justified to first
                 *    extension line.</li>
                 *   <li value = 4> Above and center-justified to second
                 *     extension line.</li>
                 * </ol>
                 * Group code = 70. */
        int DimSD1;
                /*!< Suppression of first extension line:
                 * <ol>
                 *   <li value = 0> Not suppressed.</li>
                 *   <li value = 1> Suppressed.</li>
                 * </ol>
                 * Group code = 70. */
        int DimSD2;
                /*!< Suppression of second extension line:
                 * <ol>
                 *   <li value = 0> Not suppressed.</li>
                 *   <li value = 1> Suppressed.</li>
                 * </ol>
                 * Group code = 70. */
        int DimTOLJ; /*!< */
        int DimTZIN; /*!< */
        int DimALTZ;
                /*!< Controls suppression of zeros for alternate unit
                 * dimension values:
                 * <ol>
                 *   <li value = 0> Suppresses zero feet and precisely
                 *     zero inches.</li>
                 *   <li value = 1> Includes zero feet and precisely
                 *     zero inches.</li>
                 *   <li value = 2> Includes zero feet and suppresses
                 *     zero inches.</li>
                 *   <li value = 3> Includes zero inches and suppresses
                 *     zero feet.</li>
                 * </ol>
                 * Group code = 70. */
        int DimALTTZ;
                /*!< Controls suppression of zeros for alternate
                 * tolerance values:
                 * <ol>
                 *   <li value = 0> Suppresses zero feet and precisely
                 *     zero inches.</li>
                 *   <li value = 1> Includes zero feet and precisely
                 *     zero inches.</li>
                 *   <li value = 2> Includes zero feet and suppresses
                 *     zero inches.</li>
                 *   <li value = 3> Includes zero inches and suppresses
                 *     zero feet.</li>
                 * </ol>
                 * Group code = 70. */
        int DimFIT; /*!< */
        int DimUPT; /*!< */
        int DimUNIT; /*!< */
        int DimDEC;
                /*!< Number of decimal places for the tolerance values
                 * of a primary units dimension.\n
                 * Group code = 70. */
        int DimTDEC;
                /*!< Number of decimal places to display the tolerance
                 * values.\n
                 * Group code = 70. */
        int DimALTU;
                /*!< Units format for alternate units of all dimension
                 * style family members except angular:
                 * <ol>
                 *   <li value = 1> Scientific.</li>
                 *   <li value = 2> Decimal.</li>
                 *   <li value = 3> Engineering.</li>
                 *   <li value = 4> Architectural (stacked).</li>
                 *   <li value = 5> Fractional (stacked).</li>
                 *   <li value = 6> Architectural.</li>
                 *   <li value = 7> Fractional.</li>
                 * </ol>
                 * Group code = 70. */
        int DimALTTD;
                /*!< Number of decimal places for tolerance values of an
                 * alternate units dimension.\n
                 * Group code = 70. */
        char *DimTXSTY; /*!< */
        int DimAUNIT;
                /*!< Angle format for angular dimensions:
                 * <ol>
                 *   <li value = 0> Decimal degrees.</li>
                 *   <li value = 1> Degrees/minutes/seconds.</li>
                 *   <li value = 2> Gradians.</li>
                 *   <li value = 3> Radians.</li>
                 *   <li value = 4> Surveyor's units.</li>
                 * </lo>
                 * Group code = 70. */
        int DimADEC;
                /*!< Number of precision places displayed in angular
                 * dimensions.\n
                 * Group code = 70. */
        double DimALTRND;
                /*!< Determines rounding of alternate units.\n
                 * Group code = 40. */
        int DimAZIN;
                /*!< Controls suppression of zeros for angular
                 * dimensions:
                 * <ol>
                 *   <li value = 0> Displays all leading and trailing
                 *     zeros.</li>
                 *   <li value = 1> Suppresses leading zeros in decimal
                 *     dimensions.</li>
                 *   <li value = 2> Suppresses trailing zeros in decimal
                 *     dimensions.</li>
                 *   <li value = 3> Suppresses leading and trailing
                 *     zeros.</li>
                 * </ol>
                 * Group code = 70. */
        int DimDSEP;
                /*!< Single-character decimal separator used when
                 * creating dimensions whose unit format is decimal.\n
                 * Group code = 70. */
        int DimATFIT;
                /*!< Controls dimension text and arrow placement when
                 * space is not sufficient to place both within the
                 * extension lines:
                 * <ol>
                 *   <li value = 0> Places both text and arrows outside
                 *     extension lines.</li>
                 *   <li value = 1> Moves arrows first, then text.</li>
                 *   <li value = 2> Moves text first, then arrows.</li>
                 *   <li value = 3> Moves either text or arrows,
                 *     whichever fits best.\n
                 *     AutoCAD adds a leader to moved dimension text
                 *     when DIMTMOVE is set to 1.</li>
                 * </ol>
                 * Group code = 70. */
        int DimFRAC; /*!< */
        char *DimLDRBLK;
                /*!< Arrow block name for leaders.\n
                 * Group code = 1, */
        int DimLUNIT;
                /*!< Sets units for all dimension types except Angular:\n
                 * <ol>
                 *   <li vlaue = 1> Scientific.</li>
                 *   <li value = 2> Decimal.</li>
                 *   <li value = 3> Engineering.</li>
                 *   <li value = 4> Architectural.</li>
                 *   <li value = 5> Fractional.</li>
                 *   <li value = 6> Windows desktop.</li>
                 * </ol>
                 * Group code = 70. */
        int DimLWD;
                /*!< Dimension line lineweight:
                 * <ul>
                 *   <li>-3 = Standard.</li>
                 *   <li>-2 = ByLayer.</li>
                 *   <li>-1 = ByBlock.</li>
                 *   <li>0-211 = an integer representing 100th of
                 *     mm.</li>
                 * </ul>
                 * Group code = 70. */
        int DimLWE;
                /*!< Extension line lineweight:
                 * <ul>
                 *   <li>-3 = Standard.</li>
                 *   <li>-2 = ByLayer.</li>
                 *   <li>-1 = ByBlock.</li>
                 *   <li>0-211 = an integer representing 100th of
                 *     mm.</li>
                 * </ul>
                 * Group code = 70. */
        int DimTMOVE;
                /*!< Dimension text movement rules:
                 * <ol>
                 *   <li value = 0> Moves the dimension line with
                 *     dimension text.</li>
                 *   <li value = 1> Adds a leader when dimension text is
                 *     moved.</li>
                 * <li value = 2> Allows text to be moved freely without
                 *     a leader.</li>
                 * </ol>
                 * Group code = 70. */
        int DispSilH;
                /*!< */
        int LUnits; /*!< */
        int LUPrec; /*!< */
        double Sketchinc; /*!< */
        double FilletRad; /*!< */
        int AUnits;
                /*!< Units format for angles.\n
                 * Group code = 70. */
        int AUPrec;
                /*!< Units precision for angles.\n
                 * Group code = 70. */
        char *Menu; /*!< */
        double Elevation; /*!< */
        double PElevation; /*!< */
        double Thickness; /*!< */
        int LimCheck; /*!< */
        int BlipMode; /*!< */
        double ChamferA;
                /*!< First chamfer distance.\n
                 * Group code = 40. */
        double ChamferB;
                /*!< Second chamfer distance.\n
                 * Group code = 40. */
        double ChamferC;
                /*!< Chamfer length.\n
                 * Group code = 40. */
        double ChamferD;
                /*!< Chamfer angle.
                 * Group code = 40. */
        int SKPoly; /*!< */
        double TDCreate; /*!< */
        double TDUCreate; /*!< */
        double TDUpdate; /*!< */
        double TDUUpdate; /*!< */
        double TDInDWG; /*!< */
        double TDUSRTimer; /*!< */
        int USRTimer; /*!< */
        double AngBase;
                /*!< Angle 0 direction.\n
                 * Group code = 50. */
        int AngDir;
                /*!< <ol>
                 *   <li value = 0> Counterclockwise angles.</li>
                 *   <li value = 1> Clockwise angles.</li>
                 * </ol>
                 * Group code = 70. */
        int PDMode; /*!< */
        double PDSize; /*!< */
        double PLineWid; /*!< */
        int Coords; /*!< */
        int SPLFrame; /*!< */
        int SPLineType; /*!< */
        int SPLineSegs; /*!< */
        int AttDia; /*!< */
        int AttReq; /*!< */
        int Handling; /*!< */
        char *HandSeed; /*!< */
        int SurfTab1; /*!< */
        int SurfTab2; /*!< */
        int SurfType; /*!< */
        int SurfU; /*!< */
        int SurfV; /*!< */
        char *UCSBase; /*!< */
        char *UCSName; /*!< */
        DxfPoint UCSOrg; /*!< */
        DxfPoint UCSXDir; /*!< */
        DxfPoint UCSYDir; /*!< */
        char *UCSOrthoRef; /*!< */
        int UCSOrthoView; /*!< */
        DxfPoint UCSOrgTop; /*!< */
        DxfPoint UCSOrgBottom; /*!< */
        DxfPoint UCSOrgLeft; /*!< */
        DxfPoint UCSOrgRight; /*!< */
        DxfPoint UCSOrgFront; /*!< */
        DxfPoint UCSOrgBack; /*!< */
        char *PUCSBase; /*!< */
        char *PUCSName; /*!< */
        DxfPoint PUCSOrg; /*!< */
        DxfPoint PUCSXDir; /*!< */
        DxfPoint PUCSYDir; /*!< */
        char *PUCSOrthoRef; /*!< */
        int PUCSOrthoView; /*!< */
        DxfPoint PUCSOrgTop; /*!< */
        DxfPoint PUCSOrgBottom; /*!< */
        DxfPoint PUCSOrgLeft; /*!< */
        DxfPoint PUCSOrgRight; /*!< */
        DxfPoint PUCSOrgFront; /*!< */
        DxfPoint PUCSOrgBack; /*!< */
        int UserI1; /*!< */
        int UserI2; /*!< */
        int UserI3; /*!< */
        int UserI4; /*!< */
        int UserI5; /*!< */
        double UserR1; /*!< */
        double UserR2; /*!< */
        double UserR3; /*!< */
        double UserR4; /*!< */
        double UserR5; /*!< */
        int WorldView; /*!< */
        int ShadEdge; /*!< */
        int ShadeDif; /*!< */
        int TileMode; /*!< */
        int MaxActVP; /*!< */
        DxfPoint PInsBase; /*!< */
        int PLimCheck; /*!< */
        DxfPoint PExtMin; /*!< */
        DxfPoint PExtMax; /*!< */
        DxfPoint PLimMin; /*!< */
        DxfPoint PLimMax; /*!< */
        int UnitMode; /*!< */
        int VisRetain; /*!< */
        int PLineGen; /*!< */
        int PSLTScale; /*!< */
        int TreeDepth; /*!< */
        int PickStyle; /*!< */
        char *CMLStyle;
                /*!< Current multiline style name.\n
                 * Goup code = 2. */
        int CMLJust;
                /*!< Current multiline justification:
                 * <ol>
                 *   <li value = 0> Top.<li>
                 *   <li value = 1> Middle.</li>
                 *   <li value = 2> Bottom.</li>
                 * </ol>
                 * Group value = 70. */
        double CMLScale;
                /*!< Current multiline scale.\n
                 * Group code = 40. */
        int ProxyGraphics; /*!< */
        int Measurement; /*!< */
        int SaveImages; /*!< */
        int CELWeight;
                /*!< Lineweight of new objects.\n
                 * Group code = 370. */
        int EndCaps; /*!< */
        int JoinStyle; /*!< */
        int LWDisplay; /*!< */
        int InsUnits; /*!< */
        char *HyperLinkBase; /*!< */
        char *StyleSheet; /*!< */
        int XEdit; /*!< */
        int CEPSNType;
                /*!< Plot style type of new objects:
                 * <ol>
                 *   <li value = 0> Plot style by layer.</li>
                 *   <li value = 1> Plot style by block.</li>
                 *   <li value = 2> Plot style by dictionary default.</li>
                 *   <li value = 3> Plot style by object ID/handle.</li>
                 * </ol>
                 * Group code = 380. */
        char *CEPSNID;
                /*!< Plotstyle handle of new objects; if CEPSNTYPE is 3,
                 * then this value indicates the handle.\n
                 * Group code = 390. */
        int PStyleMode; /*!< */
        char *FingerPrintGUID; /*!< */
        char *VersionGUID; /*!< */
        int ExtNames; /*!< */
        double PSVPScale; /*!< */
        int OLEStartUp; /*!< */
        int SortEnts; /*!< */
        int IndexCtl; /*!< */
        int HideText; /*!< */
        int XClipFrame; /*!< */
        int HaloGap; /*!< */
        int ObsColor; /*!< */
        int ObsLType; /*!< */
        int InterSectionDisplay; /*!< */
        int InterSectionColor; /*!< */
        char *ProjectName; /*!< */
        DxfPoint GridUnit;
                /*!< Grid X and Y spacing  */
        int GridMode;
                /*!< Grid mode on if nonzero */
} DxfHeader;


int
dxf_header_acad_version_from_string
(
        const char * version_string
);
char *
dxf_header_acad_version_to_string
(
        int version_number
);
DxfHeader *
dxf_header_new ();
DxfHeader *
dxf_header_init
(
        DxfHeader *header,
        int acad_version_number
);
DxfHeader *
dxf_header_read
(
        DxfFile *fp,
        DxfHeader *header
);
int
dxf_header_read_parse_int
(
        DxfFile *fp,
        const char *temp_string,
        const char *header_var,
        int *value,
        int version_expression
);
int
dxf_header_read_parse_n_double
(
        DxfFile *fp,
        const char *temp_string,
        const char *header_var,
        int version_expression,
        int quant,
        ...
);
int
dxf_header_read_parse_string
(
        DxfFile *fp,
        const char *temp_string,
        const char *header_var,
        char **value_string,
        int version_expression
);
int
dxf_header_read_parser
(
        DxfFile *fp,
        DxfHeader *header,
        char * temp_string,
        int acad_version_number
);
int
dxf_header_write
(
        DxfFile *fp,
        DxfHeader *header
);
int
dxf_header_write_metric_new
(
        DxfFile *fp
);
DxfHeader *
dxf_header_free
(
        DxfHeader *header
);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_HEADER_H */


/* EOF */
