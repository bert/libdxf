/*!
 * \file seqend.c
 *
 * \author Copyright (C) 2008 ... 2014 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF end of sequence marker (\c SEQEND).
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


#include "seqend.h"


/*!
 * \brief Allocate memory for a DXF \c SEQEND.
 *
 * Fill the memory contents with zeros.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfSeqend *
dxf_seqend_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfSeqend *dxf_seqend = NULL;
        size_t size;

        size = sizeof (DxfSeqend);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_seqend = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfSeqend struct.\n")),
                  __FUNCTION__);
                dxf_seqend = NULL;
        }
        else
        {
                memset (dxf_seqend, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_seqend);
}


/*!
 * \brief Write DXF output to a file for an end of sequence marker
 * (\c SEQEND).
 *
 * No fields.\n
 * This entity marks the end of vertices (Vertex type name) for a 
 * Polyline (\c POLYLINE), a Light Wight Polyline (\c LWPOLYLINE)
 * or the end of Attribute entities (Attrib type name) for an Insert
 * entity (\c INSERT) that has Attributes (indicated by 66 group present
 * and nonzero).
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_seqend_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfSeqend *dxf_seqend
                /*!< DXF \c SEQEND entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("SEQEND");

        /* Do some basic checks. */
        if (fp == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL file pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dxf_seqend == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (strcmp (dxf_seqend->linetype, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty linetype string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, dxf_seqend->id_code);
                fprintf (stderr,
                  (_("\t%s entity is reset to default linetype")),
                  dxf_entity_name);
                dxf_seqend->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (dxf_seqend->layer, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, dxf_seqend->id_code);
                fprintf (stderr,
                  (_("\t%s entity is relocated to layer 0")),
                  dxf_entity_name);
                dxf_seqend->layer = DXF_DEFAULT_LAYER;
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (dxf_seqend->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", dxf_seqend->id_code);
        }
        fprintf (fp->fp, "  8\n%s\n", dxf_seqend->layer);
        if (strcmp (dxf_seqend->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", dxf_seqend->linetype);
        }
        if (dxf_seqend->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", dxf_seqend->color);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
