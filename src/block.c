/*!
 * \file block.c
 *
 * \author Copyright (C) 2008 ... 2012 by Bert Timmerman <bert.timmerman@xs4all.nl>.
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
 */
DxfBlock *
dxf_block_new ()
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_block_new () function.\n",
                __FILE__, __LINE__);
#endif
        DxfBlock *dxf_block = NULL;
        size_t size;

        size = sizeof (DxfBlock);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_block = malloc (size)) == NULL)
        {
                fprintf (stderr, "ERROR in dxf_block_new () could not allocate memory for a DxfBlock struct.\n");
                dxf_block = NULL;
        }
        else
        {
                memset (dxf_block, 0, size);
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_block_new () function.\n",
                __FILE__, __LINE__);
#endif
        return (dxf_block);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c DxfBlock
 * (a DXF \c BLOCK entity).
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfBlock *
dxf_block_init
(
        DxfBlock *dxf_block
                /*!< DXF block entity. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_block_init () function.\n",
                __FILE__, __LINE__);
#endif
        dxf_block = dxf_block_new ();
        if (dxf_block == NULL)
        {
              fprintf (stderr, "ERROR in dxf_block_init () could not allocate memory for a DxfBlock struct.\n");
              return (NULL);
        }
        dxf_block->xref_name = strdup ("");
        dxf_block->block_name = strdup ("");
        dxf_block->id_code = 0;
        dxf_block->description = strdup ("");
        dxf_block->layer = strdup (DXF_DEFAULT_LAYER);
        dxf_block->x0 = 0.0;
        dxf_block->y0 = 0.0;
        dxf_block->z0 = 0.0;
        dxf_block->acad_version_number = 0;
        dxf_block->block_type = 0; /* 0 = invalid type */
        dxf_block->soft_owner_object = strdup ("");
        dxf_block->hard_owner_object = strdup ("");
        dxf_block->next = NULL;
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_block_init () function.\n",
                __FILE__, __LINE__);
