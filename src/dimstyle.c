/*!
 * \file dimstyle.c
 *
 * \author Copyright (C) 2012 ... 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF dimension style table (\c DIMSTYLE).
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
 * allocated memory when succesful.
 *
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfDimStyle *
dxf_dimstyle_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfDimStyle *dxf_dimstyle = NULL;
        size_t size;

        size = sizeof (DxfDimStyle);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_dimstyle = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfDimStyle struct.\n")),
                  __FUNCTION__);
                dxf_dimstyle = NULL;
        }
        else
        {
                memset (dxf_dimstyle, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_dimstyle);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c
 * DIMSTYLE entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 *
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfDimStyle *
dxf_dimstyle_init
(
        DxfDimStyle *dxf_dimstyle
                /*!< Pointer to the memory occupied by the DXF \c
                 * DIMSTYLE table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (dxf_dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                dxf_dimstyle = dxf_dimstyle_new ();
        }
        if (dxf_dimstyle == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory for a DxfDimStyle struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        dxf_dimstyle->dimstyle_name = strdup ("");
        dxf_dimstyle->dimpost = strdup ("");
        dxf_dimstyle->dimapost = strdup ("");
        dxf_dimstyle->dimblk = strdup ("");
        dxf_dimstyle->dimblk1 = strdup ("");
        dxf_dimstyle->dimblk2 = strdup ("");
        dxf_dimstyle->dimscale = 0.0;
        dxf_dimstyle->dimasz = 0.0;
        dxf_dimstyle->dimexo = 0.0;
        dxf_dimstyle->dimdli = 0.0;
        dxf_dimstyle->dimexe = 0.0;
        dxf_dimstyle->dimrnd = 0.0;
        dxf_dimstyle->dimdle = 0.0;
        dxf_dimstyle->dimtp = 0.0;
        dxf_dimstyle->dimtm = 0.0;
        dxf_dimstyle->flag = 0;
        dxf_dimstyle->dimtol = 0;
        dxf_dimstyle->dimlim = 0;
        dxf_dimstyle->dimtih = 0;
        dxf_dimstyle->dimtoh = 0;
        dxf_dimstyle->dimse1 = 0;
        dxf_dimstyle->dimse2 = 0;
        dxf_dimstyle->dimtad = 0;
        dxf_dimstyle->dimzin = 0;
        dxf_dimstyle->dimtxt = 0.0;
        dxf_dimstyle->dimcen = 0.0;
        dxf_dimstyle->dimtsz = 0.0;
        dxf_dimstyle->dimaltf = 0.0;
        dxf_dimstyle->dimlfac = 0.0;
        dxf_dimstyle->dimtvp = 0.0;
        dxf_dimstyle->dimtfac = 0.0;
        dxf_dimstyle->dimgap = 0.0;
        dxf_dimstyle->dimalt = 0;
        dxf_dimstyle->dimaltd = 0;
        dxf_dimstyle->dimtofl = 0;
        dxf_dimstyle->dimsah = 0;
        dxf_dimstyle->dimtix = 0;
        dxf_dimstyle->dimsoxd = 0;
        dxf_dimstyle->dimclrd = DXF_COLOR_BYLAYER;
        dxf_dimstyle->dimclre = DXF_COLOR_BYLAYER;
        dxf_dimstyle->dimclrt = DXF_COLOR_BYLAYER;
        dxf_dimstyle->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_dimstyle);
}


/*!
 * \brief Write DXF output for a DXF \c DIMSTYLE table.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 *
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
int
dxf_dimstyle_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfDimStyle *dxf_dimstyle
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
                return (EXIT_FAILURE);
        }
        if (dxf_dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (strcmp (dxf_dimstyle->dimstyle_name, "") == 0)
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
        if (!dxf_dimstyle->dimstyle_name)
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
        if (!dxf_dimstyle->dimpost)
        {
                dxf_dimstyle->dimpost = strdup ("");
        }
        if (!dxf_dimstyle->dimapost)
        {
                dxf_dimstyle->dimapost = strdup ("");
        }
        if (!dxf_dimstyle->dimblk)
        {
                dxf_dimstyle->dimblk = strdup ("");
        }
        if (!dxf_dimstyle->dimblk1)
        {
                dxf_dimstyle->dimblk1 = strdup ("");
        }
        if (!dxf_dimstyle->dimblk2)
        {
                dxf_dimstyle->dimblk2 = strdup ("");
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (dxf_dimstyle->id_code != -1)
        {
                fprintf (fp->fp, "105\n%x\n", dxf_dimstyle->id_code);
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbSymbolTableRecord\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbDimStyleTableRecord\n");
        }
        fprintf (fp->fp, "  2\n%s\n", dxf_dimstyle->dimstyle_name);
        fprintf (fp->fp, " 70\n%d\n", dxf_dimstyle->flag);
        fprintf (fp->fp, "  3\n%s\n", dxf_dimstyle->dimpost);
        fprintf (fp->fp, "  4\n%s\n", dxf_dimstyle->dimapost);
        if (fp->acad_version_number < AutoCAD_2000)
        {
                fprintf (fp->fp, "  5\n%s\n", dxf_dimstyle->dimblk);
        }
        if (fp->acad_version_number < AutoCAD_2000)
        {
                fprintf (fp->fp, "  6\n%s\n", dxf_dimstyle->dimblk1);
        }
        if (fp->acad_version_number < AutoCAD_2000)
        {
                fprintf (fp->fp, "  7\n%s\n", dxf_dimstyle->dimblk2);
        }
        fprintf (fp->fp, " 40\n%f\n", dxf_dimstyle->dimscale);
        fprintf (fp->fp, " 41\n%f\n", dxf_dimstyle->dimasz);
        fprintf (fp->fp, " 42\n%f\n", dxf_dimstyle->dimexo);
        fprintf (fp->fp, " 43\n%f\n", dxf_dimstyle->dimdli);
        fprintf (fp->fp, " 44\n%f\n", dxf_dimstyle->dimexe);
        fprintf (fp->fp, " 45\n%f\n", dxf_dimstyle->dimrnd);
        fprintf (fp->fp, " 46\n%f\n", dxf_dimstyle->dimdle);
        fprintf (fp->fp, " 47\n%f\n", dxf_dimstyle->dimtp);
        fprintf (fp->fp, " 48\n%f\n", dxf_dimstyle->dimtm);
        fprintf (fp->fp, "140\n%f\n", dxf_dimstyle->dimtxt);
        fprintf (fp->fp, "141\n%f\n", dxf_dimstyle->dimcen);
        fprintf (fp->fp, "142\n%f\n", dxf_dimstyle->dimtsz);
        fprintf (fp->fp, "143\n%f\n", dxf_dimstyle->dimaltf);
        fprintf (fp->fp, "144\n%f\n", dxf_dimstyle->dimlfac);
        fprintf (fp->fp, "145\n%f\n", dxf_dimstyle->dimtvp);
        fprintf (fp->fp, "146\n%f\n", dxf_dimstyle->dimtfac);
        fprintf (fp->fp, "147\n%f\n", dxf_dimstyle->dimgap);
        fprintf (fp->fp, " 71\n%d\n", dxf_dimstyle->dimtol);
        fprintf (fp->fp, " 72\n%d\n", dxf_dimstyle->dimlim);
        fprintf (fp->fp, " 73\n%d\n", dxf_dimstyle->dimtih);
        fprintf (fp->fp, " 74\n%d\n", dxf_dimstyle->dimtoh);
        fprintf (fp->fp, " 75\n%d\n", dxf_dimstyle->dimse1);
        fprintf (fp->fp, " 76\n%d\n", dxf_dimstyle->dimse2);
        fprintf (fp->fp, " 77\n%d\n", dxf_dimstyle->dimtad);
        fprintf (fp->fp, " 78\n%d\n", dxf_dimstyle->dimzin);
        fprintf (fp->fp, "170\n%d\n", dxf_dimstyle->dimalt);
        fprintf (fp->fp, "171\n%d\n", dxf_dimstyle->dimaltd);
        fprintf (fp->fp, "172\n%d\n", dxf_dimstyle->dimtofl);
        fprintf (fp->fp, "173\n%d\n", dxf_dimstyle->dimsah);
        fprintf (fp->fp, "174\n%d\n", dxf_dimstyle->dimtix);
        fprintf (fp->fp, "175\n%d\n", dxf_dimstyle->dimsoxd);
        fprintf (fp->fp, "176\n%d\n", dxf_dimstyle->dimclrd);
        fprintf (fp->fp, "177\n%d\n", dxf_dimstyle->dimclre);
        fprintf (fp->fp, "178\n%d\n", dxf_dimstyle->dimclrt);
        if ((fp->acad_version_number >= AutoCAD_13)
          && (fp->acad_version_number < AutoCAD_2000))
        {
                fprintf (fp->fp, "270\n%d\n", dxf_dimstyle->dimunit);
                fprintf (fp->fp, "271\n%d\n", dxf_dimstyle->dimdec);
                fprintf (fp->fp, "272\n%d\n", dxf_dimstyle->dimtdec);
                fprintf (fp->fp, "273\n%d\n", dxf_dimstyle->dimaltu);
                fprintf (fp->fp, "274\n%d\n", dxf_dimstyle->dimalttd);
                fprintf (fp->fp, "340\n%d\n", dxf_dimstyle->dimtxsty);
                fprintf (fp->fp, "275\n%d\n", dxf_dimstyle->dimaunit);
                fprintf (fp->fp, "280\n%d\n", dxf_dimstyle->dimjust);
                fprintf (fp->fp, "281\n%d\n", dxf_dimstyle->dimsd1);
                fprintf (fp->fp, "282\n%d\n", dxf_dimstyle->dimsd2);
                fprintf (fp->fp, "283\n%d\n", dxf_dimstyle->dimtolj);
                fprintf (fp->fp, "284\n%d\n", dxf_dimstyle->dimtzin);
                fprintf (fp->fp, "285\n%d\n", dxf_dimstyle->dimaltz);
                fprintf (fp->fp, "286\n%d\n", dxf_dimstyle->dimalttz);
                fprintf (fp->fp, "287\n%d\n", dxf_dimstyle->dimfit);
                fprintf (fp->fp, "288\n%d\n", dxf_dimstyle->dimupt);
                fprintf (fp->fp, "  0\nENDTAB\n");
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Read data from a DXF file into a DXF \c DIMSTYLE table.
 *
 * The last line read from file contained the string "DIMSTYLE". \n
 * Now follows some data for the \c DIMSTYLE, to be terminated with a
 * "  0" string announcing the following table, or the end of the
 * \c TABLES section marker \c ENDTAB. \n
 *
 * \return a pointer to \c dxf_dimstyle.
 *
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfDimStyle *
dxf_dimstyle_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfDimStyle *dxf_dimstyle
                /*!< Pointer to the memory occupied by the DXF \c
                 * DIMSTYLE table. */
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
                return (NULL);
        }
        if (dxf_dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                dxf_dimstyle = dxf_dimstyle_new ();
                dxf_dimstyle = dxf_dimstyle_init (dxf_dimstyle);
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
                if (strcmp (temp_string, "2") == 0)
                {
                        /* Now follows a string containing a dimension
                         * style name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_dimstyle->dimstyle_name);
                }
                else if (strcmp (temp_string, "3") == 0)
                {
                        /* Now follows a string containing a general
                         * dimensioning suffix. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_dimstyle->dimpost);
                }
                else if (strcmp (temp_string, "4") == 0)
                {
                        /* Now follows a string containing an alternate
                         * dimensioning suffix. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_dimstyle->dimapost);
                }
                else if ((fp->acad_version_number < AutoCAD_2000)
                        && (strcmp (temp_string, "5") == 0))
                {
                        /* Now follows a string containing an arrow
                         * block name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_dimstyle->dimblk);
                }
                else if ((fp->acad_version_number < AutoCAD_2000)
                        && (strcmp (temp_string, "6") == 0))
                {
                        /* Now follows a string containing a first arrow
                         * block name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_dimstyle->dimblk1);
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
                        fscanf (fp->fp, "%x\n", &dxf_dimstyle->id_code);
                }
#endif
                else if ((fp->acad_version_number < AutoCAD_2000)
                        && (strcmp (temp_string, "7") == 0))
                {
                        /* Now follows a string containing a first arrow
                         * block name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_dimstyle->dimblk2);
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
                        fscanf (fp->fp, "%x\n", &dxf_dimstyle->id_code);
                }
#endif
                else if (strcmp (temp_string, "40") == 0)
                {
                        /* Now follows a string containing an overall
                         * dimensioning scale factor. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_dimstyle->dimscale);
                }
                else if (strcmp (temp_string, "41") == 0)
                {
                        /* Now follows a string containing a
                         * dimensioning arrow size. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_dimstyle->dimasz);
                }
                else if (strcmp (temp_string, "42") == 0)
                {
                        /* Now follows a string containing a
                         * extension line offset. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_dimstyle->dimexo);
                }
                else if (strcmp (temp_string, "43") == 0)
                {
                        /* Now follows a string containing a
                         * dimension line increment. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_dimstyle->dimdli);
                }
                else if (strcmp (temp_string, "44") == 0)
                {
                        /* Now follows a string containing a
                         * extension line extension. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_dimstyle->dimexe);
                }
                else if (strcmp (temp_string, "45") == 0)
                {
                        /* Now follows a string containing a
                         * rounding value for dimension distances. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_dimstyle->dimrnd);
                }
                else if (strcmp (temp_string, "46") == 0)
                {
                        /* Now follows a string containing a
                         * dimension line extension. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_dimstyle->dimdle);
                }
                else if (strcmp (temp_string, "47") == 0)
                {
                        /* Now follows a string containing a
                         * plus tolerance. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_dimstyle->dimtp);
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing a
                         * minus tolerance. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_dimstyle->dimtm);
                }
                else if (strcmp (temp_string, "70") == 0)
                {
                        /* Now follows a string containing a flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_dimstyle->flag);
                }
                else if (strcmp (temp_string, "71") == 0)
                {
                        /* Now follows a string containing a dimension
                         * tolerances flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_dimstyle->dimtol);
                }
                else if (strcmp (temp_string, "72") == 0)
                {
                        /* Now follows a string containing a dimension
                         * limits flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_dimstyle->dimlim);
                }
                else if (strcmp (temp_string, "73") == 0)
                {
                        /* Now follows a string containing a dimension
                         * text inside horizontal flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_dimstyle->dimtih);
                }
                else if (strcmp (temp_string, "74") == 0)
                {
                        /* Now follows a string containing a dimension
                         * text outside horizontal flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_dimstyle->dimtoh);
                }
                else if (strcmp (temp_string, "75") == 0)
                {
                        /* Now follows a string containing a first
                         * extension line suppression flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_dimstyle->dimse1);
                }
                else if (strcmp (temp_string, "76") == 0)
                {
                        /* Now follows a string containing a second
                         * extension line suppression flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_dimstyle->dimse2);
                }
                else if (strcmp (temp_string, "77") == 0)
                {
                        /* Now follows a string containing a text above
                         * dimension line flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_dimstyle->dimtad);
                }
                else if (strcmp (temp_string, "78") == 0)
                {
                        /* Now follows a string containing a zero
                         * suppression for "feet & inch" dimensions
                         * flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_dimstyle->dimzin);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
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
                        fscanf (fp->fp, "%x\n", &dxf_dimstyle->id_code);
                }
                else if (strcmp (temp_string, "140") == 0)
                {
                        /* Now follows a string containing a
                         * dimensioning text height. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_dimstyle->dimtxt);
                }
                else if (strcmp (temp_string, "141") == 0)
                {
                        /* Now follows a string containing a size of
                         * center mark/lines. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_dimstyle->dimcen);
                }
                else if (strcmp (temp_string, "142") == 0)
                {
                        /* Now follows a string containing a
                         * dimensioning tick size: 0 = no ticks. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_dimstyle->dimtsz);
                }
                else if (strcmp (temp_string, "143") == 0)
                {
                        /* Now follows a string containing a
                         * alternate unit scale factor. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_dimstyle->dimaltf);
                }
                else if (strcmp (temp_string, "144") == 0)
                {
                        /* Now follows a string containing a linear
                         * measurements scale factor. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_dimstyle->dimlfac);
                }
                else if (strcmp (temp_string, "145") == 0)
                {
                        /* Now follows a string containing a text
                         * vertical position. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_dimstyle->dimtvp);
                }
                else if (strcmp (temp_string, "146") == 0)
                {
                        /* Now follows a string containing a dimension
                         * tolerance display scale factor. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_dimstyle->dimtfac);
                }
                else if (strcmp (temp_string, "147") == 0)
                {
                        /* Now follows a string containing a dimension
                         * line gap. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &dxf_dimstyle->dimgap);
                }
                else if (strcmp (temp_string, "170") == 0)
                {
                        /* Now follows a string containing a alternate
                         * unit dimensioning flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_dimstyle->dimalt);
                }
                else if (strcmp (temp_string, "171") == 0)
                {
                        /* Now follows a string containing a alternate
                         * unit decimal places. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_dimstyle->dimaltd);
                }
                else if (strcmp (temp_string, "172") == 0)
                {
                        /* Now follows a string containing a text
                         * outside extensions, force line extensions
                         * between extensions flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_dimstyle->dimtofl);
                }
                else if (strcmp (temp_string, "173") == 0)
                {
                        /* Now follows a string containing a use
                         * separate arrow blocks flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_dimstyle->dimsah);
                }
                else if (strcmp (temp_string, "174") == 0)
                {
                        /* Now follows a string containing a force text
                         * inside extensions flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_dimstyle->dimtix);
                }
                else if (strcmp (temp_string, "175") == 0)
                {
                        /* Now follows a string containing a suppress
                         * outside-extensions dimension lines flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_dimstyle->dimsoxd);
                }
                else if (strcmp (temp_string, "176") == 0)
                {
                        /* Now follows a string containing a dimension
                         * line color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_dimstyle->dimclrd);
                }
                else if (strcmp (temp_string, "177") == 0)
                {
                        /* Now follows a string containing a dimension
                         * extension line color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_dimstyle->dimclre);
                }
                else if (strcmp (temp_string, "178") == 0)
                {
                        /* Now follows a string containing a dimension
                         * text color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_dimstyle->dimclrt);
                }
                else if (strcmp (temp_string, "270") == 0)
                {
                        /* Now follows a string containing a units
                         * format for all dimension style family members
                         * except angular. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_dimstyle->dimunit);
                }
                else if (strcmp (temp_string, "271") == 0)
                {
                        /* Now follows a string containing a number of
                         * decimal places for the tolerance values of
                         * a primary units dimension. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_dimstyle->dimdec);
                }
                else if (strcmp (temp_string, "272") == 0)
                {
                        /* Now follows a string containing a number of
                         * decimal places to display the tolerance
                         * values. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_dimstyle->dimtdec);
                }
                else if (strcmp (temp_string, "273") == 0)
                {
                        /* Now follows a string containing a units
                         * format for alternate units of all dimension
                         * style family members except angular. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_dimstyle->dimaltu);
                }
                else if (strcmp (temp_string, "274") == 0)
                {
                        /* Now follows a string containing a number of
                         * decimal places for tolerance values of an
                         * alternate units dimension. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_dimstyle->dimalttd);
                }
                else if (strcmp (temp_string, "275") == 0)
                {
                        /* Now follows a string containing an angle
                         * format for angular dimensions. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_dimstyle->dimaunit);
                }
                else if (strcmp (temp_string, "280") == 0)
                {
                        /* Now follows a string containing a horizontal
                         * dimension text position. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_dimstyle->dimjust);
                }
                else if (strcmp (temp_string, "281") == 0)
                {
                        /* Now follows a string containing suppression
                         * of first extension line. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_dimstyle->dimsd1);
                }
                else if (strcmp (temp_string, "282") == 0)
                {
                        /* Now follows a string containing suppression
                         * of second extension line. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_dimstyle->dimsd2);
                }
                else if (strcmp (temp_string, "283") == 0)
                {
                        /* Now follows a string containing vertical
                         * justification for tolerance values. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_dimstyle->dimtolj);
                }
                else if (strcmp (temp_string, "284") == 0)
                {
                        /* Now follows a string containing suppression
                         * of zeros for tolerance values. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_dimstyle->dimtzin);
                }
                else if (strcmp (temp_string, "285") == 0)
                {
                        /* Now follows a string containing toggles
                         * suppression of zeros for alternate unit
                         * dimension values. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_dimstyle->dimaltz);
                }
                else if (strcmp (temp_string, "286") == 0)
                {
                        /* Now follows a string containing toggles
                         * suppression of zeros for tolerance values. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_dimstyle->dimalttz);
                }
                else if (strcmp (temp_string, "287") == 0)
                {
                        /* Now follows a string containing placement of
                         * text and arrowheads. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_dimstyle->dimfit);
                }
                else if (strcmp (temp_string, "288") == 0)
                {
                        /* Now follows a string containing cursor
                         * functionality for user positioned text. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_dimstyle->dimupt);
                }
                else if (strcmp (temp_string, "340") == 0)
                {
                        /* Now follows a string containing dimension
                         * text style. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_dimstyle->dimtxsty);
                }
        }
        /* Handle omitted members and/or illegal values. */
        if (strcmp (dxf_dimstyle->dimstyle_name, "") == 0)
        {
                fprintf (stderr,
                  (_("Error in %s () dimstyle_name value is empty.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_dimstyle);
}


/*!
 * \brief Free the allocated memory for a DXF \c DIMSTYLE and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 *
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
int
dxf_dimstyle_free
(
        DxfDimStyle *dxf_dimstyle
                /*!< Pointer to the memory occupied by the DXF \c
                 * DIMSTYLE table. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (dxf_dimstyle->next != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to next DxfDimStyle was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (dxf_dimstyle->dimstyle_name);
        free (dxf_dimstyle->dimpost);
        free (dxf_dimstyle->dimapost);
        free (dxf_dimstyle->dimblk);
        free (dxf_dimstyle->dimblk1);
        free (dxf_dimstyle->dimblk2);
        free (dxf_dimstyle);
        dxf_dimstyle = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
