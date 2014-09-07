/*!
 * \file endblk.c
 *
 * \author Copyright (C) 2014 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF end of block marker entity (\c ENDBLK).
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


#include "endblk.h"


/*!
 * \brief Allocate memory for a \c DxfEndblk
 * (a DXF \c ENDBLK entity).
 *
 * Fill the memory contents with zeros.
 *
 * \version According to DXF R10.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfEndblk *
dxf_endblk_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfEndblk *dxf_endblk = NULL;
        size_t size;

        size = sizeof (DxfEndblk);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_endblk = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("ERROR in %s () could not allocate memory for a DxfEndblk struct.\n")),
                  __FUNCTION__);
                dxf_endblk = NULL;
        }
        else
        {
                memset (dxf_endblk, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_endblk);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c DxfEndblk
 * (a DXF \c ENDBLK entity).
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 *
 * \version According to DXF R10.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfEndblk *
dxf_endblk_init
(
        DxfEndblk *dxf_endblk
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dxf_endblk == NULL)
        {
                fprintf (stderr,
                  (_("WARNING in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                dxf_endblk = dxf_endblk_new ();
        }
        if (dxf_endblk == NULL)
        {
                fprintf (stderr,
                  (_("ERROR in %s () could not allocate memory for a DxfEndblk struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dxf_endblk->id_code = 0;
        dxf_endblk->layer = strdup (DXF_DEFAULT_LAYER);
        dxf_endblk->dictionary_owner_soft = strdup ("");
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_endblk);
}

/*!
 * \brief Read data from a DXF file into a \c DxfEndblk
 * (a DXF \c ENDBLK entity).
 *
 * The last line read from file contained the string "ENDBLK". \n
 * Now follows some data for the \c ENDBLK, to be terminated with a "  0"
 * string announcing the following entity, or the end of the \c ENTITY
 * section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c dxf_endblk. \n
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 *
 * \version According to DXF R10.
 * \version According to DXF R13.
 * \version According to DXF R14.
 *
 * \todo After reading information from the \c BLOCK entity up until the
 * closing Group code 0, the pointer to the following \c ENDBLK entity
 * needs to be stored in the current (last) \c DxfBlock struct member
 * \c endblk.
 */
int
dxf_endblk_read
(
        DxfFile *fp,
        DxfEndblk *dxf_endblk
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char temp_string[DXF_MAX_STRING_LENGTH];

        /* Do some basic checks. */
        if (dxf_endblk == NULL)
        {
                fprintf (stderr,
                  (_("WARNING in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                dxf_endblk = dxf_endblk_new ();
                dxf_endblk_init (dxf_endblk);
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
                        return (0);
                }
                else if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        fscanf (fp->fp, "%x\n", &dxf_endblk->id_code);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        fscanf (fp->fp, "%s\n", dxf_endblk->layer);
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing Soft-pointer
                         * ID/handle to owner object. */
                        fscanf (fp->fp, "%s\n", dxf_endblk->dictionary_owner_soft);
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
                          (_("Warning: in %s () unknown string tag found while reading from: %s in line: %d.\n")),
                          __FUNCTION__, fp->filename, fp->line_number);
                }
        }
        /* Handle ommitted members and/or illegal values. */
        if (strcmp (dxf_endblk->layer, "") == 0)
        {
                dxf_endblk->layer = strdup (DXF_DEFAULT_LAYER);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write DXF output to a file for an end of block marker
 * (a DXF \c ENDBLK entity).
 *
 * Appears only in \c BLOCKS section.\n
 */
int
dxf_endblk_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfEndblk *dxf_endblk
                /*!< DXF end of block marker entity */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        fprintf (fp->fp, "  0\nENDBLK\n");
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "  5\n%x\n", dxf_endblk->id_code);
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
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
                fprintf (fp->fp, "  8\n%s\n", dxf_endblk->layer);
                fprintf (fp->fp, "100\nAcDbBlockEnd\n");
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DxfEndblk (a DXF \c ENDBLK
 * entity) and all it's data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 *
 * \version According to DXF R10.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
int
dxf_endblk_free
(
        DxfEndblk *dxf_endblk
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        free (dxf_endblk->layer);
        free (dxf_endblk->dictionary_owner_soft);
        free (dxf_endblk);
        dxf_endblk = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
