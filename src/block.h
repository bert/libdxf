/*!
 * \file block.h
 * \author Copyright (C) 2008, 2009, 2010 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 * \brief Definition of a DXF block entity (\c BLOCK).
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


#ifndef BLOCK_H
#define BLOCK_H


#include "global.h"
#include "entity.h"


/*!
 * \brief DXF definition of an AutoCAD block entity.
 *
 * The Blocks section of the DXF file contains all the Block Definitions.\n
 * This section contains the entities that make up the Blocks used in the
 * drawing, including anonymous Blocks generated by the HATCH command and by
 * associative dimensioning.\n
 * The format of the entities in this section is identical to those in the
 * Entities section described later, so see that section for details.\n
 * All entities in the Blocks section appear between Block and Endblk
 * entities.\n
 * Block and Endblk entities appear only in the Blocks section.\n
 * Block definitions are never nested (that is, no Block or Endblk entity
 * ever appears within another Block-Endblk pair), although a Block
 * definition can contain an INSERT entity.\n
 * \n
 * External References are written in the DXF file as any Block Definition,
 * except they also include a text string (group code 1) of the path and
 * filename of the External Reference.\n
 */
typedef struct
dxf_block
{
        DxfEntity common;
                /*!< common properties for DXF entities. */
        char *xref_name;
                /*!< group code = 1. */
        char *block_name;
                /*!< group code = 2 and 3. */
        double x0;
                /*!< group code = 10\n
                 * base point. */
        double y0;
                /*!< group code = 20\n
                 * base point. */
        double z0;
                /*!< group code = 30\n
                 * base point. */
        double extr_x0;
                /*!< X-value of the extrusion vector.\n
                 * Defaults to 0.0 if ommitted in the DXF file.\n
                 * Group code = 210. */
        double extr_y0;
                /*!< Y-value of the extrusion vector.\n
                 * Defaults to 0.0 if ommitted in the DXF file.\n
                 * Group code = 220. */
        double extr_z0;
                /*!< Z-value of the extrusion vector.\n
                 * Defaults to 1.0 if ommitted in the DXF file.\n
                 * Group code = 230. */
        int block_type;
                /*!< group code = 70\n
                 * bit coded:\n
                 * 1 = this is an anonymous Block generated by hatching,
                 *     associative dimensioning, other internal operations,
                 *     or an application\n
                 * 2 = this Block has Attributes\n
                 * 4 = this Block is an external reference (Xref)\n
                 * 8 = not used\n
                 * 16 = this Block is externally dependent\n
                 * 32 = this is a resolved external reference, or dependent
                 *      of an external reference\n
                 * 64 = this definition is referenced. */
} DxfBlock, * DxfBlockPtr;


DxfBlock *
dxf_block_new ();
DxfBlock *
dxf_block_init
(
        DxfBlock *dxf_block
);
int
dxf_block_write_lowlevel
(
        FILE *fp,
        int id_code,
        char *xref_name,
        char *block_name,
        char *linetype,
        char *layer,
        double x0,
        double y0,
        double z0,
        double thickness,
        int color,
        int paperspace,
        int block_type
);
int
dxf_blocks_write
(
        FILE *fp,
        DxfBlock dxf_block
);
int
dxf_block_write_endblk (FILE *fp);
int
dxf_block_write_table
(
        char *dxf_blocks_list, 
        int acad_version_number
);


#endif /* BLOCK_H */


/* EOF */
