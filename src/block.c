/*!
 * \file block.c
 *
 * \author Copyright (C) 2008, 2009, 2010, 2012, 2014, 2015, 2016, 2017,
 * 2018, 2019, 2020, 2021 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \author Copyright (C) 2010 by Luis Matos <gass@otiliamatos.ath.cx>.
 *
 * \brief Functions for a DXF block entity (\c BLOCK).
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
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


#include "block.h"


/*!
 * \brief Allocate memory for a \c DxfBlock
 * (a DXF \c BLOCK entity).
 *
 * Fill the memory contents with zeros.
 */
DxfBlock *
dxf_block_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfBlock *block = NULL;
        size_t size;

        size = sizeof (DxfBlock);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((block = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                block = NULL;
        }
        else
        {
                memset (block, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (block);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c DxfBlock
 * (a DXF \c BLOCK entity).
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfBlock *
dxf_block_init
(
        DxfBlock *block
                /*!< DXF block entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (block == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                block = dxf_block_new ();
        }
        if (block == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        /* Assign initial values to members. */
        block->xref_name = strdup ("");
        block->block_name = strdup ("");
        block->block_name_additional = strdup ("");
        block->description = strdup ("");
        block->id_code = 0;
        block->layer = strdup (DXF_DEFAULT_LAYER);
        block->p0->x0 = 0.0;
        block->p0->y0 = 0.0;
        block->p0->z0 = 0.0;
        block->block_type = 0; /* 0 = invalid type */
        block->extr_x0 = 0.0;
        block->extr_y0 = 0.0;
        block->extr_z0 = 0.0;
        block->object_owner_soft = strdup ("");
        block->endblk = (struct DxfEndblk *) dxf_endblk_new ();
        /* Initialize new structs for the following members later,
         * when they are required and when we have content. */
        block->p0 = NULL;
        block->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (block);
}


/*!
 * \brief Read data from a DXF file into a \c DxfBlock
 * (a DXF \c BLOCK entity).
 *
 * The last line read from file contained the string "BLOCK". \n
 * Now follows some data for the \c BLOCK, to be terminated with a "  0"
 * string announcing the following entity, or the end of the \c ENTITY
 * section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c dxf_block. \n
 *
 * \return a pointer to \c block.
 *
 * \todo After reading information from the \c BLOCK entity up until the
 * closing Group code 0, the pointer to the following \c ENDBLK entity
 * needs to be stored in the current (last) \c DxfBlock struct member
 * \c endblk.
 */
DxfBlock *
dxf_block_read
(
        DxfFile *fp,
                /*!< DXF file handle of input file (or device). */
        DxfBlock *block
                /*!< DXF block entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *temp_string = NULL;

        /* Do some basic checks. */
        if (fp == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL file pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (temp_string);
                return (NULL);
        }
        if (block == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                block = dxf_block_init (block);
        }
        if (block->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                block->p0 = dxf_point_init (block->p0);
                if (block->p0 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        if (block->endblk == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfEndblk.\n")));
                block->endblk = (DxfEndblk *) dxf_endblk_init ((DxfEndblk *) block->endblk);
                if (block->endblk == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        fscanf (fp->fp, "%[^\n]", temp_string);
        while (strcmp (temp_string, "0") != 0)
        {
                if (ferror (fp->fp))
                {
                        fprintf (stderr,
                          (_("Error in %s () while reading from: %s in line: %d.\n")),
                          __FUNCTION__, fp->filename, fp->line_number);
                        fclose (fp->fp);
                        /* Clean up. */
                        free (temp_string);
                        return (NULL);
                }
                if (strcmp (temp_string, "1") == 0)
                {
                        /* Now follows a string containing a external
                         * reference name. */
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, block->xref_name);
                }
                else if (strcmp (temp_string, "2") == 0)
                {
                        /* Now follows a string containing a block name. */
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, block->block_name);
                }
                else if (strcmp (temp_string, "3") == 0)
                {
                        /* Now follows a string containing a block name. */
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, block->block_name_additional);
                }
                else if (strcmp (temp_string, "4") == 0)
                {
                        /* Now follows a string containing a description. */
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, block->description);
                }
                else if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        fscanf (fp->fp, "%x\n", (uint *) &block->id_code);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, block->layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the center point. */
                        fscanf (fp->fp, "%lf\n", &block->p0->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the center point. */
                        fscanf (fp->fp, "%lf\n", &block->p0->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the center point. */
                        fscanf (fp->fp, "%lf\n", &block->p0->z0);
                }
                else if ((fp->acad_version_number <= AutoCAD_11)
                        && (strcmp (temp_string, "38") == 0)
                        && (block->p0->z0 = 0.0))
                {
                        /* Elevation is a pre AutoCAD R11 variable
                         * so additional testing for the version should
                         * probably be added.
                         * Now follows a string containing the
                         * elevation. */
                        fscanf (fp->fp, "%lf\n", &block->p0->z0);
                }
                else if (strcmp (temp_string, "70") == 0)
                {
                        /* Now follows a string containing the block
                         * type value. */
                        fscanf (fp->fp, "%hd\n", &block->block_type);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if ((strcmp (temp_string, "AcDbEntity") != 0)
                        && ((strcmp (temp_string, "AcDbBlockBegin") != 0)))
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () found a bad subclass marker in: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                        }
                }
                else if (strcmp (temp_string, "210") == 0)
                {
                        /* Now follows a string containing the
                         * X-value of the extrusion vector. */
                        fscanf (fp->fp, "%lf\n", &block->extr_x0);
                }
                else if (strcmp (temp_string, "220") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the extrusion vector. */
                        fscanf (fp->fp, "%lf\n", &block->extr_y0);
                }
                else if (strcmp (temp_string, "230") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the extrusion vector. */
                        fscanf (fp->fp, "%lf\n", &block->extr_z0);
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing Soft-pointer
                         * ID/handle to owner object. */
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, block->object_owner_soft);
                }
                else if (strcmp (temp_string, "999") == 0)
                {
                        /* Now follows a string containing a comment. */
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        fprintf (stdout, "DXF comment: %s\n", temp_string);
                }
                else
                {
                        fprintf (stderr,
                          (_("Warning in %s () unknown string tag found while reading from: %s in line: %d.\n")),
                          __FUNCTION__, fp->filename, fp->line_number);
                }
        }
        /* Handle omitted members and/or illegal values. */
        /*!
         * \todo Resolve this quick hack for preventing an empty block
         * name string in a more elegant manner.
         */
        if (strcmp (block->block_name, "") == 0)
        {
                sprintf (block->block_name, "%i", block->id_code);
        }
        if (strcmp (block->layer, "") == 0)
        {
                block->layer = strdup (DXF_DEFAULT_LAYER);
        }
        if (block->block_type == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () illegal block type value found while reading from: %s in line: %d.\n")),
                  __FUNCTION__, fp->filename, fp->line_number);
                fprintf (stderr,
                  (_("\tblock type value is reset to 1.\n")));
                block->block_type = 1;
        }
        /* Clean up. */
        free (temp_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (block);
}


/*!
 * \brief Write DXF output for a DXF \c BLOCK entity.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_block_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfBlock *block
                /*!< DXF block entity */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("BLOCK");
        DxfEndblk *endblk = NULL;

        /* Do some basic checks. */
        if (fp == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL file pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (block == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (block->block_name == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () empty block name string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, block->id_code);
                fprintf (stderr,
                  (_("\t%s entity is discarded from output.\n")),
                  dxf_entity_name);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (block->endblk == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () NULL pointer to endblk was passed or the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, block->id_code);
                fprintf (stderr,
                  (_("\t%s entity is discarded from output.\n")),
                  dxf_entity_name);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if ((block->block_type == 4) || (block->block_type == 32))
        {
                if ((block->xref_name == NULL) || (strcmp (block->xref_name, "") == 0))
                {
                        fprintf (stderr,
                          (_("Error in %s () empty xref path name string for the %s entity with id-code: %x\n")),
                          __FUNCTION__, dxf_entity_name, block->id_code);
                        fprintf (stderr,
                          (_("\t%s entity is discarded from output.\n")),
                          dxf_entity_name);
                        /* Clean up. */
                        free (dxf_entity_name);
                        return (EXIT_FAILURE);
                }
        }
        if (block->description == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () NULL pointer to description string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, block->id_code);
                block->description = strdup ("");
        }
        if (strcmp (block->layer, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, block->id_code);
                fprintf (stderr,
                  (_("\t%s entity is relocated to layer 0.\n")),
                  dxf_entity_name);
                block->layer = strdup (DXF_DEFAULT_LAYER);
        }
        if (block->object_owner_soft == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () NULL pointer to soft owner object string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, block->id_code);
                block->object_owner_soft = strdup ("");
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if ((fp->acad_version_number >= AutoCAD_13)
          && (block->id_code != -1))
        {
                fprintf (fp->fp, "  5\n%x\n", block->id_code);
        }
        /*!
         * \todo for version R14.\n
         * Implementing the start of application-defined group
         * "{application_name", with Group code 102.\n
         * For example: "{ACAD_REACTORS" indicates the start of the
         * AutoCAD persistent reactors group.\n\n
         * application-defined codes: Group codes and values within the
         * 102 groups are application defined (optional).\n\n
         * End of group, "}" (optional), with Group code 102.
         */
        if ((strcmp (block->object_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "330\n%s\n", block->object_owner_soft);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
        }
        fprintf (fp->fp, "  8\n%s\n", block->layer);
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbBlockBegin\n");
        }
        fprintf (fp->fp, "  2\n%s\n", block->block_name);
        fprintf (fp->fp, " 70\n%hd\n", block->block_type);
        fprintf (fp->fp, " 10\n%f\n", block->p0->x0);
        fprintf (fp->fp, " 20\n%f\n", block->p0->y0);
        fprintf (fp->fp, " 30\n%f\n", block->p0->z0);
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "  3\n%s\n", block->block_name);
        }
        if ((fp->acad_version_number >= AutoCAD_13)
        && ((block->block_type & 4)
        || (block->block_type & 32)))
        {
                fprintf (fp->fp, "  1\n%s\n", block->xref_name);
        }
        if ((fp->acad_version_number >= AutoCAD_2000)
        && (strcmp (block->description, "") != 0))
        {
                fprintf (fp->fp, "  4\n%s\n", block->description);
        }
        endblk = (DxfEndblk *) block->endblk;
        dxf_endblk_write (fp, endblk);
        /* Clean up. */
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write DXF output to a file for a list of block definitions.
 *
 * Appears only in the \c BLOCKS section.\n
 */
int
dxf_block_write_table
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfBlock *blocks_list
                /*!< Pointer to a list of block definitions. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (fp == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL file pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }

        /*! \todo Add code here. */
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DxfBlock (a \c BLOCK entity)
 * and all it's data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_block_free
(
        DxfBlock *block
                /*!< Pointer to the memory occupied by the DXF \c BLOCK
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (block == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (block->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (block->xref_name);
        free (block->block_name);
        free (block->block_name_additional);
        free (block->description);
        free (block->layer);
        free (block->object_owner_soft);
        free (block);
        block = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c BLOCK entities and all their data fields.
 */
void
dxf_block_free_list
(
        DxfBlock *blocks
                /*!< pointer to the single linked list of DXF \c BLOCK
                 * entities. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (blocks == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (blocks != NULL)
        {
                DxfBlock *iter = (DxfBlock *) blocks->next;
                dxf_block_free (blocks);
                blocks = (DxfBlock *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the xref name from a DXF \c BLOCK entity.
 *
 * \return xref name.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_block_get_xref_name
(
        DxfBlock *block
                /*!< a pointer to a DXF \c BLOCK entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (block == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (block->xref_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (block->xref_name));
}


/*!
 * \brief Set the xref name for a DXF \c BLOCK entity.
 */
DxfBlock *
dxf_block_set_xref_name
(
        DxfBlock *block,
                /*!< a pointer to a DXF \c BLOCK entity. */
        char *xref_name
                /*!< a string containing the xref name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (block == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (xref_name == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        block->xref_name = strdup (xref_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (block);
}


/*!
 * \brief Get the block name from a DXF \c BLOCK entity.
 *
 * \return block name.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_block_get_block_name
(
        DxfBlock *block
                /*!< a pointer to a DXF \c BLOCK entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (block == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (block->block_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (block->block_name));
}


/*!
 * \brief Set the block name for a DXF \c BLOCK entity.
 */
DxfBlock *
dxf_block_set_block_name
(
        DxfBlock *block,
                /*!< a pointer to a DXF \c BLOCK entity. */
        char *block_name
                /*!< a string containing the block name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (block == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (block_name == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        block->block_name = strdup (block_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (block);
}


/*!
 * \brief Get the additional block name from a DXF \c BLOCK entity.
 *
 * \return additional block name.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_block_get_block_name_additional
(
        DxfBlock *block
                /*!< a pointer to a DXF \c BLOCK entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (block == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (block->block_name_additional ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (block->block_name_additional));
}


/*!
 * \brief Set the additional block name for a DXF \c BLOCK entity.
 */
DxfBlock *
dxf_block_set_block_name_additional
(
        DxfBlock *block,
                /*!< a pointer to a DXF \c BLOCK entity. */
        char *block_name_additional
                /*!< a string containing the additional block name for
                 * the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (block == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (block_name_additional == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        block->block_name_additional = strdup (block_name_additional);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (block);
}


/*!
 * \brief Get the description from a DXF \c BLOCK entity.
 *
 * \return description.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_block_get_description
(
        DxfBlock *block
                /*!< a pointer to a DXF \c BLOCK entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (block == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (block->description ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (block->description));
}


/*!
 * \brief Set the description for a DXF \c BLOCK entity.
 */
DxfBlock *
dxf_block_set_description
(
        DxfBlock *block,
                /*!< a pointer to a DXF \c BLOCK entity. */
        char *description
                /*!< a string containing the description for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (block == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (description == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        block->description = strdup (description);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (block);
}


/*!
 * \brief Get the ID code from a DXF \c BLOCK entity.
 *
 * \return ID code.
 */
int
dxf_block_get_id_code
(
        DxfBlock *block
                /*!< a pointer to a DXF \c BLOCK entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (block == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (block->id_code < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (block->id_code);
}


/*!
 * \brief Set the ID code for a DXF \c BLOCK entity.
 */
DxfBlock *
dxf_block_set_id_code
(
        DxfBlock *block,
                /*!< a pointer to a DXF \c BLOCK entity. */
        int id_code
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (block == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (id_code < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        block->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (block);
}


/*!
 * \brief Get the layer from a DXF \c BLOCK entity.
 *
 * \return layer when sucessful, \c NULL when an error occurred.
 */
char *
dxf_block_get_layer
(
        DxfBlock *block
                /*!< a pointer to a DXF \c BLOCK entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (block == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (block->layer ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (block->layer));
}


/*!
 * \brief Set the layer for a DXF \c BLOCK entity.
 */
DxfBlock *
dxf_block_set_layer
(
        DxfBlock *block,
                /*!< a pointer to a DXF \c BLOCK entity. */
        char *layer
                /*!< a string containing the layer for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (block == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (layer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        block->layer = strdup (layer);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (block);
}


/*!
 * \brief Get the base point of a DXF \c BLOCK entity.
 *
 * \return the base point.
 */
DxfPoint *
dxf_block_get_p0
(
        DxfBlock *block
                /*!< a pointer to a DXF \c BLOCK entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (block == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (block->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (block->p0);
}


/*!
 * \brief Set the base point of a DXF \c BLOCK entity.
 *
 * \return a pointer to a DXF \c BLOCK entity.
 */
DxfBlock *
dxf_block_set_p0
(
        DxfBlock *block,
                /*!< a pointer to a DXF \c BLOCK entity. */
        DxfPoint *p0
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (block == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        block->p0 = p0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (block);
}


/*!
 * \brief Get the X-value of the base point \c x0 of a DXF \c BLOCK
 * entity.
 *
 * \return the X-value of the base point \c x0.
 */
double
dxf_block_get_x0
(
        DxfBlock *block
                /*!< a pointer to a DXF \c BLOCK entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (block == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (block->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (block->p0->x0);
}


/*!
 * \brief Set the X-value of the base point \c x0 of a DXF \c BLOCK
 * entity.
 *
 * \return a pointer to \c block when successful, or \c NULL when an
 * error occurred.
 */
DxfBlock *
dxf_block_set_x0
(
        DxfBlock *block,
                /*!< a pointer to a DXF \c BLOCK entity. */
        double x0
                /*!< the X-value of the base point \c x0 of a DXF
                 * \c ARC entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (block == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (block->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                block->p0 = dxf_point_init (block->p0);
                if (block->p0 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        block->p0->x0 = x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (block);
}


/*!
 * \brief Get the Y-value of the base point \c y0 of a DXF \c BLOCK
 * entity.
 *
 * \return the Y-value of the base point \c y0.
 */
double
dxf_block_get_y0
(
        DxfBlock *block
                /*!< a pointer to a DXF \c BLOCK entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (block == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (block->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (block->p0->y0);
}


/*!
 * \brief Set the Y-value of the base point \c y0 of a DXF \c BLOCK
 * entity.
 *
 * \return a pointer to \c block when successful, or \c NULL when an
 * error occurred.
 */
DxfBlock *
dxf_block_set_y0
(
        DxfBlock *block,
                /*!< a pointer to a DXF \c BLOCK entity. */
        double y0
                /*!< the Y-value of the base point \c y0 of a DXF
                 * \c BLOCK entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (block == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (block->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                block->p0 = dxf_point_init (block->p0);
                if (block->p0 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        block->p0->y0 = y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (block);
}


/*!
 * \brief Get the Z-value of the base point \c z0 of a DXF \c BLOCK
 * entity.
 *
 * \return the Z-value of the base point \c z0.
 */
double
dxf_block_get_z0
(
        DxfBlock *block
                /*!< a pointer to a DXF \c BLOCK entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (block == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (block->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (block->p0->z0);
}


/*!
 * \brief Set the Z-value of the base point \c z0 of a DXF \c BLOCK
 * entity.
 *
 * \return a pointer to \c block when successful, or \c NULL when an
 * error occurred.
 */
DxfBlock *
dxf_block_set_z0
(
        DxfBlock *block,
                /*!< a pointer to a DXF \c BLOCK entity. */
        double z0
                /*!< the Z-value of the base point \c z0 of a DXF
                 * \c BLOCK entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (block == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (block->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfPoint.\n")));
                block->p0 = dxf_point_init (block->p0);
                if (block->p0 == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        block->p0->z0 = z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (block);
}


/*!
 * \brief Get the \c block_type from a DXF \c BLOCK entity.
 *
 * \return block type.
 */
int16_t
dxf_block_get_block_type
(
        DxfBlock *block
                /*!< a pointer to a DXF \c BLOCK entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (block == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (block->block_type < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (block->block_type);
}


/*!
 * \brief Set the \c block_type for a DXF \c BLOCK entity.
 */
DxfBlock *
dxf_block_set_block_type
(
        DxfBlock *block,
                /*!< a pointer to a DXF \c BLOCK entity. */
        int16_t block_type
                /*!< block type for the entity.\n */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (block == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (block_type < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        block->block_type = block_type;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (block);
}


/*!
 * \brief Test if this block is anonymous.
 *
 * \return \c TRUE when this block is anonymous,
 * or \c FALSE when this block is not anonymous.
 */
int
dxf_block_is_anonymous
(
        DxfBlock *block
                /*!< DXF \c BLOCK entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (block == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (DXF_CHECK_BIT (block->block_type, 0));
}


/*!
 * \brief Test if this block has attributes.
 *
 * \return \c TRUE when this block has attributes,
 * or \c FALSE when this block has no attributes.
 */
int
dxf_block_has_attributes
(
        DxfBlock *block
                /*!< DXF \c BLOCK entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (block == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (DXF_CHECK_BIT (block->block_type, 1));
}


/*!
 * \brief Test if this DXF \c BLOCK is an external refence (Xref).
 *
 * \return \c TRUE when \c BLOCK is an external refence,
 * or \c FALSE when \c BLOCK is not an external refence.
 */
int
dxf_block_is_xreferenced
(
        DxfBlock *block
                /*!< DXF \c BLOCK entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (block == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (DXF_CHECK_BIT (block->block_type, 2));
}


/*!
 * \brief Test if this DXF \c BLOCK is externally dependent on an xref.
 *
 * \return \c TRUE when \c BLOCK is externally dependent on an xref,
 * or \c FALSE when \c BLOCK is not externally dependent on an xref.
 */
int
dxf_block_is_xdependent
(
        DxfBlock *block
                /*!< DXF \c BLOCK entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (block == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (DXF_CHECK_BIT (block->block_type, 4));
}


/*!
 * \brief Test if this DXF \c BLOCK is a resolved external reference, or
 * dependent of an external reference.
 *
 * \return \c TRUE when \c BLOCK is a resolved xref,
 * or \c FALSE when \c BLOCK is not a resolved xref.
 */
int
dxf_block_is_xresolved
(
        DxfBlock *block
                /*!< DXF \c BLOCK entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (block == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (DXF_CHECK_BIT (block->block_type, 5));
}


/*!
 * \brief Test if this DXF \c BLOCK is referenced.
 *
 * \return \c TRUE when \c BLOCK is referenced,
 * or \c FALSE when \c BLOCK is not referenced.
 */
int
dxf_block_is_referenced
(
        DxfBlock *block
                /*!< DXF \c BLOCK entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (block == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (DXF_CHECK_BIT (block->block_type, 6));
}


/*!
 * \brief Get the X-value of the extrusion vector \c extr_x0 of a DXF
 * \c BLOCK entity.
 *
 * \return the X-value of the extrusion vector \c extr_x0.
 */
double
dxf_block_get_extr_x0
(
        DxfBlock *block
                /*!< a pointer to a DXF \c BLOCK entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (block == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (block->extr_x0);
}


/*!
 * \brief Set the X-value of the extrusion vector \c extr_x0 of a DXF
 * \c BLOCK entity.
 *
 * \return a pointer to \c block when successful, or \c NULL when an
 * error occurred.
 */
DxfBlock *
dxf_block_set_extr_x0
(
        DxfBlock *block,
                /*!< a pointer to a DXF \c BLOCK entity. */
        double extr_x0
                /*!< the X-value of the extrusion vector \c extr_x0 of a
                 * DXF \c BLOCK entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (block == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        block->extr_x0 = extr_x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (block);
}


/*!
 * \brief Get the Y-value of the extrusion vector \c extr_y0 of a DXF
 * \c BLOCK entity.
 *
 * \return the Y-value of the extrusion vector \c extr_y0.
 */
double
dxf_block_get_extr_y0
(
        DxfBlock *block
                /*!< a pointer to a DXF \c BLOCK entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (block == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (block->extr_y0);
}


/*!
 * \brief Set the Y-value of the extrusion vector \c extr_y0 of a DXF
 * \c BLOCK entity.
 *
 * \return a pointer to \c block when successful, or \c NULL when an
 * error occurred.
 */
DxfBlock *
dxf_block_set_extr_y0
(
        DxfBlock *block,
                /*!< a pointer to a DXF \c BLOCK entity. */
        double extr_y0
                /*!< the Y-value of the extrusion vector \c extr_y0 of a
                 * DXF \c BLOCK entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (block == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        block->extr_y0 = extr_y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (block);
}


/*!
 * \brief Get the Z-value of the extrusion vector \c extr_z0 of a DXF
 * \c BLOCK entity.
 *
 * \return the Z-value of the extrusion vector \c extr_z0.
 */
double
dxf_block_get_extr_z0
(
        DxfBlock *block
                /*!< a pointer to a DXF \c BLOCK entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (block == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (block->extr_z0);
}


/*!
 * \brief Set the Z-value of the extrusion vector \c extr_z0 of a DXF
 * \c BLOCK entity.
 *
 * \return a pointer to \c block when successful, or \c NULL when an
 * error occurred.
 */
DxfBlock *
dxf_block_set_extr_z0
(
        DxfBlock *block,
                /*!< a pointer to a DXF \c BLOCK entity. */
        double extr_z0
                /*!< the Z-value of the extrusion vector \c extr_z0 of a
                 * DXF \c BLOCK entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (block == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        block->extr_z0 = extr_z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (block);
}


/*!
 * \brief Get the extrusion vector as a DXF \c POINT entity from a DXF
 * \c BLOCK entity.
 *
 * \return a DXF \c POINT containing the extrusion coordinates.
 *
 * \warning No other members are copied into the DXF \c POINT.
 */
DxfPoint *
dxf_block_get_extrusion_vector_as_point
(
        DxfBlock *block
                /*!< a pointer to a DXF \c BLOCK entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfPoint *point = NULL;

        /* Do some basic checks. */
        if (block == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        point = dxf_point_init (point);
        if (point == NULL)
        {
              fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                __FUNCTION__);
              return (NULL);
        }
        point->x0 = block->extr_x0;
        point->y0 = block->extr_y0;
        point->z0 = block->extr_z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (point);
}


/*!
 * \brief Set the extrusion vector for a DXF \c BLOCK entity.
 */
DxfBlock *
dxf_block_set_extrusion_vector
(
        DxfBlock *block,
                /*!< a pointer to a DXF \c BLOCK entity. */
        double extr_x0,
                /*!<  X-value of the extrusion direction. */
        double extr_y0,
                /*!<  Y-value of the extrusion direction. */
        double extr_z0
                /*!<  Z-value of the extrusion direction. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (block == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        block->extr_x0 = extr_x0;
        block->extr_y0 = extr_y0;
        block->extr_z0 = extr_z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (block);
}


/*!
 * \brief Get the soft pointer to the object owner from a DXF 
 * \c BLOCK entity.
 *
 * \return soft pointer to the object owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_block_get_object_owner_soft
(
        DxfBlock *block
                /*!< a pointer to a DXF \c BLOCK entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (block == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (block->object_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (block->object_owner_soft));
}


/*!
 * \brief Set the pointer to the object_owner_soft for a DXF
 * \c BLOCK entity.
 */
DxfBlock *
dxf_block_set_object_owner_soft
(
        DxfBlock *block,
                /*!< a pointer to a DXF \c BLOCK entity. */
        char *object_owner_soft
                /*!< a string containing the pointer to the
                 * object_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (block == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (object_owner_soft == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        block->object_owner_soft = strdup (object_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (block);
}


/*!
 * \brief Get the pointer to the DXF \c ENDBLK (end of block) marker
 * from a DXF \c BLOCK entity.
 *
 * \return pointer to the DXF \c ENDBLK (end of block) marker.
 *
 * \warning No checks are performed on the returned pointer.
 */
struct DxfEndblk *
dxf_block_get_endblk
(
        DxfBlock *block
                /*!< a pointer to a DXF \c BLOCK entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (block == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (block->endblk ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((struct DxfEndblk *) block->endblk);
}


/*!
 * \brief Set the pointer to the DXF \c ENDBLK (end of block) marker for
 * a DXF \c BLOCK entity.
 */
DxfBlock *
dxf_block_set_endblk
(
        DxfBlock *block,
                /*!< a pointer to a DXF \c BLOCK entity. */
        struct DxfEndblk *endblk
                /*!< a pointerto the DXF \c ENDBLK (end of block) marker for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (block == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (endblk == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (block->endblk == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("Initializing a DxfEndblk.\n")));
                block->endblk = (DxfEndblk *) dxf_endblk_init ((DxfEndblk *) block->endblk);
                if (block->endblk == NULL)
                {
                        fprintf (stderr,
                          (_("Error in %s () could not allocate memory.\n")),
                          __FUNCTION__);
                        return (NULL);
                }
        }
        block->endblk = (struct DxfEndblk *) endblk;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (block);
}


/*!
 * \brief Get the pointer to the next DXF \c BLOCK entity from a DXF 
 * \c BLOCK entity.
 *
 * \return pointer to the next DXF \c BLOCK entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfBlock *
dxf_block_get_next
(
        DxfBlock *block
                /*!< a pointer to a DXF \c BLOCK entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (block == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (block->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfBlock *) block->next);
}


/*!
 * \brief Set the pointer to the next DXF \c BLOCK for a DXF \c BLOCK
 * entity.
 */
DxfBlock *
dxf_block_set_next
(
        DxfBlock *block,
                /*!< a pointer to a DXF \c BLOCK entity. */
        DxfBlock *next
                /*!< a pointer to the next DXF \c BLOCK for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (block == NULL)
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
        block->next = (struct DxfBlock *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (block);
}


/*!
 * \brief Get the pointer to the last DXF \c BLOCK entity from a linked
 * list of DXF \c BLOCK entities.
 *
 * \return pointer to the last DXF \c BLOCK entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfBlock *
dxf_block_get_last
(
        DxfBlock *block
                /*!< a pointer to a DXF \c BLOCK entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (block == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (block->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found in the next member.\n")),
                  __FUNCTION__);
                return ((DxfBlock *) block);
        }
        DxfBlock *iter = (DxfBlock *) block->next;
        while (iter->next != NULL)
        {
                iter = (DxfBlock *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfBlock *) iter);
}


/* EOF */
