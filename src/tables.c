/*!
 * \file tables.c
 *
 * \author Copyright (C) 2014, 2015, 2017 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF tables section (\c TABLES).
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


#include "tables.h"
#include "section.h"


/*!
 * \brief Allocate memory for a DXF \c TABLES section.
 *
 * Fill the memory contents with zeros.
 *
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfTables *
dxf_tables_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfTables *tables = NULL;
        size_t size;

        size = sizeof (DxfTables);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((tables = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfTables struct.\n")),
                  __FUNCTION__);
                tables = NULL;
        }
        else
        {
                memset (tables, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (tables);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c TABLES
 * section.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfTables *
dxf_tables_init
(
        DxfTables *tables
                /*!< DXF tables section. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tables == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                tables = dxf_tables_new ();
        }
        if (tables == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfTables struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        tables->max_table_entries = 0;
        tables->appids = NULL;
        tables->block_records = NULL;
        tables->dimstyles = NULL;
        tables->layers = NULL;
        tables->ltypes = NULL;
        tables->styles = NULL;
        tables->ucss = NULL;
        tables->views = NULL;
        tables->vports = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (tables);
}


/*!
 * \brief Write DXF output to a file for a table section.
 * 
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_tables_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfTables *tables
                /*!< DXF table section. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_section_name = strdup ("TABLES");

        /* Do some basic checks. */
        if (fp == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL file pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_section_name);
                return (EXIT_FAILURE);
        }
        dxf_section_write (fp, dxf_section_name);
        /*! \todo Add code here */
        dxf_endsec_write (fp);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c TABLE and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_tables_free
(
        DxfTables *tables
                /*!< DXF table section. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (tables == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (tables->appids);
        free (tables->block_records);
        free (tables->dimstyles);
        free (tables->layers);
        free (tables->ltypes);
        free (tables->styles);
        free (tables->ucss);
        free (tables->views);
        free (tables->vports);
        tables = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Get the \c max_table_entries from a DXF \c TABLES section.
 *
 * \return \c max_table_entries.
 */
int
dxf_tables_get_max_table_entries
(
        DxfTables *tables
                /*!< a pointer to a DXF \c TABLES section. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tables == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (tables->max_table_entries < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (tables->max_table_entries);
}


/*!
 * \brief Set the \c max_table_entries for a DXF \c TABLES section.
 */
DxfTables *
dxf_tables_set_max_table_entries
(
        DxfTables *tables,
                /*!< a pointer to a DXF \c TABLES section. */
        int max_table_entries
                /*!< the \c max_table_entries to be set for the section. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tables == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (max_table_entries < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        tables->max_table_entries = max_table_entries;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (tables);
}


/*!
 * \brief Get the \c appids from a DXF \c TABLES section.
 *
 * \return \c appids.
 */
struct DxfAppid *
dxf_tables_get_appids
(
        DxfTables *tables
                /*!< a pointer to a DXF \c TABLES section. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tables == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (tables->appids == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (tables->appids);
}


/*!
 * \brief Set the \c appids for a DXF \c TABLES section.
 */
DxfTables *
dxf_tables_set_appids
(
        DxfTables *tables,
                /*!< a pointer to a DXF \c TABLES section. */
        struct DxfAppid *appids
                /*!< the \c appids to be set for the section. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tables == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (appids == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        tables->appids = appids;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (tables);
}


/*!
 * \brief Get the \c block_records from a DXF \c TABLES section.
 *
 * \return \c block_records.
 */
struct DxfBlockRecord *
dxf_tables_get_block_records
(
        DxfTables *tables
                /*!< a pointer to a DXF \c TABLES section. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tables == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (tables->block_records == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (tables->block_records);
}


/*!
 * \brief Set the \c block_records for a DXF \c TABLES section.
 */
DxfTables *
dxf_tables_set_block_records
(
        DxfTables *tables,
                /*!< a pointer to a DXF \c TABLES section. */
        struct DxfBlockRecord *block_records
                /*!< the \c block_records to be set for the section. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tables == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (block_records == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        tables->block_records = block_records;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (tables);
}


/*!
 * \brief Get the \c dimstyles from a DXF \c TABLES section.
 *
 * \return \c dimstyles.
 */
struct DxfDimStyle *
dxf_tables_get_dimstyles
(
        DxfTables *tables
                /*!< a pointer to a DXF \c TABLES section. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tables == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (tables->dimstyles == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (tables->dimstyles);
}


/*!
 * \brief Set the \c dimstyles for a DXF \c TABLES section.
 */
DxfTables *
dxf_tables_set_dimstyles
(
        DxfTables *tables,
                /*!< a pointer to a DXF \c TABLES section. */
        struct DxfDimStyle *dimstyles
                /*!< the \c dimstyles to be set for the section. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tables == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimstyles == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        tables->dimstyles = dimstyles;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (tables);
}


/*!
 * \brief Get the \c layers from a DXF \c TABLES section.
 *
 * \return \c layers.
 */
struct DxfLayer *
dxf_tables_get_layers
(
        DxfTables *tables
                /*!< a pointer to a DXF \c TABLES section. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tables == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (tables->layers == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (tables->layers);
}


/*!
 * \brief Set the \c layers for a DXF \c TABLES section.
 */
DxfTables *
dxf_tables_set_layers
(
        DxfTables *tables,
                /*!< a pointer to a DXF \c TABLES section. */
        struct DxfLayer *layers
                /*!< the \c layers to be set for the section. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tables == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (layers == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        tables->layers = layers;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (tables);
}


/*!
 * \brief Get the \c ltypes from a DXF \c TABLES section.
 *
 * \return \c ltypes.
 */
struct DxfLType *
dxf_tables_get_ltypes
(
        DxfTables *tables
                /*!< a pointer to a DXF \c TABLES section. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tables == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (tables->ltypes == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (tables->ltypes);
}


/*!
 * \brief Set the \c ltypes for a DXF \c TABLES section.
 */
DxfTables *
dxf_tables_set_ltypes
(
        DxfTables *tables,
                /*!< a pointer to a DXF \c TABLES section. */
        struct DxfLType *ltypes
                /*!< the \c ltypes to be set for the section. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tables == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ltypes == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        tables->ltypes = ltypes;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (tables);
}


/*!
 * \brief Get the \c styles from a DXF \c TABLES section.
 *
 * \return \c styles.
 */
struct DxfStyle *
dxf_tables_get_styles
(
        DxfTables *tables
                /*!< a pointer to a DXF \c TABLES section. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tables == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (tables->styles == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (tables->styles);
}


/*!
 * \brief Set the \c styles for a DXF \c TABLES section.
 */
DxfTables *
dxf_tables_set_styles
(
        DxfTables *tables,
                /*!< a pointer to a DXF \c TABLES section. */
        struct DxfStyle *styles
                /*!< the \c styles to be set for the section. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tables == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (styles == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        tables->styles = styles;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (tables);
}


/*!
 * \brief Get the \c ucss from a DXF \c TABLES section.
 *
 * \return \c ucss.
 */
struct DxfUcs *
dxf_tables_get_ucss
(
        DxfTables *tables
                /*!< a pointer to a DXF \c TABLES section. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tables == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (tables->ucss == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (tables->ucss);
}


/*!
 * \brief Set the \c ucss for a DXF \c TABLES section.
 */
DxfTables *
dxf_tables_set_ucss
(
        DxfTables *tables,
                /*!< a pointer to a DXF \c TABLES section. */
        struct DxfUcs *ucss
                /*!< the \c ucss to be set for the section. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (tables == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (ucss == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        tables->ucss = ucss;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (tables);
}


/* EOF */