#endif
        return (dxf_block);
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
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_block_read
(
        DxfFile *fp,
                /*!< DXF file handle of input file (or device). */
        DxfBlock *dxf_block
                /*!< DXF block entity. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_block_read () function.\n",
                __FILE__, __LINE__);
#endif
        char temp_string[DXF_MAX_STRING_LENGTH];

        if (!dxf_block)
        {
                dxf_block = dxf_block_new ();
        }
        fscanf (fp->fp, "%[^\n]", temp_string);
        while (strcmp (temp_string, "0") != 0)
        {
                if (strcmp (temp_string, "1") == 0)
                {
                        /* Now follows a string containing a external
                         * reference name. */
                        fscanf (fp->fp, "%s\n", dxf_block->xref_name);
                }
                else if (strcmp (temp_string, "2") == 0)
                {
                        /* Now follows a string containing a block name. */
                        fscanf (fp->fp, "%s\n", dxf_block->block_name);
                }
                else if (strcmp (temp_string, "3") == 0)
                {
                        /* Now follows a string containing a block name. */
                        fscanf (fp->fp, "%s\n", dxf_block->block_name);
                }
                else if (strcmp (temp_string, "4") == 0)
                {
                        /* Now follows a string containing a description. */
                        fscanf (fp->fp, "%s\n", dxf_block->description);
                }
                else if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        fscanf (fp->fp, "%x\n", &dxf_block->id_code);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        fscanf (fp->fp, "%s\n", dxf_block->layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the center point. */
                        fscanf (fp->fp, "%lf\n", &dxf_block->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the center point. */
                        fscanf (fp->fp, "%lf\n", &dxf_block->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the center point. */
                        fscanf (fp->fp, "%lf\n", &dxf_block->z0);
                }
                else if ((dxf_block->acad_version_number <= AutoCAD_11)
                        && (strcmp (temp_string, "38") == 0)
                        && (dxf_block->z0 = 0.0))
                {
                        /* Elevation is a pre AutoCAD R11 variable
                         * so additional testing for the version should
                         * probably be added.
                         * Now follows a string containing the
                         * elevation. */
                        fscanf (fp->fp, "%lf\n", &dxf_block->z0);
                }
                else if (strcmp (temp_string, "70") == 0)
                {
                        /* Now follows a string containing the block
                         * type value. */
                        fscanf (fp->fp, "%d\n", &dxf_block->block_type);
                }
                else if ((dxf_block->acad_version_number >= AutoCAD_12)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Subclass markers are post AutoCAD R12
                         * variable so additional testing for the
                         * version should probably be added here.
                         * Now follows a string containing the
                         * subclass marker value. */
                        fscanf (fp->fp, "%s\n", temp_string);
                        if ((strcmp (temp_string, "AcDbEntity") != 0)
                        && ((strcmp (temp_string, "AcDbBlockBegin") != 0)))
                        {
                                fprintf (stderr, "Error in dxf_block_read () found a bad subclass marker in: %s in line: %d.\n",
                                        fp->filename, fp->line_number);
                        }
                }
                else if (strcmp (temp_string, "210") == 0)
                {
                        /* Now follows a string containing the
                         * X-value of the extrusion vector. */
                        fscanf (fp->fp, "%lf\n", &dxf_block->extr_x0);
                }
                else if (strcmp (temp_string, "220") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the extrusion vector. */
                        fscanf (fp->fp, "%lf\n", &dxf_block->extr_y0);
                }
                else if (strcmp (temp_string, "230") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the extrusion vector. */
                        fscanf (fp->fp, "%lf\n", &dxf_block->extr_z0);
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing Soft-pointer
                         * ID/handle to owner object. */
                        fscanf (fp->fp, "%s\n", dxf_block->soft_owner_object);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        fscanf (fp->fp, "%s\n", dxf_block->hard_owner_object);
                }
                else if (strcmp (temp_string, "999") == 0)
                {
                        /* Now follows a string containing a comment. */
                        fscanf (fp->fp, "%s\n", temp_string);
                        fprintf (stdout, "DXF comment: %s\n", temp_string);
                }
                else
                {
                        fprintf (stderr, "Warning: in dxf_block_read () unknown string tag found while reading from: %s in line: %d.\n",
                                fp->filename, fp->line_number);
                }
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_block_read () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write DXF output to a file for a DxfBlock
 * (a DXF \c BLOCK entity).
 */
int
dxf_block_write_lowlevel
(
        FILE *fp,
                /*!< file pointer to output file (or device). */
        int id_code,
                /*!< group code = 5. */
        char *xref_name,
                /*!< group code = 1. */
        char *block_name,
                /*!< group code = 2 and 3. */
        char *description,
                /*!< Block description (optional).\n
                 * Group code = 4. */
        char *layer,
                /*!< group code = 8. */
        double x0,
                /*!< group code = 10\n
                 * base point. */
        double y0,
                /*!< group code = 20\n
                 * base point. */
        double z0,
                /*!< group code = 30\n
                 * base point. */
        int block_type,
                /*!< group code = 70\n
                 * bit codes:\n
                 * 1 = this is an anonymous Block generated by hatching,
                 *     associative dimensioning, other internal operations,
                 *     or an application\n
                 * 2 = this Block has Attributes\n
                 * 4 = this Block is an external reference (Xref)\n
                 * 8 = not used\n
                 * 16 = this Block is externally dependent\n
                 * 32 = this is a resolved external reference, or dependent
                 *      of an external reference\n
                 * 64 = this definition is referenced. */
        double extr_x0,
                /*!< X-value of the extrusion vector.\n
                 * Defaults to 0.0 if ommitted in the DXF file.\n
                 * Group code = 210. */
        double extr_y0,
                /*!< Y-value of the extrusion vector.\n
                 * Defaults to 0.0 if ommitted in the DXF file.\n
                 * Group code = 220. */
        double extr_z0,
                /*!< Z-value of the extrusion vector.\n
                 * Defaults to 1.0 if ommitted in the DXF file.\n
                 * Group code = 230. */
        char *soft_owner_object,
                /*!< Soft-pointer ID/handle to owner object.\n
                 * Group code = 330. */
        char *hard_owner_object
                /*!< Hard owner ID/handle to owner dictionary
                 * (optional).\n
                 * Group code = 360. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_block_write_lowlevel () function.\n", __FILE__, __LINE__);
#endif
        char *dxf_entity_name = strdup ("BLOCK");
        if (block_name == NULL)
        {
                fprintf (stderr, "Warning: empty block name string for the %s entity with id-code: %x\n", dxf_entity_name, id_code);
                fprintf (stderr, "         %s entity is discarded from output.\n", dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (xref_name == NULL)
        {
                fprintf (stderr, "Warning: empty xref name string for the %s entity with id-code: %x\n", dxf_entity_name, id_code);
                fprintf (stderr, "         %s entity is discarded from output.\n", dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (strcmp (layer, "") == 0)
        {
                fprintf (stderr, "Warning: empty layer string for the %s entity with id-code: %x\n", dxf_entity_name, id_code);
                fprintf (stderr, "    %s entity is relocated to layer 0.\n", dxf_entity_name);
                layer = strdup (DXF_DEFAULT_LAYER);
        }
        fprintf (fp, "  0\n%s\n", dxf_entity_name);
        if ((block_type && 4) || (block_type && 32))
        {
                fprintf (fp, "  1\n%s\n", xref_name);
        }
        fprintf (fp, "  2\n%s\n", block_name);
        fprintf (fp, "  3\n%s\n", block_name);
        if (strcmp (description, "") != 0)
        {
                fprintf (fp, "  4\n%s\n", description);
        }
        if (id_code != -1)
        {
                fprintf (fp, "  5\n%x\n", id_code);
        }
        fprintf (fp, "  8\n%s\n", layer);
        fprintf (fp, " 10\n%f\n", x0);
        fprintf (fp, " 20\n%f\n", y0);
        fprintf (fp, " 30\n%f\n", z0);
        fprintf (fp, " 70\n%d\n", block_type);
        if (strcmp (soft_owner_object, "") != 0)
        {
                fprintf (fp, "330\n%s\n", soft_owner_object);
        }
        if (strcmp (hard_owner_object, "") != 0)
        {
                fprintf (fp, "360\n%s\n", hard_owner_object);
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_block_write_lowlevel () function.\n", __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write DXF output to fp for a DxfBlock
 * ( a \c BLOCK entity).
 */
int
dxf_block_write
(
        FILE *fp,
                /*!< file pointer to output device */
        DxfBlock *dxf_block
                /*!< DXF block entity */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_block_write () function.\n",
                __FILE__, __LINE__);
#endif
        char *dxf_entity_name = strdup ("BLOCK");
        if (dxf_block == NULL)
        {
                return (EXIT_FAILURE);
                fprintf (stderr, "Error in dxf_block_write () a NULL pointer was passed.\n");
        }
        if (dxf_block->block_name == NULL)
        {
                fprintf (stderr, "Warning: empty block name string for the %s entity with id-code: %x\n",
                        dxf_entity_name, dxf_block->id_code);
                fprintf (stderr, "         %s entity is discarded from output.\n",
                        dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (dxf_block->xref_name == NULL)
        {
                fprintf (stderr, "Warning: empty xref name string for the %s entity with id-code: %x\n",
                        dxf_entity_name, dxf_block->id_code);
                fprintf (stderr, "         %s entity is discarded from output.\n",
                        dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (dxf_block->description == NULL)
        {
                fprintf (stderr, "Warning: NULL pointer to description string for the %s entity with id-code: %x\n",
                        dxf_entity_name, dxf_block->id_code);
                dxf_block->description = strdup ("");
        }
        if (strcmp (dxf_block->layer, "") == 0)
        {
                fprintf (stderr, "Warning: empty layer string for the %s entity with id-code: %x\n",
                        dxf_entity_name, dxf_block->id_code);
                fprintf (stderr, "    %s entity is relocated to layer 0.\n",
                        dxf_entity_name);
                dxf_block->layer = strdup (DXF_DEFAULT_LAYER);
        }
        if (dxf_block->soft_owner_object == NULL)
        {
                fprintf (stderr, "Warning: NULL pointer to soft owner object string for the %s entity with id-code: %x\n",
                        dxf_entity_name, dxf_block->id_code);
                dxf_block->soft_owner_object = strdup ("");
        }
        fprintf (fp, "  0\n%s\n", dxf_entity_name);
        if ((dxf_block->block_type && 4) || (dxf_block->block_type && 32))
        {
                fprintf (fp, "  1\n%s\n", dxf_block->xref_name);
        }
        fprintf (fp, "  2\n%s\n", dxf_block->block_name);
        fprintf (fp, "  3\n%s\n", dxf_block->block_name);
        if (strcmp (dxf_block->description, "") != 0)
        {
                fprintf (fp, "  4\n%s\n", dxf_block->description);
        }
        if (dxf_block->id_code != -1)
        {
                fprintf (fp, "  5\n%x\n", dxf_block->id_code);
        }
        fprintf (fp, "  8\n%s\n", dxf_block->layer);
        fprintf (fp, " 10\n%f\n", dxf_block->x0);
        fprintf (fp, " 20\n%f\n", dxf_block->y0);
        fprintf (fp, " 30\n%f\n", dxf_block->z0);
        fprintf (fp, " 70\n%d\n", dxf_block->block_type);
        if (strcmp (dxf_block->soft_owner_object, "") != 0)
        {
                fprintf (fp, "330\n%s\n", dxf_block->soft_owner_object);
        }
        if (strcmp (dxf_block->hard_owner_object, "") != 0)
        {
                fprintf (fp, "360\n%s\n", dxf_block->hard_owner_object);
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_block_write () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write DXF output to a file for an end of block marker
 * (a \c ENDBLK entity).
 *
 * Appears only in \c BLOCKS section.\n
 * Contains no other group codes than "0".
 */
int
dxf_block_write_endblk (FILE *fp)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_block_write_endblk () function.\n", __FILE__, __LINE__);
#endif
        fprintf (fp, "  0\nENDBLK\n");
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_block_write_endblk () function.\n", __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write DXF output to a file for a table of blocks.
 *
 * Appears only in \c TABLES section.\n
 */
int
dxf_block_write_table
(
        char *dxf_blocks_list, 
        int acad_version_number
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_block_write_table () function.\n", __FILE__, __LINE__);
#endif
        /*! \todo Add code here. */
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_block_write_table () function.\n", __FILE__, __LINE__);
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
        DxfBlock *dxf_block
                /*!< Pointer to the memory occupied by the DXF \c BLOCK
                 * entity. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_block_free () function.\n",
                __FILE__, __LINE__);
#endif
        if (dxf_block->next != NULL)
        {
              fprintf (stderr, "ERROR in dxf_block_free () pointer to next DxfBlock was not NULL.\n");
              return (EXIT_FAILURE);
        }
        free (dxf_block->xref_name);
        free (dxf_block->block_name);
        free (dxf_block->description);
        free (dxf_block->layer);
        free (dxf_block->soft_owner_object);
        free (dxf_block->hard_owner_object);
        free (dxf_block);
        dxf_block = NULL;
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_block_free () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
