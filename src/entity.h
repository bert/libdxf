/*!
 * \file entity.h
 * \author Copyright (C) 2008, 2009, 2010 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 * \brief Header file for DXF entity functions.
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
 * For more details see http://www.autodesk.com.\n\n
 * <hr>
 */


#ifndef ENTITY_H
#define ENTITY_H


/*!
 * \brief DXF definition of common properties of an AutoCAD entity.
 */
typedef struct
dxf_entity
{
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
        double thickness;
                /*!< Thickness of the arc in the local Z-direction.\n
                 * Defaults to 0.0 if ommitted in the DXF file.\n
                 * Group code = 39. */
        int color;
                /*!< Color of the entity.\n
                 * Defaults to \c BYLAYER if ommitted in the DXF file.\n
                 * Note that entities encapsulated in a block with the
                 * color \c BYBLOCK are represented in the "native" color of
                 * the \c BLOCK entity.\n
                 * Group code = 62. */
        int paperspace;
                /*!< Entities are to be drawn on either \c PAPERSPACE or
                 * \c MODELSPACE.\n
                 * Optional, defaults to \c DXF_MODELSPACE (0).\n
                 * Group code = 67. */
        int acad_version_number;
                /*!< AutoCAD version number. */
} DxfEntity, * DxfEntityPtr;


/*!
 * \brief DXF entity types.
 */
typedef enum
dxf_entity_type
{
        APPID,
        ARC,
        ATTDEF,
        ATTRIB,
        BLOCK,
        CIRCLE,
        DIMSTYLE,
        HEADER,
        INSERT,
        LAYER,
        LINE,
        LTYPE,
        POINT,
        POLYLINE,
        SHAPE,
        SOLID,
        STYLE,
        TEXT,
        TRACE,
        UCS,
        VIEW,
        VPORT
} DxfEntityType;


int
dxf_read_entities
(
       char *filename,
       FILE *fp,
       int line_number,
       char *dxf_entities_list,
       int acad_version_number
);
int
dxf_skip_entity
(
        char *dxf_entity_name
);
int
dxf_write_entities
(
        char *dxf_entities_list,
        int acad_version_number
);


#endif /* ENTITY_H */


/* EOF */
