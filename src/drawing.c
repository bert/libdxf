/*!
 * \file drawing.c
 *
 * \author Copyright (C) 2016, 2018, 2020, 2021
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a libDXF drawing.
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


#include "drawing.h"


/*!
 * \brief Allocate memory for a libDXF \c drawing.
 *
 * Fill the memory contents with zeros.
 *
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfDrawing *
dxf_drawing_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfDrawing *drawing = NULL;
        size_t size;

        size = sizeof (DxfDrawing);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((drawing = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                drawing = NULL;
        }
        else
        {
                memset (drawing, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (drawing);
}


/*!
 * \brief Allocate memory and initialize data fields in a libDXF drawing.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfDrawing *
dxf_drawing_init
(
        DxfDrawing *drawing,
                /*!< a pointer to the libDXF drawing. */
        int acad_version_number
                /*!< AutoCAD version number.\n */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (drawing == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                drawing = dxf_drawing_new ();
                if (drawing == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        /* Initialize new structs for the following members later,
         * when they are required and when we have content. */
        drawing->header = NULL;
        drawing->class_list = NULL;
        drawing->block_list = NULL;
        drawing->entities_list = NULL;
        drawing->object_list = NULL;
        drawing->thumbnail = NULL;
        drawing->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (drawing);
}


/*!
 * \brief Free the allocated memory for a libDXF drawing and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_drawing_free
(
        DxfDrawing *drawing
                /*!< a pointer to the memory occupied by the libDXF
                 * drawing. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (drawing == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (drawing->next != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to next was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        dxf_header_free ((DxfHeader *) drawing->header);
        dxf_class_free_list ((DxfClass *) drawing->class_list);
        dxf_block_free_list ((DxfBlock *) drawing->block_list);
        //dxf_entities_free_list ((DxfEntities *) drawing->entities_list);
        dxf_object_free_list ((DxfObject *) drawing->object_list);
        dxf_thumbnail_free ((DxfThumbnail *) drawing->thumbnail);
        free (drawing);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Get the header from a libDXF drawing.
 *
 * \return \c header when successful, \c NULL when an error occurred.
 */
DxfHeader *
dxf_drawing_get_header
(
        DxfDrawing *drawing
                /*!< a pointer to a libDXF drawing. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfHeader *result = NULL;

        /* Do some basic checks. */
        if (drawing == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (drawing->header ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = (DxfHeader *) drawing->header;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the header for a libDXF drawing.
 *
 * \return a pointer to the libDXF drawing when OK, \c NULL when an
 * error occurred.
 */
DxfDrawing *
dxf_drawing_set_header
(
        DxfDrawing *drawing,
                /*!< a pointer to a libDXF drawing. */
        DxfHeader *header
                /*!< a string containing the header for the libDXF
                 * drawing. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (drawing == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (header == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        drawing->header = (struct DxfHeader *) header;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (drawing);
}


/*!
 * \brief Get the first entry to the Classes list from a libDXF drawing.
 *
 * \return \c class_list when sucessful, \c NULL when an error occurred.
 */
DxfClass *
dxf_drawing_get_class_list
(
        DxfDrawing *drawing
                /*!< a pointer to a libDXF drawing. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfClass *result = NULL;

        /* Do some basic checks. */
        if (drawing == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (drawing->class_list ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = (DxfClass *) drawing->class_list;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the first entry to the Classes list for a libDXF drawing.
 *
 * \return a pointer to the libDXF drawing when OK, \c NULL when an
 * error occurred.
 */
DxfDrawing *
dxf_drawing_set_class_list
(
        DxfDrawing *drawing,
                /*!< a pointer to a libDXF drawing. */
        DxfClass *class_list
                /*!< a pointer containing the first entry to the Classes
                 * list for the libDXF drawing. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (drawing == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (class_list == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        drawing->class_list = (struct DxfClass *) class_list;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (drawing);
}


/*!
 * \brief Get the first entry to the Tables list from a libDXF drawing.
 *
 * \return \c tables_list when sucessful, \c NULL when an error occurred.
 */
DxfTables *
dxf_drawing_get_tables_list
(
        DxfDrawing *drawing
                /*!< a pointer to a libDXF drawing. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfTables *result = NULL;

        /* Do some basic checks. */
        if (drawing == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (drawing->tables_list ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = (DxfTables *) drawing->tables_list;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the first entry to the Tables list for a libDXF drawing.
 *
 * \return a pointer to the libDXF drawing when OK, \c NULL when an
 * error occurred.
 */
DxfDrawing *
dxf_drawing_set_tables_list
(
        DxfDrawing *drawing,
                /*!< a pointer to a libDXF drawing. */
        DxfTables *tables_list
                /*!< a pointer containing the first entry to the Tables
                 * list for the libDXF drawing. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (drawing == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (tables_list == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        drawing->tables_list = (struct DxfTables *) tables_list;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (drawing);
}


/*!
 * \brief Get the first entry to the Block list from a libDXF drawing.
 *
 * \return \c block_list when sucessful, \c NULL when an error occurred.
 */
DxfBlock *
dxf_drawing_get_block_list
(
        DxfDrawing *drawing
                /*!< a pointer to a libDXF drawing. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfBlock *result = NULL;

        /* Do some basic checks. */
        if (drawing == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (drawing->block_list ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = (DxfBlock *) drawing->block_list;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the first entry to the Block list for a libDXF drawing.
 *
 * \return a pointer to the libDXF drawing when OK, \c NULL when an
 * error occurred.
 */
DxfDrawing *
dxf_drawing_set_block_list
(
        DxfDrawing *drawing,
                /*!< a pointer to a libDXF drawing. */
        DxfBlock *block_list
                /*!< a pointer containing the first entry to the Block
                 * list for the libDXF drawing. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (drawing == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (block_list == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        drawing->block_list = (struct DxfBlock *) block_list;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (drawing);
}


/*!
 * \brief Get the first entry to the Entities list from a libDXF drawing.
 *
 * \return \c entities_list when sucessful, \c NULL when an error
 * occurred.
 */
DxfEntities *
dxf_drawing_get_entities_list
(
        DxfDrawing *drawing
                /*!< a pointer to a libDXF drawing. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfEntities *result = NULL;

        /* Do some basic checks. */
        if (drawing == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (drawing->entities_list ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = (DxfEntities *) drawing->entities_list;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the first entry to the Entities list for a libDXF drawing.
 *
 * \return a pointer to the libDXF drawing when OK, \c NULL when an
 * error occurred.
 */
DxfDrawing *
dxf_drawing_set_entities_list
(
        DxfDrawing *drawing,
                /*!< a pointer to a libDXF drawing. */
        DxfEntities *entities_list
                /*!< a pointer containing the first entry to the
                 * Entities list for the libDXF drawing. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (drawing == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (entities_list == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        drawing->entities_list = (struct DxfEntities *) entities_list;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (drawing);
}


/*!
 * \brief Get the first entry to the Object list from a libDXF drawing.
 *
 * \return \c object_list when sucessful, \c NULL when an error
 * occurred.
 */
DxfObject *
dxf_drawing_get_object_list
(
        DxfDrawing *drawing
                /*!< a pointer to a libDXF drawing. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfObject *result = NULL;

        /* Do some basic checks. */
        if (drawing == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (drawing->object_list ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = (DxfObject *) drawing->object_list;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the first entry to the Object list for a libDXF drawing.
 *
 * \return a pointer to the libDXF drawing when OK, \c NULL when an
 * error occurred.
 */
DxfDrawing *
dxf_drawing_set_object_list
(
        DxfDrawing *drawing,
                /*!< a pointer to a libDXF drawing. */
        DxfObject *object_list
                /*!< a pointer containing the first entry to the
                 * Object list for the libDXF drawing. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (drawing == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (object_list == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        drawing->object_list = (struct DxfObject *) object_list;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (drawing);
}


/*!
 * \brief Get the thumbnail from a libDXF drawing.
 *
 * \return \c thumbnail when sucessful, \c NULL when an error occurred.
 */
DxfThumbnail *
dxf_drawing_get_thumbnail
(
        DxfDrawing *drawing
                /*!< a pointer to a libDXF drawing. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfThumbnail *result = NULL;

        /* Do some basic checks. */
        if (drawing == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (drawing->thumbnail ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = (DxfThumbnail *) drawing->thumbnail;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the thumbnail for a libDXF drawing.
 *
 * \return a pointer to the libDXF drawing when OK, \c NULL when an
 * error occurred.
 */
DxfDrawing *
dxf_drawing_set_thumbnail
(
        DxfDrawing *drawing,
                /*!< a pointer to a libDXF drawing. */
        DxfThumbnail *thumbnail
                /*!< a pointer containing the thumbnail for the libDXF
                 * drawing. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (drawing == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (thumbnail == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        drawing->thumbnail = (struct DxfThumbnail *) thumbnail;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (drawing);
}


/*!
 * \brief Get the pointer to the next \c DRAWING from a DXF 
 * \c DRAWING.
 *
 * \return pointer to the next \c DRAWING.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfDrawing *
dxf_drawing_get_next
(
        DxfDrawing *drawing
                /*!< a pointer to a DXF \c DRAWING. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (drawing == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (drawing->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfDrawing *) drawing->next);
}


/*!
 * \brief Set the pointer to the next libDXF \c DRAWING for a \c DRAWING.
 *
 * \return a pointer to \c drawing when successful, or \c NULL when an
 * error occurred.
 */
DxfDrawing *
dxf_drawing_set_next
(
        DxfDrawing *drawing,
                /*!< a pointer to a libDXF \c DRAWING. */
        DxfDrawing *next
                /*!< a pointer to the next \c DRAWING. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (drawing == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        drawing->next = (struct DxfDrawing *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (drawing);
}


/*!
 * \brief Get the pointer to the last \c DRAWING from a linked
 * list of libDXF \c DRAWINGs.
 *
 * \return pointer to the last \c DRAWING.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfDrawing *
dxf_drawing_get_last
(
        DxfDrawing *drawing
                /*!< a pointer to a libDXF \c DRAWING. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (drawing == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (drawing->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfDrawing *) drawing);
        }
        DxfDrawing *iter = (DxfDrawing *) drawing->next;
        while (iter->next != NULL)
        {
                iter = (DxfDrawing *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfDrawing *) iter);
}


/* EOF*/
