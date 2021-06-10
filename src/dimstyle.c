/*!
 * \file dimstyle.c
 *
 * \author Copyright (C) 2012, 2014, 2015, 2016, 2017, 2018, 2019, 2020,
 * 2021 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF dimension style table (\c DIMSTYLE).
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
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


#include "dimstyle.h"


/*!
 * \brief Allocate memory for a DXF \c DIMSTYLE.
 *
 * Fill the memory contents with zeros.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfDimStyle *
dxf_dimstyle_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfDimStyle *dimstyle = NULL;
        size_t size;

        size = sizeof (DxfDimStyle);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dimstyle = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                dimstyle = NULL;
        }
        else
        {
                memset (dimstyle, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c
 * DIMSTYLE entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfDimStyle *
dxf_dimstyle_init
(
        DxfDimStyle *dimstyle
                /*!< Pointer to the memory occupied by the DXF \c
                 * DIMSTYLE table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                dimstyle = dxf_dimstyle_new ();
        }
        if (dimstyle == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory.\n")),
                __FUNCTION__);
              return (NULL);
        }
        dimstyle->dimstyle_name = strdup ("");
        dimstyle->dimpost = strdup ("");
        dimstyle->dimapost = strdup ("");
        dimstyle->dimblk = strdup ("");
        dimstyle->dimblk1 = strdup ("");
        dimstyle->dimblk2 = strdup ("");
        dimstyle->dimscale = 0.0;
        dimstyle->dimasz = 0.0;
        dimstyle->dimexo = 0.0;
        dimstyle->dimdli = 0.0;
        dimstyle->dimexe = 0.0;
        dimstyle->dimrnd = 0.0;
        dimstyle->dimdle = 0.0;
        dimstyle->dimtp = 0.0;
        dimstyle->dimtm = 0.0;
        dimstyle->flag = 0;
        dimstyle->dimtol = 0;
        dimstyle->dimlim = 0;
        dimstyle->dimtih = 0;
        dimstyle->dimtoh = 0;
        dimstyle->dimse1 = 0;
        dimstyle->dimse2 = 0;
        dimstyle->dimtad = 0;
        dimstyle->dimzin = 0;
        dimstyle->dimtxt = 0.0;
        dimstyle->dimcen = 0.0;
        dimstyle->dimtsz = 0.0;
        dimstyle->dimaltf = 0.0;
        dimstyle->dimlfac = 0.0;
        dimstyle->dimtvp = 0.0;
        dimstyle->dimtfac = 0.0;
        dimstyle->dimgap = 0.0;
        dimstyle->dimalt = 0;
        dimstyle->dimaltd = 0;
        dimstyle->dimtofl = 0;
        dimstyle->dimsah = 0;
        dimstyle->dimtix = 0;
        dimstyle->dimsoxd = 0;
        dimstyle->dimclrd = DXF_COLOR_BYLAYER;
        dimstyle->dimclre = DXF_COLOR_BYLAYER;
        dimstyle->dimclrt = DXF_COLOR_BYLAYER;
        dimstyle->dictionary_owner_soft = strdup ("");
        dimstyle->object_owner_soft = strdup ("");
        dimstyle->dictionary_owner_hard = strdup ("");
        dimstyle->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle);
}


/*!
 * \brief Read data from a DXF file into a DXF \c DIMSTYLE table.
 *
 * The last line read from file contained the string "DIMSTYLE". \n
 * Now follows some data for the \c DIMSTYLE, to be terminated with a
 * "  0" string announcing the following table, or the end of the
 * \c TABLES section marker \c ENDTAB. \n
 *
 * \return a pointer to \c dimstyle.
 */
DxfDimStyle *
dxf_dimstyle_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfDimStyle *dimstyle
                /*!< Pointer to the memory occupied by the DXF \c
                 * DIMSTYLE table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *temp_string = NULL;
        int iter330;

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
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                dimstyle = dxf_dimstyle_init (dimstyle);
        }
        iter330 = 0;
        (fp->line_number)++;
        fscanf (fp->fp, "%[^\n]", temp_string);
        while (strcmp (temp_string, "0") != 0)
        {
                if (ferror (fp->fp))
                {
                        fprintf (stderr,
                          (_("Error in %s () while reading from: %s in line: %d.\n")),
                          __FUNCTION__, fp->filename, fp->line_number);
                        /* Clean up. */
                        free (temp_string);
                        fclose (fp->fp);
                        return (NULL);
                }
                if (strcmp (temp_string, "2") == 0)
                {
                        /* Now follows a string containing a dimension
                         * style name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, dimstyle->dimstyle_name);
                }
                else if (strcmp (temp_string, "3") == 0)
                {
                        /* Now follows a string containing a general
                         * dimensioning suffix. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, dimstyle->dimpost);
                }
                else if (strcmp (temp_string, "4") == 0)
                {
                        /* Now follows a string containing an alternate
                         * dimensioning suffix. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, dimstyle->dimapost);
                }
                else if ((fp->acad_version_number < AutoCAD_2000)
                        && (strcmp (temp_string, "5") == 0))
                {
                        /* Now follows a string containing an arrow
                         * block name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, dimstyle->dimblk);
                }
                else if ((fp->acad_version_number < AutoCAD_2000)
                        && (strcmp (temp_string, "6") == 0))
                {
                        /* Now follows a string containing a first arrow
                         * block name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, dimstyle->dimblk1);
                }
#if 0
/*!
 * \todo For AutoCAD versions > 2000 the value of group code 6 has to be
 * tested before overwriting the id_code.
 */
                else if ((fp->acad_version_number >= AutoCAD_2000)
                        && (strcmp (temp_string, "6") == 0))
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", &dimstyle->id_code);
                }
#endif
                else if ((fp->acad_version_number < AutoCAD_2000)
                        && (strcmp (temp_string, "7") == 0))
                {
                        /* Now follows a string containing a first arrow
                         * block name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, dimstyle->dimblk2);
                }
#if 0
/*!
 * \todo For AutoCAD versions > 2000 the value of group code 7 has to be
 * tested before overwriting the id_code.
 */
                else if ((fp->acad_version_number >= AutoCAD_2000)
                        && (strcmp (temp_string, "7") == 0))
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", &dimstyle->id_code);
                }
