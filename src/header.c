/*!
 * \file header.c
 * \author Copyright (C) 2008, 2010 by Bert Timmerman <bert.timmerman@xs4all.nl>.\n
 * \brief DXF header section.
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

#include <stdarg.h>
#include "global.h"
#include "file.h"
#include "header.h"
#include "section.h"
#include "util.h"

static char *acad_version_string (int version_number)
{
        switch (version_number)
        {
                case AC1006: return "AC1006";
                case AC1009: return "AC1009";
                case AC1012: return "AC1012";
                case AC1014: return "AC1014";
                case AC1015: return "AC1015";
                case AC1016: return "AC1016";
                case AC1017: return "AC1017";
                case AC1018: return "AC1018";
                case AC1021: return "AC1021";
                case AC1024: return "AC1024";
        }
        return NULL;
}

/*!
 * \brief converts a version string the version number.
 *
 */
static int acad_version_from_string
(
        const char * version_string
                /*!< Pointer to the version string. */
)
{
        if (strcmp ("AC1006", version_string) == 0)
                return AC1006;
        if (strcmp ("AC1009", version_string) == 0)
                return AC1009;
        if (strcmp ("AC1012", version_string) == 0)
                return AC1012;
        if (strcmp ("AC1014", version_string) == 0)
                return AC1014;
        if (strcmp ("AC1015", version_string) == 0)
                return AC1015;
        if (strcmp ("AC1016", version_string) == 0)
                return AC1016;
        if (strcmp ("AC1017", version_string) == 0)
                return AC1017;
        if (strcmp ("AC1018", version_string) == 0)
                return AC1018;
        if (strcmp ("AC1021", version_string) == 0)
                return AC1021;
        if (strcmp ("AC1024", version_string) == 0)
                return AC1024;
        /* in the case that it is an invalid version */
        return 0;
}


/*! * \brief Initialize a dxf header.
 *
 * Only initialize members which are valid for the given AutoCAD version.\n
 */
