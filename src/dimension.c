/*!
 * \file dimension.c
 *
 * \author Copyright (C) 2012 ... 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF dimension entity (\c DIMENSION).
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


#include "dimension.h"


/*!
 * \brief Allocate memory for a DXF \c DIMENSION.
 *
 * Fill the memory contents with zeros.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 * \version According to DXF R2000.
 */
DxfDimension *
dxf_dimension_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfDimension *dimension = NULL;
        size_t size;

        size = sizeof (DxfDimension);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dimension = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfDimension struct.\n")),
                  __FUNCTION__);
                dimension = NULL;
        }
        else
        {
                memset (dimension, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c
 * DIMENSION entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 * \version According to DXF R2000.
 */
DxfDimension *
dxf_dimension_init
(
        DxfDimension *dimension
                /*!< Pointer to the memory occupied by the DXF \c
                 * DIMENSION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                dimension = dxf_dimension_new ();
        }
        if (dimension == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory for a DxfDimension struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        dimension->id_code = 0;
        dimension->linetype = strdup (DXF_DEFAULT_LINETYPE);
        dimension->layer = strdup (DXF_DEFAULT_LAYER);
        dimension->elevation = 0.0;
        dimension->thickness = 0.0;
        dimension->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        dimension->visibility = DXF_DEFAULT_VISIBILITY;
        dimension->color = DXF_COLOR_BYLAYER;
        dimension->paperspace = DXF_PAPERSPACE;
        dimension->dim_text = strdup ("");
        dimension->dimblock_name = strdup ("");
        dimension->dimstyle_name = strdup ("");
        dimension->x0 = 0.0;
        dimension->y0 = 0.0;
        dimension->z0 = 0.0;
        dimension->x1 = 0.0;
        dimension->y1 = 0.0;
        dimension->z1 = 0.0;
        dimension->x2 = 0.0;
        dimension->y2 = 0.0;
        dimension->z2 = 0.0;
        dimension->x3 = 0.0;
        dimension->y3 = 0.0;
        dimension->z3 = 0.0;
        dimension->x4 = 0.0;
        dimension->y4 = 0.0;
        dimension->z4 = 0.0;
        dimension->x5 = 0.0;
        dimension->y5 = 0.0;
        dimension->z5 = 0.0;
        dimension->x6 = 0.0;
        dimension->y6 = 0.0;
        dimension->z6 = 0.0;
        dimension->leader_length = 0.0;
        dimension->text_line_spacing_factor = 0.0;
        dimension->actual_measurement = 0.0;
        dimension->angle = 0.0;
        dimension->hor_dir = 0.0;
        dimension->obl_angle = 0.0;
        dimension->text_angle = 0.0;
        dimension->flag = 0;
        dimension->attachment_point = 0;
        dimension->text_line_spacing = 0;
        dimension->extr_x0 = 0.0;
        dimension->extr_y0 = 0.0;
        dimension->extr_z0 = 0.0;
        dimension->dictionary_owner_soft = strdup ("");
        dimension->dictionary_owner_hard = strdup ("");
        dimension->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Read data from a DXF file into a DXF \c DIMENSION entity.
 *
 * The last line read from file contained the string "DIMENSION". \n
 * Now follows some data for the \c DIMENSION, to be terminated with a
 * "  0" string announcing the following entity, or the end of the
 * \c ENTITY section marker \c ENDSEC. \n
 *
 * \return a pointer to \c dimension.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 * \version According to DXF R2000.
 */
DxfDimension *
dxf_dimension_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfDimension *dimension
                /*!< DXF \c DIMENSION entity. */
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
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                dimension = dxf_dimension_new ();
                dimension = dxf_dimension_init (dimension);
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
                        /* Clean up. */
                        free (temp_string);
                        return (NULL);
                }
                if (strcmp (temp_string, "1") == 0)
                {
                        /* Now follows a string containing a dimension
                         * text string. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dimension->dim_text);
                }
                if (strcmp (temp_string, "2") == 0)
                {
                        /* Now follows a string containing a dimension
                         * block name string. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dimension->dimblock_name);
                }
                if (strcmp (temp_string, "3") == 0)
                {
                        /* Now follows a string containing a dimension
                         * style name string. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dimension->dimstyle_name);
                }
                if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", &dimension->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dimension->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dimension->layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-value of the definition point for all
                         * dimension types. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimension->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the definition point for all
                         * dimension types. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimension->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the definition point for all
                         * dimension types. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimension->z0);
                }
                else if (strcmp (temp_string, "11") == 0)
                {
                        /* Now follows a string containing the
                         * X-value of the middle point of dimension text. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimension->x1);
                }
                else if (strcmp (temp_string, "21") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the middle point of dimension text. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimension->y1);
                }
                else if (strcmp (temp_string, "31") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the middle point of dimension text. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimension->z1);
                }
                else if (strcmp (temp_string, "12") == 0)
                {
                        /* Now follows a string containing the
                         * X-value of the dimension block translation
                         * vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimension->x2);
                }
                else if (strcmp (temp_string, "22") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the dimension block translation
                         * vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimension->y2);
                }
                else if (strcmp (temp_string, "32") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the dimension block translation
                         * vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimension->z2);
                }
                else if (strcmp (temp_string, "13") == 0)
                {
                        /* Now follows a string containing the
                         * X-value of the definition point for linear and
                         * angular dimensions. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimension->x3);
                }
                else if (strcmp (temp_string, "23") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the definition point for linear and
                         * angular dimensions. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimension->y3);
                }
                else if (strcmp (temp_string, "33") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the definition point for linear and
                         * angular dimensions. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimension->z3);
                }
                else if (strcmp (temp_string, "14") == 0)
                {
                        /* Now follows a string containing the
                         * X-value of the definition point for linear and
                         * angular dimensions. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimension->x4);
                }
                else if (strcmp (temp_string, "24") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the definition point for linear and
                         * angular dimensions. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimension->y4);
                }
                else if (strcmp (temp_string, "34") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the definition point for linear and
                         * angular dimensions. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimension->z4);
                }
                else if (strcmp (temp_string, "15") == 0)
                {
                        /* Now follows a string containing the
                         * X-value of the definition point for diameter,
                         * radius, and angular dimensions. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimension->x5);
                }
                else if (strcmp (temp_string, "25") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the definition point for diameter,
                         * radius, and angular dimensions. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimension->y5);
                }
                else if (strcmp (temp_string, "35") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the definition point for diameter,
                         * radius, and angular dimensions. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimension->z5);
                }
                else if (strcmp (temp_string, "16") == 0)
                {
                        /* Now follows a string containing the
                         * X-value of the point defining dimension arc for
                         * angular dimensions. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimension->x6);
                }
                else if (strcmp (temp_string, "26") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the point defining dimension arc for
                         * angular dimensions. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimension->y6);
                }
                else if (strcmp (temp_string, "36") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the point defining dimension arc for
                         * angular dimensions. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimension->z5);
                }
                else if ((fp->acad_version_number <= AutoCAD_11)
                        && (strcmp (temp_string, "38") == 0)
                        && (dimension->elevation = 0.0))
                {
                        /* Now follows a string containing the
                         * elevation. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimension->elevation);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimension->thickness);
                }
                else if (strcmp (temp_string, "40") == 0)
                {
                        /* Now follows a string containing the leader
                         * length. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimension->leader_length);
                }
                else if (strcmp (temp_string, "41") == 0)
                {
                        /* Now follows a string containing the text line
                         * spacing factor. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimension->text_line_spacing_factor);
                }
                else if (strcmp (temp_string, "42") == 0)
                {
                        /* Now follows a string containing the actual
                         * measurement. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimension->actual_measurement);
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing the linetype
                         * scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimension->linetype_scale);
                }
                else if (strcmp (temp_string, "50") == 0)
                {
                        /* Now follows a string containing the angle of
                         * rotated, horizontal, or vertical linear
                         * dimensions. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimension->angle);
                }
                else if (strcmp (temp_string, "51") == 0)
                {
                        /* Now follows a string containing the horizontal
                         * direction. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimension->hor_dir);
                }
                else if (strcmp (temp_string, "52") == 0)
                {
                        /* Now follows a string containing the oblique
                         * angle. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimension->obl_angle);
                }
                else if (strcmp (temp_string, "53") == 0)
                {
                        /* Now follows a string containing the text
                         * angle. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimension->text_angle);
                }
                else if (strcmp (temp_string, "60") == 0)
                {
                        /* Now follows a string containing the
                         * visibility value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &dimension->visibility);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dimension->color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dimension->paperspace);
                }
                else if (strcmp (temp_string, "70") == 0)
                {
                        /* Now follows a string containing a flag
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dimension->flag);
                }
                else if (strcmp (temp_string, "71") == 0)
                {
                        /* Now follows a string containing the attachment
                         * point value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dimension->attachment_point);
                }
                else if (strcmp (temp_string, "72") == 0)
                {
                        /* Now follows a string containing the text line
                         * spacing value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dimension->text_line_spacing);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
                        if ((strcmp (temp_string, "AcDbEntity") != 0)
                          && (strcmp (temp_string, "AcDbDimension") != 0)
                          && (strcmp (temp_string, "AcDbAlignedDimension") != 0)
                          && (strcmp (temp_string, "AcDbRotatedDimension") != 0)
                          && (strcmp (temp_string, "AcDb3PointAngularDimension") != 0)
                          && (strcmp (temp_string, "AcDbDiametricDimension") != 0)
                          && (strcmp (temp_string, "AcDbRadialDimension") != 0)
                          && (strcmp (temp_string, "AcDbOrdinateDimension") != 0))
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
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimension->extr_x0);
                }
                else if (strcmp (temp_string, "220") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimension->extr_y0);
                }
                else if (strcmp (temp_string, "230") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimension->extr_z0);
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing Soft-pointer
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dimension->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dimension->dictionary_owner_hard);
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
        if (strcmp (dimension->linetype, "") == 0)
        {
                dimension->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (dimension->layer, "") == 0)
        {
                dimension->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Clean up. */
        free (temp_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Write DXF output for a DXF \c DIMENSION entity.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 * \version According to DXF R2000.
 */
int
dxf_dimension_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfDimension *dimension
                /*!< Pointer to the memory occupied by the DXF \c
                 * DIMENSION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("DIMENSION");

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
        if (dimension == NULL)
        {
                return (EXIT_FAILURE);
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (strcmp (dimension->layer, "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, dimension->id_code);
                fprintf (stderr,
                  (_("\t%s entity is relocated to layer 0")),
                  dxf_entity_name);
                dimension->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (dimension->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", dimension->id_code);
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
        if ((strcmp (dimension->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", dimension->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (dimension->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", dimension->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
        }
        if (dimension->paperspace == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
        fprintf (fp->fp, "  8\n%s\n", dimension->layer);
        if (strcmp (dimension->linetype, DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", dimension->linetype);
        }
        if (dimension->color != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", dimension->color);
        }
        if (dimension->linetype_scale != 1.0)
        {
                fprintf (fp->fp, " 48\n%f\n", dimension->linetype_scale);
        }
        if (dimension->visibility != 0)
        {
                fprintf (fp->fp, " 60\n%d\n", dimension->visibility);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbDimension\n");
        }
        fprintf (fp->fp, "  2\n%s\n", dimension->dimblock_name);
        fprintf (fp->fp, " 10\n%f\n", dimension->x0);
        fprintf (fp->fp, " 20\n%f\n", dimension->y0);
        fprintf (fp->fp, " 30\n%f\n", dimension->z0);
        fprintf (fp->fp, " 11\n%f\n", dimension->x1);
        fprintf (fp->fp, " 21\n%f\n", dimension->y1);
        fprintf (fp->fp, " 31\n%f\n", dimension->z1);
        fprintf (fp->fp, " 70\n%d\n", dimension->flag);
        if (fp->acad_version_number >= AutoCAD_2000)
        {
                fprintf (fp->fp, " 71\n%d\n", dimension->attachment_point);
                fprintf (fp->fp, " 72\n%d\n", dimension->text_line_spacing);
                fprintf (fp->fp, " 41\n%f\n", dimension->text_line_spacing_factor);
                fprintf (fp->fp, " 42\n%f\n", dimension->actual_measurement);
        }
        fprintf (fp->fp, "  1\n%s\n", dimension->dim_text);
        fprintf (fp->fp, " 53\n%f\n", dimension->text_angle);
        fprintf (fp->fp, " 51\n%f\n", dimension->hor_dir);
        fprintf (fp->fp, "210\n%fn", dimension->extr_x0);
        fprintf (fp->fp, "220\n%fn", dimension->extr_y0);
        fprintf (fp->fp, "230\n%fn", dimension->extr_z0);
        fprintf (fp->fp, "  3\n%s\n", dimension->dimstyle_name);
        /* Rotated, horizontal, or vertical dimension. */
        if (dimension->flag == 0)
        {
                if (fp->acad_version_number >= AutoCAD_13)
                {
                        fprintf (fp->fp, "100\nAcDbAlignedDimension\n");
                }
                fprintf (fp->fp, " 12\n%f\n", dimension->x2);
                fprintf (fp->fp, " 22\n%f\n", dimension->y2);
                fprintf (fp->fp, " 32\n%f\n", dimension->z2);
                fprintf (fp->fp, " 13\n%f\n", dimension->x3);
                fprintf (fp->fp, " 23\n%f\n", dimension->y3);
                fprintf (fp->fp, " 33\n%f\n", dimension->z3);
                fprintf (fp->fp, " 14\n%f\n", dimension->x4);
                fprintf (fp->fp, " 24\n%f\n", dimension->y4);
                fprintf (fp->fp, " 34\n%f\n", dimension->z4);
                fprintf (fp->fp, " 50\n%f\n", dimension->angle);
                fprintf (fp->fp, " 52\n%f\n", dimension->obl_angle);
                if (fp->acad_version_number >= AutoCAD_13)
                {
                        fprintf (fp->fp, "100\nAcDbRotatedDimension\n");
                }
        }
        /* Aligned dimension. */
        if (dimension->flag == 1)
        {
                if (fp->acad_version_number >= AutoCAD_13)
                {
                        fprintf (fp->fp, "100\nAcDbAlignedDimension\n");
                }
                fprintf (fp->fp, " 12\n%f\n", dimension->x2);
                fprintf (fp->fp, " 22\n%f\n", dimension->y2);
                fprintf (fp->fp, " 32\n%f\n", dimension->z2);
                fprintf (fp->fp, " 13\n%f\n", dimension->x3);
                fprintf (fp->fp, " 23\n%f\n", dimension->y3);
                fprintf (fp->fp, " 33\n%f\n", dimension->z3);
                fprintf (fp->fp, " 14\n%f\n", dimension->x4);
                fprintf (fp->fp, " 24\n%f\n", dimension->y4);
                fprintf (fp->fp, " 34\n%f\n", dimension->z4);
                fprintf (fp->fp, " 50\n%f\n", dimension->angle);
        }
        /* Angular dimension. */
        if (dimension->flag == 2)
        {
                if (fp->acad_version_number >= AutoCAD_13)
                {
                        fprintf (fp->fp, "100\nAcDb3PointAngularDimension\n");
                }
                fprintf (fp->fp, " 13\n%f\n", dimension->x3);
                fprintf (fp->fp, " 23\n%f\n", dimension->y3);
                fprintf (fp->fp, " 33\n%f\n", dimension->z3);
                fprintf (fp->fp, " 14\n%f\n", dimension->x4);
                fprintf (fp->fp, " 24\n%f\n", dimension->y4);
                fprintf (fp->fp, " 34\n%f\n", dimension->z4);
                fprintf (fp->fp, " 15\n%f\n", dimension->x5);
                fprintf (fp->fp, " 25\n%f\n", dimension->y5);
                fprintf (fp->fp, " 35\n%f\n", dimension->z5);
                fprintf (fp->fp, " 16\n%f\n", dimension->x6);
                fprintf (fp->fp, " 26\n%f\n", dimension->y6);
                fprintf (fp->fp, " 36\n%f\n", dimension->z6);
        }
        /* Diameter dimension. */
        if (dimension->flag == 3)
        {
                if (fp->acad_version_number >= AutoCAD_13)
                {
                        fprintf (fp->fp, "100\nAcDbDiametricDimension\n");
                }
                fprintf (fp->fp, " 15\n%f\n", dimension->x5);
                fprintf (fp->fp, " 25\n%f\n", dimension->y5);
                fprintf (fp->fp, " 35\n%f\n", dimension->z5);
                fprintf (fp->fp, " 40\n%f\n", dimension->leader_length);
        }
        /* Radius dimension. */
        if (dimension->flag == 4)
        {
                if (fp->acad_version_number >= AutoCAD_13)
                {
                        fprintf (fp->fp, "100\nAcDbRadialDimension\n");
                }
                fprintf (fp->fp, " 15\n%f\n", dimension->x5);
                fprintf (fp->fp, " 25\n%f\n", dimension->y5);
                fprintf (fp->fp, " 35\n%f\n", dimension->z5);
                fprintf (fp->fp, " 40\n%f\n", dimension->leader_length);
        }
        /* Angular 3-point dimension. */
        if (dimension->flag == 5)
        {
                if (fp->acad_version_number >= AutoCAD_13)
                {
                        fprintf (fp->fp, "100\nAcDb3PointAngularDimension\n");
                }
                fprintf (fp->fp, " 13\n%f\n", dimension->x3);
                fprintf (fp->fp, " 23\n%f\n", dimension->y3);
                fprintf (fp->fp, " 33\n%f\n", dimension->z3);
                fprintf (fp->fp, " 14\n%f\n", dimension->x4);
                fprintf (fp->fp, " 24\n%f\n", dimension->y4);
                fprintf (fp->fp, " 34\n%f\n", dimension->z4);
                fprintf (fp->fp, " 15\n%f\n", dimension->x5);
                fprintf (fp->fp, " 25\n%f\n", dimension->y5);
                fprintf (fp->fp, " 35\n%f\n", dimension->z5);
                fprintf (fp->fp, " 16\n%f\n", dimension->x6);
                fprintf (fp->fp, " 26\n%f\n", dimension->y6);
                fprintf (fp->fp, " 36\n%f\n", dimension->z6);
        }
        /* Ordinate dimension. */
        if (dimension->flag == 6)
        {
                if (fp->acad_version_number >= AutoCAD_13)
                {
                        fprintf (fp->fp, "100\nAcDbOrdinateDimension\n");
                }
                fprintf (fp->fp, " 13\n%f\n", dimension->x3);
                fprintf (fp->fp, " 23\n%f\n", dimension->y3);
                fprintf (fp->fp, " 33\n%f\n", dimension->z3);
                fprintf (fp->fp, " 14\n%f\n", dimension->x4);
                fprintf (fp->fp, " 24\n%f\n", dimension->y4);
                fprintf (fp->fp, " 34\n%f\n", dimension->z4);
        }
        if (dimension->thickness != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", dimension->thickness);
        }
        /* Clean up. */
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c DIMENSION and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 * \version According to DXF R2000.
 */
int
dxf_dimension_free
(
        DxfDimension *dimension
                /*!< Pointer to the memory occupied by the DXF \c
                 * DIMENSION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (dimension->next != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to next DxfDimension was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (dimension->linetype);
        free (dimension->layer);
        free (dimension->dim_text);
        free (dimension->dimblock_name);
        free (dimension->dimstyle_name);
        free (dimension->dictionary_owner_soft);
        free (dimension->dictionary_owner_hard);
        free (dimension);
        dimension = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a chain of DXF \c DIMENSION
 * entities and all their data fields.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
void
dxf_dimension_free_chain
(
        DxfDimension *dimensions
                /*!< pointer to the chain of DXF \c DIMENSION entities. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (dimensions == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (dimensions != NULL)
        {
                struct DxfDimension *iter = dimensions->next;
                dxf_dimension_free (dimensions);
                dimensions = (DxfDimension *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the ID code from a DXF \c DIMENSION entity.
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
dxf_dimension_get_id_code
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result;

        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dimension->id_code < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the id-code member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = dimension->id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Get the value of the \c flag of a DXF \c DIMENSION.
 *
 * \return The value of the \c flag, or -1 when an error occurred.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 * \version According to DXF R2000.
 */
int
dxf_dimension_get_flag
(
        DxfDimension *dimension
                /*!< Pointer to the DXF \c DIMENSION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (dimension == NULL)
        {
              fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
              return (-1);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension->flag);
}


/*!
 * \brief Set the ID code for a DXF \c DIMENSION entity.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfDimension *
dxf_dimension_set_id_code
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
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
        if (dimension == NULL)
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
        dimension->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the linetype from a DXF \c DIMENSION entity.
 *
 * \return linetype when sucessful, \c NULL when an error occurred.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
char *
dxf_dimension_get_linetype
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *result = NULL;

        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimension->linetype ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the linetype member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = strdup (dimension->linetype);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the linetype for a DXF \c DIMENSION entity.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfDimension *
dxf_dimension_set_linetype
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        char *linetype
                /*!< a string containing the linetype for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (linetype == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimension->linetype = strdup (linetype);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the layer from a DXF \c DIMENSION entity.
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
dxf_dimension_get_layer
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *result = NULL;

        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimension->layer ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the layer member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = strdup (dimension->layer);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the layer for a DXF \c DIMENSION entity.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfDimension *
dxf_dimension_set_layer
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        char *layer
                /*!< a string containing the layer for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
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
        dimension->layer = strdup (layer);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the elevation from a DXF \c DIMENSION entity.
 *
 * \return elevation.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
double
dxf_dimension_get_elevation
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        double result;

        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = dimension->elevation;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the elevation for a DXF \c DIMENSION entity.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfDimension *
dxf_dimension_set_elevation
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        double elevation
                /*!< the elevation to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimension->elevation = elevation;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the thickness from a DXF \c DIMENSION entity.
 *
 * \return thickness.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
double
dxf_dimension_get_thickness
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        double result;

        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dimension->thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the thickness member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = dimension->thickness;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the thickness for a DXF \c DIMENSION entity.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfDimension *
dxf_dimension_set_thickness
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        double thickness
                /*!< the thickness to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative thickness value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimension->thickness = thickness;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the linetype scale from a DXF \c DIMENSION entity.
 *
 * \return linetype scale.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
double
dxf_dimension_get_linetype_scale
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        double result;

        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dimension->linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the linetype scale member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = dimension->linetype_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the linetype scale for a DXF \c DIMENSION entity.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfDimension *
dxf_dimension_set_linetype_scale
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        double linetype_scale
                /*!< the linetype scale to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative linetype scale value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimension->linetype_scale = linetype_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the visibility from a DXF \c DIMENSION entity.
 *
 * \return visibility.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
int16_t
dxf_dimension_get_visibility
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int16_t result;

        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dimension->visibility < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found in the visibility member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dimension->visibility > 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was found in the visibility member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = dimension->visibility;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the visibility for a DXF \c DIMENSION entity.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfDimension *
dxf_dimension_set_visibility
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        int16_t visibility
                /*!< the visibility to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (visibility < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative visibility value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (visibility > 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range visibility value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimension->visibility = visibility;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the color from a DXF \c DIMENSION entity.
 *
 * \return color.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
int
dxf_dimension_get_color
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result;

        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dimension->color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found in the color member.\n")),
                  __FUNCTION__);
        }
        result = dimension->color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the color for a DXF \c DIMENSION entity.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfDimension *
dxf_dimension_set_color
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        int color
                /*!< the color to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative color value was passed.\n")),
                  __FUNCTION__);
                fprintf (stderr,
                  (_("\teffectively turning this entity it's visibility off.\n")));
        }
        dimension->color = color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the paperspace flag value from a DXF \c DIMENSION entity.
 *
 * \return paperspace flag value.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
int
dxf_dimension_get_paperspace
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int result;

        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dimension->paperspace < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found in the paperspace member.\n")),
                  __FUNCTION__);
        }
        if (dimension->paperspace > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found in the paperspace member.\n")),
                  __FUNCTION__);
        }
        result = dimension->paperspace;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the paperspace flag for a DXF \c DIMENSION entity.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfDimension *
dxf_dimension_set_paperspace
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        int paperspace
                /*!< the paperspace flag value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (paperspace < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative paperspace value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (paperspace > 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range paperspace value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimension->paperspace = paperspace;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the soft pointer to the dictionary owner from a DXF 
 * \c DIMENSION entity.
 *
 * \return soft pointer to the dictionary owner.
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
dxf_dimension_get_dictionary_owner_soft
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *result;

        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimension->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the dictionary_owner_soft member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = strdup (dimension->dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_soft for a DXF
 * \c DIMENSION entity.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfDimension *
dxf_dimension_set_dictionary_owner_soft
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the
                 * \c dictionary_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dictionary_owner_soft == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimension->dictionary_owner_soft = strdup (dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the hard pointer to the dictionary owner from a DXF 
 * \c DIMENSION entity.
 *
 * \return hard pointer to the dictionary owner.
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
dxf_dimension_get_dictionary_owner_hard
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *result;

        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimension->dictionary_owner_hard ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the dictionary_owner_hard member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = strdup (dimension->dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_hard for a DXF
 * \c DIMENSION entity.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfDimension *
dxf_dimension_set_dictionary_owner_hard
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        char *dictionary_owner_hard
                /*!< a string containing the pointer to the
                 * \c dictionary_owner_hard for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dictionary_owner_hard == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimension->dictionary_owner_hard = strdup (dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the \c dim_text from a DXF \c DIMENSION entity.
 *
 * \return \c dim_text when sucessful, \c NULL when an error occurred.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
char *
dxf_dimension_get_dim_text
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *result = NULL;

        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimension->dim_text ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the dim_text member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = strdup (dimension->dim_text);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the \c dim_text for a DXF \c DIMENSION entity.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfDimension *
dxf_dimension_set_dim_text
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        char *dim_text
                /*!< a string containing the \c dim_text for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dim_text == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimension->dim_text = strdup (dim_text);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the \c dimblock_name from a DXF \c DIMENSION entity.
 *
 * \return \c dimblock_name when sucessful, \c NULL when an error
 * occurred.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
char *
dxf_dimension_get_dimblock_name
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *result = NULL;

        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimension->dimblock_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the dimblock_name member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = strdup (dimension->dimblock_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the \c dimblock_name for a DXF \c DIMENSION entity.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfDimension *
dxf_dimension_set_dimblock_name
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        char *dimblock_name
                /*!< a string containing the \c dimblock_name for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimblock_name == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimension->dimblock_name = strdup (dimblock_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the \c dimstyle_name from a DXF \c DIMENSION entity.
 *
 * \return \c dimstyle_name when sucessful, \c NULL when an error
 * occurred.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
char *
dxf_dimension_get_dimstyle_name
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *result = NULL;

        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimension->dimstyle_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found in the dimstyle_name member.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = strdup (dimension->dimstyle_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the \c dimstyle_name for a DXF \c DIMENSION entity.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfDimension *
dxf_dimension_set_dimstyle_name
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        char *dimstyle_name
                /*!< a string containing the \c dimstyle_name for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimstyle_name == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimension->dimblock_name = strdup (dimstyle_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the definition point for all dimension types of a DXF
 * \c DIMENSION entity.
 *
 * \return the definition point.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfPoint *
dxf_dimension_get_x0
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        int id_code,
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file. */
        int inheritance
                /*!< Inherit layer, linetype, color and other relevant
                 * properties from either:
                 * <ol>
                 * <li value = "0"> Default (as initialised).</li>
                 * <li value = "1"> \c DIMENSION.</li>
                 * </ol>
                 */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfPoint *p1 = NULL;

        /* Do some basic checks. */
        if (dimension == NULL)
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
        p1->x0 = dimension->x0;
        p1->y0 = dimension->y0;
        p1->z0 = dimension->z0;
        switch (inheritance)
        {
                case 0:
                        /* Do nothing. */
                        break;
                case 1:
                        if (dimension->linetype != NULL)
                        {
                                p1->linetype = strdup (dimension->linetype);
                        }
                        if (dimension->layer != NULL)
                        {
                                p1->layer = strdup (dimension->layer);
                        }
                        p1->thickness = dimension->thickness;
                        p1->linetype_scale = dimension->linetype_scale;
                        p1->visibility = dimension->visibility;
                        p1->color = dimension->color;
                        p1->paperspace = dimension->paperspace;
                        if (dimension->dictionary_owner_soft != NULL)
                        {
                                p1->dictionary_owner_soft = strdup (dimension->dictionary_owner_soft);
                        }
                        if (dimension->dictionary_owner_hard != NULL)
                        {
                                p1->dictionary_owner_hard = strdup (dimension->dictionary_owner_hard);
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
 * \brief Set the definition point for all dimension types of a DXF
 * \c DIMENSION entity.
 *
 * \return a pointer to a DXF \c DIMENSION entity.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfDimension *
dxf_dimension_set_x0
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        DxfPoint *point
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimension->x0 = point->x0;
        dimension->y0 = point->y0;
        dimension->z0 = point->z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the middle point for all dimension types of a DXF
 * \c DIMENSION entity.
 *
 * \return the middle point.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfPoint *
dxf_dimension_get_x1
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        int id_code,
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file. */
        int inheritance
                /*!< Inherit layer, linetype, color and other relevant
                 * properties from either:
                 * <ol>
                 * <li value = "0"> Default (as initialised).</li>
                 * <li value = "1"> \c DIMENSION.</li>
                 * </ol>
                 */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfPoint *p1 = NULL;

        /* Do some basic checks. */
        if (dimension == NULL)
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
        p1->x0 = dimension->x1;
        p1->y0 = dimension->y1;
        p1->z0 = dimension->z1;
        switch (inheritance)
        {
                case 0:
                        /* Do nothing. */
                        break;
                case 1:
                        if (dimension->linetype != NULL)
                        {
                                p1->linetype = strdup (dimension->linetype);
                        }
                        if (dimension->layer != NULL)
                        {
                                p1->layer = strdup (dimension->layer);
                        }
                        p1->thickness = dimension->thickness;
                        p1->linetype_scale = dimension->linetype_scale;
                        p1->visibility = dimension->visibility;
                        p1->color = dimension->color;
                        p1->paperspace = dimension->paperspace;
                        if (dimension->dictionary_owner_soft != NULL)
                        {
                                p1->dictionary_owner_soft = strdup (dimension->dictionary_owner_soft);
                        }
                        if (dimension->dictionary_owner_hard != NULL)
                        {
                                p1->dictionary_owner_hard = strdup (dimension->dictionary_owner_hard);
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
 * \brief Set the middle point for all dimension types of a DXF
 * \c DIMENSION entity.
 *
 * \return a pointer to a DXF \c DIMENSION entity.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfDimension *
dxf_dimension_set_x1
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        DxfPoint *point
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimension->x1 = point->x0;
        dimension->y1 = point->y0;
        dimension->z1 = point->z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the dimension block translation vector for a DXF
 * \c DIMENSION entity.
 *
 * \return the dimension block translation vector.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfPoint *
dxf_dimension_get_x2
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        int id_code,
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file. */
        int inheritance
                /*!< Inherit layer, linetype, color and other relevant
                 * properties from either:
                 * <ol>
                 * <li value = "0"> Default (as initialised).</li>
                 * <li value = "1"> \c DIMENSION.</li>
                 * </ol>
                 */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfPoint *p1 = NULL;

        /* Do some basic checks. */
        if (dimension == NULL)
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
        p1->x0 = dimension->x2;
        p1->y0 = dimension->y2;
        p1->z0 = dimension->z2;
        switch (inheritance)
        {
                case 0:
                        /* Do nothing. */
                        break;
                case 1:
                        if (dimension->linetype != NULL)
                        {
                                p1->linetype = strdup (dimension->linetype);
                        }
                        if (dimension->layer != NULL)
                        {
                                p1->layer = strdup (dimension->layer);
                        }
                        p1->thickness = dimension->thickness;
                        p1->linetype_scale = dimension->linetype_scale;
                        p1->visibility = dimension->visibility;
                        p1->color = dimension->color;
                        p1->paperspace = dimension->paperspace;
                        if (dimension->dictionary_owner_soft != NULL)
                        {
                                p1->dictionary_owner_soft = strdup (dimension->dictionary_owner_soft);
                        }
                        if (dimension->dictionary_owner_hard != NULL)
                        {
                                p1->dictionary_owner_hard = strdup (dimension->dictionary_owner_hard);
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
 * \brief Set the dimension block translation vector for a DXF
 * \c DIMENSION entity.
 *
 * \return a pointer to a DXF \c DIMENSION entity.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfDimension *
dxf_dimension_set_x2
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        DxfPoint *point
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimension->x2 = point->x0;
        dimension->y2 = point->y0;
        dimension->z2 = point->z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the definition point for linear and angular dimensions for
 * a DXF \c DIMENSION entity.
 *
 * \return the definition point for linear and angular dimensions.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfPoint *
dxf_dimension_get_x3
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        int id_code,
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file. */
        int inheritance
                /*!< Inherit layer, linetype, color and other relevant
                 * properties from either:
                 * <ol>
                 * <li value = "0"> Default (as initialised).</li>
                 * <li value = "1"> \c DIMENSION.</li>
                 * </ol>
                 */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfPoint *p1 = NULL;

        /* Do some basic checks. */
        if (dimension == NULL)
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
        p1->x0 = dimension->x3;
        p1->y0 = dimension->y3;
        p1->z0 = dimension->z3;
        switch (inheritance)
        {
                case 0:
                        /* Do nothing. */
                        break;
                case 1:
                        if (dimension->linetype != NULL)
                        {
                                p1->linetype = strdup (dimension->linetype);
                        }
                        if (dimension->layer != NULL)
                        {
                                p1->layer = strdup (dimension->layer);
                        }
                        p1->thickness = dimension->thickness;
                        p1->linetype_scale = dimension->linetype_scale;
                        p1->visibility = dimension->visibility;
                        p1->color = dimension->color;
                        p1->paperspace = dimension->paperspace;
                        if (dimension->dictionary_owner_soft != NULL)
                        {
                                p1->dictionary_owner_soft = strdup (dimension->dictionary_owner_soft);
                        }
                        if (dimension->dictionary_owner_hard != NULL)
                        {
                                p1->dictionary_owner_hard = strdup (dimension->dictionary_owner_hard);
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
 * \brief Set the definition point for linear and angular dimensions for
 * a DXF \c DIMENSION entity.
 *
 * \return a pointer to a DXF \c DIMENSION entity.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfDimension *
dxf_dimension_set_x3
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        DxfPoint *point
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimension->x3 = point->x0;
        dimension->y3 = point->y0;
        dimension->z3 = point->z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the definition point for linear and angular dimensions for
 * a DXF \c DIMENSION entity.
 *
 * \return the definition point for linear and angular dimensions.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfPoint *
dxf_dimension_get_x4
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        int id_code,
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file. */
        int inheritance
                /*!< Inherit layer, linetype, color and other relevant
                 * properties from either:
                 * <ol>
                 * <li value = "0"> Default (as initialised).</li>
                 * <li value = "1"> \c DIMENSION.</li>
                 * </ol>
                 */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfPoint *p1 = NULL;

        /* Do some basic checks. */
        if (dimension == NULL)
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
        p1->x0 = dimension->x4;
        p1->y0 = dimension->y4;
        p1->z0 = dimension->z4;
        switch (inheritance)
        {
                case 0:
                        /* Do nothing. */
                        break;
                case 1:
                        if (dimension->linetype != NULL)
                        {
                                p1->linetype = strdup (dimension->linetype);
                        }
                        if (dimension->layer != NULL)
                        {
                                p1->layer = strdup (dimension->layer);
                        }
                        p1->thickness = dimension->thickness;
                        p1->linetype_scale = dimension->linetype_scale;
                        p1->visibility = dimension->visibility;
                        p1->color = dimension->color;
                        p1->paperspace = dimension->paperspace;
                        if (dimension->dictionary_owner_soft != NULL)
                        {
                                p1->dictionary_owner_soft = strdup (dimension->dictionary_owner_soft);
                        }
                        if (dimension->dictionary_owner_hard != NULL)
                        {
                                p1->dictionary_owner_hard = strdup (dimension->dictionary_owner_hard);
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
 * \brief Set the definition point for linear and angular dimensions for
 * a DXF \c DIMENSION entity.
 *
 * \return a pointer to a DXF \c DIMENSION entity.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfDimension *
dxf_dimension_set_x4
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        DxfPoint *point
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimension->x4 = point->x0;
        dimension->y4 = point->y0;
        dimension->z4 = point->z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the definition point for diameter, radius, and angular
 * dimensions for a DXF \c DIMENSION entity.
 *
 * \return the definition point for linear and angular dimensions.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfPoint *
dxf_dimension_get_x5
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        int id_code,
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file. */
        int inheritance
                /*!< Inherit layer, linetype, color and other relevant
                 * properties from either:
                 * <ol>
                 * <li value = "0"> Default (as initialised).</li>
                 * <li value = "1"> \c DIMENSION.</li>
                 * </ol>
                 */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfPoint *p1 = NULL;

        /* Do some basic checks. */
        if (dimension == NULL)
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
        p1->x0 = dimension->x5;
        p1->y0 = dimension->y5;
        p1->z0 = dimension->z5;
        switch (inheritance)
        {
                case 0:
                        /* Do nothing. */
                        break;
                case 1:
                        if (dimension->linetype != NULL)
                        {
                                p1->linetype = strdup (dimension->linetype);
                        }
                        if (dimension->layer != NULL)
                        {
                                p1->layer = strdup (dimension->layer);
                        }
                        p1->thickness = dimension->thickness;
                        p1->linetype_scale = dimension->linetype_scale;
                        p1->visibility = dimension->visibility;
                        p1->color = dimension->color;
                        p1->paperspace = dimension->paperspace;
                        if (dimension->dictionary_owner_soft != NULL)
                        {
                                p1->dictionary_owner_soft = strdup (dimension->dictionary_owner_soft);
                        }
                        if (dimension->dictionary_owner_hard != NULL)
                        {
                                p1->dictionary_owner_hard = strdup (dimension->dictionary_owner_hard);
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
 * \brief Set the definition point for diameter, radius, and angular
 * dimensions for a DXF \c DIMENSION entity.
 *
 * \return a pointer to a DXF \c DIMENSION entity.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfDimension *
dxf_dimension_set_x5
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        DxfPoint *point
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimension->x5 = point->x0;
        dimension->y5 = point->y0;
        dimension->z5 = point->z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the point defining dimension arc for angular dimensions
 * for a DXF \c DIMENSION entity.
 *
 * \return the point defining dimension arc for angular dimensions.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfPoint *
dxf_dimension_get_x6
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        int id_code,
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file. */
        int inheritance
                /*!< Inherit layer, linetype, color and other relevant
                 * properties from either:
                 * <ol>
                 * <li value = "0"> Default (as initialised).</li>
                 * <li value = "1"> \c DIMENSION.</li>
                 * </ol>
                 */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfPoint *p1 = NULL;

        /* Do some basic checks. */
        if (dimension == NULL)
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
        p1->x0 = dimension->x6;
        p1->y0 = dimension->y6;
        p1->z0 = dimension->z6;
        switch (inheritance)
        {
                case 0:
                        /* Do nothing. */
                        break;
                case 1:
                        if (dimension->linetype != NULL)
                        {
                                p1->linetype = strdup (dimension->linetype);
                        }
                        if (dimension->layer != NULL)
                        {
                                p1->layer = strdup (dimension->layer);
                        }
                        p1->thickness = dimension->thickness;
                        p1->linetype_scale = dimension->linetype_scale;
                        p1->visibility = dimension->visibility;
                        p1->color = dimension->color;
                        p1->paperspace = dimension->paperspace;
                        if (dimension->dictionary_owner_soft != NULL)
                        {
                                p1->dictionary_owner_soft = strdup (dimension->dictionary_owner_soft);
                        }
                        if (dimension->dictionary_owner_hard != NULL)
                        {
                                p1->dictionary_owner_hard = strdup (dimension->dictionary_owner_hard);
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
 * \brief Set the point defining dimension arc for angular dimensions
 * for a DXF \c DIMENSION entity.
 *
 * \return a pointer to a DXF \c DIMENSION entity.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfDimension *
dxf_dimension_set_x6
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        DxfPoint *point
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimension->x6 = point->x0;
        dimension->y6 = point->y0;
        dimension->z6 = point->z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the leader length from a DXF \c DIMENSION entity.
 *
 * \return leader length.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
double
dxf_dimension_get_leader_length
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        double result;

        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = dimension->leader_length;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the leader length for a DXF \c DIMENSION entity.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfDimension *
dxf_dimension_set_leader_length
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        double leader_length
                /*!< the leader length to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimension->leader_length = leader_length;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the text line spacing factor from a DXF \c DIMENSION entity.
 *
 * \return text line spacing factor.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
double
dxf_dimension_get_text_line_spacing_factor
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        double result;

        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = dimension->text_line_spacing_factor;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the text line spacing factor for a DXF \c DIMENSION entity.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfDimension *
dxf_dimension_set_text_line_spacing_factor
(
        DxfDimension *dimension,
                /*!< a pointer to a DXF \c DIMENSION entity. */
        double text_line_spacing_factor
                /*!< the text line spacing factor to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimension->text_line_spacing_factor = text_line_spacing_factor;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimension);
}


/*!
 * \brief Get the tactual measurement from a DXF \c DIMENSION entity.
 *
 * \return actual_measurement.
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
double
dxf_dimension_get_actual_measurement
(
        DxfDimension *dimension
                /*!< a pointer to a DXF \c DIMENSION entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        double result;

        /* Do some basic checks. */
        if (dimension == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = dimension->actual_measurement;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/* EOF */
