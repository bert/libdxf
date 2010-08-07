/*!
 * \file entity.c
 * \author Copyright (C) 2008, 2009, 2010 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 * \brief DXF entity typedefinition.
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


#include "global.h"


/*!
 * \brief Read entities from a DXF file.
 */
int
dxf_read_entities
(
        char *filename,
                /*!< filename of input file (or device). */
        FILE *fp,
                /*!< filepointer to the input file (or device). */
        int line_number,
                /*!< current line number in the input file (or device). */
        char *dxf_entities_list, 
                /*!< pointer to a list of entities. */
        int acad_version_number
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_read_entities () function.\n", __FILE__, __LINE__);
#endif
        /*! \todo Add code here. */
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_read_entities () function.\n", __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Prints warning on stderr and asks for confirmation (if interactive)
 * on skipping output for an entity to a file (or device).
 */
int
dxf_skip_entity
(
        char *dxf_entity_name
                /*!< Type of the entity skipped from output. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_skip_entity () function.\n", __FILE__, __LINE__);
#endif
        char answer;
        if (dxf_entity_name == NULL) return (EXIT_FAILURE);
        if (INTER_ACTIVE_PROMPT)
        {
                fprintf (stderr, "    skip %s entity ? [Y/N]:\n", dxf_entity_name);
                answer = getchar ();
                if ((answer == 'Y') || (answer == 'y'))
                {
                        fprintf (stderr, "    OK, done.\n");
                }
        }
        else
        {
                fprintf (stderr, "    skipping %s entity.\n", dxf_entity_name);
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_skip_entity () function.\n", __FILE__, __LINE__);
#endif
		return (EXIT_SUCCESS);
}


/*!
 * \brief Write DXF output to a file for a table of entities.
 *
 * Appears only in \c TABLES section.\n
 */
int
dxf_write_entities
(
        char *dxf_entities_list, 
        int acad_version_number
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_write_entities () function.\n", __FILE__, __LINE__);
#endif
        /*! \todo Add code here. */
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_write_entities () function.\n", __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
