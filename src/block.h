/*!
 * \file block.h
 *
 * \author Copyright (C) 2008 ... 2014 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF block entity (\c BLOCK).
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
#include "util.h"
#include "entity.h"
#include "endblk.h"


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
 *
 * \version According to DXF R10.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
typedef struct
dxf_block
{
        char *xref_name;
                /*!< Xref path name.\n
                 * Group code = 1. */
        char *block_name;
                /*!< Block name.\n
                 * Group code = 2. */
        char *block_name_additional;
                /*!< Additional block name.\n
                 * Group code = 3. */
        char *description;
                /*!< Block description (optional).\n
                 * Group code = 4. */
        int id_code;
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file.\n
                 * Group code = 5. */
        char *layer;
                /*!< Layer on which the entity is drawn.\n
                 * Defaults to layer "0" if no valid layername is given.\n
                 * Group code = 8. */
        double x0;
                /*!< Base point, X-value.\n
                 * Group code = 10. */
        double y0;
                /*!< Base point, Y-value.\n
                 * Group code = 20. */
        double z0;
                /*!< Base point, Z-value.\n
                 * Group code = 30. */
        int block_type;
                /*!< Bit coded:\n
                 * <ol>
                 * <li value = "1"> this is an anonymous Block generated
                 * by hatching, associative dimensioning, other internal
                 * operations, or an application.</li>
                 * <li value = "2"> this Block has Attributes.</li>
                 * <li value = "4"> this Block is an external reference (Xref).</li>
                 * <li value = "8"> not used.</li>
                 * <li value = "16"> this Block is externally dependent.</li>
                 * <li value = "32"> this is a resolved external
                 * reference, or dependent of an external reference.</li>
                 * <li value = "64"> this definition is referenced.</li>
                 * </ol>
                 * Group code = 70. */
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
        char *dictionary_owner_soft;
                /*!< Soft-pointer ID/handle to owner dictionary
                 * (optional).\n
                 * Group code = 330. */
        struct DxfEndblk *endblk;
                /*!< pointer to the end of block marker. */
        struct DxfBlock *next;
                /*!< pointer to the next DxfBlock.\n
                 * \c NULL in the last DxfBlock. */
        
} DxfBlock, * DxfBlockPtr;


DxfBlock *dxf_block_new ();
DxfBlock *dxf_block_init
(
        DxfBlock *dxf_block
);
int dxf_block_read
(
        DxfFile *fp,
        DxfBlock *dxf_block
);
int dxf_block_write
(
        DxfFile *fp,
        DxfBlock *dxf_block
);
int dxf_block_write_endblk
(
        DxfFile *fp
);
int dxf_block_write_table
(
        DxfFile *fp,
        DxfBlock *dxf_blocks_list
);
int dxf_block_free
(
        DxfBlock *dxf_block
);


#endif /* BLOCK_H */


/* EOF */