#endif
                else if (strcmp (temp_string, "40") == 0)
                {
                        /* Now follows a string containing an overall
                         * dimensioning scale factor. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimstyle->dimscale);
                }
                else if (strcmp (temp_string, "41") == 0)
                {
                        /* Now follows a string containing a
                         * dimensioning arrow size. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimstyle->dimasz);
                }
                else if (strcmp (temp_string, "42") == 0)
                {
                        /* Now follows a string containing a
                         * extension line offset. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimstyle->dimexo);
                }
                else if (strcmp (temp_string, "43") == 0)
                {
                        /* Now follows a string containing a
                         * dimension line increment. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimstyle->dimdli);
                }
                else if (strcmp (temp_string, "44") == 0)
                {
                        /* Now follows a string containing a
                         * extension line extension. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimstyle->dimexe);
                }
                else if (strcmp (temp_string, "45") == 0)
                {
                        /* Now follows a string containing a
                         * rounding value for dimension distances. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimstyle->dimrnd);
                }
                else if (strcmp (temp_string, "46") == 0)
                {
                        /* Now follows a string containing a
                         * dimension line extension. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimstyle->dimdle);
                }
                else if (strcmp (temp_string, "47") == 0)
                {
                        /* Now follows a string containing a
                         * plus tolerance. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimstyle->dimtp);
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing a
                         * minus tolerance. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimstyle->dimtm);
                }
                else if (strcmp (temp_string, "70") == 0)
                {
                        /* Now follows a string containing a flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &dimstyle->flag);
                }
                else if (strcmp (temp_string, "71") == 0)
                {
                        /* Now follows a string containing a dimension
                         * tolerances flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &dimstyle->dimtol);
                }
                else if (strcmp (temp_string, "72") == 0)
                {
                        /* Now follows a string containing a dimension
                         * limits flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &dimstyle->dimlim);
                }
                else if (strcmp (temp_string, "73") == 0)
                {
                        /* Now follows a string containing a dimension
                         * text inside horizontal flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &dimstyle->dimtih);
                }
                else if (strcmp (temp_string, "74") == 0)
                {
                        /* Now follows a string containing a dimension
                         * text outside horizontal flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &dimstyle->dimtoh);
                }
                else if (strcmp (temp_string, "75") == 0)
                {
                        /* Now follows a string containing a first
                         * extension line suppression flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &dimstyle->dimse1);
                }
                else if (strcmp (temp_string, "76") == 0)
                {
                        /* Now follows a string containing a second
                         * extension line suppression flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &dimstyle->dimse2);
                }
                else if (strcmp (temp_string, "77") == 0)
                {
                        /* Now follows a string containing a text above
                         * dimension line flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &dimstyle->dimtad);
                }
                else if (strcmp (temp_string, "78") == 0)
                {
                        /* Now follows a string containing a zero
                         * suppression for "feet & inch" dimensions
                         * flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &dimstyle->dimzin);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if ((strcmp (temp_string, "AcDbSymbolTableRecord") != 0)
                        && (strcmp (temp_string, "AcDbDimStyleTableRecord") != 0))
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () found a bad subclass marker in: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                        }
                }
                else if (strcmp (temp_string, "105") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", (uint *) &dimstyle->id_code);
                }
                else if (strcmp (temp_string, "140") == 0)
                {
                        /* Now follows a string containing a
                         * dimensioning text height. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimstyle->dimtxt);
                }
                else if (strcmp (temp_string, "141") == 0)
                {
                        /* Now follows a string containing a size of
                         * center mark/lines. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimstyle->dimcen);
                }
                else if (strcmp (temp_string, "142") == 0)
                {
                        /* Now follows a string containing a
                         * dimensioning tick size: 0 = no ticks. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimstyle->dimtsz);
                }
                else if (strcmp (temp_string, "143") == 0)
                {
                        /* Now follows a string containing a
                         * alternate unit scale factor. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimstyle->dimaltf);
                }
                else if (strcmp (temp_string, "144") == 0)
                {
                        /* Now follows a string containing a linear
                         * measurements scale factor. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimstyle->dimlfac);
                }
                else if (strcmp (temp_string, "145") == 0)
                {
                        /* Now follows a string containing a text
                         * vertical position. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimstyle->dimtvp);
                }
                else if (strcmp (temp_string, "146") == 0)
                {
                        /* Now follows a string containing a dimension
                         * tolerance display scale factor. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimstyle->dimtfac);
                }
                else if (strcmp (temp_string, "147") == 0)
                {
                        /* Now follows a string containing a dimension
                         * line gap. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dimstyle->dimgap);
                }
                else if (strcmp (temp_string, "170") == 0)
                {
                        /* Now follows a string containing a alternate
                         * unit dimensioning flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &dimstyle->dimalt);
                }
                else if (strcmp (temp_string, "171") == 0)
                {
                        /* Now follows a string containing a alternate
                         * unit decimal places. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &dimstyle->dimaltd);
                }
                else if (strcmp (temp_string, "172") == 0)
                {
                        /* Now follows a string containing a text
                         * outside extensions, force line extensions
                         * between extensions flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &dimstyle->dimtofl);
                }
                else if (strcmp (temp_string, "173") == 0)
                {
                        /* Now follows a string containing a use
                         * separate arrow blocks flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &dimstyle->dimsah);
                }
                else if (strcmp (temp_string, "174") == 0)
                {
                        /* Now follows a string containing a force text
                         * inside extensions flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &dimstyle->dimtix);
                }
                else if (strcmp (temp_string, "175") == 0)
                {
                        /* Now follows a string containing a suppress
                         * outside-extensions dimension lines flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &dimstyle->dimsoxd);
                }
                else if (strcmp (temp_string, "176") == 0)
                {
                        /* Now follows a string containing a dimension
                         * line color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &dimstyle->dimclrd);
                }
                else if (strcmp (temp_string, "177") == 0)
                {
                        /* Now follows a string containing a dimension
                         * extension line color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &dimstyle->dimclre);
                }
                else if (strcmp (temp_string, "178") == 0)
                {
                        /* Now follows a string containing a dimension
                         * text color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &dimstyle->dimclrt);
                }
                else if (strcmp (temp_string, "270") == 0)
                {
                        /* Now follows a string containing a units
                         * format for all dimension style family members
                         * except angular. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &dimstyle->dimunit);
                }
                else if (strcmp (temp_string, "271") == 0)
                {
                        /* Now follows a string containing a number of
                         * decimal places for the tolerance values of
                         * a primary units dimension. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &dimstyle->dimdec);
                }
                else if (strcmp (temp_string, "272") == 0)
                {
                        /* Now follows a string containing a number of
                         * decimal places to display the tolerance
                         * values. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &dimstyle->dimtdec);
                }
                else if (strcmp (temp_string, "273") == 0)
                {
                        /* Now follows a string containing a units
                         * format for alternate units of all dimension
                         * style family members except angular. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &dimstyle->dimaltu);
                }
                else if (strcmp (temp_string, "274") == 0)
                {
                        /* Now follows a string containing a number of
                         * decimal places for tolerance values of an
                         * alternate units dimension. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &dimstyle->dimalttd);
                }
                else if (strcmp (temp_string, "275") == 0)
                {
                        /* Now follows a string containing an angle
                         * format for angular dimensions. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &dimstyle->dimaunit);
                }
                else if (strcmp (temp_string, "280") == 0)
                {
                        /* Now follows a string containing a horizontal
                         * dimension text position. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &dimstyle->dimjust);
                }
                else if (strcmp (temp_string, "281") == 0)
                {
                        /* Now follows a string containing suppression
                         * of first extension line. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &dimstyle->dimsd1);
                }
                else if (strcmp (temp_string, "282") == 0)
                {
                        /* Now follows a string containing suppression
                         * of second extension line. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &dimstyle->dimsd2);
                }
                else if (strcmp (temp_string, "283") == 0)
                {
                        /* Now follows a string containing vertical
                         * justification for tolerance values. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &dimstyle->dimtolj);
                }
                else if (strcmp (temp_string, "284") == 0)
                {
                        /* Now follows a string containing suppression
                         * of zeros for tolerance values. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &dimstyle->dimtzin);
                }
                else if (strcmp (temp_string, "285") == 0)
                {
                        /* Now follows a string containing toggles
                         * suppression of zeros for alternate unit
                         * dimension values. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &dimstyle->dimaltz);
                }
                else if (strcmp (temp_string, "286") == 0)
                {
                        /* Now follows a string containing toggles
                         * suppression of zeros for tolerance values. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &dimstyle->dimalttz);
                }
                else if (strcmp (temp_string, "287") == 0)
                {
                        /* Now follows a string containing placement of
                         * text and arrowheads. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &dimstyle->dimfit);
                }
                else if (strcmp (temp_string, "288") == 0)
                {
                        /* Now follows a string containing cursor
                         * functionality for user positioned text. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &dimstyle->dimupt);
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        if (iter330 == 0)
                        {
                                /* Now follows a string containing a soft-pointer
                                 * ID/handle to owner dictionary. */
                                (fp->line_number)++;
                                fscanf (fp->fp, DXF_MAX_STRING_FORMAT, dimstyle->dictionary_owner_soft);
                        }
                        if (iter330 == 1)
                        {
                                /* Now follows a string containing a soft-pointer
                                 * ID/handle to owner object. */
                                (fp->line_number)++;
                                fscanf (fp->fp, DXF_MAX_STRING_FORMAT, dimstyle->object_owner_soft);
                        }
                        iter330++;
                }
                else if (strcmp (temp_string, "340") == 0)
                {
                        /* Now follows a string containing dimension
                         * text style. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, dimstyle->dimtxsty);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, dimstyle->dictionary_owner_hard);
                }
        }
        /* Handle omitted members and/or illegal values. */
        if (strcmp (dimstyle->dimstyle_name, "") == 0)
        {
                fprintf (stderr,
                  (_("Error in %s () dimstyle_name value is empty.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (temp_string);
                return (NULL);
        }
        /* Clean up. */
        free (temp_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle);
}


/*!
 * \brief Write DXF output for a DXF \c DIMSTYLE table.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_dimstyle_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfDimStyle *dimstyle
                /*!< Pointer to the memory occupied by the DXF \c
                 * DIMSTYLE table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("DIMSTYLE");

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
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (strcmp (dimstyle->dimstyle_name, "") == 0)
        {
                fprintf (stderr,
                  (_("Error in %s () dimstyle_name value is empty for the %s entity.\n")),
                  __FUNCTION__, dxf_entity_name);
                fprintf (stderr,
                  (_("\tskipping %s table.\n")),
                  dxf_entity_name);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (!dimstyle->dimstyle_name)
        {
                fprintf (stderr,
                  (_("Error in %s () dimstyle_name value is NULL for the %s entity.\n")),
                  __FUNCTION__, dxf_entity_name);
                fprintf (stderr,
                  (_("\tskipping %s table.\n")),
                  dxf_entity_name);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (fp->acad_version_number < AutoCAD_13)
        {
                fprintf (stderr,
                  (_("Warning in %s () illegal DXF version for this %s entity with id-code: %x.\n")),
                  __FUNCTION__, dxf_entity_name, dimstyle->id_code);
        }
        if (!dimstyle->dimpost)
        {
                dimstyle->dimpost = strdup ("");
        }
        if (!dimstyle->dimapost)
        {
                dimstyle->dimapost = strdup ("");
        }
        if (!dimstyle->dimblk)
        {
                dimstyle->dimblk = strdup ("");
        }
        if (!dimstyle->dimblk1)
        {
                dimstyle->dimblk1 = strdup ("");
        }
        if (!dimstyle->dimblk2)
        {
                dimstyle->dimblk2 = strdup ("");
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (dimstyle->id_code != -1)
        {
                fprintf (fp->fp, "105\n%x\n", dimstyle->id_code);
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
        if ((strcmp (dimstyle->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", dimstyle->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (dimstyle->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", dimstyle->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (dimstyle->object_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_2000))
        {
                fprintf (fp->fp, "330\n%s\n", dimstyle->object_owner_soft);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbSymbolTableRecord\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbDimStyleTableRecord\n");
        }
        fprintf (fp->fp, "  2\n%s\n", dimstyle->dimstyle_name);
        fprintf (fp->fp, " 70\n%hd\n", dimstyle->flag);
        fprintf (fp->fp, "  3\n%s\n", dimstyle->dimpost);
        fprintf (fp->fp, "  4\n%s\n", dimstyle->dimapost);
        if (fp->acad_version_number < AutoCAD_2000)
        {
                fprintf (fp->fp, "  5\n%s\n", dimstyle->dimblk);
        }
        if (fp->acad_version_number < AutoCAD_2000)
        {
                fprintf (fp->fp, "  6\n%s\n", dimstyle->dimblk1);
        }
        if (fp->acad_version_number < AutoCAD_2000)
        {
                fprintf (fp->fp, "  7\n%s\n", dimstyle->dimblk2);
        }
        fprintf (fp->fp, " 40\n%f\n", dimstyle->dimscale);
        fprintf (fp->fp, " 41\n%f\n", dimstyle->dimasz);
        fprintf (fp->fp, " 42\n%f\n", dimstyle->dimexo);
        fprintf (fp->fp, " 43\n%f\n", dimstyle->dimdli);
        fprintf (fp->fp, " 44\n%f\n", dimstyle->dimexe);
        fprintf (fp->fp, " 45\n%f\n", dimstyle->dimrnd);
        fprintf (fp->fp, " 46\n%f\n", dimstyle->dimdle);
        fprintf (fp->fp, " 47\n%f\n", dimstyle->dimtp);
        fprintf (fp->fp, " 48\n%f\n", dimstyle->dimtm);
        fprintf (fp->fp, "140\n%f\n", dimstyle->dimtxt);
        fprintf (fp->fp, "141\n%f\n", dimstyle->dimcen);
        fprintf (fp->fp, "142\n%f\n", dimstyle->dimtsz);
        fprintf (fp->fp, "143\n%f\n", dimstyle->dimaltf);
        fprintf (fp->fp, "144\n%f\n", dimstyle->dimlfac);
        fprintf (fp->fp, "145\n%f\n", dimstyle->dimtvp);
        fprintf (fp->fp, "146\n%f\n", dimstyle->dimtfac);
        fprintf (fp->fp, "147\n%f\n", dimstyle->dimgap);
        fprintf (fp->fp, " 71\n%hd\n", dimstyle->dimtol);
        fprintf (fp->fp, " 72\n%hd\n", dimstyle->dimlim);
        fprintf (fp->fp, " 73\n%hd\n", dimstyle->dimtih);
        fprintf (fp->fp, " 74\n%hd\n", dimstyle->dimtoh);
        fprintf (fp->fp, " 75\n%hd\n", dimstyle->dimse1);
        fprintf (fp->fp, " 76\n%hd\n", dimstyle->dimse2);
        fprintf (fp->fp, " 77\n%hd\n", dimstyle->dimtad);
        fprintf (fp->fp, " 78\n%hd\n", dimstyle->dimzin);
        fprintf (fp->fp, "170\n%hd\n", dimstyle->dimalt);
        fprintf (fp->fp, "171\n%hd\n", dimstyle->dimaltd);
        fprintf (fp->fp, "172\n%hd\n", dimstyle->dimtofl);
        fprintf (fp->fp, "173\n%hd\n", dimstyle->dimsah);
        fprintf (fp->fp, "174\n%hd\n", dimstyle->dimtix);
        fprintf (fp->fp, "175\n%hd\n", dimstyle->dimsoxd);
        fprintf (fp->fp, "176\n%hd\n", dimstyle->dimclrd);
        fprintf (fp->fp, "177\n%hd\n", dimstyle->dimclre);
        fprintf (fp->fp, "178\n%dh\n", dimstyle->dimclrt);
        if ((fp->acad_version_number >= AutoCAD_13)
          && (fp->acad_version_number < AutoCAD_2000))
        {
                fprintf (fp->fp, "270\n%hd\n", dimstyle->dimunit);
                fprintf (fp->fp, "271\n%hd\n", dimstyle->dimdec);
                fprintf (fp->fp, "272\n%hd\n", dimstyle->dimtdec);
                fprintf (fp->fp, "273\n%hd\n", dimstyle->dimaltu);
                fprintf (fp->fp, "274\n%hd\n", dimstyle->dimalttd);
                fprintf (fp->fp, "340\n%s\n", dimstyle->dimtxsty);
                fprintf (fp->fp, "275\n%hd\n", dimstyle->dimaunit);
                fprintf (fp->fp, "280\n%hd\n", dimstyle->dimjust);
                fprintf (fp->fp, "281\n%hd\n", dimstyle->dimsd1);
                fprintf (fp->fp, "282\n%hd\n", dimstyle->dimsd2);
                fprintf (fp->fp, "283\n%hd\n", dimstyle->dimtolj);
                fprintf (fp->fp, "284\n%hd\n", dimstyle->dimtzin);
                fprintf (fp->fp, "285\n%hd\n", dimstyle->dimaltz);
                fprintf (fp->fp, "286\n%hd\n", dimstyle->dimalttz);
                fprintf (fp->fp, "287\n%hd\n", dimstyle->dimfit);
                fprintf (fp->fp, "288\n%hd\n", dimstyle->dimupt);
                fprintf (fp->fp, "  0\nENDTAB\n");
        }
        /* Clean up. */
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c DIMSTYLE and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_dimstyle_free
(
        DxfDimStyle *dimstyle
                /*!< Pointer to the memory occupied by the DXF \c
                 * DIMSTYLE table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dimstyle->next != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to next was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (dimstyle->dimstyle_name);
        free (dimstyle->dimpost);
        free (dimstyle->dimapost);
        free (dimstyle->dimblk);
        free (dimstyle->dimblk1);
        free (dimstyle->dimblk2);
        free (dimstyle->dictionary_owner_soft);
        free (dimstyle->object_owner_soft);
        free (dimstyle->dictionary_owner_hard);
        free (dimstyle);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c DIMSTYLE symbol table and all their data fields.
 */
void
dxf_dimstyle_free_list
(
        DxfDimStyle *dimstyles
                /*!< pointer to the single linked list of DXF
                 * \c DIMSTYLE symbol tables. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (dimstyles == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (dimstyles != NULL)
        {
                DxfDimStyle *iter = (DxfDimStyle *) dimstyles->next;
                dxf_dimstyle_free (dimstyles);
                dimstyles = (DxfDimStyle *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the dimension style name string value (\c dimstyle_name)
 * from this DXF dimension style symbol table (\c DIMSTYLE).
 *
 * \return the dimension style name string value (\c dimstyle_name).
 */
char *
dxf_dimstyle_get_dimstyle_name
(
        DxfDimStyle *dimstyle
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimstyle->dimstyle_name == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (dimstyle->dimstyle_name));
}


/*!
 * \brief Set the dimension style name string value (\c dimstyle_name)
 * for a DXF dimension style symbol table (\c DIMSTYLE).
 *
 * \return a pointer to the DXF \c DIMSTYLE symbol table if
 * successful, a \c NULL when an error occurred.
 *
 * \warning No testing for the contents of the \c dimstyle_name
 * member of the \c DxfDimstyle struct is performed.\n
 *
 * \warning The passed \c dimstyle_name variable is not freed by this
 * function and needs to be freed by the caller.
 */
DxfDimStyle *
dxf_dimstyle_set_dimstyle_name
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
        char *dimstyle_name
                /*!< a pointer to a dimension style name string value
                 * (\c dimstyle_name). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
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
        dimstyle->dimstyle_name = strdup (dimstyle_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle);
}


/*!
 * \brief Get the general dimensioning suffix string value (\c dimpost)
 * from this DXF dimension style symbol table (\c DIMSTYLE).
 *
 * \return the general dimensioning suffix string value (\c dimpost).
 */
char *
dxf_dimstyle_get_dimpost
(
        DxfDimStyle *dimstyle
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimstyle->dimpost == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (dimstyle->dimpost));
}


/*!
 * \brief Set the general dimensioning suffix string value (\c dimpost)
 * for this DXF dimension style symbol table (\c DIMSTYLE).
 *
 * \return a pointer to the DXF \c DIMSTYLE symbol table if
 * successful, a \c NULL when an error occurred.
 *
 * \warning No testing for the contents of the \c dimpost
 * member of the \c DxfDimstyle struct is performed.\n
 *
 * \warning The passed \c dimpost variable is not freed by this function
 * and needs to be freed by the caller.
 */
DxfDimStyle *
dxf_dimstyle_set_dimpost
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
        char *dimpost
                /*!< a pointer to a general dimensioning suffix string
                 * value (\c dimpost). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimpost == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimstyle->dimpost = strdup (dimpost);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle);
}


/*!
 * \brief Get the alternate dimensioning suffix string value
 * (\c dimapost) from this DXF dimension style symbol table (\c DIMSTYLE).
 *
 * \return the alternate dimensioning suffix string value (\c dimapost).
 */
char *
dxf_dimstyle_get_dimapost
(
        DxfDimStyle *dimstyle
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimstyle->dimapost == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (dimstyle->dimapost));
}


/*!
 * \brief Set the alternate dimensioning suffix string value
 * (\c dimapost) for this DXF dimension style symbol table (\c DIMSTYLE).
 *
 * \return a pointer to the DXF \c DIMSTYLE symbol table if
 * successful, a \c NULL when an error occurred.
 *
 * \warning No testing for the contents of the \c dimapost
 * member of the \c DxfDimstyle struct is performed.\n
 *
 * \warning The passed \c dimapost variable is not freed by this function
 * and needs to be freed by the caller.
 */
DxfDimStyle *
dxf_dimstyle_set_dimapost
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
        char *dimapost
                /*!< a pointer to a alternate dimensioning suffix string
                 * value (\c dimapost). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimapost == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimstyle->dimapost = strdup (dimapost);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle);
}


/*!
 * \brief Get the arrow block name string value (\c dimblk) from this
 * DXF dimension style symbol table (\c DIMSTYLE).
 *
 * \return the arrow block name string value (\c dimblk).
 */
char *
dxf_dimstyle_get_dimblk
(
        DxfDimStyle *dimstyle
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimstyle->dimblk == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (dimstyle->dimblk));
}


/*!
 * \brief Set the arrow block name string value (\c dimblk) for this DXF
 * dimension style symbol table (\c DIMSTYLE).
 *
 * \return a pointer to the DXF \c DIMSTYLE symbol table if
 * successful, a \c NULL when an error occurred.
 *
 * \warning No testing for the contents of the \c dimblk member of the
 * \c DxfDimstyle struct is performed.\n
 *
 * \warning The passed \c dimblk variable is not freed by this function
 * and needs to be freed by the caller.
 */
DxfDimStyle *
dxf_dimstyle_set_dimblk
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
        char *dimblk
                /*!< arrow block name string value (\c dimblk). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimblk == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimstyle->dimblk = strdup (dimblk);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle);
}


/*!
 * \brief Get the first arrow block name string value (\c dimblk1) from
 * this DXF dimension style symbol table (\c DIMSTYLE).
 *
 * \return the first arrow block name string value (\c dimblk1).
 */
char *
dxf_dimstyle_get_dimblk1
(
        DxfDimStyle *dimstyle
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimstyle->dimblk1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (dimstyle->dimblk1));
}


