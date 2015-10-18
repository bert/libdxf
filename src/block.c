/*!
 * \file block.c
 *
 * \author Copyright (C) 2008 ... 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF block entity (\c BLOCK).
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
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
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
                  (_("Error in %s () could not allocate memory for a DxfBlock struct.\n")),
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
 * allocated memory when succesful.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
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
                  (_("Error in %s () could not allocate memory for a DxfBlock struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        block->xref_name = strdup ("");
        block->block_name = strdup ("");
        block->block_name_additional = strdup ("");
        block->id_code = 0;
        block->description = strdup ("");
        block->layer = strdup (DXF_DEFAULT_LAYER);
        block->x0 = 0.0;
        block->y0 = 0.0;
        block->z0 = 0.0;
        block->block_type = 0; /* 0 = invalid type */
        block->dictionary_owner_soft = strdup ("");
        block->endblk = (struct DxfEndblk *) dxf_endblk_new ();
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
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
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
                block = dxf_block_new ();
                block = dxf_block_init (block);
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
                        fscanf (fp->fp, "%s\n", block->xref_name);
                }
                else if (strcmp (temp_string, "2") == 0)
                {
                        /* Now follows a string containing a block name. */
                        fscanf (fp->fp, "%s\n", block->block_name);
                }
                else if (strcmp (temp_string, "3") == 0)
                {
                        /* Now follows a string containing a block name. */
                        fscanf (fp->fp, "%s\n", block->block_name_additional);
                }
                else if (strcmp (temp_string, "4") == 0)
                {
                        /* Now follows a string containing a description. */
                        fscanf (fp->fp, "%s\n", block->description);
                }
                else if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        fscanf (fp->fp, "%x\n", &block->id_code);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        fscanf (fp->fp, "%s\n", block->layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the center point. */
                        fscanf (fp->fp, "%lf\n", &block->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the center point. */
                        fscanf (fp->fp, "%lf\n", &block->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the center point. */
                        fscanf (fp->fp, "%lf\n", &block->z0);
                }
                else if ((fp->acad_version_number <= AutoCAD_11)
                        && (strcmp (temp_string, "38") == 0)
                        && (block->z0 = 0.0))
                {
                        /* Elevation is a pre AutoCAD R11 variable
                         * so additional testing for the version should
                         * probably be added.
                         * Now follows a string containing the
                         * elevation. */
                        fscanf (fp->fp, "%lf\n", &block->z0);
                }
                else if (strcmp (temp_string, "70") == 0)
                {
                        /* Now follows a string containing the block
                         * type value. */
                        fscanf (fp->fp, "%d\n", &block->block_type);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        fscanf (fp->fp, "%s\n", temp_string);
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
                        fscanf (fp->fp, "%s\n", block->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "999") == 0)
                {
                        /* Now follows a string containing a comment. */
                        fscanf (fp->fp, "%s\n", temp_string);
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
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
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
        if (((block->xref_name == NULL)
          || (strcmp (block->xref_name, "") == 0))
          && ((block->block_type != 4)
          || (block->block_type != 32)))
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
        if (block->dictionary_owner_soft == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () NULL pointer to soft owner object string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, block->id_code);
                block->dictionary_owner_soft = strdup ("");
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
        if ((strcmp (block->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "330\n%s\n", block->dictionary_owner_soft);
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
        fprintf (fp->fp, " 70\n%d\n", block->block_type);
        fprintf (fp->fp, " 10\n%f\n", block->x0);
        fprintf (fp->fp, " 20\n%f\n", block->y0);
        fprintf (fp->fp, " 30\n%f\n", block->z0);
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "  3\n%s\n", block->block_name);
        }
        if ((fp->acad_version_number >= AutoCAD_13)
        && ((block->block_type && 4)
        || (block->block_type && 32)))
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
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
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
        if (block->next != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to next DxfBlock was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (block->xref_name);
        free (block->block_name);
        free (block->block_name_additional);
        free (block->description);
        free (block->layer);
        free (block->dictionary_owner_soft);
        free (block);
        block = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a chain of DXF \c BLOCK
 * entities and all their data fields.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
void
dxf_block_free_chain
(
        DxfBlock *blocks
                /*!< pointer to the chain of DXF \c BLOCK entities. */
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
                struct DxfBlock *iter = blocks->next;
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
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
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
        char *result;

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
                  (_("Error in %s () a NULL pointer was found in the xref_name member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = strdup (block->xref_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the xref name for a DXF \c BLOCK entity.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
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
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
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
        char *result;

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
                  (_("Error in %s () a NULL pointer was found in the block_name member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = strdup (block->block_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the block name for a DXF \c BLOCK entity.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
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
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
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
        char *result;

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
                  (_("Error in %s () a NULL pointer was found in the block_name_additional member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = strdup (block->block_name_additional);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the additional block name for a DXF \c BLOCK entity.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
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
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
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
        char *result;

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
                  (_("Error in %s () a NULL pointer was found in the description member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = strdup (block->description);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the description for a DXF \c BLOCK entity.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
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
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
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
        int result;

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
                  (_("Error in %s () a negative value was found in the id-code member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = block->id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the ID code for a DXF \c BLOCK entity.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
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
                  (_("Error in %s () a negative id-code value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
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
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
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
        char *result = NULL;

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
                  (_("Error in %s () a NULL pointer was found in the layer member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = strdup (block->layer);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the layer for a DXF \c BLOCK entity.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
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
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfPoint *
dxf_block_get_base_point
(
        DxfBlock *block,
                /*!< a pointer to a DXF \c BLOCK entity. */
        int id_code,
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file. */
        int inheritance
                /*!< Inherit layer, linetype, color and other relevant
                 * properties from either:
                 * <ol>
                 * <li value = "0"> Default (as initialised).</li>
                 * <li value = "1"> \c BLOCK.</li>
                 * </ol>
                 */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfPoint *p1 = NULL;

        /* Do some basic checks. */
        if (block == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        p1 = dxf_point_init (p1);
        if (p1 == NULL)
        {
              fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfPoint struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        if (id_code < 0)
        {
              fprintf (stderr,
                  (_("Warning in %s () passed id_code is smaller than 0.\n")),
                __FUNCTION__);
        }
        p1->id_code = id_code;
        p1->x0 = block->x0;
        p1->y0 = block->y0;
        p1->z0 = block->z0;
        switch (inheritance)
        {
                case 0:
                        /* Do nothing. */
                        break;
                case 1:
                        if (block->layer != NULL)
                        {
                                p1->layer = strdup (block->layer);
                        }
                        if (block->dictionary_owner_soft != NULL)
                        {
                                p1->dictionary_owner_soft = strdup (block->dictionary_owner_soft);
                        }
                        break;
                default:
                        fprintf (stderr,
                          (_("Warning in %s (): unknown inheritance option passed.\n")),
                          __FUNCTION__);
                        fprintf (stderr,
                          (_("\tResolving to default.\n")));
                        break;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (p1);
}


/*!
 * \brief Test if this block is anonymous.
 *
 * \return \c TRUE when this block is anonymous,
 * or \c FALSE when this block is not anonymous.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
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
        int result = FALSE;

        /* Do some basic checks. */
        if (block == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = DXF_CHECK_BIT (block->block_type, 0);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Test if this block has attributes.
 *
 * \return \c TRUE when this block has attributes,
 * or \c FALSE when this block has no attributes.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
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
        int result = FALSE;

        /* Do some basic checks. */
        if (block == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = DXF_CHECK_BIT (block->block_type, 1);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Test if this DXF \c BLOCK is an external refence (Xref).
 *
 * \return \c TRUE when \c BLOCK is an external refence,
 * or \c FALSE when \c BLOCK is not an external refence.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
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
        int result = FALSE;

        /* Do some basic checks. */
        if (block == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = DXF_CHECK_BIT (block->block_type, 2);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Test if this DXF \c BLOCK is externally dependent on an xref.
 *
 * \return \c TRUE when \c BLOCK is externally dependent on an xref,
 * or \c FALSE when \c BLOCK is not externally dependent on an xref.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
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
        int result = FALSE;

        /* Do some basic checks. */
        if (block == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = DXF_CHECK_BIT (block->block_type, 4);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Test if this DXF \c BLOCK is a resolved external reference, or
 * dependent of an external reference.
 *
 * \return \c TRUE when \c BLOCK is a resolved xref,
 * or \c FALSE when \c BLOCK is not a resolved xref.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
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
        int result = FALSE;

        /* Do some basic checks. */
        if (block == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = DXF_CHECK_BIT (block->block_type, 5);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Test if this DXF \c BLOCK is referenced.
 *
 * \return \c TRUE when \c BLOCK is referenced,
 * or \c FALSE when \c BLOCK is not referenced.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
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
        int result = FALSE;

        /* Do some basic checks. */
        if (block == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = DXF_CHECK_BIT (block->block_type, 6);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/* EOF */
