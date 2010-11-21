/*!
 * \file header.h
 * \author Copyright (C) 2008 by Bert Timmerman <bert.timmerman@xs4all.nl>.\n
 * \brief Definition of a DXF header section.
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

#ifndef HEADER_H
#define HEADER_H
#include "global.h"
#include "point.h"

typedef struct
dxf_header
{
        int id_code;
                /*!< group code = 5. */
        char *AcadVer;
                /*!< */
        int _AcadVer;
                /*!< */
        int AcadMaintVer;
                /*!< */
        char *DWGCodePage;
                /*!< drawing code page.\n
                 * Set to the system code page when a new drawing is created,
                 * but not otherwise maintained by AutoCAD. */
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
                /*!< */
        double TextSize;
                /*!< */
        double TraceWid;
                /*!< */
        char *TextStyle;
                /*!< */
        char *CLayer;
                /*!< */
        char *CELType;
                /*!< */
        int CEColor;
                /*!< */
        double CELTScale;
                /*!< */
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
                /*!< create associative dimensions:\n
                 * 0 = draw individual entities.\n
                 * 1 = create associative dimensioning. */
        int DimSHO;
                /*!< recompute dimensions while dragging:\n
                 * 0 = drag original image.\n
                 * 1 = recompute dimensions while dragging. */
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
        int AUnits; /*!< */
        int AUPrec; /*!< */
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
        double AngBase; /*!< */
        int AngDir; /*!< */
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
        int CELWeight; /*!< */
        int EndCaps; /*!< */
        int JoinStyle; /*!< */
        int LWDisplay; /*!< */
        int InsUnits; /*!< */
        char *HyperLinkBase; /*!< */
        char *StyleSheet; /*!< */
        int XEdit; /*!< */
        int CEPSNType; /*!< */
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

        DxfPoint GridUnit; /*!< Grid X and Y spacing  */
        int GridMode; /*!< Grid mode on if nonzero */
        
} DxfHeader, * DxfHeaderPtr;

int dxf_init_header ( DxfHeader dxf_header, int acad_version_number );
int dxf_read_header ( FILE *fp, DxfHeader dxf_header);
int dxf_write_header ( FILE *fp, DxfHeader dxf_header, int acad_version_number);

#endif /* HEADER_H */
/* EOF */