/*!
 * \brief Set the first arrow block name string value (\c dimblk1) for
 * this DXF dimension style symbol table (\c DIMSTYLE).
 *
 * \return a pointer to the DXF \c DIMSTYLE symbol table if
 * successful, a \c NULL when an error occurred.
 *
 * \warning No testing for the contents of the \c dimblk1 member of the
 * \c DxfDimstyle struct is performed.\n
 *
 * \warning The passed \c dimblk1 variable is not freed by this function
 * and needs to be freed by the caller.
 */
DxfDimStyle *
dxf_dimstyle_set_dimblk1
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
        char *dimblk1
                /*!< a pointer to the first arrow block name string
                 * value (\c dimblk1). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimblk1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimstyle->dimblk1 = strdup (dimblk1);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle);
}


/*!
 * \brief Get the second arrow block name string value (\c dimblk2) from
 * this DXF dimension style symbol table (\c DIMSTYLE).
 *
 * \return the second arrow block name string value (\c dimblk2).
 */
char *
dxf_dimstyle_get_dimblk2
(
        DxfDimStyle *dimstyle
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimstyle->dimblk2 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (dimstyle->dimblk2));
}


/*!
 * \brief Set the second arrow block name string value (\c dimblk2) for
 * this DXF dimension style symbol table (\c DIMSTYLE).
 *
 * \return a pointer to the DXF \c DIMSTYLE symbol table if
 * successful, a \c NULL when an error occurred.
 *
 * \warning No testing for the contents of the \c dimblk2 member of the
 * \c DxfDimstyle struct is performed.\n
 *
 * \warning The passed \c dimblk2 variable is not freed by this function
 * and needs to be freed by the caller.
 */
DxfDimStyle *
dxf_dimstyle_set_dimblk2
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
        char *dimblk2
                /*!< a pointer to the second arrow block name string
                 * value (\c dimblk2). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimblk2 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimstyle->dimblk2 = strdup (dimblk2);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle);
}


/*!
 * \brief Get the overall dimensioning scale factor value (\c dimscale)
 * from a DXF dimension style symbol table (\c DIMSTYLE).
 *
 * \return the overall dimensioning scale factor value (\c dimscale).
 */
double
dxf_dimstyle_get_dimscale
(
        DxfDimStyle *dimstyle
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dimstyle->dimscale == 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle->dimscale);
}