int
dxf_init_header
(
        DxfHeader dxf_header, /*!< DXF header to be initialized.\n */
        int acad_version_number /*!< AutoCAD version number.\n */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_init_header () function.\n", __FILE__, __LINE__);
#endif
        dxf_header.AcadVer = acad_version_string (acad_version_number);
        switch (acad_version_number)
        {
                case AC1009: /* AutoCAD 12 */
                {
                        dxf_header.DragMode = 2;
                        dxf_header.OSMode = 125;
                        dxf_header.BlipMode = 0;
                        dxf_header.Coords = 2;
                        dxf_header.AttDia = 0;
                        dxf_header.AttReq = 1;
                        dxf_header.Handling = 1;
                        dxf_header.HandSeed = strdup ("233");

                }
                case AC1012: /* AutoCAD 13 */
                {
                        dxf_header.DWGCodePage = strdup ("ANSI_1252");
                        dxf_header.DragMode = 2;
                        dxf_header.OSMode = 125;
                        dxf_header.CELTScale = 1.0;
                        dxf_header.DispSilH = 0;
                        dxf_header.DelObj = 1;
                        dxf_header.DimJUST = 0;
                        dxf_header.DimSD1 = 0;
                        dxf_header.DimSD2 = 0;
                        dxf_header.DimTOLJ = 1;
                        dxf_header.DimTZIN = 0;
                        dxf_header.DimALTZ = 0;
                        dxf_header.DimALTTZ = 0;
                        dxf_header.DimFIT = 3;
                        dxf_header.DimUPT = 0;
                        dxf_header.DimUNIT = 2;
                        dxf_header.DimDEC = 4;
                        dxf_header.DimTDEC = 4;
                        dxf_header.DimALTU = 2;
                        dxf_header.DimALTTD = 2;
                        dxf_header.DimTXSTY = strdup ("STANDARD");
                        dxf_header.DimAUNIT = 0;
                        dxf_header.BlipMode = 0;
                        dxf_header.ChamferC = 10.0;
                        dxf_header.ChamferD = 10.0;
                        dxf_header.Coords = 2;
                        dxf_header.AttDia = 0;
                        dxf_header.AttReq = 1;
                        dxf_header.Handling = 1;
                        dxf_header.HandSeed = strdup ("233");
                        dxf_header.TreeDepth = 3020;
                        dxf_header.PickStyle = 1;
                        dxf_header.CMLStyle = strdup ("STANDARD");
                        dxf_header.CMLJust = 0;
                        dxf_header.CMLScale = 1.0;
                        dxf_header.SaveImages = 1;
                }
                case AC1014: /* AutoCAD 14 */
                {
                        dxf_header.AcadMaintVer = 0;
                        dxf_header.DWGCodePage = strdup ("ANSI_1252");
                        dxf_header.DragMode = 2;
                        dxf_header.OSMode = 125;
                        dxf_header.CELTScale = 1.0;
                        dxf_header.DispSilH = 0;
                        dxf_header.DelObj = 1;
                        dxf_header.DimJUST = 0;
                        dxf_header.DimSD1 = 0;
                        dxf_header.DimSD2 = 0;
                        dxf_header.DimTOLJ = 1;
                        dxf_header.DimTZIN = 0;
                        dxf_header.DimALTZ = 0;
                        dxf_header.DimALTTZ = 0;
                        dxf_header.DimFIT = 3;
                        dxf_header.DimUPT = 0;
                        dxf_header.DimUNIT = 0;
                        dxf_header.DimDEC = 4;
                        dxf_header.DimTDEC = 4;
                        dxf_header.DimALTU = 2;
                        dxf_header.DimALTTD = 2;
                        dxf_header.DimTXSTY = strdup ("STANDARD");
                        dxf_header.DimAUNIT = 0;
                        dxf_header.BlipMode = 0;
                        dxf_header.ChamferC = 10.0;
                        dxf_header.ChamferD = 10.0;
                        dxf_header.Coords = 2;
                        dxf_header.AttDia = 0;
                        dxf_header.AttReq = 1;
                        dxf_header.Handling = 1;
                        dxf_header.HandSeed = strdup ("262");
                        dxf_header.TreeDepth = 3020;
                        dxf_header.PickStyle = 1;
                        dxf_header.CMLStyle = strdup ("STANDARD");
                        dxf_header.CMLJust = 0;
                        dxf_header.CMLScale = 1.0;
                        dxf_header.ProxyGraphics = 1;
                        dxf_header.Measurement = 0;
                }
                case AC1015: /* AutoCAD 2000 */
                {
                        dxf_header.AcadMaintVer = 20;
                        dxf_header.DWGCodePage = strdup ("ANSI_1252");
                        dxf_header.CELTScale = 1.0;
                        dxf_header.DispSilH = 0;
                        dxf_header.DimJUST = 0;
                        dxf_header.DimSD1 = 0;
                        dxf_header.DimSD2 = 0;
                        dxf_header.DimTOLJ = 1;
                        dxf_header.DimTZIN = 0;
                        dxf_header.DimALTZ = 0;
                        dxf_header.DimALTTZ = 0;
                        dxf_header.DimUPT = 0;
                        dxf_header.DimDEC = 4;
                        dxf_header.DimTDEC = 4;
                        dxf_header.DimALTU = 2;
                        dxf_header.DimALTTD = 2;
                        dxf_header.DimTXSTY = strdup ("STANDARD");
                        dxf_header.DimAUNIT = 0;
                        dxf_header.DimADEC = 0;
                        dxf_header.DimALTRND = 0.0;
                        dxf_header.DimAZIN = 0;
                        dxf_header.DimDSEP = 46;
                        dxf_header.DimATFIT = 3;
                        dxf_header.DimFRAC = 0;
                        dxf_header.DimLDRBLK = strdup ("");
                        dxf_header.DimLUNIT = 2;
                        dxf_header.DimLWD = -2;
                        dxf_header.DimLWE = -2;
                        dxf_header.DimTMOVE = 0;
                        dxf_header.ChamferC = 10.0;
                        dxf_header.ChamferD = 10.0;
                        dxf_header.TDUCreate = 0.0;
                        dxf_header.TDUUpdate = 0.0;
                        dxf_header.HandSeed = strdup ("274");
                        dxf_header.UCSBase = strdup ("");
                        dxf_header.UCSOrthoRef = strdup ("");
                        dxf_header.UCSOrthoView = 0;
                        dxf_header.UCSOrgTop.x0 = 0.0;
                        dxf_header.UCSOrgTop.y0 = 0.0;
                        dxf_header.UCSOrgTop.z0 = 0.0;
                        dxf_header.UCSOrgBottom.x0 = 0.0;
                        dxf_header.UCSOrgBottom.y0 = 0.0;
                        dxf_header.UCSOrgBottom.z0 = 0.0;
                        dxf_header.UCSOrgLeft.x0 = 0.0;
                        dxf_header.UCSOrgLeft.y0 = 0.0;
                        dxf_header.UCSOrgLeft.z0 = 0.0;
                        dxf_header.UCSOrgRight.x0 = 0.0;
                        dxf_header.UCSOrgRight.y0 = 0.0;
                        dxf_header.UCSOrgRight.z0 = 0.0;
                        dxf_header.UCSOrgFront.x0 = 0.0;
                        dxf_header.UCSOrgFront.y0 = 0.0;
                        dxf_header.UCSOrgFront.z0 = 0.0;
                        dxf_header.UCSOrgBack.x0 = 0.0;
                        dxf_header.UCSOrgBack.y0 = 0.0;
                        dxf_header.UCSOrgBack.z0 = 0.0;
                        dxf_header.PUCSBase = strdup ("");
                        dxf_header.PUCSOrthoRef = strdup ("");
                        dxf_header.PUCSOrthoView = 0;
                        dxf_header.PUCSOrgTop.x0 = 0.0;
                        dxf_header.PUCSOrgTop.y0 = 0.0;
                        dxf_header.PUCSOrgTop.z0 = 0.0;
                        dxf_header.PUCSOrgBottom.x0 = 0.0;
                        dxf_header.PUCSOrgBottom.y0 = 0.0;
                        dxf_header.PUCSOrgBottom.z0 = 0.0;
                        dxf_header.PUCSOrgLeft.x0 = 0.0;
                        dxf_header.PUCSOrgLeft.y0 = 0.0;
                        dxf_header.PUCSOrgLeft.z0 = 0.0;
                        dxf_header.PUCSOrgRight.x0 = 0.0;
                        dxf_header.PUCSOrgRight.y0 = 0.0;
                        dxf_header.PUCSOrgRight.z0 = 0.0;
                        dxf_header.PUCSOrgFront.x0 = 0.0;
                        dxf_header.PUCSOrgFront.y0 = 0.0;
                        dxf_header.PUCSOrgFront.z0 = 0.0;
                        dxf_header.PUCSOrgBack.x0 = 0.0;
                        dxf_header.PUCSOrgBack.y0 = 0.0;
                        dxf_header.PUCSOrgBack.z0 = 0.0;
                        dxf_header.TreeDepth = 3020;
                        dxf_header.CMLStyle = strdup ("STANDARD");
                        dxf_header.CMLJust = 0;
                        dxf_header.CMLScale = 1.0;
                        dxf_header.ProxyGraphics = 1;
                        dxf_header.Measurement = 0;
                        dxf_header.CELWeight = -1;
                        dxf_header.EndCaps = 0;
                        dxf_header.JoinStyle = 0;
                        dxf_header.LWDisplay = 0;
                        dxf_header.InsUnits = 0;
                        dxf_header.HyperLinkBase = strdup ("");
                        dxf_header.StyleSheet = strdup ("");
                        dxf_header.XEdit = 1;
                        dxf_header.CEPSNType = 0;
                        dxf_header.PStyleMode = 1;
                        dxf_header.FingerPrintGUID = strdup ("");
                        dxf_header.VersionGUID = strdup ("");
                        dxf_header.ExtNames = 0;
                        dxf_header.PSVPScale = 0.0;
                        dxf_header.OLEStartUp = 0;
                }
                case AC1018: /* AutoCAD 2004 */
                {
                        dxf_header.AcadMaintVer = 0;
                        dxf_header.DWGCodePage = strdup ("ANSI_1252");
                        dxf_header.CELTScale = 1.0;
                        dxf_header.DispSilH = 0;
                        dxf_header.DimJUST = 0;
                        dxf_header.DimSD1 = 0;
                        dxf_header.DimSD2 = 0;
                        dxf_header.DimTOLJ = 1;
                        dxf_header.DimTZIN = 0;
                        dxf_header.DimALTZ = 0;
                        dxf_header.DimALTTZ = 0;
                        dxf_header.DimUPT = 0;
                        dxf_header.DimDEC = 4;
                        dxf_header.DimTDEC = 4;
                        dxf_header.DimALTU = 2;
                        dxf_header.DimALTTD = 2;
                        dxf_header.DimTXSTY = strdup ("STANDARD");
                        dxf_header.DimAUNIT = 0;
                        dxf_header.DimADEC = 0;
                        dxf_header.DimALTRND = 0.0;
                        dxf_header.DimAZIN = 0;
                        dxf_header.DimDSEP = 46;
                        dxf_header.DimATFIT = 3;
                        dxf_header.DimFRAC = 0;
                        dxf_header.DimLDRBLK = strdup ("");
                        dxf_header.DimLUNIT = 2;
                        dxf_header.DimLWD = -2;
                        dxf_header.DimLWE = -2;
                        dxf_header.DimTMOVE = 0;
                        dxf_header.ChamferC = 10.0;
                        dxf_header.ChamferD = 10.0;
                        dxf_header.TDUCreate = 0.0;
                        dxf_header.TDUUpdate = 0.0;
                        dxf_header.HandSeed = strdup ("26A");
                        dxf_header.UCSBase = strdup ("");
                        dxf_header.UCSOrthoRef = strdup ("");
                        dxf_header.UCSOrthoView = 0;
                        dxf_header.UCSOrgTop.x0 = 0.0;
                        dxf_header.UCSOrgTop.y0 = 0.0;
                        dxf_header.UCSOrgTop.z0 = 0.0;
                        dxf_header.UCSOrgBottom.x0 = 0.0;
                        dxf_header.UCSOrgBottom.y0 = 0.0;
                        dxf_header.UCSOrgBottom.z0 = 0.0;
                        dxf_header.UCSOrgLeft.x0 = 0.0;
                        dxf_header.UCSOrgLeft.y0 = 0.0;
                        dxf_header.UCSOrgLeft.z0 = 0.0;
                        dxf_header.UCSOrgRight.x0 = 0.0;
                        dxf_header.UCSOrgRight.y0 = 0.0;
                        dxf_header.UCSOrgRight.z0 = 0.0;
                        dxf_header.UCSOrgFront.x0 = 0.0;
                        dxf_header.UCSOrgFront.y0 = 0.0;
                        dxf_header.UCSOrgFront.z0 = 0.0;
                        dxf_header.UCSOrgBack.x0 = 0.0;
                        dxf_header.UCSOrgBack.y0 = 0.0;
                        dxf_header.UCSOrgBack.z0 = 0.0;
                        dxf_header.PUCSBase = strdup ("");
                        dxf_header.PUCSOrthoRef = strdup ("");
                        dxf_header.PUCSOrthoView = 0;
                        dxf_header.PUCSOrgTop.x0 = 0.0;
                        dxf_header.PUCSOrgTop.y0 = 0.0;
                        dxf_header.PUCSOrgTop.z0 = 0.0;
                        dxf_header.PUCSOrgBottom.x0 = 0.0;
                        dxf_header.PUCSOrgBottom.y0 = 0.0;
                        dxf_header.PUCSOrgBottom.z0 = 0.0;
                        dxf_header.PUCSOrgLeft.x0 = 0.0;
                        dxf_header.PUCSOrgLeft.y0 = 0.0;
                        dxf_header.PUCSOrgLeft.z0 = 0.0;
                        dxf_header.PUCSOrgRight.x0 = 0.0;
                        dxf_header.PUCSOrgRight.y0 = 0.0;
                        dxf_header.PUCSOrgRight.z0 = 0.0;
                        dxf_header.PUCSOrgFront.x0 = 0.0;
                        dxf_header.PUCSOrgFront.y0 = 0.0;
                        dxf_header.PUCSOrgFront.z0 = 0.0;
                        dxf_header.PUCSOrgBack.x0 = 0.0;
                        dxf_header.PUCSOrgBack.y0 = 0.0;
                        dxf_header.PUCSOrgBack.z0 = 0.0;
                        dxf_header.TreeDepth = 3020;
                        dxf_header.CMLStyle = strdup ("STANDARD");
                        dxf_header.CMLJust = 0;
                        dxf_header.CMLScale = 1.0;
                        dxf_header.ProxyGraphics = 1;
                        dxf_header.Measurement = 0;
                        dxf_header.CELWeight = -1;
                        dxf_header.EndCaps = 0;
                        dxf_header.JoinStyle = 0;
                        dxf_header.LWDisplay = 0;
                        dxf_header.InsUnits = 0;
                        dxf_header.HyperLinkBase = strdup ("");
                        dxf_header.StyleSheet = strdup ("");
                        dxf_header.XEdit = 1;
                        dxf_header.CEPSNType = 0;
                        dxf_header.PStyleMode = 1;
                        dxf_header.FingerPrintGUID = strdup ("");
                        dxf_header.VersionGUID = strdup ("");
                        dxf_header.ExtNames = 0;
                        dxf_header.PSVPScale = 0.0;
                        dxf_header.OLEStartUp = 0;
                        dxf_header.SortEnts = 127;
                        dxf_header.IndexCtl = 0;
                        dxf_header.HideText = 0;
                        dxf_header.XClipFrame = 0;
                        dxf_header.HaloGap = 0;
                        dxf_header.ObsColor = 257;
                        dxf_header.ObsLType = 0;
                        dxf_header.InterSectionDisplay = 0;
                        dxf_header.InterSectionColor = 257;
                        dxf_header.DimASSOC = 1;
                        dxf_header.ProjectName = strdup ("");
                }
        }
        dxf_header.AcadVer = strdup (acad_version_string (acad_version_number));
        dxf_header.InsBase.x0 = 0.0;
        dxf_header.InsBase.y0 = 0.0;
        dxf_header.InsBase.z0 = 0.0;
        dxf_header.ExtMin.x0 = 0.0;
        dxf_header.ExtMin.y0 = 0.0;
        dxf_header.ExtMin.z0 = 0.0;
        dxf_header.ExtMax.x0 = 0.0;
        dxf_header.ExtMax.y0 = 0.0;
        dxf_header.ExtMax.z0 = 0.0;
        dxf_header.LimMin.x0 = 0.0;
        dxf_header.LimMin.y0 = 0.0;
        dxf_header.LimMax.x0 = 0.0;
        dxf_header.LimMax.y0 = 0.0;
        dxf_header.OrthoMode = 0;
        dxf_header.RegenMode = 0;
        dxf_header.FillMode = 1;
        dxf_header.QTextMode = 0;
        dxf_header.MirrText = 1;
        dxf_header.LTScale = 1.0;
        dxf_header.AttMode = 1;
        dxf_header.TextSize = 2.5;
        dxf_header.TraceWid = 1.0;
        dxf_header.TextStyle = strdup ("STANDARD");
        dxf_header.CELType = strdup ("BYLAYER");
        dxf_header.CLayer = strdup ("0");
        dxf_header.CEColor = 256;
        dxf_header.DimSCALE = 1.0;
        dxf_header.DimASZ = 2.5;
        dxf_header.DimEXO = 0.625;
        dxf_header.DimDLI = 3.75;
        dxf_header.DimRND = 0.0;
        dxf_header.DimDLE = 0.0;
        dxf_header.DimEXE = 1.25;
        dxf_header.DimTP = 0.0;
        dxf_header.DimTM = 0.0;
        dxf_header.DimTXT = 2.5;
        dxf_header.DimCEN = 2.5;
        dxf_header.DimTSZ = 0.0;
        dxf_header.DimTOL = 0;
        dxf_header.DimLIM = 0;
        dxf_header.DimTIH = 0;
        dxf_header.DimTOH = 0;
        dxf_header.DimSE1 = 0;
        dxf_header.DimSE2 = 0;
        dxf_header.DimTAD = 1;
        dxf_header.DimZIN = 8;
        dxf_header.DimBLK = strdup ("");
        dxf_header.DimASO = 1;
        dxf_header.DimSHO = 1;
        dxf_header.DimPOST = strdup ("");
        dxf_header.DimAPOST = strdup ("");
        dxf_header.DimALT = 0;
        dxf_header.DimALTD = 4;
        dxf_header.DimALTF = 0.0394;
        dxf_header.DimLFAC = 1.0;
        dxf_header.DimTOFL = 1;
        dxf_header.DimTVP = 0.0;
        dxf_header.DimTIX = 0;
        dxf_header.DimSOXD = 0;
        dxf_header.DimSAH = 0;
        dxf_header.DimBLK1 = strdup ("");
        dxf_header.DimBLK2 = strdup ("");
        dxf_header.DimCLRD = 0;
        dxf_header.DimCLRE = 0;
        dxf_header.DimCLRT = 0;
        dxf_header.DimTFAC = 1.0;
        dxf_header.DimGAP = 0.625;
        dxf_header.LUnits = 2;
        dxf_header.LUPrec = 4;
        dxf_header.Sketchinc = 1.0;
        dxf_header.FilletRad = 1.0;
        dxf_header.AUnits = 0;
        dxf_header.AUPrec = 0;
        dxf_header.Menu = strdup (".");
        dxf_header.Elevation = 0.0;
        dxf_header.PElevation = 0.0;
        dxf_header.Thickness = 0.0;
        dxf_header.LimCheck = 0;
        dxf_header.ChamferA = 10.0;
        dxf_header.ChamferB = 10.0;
        dxf_header.SKPoly = 0;
        dxf_header.TDCreate = 0.0;
        dxf_header.TDUpdate = 0.0;
        dxf_header.TDInDWG = 0.0;
        dxf_header.TDUSRTimer = 0.0;
        dxf_header.USRTimer = 1;
        dxf_header.AngBase = 0.0;
        dxf_header.AngDir = 0;
        dxf_header.PDMode = 98;
        dxf_header.PDSize = 0.0;
        dxf_header.PLineWid = 0.0;
        dxf_header.SPLFrame = 0;
        dxf_header.SPLineType = 6;
        dxf_header.SPLineSegs = 8;
        dxf_header.SurfTab1 = 6;
        dxf_header.SurfTab2 = 6;
        dxf_header.SurfType = 6;
        dxf_header.SurfU = 6;
        dxf_header.SurfV = 6;
        dxf_header.UCSName = strdup ("");
        dxf_header.UCSOrg.x0 = 0.0;
        dxf_header.UCSOrg.y0 = 0.0;
        dxf_header.UCSOrg.z0 = 0.0;
        dxf_header.UCSXDir.x0 = 0.0;
        dxf_header.UCSXDir.y0 = 0.0;
        dxf_header.UCSXDir.z0 = 0.0;
        dxf_header.UCSYDir.x0 = 0.0;
        dxf_header.UCSYDir.y0 = 0.0;
        dxf_header.UCSYDir.z0 = 0.0;
        dxf_header.PUCSName = strdup ("");
        dxf_header.PUCSOrg.x0 = 0.0;
        dxf_header.PUCSOrg.y0 = 0.0;
        dxf_header.PUCSOrg.z0 = 0.0;
        dxf_header.PUCSXDir.x0 = 0.0;
        dxf_header.PUCSXDir.y0 = 0.0;
        dxf_header.PUCSXDir.z0 = 0.0;
        dxf_header.PUCSYDir.x0 = 0.0;
        dxf_header.PUCSYDir.y0 = 0.0;
        dxf_header.PUCSYDir.z0 = 0.0;
        dxf_header.UserI1 = 0;
        dxf_header.UserI2 = 0;
        dxf_header.UserI3 = 0;
        dxf_header.UserI4 = 0;
        dxf_header.UserI5 = 0;
        dxf_header.UserR1 = 0.0;
        dxf_header.UserR2 = 0.0;
        dxf_header.UserR3 = 0.0;
        dxf_header.UserR4 = 0.0;
        dxf_header.UserR5 = 0.0;
        dxf_header.WorldView = 0;
        dxf_header.ShadEdge = 3;
        dxf_header.ShadeDif = 70;
        dxf_header.TileMode = 1;
        dxf_header.MaxActVP = 48;
        dxf_header.PInsBase.x0 = 0.0;
        dxf_header.PInsBase.y0 = 0.0;
        dxf_header.PInsBase.z0 = 0.0;
        dxf_header.PLimCheck = 0;
        dxf_header.PExtMin.x0 = 0.0;
        dxf_header.PExtMin.y0 = 0.0;
        dxf_header.PExtMin.z0 = 0.0;
        dxf_header.PExtMax.x0 = 0.0;
        dxf_header.PExtMax.y0 = 0.0;
        dxf_header.PExtMax.z0 = 0.0;
        dxf_header.PLimMin.x0 = 0.0;
        dxf_header.PLimMin.y0 = 0.0;
        dxf_header.PLimMax.x0 = 0.0;
        dxf_header.PLimMax.y0 = 0.0;
        dxf_header.UnitMode = 0;
        dxf_header.VisRetain = 1;
        dxf_header.PLineGen = 0;
        dxf_header.PSLTScale = 1;
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_init_header () function.\n", __FILE__, __LINE__);
#endif
                return (EXIT_SUCCESS);
}


/*!
 * \brief Write DXF output to a file for a metric DXF header.
 *
 * Fall back for a situation where no default metric header file exists.\n
 * Basically this function writes down a DXF header based on metric values.\n
 * Included are:\n
 * <ul>
 *   <li>HEADER
 *   <li>CLASSES
 *   <li>TABLES
 *   <ul>
 *     <li>VPORT
 *     <li>LTYPE
 *     <li>LAYER
 *     <li>STYLE
 *     <li>VIEW
 *     <li>UCS
 *     <li>APPID
 *     <li>DIMSTYLE
 *   </ul>
 * </ul>
 */
