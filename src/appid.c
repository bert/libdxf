/*!
 * \file appid.c
 * \author Copyright (C) 2009, 2010, 2011 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 * \brief Functions for a DXF application identity entity (\c APPID).
 *
 * A DXF \c APPID entity contains data concerning the application registered
 * with the drawing involved.\n
 * It is a table entry in the \c TABLES section of the DXF file.
 * These table entries maintain a set of names for all applications
 * registered with a drawing.
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


#include "appid.h"


/*!
 * \brief Allocate memory for a \c DxfAppid.
 *
 * Fill the memory contents with zeros.
 */
DxfAppid *
dxf_appid_new ()
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_appid_new () function.\n",
                __FILE__, __LINE__);
#endif
        DxfAppid *dxf_appid = NULL;
        size_t size;

        size = sizeof (DxfAppid);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_appid = malloc (size)) == NULL)
        {
                fprintf (stderr, "ERROR in dxf_appid_new () could not allocate memory for a DxfAppid struct.\n");
                dxf_appid = NULL;
        }
        else
        {
                memset (dxf_appid, 0, size);
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_appid_new () function.\n",
                __FILE__, __LINE__);
#endif
        return (dxf_appid);
}


/*!
 * \brief Write DXF output for an \c APPID entity.
 */
static int
dxf_appid_write_lowlevel
(
        FILE *fp,
                /*!< File pointer to output file (or device). */
        int acad_version_number,
                /*!< AutoCAD version number. */
        int id_code,
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file.\n
                 * Group code = 5. */
        char *application_name,
                /*!< Name of the application registered with the drawing.\n
                 * Group code = 2. */
        int standard_flag
                /*!< This flag is for the benefit of AutoCAD commands;
                 * it can be ignored by most programs that read DXF files,
                 * and need not be set by programs that write DXF files.\n
                 * bit coded:\n
                 * 16 = if set, table entry is externally dependent on an
                 *      Xref.\n
                 * 32 = if this bit and bit 16 are both set, the externally
                 *      dependent Xref has been successfully resolved.\n
                 * 64 = if set, the table entry was referenced by at least
                 *      one entity in the drawing the last time the drawing
                 *      was edited.\n
                 * Group code = 70. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_appid_write_lowlevel () function.\n",
                __FILE__, __LINE__);
#endif
        char *dxf_entity_name = strdup ("APPID");

        if (strcmp (application_name, "") == 0)
        {
                fprintf (stderr, "Warning: empty block name string for the %s entity with id-code: %x\n",
                        dxf_entity_name, id_code);
                fprintf (stderr, "    %s entity is relocated to default layer.\n",
                        dxf_entity_name);
        }
        fprintf (fp, "  0\n%s\n", dxf_entity_name);
        if (id_code != -1)
        {
                fprintf (fp, "  5\n%x\n", id_code);
        }
        fprintf (fp, "  2\n%s\n", application_name);
        fprintf (fp, " 70\n%d\n", standard_flag);
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_appid_write_lowlevel () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write DXF output to a file for an \c APPID entity.
 */
int
dxf_appid_write
(
        FILE *fp,
                /*!< file pointer to output file (or device). */
        DxfAppid dxf_appid
                /*!< DXF appid entity. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_appid_write () function.\n",
                __FILE__, __LINE__);
#endif
        char *dxf_entity_name = strdup ("APPID");
        if (dxf_appid.application_name == NULL)
        {
                fprintf (stderr, "Warning: empty block name string for the %s entity with id-code: %x\n",
                        dxf_entity_name, dxf_appid.id_code);
                fprintf (stderr, "         %s entity is discarded from output.\n",
                        dxf_entity_name);
                return (EXIT_FAILURE);
        }
        fprintf (fp, "  0\n%s\n", dxf_entity_name);
        if (dxf_appid.id_code != -1)
        {
                fprintf (fp, "  5\n%x\n", dxf_appid.id_code);
        }
        fprintf (fp, "  2\n%s\n", dxf_appid.application_name);
        fprintf (fp, " 70\n%d\n", dxf_appid.standard_flag);
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_appid_write () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/* EOF*/
