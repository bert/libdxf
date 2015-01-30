/*!
 * \file block_record.c
 *
 * \author Copyright (C) 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF block record symbol table entry
 * (\c BLOCK_RECORD).
 *
 * \version The \c BLOCK_RECORD table was introduced in DXF R13.
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


#include "block_record.h"


/*!
 * \brief Allocate memory for a DXF \c BLOCK_RECORD symbol table entry.
 *
 * Fill the memory contents with zeros.
 */
DxfBlockRecord *
dxf_block_record_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfBlockRecord *block_record = NULL;
        size_t size;

        size = sizeof (DxfBlockRecord);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((block_record = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfBlockRecord struct.\n")),
                  __FUNCTION__);
                block_record = NULL;
        }
        else
        {
                memset (block_record, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (block_record);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF
 * \c BLOCK_RECORD symbol table entry.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfBlockRecord *
dxf_block_record_init
(
        DxfBlockRecord *block_record
                /*!< DXF block record symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (block_record == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                block_record = dxf_block_record_new ();
        }
        if (block_record == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfBlockRecord struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        block_record->id_code = 0;
        block_record->block_name = strdup ("");
        block_record->flag = 0;
        block_record->dictionary_owner_soft = strdup ("");
        block_record->dictionary_owner_hard = strdup ("");
        block_record->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (block_record);
}


/*!
 * \brief Free the allocate memory for a DXF \c BLOCK_RECORD and all
 * it's data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_block_record_free
(
        DxfBlockRecord *block_record
                /*!< DXF \c BLOCK_RECORD symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (block_record->next != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to next DxfBlockRecord was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (block_record->block_name);
        free (block_record->dictionary_owner_soft);
        free (block_record->dictionary_owner_hard);
        free (block_record);
        block_record = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/* EOF*/
