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
                 * Set to the system code page when a new drawing is created,
                 * but not otherwise maintained by AutoCAD.\n
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
                /*!< */
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
        int DelObj;
                /*!< */
        int DispSilH;
                /*!< */
        double DimSCALE; /*!< */
        double DimASZ; /*!< */
        double DimEXO; /*!< */
        double DimDLI; /*!< */
        double DimRND; /*!< */
        double DimDLE; /*!< */
        double DimEXE; /*!< */
        double DimTP; /*!< */
        double DimTM; /*!< */
        double DimTXT; /*!< */
        double DimCEN; /*!< */
        double DimTSZ; /*!< */
        int DimTOL; /*!< */
        int DimLIM; /*!< */
        int DimTIH; /*!< */
        int DimTOH; /*!< */
        int DimSE1; /*!< */
        int DimSE2; /*!< */
        int DimTAD; /*!< */
        int DimZIN; /*!< */
        char *DimBLK; /*!< */
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
        char *DimPOST; /*!< */
        char *DimAPOST; /*!< */
        int DimALT; /*!< */
        int DimALTD; /*!< */
        double DimALTF; /*!< */
        double DimLFAC; /*!< */
        int DimTOFL; /*!< */
        double DimTVP; /*!< */
        int DimTIX; /*!< */
        int DimSOXD; /*!< */
        int DimSAH; /*!< */
        char *DimBLK1; /*!< */
        char *DimBLK2; /*!< */
        char *DimSTYLE; /*!< */
        int DimCLRD; /*!< */
        int DimCLRE; /*!< */
        int DimCLRT; /*!< */
        double DimTFAC; /*!< */
        double DimGAP; /*!< */
        int DimJUST; /*!< */
        int DimSD1; /*!< */
        int DimSD2; /*!< */
        int DimTOLJ; /*!< */
        int DimTZIN; /*!< */
        int DimALTZ; /*!< */
        int DimALTTZ; /*!< */
        int DimFIT; /*!< */
        int DimUPT; /*!< */
        int DimUNIT; /*!< */
        int DimDEC; /*!< */
        int DimTDEC; /*!< */
        int DimALTU; /*!< */
        int DimALTTD; /*!< */
        char *DimTXSTY; /*!< */
        int DimAUNIT; /*!< */
        int DimADEC; /*!< */
        double DimALTRND; /*!< */
        int DimAZIN; /*!< */
        int DimDSEP; /*!< */
        int DimATFIT; /*!< */
        int DimFRAC; /*!< */
        char *DimLDRBLK; /*!< */
        int DimLUNIT; /*!< */
        int DimLWD; /*!< */
        int DimLWE; /*!< */
        int DimTMOVE; /*!< */
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
        double ChamferA; /*!< */
        double ChamferB; /*!< */
        double ChamferC; /*!< */
        double ChamferD; /*!< */
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
        char *CMLStyle; /*!< */
        int CMLJust; /*!< */
        double CMLScale; /*!< */
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
        int CEPSNType; /*!< */
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
        int DimASSOC; /*!< */
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
