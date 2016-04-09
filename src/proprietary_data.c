/*!
 * \file proprietary_data.c
 *
 * \author Copyright (C) 2016 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF proprietary data entity.
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


#include "proprietary_data.h"


/*!
 * \brief Allocate memory for a DXF \c DxfProprietaryData object.
 *
 * Fill the memory contents with zeros.
 */
DxfProprietaryData *
dxf_proprietary_data_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfProprietaryData *data = NULL;
        size_t size;

        size = sizeof (DxfProprietaryData);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((data = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfProprietaryData struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        else
        {
                memset (data, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data);
}


/*!
 * \brief Free the allocated memory for a DXF \c DxfProprietaryData
 * object and all it's data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_proprietary_data_free
(
        DxfProprietaryData *data
                /*!< a pointer to the memory occupied by the DXF
                 * \c DxfProprietaryData object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (data->next != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to next DxfProprietaryData was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (data->data_line);
        free (data);
        data = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a chain of DXF
 * \c DxfProprietaryData objects and all their data fields.
 */
void
dxf_proprietary_data_free_chain
(
        DxfProprietaryData *datas
                /*!< a pointer to the chain of DXF \c DxfProprietaryData
                 * objects. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (datas == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (datas != NULL)
        {
                struct DxfProprietaryData *iter = datas->next;
                dxf_proprietary_data_free (datas);
                datas = (DxfProprietaryData *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the incremental counter \c order from a DXF
 * \c DxfProprietaryData object.
 *
 * \return incremental counter \c order.
 */
int
dxf_proprietary_data_get_order
(
        DxfProprietaryData *data
                /*!< a pointer to a DXF \c DxfProprietaryData entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (data == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (data->order < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the order member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (data->order);
}


/* EOF */