static void
dxf_write_header_metric_new
(
        FILE *fp /*!< file pointer to output file (or device) */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_write_header_metric_new () function.\n", __FILE__, __LINE__);
#endif
        fprintf (fp, "  0\nSECTION\n");
        fprintf (fp, "  2\nHEADER\n");
        fprintf (fp, "  9\n$ACADVER\n  1\nAC1014\n");
        fprintf (fp, "  9\n$ACADMAINTVER\n 70\n     0\n");
        fprintf (fp, "  9\n$DWGCODEPAGE\n  3\nANSI_1252\n");
        fprintf (fp, "  9\n$INSBASE\n 10\n0.0\n 20\n0.0\n 30\n0.0\n");
        fprintf (fp, "  9\n$EXTMIN\n 10\n-0.012816\n 20\n-0.009063\n 30\n-0.001526\n");
        fprintf (fp, "  9\n$EXTMAX\n 10\n88.01056\n 20\n35.022217\n 30\n0.0\n");
        fprintf (fp, "  9\n$LIMMIN\n 10\n0.0\n 20\n0.0\n");
        fprintf (fp, "  9\n$LIMMAX\n 10\n420.0\n 20\n297.0\n");
        fprintf (fp, "  9\n$ORTHOMODE\n 70\n     0\n");
        fprintf (fp, "  9\n$REGENMODE\n 70\n     1\n");
        fprintf (fp, "  9\n$FILLMODE\n 70\n     1\n");
        fprintf (fp, "  9\n$QTEXTMODE\n 70\n     0\n");
        fprintf (fp, "  9\n$MIRRTEXT\n 70\n     1\n");
        fprintf (fp, "  9\n$DRAGMODE\n 70\n     2\n");
        fprintf (fp, "  9\n$LTSCALE\n 40\n1.0\n");
        fprintf (fp, "  9\n$OSMODE\n 70\n   125\n");
        fprintf (fp, "  9\n$ATTMODE\n 70\n     1\n");
        fprintf (fp, "  9\n$TEXTSIZE\n 40\n2.5\n");
        fprintf (fp, "  9\n$TRACEWID\n 40\n1.0\n");
        fprintf (fp, "  9\n$TEXTSTYLE\n  7\nSTANDARD\n");
        fprintf (fp, "  9\n$CLAYER\n  8\n0\n");
        fprintf (fp, "  9\n$CELTYPE\n  6\nBYLAYER\n");
        fprintf (fp, "  9\n$CECOLOR\n 62\n   256\n");
        fprintf (fp, "  9\n$CELTSCALE\n 40\n1.0\n");
        fprintf (fp, "  9\n$DELOBJ\n 70\n     1\n");
        fprintf (fp, "  9\n$DISPSILH\n 70\n     0\n");
        fprintf (fp, "  9\n$DIMSCALE\n 40\n1.0\n");
        fprintf (fp, "  9\n$DIMASZ\n 40\n2.5\n");
        fprintf (fp, "  9\n$DIMEXO\n 40\n0.625\n");
        fprintf (fp, "  9\n$DIMDLI\n 40\n3.75\n");
        fprintf (fp, "  9\n$DIMRND\n 40\n0.0\n");
        fprintf (fp, "  9\n$DIMDLE\n 40\n0.0\n");
        fprintf (fp, "  9\n$DIMEXE\n 40\n1.25\n");
        fprintf (fp, "  9\n$DIMTP\n 40\n0.0\n");
        fprintf (fp, "  9\n$DIMTM\n 40\n0.0\n");
        fprintf (fp, "  9\n$DIMTXT\n 40\n2.5\n");
        fprintf (fp, "  9\n$DIMCEN\n 40\n2.5\n");
        fprintf (fp, "  9\n$DIMTSZ\n 40\n0.0\n");
        fprintf (fp, "  9\n$DIMTOL\n 70\n     0\n");
        fprintf (fp, "  9\n$DIMLIM\n 70\n     0\n");
        fprintf (fp, "  9\n$DIMTIH\n 70\n     0\n");
        fprintf (fp, "  9\n$DIMTOH\n 70\n     0\n");
        fprintf (fp, "  9\n$DIMSE1\n 70\n     0\n");
        fprintf (fp, "  9\n$DIMSE2\n 70\n     0\n");
        fprintf (fp, "  9\n$DIMTAD\n 70\n     1\n");
        fprintf (fp, "  9\n$DIMZIN\n 70\n     8\n");
        fprintf (fp, "  9\n$DIMBLK\n  1\n\n");
        fprintf (fp, "  9\n$DIMASO\n 70\n     1\n");
        fprintf (fp, "  9\n$DIMSHO\n 70\n     1\n");
        fprintf (fp, "  9\n$DIMPOST\n  1\n\n");
        fprintf (fp, "  9\n$DIMAPOST\n  1\n\n");
        fprintf (fp, "  9\n$DIMALT\n 70\n     0\n");
        fprintf (fp, "  9\n$DIMALTD\n 70\n     4\n");
        fprintf (fp, "  9\n$DIMALTF\n 40\n0.0394\n");
        fprintf (fp, "  9\n$DIMLFAC\n 40\n1.0\n");
        fprintf (fp, "  9\n$DIMTOFL\n 70\n     1\n");
        fprintf (fp, "  9\n$DIMTVP\n 40\n0.0\n");
        fprintf (fp, "  9\n$DIMTIX\n 70\n     0\n");
        fprintf (fp, "  9\n$DIMSOXD\n 70\n     0\n");
        fprintf (fp, "  9\n$DIMSAH\n 70\n     0\n");
        fprintf (fp, "  9\n$DIMBLK1\n  1\n\n");
        fprintf (fp, "  9\n$DIMBLK2\n  1\n\n");
        fprintf (fp, "  9\n$DIMSTYLE\n  2\nSTANDARD\n");
        fprintf (fp, "  9\n$DIMCLRD\n 70\n     0\n");
        fprintf (fp, "  9\n$DIMCLRE\n 70\n     0\n");
        fprintf (fp, "  9\n$DIMCLRT\n 70\n     0\n");
        fprintf (fp, "  9\n$DIMTFAC\n 40\n1.0\n");
        fprintf (fp, "  9\n$DIMGAP\n 40\n0.625\n");
        fprintf (fp, "  9\n$DIMJUST\n 70\n     0\n");
        fprintf (fp, "  9\n$DIMSD1\n 70\n     0\n");
        fprintf (fp, "  9\n$DIMSD2\n 70\n     0\n");
        fprintf (fp, "  9\n$DIMTOLJ\n 70\n     1\n");
        fprintf (fp, "  9\n$DIMTZIN\n 70\n     0\n");
        fprintf (fp, "  9\n$DIMALTZ\n 70\n     0\n");
        fprintf (fp, "  9\n$DIMALTTZ\n 70\n     0\n");
        fprintf (fp, "  9\n$DIMFIT\n 70\n     3\n");
        fprintf (fp, "  9\n$DIMUPT\n 70\n     0\n");
        fprintf (fp, "  9\n$DIMUNIT\n 70\n     2\n");
        fprintf (fp, "  9\n$DIMDEC\n 70\n     4\n");
        fprintf (fp, "  9\n$DIMTDEC\n 70\n     4\n");
        fprintf (fp, "  9\n$DIMALTU\n 70\n     2\n");
        fprintf (fp, "  9\n$DIMALTTD\n 70\n     2\n");
        fprintf (fp, "  9\n$DIMTXSTY\n  7\nSTANDARD\n");
        fprintf (fp, "  9\n$DIMAUNIT\n 70\n     0\n");
        fprintf (fp, "  9\n$LUNITS\n 70\n     2\n");
        fprintf (fp, "  9\n$LUPREC\n 70\n     4\n");
        fprintf (fp, "  9\n$SKETCHINC\n 40\n1.0\n");
        fprintf (fp, "  9\n$FILLETRAD\n 40\n1.0\n");
        fprintf (fp, "  9\n$AUNITS\n 70\n     0\n");
        fprintf (fp, "  9\n$AUPREC\n 70\n     0\n");
        fprintf (fp, "  9\n$MENU\n  1\n.\n");
        fprintf (fp, "  9\n$ELEVATION\n 40\n0.0\n");
        fprintf (fp, "  9\n$PELEVATION\n 40\n0.0\n");
        fprintf (fp, "  9\n$THICKNESS\n 40\n0.0\n");
        fprintf (fp, "  9\n$LIMCHECK\n 70\n     0\n");
        fprintf (fp, "  9\n$BLIPMODE\n 70\n     0\n");
        fprintf (fp, "  9\n$CHAMFERA\n 40\n10.0\n");
        fprintf (fp, "  9\n$CHAMFERB\n 40\n10.0\n");
        fprintf (fp, "  9\n$CHAMFERC\n 40\n0.0\n");
        fprintf (fp, "  9\n$CHAMFERD\n 40\n0.0\n");
        fprintf (fp, "  9\n$SKPOLY\n 70\n     0\n");
        fprintf (fp, "  9\n$TDCREATE\n 40\n2452949.844398842\n");
        fprintf (fp, "  9\n$TDUPDATE\n 40\n2453105.563639282\n");
        fprintf (fp, "  9\n$TDINDWG\n 40\n0.0994079282\n");
        fprintf (fp, "  9\n$TDUSRTIMER\n 40\n0.0994079282\n");
        fprintf (fp, "  9\n$USRTIMER\n 70\n     1\n");
        fprintf (fp, "  9\n$ANGBASE\n 50\n0.0\n");
        fprintf (fp, "  9\n$ANGDIR\n 70\n     0\n");
        fprintf (fp, "  9\n$PDMODE\n 70\n    98\n");
        fprintf (fp, "  9\n$PDSIZE\n 40\n0.0\n");
        fprintf (fp, "  9\n$PLINEWID\n 40\n0.0\n");
        fprintf (fp, "  9\n$COORDS\n 70\n     2\n");
        fprintf (fp, "  9\n$SPLFRAME\n 70\n     0\n");
        fprintf (fp, "  9\n$SPLINETYPE\n 70\n     6\n");
        fprintf (fp, "  9\n$SPLINESEGS\n 70\n     8\n");
        fprintf (fp, "  9\n$ATTDIA\n 70\n     0\n");
        fprintf (fp, "  9\n$ATTREQ\n 70\n     1\n");
        fprintf (fp, "  9\n$HANDLING\n 70\n     1\n");
        fprintf (fp, "  9\n$HANDSEED\n  5\n262\n");
        fprintf (fp, "  9\n$SURFTAB1\n 70\n     6\n");
        fprintf (fp, "  9\n$SURFTAB2\n 70\n     6\n");
        fprintf (fp, "  9\n$SURFTYPE\n 70\n     6\n");
        fprintf (fp, "  9\n$SURFU\n 70\n     6\n");
        fprintf (fp, "  9\n$SURFV\n 70\n     6\n");
        fprintf (fp, "  9\n$UCSNAME\n  2\n\n");
        fprintf (fp, "  9\n$UCSORG\n 10\n0.0\n 20\n0.0\n 30\n0.0\n");
        fprintf (fp, "  9\n$UCSXDIR\n 10\n1.0\n 20\n0.0\n 30\n0.0\n");
        fprintf (fp, "  9\n$UCSYDIR\n 10\n0.0\n 20\n1.0\n 30\n0.0\n");
        fprintf (fp, "  9\n$PUCSNAME\n  2\n\n");
        fprintf (fp, "  9\n$PUCSORG\n 10\n0.0\n 20\n0.0\n 30\n0.0\n");
        fprintf (fp, "  9\n$PUCSXDIR\n 10\n1.0\n 20\n0.0\n 30\n0.0\n");
        fprintf (fp, "  9\n$PUCSYDIR\n 10\n0.0\n 20\n1.0\n 30\n0.0\n");
        fprintf (fp, "  9\n$USERI1\n 70\n     0\n");
        fprintf (fp, "  9\n$USERI2\n 70\n     0\n");
        fprintf (fp, "  9\n$USERI3\n 70\n     0\n");
        fprintf (fp, "  9\n$USERI4\n 70\n     0\n");
        fprintf (fp, "  9\n$USERI5\n 70\n     0\n");
        fprintf (fp, "  9\n$USERR1\n 40\n0.0\n");
        fprintf (fp, "  9\n$USERR2\n 40\n0.0\n");
        fprintf (fp, "  9\n$USERR3\n 40\n0.0\n");
        fprintf (fp, "  9\n$USERR4\n 40\n0.0\n");
        fprintf (fp, "  9\n$USERR5\n 40\n0.0\n");
        fprintf (fp, "  9\n$WORLDVIEW\n 70\n     1\n");
        fprintf (fp, "  9\n$SHADEDGE\n 70\n     3\n");
        fprintf (fp, "  9\n$SHADEDIF\n 70\n    70\n");
        fprintf (fp, "  9\n$TILEMODE\n 70\n     1\n");
        fprintf (fp, "  9\n$MAXACTVP\n 70\n    48\n");
        fprintf (fp, "  9\n$PINSBASE\n 10\n0.0\n 20\n0.0\n 30\n0.0\n");
        fprintf (fp, "  9\n$PLIMCHECK\n 70\n     0\n");
        fprintf (fp, "  9\n$PEXTMIN\n 10\n1.000000E+20\n 20\n1.000000E+20\n 30\n1.000000E+20\n");
        fprintf (fp, "  9\n$PEXTMAX\n 10\n-1.000000E+20\n 20\n-1.000000E+20\n 30\n-1.000000E+20\n");
        fprintf (fp, "  9\n$PLIMMIN\n 10\n0.0\n 20\n0.0\n");
        fprintf (fp, "  9\n$PLIMMAX\n 10\n420.0\n 20\n297.0");
        fprintf (fp, "  9\n$UNITMODE\n 70\n     0\n");
        fprintf (fp, "  9\n$VISRETAIN\n 70\n     1\n");
        fprintf (fp, "  9\n$PLINEGEN\n 70\n     0\n");
        fprintf (fp, "  9\n$PSLTSCALE\n 70\n     1\n");
        fprintf (fp, "  9\n$TREEDEPTH\n 70\n  3020\n");
        fprintf (fp, "  9\n$PICKSTYLE\n 70\n     1\n");
        fprintf (fp, "  9\n$CMLSTYLE\n  2\nSTANDARD\n");
        fprintf (fp, "  9\n$CMLJUST\n 70\n     0\n");
        fprintf (fp, "  9\n$CMLSCALE\n 40\n1.0\n");
        fprintf (fp, "  9\n$PROXYGRAPHICS\n 70\n     1\n");
        fprintf (fp, "  9\n$MEASUREMENT\n 70\n     0\n");
        fprintf (fp, "  0\nENDSEC\n");
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_write_header_metric_new () function.\n", __FILE__, __LINE__);
#endif
}


