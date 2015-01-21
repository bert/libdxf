/*!
 * \file region.c
 *
 * \author Copyright (C) 2013 ... 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF region entity (\c REGION).
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


#include "region.h"


/*!
 * \brief Allocate memory for a \c DxfRegion.
 *
 * Fill the memory contents with zeros.
 *
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfRegion *
dxf_region_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfRegion *dxf_region = NULL;
        size_t size;

        size = sizeof (DxfRegion);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_region = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfRegion struct.\n")),
                  __FUNCTION__);
                dxf_region = NULL;
        }
        else
        {
                memset (dxf_region, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_region);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c REGION
 * entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 *
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfRegion *
dxf_region_init
(
        DxfRegion *dxf_region
                /*!< DXF \c REGION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        /* Do some basic checks. */
        if (dxf_region == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                dxf_region = dxf_region_new ();
        }
        if (dxf_region == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory for a DxfRegion struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        dxf_region->modeler_format_version_number = 0;
        dxf_region->id_code = 0;
        dxf_region->linetype = strdup (DXF_DEFAULT_LINETYPE);
        dxf_region->layer = strdup (DXF_DEFAULT_LAYER);
        dxf_region->elevation = 0.0;
        dxf_region->thickness = 0.0;
        dxf_region->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        dxf_region->visibility = DXF_DEFAULT_VISIBILITY;
        dxf_region->color = DXF_COLOR_BYLAYER;
        dxf_region->paperspace = DXF_MODELSPACE;
        dxf_region->modeler_format_version_number = 1;
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                dxf_region->proprietary_data[i] = strdup ("");
                dxf_region->additional_proprietary_data[i] = strdup ("");
        }
        dxf_region->dictionary_owner_soft = strdup ("");
        dxf_region->dictionary_owner_hard = strdup ("");
        dxf_region->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_region);
}


/*!
 * \brief Read data from a DXF file into a DXF \c REGION entity.
 *
 * The last line read from file contained the string "REGION". \n
 * Now follows some data for the \c REGION, to be terminated with a "  0"
 * string announcing the following entity, or the end of the \c ENTITY
 * section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c dxf_region. \n
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 *
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfRegion *
dxf_region_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfRegion *dxf_region
                /*!< DXF \c REGION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *temp_string = NULL;
        int i;
        int j;

        i = 0;
        j = 0;
        /* Do some basic checks. */
        if (dxf_region == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                dxf_region = dxf_region_new ();
                dxf_region = dxf_region_init (dxf_region);
        }
        (fp->line_number)++;
        fscanf (fp->fp, "%[^\n]", temp_string);
        while (strcmp (temp_string, "0") != 0)
        {
                if (ferror (fp->fp))
                {
                        fprintf (stderr,
                          (_("Error in %s () while reading from: %s in line: %d.\n")),
                          __FUNCTION__, fp->filename, fp->line_number);
                        fclose (fp->fp);
                        return (NULL);
                }
                else if (strcmp (temp_string, "  1") == 0)
                {
                        /* Now follows a string containing proprietary
                         * data. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_region->proprietary_data[i]);
                        i++;
                }
                else if (strcmp (temp_string, "  3") == 0)
                {
                        /* Now follows a string containing additional
                         * proprietary data. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_region->additional_proprietary_data[j]);
                        i++;
                }
                if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", &dxf_region->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_region->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_region->layer);
                }
                else if ((fp->acad_version_number <= AutoCAD_11)
                        && (strcmp (temp_string, "38") == 0)
                        && (dxf_region->elevation != 0.0))
                {
                        /* Now follows a string containing the
                         * elevation. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_region->elevation);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_region->thickness);
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing the linetype
                         * scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_region->linetype_scale);
                }
                else if (strcmp (temp_string, "60") == 0)
                {
                        /* Now follows a string containing the
                         * visibility value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &dxf_region->visibility);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_region->color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_region->paperspace);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "70") == 0))
                {
                        /* Now follows a string containing the modeler
                         * format version number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_region->modeler_format_version_number);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
                        if (strcmp (temp_string, "AcDbModelerGeometry") != 0)
                        {
                                fprintf (stderr, "Error in dxf_region_read () found a bad subclass marker in: %s in line: %d.\n",
                                        fp->filename, fp->line_number);
                        }
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing Soft-pointer
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_region->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_region->dictionary_owner_hard);
                }
                else if (strcmp (temp_string, "999") == 0)
                {
                        /* Now follows a string containing a comment. */
                        (fp->line_number)++;
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
        if (strcmp (dxf_region->linetype, "") == 0)
        {
                dxf_region->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (dxf_region->layer, "") == 0)
        {
                dxf_region->layer = strdup (DXF_DEFAULT_LAYER);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_region);
}


/*!
 * \brief Write DXF output to a file for a DXF \c REGION entity.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred while reading from the input file.
 *
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
int
dxf_region_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfRegion *dxf_region
                /*!< DXF \c REGION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("REGION");
        int i;

        /* Do some basic checks. */
        if (dxf_region == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (strcmp (dxf_region->linetype, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty linetype string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, dxf_region->id_code);
                fprintf (stderr,
                  (_("\t%s entity is reset to default linetype")),
                  dxf_entity_name);
                dxf_region->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (dxf_region->layer, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, dxf_region->id_code);
                fprintf (stderr,
                  (_("\t%s entity is relocated to layer 0")),
                  dxf_entity_name);
                dxf_region->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (dxf_region->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", dxf_region->id_code);
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
        if ((strcmp (dxf_region->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", dxf_region->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (dxf_region->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", dxf_region->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
        }
        if (dxf_region->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
        fprintf (fp->fp, "  8\n%s\n", dxf_region->layer);
        if (strcmp (dxf_region->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", dxf_region->linetype);
        }
        if ((fp->acad_version_number <= AutoCAD_11)
          && DXF_FLATLAND
          && (dxf_region->elevation != 0.0))
        {
                fprintf (fp->fp, " 38\n%f\n", dxf_region->elevation);
        }
        if (dxf_region->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", dxf_region->color);
        }
        if (dxf_region->linetype_scale != 1.0)
        {
                fprintf (fp->fp, " 48\n%f\n", dxf_region->linetype_scale);
        }
        if (dxf_region->visibility != 0)
        {
                fprintf (fp->fp, " 60\n%d\n", dxf_region->visibility);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbModelerGeometry\n");
        }
        if (dxf_region->thickness != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", dxf_region->thickness);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, " 70\n%d\n", dxf_region->modeler_format_version_number);
        }
        i = 0;
        while (strlen (dxf_region->proprietary_data[i]) > 0)
        {
                fprintf (fp->fp, "  1\n%s\n", dxf_region->proprietary_data[i]);
                i++;
        }
        i = 0;
        while (strlen (dxf_region->additional_proprietary_data[i]) > 0)
        {
                fprintf (fp->fp, "  3\n%s\n", dxf_region->additional_proprietary_data[i]);
                i++;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c REGION and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 *
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
int
dxf_region_free
(
        DxfRegion *dxf_region
                /*!< Pointer to the memory occupied by the DXF
                 * \c REGION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        if (dxf_region->next != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to next DxfRegion was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (dxf_region->linetype);
        free (dxf_region->layer);
        for (i = 0; i < DXF_MAX_PARAM; i++)
        {
                free (dxf_region->proprietary_data[i]);
                free (dxf_region->additional_proprietary_data[i]);
        }
        free (dxf_region->dictionary_owner_soft);
        free (dxf_region->dictionary_owner_hard);
        free (dxf_region);
        dxf_region = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