/*!
 * \brief Set the overall dimensioning scale factor value (\c dimscale)
 * for a DXF dimension style symbol table (\c DIMSTYLE).
 *
 * \return a pointer to \c dimstyle when sucessful, \c NULL when an error
 * occurred.
 */
DxfDimStyle *
dxf_dimstyle_set_dimscale
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
        double dimscale
                /*!< the overall dimensioning scale factor value
                 * (\c dimscale) to be set for the symbol table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimscale == 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero value was passed.\n")),
                  __FUNCTION__);
        }
        dimstyle->dimscale = dimscale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle);
}


/*!
 * \brief Get the dimensioning arrow size value (\c dimasz) from a DXF
 * dimension style symbol table (\c DIMSTYLE).
 *
 * \return the dimensioning arrow size value (\c dimasz).
 */
double
dxf_dimstyle_get_dimasz
(
        DxfDimStyle *dimstyle
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dimstyle->dimasz == 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle->dimasz);
}


/*!
 * \brief Set the dimensioning arrow size value (\c dimasz) for a DXF
 * dimension style symbol table (\c DIMSTYLE).
 *
 * \return a pointer to \c dimstyle when sucessful, \c NULL when an error
 * occurred.
 */
DxfDimStyle *
dxf_dimstyle_set_dimasz
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
        double dimasz
                /*!< the dimensioning arrow size value (\c dimasz) to be
                 * set for the symbol table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimasz == 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero value was passed.\n")),
                  __FUNCTION__);
        }
        dimstyle->dimasz = dimasz;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle);
}


/*!
 * \brief Get the extension line offset value (\c dimexo) from a DXF
 * dimension style symbol table (\c DIMSTYLE).
 *
 * \return the extension line offset value (\c dimexo).
 */
double
dxf_dimstyle_get_dimexo
(
        DxfDimStyle *dimstyle
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle->dimexo);
}


/*!
 * \brief Set the extension line offset value (\c dimexo) for a DXF
 * dimension style symbol table (\c DIMSTYLE).
 *
 * \return a pointer to \c dimstyle when sucessful, \c NULL when an error
 * occurred.
 */
DxfDimStyle *
dxf_dimstyle_set_dimexo
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
        double dimexo
                /*!< the extension line offset value (\c dimexo) to be
                 * set for the symbol table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimstyle->dimexo = dimexo;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle);
}


/*!
 * \brief Get the dimension line increment value (\c dimdli) from a DXF
 * dimension style symbol table (\c DIMSTYLE).
 *
 * \return the dimension line increment value (\c dimdli).
 */
double
dxf_dimstyle_get_dimdli
(
        DxfDimStyle *dimstyle
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle->dimdli);
}


/*!
 * \brief Set the dimension line increment value (\c dimdli) for a DXF
 * dimension style symbol table (\c DIMSTYLE).
 *
 * \return a pointer to \c dimstyle when sucessful, \c NULL when an error
 * occurred.
 */
DxfDimStyle *
dxf_dimstyle_set_dimdli
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
        double dimdli
                /*!< the dimension line increment value (\c dimdli) to
                 * be set for the symbol table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimstyle->dimdli = dimdli;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle);
}


/*!
 * \brief Get the extension line extension value (\c dimexe) from a DXF
 * dimension style symbol table (\c DIMSTYLE).
 *
 * \return the extension line extension value (\c dimexe).
 */
double
dxf_dimstyle_get_dimexe
(
        DxfDimStyle *dimstyle
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle->dimexe);
}


/*!
 * \brief Set the extension line extension value (\c dimexe) for a DXF
 * dimension style symbol table (\c DIMSTYLE).
 *
 * \return a pointer to \c dimstyle when sucessful, \c NULL when an error
 * occurred.
 */
DxfDimStyle *
dxf_dimstyle_set_dimexe
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
        double dimexe
                /*!< the extension line extension value (\c dimexe) to
                 * be set for the symbol table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimstyle->dimexe = dimexe;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle);
}


/*!
 * \brief Get the rounding value for dimension distances (\c dimrnd)
 * from a DXF dimension style symbol table (\c DIMSTYLE).
 *
 * \return the rounding value for dimension distances (\c dimrnd).
 */
double
dxf_dimstyle_get_dimrnd
(
        DxfDimStyle *dimstyle
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle->dimrnd);
}


/*!
 * \brief Set the rounding value for dimension distances (\c dimrnd)
 * for a DXF dimension style symbol table (\c DIMSTYLE).
 *
 * \return a pointer to \c dimstyle when sucessful, \c NULL when an error
 * occurred.
 */
DxfDimStyle *
dxf_dimstyle_set_dimrnd
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
        double dimrnd
                /*!< the rounding value for dimension distances
                 * (\c dimrnd) to be set for the symbol table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimstyle->dimrnd = dimrnd;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle);
}


/*!
 * \brief Get the dimension line extension value (\c dimdle) from a DXF
 * dimension style symbol table (\c DIMSTYLE).
 *
 * \return the dimension line extension value (\c dimdle).
 */
double
dxf_dimstyle_get_dimdle
(
        DxfDimStyle *dimstyle
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle->dimdle);
}


/*!
 * \brief Set the dimension line extension value (\c dimdle) for a DXF
 * dimension style symbol table (\c DIMSTYLE).
 *
 * \return a pointer to \c dimstyle when sucessful, \c NULL when an error
 * occurred.
 */
DxfDimStyle *
dxf_dimstyle_set_dimdle
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
        double dimdle
                /*!< the dimension line extension value (\c dimdle) to
                 * be set for the symbol table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimstyle->dimdle = dimdle;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle);
}


/*!
 * \brief Get the plus tolerance value (\c dimtp) from a DXF dimension
 * style symbol table (\c DIMSTYLE).
 *
 * \return the plus tolerance value (\c dimtp).
 */
double
dxf_dimstyle_get_dimtp
(
        DxfDimStyle *dimstyle
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle->dimtp);
}


/*!
 * \brief Set the plus tolerance value (\c dimtp) for a DXF dimension
 * style symbol table (\c DIMSTYLE).
 *
 * \return a pointer to \c dimstyle when sucessful, \c NULL when an error
 * occurred.
 */
DxfDimStyle *
dxf_dimstyle_set_dimtp
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
        double dimtp
                /*!< the plus tolerance value (\c dimtp) to be set for
                 * the symbol table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimstyle->dimtp = dimtp;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle);
}


/*!
 * \brief Get the minus tolerance value (\c dimtm) from a DXF dimension
 * style symbol table (\c DIMSTYLE).
 *
 * \return the minus tolerance value (\c dimtm).
 */
double
dxf_dimstyle_get_dimtm
(
        DxfDimStyle *dimstyle
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle->dimtm);
}


/*!
 * \brief Set the minus tolerance value (\c dimtm) for a DXF dimension
 * style symbol table (\c DIMSTYLE).
 *
 * \return a pointer to \c dimstyle when sucessful, \c NULL when an error
 * occurred.
 */
DxfDimStyle *
dxf_dimstyle_set_dimtm
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
        double dimtm
                /*!< the minus tolerance value (\c dimtm) to be set for
                 * the symbol table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimstyle->dimtm = dimtm;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle);
}


/*!
 * \brief Get the flag value (\c flag) from a DXF dimension style symbol
 * table (\c DIMSTYLE).
 *
 * \return the flag value (\c flag).
 *
 * \note This flag is for the benefit of AutoCAD commands;
 * it can be ignored by most programs that read DXF files, and need not
 * be set by programs that write DXF files.
 */
int16_t
dxf_dimstyle_get_flag
(
        DxfDimStyle *dimstyle
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle->flag);
}


/*!
 * \brief Set the flag value (\c flag) for this DXF dimension style
 * symbol table (\c DIMSTYLE).
 *
 * \return a pointer to \c dimstyle when sucessful, \c NULL when an error
 * occurred.
 */
DxfDimStyle *
dxf_dimstyle_set_flag
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
        int16_t flag
                /*!< the flag value (\c flag).\n
                 * \note This flag is for the benefit of AutoCAD commands;
                 * it can be ignored by most programs that read DXF
                 * files, and need not be set by programs that write DXF
                 * files. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimstyle->flag = flag;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle);
}


/*!
 * \brief Get the dimension tolerances value (\c dimtol) from a DXF
 * dimension style symbol table (\c DIMSTYLE).
 *
 * \return the dimension tolerances value (\c dimtol).
 */
int16_t
dxf_dimstyle_get_dimtol
(
        DxfDimStyle *dimstyle
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle->dimtol);
}


/*!
 * \brief Set the dimension tolerances value (\c dimtol) for this DXF
 * dimension style symbol table (\c DIMSTYLE).
 *
 * \return a pointer to \c dimstyle when sucessful, \c NULL when an error
 * occurred.
 */
DxfDimStyle *
dxf_dimstyle_set_dimtol
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
        int16_t dimtol
                /*!< the dimension tolerances value (\c dimtol) to be
                 * set for the symbol table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimstyle->dimtol = dimtol;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle);
}


/*!
 * \brief Get the dimension limits value (\c dimlim) from a DXF dimension style
 * symbol table (\c DIMSTYLE).
 *
 * \return the dimension limits value (\c dimlim).
 */
int16_t
dxf_dimstyle_get_dimlim
(
        DxfDimStyle *dimstyle
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle->dimlim);
}


/*!
 * \brief Set the dimension limits value (\c dimlim) for this DXF
 * dimension style symbol table (\c DIMSTYLE).
 *
 * \return a pointer to \c dimstyle when sucessful, \c NULL when an error
 * occurred.
 */
DxfDimStyle *
dxf_dimstyle_set_dimlim
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
        int16_t dimlim
                /*!< the dimension limits value (\c dimlim) to be
                 * set for the symbol table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimstyle->dimlim = dimlim;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle);
}


/*!
 * \brief Get the text inside horizontal value (\c dimtih) from a DXF
 * dimension style symbol table (\c DIMSTYLE).
 *
 * \return the text inside horizontal value (\c dimtih).
 */
int16_t
dxf_dimstyle_get_dimtih
(
        DxfDimStyle *dimstyle
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle->dimtih);
}


/*!
 * \brief Set the text inside horizontal value (\c dimtih) for this DXF
 * dimension style symbol table (\c DIMSTYLE).
 *
 * \return a pointer to \c dimstyle when sucessful, \c NULL when an error
 * occurred.
 */
DxfDimStyle *
dxf_dimstyle_set_dimtih
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
        int16_t dimtih
                /*!< the text inside horizontal value (\c dimtih) to be
                 * set for the symbol table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimstyle->dimtih = dimtih;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle);
}


/*!
 * \brief Get the text outside horizontal value (\c dimtoh) from a DXF
 * dimension style symbol table (\c DIMSTYLE).
 *
 * \return the text outside horizontal value (\c dimtoh).
 */