/*!
 * \brief Write DXF output to a file for a dxf header.
 */
int
dxf_write_header
(
        FILE *fp,
        DxfHeader dxf_header,
        int acad_version_number
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_write_header2 () function.\n", __FILE__, __LINE__);
#endif
        char *dxf_entity_name = strdup ("HEADER");

        dxf_write_section (fp, dxf_entity_name);
        fprintf (fp, "  9\n$ACADVER\n  1\n%s\n", dxf_header.AcadVer);
        if (acad_version_number >= AC1014) fprintf (fp, "  9\n$ACADMAINTVER\n 70\n%i\n", dxf_header.AcadMaintVer);
        if (acad_version_number >= AC1012) fprintf (fp, "  9\n$DWGCODEPAGE\n  3\n%s\n", dxf_header.DWGCodePage);
        fprintf (fp, "  9\n$INSBASE\n 10\n%f\n 20\n%f\n 30\n%f\n", dxf_header.InsBase.x0, dxf_header.InsBase.y0, dxf_header.InsBase.z0);
        fprintf (fp, "  9\n$EXTMIN\n 10\n%f\n 20\n%f\n 30\n%f\n", dxf_header.ExtMin.x0, dxf_header.ExtMin.y0, dxf_header.ExtMin.z0);
        fprintf (fp, "  9\n$EXTMAX\n 10\n%f\n 20\n%f\n 30\n%f\n", dxf_header.ExtMax.x0, dxf_header.ExtMax.y0, dxf_header.ExtMax.z0);
        fprintf (fp, "  9\n$LIMMIN\n 10\n%f\n 20\n%f\n", dxf_header.LimMin.x0, dxf_header.LimMin.y0);
        fprintf (fp, "  9\n$LIMMAX\n 10\n%f\n 20\n%f\n", dxf_header.LimMax.x0, dxf_header.LimMax.y0);
        fprintf (fp, "  9\n$ORTHOMODE\n 70\n%i\n", dxf_header.OrthoMode);
        fprintf (fp, "  9\n$REGENMODE\n 70\n%i\n", dxf_header.RegenMode);
        fprintf (fp, "  9\n$FILLMODE\n 70\n%i\n", dxf_header.FillMode);
        fprintf (fp, "  9\n$QTEXTMODE\n 70\n%i\n", dxf_header.QTextMode);
        fprintf (fp, "  9\n$MIRRTEXT\n 70\n%i\n", dxf_header.MirrText);
        if (acad_version_number <= AC1015) fprintf (fp, "  9\n$DRAGMODE\n 70\n%i\n", dxf_header.DragMode);
        fprintf (fp, "  9\n$LTSCALE\n 40\n%f\n", dxf_header.LTScale);
        if (acad_version_number <= AC1014) fprintf (fp, "  9\n$OSMODE\n 70\n%i\n", dxf_header.OSMode);
        fprintf (fp, "  9\n$ATTMODE\n 70\n%i\n", dxf_header.AttMode);
        fprintf (fp, "  9\n$TEXTSIZE\n 40\n%f\n", dxf_header.TextSize);
        fprintf (fp, "  9\n$TRACEWID\n 40\n%f\n", dxf_header.TraceWid);
        fprintf (fp, "  9\n$TEXTSTYLE\n  7\n%s\n", dxf_header.TextStyle);
        fprintf (fp, "  9\n$CLAYER\n  8\n%s\n", dxf_header.CLayer);
        fprintf (fp, "  9\n$CELTYPE\n  6\n%s\n", dxf_header.CELType);
        fprintf (fp, "  9\n$CECOLOR\n 62\n%i\n", dxf_header.CEColor);
        if (acad_version_number >= AC1012) fprintf (fp, "  9\n$CELTSCALE\n 40\n%f\n", dxf_header.CELTScale);
        if ((acad_version_number == AC1012) || (acad_version_number == AC1014)) fprintf (fp, "  9\n$DELOBJ\n 70\n%i\n", dxf_header.DelObj);
        if (acad_version_number <= AC1012) fprintf (fp, "  9\n$DISPSILH\n 70\n%i\n", dxf_header.DispSilH);
        fprintf (fp, "  9\n$DIMSCALE\n 40\n%f\n", dxf_header.DimSCALE);
        fprintf (fp, "  9\n$DIMASZ\n 40\n%f\n", dxf_header.DimASZ);
        fprintf (fp, "  9\n$DIMEXO\n 40\n%f\n", dxf_header.DimEXO);
        fprintf (fp, "  9\n$DIMDLI\n 40\n%f\n", dxf_header.DimDLI);
        fprintf (fp, "  9\n$DIMRND\n 40\n%f\n", dxf_header.DimRND);
        fprintf (fp, "  9\n$DIMDLE\n 40\n%f\n", dxf_header.DimDLE);
        fprintf (fp, "  9\n$DIMEXE\n 40\n%f\n", dxf_header.DimEXE);
        fprintf (fp, "  9\n$DIMTP\n 40\n%f\n", dxf_header.DimTP);
        fprintf (fp, "  9\n$DIMTM\n 40\n%f\n", dxf_header.DimTM);
        fprintf (fp, "  9\n$DIMTXT\n 40\n%f\n", dxf_header.DimTXT);
        fprintf (fp, "  9\n$DIMCEN\n 40\n%f\n", dxf_header.DimCEN);
        fprintf (fp, "  9\n$DIMTSZ\n 40\n%f\n", dxf_header.DimTSZ);
        fprintf (fp, "  9\n$DIMTOL\n 70\n%i\n", dxf_header.DimTOL);
        fprintf (fp, "  9\n$DIMLIM\n 70\n%i\n", dxf_header.DimLIM);
        fprintf (fp, "  9\n$DIMTIH\n 70\n%i\n", dxf_header.DimTIH);
        fprintf (fp, "  9\n$DIMTOH\n 70\n%i\n", dxf_header.DimTOH);
        fprintf (fp, "  9\n$DIMSE1\n 70\n%i\n", dxf_header.DimSE1);
        fprintf (fp, "  9\n$DIMSE2\n 70\n%i\n", dxf_header.DimSE2);
        fprintf (fp, "  9\n$DIMTAD\n 70\n%i\n", dxf_header.DimTAD);
        fprintf (fp, "  9\n$DIMZIN\n 70\n%i\n", dxf_header.DimZIN);
        fprintf (fp, "  9\n$DIMBLK\n  1\n%s\n", dxf_header.DimBLK);
        fprintf (fp, "  9\n$DIMASO\n 70\n%i\n", dxf_header.DimASO);
        fprintf (fp, "  9\n$DIMSHO\n 70\n%i\n", dxf_header.DimSHO);
        fprintf (fp, "  9\n$DIMPOST\n  1\n%s\n", dxf_header.DimPOST);
        fprintf (fp, "  9\n$DIMAPOST\n  1\n%s\n", dxf_header.DimAPOST);
        fprintf (fp, "  9\n$DIMALT\n 70\n%i\n", dxf_header.DimALT);
        fprintf (fp, "  9\n$DIMALTD\n 70\n%i\n", dxf_header.DimALTD);
        fprintf (fp, "  9\n$DIMALTF\n 40\n%f\n", dxf_header.DimALTF);
        fprintf (fp, "  9\n$DIMLFAC\n 40\n%f\n", dxf_header.DimLFAC);
        fprintf (fp, "  9\n$DIMTOFL\n 70\n%i\n", dxf_header.DimTOFL);
        fprintf (fp, "  9\n$DIMTVP\n 40\n%f\n", dxf_header.DimTVP);
        fprintf (fp, "  9\n$DIMTIX\n 70\n%i\n", dxf_header.DimTIX);
        fprintf (fp, "  9\n$DIMSOXD\n 70\n%i\n", dxf_header.DimSOXD);
        fprintf (fp, "  9\n$DIMSAH\n 70\n%i\n", dxf_header.DimSAH);
        fprintf (fp, "  9\n$DIMBLK1\n  1\n%s\n", dxf_header.DimBLK1);
        fprintf (fp, "  9\n$DIMBLK2\n  1\n%s\n", dxf_header.DimBLK2);
        fprintf (fp, "  9\n$DIMSTYLE\n  2\n%s\n", dxf_header.DimSTYLE);
        fprintf (fp, "  9\n$DIMCLRD\n 70\n%i\n", dxf_header.DimCLRD);
        fprintf (fp, "  9\n$DIMCLRE\n 70\n%i\n", dxf_header.DimCLRE);
        fprintf (fp, "  9\n$DIMCLRT\n 70\n%i\n", dxf_header.DimCLRT);
        fprintf (fp, "  9\n$DIMTFAC\n 40\n%f\n", dxf_header.DimTFAC);
        fprintf (fp, "  9\n$DIMGAP\n 40\n%f\n", dxf_header.DimGAP);
        if (acad_version_number >= AC1012) fprintf (fp, "  9\n$DIMJUST\n 70\n%i\n", dxf_header.DimJUST);
        if (acad_version_number >= AC1012) fprintf (fp, "  9\n$DIMSD1\n 70\n%i\n", dxf_header.DimSD1);
        if (acad_version_number >= AC1012) fprintf (fp, "  9\n$DIMSD2\n 70\n%i\n", dxf_header.DimSD2);
        if (acad_version_number >= AC1012) fprintf (fp, "  9\n$DIMTOLJ\n 70\n%i\n", dxf_header.DimTOLJ);
        if (acad_version_number >= AC1012) fprintf (fp, "  9\n$DIMTZIN\n 70\n%i\n", dxf_header.DimTZIN);
        if (acad_version_number >= AC1012) fprintf (fp, "  9\n$DIMALTZ\n 70\n%i\n", dxf_header.DimALTZ);
        if (acad_version_number >= AC1012) fprintf (fp, "  9\n$DIMALTTZ\n 70\n%i\n", dxf_header.DimALTTZ);
        if ((acad_version_number == AC1012) || (acad_version_number == AC1014)) fprintf (fp, "  9\n$DIMFIT\n 70\n%i\n", dxf_header.DimFIT);
        if (acad_version_number >= AC1012) fprintf (fp, "  9\n$DIMUPT\n 70\n%i\n", dxf_header.DimUPT);
        if ((acad_version_number == AC1012) || (acad_version_number == AC1014)) fprintf (fp, "  9\n$DIMUNIT\n 70\n%i\n", dxf_header.DimUNIT);
        if (acad_version_number >= AC1012) fprintf (fp, "  9\n$DIMDEC\n 70\n%i\n", dxf_header.DimDEC);
        if (acad_version_number >= AC1012) fprintf (fp, "  9\n$DIMTDEC\n 70\n%i\n", dxf_header.DimTDEC);
        if (acad_version_number >= AC1012) fprintf (fp, "  9\n$DIMALTU\n 70\n%i\n", dxf_header.DimALTU);
        if (acad_version_number >= AC1012) fprintf (fp, "  9\n$DIMALTTD\n 70\n%i\n", dxf_header.DimALTTD);
        if (acad_version_number >= AC1012) fprintf (fp, "  9\n$DIMTXSTY\n  7\n%s\n", dxf_header.DimTXSTY);
        if (acad_version_number >= AC1012) fprintf (fp, "  9\n$DIMAUNIT\n 70\n%i\n", dxf_header.DimAUNIT);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$DIMADEC\n 70\n%i\n", dxf_header.DimADEC);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$DIMALTRND\n 40\n%f\n", dxf_header.DimALTRND);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$DIMAZIN\n 70\n%i\n", dxf_header.DimAZIN);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$DIMDSEP\n 70\n%i\n", dxf_header.DimDSEP);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$DIMATFIT\n 70\n%i\n", dxf_header.DimATFIT);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$DIMFRAC\n 70\n%i\n", dxf_header.DimFRAC);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$DIMLDRBLK\n  1\n%s\n", dxf_header.DimLDRBLK);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$DIMLUNIT\n 70\n%i\n", dxf_header.DimLUNIT);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$DIMLWD\n 70\n%i\n", dxf_header.DimLWD);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$DIMLWE\n 70\n%i\n", dxf_header.DimLWE);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$DIMTMOVE\n 70\n%i\n", dxf_header.DimTMOVE);
        fprintf (fp, "  9\n$LUNITS\n 70\n%i\n", dxf_header.LUnits);
        fprintf (fp, "  9\n$LUPREC\n 70\n%i\n", dxf_header.LUPrec);
        fprintf (fp, "  9\n$SKETCHINC\n 40\n%f\n", dxf_header.Sketchinc);
        fprintf (fp, "  9\n$FILLETRAD\n 40\n%f\n", dxf_header.FilletRad);
        fprintf (fp, "  9\n$AUNITS\n 70\n%i\n", dxf_header.AUnits);
        fprintf (fp, "  9\n$AUPREC\n 70\n%i\n", dxf_header.AUPrec);
        fprintf (fp, "  9\n$MENU\n  1\n%s\n", dxf_header.Menu);
        fprintf (fp, "  9\n$ELEVATION\n 40\n%f\n", dxf_header.Elevation);
        fprintf (fp, "  9\n$PELEVATION\n 40\n%f\n", dxf_header.PElevation);
        fprintf (fp, "  9\n$THICKNESS\n 40\n%f\n", dxf_header.Thickness);
        fprintf (fp, "  9\n$LIMCHECK\n 70\n%i\n", dxf_header.LimCheck);
        if (acad_version_number <= AC1014) fprintf (fp, "  9\n$BLIPMODE\n 70\n%i\n", dxf_header.BlipMode);
        fprintf (fp, "  9\n$CHAMFERA\n 40\n%f\n", dxf_header.ChamferA);
        fprintf (fp, "  9\n$CHAMFERB\n 40\n%f\n", dxf_header.ChamferB);
        if (acad_version_number >= AC1012) fprintf (fp, "  9\n$CHAMFERC\n 40\n%f\n", dxf_header.ChamferC);
        if (acad_version_number >= AC1012) fprintf (fp, "  9\n$CHAMFERD\n 40\n%f\n", dxf_header.ChamferD);
        fprintf (fp, "  9\n$SKPOLY\n 70\n%i\n", dxf_header.SKPoly);
        fprintf (fp, "  9\n$TDCREATE\n 40\n%f\n", dxf_header.TDCreate);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$TDUCREATE\n 40\n%f\n", dxf_header.TDUCreate);
        fprintf (fp, "  9\n$TDUPDATE\n 40\n%f\n", dxf_header.TDUpdate);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$TDUUPDATE\n 40\n%f\n", dxf_header.TDUUpdate);
        fprintf (fp, "  9\n$TDINDWG\n 40\n%f\n", dxf_header.TDInDWG);
        fprintf (fp, "  9\n$TDUSRTIMER\n 40\n%f\n", dxf_header.TDUSRTimer);
        fprintf (fp, "  9\n$USRTIMER\n 70\n%i\n", dxf_header.USRTimer);
        fprintf (fp, "  9\n$ANGBASE\n 50\n%f\n", dxf_header.AngBase);
        fprintf (fp, "  9\n$ANGDIR\n 70\n%i\n", dxf_header.AngDir);
        fprintf (fp, "  9\n$PDMODE\n 70\n%i\n", dxf_header.PDMode);
        fprintf (fp, "  9\n$PDSIZE\n 40\n%f\n", dxf_header.PDSize);
        fprintf (fp, "  9\n$PLINEWID\n 40\n%f\n", dxf_header.PLineWid);
        if (acad_version_number <= AC1014) fprintf (fp, "  9\n$COORDS\n 70\n%i\n", dxf_header.Coords);
        fprintf (fp, "  9\n$SPLFRAME\n 70\n%i\n", dxf_header.SPLFrame);
        fprintf (fp, "  9\n$SPLINETYPE\n 70\n%i\n", dxf_header.SPLineType);
        if (acad_version_number <= AC1014) fprintf (fp, "  9\n$ATTDIA\n 70\n%i\n", dxf_header.AttDia);
        if (acad_version_number <= AC1014) fprintf (fp, "  9\n$ATTREQ\n 70\n%i\n", dxf_header.AttReq);
        if (acad_version_number <= AC1014) fprintf (fp, "  9\n$HANDLING\n 70\n%i\n", dxf_header.Handling);
        fprintf (fp, "  9\n$SPLINESEGS\n 70\n%i\n", dxf_header.SPLineSegs);
        fprintf (fp, "  9\n$HANDSEED\n  5\n%s\n", dxf_header.HandSeed);
        fprintf (fp, "  9\n$SURFTAB1\n 70\n%i\n", dxf_header.SurfTab1);
        fprintf (fp, "  9\n$SURFTAB2\n 70\n%i\n", dxf_header.SurfTab2);
        fprintf (fp, "  9\n$SURFTYPE\n 70\n%i\n", dxf_header.SurfType);
        fprintf (fp, "  9\n$SURFU\n 70\n%i\n", dxf_header.SurfU);
        fprintf (fp, "  9\n$SURFV\n 70\n%i\n", dxf_header.SurfV);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$UCSBASE\n  2\n%s\n", dxf_header.UCSBase);
        fprintf (fp, "  9\n$UCSNAME\n  2\n%s\n", dxf_header.UCSName);
        fprintf (fp, "  9\n$UCSORG\n 10\n%f\n 20\n%f\n 30\n%f\n", dxf_header.UCSOrg.x0, dxf_header.UCSOrg.y0, dxf_header.UCSOrg.z0);
        fprintf (fp, "  9\n$UCSXDIR\n 10\n%f\n 20\n%f\n 30\n%f\n", dxf_header.UCSXDir.x0, dxf_header.UCSXDir.y0, dxf_header.UCSXDir.z0);
        fprintf (fp, "  9\n$UCSYDIR\n 10\n%f\n 20\n%f\n 30\n%f\n", dxf_header.UCSYDir.x0, dxf_header.UCSYDir.y0, dxf_header.UCSYDir.z0);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$UCSORTHOREF\n  2\n%s\n", dxf_header.UCSOrthoRef);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$UCSORTHOVIEW\n 70\n%i\n", dxf_header.UCSOrthoView);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$UCSORGTOP\n 10\n%f\n 20\n%f\n 30\n%f\n", dxf_header.UCSOrgTop.x0, dxf_header.UCSOrgTop.y0, dxf_header.UCSOrgTop.z0);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$UCSORGBOTTOM\n 10\n%f\n 20\n%f\n 30\n%f\n", dxf_header.UCSOrgBottom.x0, dxf_header.UCSOrgBottom.y0, dxf_header.UCSOrgBottom.z0);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$UCSORGLEFT\n 10\n%f\n 20\n%f\n 30\n%f\n", dxf_header.UCSOrgLeft.x0, dxf_header.UCSOrgLeft.y0, dxf_header.UCSOrgLeft.z0);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$UCSORGRIGHT\n 10\n%f\n 20\n%f\n 30\n%f\n", dxf_header.UCSOrgRight.x0, dxf_header.UCSOrgRight.y0, dxf_header.UCSOrgRight.z0);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$UCSORGFRONT\n 10\n%f\n 20\n%f\n 30\n%f\n", dxf_header.UCSOrgFront.x0, dxf_header.UCSOrgFront.y0, dxf_header.UCSOrgFront.z0);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$UCSORGBACK\n 10\n%f\n 20\n%f\n 30\n%f\n", dxf_header.UCSOrgBack.x0, dxf_header.UCSOrgBack.y0, dxf_header.UCSOrgBack.z0);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$PUCSBASE\n  2\n%s\n", dxf_header.PUCSBase);
        fprintf (fp, "  9\n$PUCSNAME\n  2\n%s\n", dxf_header.PUCSName);
        fprintf (fp, "  9\n$PUCSORG\n 10\n%f\n 20\n%f\n 30\n%f\n", dxf_header.PUCSOrg.x0, dxf_header.PUCSOrg.y0, dxf_header.PUCSOrg.z0);
        fprintf (fp, "  9\n$PUCSXDIR\n 10\n%f\n 20\n%f\n 30\n%f\n", dxf_header.PUCSXDir.x0, dxf_header.PUCSXDir.y0, dxf_header.PUCSXDir.z0);
        fprintf (fp, "  9\n$PUCSYDIR\n 10\n%f\n 20\n%f\n 30\n%f\n", dxf_header.PUCSYDir.x0, dxf_header.PUCSYDir.y0, dxf_header.PUCSYDir.z0);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$PUCSORTHOREF\n  2\n%s\n", dxf_header.PUCSOrthoRef);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$PUCSORTHOVIEW\n 70\n%i\n", dxf_header.PUCSOrthoView);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$PUCSORGTOP\n 10\n%f\n 20\n%f\n 30\n%f\n", dxf_header.PUCSOrgTop.x0, dxf_header.PUCSOrgTop.y0, dxf_header.PUCSOrgTop.z0);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$PUCSORGBOTTOM\n 10\n%f\n 20\n%f\n 30\n%f\n", dxf_header.PUCSOrgBottom.x0, dxf_header.PUCSOrgBottom.y0, dxf_header.PUCSOrgBottom.z0);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$PUCSORGLEFT\n 10\n%f\n 20\n%f\n 30\n%f\n", dxf_header.PUCSOrgLeft.x0, dxf_header.PUCSOrgLeft.y0, dxf_header.PUCSOrgLeft.z0);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$PUCSORGRIGHT\n 10\n%f\n 20\n%f\n 30\n%f\n", dxf_header.PUCSOrgRight.x0, dxf_header.PUCSOrgRight.y0, dxf_header.PUCSOrgRight.z0);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$PUCSORGFRONT\n 10\n%f\n 20\n%f\n 30\n%f\n", dxf_header.PUCSOrgFront.x0, dxf_header.PUCSOrgFront.y0, dxf_header.PUCSOrgFront.z0);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$PUCSORGBACK\n 10\n%f\n 20\n%f\n 30\n%f\n", dxf_header.PUCSOrgBack.x0, dxf_header.PUCSOrgBack.y0, dxf_header.PUCSOrgBack.z0);
        fprintf (fp, "  9\n$USERI1\n 70\n%i\n", dxf_header.UserI1);
        fprintf (fp, "  9\n$USERI2\n 70\n%i\n", dxf_header.UserI2);
        fprintf (fp, "  9\n$USERI3\n 70\n%i\n", dxf_header.UserI3);
        fprintf (fp, "  9\n$USERI4\n 70\n%i\n", dxf_header.UserI4);
        fprintf (fp, "  9\n$USERI5\n 70\n%i\n", dxf_header.UserI5);
        fprintf (fp, "  9\n$USERR1\n 40\n%f\n", dxf_header.UserR1);
        fprintf (fp, "  9\n$USERR2\n 40\n%f\n", dxf_header.UserR2);
        fprintf (fp, "  9\n$USERR3\n 40\n%f\n", dxf_header.UserR3);
        fprintf (fp, "  9\n$USERR4\n 40\n%f\n", dxf_header.UserR4);
        fprintf (fp, "  9\n$USERR5\n 40\n%f\n", dxf_header.UserR5);
        fprintf (fp, "  9\n$WORLDVIEW\n 70\n%i\n", dxf_header.WorldView);
        fprintf (fp, "  9\n$SHADEDGE\n 70\n%i\n", dxf_header.ShadEdge);
        fprintf (fp, "  9\n$SHADEDIF\n 70\n%i\n", dxf_header.ShadeDif);
        fprintf (fp, "  9\n$TILEMODE\n 70\n%i\n", dxf_header.TileMode);
        fprintf (fp, "  9\n$MAXACTVP\n 70\n%i\n", dxf_header.MaxActVP);
        fprintf (fp, "  9\n$PINSBASE\n 10\n%f\n 20\n%f\n 30\n%f\n", dxf_header.PInsBase.x0, dxf_header.PInsBase.y0, dxf_header.PInsBase.z0);
        fprintf (fp, "  9\n$PLIMCHECK\n 70\n%i\n", dxf_header.PLimCheck);
        fprintf (fp, "  9\n$PEXTMIN\n 10\n%f\n 20\n%f\n 30\n%f\n", dxf_header.PExtMin.x0, dxf_header.PExtMin.y0, dxf_header.PExtMin.z0);
        fprintf (fp, "  9\n$PEXTMAX\n 10\n%f\n 20\n%f\n 30\n%f\n", dxf_header.PExtMax.x0, dxf_header.PExtMax.y0, dxf_header.PExtMax.z0);
        fprintf (fp, "  9\n$PLIMMIN\n 10\n%f\n 20\n%f\n", dxf_header.PLimMin.x0, dxf_header.PLimMin.y0);
        fprintf (fp, "  9\n$PLIMMAX\n 10\n%f\n 20\n%f\n", dxf_header.PLimMax.x0, dxf_header.PLimMax.y0);
        fprintf (fp, "  9\n$UNITMODE\n 70\n%i\n", dxf_header.UnitMode);
        fprintf (fp, "  9\n$VISRETAIN\n 70\n%i\n", dxf_header.VisRetain);
        fprintf (fp, "  9\n$PLINEGEN\n 70\n%i\n", dxf_header.PLineGen);
        fprintf (fp, "  9\n$PSLTSCALE\n 70\n%i\n", dxf_header.PSLTScale);
        if (acad_version_number >= AC1012) fprintf (fp, "  9\n$TREEDEPTH\n 70\n%i\n", dxf_header.TreeDepth);
        if ((acad_version_number == AC1012) || (acad_version_number == AC1014)) fprintf (fp, "  9\n$PICKSTYLE\n 70\n%i\n", dxf_header.PickStyle);
        if (acad_version_number >= AC1012) fprintf (fp, "  9\n$CMLSTYLE\n  2\n%s\n", dxf_header.CMLStyle);
        if (acad_version_number >= AC1012) fprintf (fp, "  9\n$CMLJUST\n 70\n%i\n", dxf_header.CMLJust);
        if (acad_version_number >= AC1012) fprintf (fp, "  9\n$CMLSCALE\n 40\n%f\n", dxf_header.CMLScale);
        if (acad_version_number >= AC1014) fprintf (fp, "  9\n$PROXYGRAPHICS\n 70\n%i\n", dxf_header.ProxyGraphics);
        if (acad_version_number >= AC1014) fprintf (fp, "  9\n$MEASUREMENT\n 70\n%i\n", dxf_header.Measurement);
        if (acad_version_number == AC1012) fprintf (fp, "  9\n$SAVEIMAGES\n 70\n%i\n", dxf_header.SaveImages);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$CELWEIGHT\n370\n%i\n", dxf_header.CELWeight);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$ENDCAPS\n280\n%i\n", dxf_header.EndCaps);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$JOINSTYLE\n280\n%i\n", dxf_header.JoinStyle);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$LWDISPLAY\n290\n%i\n", dxf_header.LWDisplay);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$INSUNITS\n 70\n%i\n", dxf_header.InsUnits);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$HYPERLINKBASE\n  1\n%s\n", dxf_header.HyperLinkBase);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$STYLESHEET\n  1\n%s\n", dxf_header.StyleSheet);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$XEDIT\n290\n%i\n", dxf_header.XEdit);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$CEPSNTYPE\n380\n%i\n", dxf_header.CEPSNType);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$PSTYLEMODE\n290\n%i\n", dxf_header.PStyleMode);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$FINGERPRINTGUID\n  2\n%s\n", dxf_header.FingerPrintGUID);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$VERSIONGUID\n  2\n%s\n", dxf_header.VersionGUID);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$EXTNAMES\n290\n%i\n", dxf_header.ExtNames);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$PSVPSCALE\n 40\n%f\n", dxf_header.PSVPScale);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$OLESTARTUP\n290\n%i\n", dxf_header.OLEStartUp);
        if (acad_version_number >= AC1018) fprintf (fp, "  9\n$SORTENTS\n280\n%i\n", dxf_header.SortEnts);
        if (acad_version_number >= AC1018) fprintf (fp, "  9\n$INDEXCTL\n280\n%i\n", dxf_header.IndexCtl);
        if (acad_version_number >= AC1018) fprintf (fp, "  9\n$HIDETEXT\n280\n%i\n", dxf_header.HideText);
        if (acad_version_number >= AC1018) fprintf (fp, "  9\n$XCLIPFRAME\n290\n%i\n", dxf_header.XClipFrame);
        if (acad_version_number >= AC1018) fprintf (fp, "  9\n$HALOGAP\n280\n%i\n", dxf_header.HaloGap);
        if (acad_version_number >= AC1018) fprintf (fp, "  9\n$OBSCOLOR\n 70\n%i\n", dxf_header.ObsColor);
        if (acad_version_number >= AC1018) fprintf (fp, "  9\n$OBSLTYPE\n280\n%i\n", dxf_header.ObsLType);
        if (acad_version_number >= AC1018) fprintf (fp, "  9\n$INTERSECTIONDISPLAY\n280\n%i\n", dxf_header.InterSectionDisplay);
        if (acad_version_number >= AC1018) fprintf (fp, "  9\n$INTERSECTIONCOLOR\n 70\n%i\n", dxf_header.InterSectionColor);
        if (acad_version_number >= AC1018) fprintf (fp, "  9\n$DIMASSOC\n280\n%i\n", dxf_header.DimASSOC);
        if (acad_version_number >= AC1018) fprintf (fp, "  9\n$PROJECTNAME\n  1\n%s\n", dxf_header.ProjectName);
        dxf_write_endsection (fp);
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_write_header2 () function.\n", __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}

