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
                /*!< Insertion base set by BASE command (in WCS).\n
                 * Group code = 10, 20 and 30. */
        DxfPoint ExtMin;
                /*!< X, Y, and Z drawing extents lower-left corner (in WCS).\n
                 * Group code = 10, 20 and 30. */
        DxfPoint ExtMax;
                /*!< X, Y, and Z drawing extents upper-right corner (in WCS).\n
                 * Group code = 10, 20 and 30. */
        DxfPoint LimMin;
                /*!< XY drawing limits lower-left corner (in WCS).\n
                 * Group code = 10 and 20. */
        DxfPoint LimMax;
                /*!< XY drawing limits upper-right corner (in WCS).\n
                 * Group code = 10 and 20. */
        int OrthoMode;
                /*!< Ortho mode on if nonzero.\n
                 * Group code = 70. */
        int RegenMode;
                /*!< REGENAUTO mode on if nonzero.\n
                 * Group code = 70. */
        int FillMode;
                /*!< Fill mode on if nonzero.\n
                 * Group code = 70. */
        int QTextMode;
                /*!< Quick Text mode on if nonzero.\n
                 * Group code = 70. */
        int MirrText;
                /*!< Mirror text if nonzero.\n
                 * Group code = 70. */
        int DragMode;
                /*!< */
        double LTScale;
                /*!< Global linetype scale.\n
                 * Group code = 40. */
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
                /*!< Default text height.\n
                 * Group code = 40. */
        double TraceWid;
                /*!< Default trace width.\n
                 * Group code = 40. */
        char *TextStyle;
                /*!< Current text style name.\n
                 * Group code = 7. */
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
        double DimTP;
                /*!< Plus tolerance.\n
                 * Group code = 40. */
        double DimTM;
                /*!< Minus tolerance.\n
                 * Group code = 40. */
        double DimTXT;
                /*!< Dimensioning text height.\n
                 * Group code = 40. */
        double DimCEN;
                /*!< Size of center mark/lines.\n
                 * Group code = 40. */
        double DimTSZ;
                /*!< Dimensioning tick size:\n
                 * 0 = No ticks.
                 * Group code = 40. */
        int DimTOL;
                /*!< Dimension tolerances generated if nonzero.\n
                 * Group code = 70. */
        int DimLIM;
                /*!< Dimension limits generated if nonzero.\n
                 * Group code = 70. */
        int DimTIH;
                /*!< Text inside horizontal if nonzero.\n
                 * Group code = 70. */
        int DimTOH;
                /*!< Text outside horizontal if nonzero.\n
                 * Group code = 70. */
        int DimSE1;
                /*!< First extension line suppressed if nonzero.\n
                 * Group code = 70. */
        int DimSE2;
                /*!< Second extension line suppressed if nonzero.\n
                 * Group code = 70. */
        int DimTAD;
                /*!< Text above dimension line if nonzero.\n
                 * Group code = 70. */
        int DimZIN;
                /*!< Controls suppression of zeros for primary unit
                 * values:
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
        double DimTVP;
                /*!< Text vertical position.\n
                 * Group code = 40. */
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
        int DimTOLJ;
                /*!< Vertical justification for tolerance values:
                 * <ol>
                 *   <li value = 0> Top.</li>
                 *   <li value = 1> Middle.</li>
                 *   <li value = 2> Bottom.</li>
                 * </ol>
                 * Group code = 70. */
        int DimTZIN;
                /*!< Controls suppression of zeros for tolerance values:
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
        int DimUPT;
                /*!< Cursor functionality for user-positioned text:
                 * <ol>
                 *   <li value = 0> Controls only the dimension line
                 *     location.</li>
                 *   <li value = 1> Controls the text position as well
                 *     as the dimension line location.</li>
                 * </ol>
                 * Group code = 70. */
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
        char *DimTXSTY;
                /*!< Dimension text style.\n
                 * Group code = 7. */
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
                /*!< Controls the display of silhouette curves of body
                 * objects in Wireframe mode:
                 * <ol>
                 *   <li value = 0> Off.</li>
                 *   <li value = 1> On.</li>
                 * </ol>
                 * Group code = 70. */
        char *DragVS;
                /*!< Hard-pointer ID to visual style while creating 3D
                 * solid primitives.\n
                 * The defualt value is NULL.\n
                 * Group code = 349. */
        int LUnits;
                /*!< Units format for coordinates and distances.\n
                 * Group code = 70. */
        int LUPrec;
                /*!< Units precision for coordinates and distances.\n
                 * Group code = 70. */
        double Sketchinc;
                /*!< Sketch record increment.\n
                 * Group code = 40. */
        double FilletRad;
                /*!< Fillet radius.\n
                 * Group code = 40. */
        int AUnits;
                /*!< Units format for angles.\n
                 * Group code = 70. */
        int AUPrec;
                /*!< Units precision for angles.\n
                 * Group code = 70. */
        char *Menu;
                /*!< Name of menu file.\n
                 * Group code = 1. */
        double Elevation;
                /*!< Current elevation set by ELEV command.\n
                 * Group code = 40. */
        double PElevation;
                /*!< Current paper space elevation.\n
                 * Group code = 40. */
        double Thickness;
                /*!< Current thickness set by ELEV command.\n
                 * Group code = 40. */
        int LimCheck;
                /*!< Nonzero if limits checking is on.\n
                 * Group code = 70. */
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
        int SKPoly;
                /*!< <ol>
                 *   <li value = 0> Sketch lines.</li>
                 *   <li value = 1> Sketch polylines.</li>
                 * </ol>
                 * Group code = 70. */
        double TDCreate;
                /*!< Local date/time of drawing creation (see Special
                 * Handling of Date/Time Variables).\n
                 * Group code = 40. */
        double TDUCreate;
                /*!< Universal date/time the drawing was created (see
                 * Special Handling of Date/Time Variables).\n
                 * Group code = 40. */
        double TDUpdate;
                /*!< Local date/time of last drawing update (see Special
                 * Handling of Date/Time Variables).\n
                 * Group code = 40. */
        double TDUUpdate;
                /*!< Universal date/time of the last update/save (see
                 * Special Handling of Date/Time Variables).\n
                 * Group code = 40. */
        double TDInDWG;
                /*!< Cumulative editing time for this drawing (see
                 * Special Handling of Date/Time Variables).\n
                 * Group code = 40. */
        double TDUSRTimer;
                /*!< User-elapsed timer.\n
                 * Group code = 40. */
        int USRTimer;
                /*!< <ol>
                 *   <li value = 0> Timer off.</li>
                 *   <li value = 1> Timer on.</li>
                 * </ol>
                 * Group code = 70. */
        double AngBase;
                /*!< Angle 0 direction.\n
                 * Group code = 50. */
        int AngDir;
                /*!< <ol>
                 *   <li value = 0> Counterclockwise angles.</li>
                 *   <li value = 1> Clockwise angles.</li>
                 * </ol>
                 * Group code = 70. */
        int PDMode;
                /*!< Point display mode.\n
                 * Group code = 70. */
        double PDSize;
                /*!< Point display size.\n
                 * Group code = 40. */
        double PLineWid;
                /*!< Default polyline width.\n
                 * Group code = 40. */
        int Coords; /*!< */
        int SPLFrame; /*!< */
        int SPLineType;
                /*!< Spline curve type for PEDIT Spline.\n
                 * Group code = 70. */
        int SPLineSegs;
                /*!< Number of line segments per spline patch.\n
                 * Group code = 70. */
        int AttDia; /*!< */
        int AttReq; /*!< */
        int Handling; /*!< */
        char *HandSeed;
                /*!< Next available handle.\n
                 * Group code = 5. */
        int SurfTab1;
                /*!< Number of mesh tabulations in first direction.\n
                 * Group code = 70. */
        int SurfTab2;
                /*!< Number of mesh tabulations in second direction.\n
                 * Group code = 70. */
        int SurfType;
                /*!< Surface type for PEDIT Smooth.\n
                 * Group code = 70. */
        int SurfU;
                /*!< Surface density (for PEDIT Smooth) in M direction.\n
                 * Group code = 70. */
        int SurfV;
                /*!< Surface density (for PEDIT Smooth) in N direction.\n
                 * Group code = 70. */
        char *UCSBase;
                /*!< Name of the UCS that defines the origin and
                 * orientation of orthographic UCS settings.\n
                 * Group code = 2. */
        char *UCSName;
                /*!< Name of current UCS.\n
                 * Group code = 2. */
        DxfPoint UCSOrg;
                /*!< Origin of current UCS (in WCS).\n
                 * Group code 10, 20 and 30. */
        DxfPoint UCSOrgTop;
                /*!< Point which becomes the new UCS origin after
                 * changing model space UCS to TOP when UCSBASE is set
                 * to WORLD.\n
                 * Group code = 10, 20 and 30. */
        DxfPoint UCSOrgBottom;
                /*!< Point which becomes the new UCS origin after
                 * changing model space UCS to BOTTOM when UCSBASE is
                 * set to WORLD.\n
                 * Group code = 10, 20 and 30. */
        DxfPoint UCSOrgLeft;
                /*!< Point which becomes the new UCS origin after
                 * changing model space UCS to LEFT when UCSBASE is set
                 * to WORLD.\n
                 * Group code = 10, 20 and 30. */
        DxfPoint UCSOrgRight;
                /*!< Point which becomes the new UCS origin after
                 * changing model space UCS to RIGHT when UCSBASE is set
                 * to WORLD.\n
                 * Group code = 10, 20 and 30. */
        DxfPoint UCSOrgFront;
                /*!< Point which becomes the new UCS origin after
                 * changing model space UCS to FRONT when UCSBASE is set
                 * to WORLD.\n
                 * Group code = 10, 20 and 30. */
        DxfPoint UCSOrgBack;
                /*!< Point which becomes the new UCS origin after
                 * changing model space UCS to BACK when UCSBASE is set
                 * to WORLD.\n
                 * Group codes = 10, 20 and 30. */
        DxfPoint UCSXDir;
                /*!< Direction of the current UCS X axis (in WCS).\n
                 * Group code = 10, 20 and 30. */
        DxfPoint UCSYDir;
                /*!< Direction of the current UCS Y axis (in WCS).\n
                 * Group code = 10, 20 and 30. */
        char *UCSOrthoRef;
                /*!< If model space UCS is orthographic (UCSORTHOVIEW
                 * not equal to 0), this is the name of the UCS that the
                 * orthographic UCS is relative to.\n
                 * If blank, UCS is relative to WORLD.\n
                 * Group code = 2. */
        int UCSOrthoView;
                /*!< Orthographic view type of model space UCS:
                 * <ol>
                 *   <li value = 0> UCS is not orthographic.</li>
                 *   <li value = 1> Top.</li>
                 *   <li value = 2> Bottom.</li>
                 *   <li value = 3> Front.</li>
                 *   <li value = 4> Back.</li>
                 *   <li value = 5> Left.</li>
                 *   <li value = 6> Right.</li>
                 * </ol>
                 * Group code = 70. */
        char *PUCSBase;
                /*!< Name of the UCS that defines the origin and
                 * orientation of orthographic UCS settings (paper space
                 * only).\n
                 * Group code = 2. */
        char *PUCSName;
                /*!< Current paper space UCS name.\n
                 * Group code = 2. */
        DxfPoint PUCSOrg;
                /*!< Current paper space UCS origin.\n
                 * Group code = 10, 20 and 30. */
        DxfPoint PUCSOrgTop;
                /*!< Point which becomes the new UCS origin after
                 * changing paper space UCS to TOP when PUCSBASE is set
                 * to WORLD.\n
                 * Group code = 10, 20 and 30. */
        DxfPoint PUCSOrgBottom;
                /*!< Point which becomes the new UCS origin after
                 * changing paper space UCS to BOTTOM when PUCSBASE is
                 * set to WORLD.\n
                 * Group code = 10, 20 and 30. */
        DxfPoint PUCSOrgLeft;
                /*!< Point which becomes the new UCS origin after
                 * changing paper space UCS to LEFT when PUCSBASE is set
                 * to WORLD.\n
                 * Group code = 10, 20 and 30. */
        DxfPoint PUCSOrgRight;
                /*!< Point which becomes the new UCS origin after
                 * changing paper space UCS to RIGHT when PUCSBASE is
                 * set to WORLD.\n
                 * Group code = 10, 20 and 30. */
        DxfPoint PUCSOrgFront;
                /*!< Point which becomes the new UCS origin after
                 * changing paper space UCS to FRONT when PUCSBASE is
                 * set to WORLD.\n
                 * Group ode = 10, 20 and 30. */
        DxfPoint PUCSOrgBack;
                /*!< Point which becomes the new UCS origin after
                 * changing paper space UCS to BACK when PUCSBASE is set
                 * to WORLD.\n
                 * Group code = 10, 20 and 30. */
        DxfPoint PUCSXDir;
                /*!< Current paper space UCS X axis.\n
                 * Group code = 10, 20 and 30. */
        DxfPoint PUCSYDir;
                /*!< Current paper space UCS Y axis.\n
                 * Group code = 10, 20 and 30. */
        char *PUCSOrthoRef;
                /*!< If paper space UCS is orthographic (PUCSORTHOVIEW
                 * not equal to 0), this is the name of the UCS that the
                 * orthographic UCS is relative to.\n
                 * If blank, UCS is relative to WORLD.\n
                 * Goup code = 2. */
        int PUCSOrthoView;
                /*!< Orthographic view type of paper space UCS:
                 * <ol>
                 *   <li value = 0> UCS is not orthographic.</li>
                 *   <li value = 1> Top.</li>
                 *   <li value = 2> Bottom.</li>
                 *   <li value = 3> Front.</li>
                 *   <li value = 4> Back.</li>
                 *   <li value = 5> Left.</li>
                 *   <li value = 6> Right.</li>
                 * </ol>
                 * Group code = 70. */
        int UserI1;
                /*!< Integer variable intended for use by third-party
                 * developers.\n
                 * Group code = 70. */
        int UserI2;
                /*!< Integer variable intended for use by third-party
                 * developers.\n
                 * Group code = 70. */
        int UserI3;
                /*!< Integer variable intended for use by third-party
                 * developers.\n
                 * Group code = 70. */
        int UserI4;
                /*!< Integer variable intended for use by third-party
                 * developers.\n
                 * Group code = 70. */
        int UserI5;
                /*!< Integer variable intended for use by third-party
                 * developers.\n
                 * Group code = 70. */
        double UserR1;
                /*!< Real variable intended for use by third-party
                 * developers.\n
                 * Group code = 40. */
        double UserR2;
                /*!< Real variable intended for use by third-party
                 * developers.\n
                 * Group code = 40. */
        double UserR3;
                /*!< Real variable intended for use by third-party
                 * developers.\n
                 * Group code = 40. */
        double UserR4;
                /*!< Real variable intended for use by third-party
                 * developers.\n
                 * Group code = 40. */
        double UserR5;
                /*!< Real variable intended for use by third-party
                 * developers.\n
                 * Group code = 40. */
        int WorldView;
                /*!< <ol>
                 *   <li value = 0> Don't change UCS.</li>
                 *   <li value = 1> Set UCS to WCS during DVIEW/VPOINT.</li>
                 * </ol>
                 * Group code = 70. */
        int ShadEdge;
                /*!< <ol>
                 *   <li value = 0> Faces shaded, edges not highlighted.</li>
                 *   <li value = 1> Faces shaded, edges highlighted in black.</li>
                 *   <li value = 2> Faces not filled, edges in entity color.</li>
                 *   <li value = 3> Faces in entity color, edges in black.</li>
                 * </ol>
                 * Group code = 70. */
        int ShadeDif;
                /*!< Percent ambient/diffuse light.\n
                 * Range 1-100.\n
                 * Default 70.\n
                 * Group code = 70. */
        int TileMode;
                /*!< 1 for previous release compatibility mode;
                 * 0 otherwise.\n
                 * Group code = 70. */
        int MaxActVP;
                /*!< Sets maximum number of viewports to be regenerated.\n
                 * Group code = 70. */
        DxfPoint PInsBase;
                /*!< Paper space insertion base point.\n
                 * Group code = 10, 20 and 30. */
        int PLimCheck;
                /*!< Limits checking in paper space when nonzero.\n
                 * Group code = 70. */
        DxfPoint PExtMin;
                /*!< Minimum X, Y, and Z extents for paper space.\n
                 * Group code = 10, 20 and 30. */
        DxfPoint PExtMax;
                /*!< Maximum X, Y, and Z extents for paper space.\n
                 * Group code = 10, 20 and 30. */
        DxfPoint PLimMin;
                /*!< Minimum X and Y limits in paper space.\n
                 * Group code = 10 and 20. */
        DxfPoint PLimMax;
                /*!< Maximum X and Y limits in paper space.\n
                 * Group code = 10 and 20. */
        int UnitMode;
                /*!< Low bit set = Display fractions, feet-and-inches,
                 * and surveyor's angles in input format.\n
                 * Group code = 70. */
        int VisRetain;
                /*!< <ol>
                 *   <li value = 0> Don't retain xref-dependent
                 *     visibility settings.</li>
                 *   <li value = 1> Retain xref-dependent visibility
                 *     settings.</li>
                 * </ol>
                 * Group code = 70. */
        int PLineGen;
                /*!< Governs the generation of linetype patterns around
                 * the vertices of a 2D polyline:
                 * <ol>
                 *   <li value = 1> Linetype is generated in a
                 *     continuous pattern around vertices of the
                 *     polyline.</li>
                 *   <li value = 0> Each segment of the polyline starts
                 *     and ends with a dash.</li>
                 * </ol>
                 * Group code = 70. */
        int PSLTScale;
                /*!< Controls paper space linetype scaling:
                 * <ol>
                 *   <li value = 1> No special linetype scaling.</li>
                 *   <li value = 0> Viewport scaling governs linetype
                 *     scaling.</li>
                 * </ol>
                 * Group code = 70. */
        int TreeDepth;
                /*!< Specifies the maximum depth of the spatial index.\n
                 * Group code = 70. */
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
        int ProxyGraphics;
                /*!< Controls the saving of proxy object images.\n
                 * Group code = 70. */
        int Measurement;
                /*!< Sets drawing units:
                 * <ol>
                 *   <li value = 0> Imperial.</li>
                 *   <li value = 1> Metric.</li>
                 * </ol>
                 * Group code = 70. */
        int SaveImages; /*!< */
        int CELWeight;
                /*!< Lineweight of new objects.\n
                 * Group code = 370. */
        int EndCaps;
                /*!< Lineweight endcaps setting for new objects:
                 * <ol>
                 *   <li value = 0> none.</li>
                 *   <li value = 1> round.</li>
                 *   <li value = 2> angle.</li>
                 *   <li value = 3> square.</li>
                 * </ol>
                 * Group code = 280. */
        int JoinStyle;
                /*!< Lineweight joint setting for new objects:
                 * <ol>
                 *   <li value = 0> none.</li>
                 *   <li value = 1> round.</li>
                 *   <li value = 2> angle.</li>
                 *   <li value = 3> flat.</li>
                 * </ol>
                 * Group code = 280. */
        int LWDisplay;
                /*!< Controls the display of lineweights on the Model or
                 * Layout tab:
                 * <ol>
                 *   <li value = 0> Lineweight is not displayed.</li>
                 *   <li value = 1> Lineweight is displayed.</li>
                 * </ol>
                 * Group code = 290. */
        int InsUnits;
                /*!< Default drawing units for AutoCAD DesignCenter
                 * blocks:
                 * <ol>
                 *   <li value = 0> Unitless.</li>
                 *   <li value = 1> Inches.</li>
                 *   <li value = 2> Feet.</li>
                 *   <li value = 3> Miles.</li>
                 *   <li value = 4> Millimeters.</li>
                 *   <li value = 5> Centimeters.</li>
                 *   <li value = 6> Meters.</li>
                 *   <li value = 7> Kilometers.</li>
                 *   <li value = 8> Microinches.</li>
                 *   <li value = 9> Mils.</li>
                 *   <li value = 10> Yards.</li>
                 *   <li value = 11> Angstroms.</li>
                 *   <li value = 12> Nanometers.</li>
                 *   <li value = 13> Microns.</li>
                 *   <li value = 14< Decimeters.</li>
                 *   <li value = 15> Decameters.</li>
                 *   <li value = 16> Hectometers.</li>
                 *   <li value = 17> Gigameters.</li>
                 *   <li value = 18> Astronomical units.</li>
                 *   <li value = 19> Light years.</li>
                 *   <li value = 20> Parsecs.</li>
                 * </ol>
                 * Group code = 70. */
        char *HyperLinkBase;
                /*!< Path for all relative hyperlinks in the drawing.\n
                 * If null, the drawing path is used.\n
                 * Group code = 1. */
        char *StyleSheet; /*!< */
        int XEdit;
                /*!< Controls whether the current drawing can be edited
                 * in-place when being referenced by another drawing.
                 * <ol>
                 *   <li value = 0> Can't use in-place reference
                 *     editing.</li>
                 *   <li value = 1> Can use in-place reference editing.</li>
                 * </ol>
                 * Group code = 290. */
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
        int PStyleMode;
                /*!< Indicates whether the current drawing is in a
                 * Color-Dependent or Named Plot Style mode:
                 * <ol>
                 *   <li value =0> Uses named plot style tables in the
                 *     current drawing.</li>
                 *   <li value = 1> Uses color-dependent plot style
                 *     tables in the current drawing.</li>
                 * </ol>
                 * Group code = 290. */
        char *FingerPrintGUID;
                /*!< Set at creation time, uniquely identifies a
                 * particular drawing.\n
                 * Group code = 2. */
        char *VersionGUID;
                /*!< Uniquely identifies a particular version of a
                 * drawing.\n
                 * Updated when the drawing is modified.\n
                 * Group code = 2. */
        int ExtNames;
                /*!< Controls symbol table naming:
                 * <ol>
                 *   <li value = 0> Release 14 compatibility.\n
                 *     Limits names to 31 characters in length.\n
                 *     Names can include the letters A to Z, the
                 *     numerals 0 to 9, and the special characters
                 *     dollar sign ($), underscore (_), and hyphen (-).</li>
                 *   <li value = 1> AutoCAD 2000.\n
                 *     Names can be up to 255 characters in length, and
                 *     can include the letters A to Z, the numerals 0 to
                 *     9, spaces, and any special characters not used
                 *     for other purposes by Microsoft Windows and
                 *     AutoCAD.</li>
                 * </ol>
                 * Group code = 290. */
        double PSVPScale;
                /*!< View scale factor for new viewports:\n
                 * 0 = Scaled to fit.\n
                 * >0 = Scale factor (a positive real value).\n
                 * Group code = 40. */
        int OLEStartUp; /*!< */
        int SortEnts;
                /*!< Controls the object sorting methods; accessible
                 * from the Options dialog box User Preferences tab.\n
                 * SORTENTS uses the following bitcodes:
                 * <ol>
                 *   <li value = 0> Disables SORTENTS.</li>
                 *   <li value = 1> Sorts for object selection.</li>
                 *   <li value = 2> Sorts for object snap.</li>
                 *   <li value = 4> Sorts for redraws.</li>
                 *   <li value = 8> Sorts for MSLIDE command slide
                 *     creation.</li>
                 *   <li value = 16> Sorts for REGEN commands.</li>
                 *   <li value = 32> Sorts for plotting.</li>
                 *   <li value = 64> Sorts for PostScript output.</li>
                 * </ol>
                 * Group code = 280. */
        int IndexCtl;
                /*!< Controls whether layer and spatial indexes are
                 * created and saved in drawing files:
                 * <ol>
                 *   <li value = 0> No indexes are created.</li>
                 *   <li value = 1> Layer index is created.</li>
                 *   <li value = 2> Spatial index is created.</li>
                 *   <li value = 3> Layer and spatial indexes are
                 *     created.</li>
                 * </ol>
                 * Group code = 290. */
        int HideText;
                /*!< Specifies HIDETEXT system variable:
                 * <ol>
                 *   <li value = 0> HIDE ignores text objects when
                 *     producing the hidden view.</li>
                 *   <li value = 1> HIDE does not ignore text objects.</li>
                 * </ol>
                 * Group code = 290. */
        int XClipFrame;
                /*!< Controls the visibility of xref
                 * clipping boundaries:
                 * <ol>
                 *   <li value = 0> Clipping boundary is not visible.</li>
                 *   <li value = 1> Clipping boundary is visible.</li>
                 * </ol>
                 * Group code = 290. */
        int HaloGap;
                /*!< Specifies a gap to be displayed where an object is
                 * hidden by another object; the value is specified as a
                 * percent of one unit and is independent of the zoom
                 * level.\n
                 * A haloed line is shortened at the point where it is
                 * hidden when HIDE or the Hidden option of SHADEMODE is
                 * used.\n
                 * Group code = 280. */
        int ObsColor;
                /*!< Specifies the color of obscured lines.\n
                 * An obscured line is a hidden line made visible by
                 * changing its color and linetype and is visible only
                 * when the HIDE or SHADEMODE command is used.\n
                 * The OBSCUREDCOLOR setting is visible only if the
                 * OBSCUREDLTYPE is turned ON by setting it to a value
                 * other than 0.\n
                 * 0 and 256 = Entity color.\n
                 * 1-255 = An AutoCAD color index (ACI).\n
                 * Group code = 70. */
        int ObsLType;
                /*!< Specifies the linetype of obscured lines.\n
                 * Obscured linetypes are independent of zoom level,
                 * unlike regular AutoCAD linetypes.\n
                 * Value 0 turns off display of obscured lines and is
                 * the default.\n
                 * Linetype values are defined as follows:
                 * <ol>
                 *   <li value = 0> Off.</li>
                 *   <li value = 1> Solid.</li>
                 *   <li value = 2> Dashed.</li>
                 *   <li value = 3> Dotted.</li>
                 *   <li value = 4> Short Dash.</li>
                 *   <li value = 5> Medium Dash.</li>
                 *   <li value = 6> Long Dash.</li>
                 *   <li value = 7> Double Short Dash.</li>
                 *   <li value = 8> Double Medium Dash.</li>
                 *   <li value = 9> Double Long Dash.</li>
                 *   <li value = 10> Medium Long Dash.</li>
                 *   <li value = 11> Sparse Dot.</li>
                 * </ol>
                 *   Group code = 280. */
        int InterSectionDisplay;
                /*!< Specifies the display of intersection polylines:
                 * <ol>
                 *   <li value = 0> Turns off the display of
                 *     intersection polylines.</li>
                 *   <li value = 1> Turns on the display of intersection
                 *     polylines.</li>
                 * </ol>
                 * Group code = 290. */
        int InterSectionColor;
                /*!< Specifies the entity color of intersection
                 * polylines:\n
                 * Values 1-255 designate an AutoCAD color index (ACI).\n
                 * <ol>
                 *   <li value = 0> Color BYBLOCK.</li>
                 *   <li value = 256> Color BYLAYER.</li>
                 *   <li value = 257> Color BYENTITY.</li>
                 * </ol>
                 * Group code = 70. */
        char *ProjectName;
                /*!< Assigns a project name to the current drawing.\n
                 * Used when an external reference or image is not found
                 * on its original path.\n
                 * The project name points to a section in the registry
                 * that can contain one or more search paths for each
                 * project name defined.\n
                 * Project names and their search directories are
                 * created from the Files tab of the Options dialog box.\n
                 * Group code = 1. */
        DxfPoint GridUnit;
                /*!< Grid X and Y spacing  */
        int GridMode;
                /*!< Grid mode on if nonzero */
        int16_t InterfereColor;
                /*!< Represents the ACI color index of the "interference
                 * objects" created during the interfere command.\n
                 * Default value is 1.\n
                 * Group code = 62. */
        char *InterfereObjVS;
                /*!< Hard-pointer ID to the visual style for
                 * interference objects.\n
                 * Default visual style is Conceptual.\n
                 * Group code = 345. */
        char *InterfereVPVS;
                /*!< Hard-pointer ID to the visual style for the
                 * viewport during interference checking.\n
                 * Default visual style is 3d Wireframe.\n
                 * Group code = 346. */
        double ShadowPlaneLocation;
                /*!< Location of the ground shadow plane.\n
                 * This is a Z axis ordinate.\n
                 * Group code = 40. */
} DxfHeader;


int dxf_header_acad_version_from_string (const char * version_string);
char *dxf_header_acad_version_to_string (int version_number);
DxfHeader *dxf_header_new ();
DxfHeader *dxf_header_init (DxfHeader *header, int acad_version_number);
DxfHeader *dxf_header_read (DxfFile *fp, DxfHeader *header);
int dxf_header_read_parse_int (DxfFile *fp, const char *temp_string, const char *header_var, int *value, int version_expression);
int dxf_header_read_parse_n_double (DxfFile *fp,const char *temp_string, const char *header_var, int version_expression, int quant, ... );
int dxf_header_read_parse_string (DxfFile *fp, const char *temp_string, const char *header_var, char **value_string, int version_expression);
int dxf_header_read_parser (DxfFile *fp, DxfHeader *header, char * temp_string, int acad_version_number);
int dxf_header_write (DxfFile *fp, DxfHeader *header);
int dxf_header_write_metric_new (DxfFile *fp);
DxfHeader *dxf_header_free (DxfHeader *header);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_HEADER_H */


/* EOF */