int16_t
dxf_dimstyle_get_dimtoh
(
        DxfDimStyle *dimstyle
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle->dimtoh);
}


/*!
 * \brief Set the text outside horizontal value (\c dimtoh) for this DXF
 * dimension style symbol table (\c DIMSTYLE).
 *
 * \return a pointer to \c dimstyle when sucessful, \c NULL when an error
 * occurred.
 */
DxfDimStyle *
dxf_dimstyle_set_dimtoh
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
        int16_t dimtoh
                /*!< the text outside horizontal value (\c dimtoh) to be
                 * set for the symbol table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimstyle->dimtoh = dimtoh;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle);
}


/*!
 * \brief Get the first extension line suppressed value (\c dimse1) from a DXF
 * dimension style symbol table (\c DIMSTYLE).
 *
 * \return the first extension line suppressed value (\c dimse1).
 */
int16_t
dxf_dimstyle_get_dimse1
(
        DxfDimStyle *dimstyle
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle->dimse1);
}


/*!
 * \brief Set the first extension line suppressed value (\c dimse1) for
 * this DXF dimension style symbol table (\c DIMSTYLE).
 *
 * \return a pointer to \c dimstyle when sucessful, \c NULL when an error
 * occurred.
 */
DxfDimStyle *
dxf_dimstyle_set_dimse1
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
        int16_t dimse1
                /*!< the first extension line suppressed value
                 * (\c dimse1) to be set for the symbol table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimstyle->dimse1 = dimse1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle);
}


/*!
 * \brief Get the second extension line suppressed value (\c dimse2) from a DXF
 * dimension style symbol table (\c DIMSTYLE).
 *
 * \return the second extension line suppressed value (\c dimse2).
 */
int16_t
dxf_dimstyle_get_dimse2
(
        DxfDimStyle *dimstyle
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle->dimse2);
}


/*!
 * \brief Set the second extension line suppressed value (\c dimse2) for
 * this DXF dimension style symbol table (\c DIMSTYLE).
 *
 * \return a pointer to \c dimstyle when sucessful, \c NULL when an error
 * occurred.
 */
DxfDimStyle *
dxf_dimstyle_set_dimse2
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
        int16_t dimse2
                /*!< the second extension line suppressed value
                 * (\c dimse2) to be set for the symbol table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimstyle->dimse2 = dimse2;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle);
}


/*!
 * \brief Get the text above dimension line value (\c dimtad) from a DXF
 * dimension style symbol table (\c DIMSTYLE).
 *
 * \return the text above dimension line value (\c dimtad).
 */
int16_t
dxf_dimstyle_get_dimtad
(
        DxfDimStyle *dimstyle
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle->dimtad);
}


/*!
 * \brief Set the text above dimension line value (\c dimtad) for
 * this DXF dimension style symbol table (\c DIMSTYLE).
 *
 * \return a pointer to \c dimstyle when sucessful, \c NULL when an error
 * occurred.
 */
DxfDimStyle *
dxf_dimstyle_set_dimtad
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
        int16_t dimtad
                /*!< the text above dimension line value (\c dimtad) to
                 * be set for the symbol table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimstyle->dimtad = dimtad;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle);
}


/*!
 * \brief Get the zero suppression for "feet & inch" dimensions value
 * (\c dimzin) from a DXF dimension style symbol table (\c DIMSTYLE).
 *
 * \return the zero suppression for "feet & inch" dimensions value
 * (\c dimzin).
 */
int16_t
dxf_dimstyle_get_dimzin
(
        DxfDimStyle *dimstyle
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle->dimzin);
}


/*!
 * \brief Set the zero suppression for "feet & inch" dimensions value
 * (\c dimzin) for this DXF dimension style symbol table (\c DIMSTYLE).
 *
 * \return a pointer to \c dimstyle when sucessful, \c NULL when an error
 * occurred.
 */
DxfDimStyle *
dxf_dimstyle_set_dimzin
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
        int16_t dimzin
                /*!< the zero suppression for "feet & inch" dimensions
                 * value (\c dimzin) to be set for the symbol table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimstyle->dimzin = dimzin;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle);
}


/*!
 * \brief Get the ID code from this DXF dimenstion style symbol table
 * (\c DIMSTYLE).
 *
 * \return ID code.
 */
int
dxf_dimstyle_get_id_code
(
        DxfDimStyle *dimstyle
                /*!< a pointer to a DXF \c DIMSTYLE symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle->id_code);
}


/*!
 * \brief Set the ID code for this DXF dimenstion style symbol table
 * (\c DIMSTYLE).
 *
 * \return a pointer to \c dimstyle when sucessful, \c NULL when an error
 * occurred.
 */
DxfDimStyle *
dxf_dimstyle_set_id_code
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF dimenstion style symbol table
                 * (\c DIMSTYLE). */
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
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimstyle->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle);
}


/*!
 * \brief Get the dimensioning text height value (\c dimtxt) from a DXF
 * dimension style symbol table (\c DIMSTYLE).
 *
 * \return the dimensioning text height value (\c dimtxt).
 */
double
dxf_dimstyle_get_dimtxt
(
        DxfDimStyle *dimstyle
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle->dimtxt);
}


/*!
 * \brief Set the dimensioning text height value (\c dimtxt) for a DXF
 * dimension style symbol table (\c DIMSTYLE).
 *
 * \return a pointer to \c dimstyle when sucessful, \c NULL when an error
 * occurred.
 */
DxfDimStyle *
dxf_dimstyle_set_dimtxt
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
        double dimtxt
                /*!< the dimensioning text height value (\c dimtxt) to
                 * be set for the symbol table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimstyle->dimtxt = dimtxt;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle);
}


/*!
 * \brief Get the size of center mark/lines value (\c dimcen) from a DXF
 * dimension style symbol table (\c DIMSTYLE).
 *
 * \return the size of center mark/lines value (\c dimcen).
 */
double
dxf_dimstyle_get_dimcen
(
        DxfDimStyle *dimstyle
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle->dimcen);
}


/*!
 * \brief Set the size of center mark/lines value (\c dimcen) for a DXF
 * dimension style symbol table (\c DIMSTYLE).
 *
 * \return a pointer to \c dimstyle when sucessful, \c NULL when an error
 * occurred.
 */
DxfDimStyle *
dxf_dimstyle_set_dimcen
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
        double dimcen
                /*!< the size of center mark/lines value (\c dimcen) to
                 * be set for the symbol table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimstyle->dimcen = dimcen;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle);
}


/*!
 * \brief Get the dimensioning tick size value (\c dimtsz) from a DXF
 * dimension style symbol table (\c DIMSTYLE).
 *
 * \return the dimensioning tick size value (\c dimtsz).
 */
double
dxf_dimstyle_get_dimtsz
(
        DxfDimStyle *dimstyle
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle->dimtsz);
}


/*!
 * \brief Set the dimensioning tick size value (\c dimtsz) for a DXF
 * dimension style symbol table (\c DIMSTYLE).
 *
 * \return a pointer to \c dimstyle when sucessful, \c NULL when an error
 * occurred.
 */
DxfDimStyle *
dxf_dimstyle_set_dimtsz
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
        double dimtsz
                /*!< the dimensioning tick size value (\c dimtsz) to
                 * be set for the symbol table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimstyle->dimtsz = dimtsz;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle);
}


/*!
 * \brief Get the alternate unit scale factor value (\c dimaltf) from a DXF
 * dimension style symbol table (\c DIMSTYLE).
 *
 * \return the alternate unit scale factor value (\c dimaltf).
 */
double
dxf_dimstyle_get_dimaltf
(
        DxfDimStyle *dimstyle
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle->dimaltf);
}


/*!
 * \brief Set the alternate unit scale factor value (\c dimaltf) for a DXF
 * dimension style symbol table (\c DIMSTYLE).
 *
 * \return a pointer to \c dimstyle when sucessful, \c NULL when an error
 * occurred.
 */
DxfDimStyle *
dxf_dimstyle_set_dimaltf
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
        double dimaltf
                /*!< the alternate unit scale factor value (\c dimaltf)
                 * to be set for the symbol table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimstyle->dimaltf = dimaltf;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle);
}


/*!
 * \brief Get the linear measurements scale factor value (\c dimlfac)
 * from a DXF dimension style symbol table (\c DIMSTYLE).
 *
 * \return the linear measurements scale factor value (\c dimlfac).
 */
double
dxf_dimstyle_get_dimlfac
(
        DxfDimStyle *dimstyle
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle->dimlfac);
}


/*!
 * \brief Set the linear measurements scale factor value (\c dimlfac)
 * for a DXF dimension style symbol table (\c DIMSTYLE).
 *
 * \return a pointer to \c dimstyle when sucessful, \c NULL when an error
 * occurred.
 */
DxfDimStyle *
dxf_dimstyle_set_dimlfac
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
        double dimlfac
                /*!< the linear measurements scale factor value
                 * (\c dimlfac) to be set for the symbol table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimstyle->dimlfac = dimlfac;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle);
}


/*!
 * \brief Get the text vertical position value (\c dimtvp) from a DXF
 * dimension style symbol table (\c DIMSTYLE).
 *
 * \return the text vertical position value (\c dimtvp).
 */
double
dxf_dimstyle_get_dimtvp
(
        DxfDimStyle *dimstyle
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle->dimtvp);
}


/*!
 * \brief Set the text vertical position value (\c dimtvp) for a DXF
 * dimension style symbol table (\c DIMSTYLE).
 *
 * \return a pointer to \c dimstyle when sucessful, \c NULL when an error
 * occurred.

 */
DxfDimStyle *
dxf_dimstyle_set_dimtvp
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
        double dimtvp
                /*!< the text vertical position value (\c dimtvp) to be
                 * set for the symbol table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimstyle->dimtvp = dimtvp;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle);
}


/*!
 * \brief Get the dimension tolerance display scale factor value
 * (\c dimtfac) from a DXF dimension style symbol table (\c DIMSTYLE).
 *
 * \return the dimension tolerance display scale factor value (\c dimtfac).
 */
double
dxf_dimstyle_get_dimtfac
(
        DxfDimStyle *dimstyle
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle->dimtfac);
}


/*!
 * \brief Set the dimension tolerance display scale factor value
 * (\c dimtfac) for a DXF dimension style symbol table (\c DIMSTYLE).
 *
 * \return a pointer to \c dimstyle when sucessful, \c NULL when an error
 * occurred.
 */