static int
dxf_read_header_parse_string
(
        FILE *fp,  /*!< DXF file handler.\n */
        const char *temp_string,
        const char *header_var,
        char **value_string,
        int version_expression
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_read_header_parse_string () function.\n", __FILE__, __LINE__);
#endif
        char tstring[255];
        int n, ret = SUCCESS;
        if (strcmp (temp_string, header_var) == 0 && version_expression)
        {
                ret = FOUND;
                dxf_read_scanf (fp, "%i\n%s\n", &n, tstring);
                if (dxf_read_is_string(n))
                {
                        *value_string = strdup(tstring);
                }
                else
                        ret = FAIL;
        }
        else
                ret = SUCCESS;
                
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_read_header_parse_string () function.\n", __FILE__, __LINE__);
#endif
        return ret;
}

static int
dxf_read_header_parse_int
(
        FILE *fp,  /*!< DXF file handler.\n */
        const char *temp_string,
        const char *header_var,
        int *value,
        int version_expression
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_read_header_parse_int () function.\n", __FILE__, __LINE__);
#endif
        int f, tvar, n, ret = SUCCESS;
        /* test for header_var and version number. -3 makes it version agnostic */
        if (strcmp (temp_string, header_var) == 0  && version_expression)
        {
                f = dxf_read_scanf (fp, "%i\n%i\n", &n, &tvar);
                if (f > 0 && dxf_read_is_int(n))
                {
                        *value = tvar;
                        ret = FOUND;                                
                }
                else
                        ret = FAIL;
        }
        else
                ret = SUCCESS;

#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_read_header_parse_int () function.\n", __FILE__, __LINE__);
#endif
        return ret;
}

