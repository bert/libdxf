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
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
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
                  (_("Error in %s () could not allocate memory for a DxfDimStyle struct.\n")),
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
 * allocated memory when succesful.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
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
                (_("Error in %s () could not allocate memory for a DxfDimStyle struct.\n")),
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
        dimstyle->next = NULL;
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
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
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
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbSymbolTableRecord\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbDimStyleTableRecord\n");
        }
        fprintf (fp->fp, "  2\n%s\n", dimstyle->dimstyle_name);
        fprintf (fp->fp, " 70\n%d\n", dimstyle->flag);
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
        fprintf (fp->fp, " 71\n%d\n", dimstyle->dimtol);
        fprintf (fp->fp, " 72\n%d\n", dimstyle->dimlim);
        fprintf (fp->fp, " 73\n%d\n", dimstyle->dimtih);
        fprintf (fp->fp, " 74\n%d\n", dimstyle->dimtoh);
        fprintf (fp->fp, " 75\n%d\n", dimstyle->dimse1);
        fprintf (fp->fp, " 76\n%d\n", dimstyle->dimse2);
        fprintf (fp->fp, " 77\n%d\n", dimstyle->dimtad);
        fprintf (fp->fp, " 78\n%d\n", dimstyle->dimzin);
        fprintf (fp->fp, "170\n%d\n", dimstyle->dimalt);
        fprintf (fp->fp, "171\n%d\n", dimstyle->dimaltd);
        fprintf (fp->fp, "172\n%d\n", dimstyle->dimtofl);
        fprintf (fp->fp, "173\n%d\n", dimstyle->dimsah);
        fprintf (fp->fp, "174\n%d\n", dimstyle->dimtix);
        fprintf (fp->fp, "175\n%d\n", dimstyle->dimsoxd);
        fprintf (fp->fp, "176\n%d\n", dimstyle->dimclrd);
        fprintf (fp->fp, "177\n%d\n", dimstyle->dimclre);
        fprintf (fp->fp, "178\n%d\n", dimstyle->dimclrt);
        if ((fp->acad_version_number >= AutoCAD_13)
          && (fp->acad_version_number < AutoCAD_2000))
        {
                fprintf (fp->fp, "270\n%d\n", dimstyle->dimunit);
                fprintf (fp->fp, "271\n%d\n", dimstyle->dimdec);
                fprintf (fp->fp, "272\n%d\n", dimstyle->dimtdec);
                fprintf (fp->fp, "273\n%d\n", dimstyle->dimaltu);
                fprintf (fp->fp, "274\n%d\n", dimstyle->dimalttd);
                fprintf (fp->fp, "340\n%d\n", dimstyle->dimtxsty);
                fprintf (fp->fp, "275\n%d\n", dimstyle->dimaunit);
                fprintf (fp->fp, "280\n%d\n", dimstyle->dimjust);
                fprintf (fp->fp, "281\n%d\n", dimstyle->dimsd1);
                fprintf (fp->fp, "282\n%d\n", dimstyle->dimsd2);
                fprintf (fp->fp, "283\n%d\n", dimstyle->dimtolj);
                fprintf (fp->fp, "284\n%d\n", dimstyle->dimtzin);
                fprintf (fp->fp, "285\n%d\n", dimstyle->dimaltz);
                fprintf (fp->fp, "286\n%d\n", dimstyle->dimalttz);
                fprintf (fp->fp, "287\n%d\n", dimstyle->dimfit);
                fprintf (fp->fp, "288\n%d\n", dimstyle->dimupt);
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
 * \brief Read data from a DXF file into a DXF \c DIMSTYLE table.
 *
 * The last line read from file contained the string "DIMSTYLE". \n
 * Now follows some data for the \c DIMSTYLE, to be terminated with a
 * "  0" string announcing the following table, or the end of the
 * \c TABLES section marker \c ENDTAB. \n
 *
 * \return a pointer to \c dimstyle.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
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
                dimstyle = dxf_dimstyle_new ();
                dimstyle = dxf_dimstyle_init (dimstyle);
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
                        fscanf (fp->fp, "%s\n", dimstyle->dimstyle_name);
                }
                else if (strcmp (temp_string, "3") == 0)
                {
                        /* Now follows a string containing a general
                         * dimensioning suffix. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dimstyle->dimpost);
                }
                else if (strcmp (temp_string, "4") == 0)
                {
                        /* Now follows a string containing an alternate
                         * dimensioning suffix. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dimstyle->dimapost);
                }
                else if ((fp->acad_version_number < AutoCAD_2000)
                        && (strcmp (temp_string, "5") == 0))
                {
                        /* Now follows a string containing an arrow
                         * block name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dimstyle->dimblk);
                }
                else if ((fp->acad_version_number < AutoCAD_2000)
                        && (strcmp (temp_string, "6") == 0))
                {
                        /* Now follows a string containing a first arrow
                         * block name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dimstyle->dimblk1);
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
                        fscanf (fp->fp, "%s\n", dimstyle->dimblk2);
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
                        fscanf (fp->fp, "%d\n", &dimstyle->flag);
                }
                else if (strcmp (temp_string, "71") == 0)
                {
                        /* Now follows a string containing a dimension
                         * tolerances flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dimstyle->dimtol);
                }
                else if (strcmp (temp_string, "72") == 0)
                {
                        /* Now follows a string containing a dimension
                         * limits flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dimstyle->dimlim);
                }
                else if (strcmp (temp_string, "73") == 0)
                {
                        /* Now follows a string containing a dimension
                         * text inside horizontal flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dimstyle->dimtih);
                }
                else if (strcmp (temp_string, "74") == 0)
                {
                        /* Now follows a string containing a dimension
                         * text outside horizontal flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dimstyle->dimtoh);
                }
                else if (strcmp (temp_string, "75") == 0)
                {
                        /* Now follows a string containing a first
                         * extension line suppression flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dimstyle->dimse1);
                }
                else if (strcmp (temp_string, "76") == 0)
                {
                        /* Now follows a string containing a second
                         * extension line suppression flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dimstyle->dimse2);
                }
                else if (strcmp (temp_string, "77") == 0)
                {
                        /* Now follows a string containing a text above
                         * dimension line flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dimstyle->dimtad);
                }
                else if (strcmp (temp_string, "78") == 0)
                {
                        /* Now follows a string containing a zero
                         * suppression for "feet & inch" dimensions
                         * flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dimstyle->dimzin);
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
                        fscanf (fp->fp, "%x\n", &dimstyle->id_code);
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
                        fscanf (fp->fp, "%d\n", &dimstyle->dimalt);
                }
                else if (strcmp (temp_string, "171") == 0)
                {
                        /* Now follows a string containing a alternate
                         * unit decimal places. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dimstyle->dimaltd);
                }
                else if (strcmp (temp_string, "172") == 0)
                {
                        /* Now follows a string containing a text
                         * outside extensions, force line extensions
                         * between extensions flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dimstyle->dimtofl);
                }
                else if (strcmp (temp_string, "173") == 0)
                {
                        /* Now follows a string containing a use
                         * separate arrow blocks flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dimstyle->dimsah);
                }
                else if (strcmp (temp_string, "174") == 0)
                {
                        /* Now follows a string containing a force text
                         * inside extensions flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dimstyle->dimtix);
                }
                else if (strcmp (temp_string, "175") == 0)
                {
                        /* Now follows a string containing a suppress
                         * outside-extensions dimension lines flag. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dimstyle->dimsoxd);
                }
                else if (strcmp (temp_string, "176") == 0)
                {
                        /* Now follows a string containing a dimension
                         * line color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dimstyle->dimclrd);
                }
                else if (strcmp (temp_string, "177") == 0)
                {
                        /* Now follows a string containing a dimension
                         * extension line color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dimstyle->dimclre);
                }
                else if (strcmp (temp_string, "178") == 0)
                {
                        /* Now follows a string containing a dimension
                         * text color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dimstyle->dimclrt);
                }
                else if (strcmp (temp_string, "270") == 0)
                {
                        /* Now follows a string containing a units
                         * format for all dimension style family members
                         * except angular. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dimstyle->dimunit);
                }
                else if (strcmp (temp_string, "271") == 0)
                {
                        /* Now follows a string containing a number of
                         * decimal places for the tolerance values of
                         * a primary units dimension. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dimstyle->dimdec);
                }
                else if (strcmp (temp_string, "272") == 0)
                {
                        /* Now follows a string containing a number of
                         * decimal places to display the tolerance
                         * values. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dimstyle->dimtdec);
                }
                else if (strcmp (temp_string, "273") == 0)
                {
                        /* Now follows a string containing a units
                         * format for alternate units of all dimension
                         * style family members except angular. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dimstyle->dimaltu);
                }
                else if (strcmp (temp_string, "274") == 0)
                {
                        /* Now follows a string containing a number of
                         * decimal places for tolerance values of an
                         * alternate units dimension. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dimstyle->dimalttd);
                }
                else if (strcmp (temp_string, "275") == 0)
                {
                        /* Now follows a string containing an angle
                         * format for angular dimensions. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dimstyle->dimaunit);
                }
                else if (strcmp (temp_string, "280") == 0)
                {
                        /* Now follows a string containing a horizontal
                         * dimension text position. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dimstyle->dimjust);
                }
                else if (strcmp (temp_string, "281") == 0)
                {
                        /* Now follows a string containing suppression
                         * of first extension line. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dimstyle->dimsd1);
                }
                else if (strcmp (temp_string, "282") == 0)
                {
                        /* Now follows a string containing suppression
                         * of second extension line. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dimstyle->dimsd2);
                }
                else if (strcmp (temp_string, "283") == 0)
                {
                        /* Now follows a string containing vertical
                         * justification for tolerance values. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dimstyle->dimtolj);
                }
                else if (strcmp (temp_string, "284") == 0)
                {
                        /* Now follows a string containing suppression
                         * of zeros for tolerance values. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dimstyle->dimtzin);
                }
                else if (strcmp (temp_string, "285") == 0)
                {
                        /* Now follows a string containing toggles
                         * suppression of zeros for alternate unit
                         * dimension values. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dimstyle->dimaltz);
                }
                else if (strcmp (temp_string, "286") == 0)
                {
                        /* Now follows a string containing toggles
                         * suppression of zeros for tolerance values. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dimstyle->dimalttz);
                }
                else if (strcmp (temp_string, "287") == 0)
                {
                        /* Now follows a string containing placement of
                         * text and arrowheads. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dimstyle->dimfit);
                }
                else if (strcmp (temp_string, "288") == 0)
                {
                        /* Now follows a string containing cursor
                         * functionality for user positioned text. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dimstyle->dimupt);
                }
                else if (strcmp (temp_string, "340") == 0)
                {
                        /* Now follows a string containing dimension
                         * text style. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dimstyle->dimtxsty);
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
 * \brief Free the allocated memory for a DXF \c DIMSTYLE and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
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
        if (dimstyle->next != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to next DxfDimStyle was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (dimstyle->dimstyle_name);
        free (dimstyle->dimpost);
        free (dimstyle->dimapost);
        free (dimstyle->dimblk);
        free (dimstyle->dimblk1);
        free (dimstyle->dimblk2);
        free (dimstyle);
        dimstyle = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a chain of DXF \c DIMSTYLE
 * symbol table and all their data fields.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
void
dxf_dimstyle_free_chain
(
        DxfDimStyle *dimstyles
                /*!< pointer to the chain of DXF \c DIMSTYLE symbol
                 * tables. */
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
                struct DxfDimStyle *iter = dimstyles->next;
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
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
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
        char *result;

        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = strdup (dimstyle->dimstyle_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
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
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
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
                  (_("Warning in %s () the string name contained a NULL pointer.\n")),
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
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
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
        char *result;

        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = strdup (dimstyle->dimpost);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
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
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
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
                  (_("Warning in %s () the string name contained a NULL pointer.\n")),
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
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
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
        char *result;

        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = strdup (dimstyle->dimapost);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
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
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
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
                  (_("Warning in %s () the string name contained a NULL pointer.\n")),
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
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
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
        char *result;

        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = strdup (dimstyle->dimblk);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
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
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
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
                  (_("Warning in %s () the string contained a NULL pointer.\n")),
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
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
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
        char *result;

        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = strdup (dimstyle->dimblk1);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
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
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
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
                  (_("Warning in %s () the string contained a NULL pointer.\n")),
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
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
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
        char *result;

        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        result = strdup (dimstyle->dimblk2);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
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
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
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
                  (_("Warning in %s () the string contained a NULL pointer.\n")),
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
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
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
        double result;

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
                  (_("Error in %s () a value of zero was found in the dimscale member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = dimstyle->dimscale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the overall dimensioning scale factor value (\c dimscale)
 * for a DXF dimension style symbol table (\c DIMSTYLE).
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
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
                  (_("Error in %s () a value of zero was passed.\n")),
                  __FUNCTION__);
                return (NULL);
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
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
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
        double result;

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
                  (_("Error in %s () a value of zero was found in the dimasz member.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = dimstyle->dimasz;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the dimensioning arrow size value (\c dimasz) for a DXF
 * dimension style symbol table (\c DIMSTYLE).
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
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
                  (_("Error in %s () a value of zero was passed.\n")),
                  __FUNCTION__);
                return (NULL);
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
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
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
        double result;

        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = dimstyle->dimexo;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the extension line offset value (\c dimexo) for a DXF
 * dimension style symbol table (\c DIMSTYLE).
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
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
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
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
        double result;

        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = dimstyle->dimdli;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the dimension line increment value (\c dimdli) for a DXF
 * dimension style symbol table (\c DIMSTYLE).
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
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
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
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
        double result;

        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = dimstyle->dimexe;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the extension line extension value (\c dimexe) for a DXF
 * dimension style symbol table (\c DIMSTYLE).
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
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
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
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
        double result;

        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = dimstyle->dimrnd;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the rounding value for dimension distances (\c dimrnd)
 * for a DXF dimension style symbol table (\c DIMSTYLE).
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
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
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
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
        double result;

        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = dimstyle->dimdle;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the dimension line extension value (\c dimdle) for a DXF
 * dimension style symbol table (\c DIMSTYLE).
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
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
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
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
        double result;

        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = dimstyle->dimtp;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the plus tolerance value (\c dimtp) for a DXF dimension
 * style symbol table (\c DIMSTYLE).
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
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
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
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
        double result;

        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = dimstyle->dimtm;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the minus tolerance value (\c dimtm) for a DXF dimension
 * style symbol table (\c DIMSTYLE).
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
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
 * 
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
int
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
        int result;

        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = dimstyle->flag;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the flag value (\c flag) for this DXF dimension style
 * symbol table (\c DIMSTYLE).
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfDimStyle *
dxf_dimstyle_set_flag
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
        int flag
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
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
int
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
        int result;

        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = dimstyle->dimtol;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the dimension tolerances value (\c dimtol) for this DXF
 * dimension style symbol table (\c DIMSTYLE).
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfDimStyle *
dxf_dimstyle_set_dimtol
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
        int dimtol
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
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
int
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
        int result;

        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = dimstyle->dimlim;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the dimension limits value (\c dimlim) for this DXF
 * dimension style symbol table (\c DIMSTYLE).
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfDimStyle *
dxf_dimstyle_set_dimlim
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
        int dimlim
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
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
int
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
        int result;

        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = dimstyle->dimtih;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the text inside horizontal value (\c dimtih) for this DXF
 * dimension style symbol table (\c DIMSTYLE).
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfDimStyle *
dxf_dimstyle_set_dimtih
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
        int dimtih
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
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
int
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
        int result;

        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = dimstyle->dimtoh;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the text outside horizontal value (\c dimtoh) for this DXF
 * dimension style symbol table (\c DIMSTYLE).
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfDimStyle *
dxf_dimstyle_set_dimtoh
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
        int dimtoh
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
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
int
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
        int result;

        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = dimstyle->dimse1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the first extension line suppressed value (\c dimse1) for
 * this DXF dimension style symbol table (\c DIMSTYLE).
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfDimStyle *
dxf_dimstyle_set_dimse1
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
        int dimse1
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
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
int
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
        int result;

        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = dimstyle->dimse2;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the second extension line suppressed value (\c dimse2) for
 * this DXF dimension style symbol table (\c DIMSTYLE).
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfDimStyle *
dxf_dimstyle_set_dimse2
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
        int dimse2
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
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
int
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
        int result;

        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = dimstyle->dimtad;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the text above dimension line value (\c dimtad) for
 * this DXF dimension style symbol table (\c DIMSTYLE).
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfDimStyle *
dxf_dimstyle_set_dimtad
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
        int dimtad
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
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
int
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
        int result;

        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = dimstyle->dimzin;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the zero suppression for "feet & inch" dimensions value
 * (\c dimZIN) for this DXF dimension style symbol table (\c DIMSTYLE).
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 */
DxfDimStyle *
dxf_dimstyle_set_dimzin
(
        DxfDimStyle *dimstyle,
                /*!< a pointer to a DXF dimension style symbol table
                 * (\c DIMSTYLE). */
        int dimzin
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
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
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
        int result;

        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = dimstyle->id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the ID code for this DXF dimenstion style symbol table
 * (\c DIMSTYLE).
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
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
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
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
        double result;

        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = dimstyle->dimtxt;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the dimensioning text height value (\c dimtxt) for a DXF
 * dimension style symbol table (\c DIMSTYLE).
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
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
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
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
        double result;

        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = dimstyle->dimcen;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/*!
 * \brief Set the size of center mark/lines value (\c dimcen) for a DXF
 * dimension style symbol table (\c DIMSTYLE).
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
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
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
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
        double result;

        /* Do some basic checks. */
        if (dimstyle == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        result = dimstyle->dimtsz;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (result);
}


/* EOF */