DxfDimStyle *
dxf_dimstyle_set_dimtfac
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
        double dimtfac
                /*!< the dimension tolerance display scale factor value
                 * (\c dimtfac) to be set for the symbol table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimstyle->dimtfac = dimtfac;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle);
}


/*!
 * \brief Get the dimension line gap value (\c dimgap) from a DXF
 * dimension style symbol table (\c DIMSTYLE).
 *
 * \return the dimension line gap value (\c dimgap).
 */
double
dxf_dimstyle_get_dimgap
(
        DxfDimStyle *dimstyle
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle->dimgap);
}


/*!
 * \brief Set the dimension line gap value (\c dimgap) for a DXF
 * dimension style symbol table (\c DIMSTYLE).
 *
 * \return a pointer to \c dimstyle when sucessful, \c NULL when an error
 * occurred.
 */
DxfDimStyle *
dxf_dimstyle_set_dimgap
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
        double dimgap
                /*!< the dimension line gap value (\c dimgap) to be set
                 * for the symbol table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimstyle->dimgap = dimgap;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle);
}


/*!
 * \brief Get the alternate unit dimensioning value (\c dimalt) from a
 * DXF dimension style symbol table (\c DIMSTYLE).
 *
 * \return the alternate unit dimensioning value (\c dimalt).
 */
int16_t
dxf_dimstyle_get_dimalt
(
        DxfDimStyle *dimstyle
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle->dimalt);
}


/*!
 * \brief Set the alternate unit dimensioning value (\c dimalt) for this
 * DXF dimension style symbol table (\c DIMSTYLE).
 *
 * \return a pointer to \c dimstyle when sucessful, \c NULL when an error
 * occurred.
 */
DxfDimStyle *
dxf_dimstyle_set_dimalt
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
        int16_t dimalt
                /*!< the alternate unit dimensioning value (\c dimalt)
                 * to be set for the symbol table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimstyle->dimalt = dimalt;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle);
}


/*!
 * \brief Get the alternate unit decimal places value (\c dimaltd) from a
 * DXF dimension style symbol table (\c DIMSTYLE).
 *
 * \return the alternate unit decimal places value (\c dimaltd).
 */
int16_t
dxf_dimstyle_get_dimaltd
(
        DxfDimStyle *dimstyle
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle->dimaltd);
}


/*!
 * \brief Set the alternate unit decimal places value (\c dimaltd) for
 * this DXF dimension style symbol table (\c DIMSTYLE).
 *
 * \return a pointer to \c dimstyle when sucessful, \c NULL when an error
 * occurred.
 */
DxfDimStyle *
dxf_dimstyle_set_dimaltd
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
        int16_t dimaltd
                /*!< the alternate unit decimal places value
                 * (\c dimaltd) to be set for the symbol table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimstyle->dimaltd = dimaltd;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle);
}


/*!
 * \brief Get the text outside extensions, force line extensions value
 * (\c dimtofl) from a DXF dimension style symbol table (\c DIMSTYLE).
 *
 * \return the text outside extensions, force line extensions value
 * (\c dimtofl).
 */
int16_t
dxf_dimstyle_get_dimtofl
(
        DxfDimStyle *dimstyle
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle->dimtofl);
}


/*!
 * \brief Set the text outside extensions, force line extensions value
 * (\c dimtofl) for this DXF dimension style symbol table (\c DIMSTYLE).
 *
 * \return a pointer to \c dimstyle when sucessful, \c NULL when an error
 * occurred.
 */
DxfDimStyle *
dxf_dimstyle_set_dimtofl
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
        int16_t dimtofl
                /*!< the text outside extensions, force line extensions
                 * value (\c dimtofl) to be set for the symbol table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimstyle->dimtofl = dimtofl;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle);
}


/*!
 * \brief Get the use separate arrow blocks value (\c dimsah) from a DXF
 * dimension style symbol table (\c DIMSTYLE).
 *
 * \return the use separate arrow blocks value (\c dimsah).
 */
int16_t
dxf_dimstyle_get_dimsah
(
        DxfDimStyle *dimstyle
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle->dimsah);
}


/*!
 * \brief Set the use separate arrow blocks value (\c dimsah) for this
 * DXF dimension style symbol table (\c DIMSTYLE).
 *
 * \return a pointer to \c dimstyle when sucessful, \c NULL when an error
 * occurred.
 */
DxfDimStyle *
dxf_dimstyle_set_dimsah
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
        int16_t dimsah
                /*!< the use separate arrow blocks value (\c dimsah) to
                 * be set for the symbol table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimstyle->dimsah = dimsah;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle);
}


/*!
 * \brief Get the force text inside extensions value (\c dimtix) from a
 * DXF dimension style symbol table (\c DIMSTYLE).
 *
 * \return the force text inside extensions value (\c dimtix).
 */
int16_t
dxf_dimstyle_get_dimtix
(
        DxfDimStyle *dimstyle
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle->dimtix);
}


/*!
 * \brief Set the force text inside extensions value (\c dimtix) for
 * this DXF dimension style symbol table (\c DIMSTYLE).
 *
 * \return a pointer to \c dimstyle when sucessful, \c NULL when an error
 * occurred.
 */
DxfDimStyle *
dxf_dimstyle_set_dimtix
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
        int16_t dimtix
                /*!< the force text inside extensions value (\c dimtix)
                 * to be set for the symbol table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimstyle->dimtix = dimtix;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle);
}


/*!
 * \brief Get the suppress outside-extensions dimension lines value
 * (\c dimsoxd) from a DXF dimension style symbol table (\c DIMSTYLE).
 *
 * \return the suppress outside-extensions dimension lines value
 * (\c dimsoxd).
 */
int16_t
dxf_dimstyle_get_dimsoxd
(
        DxfDimStyle *dimstyle
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle->dimsoxd);
}


/*!
 * \brief Set the suppress outside-extensions dimension lines value
 * (\c dimsoxd) for this DXF dimension style symbol table (\c DIMSTYLE).
 *
 * \return a pointer to \c dimstyle when sucessful, \c NULL when an error
 * occurred.
 */
DxfDimStyle *
dxf_dimstyle_set_dimsoxd
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
        int16_t dimsoxd
                /*!< the suppress outside-extensions dimension lines
                 * value (\c dimsoxd) to be set for the symbol table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimstyle->dimsoxd = dimsoxd;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle);
}


/*!
 * \brief Get the dimension line color value (\c dimclrd) from a DXF
 * dimension style symbol table (\c DIMSTYLE).
 *
 * \return the dimension line color value (\c dimclrd).
 */
int16_t
dxf_dimstyle_get_dimclrd
(
        DxfDimStyle *dimstyle
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle->dimclrd);
}


/*!
 * \brief Set the dimension line color value (\c dimclrd) for this DXF
 * dimension style symbol table (\c DIMSTYLE).
 *
 * \return a pointer to \c dimstyle when sucessful, \c NULL when an error
 * occurred.
 */
DxfDimStyle *
dxf_dimstyle_set_dimclrd
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
        int16_t dimclrd
                /*!< the dimension line color value (\c dimclrd) to be
                 * set for the symbol table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimstyle->dimclrd = dimclrd;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle);
}


/*!
 * \brief Get the dimension extension line color value (\c dimclre) from
 * a DXF dimension style symbol table (\c DIMSTYLE).
 *
 * \return the dimension extension line color value (\c dimclre).
 */
int16_t
dxf_dimstyle_get_dimclre
(
        DxfDimStyle *dimstyle
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle->dimclre);
}


/*!
 * \brief Set the dimension extension line color value (\c dimclre) for
 * this DXF dimension style symbol table (\c DIMSTYLE).
 *
 * \return a pointer to \c dimstyle when sucessful, \c NULL when an error
 * occurred.
 */
DxfDimStyle *
dxf_dimstyle_set_dimclre
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
        int16_t dimclre
                /*!< the dimension extension line color value
                 * (\c dimclre) to be set for the symbol table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimstyle->dimclre = dimclre;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle);
}


/*!
 * \brief Get the dimension text color value (\c dimclrt) from a DXF
 * dimension style symbol table (\c DIMSTYLE).
 *
 * \return the dimension text color value (\c dimclrt).
 */
int16_t
dxf_dimstyle_get_dimclrt
(
        DxfDimStyle *dimstyle
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle->dimclrt);
}


/*!
 * \brief Set the dimension text color value (\c dimclrt) for this DXF
 * dimension style symbol table (\c DIMSTYLE).
 *
 * \return a pointer to \c dimstyle when sucessful, \c NULL when an error
 * occurred.
 */
DxfDimStyle *
dxf_dimstyle_set_dimclrt
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
        int16_t dimclrt
                /*!< the dimension text color value (\c dimclrt) to be
                 * set for the symbol table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimstyle->dimclrt = dimclrt;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle);
}


/*!
 * \brief Get the dimension units format value (\c dimunit) from a DXF
 * dimension style symbol table (\c DIMSTYLE).
 *
 * \return the dimension units format value (\c dimunit).
 */
int16_t
dxf_dimstyle_get_dimunit
(
        DxfDimStyle *dimstyle
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dimstyle->dimunit < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found in the dimunit member.\n")),
                  __FUNCTION__);
        }
        if (dimstyle->dimunit > 4)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found in the dimunit member.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle->dimunit);
}


/*!
 * \brief Set the dimension units format value (\c dimunit) for this DXF
 * dimension style symbol table (\c DIMSTYLE).
 *
 * \return a pointer to \c dimstyle when sucessful, \c NULL when an error
 * occurred.
 */
DxfDimStyle *
dxf_dimstyle_set_dimunit
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
        int16_t dimunit
                /*!< the dimension units format value (\c dimunit) to be
                 * set for the symbol table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimunit < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed in the dimunit member.\n")),
                  __FUNCTION__);
        }
        if (dimunit > 4)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed in the dimunit member.\n")),
                  __FUNCTION__);
        }
        dimstyle->dimunit = dimunit;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle);
}


/*!
 * \brief Get the number of decimal places for the tolerance values of
 * a primary units dimension value (\c dimdec) from a DXF dimension
 * style symbol table (\c DIMSTYLE).
 *
 * \return the number of decimal places for the tolerance values of a
 * primary units dimension value (\c dimdec).
 */
int16_t
dxf_dimstyle_get_dimdec
(
        DxfDimStyle *dimstyle
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle->dimdec);
}


/*!
 * \brief Set the number of decimal places for the tolerance values of a
 * primary units dimension value (\c dimdec) for this DXF
 * dimension style symbol table (\c DIMSTYLE).
 *
 * \return a pointer to \c dimstyle when sucessful, \c NULL when an error
 * occurred.
 */