static int
dxf_read_header_parse_n_double
(
        FILE *fp,  /*!< DXF file handler.\n */
        const char *temp_string,
        const char *header_var,
        int version_expression,
        int quant,
        ...
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_read_header_parse_n_double () function.\n", __FILE__, __LINE__);
#endif
        int f, n, i, ret = SUCCESS;
        double *dvar;
        double tvar;
        va_list dlist;

        /* test for header_var and version number. -3 makes it version agnostic */
        if (strcmp (temp_string, header_var) == 0  && version_expression)
        {
                ret = FOUND;
                va_start (dlist, quant);
                for (i = 1; i <= quant; i++)
                {
                        dvar = va_arg(dlist, double *);
                        /* prepare the string to read all vars */
                        f = dxf_read_scanf (fp, "%d\n%'lf\n", &n, &tvar);
                        if (f > 0 && dxf_read_is_double (n))
                        {
                                *dvar = tvar;
                        }
                        else
                        {
                                ret = FALSE;
                                break;
                        }
                }
                va_end(dlist);
        }
        else
                ret = SUCCESS;

#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_read_header_parse_n_double () function.\n", __FILE__, __LINE__);
#endif
        return ret;
}

/*!
 * \brief Parses the header from a DXF file, with no particulary order.
 */
static int
dxf_read_header_parser
(
        FILE *fp,  /*!< DXF file handler.\n */
        DxfHeader dxf_header,  /*!< DXF header to be initialized.\n */
        char * temp_string,
        int acad_version_number
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering read_header_parser () function.\n", __FILE__, __LINE__);
#endif
        int ret;
        /*!
        * \todo: add some kind of control to what we have already read and check
        if we read all header data.
        */
        ret = dxf_read_header_parse_int (fp, temp_string, "$ACADMAINTVER",
                                         &dxf_header.AcadMaintVer,
                                         acad_version_number > AC1014);
        dxf_return(ret);
                
        ret = dxf_read_header_parse_string (fp, temp_string, "$DWGCODEPAGE",
                                            &dxf_header.DWGCodePage,
                                            acad_version_number >= AC1012);
        dxf_return(ret);
        
        ret = dxf_read_header_parse_n_double (fp, temp_string, "$INSBASE",
                                              TRUE,
                                              3,
                                              &dxf_header.InsBase.x0,
                                              &dxf_header.InsBase.y0,
                                              &dxf_header.InsBase.z0);
        dxf_return(ret);

        ret = dxf_read_header_parse_n_double (fp, temp_string, "$EXTMIN",
                                              TRUE,
                                              3,
                                              &dxf_header.ExtMin.x0,
                                              &dxf_header.ExtMin.y0,
                                              &dxf_header.ExtMin.z0);
        dxf_return(ret);

        ret = dxf_read_header_parse_n_double (fp, temp_string, "$EXTMAX",
                                              TRUE,
                                              3,
                                              &dxf_header.ExtMax.x0,
                                              &dxf_header.ExtMax.y0,
                                              &dxf_header.ExtMax.z0);
        dxf_return(ret);

        ret = dxf_read_header_parse_n_double (fp, temp_string, "$LIMMIN",
                                              TRUE,
                                              2,
                                              &dxf_header.LimMin.x0,
                                              &dxf_header.LimMin.y0);
        dxf_return(ret);

        ret = dxf_read_header_parse_n_double (fp, temp_string, "$LIMMAX",
                                              TRUE,
                                              2,
                                              &dxf_header.LimMax.x0,
                                              &dxf_header.LimMax.y0);
        dxf_return(ret);

        ret = dxf_read_header_parse_int (fp, temp_string, "$ORTHOMODE",
                                         &dxf_header.OrthoMode,
                                         TRUE);
        dxf_return(ret);

        ret = dxf_read_header_parse_int (fp, temp_string, "$REGENMODE",
                                         &dxf_header.RegenMode,
                                         TRUE);
        dxf_return(ret);

        ret = dxf_read_header_parse_int (fp, temp_string, "$FILLMODE",
                                         &dxf_header.FillMode,
                                         TRUE);
        dxf_return(ret);

        ret = dxf_read_header_parse_int (fp, temp_string, "$QTEXTMODE",
                                         &dxf_header.QTextMode,
                                         TRUE);
        dxf_return(ret);

        ret = dxf_read_header_parse_int (fp, temp_string, "$MIRRTEXT",
                                         &dxf_header.MirrText,
                                         TRUE);
        dxf_return(ret);

        ret = dxf_read_header_parse_int (fp, temp_string, "$DRAGMODE",
                                         &dxf_header.MirrText,
                                         acad_version_number < AC1015);
        dxf_return(ret);

        ret = dxf_read_header_parse_n_double (fp, temp_string, "$LTSCALE",
                                              TRUE,
                                              1,
                                              &dxf_header.LTScale);
        dxf_return(ret);

        ret = dxf_read_header_parse_int (fp, temp_string, "$OSMODE",
                                         &dxf_header.OSMode,
                                         acad_version_number <= AC1014);
        dxf_return(ret);

        ret = dxf_read_header_parse_int (fp, temp_string, "$ATTMODE",
                                         &dxf_header.AttMode,
                                         TRUE);
        dxf_return(ret);
    
        ret = dxf_read_header_parse_n_double (fp, temp_string, "$TEXTSIZE",
                                              TRUE,
                                              1,
                                              &dxf_header.TextSize);
        dxf_return(ret);

        ret = dxf_read_header_parse_n_double (fp, temp_string, "$TRACEWID",
                                              TRUE,
                                              1,
                                              &dxf_header.TraceWid);
        dxf_return(ret);

        ret = dxf_read_header_parse_string (fp, temp_string, "$TEXTSTYLE",
                                            &dxf_header.TextStyle,
                                            TRUE);
        dxf_return(ret);

        ret = dxf_read_header_parse_string (fp, temp_string, "$CLAYER",
                                            &dxf_header.CLayer,
                                            TRUE);
        dxf_return(ret);

        ret = dxf_read_header_parse_string (fp, temp_string, "$CELTYPE",
                                            &dxf_header.CELType,
                                            TRUE);
        dxf_return(ret);

        ret = dxf_read_header_parse_int (fp, temp_string, "$CECOLOR",
                                         &dxf_header.CEColor,
                                         TRUE);
        dxf_return(ret);

        ret = dxf_read_header_parse_n_double (fp, temp_string, "$CELTSCALE",
                                              acad_version_number >= AC1012,
                                              1,
                                              &dxf_header.CELTScale);
        dxf_return(ret);

        ret = dxf_read_header_parse_int (fp, temp_string, "$DELOBJ",
                                         &dxf_header.DelObj,
                                         (acad_version_number == AC1012)
                                         || (acad_version_number == AC1014));
        dxf_return(ret);

        /* FIXME: changed from AC1012 to AC1015 */
        ret = dxf_read_header_parse_int (fp, temp_string, "$DISPSILH",
                                         &dxf_header.DispSilH,
                                         acad_version_number <= AC1015);
        dxf_return(ret);

        ret = dxf_read_header_parse_n_double (fp, temp_string, "$DIMSCALE",
                                              TRUE,
                                              1,
                                              &dxf_header.DimSCALE);
        dxf_return(ret);

        ret = dxf_read_header_parse_n_double (fp, temp_string, "$DIMASZ",
                                              TRUE,
                                              1,
                                              &dxf_header.DimASZ);
        dxf_return(ret);

        ret = dxf_read_header_parse_n_double (fp, temp_string, "$DIMEXO",
                                              TRUE,
                                              1,
                                              &dxf_header.DimEXO);
        dxf_return(ret);

        /*
        fprintf (fp, "  9\n$DIMDLI\n 40\n%f\n", dxf_header.DimDLI);
        fprintf (fp, "  9\n$DIMRND\n 40\n%f\n", dxf_header.DimRND);
        fprintf (fp, "  9\n$DIMDLE\n 40\n%f\n", dxf_header.DimDLE);
        */
        ret = dxf_read_header_parse_n_double (fp, temp_string, "$DIMEXE",
                                              TRUE,
                                              1,
                                              &dxf_header.DimEXE);
        dxf_return(ret);
        /*
        fprintf (fp, "  9\n$DIMTP\n 40\n%f\n", dxf_header.DimTP);
        fprintf (fp, "  9\n$DIMTM\n 40\n%f\n", dxf_header.DimTM);
        */
        ret = dxf_read_header_parse_n_double (fp, temp_string, "$DIMTXT",
                                              TRUE,
                                              1,
                                              &dxf_header.DimTXT);
        dxf_return(ret);
        /*
        fprintf (fp, "  9\n$DIMCEN\n 40\n%f\n", dxf_header.DimCEN);
        fprintf (fp, "  9\n$DIMTSZ\n 40\n%f\n", dxf_header.DimTSZ);
        fprintf (fp, "  9\n$DIMTOL\n 70\n%i\n", dxf_header.DimTOL);
        fprintf (fp, "  9\n$DIMLIM\n 70\n%i\n", dxf_header.DimLIM);
        fprintf (fp, "  9\n$DIMTIH\n 70\n%i\n", dxf_header.DimTIH);
        fprintf (fp, "  9\n$DIMTOH\n 70\n%i\n", dxf_header.DimTOH);
        fprintf (fp, "  9\n$DIMSE1\n 70\n%i\n", dxf_header.DimSE1);
        fprintf (fp, "  9\n$DIMSE2\n 70\n%i\n", dxf_header.DimSE2);
        fprintf (fp, "  9\n$DIMTAD\n 70\n%i\n", dxf_header.DimTAD);
        fprintf (fp, "  9\n$DIMZIN\n 70\n%i\n", dxf_header.DimZIN);
        fprintf (fp, "  9\n$DIMBLK\n  1\n%s\n", dxf_header.DimBLK);
        fprintf (fp, "  9\n$DIMASO\n 70\n%i\n", dxf_header.DimASO);
        fprintf (fp, "  9\n$DIMSHO\n 70\n%i\n", dxf_header.DimSHO);
        fprintf (fp, "  9\n$DIMPOST\n  1\n%s\n", dxf_header.DimPOST);
        fprintf (fp, "  9\n$DIMAPOST\n  1\n%s\n", dxf_header.DimAPOST);
        fprintf (fp, "  9\n$DIMALT\n 70\n%i\n", dxf_header.DimALT);
        fprintf (fp, "  9\n$DIMALTD\n 70\n%i\n", dxf_header.DimALTD);
        fprintf (fp, "  9\n$DIMALTF\n 40\n%f\n", dxf_header.DimALTF);
        fprintf (fp, "  9\n$DIMLFAC\n 40\n%f\n", dxf_header.DimLFAC);
        fprintf (fp, "  9\n$DIMTOFL\n 70\n%i\n", dxf_header.DimTOFL);
        fprintf (fp, "  9\n$DIMTVP\n 40\n%f\n", dxf_header.DimTVP);
        fprintf (fp, "  9\n$DIMTIX\n 70\n%i\n", dxf_header.DimTIX);
        fprintf (fp, "  9\n$DIMSOXD\n 70\n%i\n", dxf_header.DimSOXD);
        fprintf (fp, "  9\n$DIMSAH\n 70\n%i\n", dxf_header.DimSAH);
        fprintf (fp, "  9\n$DIMBLK1\n  1\n%s\n", dxf_header.DimBLK1);
        fprintf (fp, "  9\n$DIMBLK2\n  1\n%s\n", dxf_header.DimBLK2);
        */
        ret = dxf_read_header_parse_string (fp, temp_string, "$DIMSTYLE",
                                            &dxf_header.DimSTYLE,
                                            TRUE);
        dxf_return(ret);
        /*
        fprintf (fp, "  9\n$DIMCLRD\n 70\n%i\n", dxf_header.DimCLRD);
        fprintf (fp, "  9\n$DIMCLRE\n 70\n%i\n", dxf_header.DimCLRE);
        fprintf (fp, "  9\n$DIMCLRT\n 70\n%i\n", dxf_header.DimCLRT);
        fprintf (fp, "  9\n$DIMTFAC\n 40\n%f\n", dxf_header.DimTFAC);
        */
        ret = dxf_read_header_parse_n_double (fp, temp_string, "$DIMGAP",
                                              TRUE,
                                              1,
                                              &dxf_header.DimGAP);
        dxf_return(ret);
        /*
        if (acad_version_number >= AC1012) fprintf (fp, "  9\n$DIMJUST\n 70\n%i\n", dxf_header.DimJUST);
        if (acad_version_number >= AC1012) fprintf (fp, "  9\n$DIMSD1\n 70\n%i\n", dxf_header.DimSD1);
        if (acad_version_number >= AC1012) fprintf (fp, "  9\n$DIMSD2\n 70\n%i\n", dxf_header.DimSD2);
        if (acad_version_number >= AC1012) fprintf (fp, "  9\n$DIMTOLJ\n 70\n%i\n", dxf_header.DimTOLJ);
        if (acad_version_number >= AC1012) fprintf (fp, "  9\n$DIMTZIN\n 70\n%i\n", dxf_header.DimTZIN);
        if (acad_version_number >= AC1012) fprintf (fp, "  9\n$DIMALTZ\n 70\n%i\n", dxf_header.DimALTZ);
        if (acad_version_number >= AC1012) fprintf (fp, "  9\n$DIMALTTZ\n 70\n%i\n", dxf_header.DimALTTZ);
        if ((acad_version_number == AC1012) || (acad_version_number == AC1014)) fprintf (fp, "  9\n$DIMFIT\n 70\n%i\n", dxf_header.DimFIT);
        if (acad_version_number >= AC1012) fprintf (fp, "  9\n$DIMUPT\n 70\n%i\n", dxf_header.DimUPT);
        if ((acad_version_number == AC1012) || (acad_version_number == AC1014)) fprintf (fp, "  9\n$DIMUNIT\n 70\n%i\n", dxf_header.DimUNIT);
        if (acad_version_number >= AC1012) fprintf (fp, "  9\n$DIMDEC\n 70\n%i\n", dxf_header.DimDEC);
        if (acad_version_number >= AC1012) fprintf (fp, "  9\n$DIMTDEC\n 70\n%i\n", dxf_header.DimTDEC);
        if (acad_version_number >= AC1012) fprintf (fp, "  9\n$DIMALTU\n 70\n%i\n", dxf_header.DimALTU);
        if (acad_version_number >= AC1012) fprintf (fp, "  9\n$DIMALTTD\n 70\n%i\n", dxf_header.DimALTTD);
        if (acad_version_number >= AC1012) fprintf (fp, "  9\n$DIMTXSTY\n  7\n%s\n", dxf_header.DimTXSTY);
        */
        ret = dxf_read_header_parse_int (fp, temp_string, "$DIMAUNIT",
                                         &dxf_header.DimAUNIT,
                                         acad_version_number >= AC1012);
        dxf_return(ret);
    
        ret = dxf_read_header_parse_int (fp, temp_string, "$DIMADEC",
                                         &dxf_header.DimADEC,
                                         acad_version_number >= AC1015);
        dxf_return(ret);
        /*
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$DIMALTRND\n 40\n%f\n", dxf_header.DimALTRND);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$DIMAZIN\n 70\n%i\n", dxf_header.DimAZIN);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$DIMDSEP\n 70\n%i\n", dxf_header.DimDSEP);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$DIMATFIT\n 70\n%i\n", dxf_header.DimATFIT);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$DIMFRAC\n 70\n%i\n", dxf_header.DimFRAC);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$DIMLDRBLK\n  1\n%s\n", dxf_header.DimLDRBLK);
        */
        ret = dxf_read_header_parse_int (fp, temp_string, "$DIMLUNIT",
                                         &dxf_header.DimLUNIT,
                                         acad_version_number >= AC1015);
        dxf_return(ret);
        /*
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$DIMLWD\n 70\n%i\n", dxf_header.DimLWD);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$DIMLWE\n 70\n%i\n", dxf_header.DimLWE);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$DIMTMOVE\n 70\n%i\n", dxf_header.DimTMOVE);
        */
        ret = dxf_read_header_parse_int (fp, temp_string, "$LUNITS",
                                         &dxf_header.LUnits,
                                         TRUE);
        dxf_return(ret);
        
        ret = dxf_read_header_parse_int (fp, temp_string, "$LUPREC",
                                         &dxf_header.LUPrec,
                                         TRUE);
        dxf_return(ret);
        /*
        fprintf (fp, "  9\n$SKETCHINC\n 40\n%f\n", dxf_header.Sketchinc);
        fprintf (fp, "  9\n$FILLETRAD\n 40\n%f\n", dxf_header.FilletRad);
        */
        ret = dxf_read_header_parse_int (fp, temp_string, "$AUNITS",
                                         &dxf_header.AUnits,
                                         TRUE);
        dxf_return(ret);
    
        ret = dxf_read_header_parse_int (fp, temp_string, "$AUPREC",
                                         &dxf_header.AUPrec,
                                         TRUE);
        dxf_return(ret);
        /*
        fprintf (fp, "  9\n$MENU\n  1\n%s\n", dxf_header.Menu);
        fprintf (fp, "  9\n$ELEVATION\n 40\n%f\n", dxf_header.Elevation);
        fprintf (fp, "  9\n$PELEVATION\n 40\n%f\n", dxf_header.PElevation);
        fprintf (fp, "  9\n$THICKNESS\n 40\n%f\n", dxf_header.Thickness);
        fprintf (fp, "  9\n$LIMCHECK\n 70\n%i\n", dxf_header.LimCheck);
        if (acad_version_number <= AC1014) fprintf (fp, "  9\n$BLIPMODE\n 70\n%i\n", dxf_header.BlipMode);
        fprintf (fp, "  9\n$CHAMFERA\n 40\n%f\n", dxf_header.ChamferA);
        fprintf (fp, "  9\n$CHAMFERB\n 40\n%f\n", dxf_header.ChamferB);
        if (acad_version_number >= AC1012) fprintf (fp, "  9\n$CHAMFERC\n 40\n%f\n", dxf_header.ChamferC);
        if (acad_version_number >= AC1012) fprintf (fp, "  9\n$CHAMFERD\n 40\n%f\n", dxf_header.ChamferD);
        fprintf (fp, "  9\n$SKPOLY\n 70\n%i\n", dxf_header.SKPoly);
        fprintf (fp, "  9\n$TDCREATE\n 40\n%f\n", dxf_header.TDCreate);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$TDUCREATE\n 40\n%f\n", dxf_header.TDUCreate);
        fprintf (fp, "  9\n$TDUPDATE\n 40\n%f\n", dxf_header.TDUpdate);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$TDUUPDATE\n 40\n%f\n", dxf_header.TDUUpdate);
        fprintf (fp, "  9\n$TDINDWG\n 40\n%f\n", dxf_header.TDInDWG);
        fprintf (fp, "  9\n$TDUSRTIMER\n 40\n%f\n", dxf_header.TDUSRTimer);
        fprintf (fp, "  9\n$USRTIMER\n 70\n%i\n", dxf_header.USRTimer);
        fprintf (fp, "  9\n$ANGBASE\n 50\n%f\n", dxf_header.AngBase);
        fprintf (fp, "  9\n$ANGDIR\n 70\n%i\n", dxf_header.AngDir);
        fprintf (fp, "  9\n$PDMODE\n 70\n%i\n", dxf_header.PDMode);
        fprintf (fp, "  9\n$PDSIZE\n 40\n%f\n", dxf_header.PDSize);
        fprintf (fp, "  9\n$PLINEWID\n 40\n%f\n", dxf_header.PLineWid);
        if (acad_version_number <= AC1014) fprintf (fp, "  9\n$COORDS\n 70\n%i\n", dxf_header.Coords);
        fprintf (fp, "  9\n$SPLFRAME\n 70\n%i\n", dxf_header.SPLFrame);
        fprintf (fp, "  9\n$SPLINETYPE\n 70\n%i\n", dxf_header.SPLineType);
        if (acad_version_number <= AC1014) fprintf (fp, "  9\n$ATTDIA\n 70\n%i\n", dxf_header.AttDia);
        if (acad_version_number <= AC1014) fprintf (fp, "  9\n$ATTREQ\n 70\n%i\n", dxf_header.AttReq);
        if (acad_version_number <= AC1014) fprintf (fp, "  9\n$HANDLING\n 70\n%i\n", dxf_header.Handling);
        */
        ret = dxf_read_header_parse_int (fp, temp_string, "$SPLINESEGS",
                                         &dxf_header.SPLineSegs,
                                         TRUE);
        dxf_return(ret);
        
        ret = dxf_read_header_parse_string (fp, temp_string, "$HANDSEED",
                                            &dxf_header.HandSeed,
                                            TRUE);
        dxf_return(ret);
    /*
        fprintf (fp, "  9\n$SURFTAB1\n 70\n%i\n", dxf_header.SurfTab1);
        fprintf (fp, "  9\n$SURFTAB2\n 70\n%i\n", dxf_header.SurfTab2);
        fprintf (fp, "  9\n$SURFTYPE\n 70\n%i\n", dxf_header.SurfType);
        fprintf (fp, "  9\n$SURFU\n 70\n%i\n", dxf_header.SurfU);
        fprintf (fp, "  9\n$SURFV\n 70\n%i\n", dxf_header.SurfV);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$UCSBASE\n  2\n%s\n", dxf_header.UCSBase);
        fprintf (fp, "  9\n$UCSNAME\n  2\n%s\n", dxf_header.UCSName);
        fprintf (fp, "  9\n$UCSORG\n 10\n%f\n 20\n%f\n 30\n%f\n", dxf_header.UCSOrg.x0, dxf_header.UCSOrg.y0, dxf_header.UCSOrg.z0);
        fprintf (fp, "  9\n$UCSXDIR\n 10\n%f\n 20\n%f\n 30\n%f\n", dxf_header.UCSXDir.x0, dxf_header.UCSXDir.y0, dxf_header.UCSXDir.z0);
        fprintf (fp, "  9\n$UCSYDIR\n 10\n%f\n 20\n%f\n 30\n%f\n", dxf_header.UCSYDir.x0, dxf_header.UCSYDir.y0, dxf_header.UCSYDir.z0);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$UCSORTHOREF\n  2\n%s\n", dxf_header.UCSOrthoRef);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$UCSORTHOVIEW\n 70\n%i\n", dxf_header.UCSOrthoView);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$UCSORGTOP\n 10\n%f\n 20\n%f\n 30\n%f\n", dxf_header.UCSOrgTop.x0, dxf_header.UCSOrgTop.y0, dxf_header.UCSOrgTop.z0);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$UCSORGBOTTOM\n 10\n%f\n 20\n%f\n 30\n%f\n", dxf_header.UCSOrgBottom.x0, dxf_header.UCSOrgBottom.y0, dxf_header.UCSOrgBottom.z0);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$UCSORGLEFT\n 10\n%f\n 20\n%f\n 30\n%f\n", dxf_header.UCSOrgLeft.x0, dxf_header.UCSOrgLeft.y0, dxf_header.UCSOrgLeft.z0);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$UCSORGRIGHT\n 10\n%f\n 20\n%f\n 30\n%f\n", dxf_header.UCSOrgRight.x0, dxf_header.UCSOrgRight.y0, dxf_header.UCSOrgRight.z0);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$UCSORGFRONT\n 10\n%f\n 20\n%f\n 30\n%f\n", dxf_header.UCSOrgFront.x0, dxf_header.UCSOrgFront.y0, dxf_header.UCSOrgFront.z0);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$UCSORGBACK\n 10\n%f\n 20\n%f\n 30\n%f\n", dxf_header.UCSOrgBack.x0, dxf_header.UCSOrgBack.y0, dxf_header.UCSOrgBack.z0);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$PUCSBASE\n  2\n%s\n", dxf_header.PUCSBase);
        fprintf (fp, "  9\n$PUCSNAME\n  2\n%s\n", dxf_header.PUCSName);
        fprintf (fp, "  9\n$PUCSORG\n 10\n%f\n 20\n%f\n 30\n%f\n", dxf_header.PUCSOrg.x0, dxf_header.PUCSOrg.y0, dxf_header.PUCSOrg.z0);
        fprintf (fp, "  9\n$PUCSXDIR\n 10\n%f\n 20\n%f\n 30\n%f\n", dxf_header.PUCSXDir.x0, dxf_header.PUCSXDir.y0, dxf_header.PUCSXDir.z0);
        fprintf (fp, "  9\n$PUCSYDIR\n 10\n%f\n 20\n%f\n 30\n%f\n", dxf_header.PUCSYDir.x0, dxf_header.PUCSYDir.y0, dxf_header.PUCSYDir.z0);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$PUCSORTHOREF\n  2\n%s\n", dxf_header.PUCSOrthoRef);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$PUCSORTHOVIEW\n 70\n%i\n", dxf_header.PUCSOrthoView);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$PUCSORGTOP\n 10\n%f\n 20\n%f\n 30\n%f\n", dxf_header.PUCSOrgTop.x0, dxf_header.PUCSOrgTop.y0, dxf_header.PUCSOrgTop.z0);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$PUCSORGBOTTOM\n 10\n%f\n 20\n%f\n 30\n%f\n", dxf_header.PUCSOrgBottom.x0, dxf_header.PUCSOrgBottom.y0, dxf_header.PUCSOrgBottom.z0);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$PUCSORGLEFT\n 10\n%f\n 20\n%f\n 30\n%f\n", dxf_header.PUCSOrgLeft.x0, dxf_header.PUCSOrgLeft.y0, dxf_header.PUCSOrgLeft.z0);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$PUCSORGRIGHT\n 10\n%f\n 20\n%f\n 30\n%f\n", dxf_header.PUCSOrgRight.x0, dxf_header.PUCSOrgRight.y0, dxf_header.PUCSOrgRight.z0);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$PUCSORGFRONT\n 10\n%f\n 20\n%f\n 30\n%f\n", dxf_header.PUCSOrgFront.x0, dxf_header.PUCSOrgFront.y0, dxf_header.PUCSOrgFront.z0);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$PUCSORGBACK\n 10\n%f\n 20\n%f\n 30\n%f\n", dxf_header.PUCSOrgBack.x0, dxf_header.PUCSOrgBack.y0, dxf_header.PUCSOrgBack.z0);
        fprintf (fp, "  9\n$USERI1\n 70\n%i\n", dxf_header.UserI1);
        fprintf (fp, "  9\n$USERI2\n 70\n%i\n", dxf_header.UserI2);
        fprintf (fp, "  9\n$USERI3\n 70\n%i\n", dxf_header.UserI3);
        fprintf (fp, "  9\n$USERI4\n 70\n%i\n", dxf_header.UserI4);
        fprintf (fp, "  9\n$USERI5\n 70\n%i\n", dxf_header.UserI5);
        fprintf (fp, "  9\n$USERR1\n 40\n%f\n", dxf_header.UserR1);
        fprintf (fp, "  9\n$USERR2\n 40\n%f\n", dxf_header.UserR2);
        fprintf (fp, "  9\n$USERR3\n 40\n%f\n", dxf_header.UserR3);
        fprintf (fp, "  9\n$USERR4\n 40\n%f\n", dxf_header.UserR4);
        fprintf (fp, "  9\n$USERR5\n 40\n%f\n", dxf_header.UserR5);
        fprintf (fp, "  9\n$WORLDVIEW\n 70\n%i\n", dxf_header.WorldView);
        fprintf (fp, "  9\n$SHADEDGE\n 70\n%i\n", dxf_header.ShadEdge);
        fprintf (fp, "  9\n$SHADEDIF\n 70\n%i\n", dxf_header.ShadeDif);
        fprintf (fp, "  9\n$TILEMODE\n 70\n%i\n", dxf_header.TileMode);
        fprintf (fp, "  9\n$MAXACTVP\n 70\n%i\n", dxf_header.MaxActVP);
        fprintf (fp, "  9\n$PINSBASE\n 10\n%f\n 20\n%f\n 30\n%f\n", dxf_header.PInsBase.x0, dxf_header.PInsBase.y0, dxf_header.PInsBase.z0);
        fprintf (fp, "  9\n$PLIMCHECK\n 70\n%i\n", dxf_header.PLimCheck);
        fprintf (fp, "  9\n$PEXTMIN\n 10\n%f\n 20\n%f\n 30\n%f\n", dxf_header.PExtMin.x0, dxf_header.PExtMin.y0, dxf_header.PExtMin.z0);
        fprintf (fp, "  9\n$PEXTMAX\n 10\n%f\n 20\n%f\n 30\n%f\n", dxf_header.PExtMax.x0, dxf_header.PExtMax.y0, dxf_header.PExtMax.z0);
        */
        ret = dxf_read_header_parse_n_double (fp, temp_string, "$PLIMMIN",
                                              TRUE,
                                              2,
                                              &dxf_header.PLimMin.x0,
                                              dxf_header.PLimMin.y0);
        dxf_return(ret);
    
        ret = dxf_read_header_parse_n_double (fp, temp_string, "$PLIMMAX",
                                              TRUE,
                                              2,
                                              &dxf_header.PLimMax.x0,
                                              dxf_header.PLimMax.y0);
        dxf_return(ret);
        /*
        fprintf (fp, "  9\n$UNITMODE\n 70\n%i\n", dxf_header.UnitMode);
        fprintf (fp, "  9\n$VISRETAIN\n 70\n%i\n", dxf_header.VisRetain);
        fprintf (fp, "  9\n$PLINEGEN\n 70\n%i\n", dxf_header.PLineGen);
        fprintf (fp, "  9\n$PSLTSCALE\n 70\n%i\n", dxf_header.PSLTScale);
        if (acad_version_number >= AC1012) fprintf (fp, "  9\n$TREEDEPTH\n 70\n%i\n", dxf_header.TreeDepth);
        if ((acad_version_number == AC1012) || (acad_version_number == AC1014)) fprintf (fp, "  9\n$PICKSTYLE\n 70\n%i\n", dxf_header.PickStyle);
        if (acad_version_number >= AC1012) fprintf (fp, "  9\n$CMLSTYLE\n  2\n%s\n", dxf_header.CMLStyle);
        if (acad_version_number >= AC1012) fprintf (fp, "  9\n$CMLJUST\n 70\n%i\n", dxf_header.CMLJust);
        if (acad_version_number >= AC1012) fprintf (fp, "  9\n$CMLSCALE\n 40\n%f\n", dxf_header.CMLScale);
        if (acad_version_number >= AC1014) fprintf (fp, "  9\n$PROXYGRAPHICS\n 70\n%i\n", dxf_header.ProxyGraphics);
        if (acad_version_number >= AC1014) fprintf (fp, "  9\n$MEASUREMENT\n 70\n%i\n", dxf_header.Measurement);
        if (acad_version_number == AC1012) fprintf (fp, "  9\n$SAVEIMAGES\n 70\n%i\n", dxf_header.SaveImages);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$CELWEIGHT\n370\n%i\n", dxf_header.CELWeight);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$ENDCAPS\n280\n%i\n", dxf_header.EndCaps);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$JOINSTYLE\n280\n%i\n", dxf_header.JoinStyle);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$LWDISPLAY\n290\n%i\n", dxf_header.LWDisplay);
        */
        ret = dxf_read_header_parse_int (fp, temp_string, "$INSUNITS",
                                         &dxf_header.InsUnits,
                                         acad_version_number >= AC1015);
        dxf_return(ret);
        /*
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$HYPERLINKBASE\n  1\n%s\n", dxf_header.HyperLinkBase);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$STYLESHEET\n  1\n%s\n", dxf_header.StyleSheet);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$XEDIT\n290\n%i\n", dxf_header.XEdit);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$CEPSNTYPE\n380\n%i\n", dxf_header.CEPSNType);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$PSTYLEMODE\n290\n%i\n", dxf_header.PStyleMode);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$FINGERPRINTGUID\n  2\n%s\n", dxf_header.FingerPrintGUID);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$VERSIONGUID\n  2\n%s\n", dxf_header.VersionGUID);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$EXTNAMES\n290\n%i\n", dxf_header.ExtNames);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$PSVPSCALE\n 40\n%f\n", dxf_header.PSVPScale);
        if (acad_version_number >= AC1015) fprintf (fp, "  9\n$OLESTARTUP\n290\n%i\n", dxf_header.OLEStartUp);
        if (acad_version_number >= AC1018) fprintf (fp, "  9\n$SORTENTS\n280\n%i\n", dxf_header.SortEnts);
        if (acad_version_number >= AC1018) fprintf (fp, "  9\n$INDEXCTL\n280\n%i\n", dxf_header.IndexCtl);
        if (acad_version_number >= AC1018) fprintf (fp, "  9\n$HIDETEXT\n280\n%i\n", dxf_header.HideText);
        if (acad_version_number >= AC1018) fprintf (fp, "  9\n$XCLIPFRAME\n290\n%i\n", dxf_header.XClipFrame);
        if (acad_version_number >= AC1018) fprintf (fp, "  9\n$HALOGAP\n280\n%i\n", dxf_header.HaloGap);
        if (acad_version_number >= AC1018) fprintf (fp, "  9\n$OBSCOLOR\n 70\n%i\n", dxf_header.ObsColor);
        if (acad_version_number >= AC1018) fprintf (fp, "  9\n$OBSLTYPE\n280\n%i\n", dxf_header.ObsLType);
        if (acad_version_number >= AC1018) fprintf (fp, "  9\n$INTERSECTIONDISPLAY\n280\n%i\n", dxf_header.InterSectionDisplay);
        if (acad_version_number >= AC1018) fprintf (fp, "  9\n$INTERSECTIONCOLOR\n 70\n%i\n", dxf_header.InterSectionColor);
        if (acad_version_number >= AC1018) fprintf (fp, "  9\n$DIMASSOC\n280\n%i\n", dxf_header.DimASSOC);
        if (acad_version_number >= AC1018) fprintf (fp, "  9\n$PROJECTNAME\n  1\n%s\n", dxf_header.ProjectName);        
*/
        ret = dxf_read_header_parse_n_double (fp, temp_string, "$GRIDUNIT",
                                              acad_version_number >= AC1009,
                                              2,
                                              &dxf_header.GridUnit.x0,
                                              &dxf_header.GridUnit.y0);
        dxf_return(ret);

        ret = dxf_read_header_parse_int (fp, temp_string, "$GRIDMODE",
                                         &dxf_header.GridMode,
                                         acad_version_number >= AC1009);
        dxf_return(ret);
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving read_header_parser () function.\n", __FILE__, __LINE__);
#endif
       return FALSE;
}

