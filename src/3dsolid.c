/*!
 * \file 3dsolid.c
 *
 * \author Copyright (C) 2012 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF 3D solid entity (\c 3DSOLID).
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


#include "3dsolid.h"


/*!
 * \brief Allocate memory for a \c Dxf3dsolid.
 *
 * Fill the memory contents with zeros.
 */
Dxf3dsolid *
dxf_3dsolid_new ()
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_3dsolid_new () function.\n",
                __FILE__, __LINE__);
#endif
        Dxf3dsolid *dxf_3dsolid = NULL;
        size_t size;

        size = sizeof (Dxf3dsolid);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_3dsolid = malloc (size)) == NULL)
        {
                fprintf (stderr, "ERROR in dxf_3dsolid_new () could not allocate memory for a Dxf3dsolid struct.\n");
                dxf_3dsolid = NULL;
        }
        else
        {
                memset (dxf_3dsolid, 0, size);
        }
/*!
 * \todo Allocate memory for data fields and fill with NULL pointers ?
 * <pre>
        int i;
        int j;

        if ((dxf_3dsolid->proprietary_data = malloc (DXF_MAX_STRING_LENGTH * DXF_MAX_PARAM)) == NULL)
        {
                fprintf (stderr, "ERROR in dxf_3dsolid_init () could not allocate memory for a Dxf3dsolid struct.\n");
                dxf_3dsolid = NULL;
        }
        if ((dxf_3dsolid->additional_proprietary_data = malloc (DXF_MAX_STRING_LENGTH * DXF_MAX_PARAM)) == NULL)
        {
                fprintf (stderr, "ERROR in dxf_3dsolid_init () could not allocate memory for a Dxf3dsolid struct.\n");
                dxf_3dsolid = NULL;
        }
        for (i = 0; i <= DXF_MAX_STRING_LENGTH; i++)
        {
                for (j = 0; j <= DXF_MAX_PARAM; j++)
                {
                        dxf_3dsolid->proprietary_data[i][j] = NULL;
                        dxf_3dsolid->additional_proprietary_data[i][j] = NULL;
                }
        }
 * </pre>
 */
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_3dsolid_new () function.\n",
                __FILE__, __LINE__);
#endif
        return (dxf_3dsolid);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c 3DSOLID
 * entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
Dxf3dsolid *
dxf_3dsolid_init
(
        Dxf3dsolid *dxf_3dsolid
                /*!< DXF \c 3DSOLID entity. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_3dsolid_init () function.\n",
                __FILE__, __LINE__);
#endif
        dxf_3dsolid = dxf_3dsolid_new ();
        if (dxf_3dsolid == NULL)
        {
              fprintf (stderr, "ERROR in dxf_3dsolid_init () could not allocate memory for a Dxf3dsolid struct.\n");
              return (NULL);
        }
        dxf_3dsolid->modeler_format_version_number = 0;
        dxf_3dsolid->common.id_code = 0;
        dxf_3dsolid->common.linetype = strdup (DXF_DEFAULT_LINETYPE);
        dxf_3dsolid->common.layer = strdup (DXF_DEFAULT_LAYER);
        dxf_3dsolid->common.thickness = 0.0;
        dxf_3dsolid->common.color = DXF_COLOR_BYLAYER;
        dxf_3dsolid->common.paperspace = DXF_MODELSPACE;
        dxf_3dsolid->common.acad_version_number = 0;
        dxf_3dsolid->next = NULL;
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_3dsolid_init () function.\n",
                __FILE__, __LINE__);
#endif
        return (dxf_3dsolid);
}


/*!
 * \brief Free the allocated memory for a DXF \c 3DSOLID and all it's
 * data fields.
 */
int
dxf_3dsolid_free
(
        Dxf3dsolid *dxf_3dsolid
                /*!< Pointer to the memory occupied by the DXF
                 * \c 3DSOLID entity. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_3dsolid_free () function.\n",
                __FILE__, __LINE__);
#endif
        free (dxf_3dsolid->common.linetype);
        free (dxf_3dsolid->common.layer);
        free (dxf_3dsolid);
        dxf_3dsolid = NULL;
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_3dsolid_free () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