DxfDimStyle *
dxf_dimstyle_set_dimdec
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
        int16_t dimdec
                /*!< the number of decimal places for the tolerance
                 * values of a primary units dimension value (\c dimdec)
                 * to be set for the symbol table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimstyle->dimdec = dimdec;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle);
}


/*!
 * \brief Get the number of decimal places to display the tolerance
 * values (\c dimtdec) from a DXF dimension style symbol table
 * (\c DIMSTYLE).
 *
 * \return the number of decimal places to display the tolerance
 * values (\c dimtdec).
 */
int16_t
dxf_dimstyle_get_dimtdec
(
        DxfDimStyle *dimstyle
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle->dimtdec);
}


/*!
 * \brief Set the number of decimal places to display the tolerance
 * values (\c dimtdec) for this DXF dimension style symbol table
 * (\c DIMSTYLE).
 *
 * \return a pointer to \c dimstyle when sucessful, \c NULL when an error
 * occurred.
 */
DxfDimStyle *
dxf_dimstyle_set_dimtdec
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
        int16_t dimtdec
                /*!< the number of decimal places to display the
                 * tolerance values (\c dimtdec) to be set for the
                 * symbol table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimstyle->dimtdec = dimtdec;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle);
}


/*!
 * \brief Get the units format for alternate units value (\c dimaltu)
 * from a DXF dimension style symbol table (\c DIMSTYLE).
 *
 * \return the units format for alternate units value (\c dimaltu).
 */
int16_t
dxf_dimstyle_get_dimaltu
(
        DxfDimStyle *dimstyle
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle->dimaltu);
}


/*!
 * \brief Set the units format for alternate units value (\c dimaltu)
 * for this DXF dimension style symbol table (\c DIMSTYLE).
 *
 * \return a pointer to \c dimstyle when sucessful, \c NULL when an error
 * occurred.
 */
DxfDimStyle *
dxf_dimstyle_set_dimaltu
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
        int16_t dimaltu
                /*!< the units format for alternate units value
                 * (\c dimaltu) to be set for the symbol table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimstyle->dimaltu = dimaltu;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle);
}


/*!
 * \brief Get the number of decimal places for tolerance values of an
 * alternate units dimension value (\c dimalttd) from a DXF dimension
 * style symbol table (\c DIMSTYLE).
 *
 * \return the number of decimal places for tolerance values of an
 * alternate units dimension value (\c dimalttd).
 */
int16_t
dxf_dimstyle_get_dimalttd
(
        DxfDimStyle *dimstyle
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle->dimalttd);
}


/*!
 * \brief Set the number of decimal places for tolerance values of an
 * alternate units dimension value (\c dimalttd) for this DXF dimension
 * style symbol table (\c DIMSTYLE).
 *
 * \return a pointer to \c dimstyle when sucessful, \c NULL when an error
 * occurred.
 */
DxfDimStyle *
dxf_dimstyle_set_dimalttd
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
        int16_t dimalttd
                /*!< the number of decimal places for tolerance values
                 * of an alternate units dimension value (\c dimalttd)
                 * to be set for the symbol table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimstyle->dimalttd = dimalttd;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle);
}


/*!
 * \brief Get the angle format for angular dimensions value
 * (\c dimaunit) from a DXF dimension style symbol table (\c DIMSTYLE).
 *
 * \return the angle format for angular dimensions value value
 * (\c dimaunit).
 */
int16_t
dxf_dimstyle_get_dimaunit
(
        DxfDimStyle *dimstyle
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dimstyle->dimaunit < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found in the dimaunit member.\n")),
                  __FUNCTION__);
        }
        if (dimstyle->dimaunit > 4)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found in the dimaunit member.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle->dimaunit);
}


/*!
 * \brief Set the angle format for angular dimensions value
 * (\c dimaunit) for this DXF dimension style symbol table (\c DIMSTYLE).
 *
 * \return a pointer to \c dimstyle when sucessful, \c NULL when an error
 * occurred.
 */
DxfDimStyle *
dxf_dimstyle_set_dimaunit
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
        int16_t dimaunit
                /*!< the angle format for angular dimensions value
                 * (\c dimaunit) to be set for the symbol table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimaunit < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed in the dimaunit variable.\n")),
                  __FUNCTION__);
        }
        if (dimaunit > 4)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed in the dimaunit variable.\n")),
                  __FUNCTION__);
        }
        dimstyle->dimaunit = dimaunit;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle);
}


/*!
 * \brief Get the horizontal dimension text position value (\c dimjust)
 * from a DXF dimension style symbol table (\c DIMSTYLE).
 *
 * \return the horizontal dimension text position value (\c dimjust).
 */
int16_t
dxf_dimstyle_get_dimjust
(
        DxfDimStyle *dimstyle
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dimstyle->dimjust < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found in the dimjust member.\n")),
                  __FUNCTION__);
        }
        if (dimstyle->dimjust > 4)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found in the dimjust member.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle->dimjust);
}


/*!
 * \brief Set the horizontal dimension text position value (\c dimjust)
 * for this DXF dimension style symbol table (\c DIMSTYLE).
 *
 * \return a pointer to \c dimstyle when sucessful, \c NULL when an error
 * occurred.
 */
DxfDimStyle *
dxf_dimstyle_set_dimjust
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
        int16_t dimjust
                /*!< the horizontal dimension text position value
                 * (\c dimjust) to be set for the symbol table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimjust < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed in the dimjust variable.\n")),
                  __FUNCTION__);
        }
        if (dimjust > 4)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed in the dimjust variable.\n")),
                  __FUNCTION__);
        }
        dimstyle->dimjust = dimjust;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle);
}


/*!
 * \brief Get the suppression of first extension line value (\c dimsd1)
 * from a DXF dimension style symbol table (\c DIMSTYLE).
 *
 * \return the suppression of first extension line value (\c dimsd1).
 */
int16_t
dxf_dimstyle_get_dimsd1
(
        DxfDimStyle *dimstyle
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dimstyle->dimsd1 < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found in the dimsd1 member.\n")),
                  __FUNCTION__);
        }
        if (dimstyle->dimsd1 > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found in the dimsd1 member.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle->dimsd1);
}


/*!
 * \brief Set the suppression of first extension line value (\c dimsd1)
 * for this DXF dimension style symbol table (\c DIMSTYLE).
 *
 * \return a pointer to \c dimstyle when sucessful, \c NULL when an error
 * occurred.
 */
DxfDimStyle *
dxf_dimstyle_set_dimsd1
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
        int16_t dimsd1
                /*!< the suppression of first extension line value
                 * (\c dimsd1) to be set for the symbol table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimsd1 < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed in the dimsd1 variable.\n")),
                  __FUNCTION__);
        }
        if (dimsd1 > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed in the dimsd1 variable.\n")),
                  __FUNCTION__);
        }
        dimstyle->dimsd1 = dimsd1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle);
}


/*!
 * \brief Get the suppression of the second extension line value
 * (\c dimsd2) from a DXF dimension style symbol table (\c DIMSTYLE).
 *
 * \return the suppression of the second extension line value
 * (\c dimsd2).
 */
int16_t
dxf_dimstyle_get_dimsd2
(
        DxfDimStyle *dimstyle
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dimstyle->dimsd2 < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found in the dimsd2 member.\n")),
                  __FUNCTION__);
        }
        if (dimstyle->dimsd2 > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found in the dimsd2 member.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle->dimsd2);
}


/*!
 * \brief Set the suppression of the second extension line value
 * (\c dimsd2) for this DXF dimension style symbol table (\c DIMSTYLE).
 *
 * \return a pointer to \c dimstyle when sucessful, \c NULL when an error
 * occurred.
 */
DxfDimStyle *
dxf_dimstyle_set_dimsd2
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
        int16_t dimsd2
                /*!< the suppression of the second extension line value
                 * (\c dimsd2) to be set for the symbol table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimsd2 < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed in the dimsd2 variable.\n")),
                  __FUNCTION__);
        }
        if (dimsd2 > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed in the dimsd2 variable.\n")),
                  __FUNCTION__);
        }
        dimstyle->dimsd2 = dimsd2;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle);
}


/*!
 * \brief Get the vertical justification for tolerance value
 * (\c dimtolj) from a DXF dimension style symbol table (\c DIMSTYLE).
 *
 * \return the vertical justification for tolerance value (\c dimtolj).
 */
int16_t
dxf_dimstyle_get_dimtolj
(
        DxfDimStyle *dimstyle
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dimstyle->dimtolj < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found in the dimtolj member.\n")),
                  __FUNCTION__);
        }
        if (dimstyle->dimtolj > 2)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found in the dimtolj member.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle->dimtolj);
}


/*!
 * \brief Set the vertical justification for tolerance value
 * (\c dimtolj) for this DXF dimension style symbol table (\c DIMSTYLE).
 *
 * \return a pointer to \c dimstyle when sucessful, \c NULL when an error
 * occurred.
 */
DxfDimStyle *
dxf_dimstyle_set_dimtolj
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
        int16_t dimtolj
                /*!< the vertical justification for tolerance value
                 * (\c dimtolj) to be set for the symbol table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimtolj < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed in the dimtolj variable.\n")),
                  __FUNCTION__);
        }
        if (dimtolj > 2)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed in the dimtolj variable.\n")),
                  __FUNCTION__);
        }
        dimstyle->dimtolj = dimtolj;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle);
}


/*!
 * \brief Get the suppression of zeros for tolerance value  (\c dimtzin)
 * from a DXF dimension style symbol table (\c DIMSTYLE).
 *
 * \return the suppression of zeros for tolerance value (\c dimtzin).
 */
int16_t
dxf_dimstyle_get_dimtzin
(
        DxfDimStyle *dimstyle
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dimstyle->dimtzin < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found in the dimtzin member.\n")),
                  __FUNCTION__);
        }
        if (dimstyle->dimtzin > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found in the dimtzin member.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle->dimtzin);
}


/*!
 * \brief Set the suppression of zeros for tolerance value
 * (\c dimtzin) for this DXF dimension style symbol table (\c DIMSTYLE).
 *
 * \return a pointer to \c dimstyle when sucessful, \c NULL when an error
 * occurred.
 */
DxfDimStyle *
dxf_dimstyle_set_dimtzin
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
        int16_t dimtzin
                /*!< the suppression of zeros for tolerance value
                 * (\c dimtzin) to be set for the symbol table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimtzin < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed in the dimtzin variable.\n")),
                  __FUNCTION__);
        }
        if (dimtzin > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed in the dimtzin variable.\n")),
                  __FUNCTION__);
        }
        dimstyle->dimtzin = dimtzin;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle);
}


/*!
 * \brief Get the toggle suppression of zeros for alternate unit
 * dimension value  (\c dimaltz) from a DXF dimension style symbol table
 * (\c DIMSTYLE).
 *
 * \return the toggle suppression of zeros for alternate unit dimension
 * value (\c dimaltz).
 */