/*!
 * \brief Reads the header from a DXF file.
 */
int
dxf_read_header
(
        FILE *fp,  /*!< DXF file handler.\n */
        DxfHeader dxf_header  /*!< DXF header to be initialized.\n */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_read_header_struct () function.\n", __FILE__, __LINE__);
#endif
        char temp_string[255];
        int n, acad_version_number, ret;

        /* first of all we MUST read the version number */
        dxf_read_scanf (fp, "%i\n%s\n", &n, temp_string);
        ret = dxf_read_header_parse_string (fp, temp_string,
                                            "$ACADVER", &dxf_header.AcadVer,
                                            TRUE);
        dxf_return_val_if_fail (ret, FALSE);
        /* turn the acad_version into an integer */
        acad_version_number= acad_version_from_string (dxf_header.AcadVer);
    
        /* \FIXME: stores the autocad version as int */
        dxf_header._AcadVer = acad_version_number;
    
        /* a loop to read all the header with no particulary order */
        while (!feof(fp))
        {
                /* reads the next header content */
                dxf_read_scanf (fp, "%i\n%s\n", &n, temp_string);
                /* if it is a valid line */
                if (n == 9)
                {
                        /* parses the header content and extract info to the header struct */
                        ret = dxf_read_header_parser(fp, dxf_header,
                                                     temp_string,
                                                     acad_version_number);
                        dxf_return_val_if_fail(ret, FALSE);
                        if (ret != FOUND)
                                return FALSE;
                }
                /* or it can be the end of the section */
                else if (n == 0 && strcmp(temp_string, "ENDSEC") == 0)
                {
#if DEBUG
                        fprintf (stderr,
                                 "[File: %s: line: %d] read_header :: Section Ended.\n",
                                 __FILE__, __LINE__);
#endif
                        return TRUE;
                }        
                else
                {
                        return FALSE;
                }
        }

#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_read_header_struct () function.\n", __FILE__, __LINE__);
#endif
        return FALSE;
}

/* EOF */
