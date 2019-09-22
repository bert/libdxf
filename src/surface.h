/*!
 * \file surface.h
 *
 * \author Copyright (C) 2019 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF surface entity (\c SURFACE).
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 *
 * \since The \c SURFACE entity was introduced in DXF R2007.
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
 * For more details see http://www.autodesk.com .
 * <hr>
 */


#ifndef LIBDXF_SRC_SURFACE_H
#define LIBDXF_SRC_SURFACE_H


#include "global.h"
#include "util.h"
#include "point.h"
#include "binary_data.h"
#include "proprietary_data.h"


#ifdef __cplusplus
extern "C" {
#endif


typedef enum
{
        NO_TYPE,
        EXTRUDED,
        LOFTED,
        REVOLVED,
        SWEPT
} DXF_SURFACE_TYPE;


/*!
 * \brief DXF definition of an AutoCAD surface entity.
 */
typedef struct
dxf_surface_struct
{
        /* Members common for all DXF drawable entities. */
        int id_code;
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file.\n
                 * Group code = 5. */
        char *linetype;
                /*!< The linetype of the entity.\n
                 * Defaults to \c BYLAYER if ommitted in the DXF file.\n
                 * Group code = 6. */
        char *layer;
                /*!< Layer on which the entity is drawn.\n
                 * Defaults to layer "0" if no valid layername is given.\n
                 * Group code = 8. */
        double elevation;
                /*!< Elevation of the entity in the local Z-direction.\n
                 * Defaults to 0.0 if omitted in the DXF file, or prior
                 * to DXF version R12, or DXF_FLATLAND equals 0 (default).\n
                 * Group code = 38.\n
                 * \deprecated As of version R11. */
        double thickness;
                /*!< Thickness of the entity in the local Z-direction.\n
                 * Defaults to 0.0 if ommitted in the DXF file.\n
                 * Group code = 39. */
        double linetype_scale;
                /*!< Linetype scale (optional).\n
                 * Group code = 48.\n
                 * \since Introduced in version R13. */
        int16_t visibility;
                /*!< Object visibility (optional):\n
                 * <ol>
                 * <li value = "0"> Visible</li>
                 * <li value = "1"> Invisible</li>
                 * </ol>
                 * Group code = 60.\n
                 * \since Introduced in version R13. */
        int16_t color;
                /*!< Color of the entity.\n
                 * Defaults to \c BYLAYER if ommitted in the DXF file.\n
                 * Note that entities encapsulated in a block with the
                 * color \c BYBLOCK are represented in the "native" color of
                 * the \c BLOCK entity.\n
                 * Group code = 62. */
        int16_t paperspace;
                /*!< Entities are to be drawn on either \c PAPERSPACE or
                 * \c MODELSPACE.\n
                 * Optional, defaults to \c DXF_MODELSPACE (0).\n
                 * Group code = 67.\n
                 * \since Introduced in version R13. */
        int32_t graphics_data_size;
                /*!< Number of bytes in the proxy entity graphics
                 * represented in the sub-sequent 310 groups, which are
                 * binary chunk records (optional).\n
                 * Group code = 92.\n
                 * \since Introduced in version R2000.\n
                 * \warning On some 64 bit workstations output is
                 * generated with group code "160", thus omitting group
                 * code "92". */
        int16_t shadow_mode;
                /*!< Shadow mode:\n
                 * <ol>
                 * <li value = "0"> Casts and receives shadows.</li>
                 * <li value = "1"> Casts shadows.</li>
                 * <li value = "2"> Receives shadows.</li>
                 * <li value = "3"> Ignores shadows.</li>
                 * </ol>\n
                 * Group code = 284.\n
                 * \since Introduced in version R2009. */
        DxfBinaryData *binary_graphics_data;
                /*!< Proxy entity graphics data.\n
                 * Multiple lines of 256 characters maximum per line
                 * (optional).\n
                 * Group code = 310.\n
                 * \since Introduced in version R2000. */
        char *dictionary_owner_soft;
                /*!< Soft-pointer ID/handle to owner dictionary (optional).\n
                 * Group code = 330.\n
                 * \since Introduced in version R14. */
        char *object_owner_soft;
                /*!< Soft-pointer ID/handle  to owner BLOCK_RECORD object.\n
                 * Group code = 330.\n
                 * \since Introduced in version R2000. */
        char *material;
                /*!< Hard-pointer ID/handle to material object (present if
                 * not BYLAYER).\n
                 * Group code = 347.\n
                 * \since Introduced in version R2008. */
        char *dictionary_owner_hard;
                /*!< Hard owner ID/handle to owner dictionary (optional).\n
                 * Group code = 360.\n
                 * \since Introduced in version R14. */
        int16_t lineweight;
                /*!< Lineweight enum value.\n
                 * Stored and moved around as a 16-bit integer.\n
                 * Group code = 370.\n
                 * \since Introduced in version R2002. */
        char *plot_style_name;
                /*!< Hard pointer ID / handle of PlotStyleName object.\n
                 * Group code = 390.\n
                 * \since Introduced in version R2009. */
        int32_t color_value;
                /*!< A 24-bit color value that should be dealt with in
                 * terms of bytes with values of 0 to 255.\n
                 * The lowest byte is the blue value, the middle byte is
                 * the green value, and the third byte is the red value.\n
                 * The top byte is always 0.\n
                 * The group code cannot be used by custom entities for
                 * their own data because the group code is reserved for
                 * AcDbEntity, class-level color data and AcDbEntity,
                 * class-level transparency data.\n
                 * Group code = 420.\n
                 * \since Introduced in version R2004. */
        char *color_name;
                /*!< Color name.\n
                 * The group code cannot be used by custom entities for
                 * their own data because the group code is reserved for
                 * AcDbEntity, class-level color data and AcDbEntity,
                 * class-level transparency data.\n
                 * Group code = 430.\n
                 * \since Introduced in version R2004. */
        int32_t transparency;
                /*!< Transparency value.\n
                 * The group code cannot be used by custom entities for
                 * their own data because the group code is reserved for
                 * AcDbEntity, class-level color data and AcDbEntity,
                 * class-level transparency data.\n
                 * Group code = 440.\n
                 * \since Introduced in version R2004. */
        /* Specific members for a DXF surface. */
        DxfProprietaryData *proprietary_data;
                /*!< Proprietary data (multiple lines < 255 characters
                 * each).\n
                 * Group code = 1. */
        DxfProprietaryData *additional_proprietary_data;
                /*!< Additional lines of proprietary data if previous
                 * group 1 string is greater than 255 characters
                 * (optional).\n
                 * Group code = 3. */
        int16_t modeler_format_version_number;
                /*!< Modeler format version number (currently = 1).\n
                 * Group code = 70. */
        int16_t number_of_U_isolines;
                /*!< Number of U isolines.\n
                 * Group code = 71. */
        int16_t number_of_V_isolines;
                /*!< Number of V isolines.\n
                 * Group code = 72. */
        DXF_SURFACE_TYPE type;
                /*!< Surface type:
                 * <ol>
                 * <li value = 0>NO_TYPE</li>
                 * <li value = 1>EXTRUDED</li>
                 * <li value = 2>LOFTED</li>
                 * <li value = 3>REVOLVED</li>
                 * <li value = 4>SWEPT</li>
                 * </ol>
                 */
        struct DxfSurfaceExtruded *extruded_surface;
        struct DxfSurfaceLofted *lofted_surface;
        struct DxfSurfaceRevolved * revolved_surface;
        struct DxfSurfaceSwept *swept_surface;
        struct DxfSurface *next;
                /*!< pointer to the next DxfSurface.\n
                 * \c NULL in the last DxfSurface. */
} DxfSurface;


/*!
 * \brief DXF definition of an AutoCAD extruded surface entity.
 */
typedef struct
dxf_surface_extruded_struct
{
        DxfPoint *p0;
                /*!< Sweep vector.\n
                 * Group code = 10, 20 and 30. */
        DxfPoint *p1;
                /*!< Reference vector for controlling twist.\n
                 * Group code = 11, 21 and 31. */
        DxfDouble *transform_matrix;
                /*!< Transform matrix of extruded entity
                 * (16 reals; row major format; default = identity
                 * matrix).\n
                 * Group code = 40. */
        double draft_angle;
                /*!< Draft angle (in radians).\n
                 * Group code = 42. */
        double draft_start_distance;
                /*!< Draft start distance.\n
                 * Group code = 43. */
        double draft_end_distance;
                /*!< Draft end distance.\n
                 * Group code = 44. */
        double twist_angle;
                /*!< Twist angle.\n
                 * Group code = 45. */
        DxfDouble *sweep_matrix;
                /*!< Transform matrix of sweep entity
                 * (16 reals; row major format; default = identity
                 * matrix).\n
                 * Group code = 46. */
        DxfDouble *path_matrix;
                /*!< Transform matrix of path entity
                 * (16 reals; row major format; default = identity
                 * matrix)\n
                 * Group code = 47. */
        double scale_factor;
                /*!< Scale factor.\n
                 * Group code = 48. */
        double align_angle;
                /*!< Align angle (in radians).\n
                 * Group code = 49. */
        int16_t sweep_alignment_option;
                /*!< Sweep alignment option:
                 * <ol>
                 *   <li value = 0> No alignment.</li>
                 *   <li value = 1> Align sweep entity to path.</li>
                 *   <li value = 2> Translate sweep entity to path.</li>
                 *   <li value = 3> Translate path to sweep entity.</li>
                 * </ol>
                 * Group code = 70. */
        int32_t class_ID;
                /*!< Class ID.\n
                 * Group code = 90. */
        int32_t binary_data_size;
                /*!< Size of binary data.\n
                 * Group code = 90. */
        int solid_flag;
                /*!< Solid flag.\n
                 * Group code = 290. */
        int align_start_flag;
                /*!< Align start flag.\n
                 * Group code = 292. */
        int bank_flag;
                /*!< Bank flag.\n
                 * Group code = 293. */
        int base_point_set_flag;
                /*!< Base point set flag.\n
                 * Group code = 294. */
        int sweep_transform_computed_flag;
                /*!< Sweep entity transform computed flag.\n
                 * Group code = 295. */
        int path_transform_computed_flag;
                /*!< Path entity transform computed flag.\n
                 * Group code = 296. */
        DxfBinaryData *binary_data;
                /*!< Binary data.\n
                 * Multiple lines of 256 characters maximum per line
                 * (optional).\n
                 * Group code = 310. */
        struct DxfSurfaceExtruded *next;
                /*!< pointer to the next DxfSurfaceExtruded.\n
                 * \c NULL in the last DxfSurfaceExtruded. */
} DxfSurfaceExtruded;


/*!
 * \brief DXF definition of a DXF lofted surface entity.
 */
typedef struct
dxf_surface_lofted_struct
{
        DxfDouble *transform_matrix;
                /*!< Transform matrix of extruded entity
                 * (16 reals; row major format; default = identity
                 * matrix).\n
                 * Group code = 40. */
        double start_draft_angle;
                /*!< Start draft angle (in radians).\n
                 * Group code = 41. */
        double end_draft_angle;
                /*!< End draft angle (in radians).\n
                 * Group code = 42. */
        double start_draft_magnitude;
                /*!< Start draft magnitude.\n
                 * Group code = 43. */
        double end_draft_magnitude;
                /*!< End draft magnitude.\n
                 * Group code = 44. */
        int16_t plane_normal_lofting_type;
                /*!< Plane normal lofting type.\n
                 * Group code = 70. */
        int arc_length_parameterization_flag;
                /*!< Arc length parameterization flag.\n
                 * Group code = 290. */
        int no_twist_flag;
                /*!< No twist flag.\n
                 * Group code = 291. */
        int align_direction_flag;
                /*!< Align direction flag.\n
                 * Group code = 292. */
        int create_simple_surfaces_flag;
                /*!< Create simple surfaces flag.\n
                 * Group code = 293. */
        int create_closed_surface_flag;
                /*!< Create closed surface flag.\n
                 * Group code = 294. */
        int solid_flag;
                /*!< Solid flag.\n
                 * Group code = 295. */
        int create_ruled_surface_flag;
                /*!< Create ruled surface flag.\n
                 * Group code = 296. */
        int virtual_guide_flag;
                /*!< Virtual guide flag.\n
                 * Group code = 297. */

        /*! \todo Entity data for cross sections. */
        /*! \todo Entity data for guide curves. */
        /*! \todo Entity data for path curves. */
        
        struct DxfSurfaceLofted *next;
                /*!< pointer to the next DxfSurfaceLofted.\n
                 * \c NULL in the last DxfSurfaceLofted. */
} DxfSurfaceLofted;


/*!
 * \brief DXF definition of a DXF revolved surface entity.
 */
typedef struct
dxf_surface_revolved_struct
{
        DxfPoint *p0;
                /*!< Axis point.\n
                 * Group code = 10, 20 and 30. */
        DxfPoint *p1;
                /*!< Axis vector.\n
                 * Group code = 11, 21 and 31. */
        double revolve_angle;
                /*!< Revolve angle (in radians).\n
                 * Group code = 40. */
        double start_angle;
                /*!< Start angle (in radians).\n
                 * Group code = 41. */
        DxfDouble *transform_matrix;
                /*!< Transform matrix of revolved entity
                 * (16 reals; row major format; default = identity
                 * matrix).\n
                 * Group code = 42. */
        double draft_angle;
                /*!< Start angle (in radians).\n
                 * Group code = 43. */
        double start_draft_distance;
                /*!< Start draft distance.\n
                 * Group code = 44. */
        double end_draft_distance;
                /*!< End draft distance.\n
                 * Group code = 45. */
        double twist_angle;
                /*!< Twist angle (in radians).\n
                 * Group code = 46. */
        int32_t ID;
                /*!< ID of revolve entity.\n
                 * Group code = 90. */
        int32_t binary_data_size;
                /*!< Size of binary data.\n
                 * Group code = 90. */
        int solid_flag;
                /*!< Solid flag.\n
                 * Group code = 290. */
        int close_to_axis_flag;
                /*!< Close to axis flag.\n
                 * Group code = 291. */
        DxfBinaryData *binary_data;
                /*!< Binary data.\n
                 * Multiple lines of 256 characters maximum per line
                 * (optional).\n
                 * Group code = 310. */
        struct DxfSurfaceRevolved *next;
                /*!< pointer to the next DxfSurfaceRevolved.\n
                 * \c NULL in the last DxfSurfaceRevolved. */
} DxfSurfaceRevolved;


/*!
 * \brief DXF definition of a DXF swept surface entity.
 */
typedef struct
dxf_surface_swept_struct
{
        DxfPoint *p1;
                /*!< Reference vector for controlling twist.\n
                 * Group code = 11, 21 and 31. */
        DxfDouble *transform_sweep_matrix;
                /*!< Transform matrix of sweep entity
                 * (16 reals; row major format; default = identity
                 * matrix).\n
                 * Group code = 40. */
        DxfDouble *transform_path_matrix;
                /*!< Transform matrix of path entity
                 * (16 reals; row major format; default = identity
                 * matrix).\n
                 * Group code = 41. */
        double draft_angle;
                /*!< Start angle (in radians).\n
                 * Group code = 42. */
        double start_draft_distance;
                /*!< Start draft distance.\n
                 * Group code = 43. */
        double end_draft_distance;
                /*!< End draft distance.\n
                 * Group code = 44. */
        double twist_angle;
                /*!< Twist angle (in radians).\n
                 * Group code = 45. */
        DxfDouble *transform_sweep_matrix2;
                /*!< Transform matrix of sweep entity
                 * (16 reals; row major format; default = identity
                 * matrix).\n
                 * Group code = 46. */
        DxfDouble *transform_path_matrix2;
                /*!< Transform matrix of path entity
                 * (16 reals; row major format; default = identity
                 * matrix).\n
                 * Group code = 47. */
        double scale_factor;
                /*!< Scale factor.\n
                 * Group code = 48. */
        double align_angle;
                /*!< Align angle (in radians).\n
                 * Group code = 49. */
        int16_t sweep_alignment_option;
                /*!< Sweep alignment option:
                 * <ol>
                 *   <li value = 0> No alignment.</li>
                 *   <li value = 1> Align sweep entity to path.</li>
                 *   <li value = 2> Translate sweep entity to path.</li>
                 *   <li value = 3> Translate path to sweep entity.</li>
                 * </ol>
                 * Group code = 70. */
        int32_t sweep_ID;
                /*!< ID of sweep entity.\n
                 * Group code = 90. */
        int32_t sweep_binary_data_size;
                /*!< Size of binary data.\n
                 * Group code = 90. */
        int32_t path_ID;
                /*!< ID of path entity.\n
                 * Group code = 90. */
        int32_t path_binary_data_size;
                /*!< Size of binary data for path entity.\n
                 * Group code = 90. */
        int solid_flag;
                /*!< Solid flag.\n
                 * Group code = 290. */
        int align_start_flag;
                /*!< Align start flag.\n
                 * Group code = 292. */
        int bank_flag;
                /*!< Bank flag.\n
                 * Group code = 293. */
        int base_point_set_flag;
                /*!< Base point set flag.\n
                 * Group code = 294. */
        int sweep_transform_computed_flag;
                /*!< Sweep entity transform computed flag.\n
                 * Group code = 295. */
        int path_transform_computed_flag;
                /*!< Path entity transform computed flag.\n
                 * Group code = 296. */
        DxfBinaryData *sweep_binary_data;
                /*!< Binary data.\n
                 * Multiple lines of 256 characters maximum per line
                 * (optional).\n
                 * Group code = 310. */
        DxfBinaryData *path_binary_data;
                /*!< Binary data for path entity.\n
                 * Multiple lines of 256 characters maximum per line
                 * (optional).\n
                 * Group code = 310. */
        struct DxfSurfaceSwept *next;
                /*!< pointer to the next DxfSurfaceSwept.\n
                 * \c NULL in the last DxfSurfaceSwept. */
} DxfSurfaceSwept;


DxfSurface *dxf_surface_new ();
DxfSurface *dxf_surface_init (DxfSurface *surface);
DxfSurface *dxf_surface_read (DxfFile *fp, DxfSurface *surface);
int dxf_surface_write (DxfFile *fp, DxfSurface *surface);
int dxf_surface_free (DxfSurface *surface);
void dxf_surface_free_list (DxfSurface *surfaces);
int dxf_surface_get_id_code (DxfSurface *surface);
DxfSurface *dxf_surface_set_id_code (DxfSurface *surface, int id_code);
char *dxf_surface_get_linetype (DxfSurface *surface);
DxfSurface *dxf_surface_set_linetype (DxfSurface *surface, char *linetype);
char *dxf_surface_get_layer (DxfSurface *surface);
DxfSurface *dxf_surface_set_layer (DxfSurface *surface, char *layer);
double dxf_surface_get_elevation (DxfSurface *surface);
DxfSurface *dxf_surface_set_elevation (DxfSurface *surface, double elevation);
double dxf_surface_get_thickness (DxfSurface *surface);
DxfSurface *dxf_surface_set_thickness (DxfSurface *surface, double thickness);
double dxf_surface_get_linetype_scale (DxfSurface *surface);
DxfSurface *dxf_surface_set_linetype_scale (DxfSurface *surface, double linetype_scale);
int16_t dxf_surface_get_visibility (DxfSurface *surface);
DxfSurface *dxf_surface_set_visibility (DxfSurface *surface, int16_t visibility);
int16_t dxf_surface_get_color (DxfSurface *surface);
DxfSurface *dxf_surface_set_color (DxfSurface *surface, int16_t color);
int16_t dxf_surface_get_paperspace (DxfSurface *surface);
DxfSurface *dxf_surface_set_paperspace (DxfSurface *surface, int16_t paperspace);
int32_t dxf_surface_get_graphics_data_size (DxfSurface *surface);
DxfSurface *dxf_surface_set_graphics_data_size (DxfSurface *surface, int32_t graphics_data_size);
int16_t dxf_surface_get_shadow_mode (DxfSurface *surface);
DxfSurface *dxf_surface_set_shadow_mode (DxfSurface *surface, int16_t shadow_mode);
DxfBinaryData *dxf_surface_get_binary_graphics_data (DxfSurface *surface);
DxfSurface *dxf_surface_set_binary_graphics_data (DxfSurface *surface, DxfBinaryData *data);
char *dxf_surface_get_dictionary_owner_soft (DxfSurface *surface);
DxfSurface *dxf_surface_set_dictionary_owner_soft (DxfSurface *surface, char *dictionary_owner_soft);
char *dxf_surface_get_object_owner_soft (DxfSurface *surface);
DxfSurface *dxf_surface_set_object_owner_soft (DxfSurface *surface, char *object_owner_soft);
char *dxf_surface_get_material (DxfSurface *surface);
DxfSurface *dxf_surface_set_material (DxfSurface *surface, char *material);
char *dxf_surface_get_dictionary_owner_hard (DxfSurface *surface);
DxfSurface *dxf_surface_set_dictionary_owner_hard (DxfSurface *surface, char *dictionary_owner_hard);
int16_t dxf_surface_get_lineweight (DxfSurface *surface);
char *dxf_surface_get_plot_style_name (DxfSurface *surface);
DxfSurface *dxf_surface_set_plot_style_name (DxfSurface *surface, char *plot_style_name);
int32_t dxf_surface_get_color_value (DxfSurface *surface);
DxfSurface *dxf_surface_set_color_value (DxfSurface *surface, int32_t color_value);
char *dxf_surface_get_color_name (DxfSurface *surface);
DxfSurface *dxf_surface_set_color_name (DxfSurface *surface, char *color_name);
int32_t dxf_surface_get_transparency (DxfSurface *surface);
DxfSurface *dxf_surface_set_transparency (DxfSurface *surface, int32_t transparency);
DxfProprietaryData *dxf_surface_get_proprietary_data (DxfSurface *surface);
DxfSurface *dxf_surface_set_proprietary_data (DxfSurface *surface, DxfProprietaryData *proprietary_data);
DxfProprietaryData *dxf_surface_get_additional_proprietary_data (DxfSurface *surface);
DxfSurface *dxf_surface_set_additional_proprietary_data (DxfSurface *surface, DxfProprietaryData *additional_proprietary_data);
int16_t dxf_surface_get_modeler_format_version_number (DxfSurface *surface);
DxfSurface *dxf_surface_set_modeler_format_version_number (DxfSurface *surface, int16_t modeler_format_version_number);
int16_t dxf_surface_get_number_of_U_isolines (DxfSurface *surface);
DxfSurface *dxf_surface_set_number_of_U_isolines (DxfSurface *surface, int16_t number_of_U_isolines);
int16_t dxf_surface_get_number_of_V_isolines (DxfSurface *surface);
DxfSurface *dxf_surface_set_number_of_V_isolines (DxfSurface *surface, int16_t number_of_V_isolines);
DxfSurface *dxf_surface_get_next (DxfSurface *surface);
DxfSurface *dxf_surface_set_next (DxfSurface *surface, DxfSurface *next);
DxfSurface *dxf_surface_get_last (DxfSurface *surface);

/* Extruded surface functions. */
DxfSurfaceExtruded *dxf_surface_extruded_new ();
DxfSurfaceExtruded *dxf_surface_extruded_init (DxfSurfaceExtruded *extruded_surface);
DxfSurfaceExtruded *dxf_surface_extruded_read (DxfFile *fp, DxfSurfaceExtruded *extruded_surface);
int dxf_surface_extruded_write (DxfFile *fp, DxfSurfaceExtruded *extruded_surface);
int dxf_surface_extruded_free (DxfSurfaceExtruded *extruded_surface);
void dxf_surface_extruded_free_list (DxfSurfaceExtruded *extruded_surfaces);
DxfPoint *dxf_surface_extruded_get_p0 (DxfSurfaceExtruded *extruded_surfaces);
DxfSurfaceExtruded *dxf_surface_extruded_set_p0 (DxfSurfaceExtruded *extruded_surface, DxfPoint *p0);
double dxf_surface_extruded_get_x0 (DxfSurfaceExtruded *extruded_surface);
DxfSurfaceExtruded *dxf_surface_extruded_set_x0 (DxfSurfaceExtruded *extruded_surface, double x0);
double dxf_surface_extruded_get_y0 (DxfSurfaceExtruded *extruded_surface);
DxfSurfaceExtruded *dxf_surface_extruded_set_y0 (DxfSurfaceExtruded *extruded_surface, double y0);
double dxf_surface_extruded_get_z0 (DxfSurfaceExtruded *extruded_surface);
DxfSurfaceExtruded *dxf_surface_extruded_set_z0 (DxfSurfaceExtruded *extruded_surface, double z0);
DxfPoint *dxf_surface_extruded_get_p1 (DxfSurfaceExtruded *extruded_surfaces);
DxfSurfaceExtruded *dxf_surface_extruded_set_p1 (DxfSurfaceExtruded *extruded_surface, DxfPoint *p1);
double dxf_surface_extruded_get_x1 (DxfSurfaceExtruded *extruded_surface);
DxfSurfaceExtruded *dxf_surface_extruded_set_x1 (DxfSurfaceExtruded *extruded_surface, double x1);
double dxf_surface_extruded_get_y1 (DxfSurfaceExtruded *extruded_surface);
DxfSurfaceExtruded *dxf_surface_extruded_set_y1 (DxfSurfaceExtruded *extruded_surface, double y1);
double dxf_surface_extruded_get_z1 (DxfSurfaceExtruded *extruded_surface);
DxfSurfaceExtruded *dxf_surface_extruded_set_z1 (DxfSurfaceExtruded *extruded_surface, double z1);
DxfDouble *dxf_surface_extruded_get_transform_matrix (DxfSurfaceExtruded *extruded_surface);
DxfSurfaceExtruded *dxf_surface_extruded_set_transform_matrix (DxfSurfaceExtruded *extruded_surface, DxfDouble *transform_matrix);
double dxf_surface_extruded_get_draft_angle (DxfSurfaceExtruded *extruded_surface);
DxfSurfaceExtruded *dxf_surface_extruded_set_draft_angle (DxfSurfaceExtruded *extruded_surface, double draft_angle);
double dxf_surface_extruded_get_draft_start_distance (DxfSurfaceExtruded *extruded_surface);
DxfSurfaceExtruded *dxf_surface_extruded_set_draft_start_distance (DxfSurfaceExtruded *extruded_surface, double draft_start_distance);
double dxf_surface_extruded_get_draft_end_distance (DxfSurfaceExtruded *extruded_surface);
DxfSurfaceExtruded *dxf_surface_extruded_set_draft_end_distance (DxfSurfaceExtruded *extruded_surface, double draft_end_distance);
double dxf_surface_extruded_get_twist_angle (DxfSurfaceExtruded *extruded_surface);
DxfSurfaceExtruded *dxf_surface_extruded_set_twist_angle (DxfSurfaceExtruded *extruded_surface, double twist_angle);
DxfDouble *dxf_surface_extruded_get_sweep_matrix (DxfSurfaceExtruded *extruded_surface);
DxfSurfaceExtruded *dxf_surface_extruded_set_sweep_matrix (DxfSurfaceExtruded *extruded_surface, DxfDouble *sweep_matrix);
DxfDouble *dxf_surface_extruded_get_path_matrix (DxfSurfaceExtruded *extruded_surface);
DxfSurfaceExtruded *dxf_surface_extruded_set_path_matrix (DxfSurfaceExtruded *extruded_surface, DxfDouble *path_matrix);
double dxf_surface_extruded_get_scale_factor (DxfSurfaceExtruded *extruded_surface);
DxfSurfaceExtruded *dxf_surface_extruded_set_scale_factor (DxfSurfaceExtruded *extruded_surface, double scale_factor);
double dxf_surface_extruded_get_align_angle (DxfSurfaceExtruded *extruded_surface);
DxfSurfaceExtruded *dxf_surface_extruded_set_align_angle (DxfSurfaceExtruded *extruded_surface, double align_angle);
int16_t dxf_surface_extruded_get_sweep_alignment_option (DxfSurfaceExtruded *extruded_surface);
DxfSurfaceExtruded *dxf_surface_extruded_set_sweep_alignment_option (DxfSurfaceExtruded *extruded_surface, int16_t sweep_alignment_option);
int32_t dxf_surface_extruded_get_class_ID (DxfSurfaceExtruded *extruded_surface);
DxfSurfaceExtruded *dxf_surface_extruded_set_class_ID (DxfSurfaceExtruded *extruded_surface, int32_t class_ID);
int32_t dxf_surface_extruded_get_binary_data_size (DxfSurfaceExtruded *extruded_surface);
DxfSurfaceExtruded *dxf_surface_extruded_set_binary_data_size (DxfSurfaceExtruded *extruded_surface, int32_t binary_data_size);
int dxf_surface_extruded_get_solid_flag (DxfSurfaceExtruded *extruded_surface);
DxfSurfaceExtruded *dxf_surface_extruded_set_solid_flag (DxfSurfaceExtruded *extruded_surface, int solid_flag);
int dxf_surface_extruded_get_align_start_flag (DxfSurfaceExtruded *extruded_surface);
DxfSurfaceExtruded *dxf_surface_extruded_set_align_start_flag (DxfSurfaceExtruded *extruded_surface, int align_start_flag);
int dxf_surface_extruded_get_bank_flag (DxfSurfaceExtruded *extruded_surface);
DxfSurfaceExtruded *dxf_surface_extruded_set_bank_flag (DxfSurfaceExtruded *extruded_surface, int bank_flag);
int dxf_surface_extruded_get_align_base_point_set_flag (DxfSurfaceExtruded *extruded_surface);
DxfSurfaceExtruded *dxf_surface_extruded_set_base_point_set_flag (DxfSurfaceExtruded *extruded_surface, int base_point_set_flag);
int dxf_surface_extruded_get_align_sweep_transform_computed_flag (DxfSurfaceExtruded *extruded_surface);
DxfSurfaceExtruded *dxf_surface_extruded_set_sweep_transform_computed_flag (DxfSurfaceExtruded *extruded_surface, int sweep_transform_computed_flag);
int dxf_surface_extruded_get_path_transform_computed_flag (DxfSurfaceExtruded *extruded_surface);
DxfSurfaceExtruded *dxf_surface_extruded_set_path_transform_computed_flag (DxfSurfaceExtruded *extruded_surface, int path_transform_computed_flag);
DxfBinaryData *dxf_surface_extruded_get_binary_data (DxfSurfaceExtruded *extruded_surface);
DxfSurfaceExtruded *dxf_surface_extruded_set_binary_data (DxfSurfaceExtruded *extruded_surface, DxfBinaryData *data);
DxfSurfaceExtruded *dxf_surface_extruded_get_next (DxfSurfaceExtruded *extruded_surface);
DxfSurfaceExtruded *dxf_surface_extruded_set_next (DxfSurfaceExtruded *extruded_surface, DxfSurfaceExtruded *next);
DxfSurfaceExtruded *dxf_surface_extruded_get_last (DxfSurfaceExtruded *extruded_surface);

/* Lofted surface functions. */
DxfSurfaceLofted *dxf_surface_lofted_new ();
DxfSurfaceLofted *dxf_surface_lofted_init (DxfSurfaceLofted *lofted_surface);
DxfSurfaceLofted *dxf_surface_lofted_read (DxfFile *fp, DxfSurfaceLofted *lofted_surface);
int dxf_surface_lofted_write (DxfFile *fp, DxfSurfaceLofted *lofted_surface);
int dxf_surface_lofted_free (DxfSurfaceLofted *lofted_surface);
void dxf_surface_lofted_free_list (DxfSurfaceLofted *lofted_surfaces);
DxfDouble *dxf_surface_lofted_get_transform_matrix (DxfSurfaceLofted *lofted_surface);
DxfSurfaceLofted *dxf_surface_lofted_set_transform_matrix (DxfSurfaceLofted *lofted_surface, DxfDouble *transform_matrix);
double dxf_surface_lofted_get_start_draft_angle (DxfSurfaceLofted *lofted_surface);
DxfSurfaceLofted *dxf_surface_lofted_set_start_draft_angle (DxfSurfaceLofted *lofted_surface, double start_draft_angle);
double dxf_surface_lofted_get_end_draft_angle (DxfSurfaceLofted *lofted_surface);
DxfSurfaceLofted *dxf_surface_lofted_set_end_draft_angle (DxfSurfaceLofted *lofted_surface, double end_draft_angle);
double dxf_surface_lofted_get_start_draft_magnitude (DxfSurfaceLofted *lofted_surface);
DxfSurfaceLofted *dxf_surface_lofted_set_start_draft_magnitude (DxfSurfaceLofted *lofted_surface, double start_draft_magnitude);
double dxf_surface_lofted_get_end_draft_magnitude (DxfSurfaceLofted *lofted_surface);
DxfSurfaceLofted *dxf_surface_lofted_set_end_draft_magnitude (DxfSurfaceLofted *lofted_surface, double end_draft_magnitude);
int16_t dxf_surface_lofted_get_plane_normal_lofting_type (DxfSurfaceLofted *lofted_surface);
DxfSurfaceLofted *dxf_surface_lofted_set_plane_normal_lofting_type (DxfSurfaceLofted *lofted_surface, int16_t plane_normal_lofting_type);
int dxf_surface_lofted_get_arc_length_parameterization_flag (DxfSurfaceLofted *lofted_surface);
DxfSurfaceLofted *dxf_surface_lofted_set_arc_length_parameterization_flag (DxfSurfaceLofted *lofted_surface, int arc_length_parameterization_flag);
int dxf_surface_lofted_get_no_twist_flag (DxfSurfaceLofted *lofted_surface);
DxfSurfaceLofted *dxf_surface_lofted_set_no_twist_flag (DxfSurfaceLofted *lofted_surface, int no_twist_flag);
int dxf_surface_lofted_get_align_direction_flag (DxfSurfaceLofted *lofted_surface);
DxfSurfaceLofted *dxf_surface_lofted_set_align_direction_flag (DxfSurfaceLofted *lofted_surface, int align_direction_flag);
int dxf_surface_lofted_get_create_simple_surfaces_flag (DxfSurfaceLofted *lofted_surface);
DxfSurfaceLofted *dxf_surface_lofted_set_create_simple_surfaces_flag (DxfSurfaceLofted *lofted_surface, int create_simple_surfaces_flag);
int dxf_surface_lofted_get_create_closed_surface_flag (DxfSurfaceLofted *lofted_surface);
DxfSurfaceLofted *dxf_surface_lofted_set_create_closed_surface_flag (DxfSurfaceLofted *lofted_surface, int create_closed_surface_flag);
int dxf_surface_lofted_get_solid_flag (DxfSurfaceLofted *lofted_surface);
DxfSurfaceLofted *dxf_surface_lofted_set_solid_flag (DxfSurfaceLofted *lofted_surface, int solid_flag);
int dxf_surface_lofted_get_create_ruled_surface_flag (DxfSurfaceLofted *lofted_surface);
DxfSurfaceLofted *dxf_surface_lofted_set_create_ruled_surface_flag (DxfSurfaceLofted *lofted_surface, int create_ruled_surface_flag);
int dxf_surface_lofted_get_virtual_guide_flag (DxfSurfaceLofted *lofted_surface);
DxfSurfaceLofted *dxf_surface_lofted_set_virtual_guide_flag (DxfSurfaceLofted *lofted_surface, int virtual_guide_flag);
DxfSurfaceLofted *dxf_surface_lofted_get_next (DxfSurfaceLofted *lofted_surface);
DxfSurfaceLofted *dxf_surface_lofted_set_next (DxfSurfaceLofted *lofted_surface, DxfSurfaceLofted *next);
DxfSurfaceLofted *dxf_surface_lofted_get_last (DxfSurfaceLofted *lofted_surface);

/* Revolved surface functions. */
DxfSurfaceRevolved *dxf_surface_revolved_new ();
DxfSurfaceRevolved *dxf_surface_revolved_init (DxfSurfaceRevolved *revolved_surface);
DxfSurfaceRevolved *dxf_surface_revolved_read (DxfFile *fp, DxfSurfaceRevolved *revolved_surface);
int dxf_surface_revolved_write (DxfFile *fp, DxfSurfaceRevolved *revolved_surface);
int dxf_surface_revolved_free (DxfSurfaceRevolved *revolved_surface);
void dxf_surface_revolved_free_list (DxfSurfaceRevolved *revolved_surfaces);
DxfPoint *dxf_surface_revolved_get_p0 (DxfSurfaceRevolved *revolved_surfaces);
DxfSurfaceRevolved *dxf_surface_revolved_set_p0 (DxfSurfaceRevolved *revolved_surface, DxfPoint *p0);
double dxf_surface_revolved_get_x0 (DxfSurfaceRevolved *revolved_surface);
DxfSurfaceRevolved *dxf_surface_revolved_set_x0 (DxfSurfaceRevolved *revolved_surface, double x0);
double dxf_surface_revolved_get_y0 (DxfSurfaceRevolved *revolved_surface);
DxfSurfaceRevolved *dxf_surface_revolved_set_y0 (DxfSurfaceRevolved *revolved_surface, double y0);
double dxf_surface_revolved_get_z0 (DxfSurfaceRevolved *revolved_surface);
DxfSurfaceRevolved *dxf_surface_revolved_set_z0 (DxfSurfaceRevolved *revolved_surface, double z0);
DxfPoint *dxf_surface_revolved_get_p1 (DxfSurfaceRevolved *revolved_surfaces);
DxfSurfaceRevolved *dxf_surface_revolved_set_p1 (DxfSurfaceRevolved *revolved_surface, DxfPoint *p1);
double dxf_surface_revolved_get_x1 (DxfSurfaceRevolved *revolved_surface);
DxfSurfaceRevolved *dxf_surface_revolved_set_x1 (DxfSurfaceRevolved *revolved_surface, double x1);
double dxf_surface_revolved_get_y1 (DxfSurfaceRevolved *revolved_surface);
DxfSurfaceRevolved *dxf_surface_revolved_set_y1 (DxfSurfaceRevolved *revolved_surface, double y1);
double dxf_surface_revolved_get_z1 (DxfSurfaceRevolved *revolved_surface);
DxfSurfaceRevolved *dxf_surface_revolved_set_z1 (DxfSurfaceRevolved *revolved_surface, double z1);
double dxf_surface_revolved_get_revolve_angle (DxfSurfaceRevolved *revolved_surface);
DxfSurfaceRevolved *dxf_surface_revolved_set_revolve_angle (DxfSurfaceRevolved *revolved_surface, double revolve_angle);
double dxf_surface_revolved_get_start_angle (DxfSurfaceRevolved *revolved_surface);
DxfSurfaceRevolved *dxf_surface_revolved_set_start_angle (DxfSurfaceRevolved *revolved_surface, double start_angle);
DxfDouble *dxf_surface_revolved_get_transform_matrix (DxfSurfaceRevolved *revolved_surface);
DxfSurfaceRevolved *dxf_surface_revolved_set_transform_matrix (DxfSurfaceRevolved *revolved_surface, DxfDouble *transform_matrix);
double dxf_surface_revolved_get_draft_angle (DxfSurfaceRevolved *revolved_surface);
DxfSurfaceRevolved *dxf_surface_revolved_set_draft_angle (DxfSurfaceRevolved *revolved_surface, double draft_angle);
double dxf_surface_revolved_get_start_draft_distance (DxfSurfaceRevolved *revolved_surface);
DxfSurfaceRevolved *dxf_surface_revolved_set_start_draft_distance (DxfSurfaceRevolved *revolved_surface, double start_draft_distance);
double dxf_surface_revolved_get_end_draft_distance (DxfSurfaceRevolved *revolved_surface);
DxfSurfaceRevolved *dxf_surface_revolved_set_end_draft_distance (DxfSurfaceRevolved *revolved_surface, double end_draft_distance);
double dxf_surface_revolved_get_twist_angle (DxfSurfaceRevolved *revolved_surface);
DxfSurfaceRevolved *dxf_surface_revolved_set_twist_angle (DxfSurfaceRevolved *revolved_surface, double twist_angle);
int32_t dxf_surface_revolved_get_ID (DxfSurfaceRevolved *revolved_surface);
DxfSurfaceRevolved *dxf_surface_revolved_set_ID (DxfSurfaceRevolved *revolved_surface, int32_t ID);
int32_t dxf_surface_revolved_get_binary_data_size (DxfSurfaceRevolved *revolved_surface);
DxfSurfaceRevolved *dxf_surface_revolved_set_binary_data_size (DxfSurfaceRevolved *revolved_surface, int32_t binary_data_size);
int dxf_surface_revolved_get_solid_flag (DxfSurfaceRevolved *revolved_surface);
DxfSurfaceRevolved *dxf_surface_revolved_set_solid_flag (DxfSurfaceRevolved *revolved_surface, int solid_flag);
int dxf_surface_revolved_get_close_to_axis_flag (DxfSurfaceRevolved *revolved_surface);
DxfSurfaceRevolved *dxf_surface_revolved_set_close_to_axis_flag (DxfSurfaceRevolved *revolved_surface, int close_to_axis_flag);
DxfBinaryData *dxf_surface_revolved_get_binary_data (DxfSurfaceRevolved *revolved_surface);
DxfSurfaceRevolved *dxf_surface_revolved_set_binary_data (DxfSurfaceRevolved *revolved_surface, DxfBinaryData *data);
DxfSurfaceRevolved *dxf_surface_revolved_get_next (DxfSurfaceRevolved *revolved_surface);
DxfSurfaceRevolved *dxf_surface_revolved_set_next (DxfSurfaceRevolved *revolved_surface, DxfSurfaceRevolved *next);
DxfSurfaceRevolved *dxf_surface_revolved_get_last (DxfSurfaceRevolved *revolved_surface);

/* Swept surface functions. */
DxfSurfaceSwept *dxf_surface_swept_new ();
DxfSurfaceSwept *dxf_surface_swept_init (DxfSurfaceSwept *swept_surface);
DxfSurfaceSwept *dxf_surface_swept_read (DxfFile *fp, DxfSurfaceSwept *swept_surface);
int dxf_surface_swept_write (DxfFile *fp, DxfSurfaceSwept *swept_surface);
int dxf_surface_swept_free (DxfSurfaceSwept *swept_surface);
void dxf_surface_swept_free_list (DxfSurfaceSwept *swept_surfaces);
DxfPoint *dxf_surface_swept_get_p1 (DxfSurfaceSwept *swept_surfaces);
DxfSurfaceSwept *dxf_surface_swept_set_p1 (DxfSurfaceSwept *swept_surface, DxfPoint *p1);
double dxf_surface_swept_get_x1 (DxfSurfaceSwept *swept_surface);
DxfSurfaceSwept *dxf_surface_swept_set_x1 (DxfSurfaceSwept *swept_surface, double x1);
double dxf_surface_swept_get_y1 (DxfSurfaceSwept *swept_surface);
DxfSurfaceSwept *dxf_surface_swept_set_y1 (DxfSurfaceSwept *swept_surface, double y1);
double dxf_surface_swept_get_z1 (DxfSurfaceSwept *swept_surface);
DxfSurfaceSwept *dxf_surface_swept_set_z1 (DxfSurfaceSwept *swept_surface, double z1);
DxfDouble *dxf_surface_swept_get_transform_sweep_matrix (DxfSurfaceSwept *swept_surface);
DxfSurfaceSwept *dxf_surface_swept_set_transform_sweep_matrix (DxfSurfaceSwept *swept_surface, DxfDouble *transform_sweep_matrix);
DxfDouble *dxf_surface_swept_get_transform_path_matrix (DxfSurfaceSwept *swept_surface);
DxfSurfaceSwept *dxf_surface_swept_set_transform_path_matrix (DxfSurfaceSwept *swept_surface, DxfDouble *transform_path_matrix);
double dxf_surface_swept_get_draft_angle (DxfSurfaceSwept *swept_surface);
DxfSurfaceSwept *dxf_surface_swept_set_draft_angle (DxfSurfaceSwept *swept_surface, double draft_angle);
double dxf_surface_swept_get_start_draft_distance (DxfSurfaceSwept *swept_surface);
DxfSurfaceSwept *dxf_surface_swept_set_start_draft_distance (DxfSurfaceSwept *swept_surface, double start_draft_distance);
double dxf_surface_swept_get_end_draft_distance (DxfSurfaceSwept *swept_surface);
DxfSurfaceSwept *dxf_surface_swept_set_end_draft_distance (DxfSurfaceSwept *swept_surface, double end_draft_distance);
double dxf_surface_swept_get_twist_angle (DxfSurfaceSwept *swept_surface);
DxfSurfaceSwept *dxf_surface_swept_set_twist_angle (DxfSurfaceSwept *swept_surface, double twist_angle);
DxfDouble *dxf_surface_swept_get_transform_sweep_matrix2 (DxfSurfaceSwept *swept_surface);
DxfSurfaceSwept *dxf_surface_swept_set_transform_sweep_matrix2 (DxfSurfaceSwept *swept_surface, DxfDouble *transform_sweep_matrix2);
DxfDouble *dxf_surface_swept_get_transform_path_matrix2 (DxfSurfaceSwept *swept_surface);
DxfSurfaceSwept *dxf_surface_swept_set_transform_path_matrix2 (DxfSurfaceSwept *swept_surface, DxfDouble *transform_path_matrix2);
double dxf_surface_swept_get_scale_factor (DxfSurfaceSwept *swept_surface);
DxfSurfaceSwept *dxf_surface_swept_set_scale_factor (DxfSurfaceSwept *swept_surface, double scale_factor);
double dxf_surface_swept_get_align_angle (DxfSurfaceSwept *swept_surface);
DxfSurfaceSwept *dxf_surface_swept_set_align_angle (DxfSurfaceSwept *swept_surface, double align_angle);
int16_t dxf_surface_swept_get_sweep_alignment_option (DxfSurfaceSwept *swept_surface);
DxfSurfaceSwept *dxf_surface_swept_set_sweep_alignment_option (DxfSurfaceSwept *swept_surface, int16_t sweep_alignment_option);
int32_t dxf_surface_swept_get_sweep_ID (DxfSurfaceSwept *swept_surface);
DxfSurfaceSwept *dxf_surface_swept_set_sweep_ID (DxfSurfaceSwept *swept_surface, int32_t sweep_ID);
int32_t dxf_surface_swept_get_sweep_binary_data_size (DxfSurfaceSwept *swept_surface);
DxfSurfaceSwept *dxf_surface_swept_set_sweep_binary_data_size (DxfSurfaceSwept *swept_surface, int32_t sweep_binary_data_size);
int32_t dxf_surface_swept_get_path_ID (DxfSurfaceSwept *swept_surface);
DxfSurfaceSwept *dxf_surface_swept_set_path_ID (DxfSurfaceSwept *swept_surface, int32_t path_ID);
int32_t dxf_surface_swept_get_path_binary_data_size (DxfSurfaceSwept *swept_surface);
DxfSurfaceSwept *dxf_surface_swept_set_path_binary_data_size (DxfSurfaceSwept *swept_surface, int32_t path_binary_data_size);
int dxf_surface_swept_get_solid_flag (DxfSurfaceSwept *swept_surface);
DxfSurfaceSwept *dxf_surface_swept_set_solid_flag (DxfSurfaceSwept *swept_surface, int solid_flag);
int dxf_surface_swept_get_align_start_flag (DxfSurfaceSwept *swept_surface);
DxfSurfaceSwept *dxf_surface_swept_set_align_start_flag (DxfSurfaceSwept *swept_surface, int align_start_flag);
int dxf_surface_swept_get_bank_flag (DxfSurfaceSwept *swept_surface);
DxfSurfaceSwept *dxf_surface_swept_set_bank_flag (DxfSurfaceSwept *swept_surface, int bank_flag);
int dxf_surface_swept_get_base_point_set_flag (DxfSurfaceSwept *swept_surface);
DxfSurfaceSwept *dxf_surface_swept_set_base_point_set_flag (DxfSurfaceSwept *swept_surface, int base_point_set_flag);
int dxf_surface_swept_get_sweep_transform_computed_flag (DxfSurfaceSwept *swept_surface);
DxfSurfaceSwept *dxf_surface_swept_set_sweep_transform_computed_flag (DxfSurfaceSwept *swept_surface, int sweep_transform_computed_flag);
DxfBinaryData *dxf_surface_swept_get_sweep_binary_data (DxfSurfaceSwept *swept_surface);
DxfSurfaceSwept *dxf_surface_swept_set_sweep_binary_data (DxfSurfaceSwept *swept_surface, DxfBinaryData *sweep_binary_data);
DxfBinaryData *dxf_surface_swept_get_path_binary_data (DxfSurfaceSwept *swept_surface);
DxfSurfaceSwept *dxf_surface_swept_set_path_binary_data (DxfSurfaceSwept *swept_surface, DxfBinaryData *path_binary_data);
DxfSurfaceSwept *dxf_surface_swept_get_next (DxfSurfaceSwept *swept_surface);
DxfSurfaceSwept *dxf_surface_swept_set_next (DxfSurfaceSwept *swept_surface, DxfSurfaceSwept *next);
DxfSurfaceSwept *dxf_surface_swept_get_last (DxfSurfaceSwept *swept_surface);


#ifdef __cplusplus
}
#endif


#endif /* LIBDXF_SRC_SURFACE_H */


/* EOF */