int16_t
dxf_dimstyle_get_dimaltz
(
        DxfDimStyle *dimstyle
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dimstyle->dimaltz < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found in the dimaltz member.\n")),
                  __FUNCTION__);
        }
        if (dimstyle->dimaltz > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found in the dimaltz member.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle->dimaltz);
}


/*!
 * \brief Set the toggle suppression of zeros for alternate unit
 * dimension value (\c dimaltz) for this DXF dimension style symbol
 * table (\c DIMSTYLE).
 *
 * \return a pointer to \c dimstyle when sucessful, \c NULL when an error
 * occurred.
 */
DxfDimStyle *
dxf_dimstyle_set_dimaltz
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
        int16_t dimaltz
                /*!< the toggle suppression of zeros for alternate unit
                 * dimension value (\c dimaltz) to be set for the symbol
                 * table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimaltz < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed in the dimaltz variable.\n")),
                  __FUNCTION__);
        }
        if (dimaltz > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed in the dimaltz variable.\n")),
                  __FUNCTION__);
        }
        dimstyle->dimaltz = dimaltz;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle);
}


/*!
 * \brief Get the toggle suppression of zeros for tolerance units
 * value  (\c dimalttz) from a DXF dimension style symbol table
 * (\c DIMSTYLE).
 *
 * \return the toggle suppression of zeros for tolerance units value
 * (\c dimalttz).
 */
int16_t
dxf_dimstyle_get_dimalttz
(
        DxfDimStyle *dimstyle
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dimstyle->dimalttz < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found in the dimalttz member.\n")),
                  __FUNCTION__);
        }
        if (dimstyle->dimalttz > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found in the dimalttz member.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle->dimalttz);
}


/*!
 * \brief Set the toggle suppression of zeros for tolerance units
 * value (\c dimalttz) for this DXF dimension style symbol table
 * (\c DIMSTYLE).
 *
 * \return a pointer to \c dimstyle when sucessful, \c NULL when an error
 * occurred.
 */
DxfDimStyle *
dxf_dimstyle_set_dimalttz
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
        int16_t dimalttz
                /*!< the toggle suppression of zeros for tolerance units
                 * value (\c dimaltz) to be set for the symbol table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimalttz < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed in the dimalttz variable.\n")),
                  __FUNCTION__);
        }
        if (dimalttz > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed in the dimalttz variable.\n")),
                  __FUNCTION__);
        }
        dimstyle->dimalttz = dimalttz;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle);
}


/*!
 * \brief Get the placement of text and arrowheads value  (\c dimfit)
 * from a DXF dimension style symbol table (\c DIMSTYLE).
 *
 * \return the placement of text and arrowheads value (\c dimfit).
 */
int16_t
dxf_dimstyle_get_dimfit
(
        DxfDimStyle *dimstyle
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dimstyle->dimfit < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found in the dimfit member.\n")),
                  __FUNCTION__);
        }
        if (dimstyle->dimfit > 3)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found in the dimfit member.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle->dimfit);
}


/*!
 * \brief Set the placement of text and arrowheads value (\c dimfit) for
 * this DXF dimension style symbol table (\c DIMSTYLE).
 *
 * \return a pointer to \c dimstyle when sucessful, \c NULL when an error
 * occurred.
 */
DxfDimStyle *
dxf_dimstyle_set_dimfit
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
        int16_t dimfit
                /*!< the placement of text and arrowheads value
                 * (\c dimfit) to be set for the symbol table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimfit < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed in the dimfit variable.\n")),
                  __FUNCTION__);
        }
        if (dimfit > 3)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed in the dimfit variable.\n")),
                  __FUNCTION__);
        }
        dimstyle->dimfit = dimfit;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle);
}


/*!
 * \brief Get the cursor functionality for user positioned text value
 * (\c dimupt) from a DXF dimension style symbol table (\c DIMSTYLE).
 *
 * \return the cursor functionality for user positioned text value
 * (\c dimupt).
 */
int16_t
dxf_dimstyle_get_dimupt
(
        DxfDimStyle *dimstyle
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dimstyle->dimupt < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found in the dimupt member.\n")),
                  __FUNCTION__);
        }
        if (dimstyle->dimupt > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found in the dimupt member.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle->dimupt);
}


/*!
 * \brief Set the cursor functionality for user positioned text value
 * (\c dimupt) for this DXF dimension style symbol table (\c DIMSTYLE).
 *
 * \return a pointer to \c dimstyle when sucessful, \c NULL when an error
 * occurred.
 */
DxfDimStyle *
dxf_dimstyle_set_dimupt
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
        int16_t dimupt
                /*!< the cursor functionality for user positioned text
                 * value (\c dimupt) to be set for the symbol table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimupt < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed in the dimupt variable.\n")),
                  __FUNCTION__);
        }
        if (dimupt > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed in the dimupt variable.\n")),
                  __FUNCTION__);
        }
        dimstyle->dimupt = dimupt;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle);
}


/*!
 * \brief Get the soft pointer to the \c dictionary_owner_soft from a
 * DXF \c DIMSTYLE symbol table entry.
 *
 * \return a pointer to the \c dictionary_owner_soft.
 *
 * \warning No checks are performed on the returned pointer.
 */
char *
dxf_dimstyle_get_dictionary_owner_soft
(
        DxfDimStyle *dimstyle
                /*!< a pointer to a DXF \c DIMSTYLE symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimstyle->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (dimstyle->dictionary_owner_soft));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_soft for a DXF
 * \c DIMSTYLE symbol table entry.
 *
 * \return a pointer to \c dimstyle when sucessful, \c NULL when an error
 * occurred.
 */
DxfDimStyle *
dxf_dimstyle_set_dictionary_owner_soft
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF \c DIMSTYLE symbol table entry. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the
                 * \c dictionary_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
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
        dimstyle->dictionary_owner_soft = strdup (dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle);
}


/*!
 * \brief Get the soft pointer to the object owner from a DXF 
 * \c DIMSTYLE symbol table.
 *
 * \return soft pointer to the object owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_dimstyle_get_object_owner_soft
(
        DxfDimStyle *dimstyle
                /*!< a pointer to a DXF \c DIMSTYLE symbol table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimstyle->object_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (dimstyle->object_owner_soft));
}


/*!
 * \brief Set the pointer to the \c object_owner_soft for a DXF
 * \c DIMSTYLE symbol table.
 *
 * \return a pointer to \c dimstyle when sucessful, \c NULL when an error
 * occurred.
 */
DxfDimStyle *
dxf_dimstyle_set_object_owner_soft
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF \c DIMSTYLE symbol table. */
        char *object_owner_soft
                /*!< a string containing the pointer to the
                 * \c object_owner_soft for the symbol table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
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
        dimstyle->object_owner_soft = strdup (object_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_hard from a DXF 
 * \c DIMSTYLE symbol table entry.
 *
 * \return a pointer to the \c dictionary_owner_hard.
 *
 * \warning No checks are performed on the returned pointer.
 */
char *
dxf_dimstyle_get_dictionary_owner_hard
(
        DxfDimStyle *dimstyle
                /*!< a pointer to a DXF \c DIMSTYLE symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimstyle->dictionary_owner_hard ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (dimstyle->dictionary_owner_hard));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_hard for a DXF
 * \c DIMSTYLE symbol table entry.
 *
 * \return a pointer to \c dimstyle when sucessful, \c NULL when an error
 * occurred.
 */
DxfDimStyle *
dxf_dimstyle_set_dictionary_owner_hard
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF \c DIMSTYLE symbol table entry. */
        char *dictionary_owner_hard
                /*!< a string containing the pointer to the \c
                 * dictionary_owner_hard for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
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
        dimstyle->dictionary_owner_hard = strdup (dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle);
}


/*!
 * \brief Get the dimension text style value (\c dimtxsty) from a DXF
 * dimension style symbol table (\c DIMSTYLE).
 *
 * \return the dimension text style value (\c dimtxsty).
 */
char *
dxf_dimstyle_get_dimtxsty
(
        DxfDimStyle *dimstyle
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimstyle->dimtxsty == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (dimstyle->dimtxsty));
}


/*!
 * \brief Set the dimension text style value (\c dimtxsty) for this DXF
 * dimension style symbol table (\c DIMSTYLE).
 *
 * \return a pointer to \c dimstyle when sucessful, \c NULL when an error
 * occurred.
 */
DxfDimStyle *
dxf_dimstyle_set_dimtxsty
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
        char *dimtxsty
                /*!< the dimension text style value (\c dimtxsty) to be
                 * set for the symbol table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimtxsty == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dimstyle->dimtxsty = strdup (dimtxsty);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle);
}


/*!
 * \brief Get the pointer to the next \c DIMSTYLE dimension style symbol
 * table from a DXF \c DIMSTYLE dimension style symbol table.
 *
 * \return pointer to the next \c DIMSTYLE dimension style symbol table.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfDimStyle *
dxf_dimstyle_get_next
(
        DxfDimStyle *dimstyle
                /*!< a pointer to a DXF \c DIMSTYLE dimension style
                 * symbol table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimstyle->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfDimStyle *) dimstyle->next);
}


/*!
 * \brief Set the pointer to the next \c DIMSTYLE for a DXF \c DIMSTYLE
 * dimension style symbol table.
 *
 * \return a pointer to \c dimstyle when sucessful, \c NULL when an error
 * occurred.
 */
DxfDimStyle *
dxf_dimstyle_set_next
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF \c DIMSTYLE dimension style
                 * symbol table. */
        DxfDimStyle *next
                /*!< a pointer to the next \c DIMSTYLE for the symbol
                 * table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
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
        dimstyle->next = (struct DxfDimStyle *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dimstyle);
}


/*!
 * \brief Get the pointer to the last \c DIMSTYLE dimension style symbol
 * table from a linkedlist of DXF \c DIMSTYLE dimension style symbol
 * tables.
 *
 * \return pointer to the last \c DIMSTYLE dimension style symbol table.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfDimStyle *
dxf_dimstyle_get_last
(
        DxfDimStyle *dimstyle
                /*!< a pointer to a DXF \c DIMSTYLE dimension style
                 * symbol table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dimstyle->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfDimStyle *) dimstyle);
        }
        DxfDimStyle *iter = (DxfDimStyle *) dimstyle->next;
        while (iter->next != NULL)
        {
                iter = (DxfDimStyle *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfDimStyle *) iter);
}


/* EOF */
