/*!
 * \file dim.c
 *
 * \author Copyright (C) 2012 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF dimension entity (\c DIM).
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


#include "dim.h"


/*!
 * \brief Allocate memory for a DXF \c DIMSTYLE.
 *
 * Fill the memory contents with zeros.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfDimStyle *
dxf_dimstyle_new ()
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_dimstyle_new () function.\n",
                __FILE__, __LINE__);
#endif
        DxfDimStyle *dxf_dimstyle = NULL;
        size_t size;

        size = sizeof (DxfDimStyle);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_dimstyle = malloc (size)) == NULL)
        {
                fprintf (stderr, "ERROR in dxf_dimstyle_new () could not allocate memory for a DxfArc struct.\n");
                dxf_dimstyle = NULL;
        }
        else
        {
                memset (dxf_dimstyle, 0, size);
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_dimstyle_new () function.\n",
                __FILE__, __LINE__);
#endif
        return (dxf_dimstyle);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c
 * DIMSTYLE entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfDimStyle *
dxf_dimstyle_init
(
        DxfDimStyle *dxf_dimstyle
                /*!< DXF dimstyle entity. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_dimstyle_init () function.\n",
                __FILE__, __LINE__);
#endif
        dxf_dimstyle = dxf_dimstyle_new ();
        if (dxf_dimstyle == NULL)
        {
              fprintf (stderr, "ERROR in dxf_dimstyle_init () could not allocate memory for a DxfDimStyle struct.\n");
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
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_dimstyle_init () function.\n",
                __FILE__, __LINE__);
#endif
        return (dxf_dimstyle);
}


/*!
 * \brief Write DXF output for a DXF \c DIMSTYLE entity.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_dimstyle_write
(
        FILE *fp,
                /*!< file pointer to output file (or device). */
        DxfDimStyle dxf_dimstyle
                /*!< DXF \c DIMSTYLE entity. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_dimstyle_write () function.\n",
                __FILE__, __LINE__);
#endif
        char *dxf_entity_name = strdup ("DIMSTYLE");

        if (&dxf_dimstyle == NULL)
        {
                return (EXIT_FAILURE);
                fprintf (stderr, "Error in dxf_dimstyle_write () a NULL pointer was passed.\n");
        }
        if (strcmp (dxf_dimstyle.dimstyle_name, "") == 0)
        {
                fprintf (stderr, "Error in dxf_dimstyle_write () dimstyle_name value is empty for the %s entity.\n",
                        dxf_entity_name);
                fprintf (stderr, "    skipping %s entity.\n",
                        dxf_entity_name);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (!dxf_dimstyle.dimstyle_name)
        {
                fprintf (stderr, "Error in dxf_dimstyle_write () dimstyle_name value is NULL for the %s entity.\n",
                        dxf_entity_name);
                fprintf (stderr, "    skipping %s entity.\n",
                        dxf_entity_name);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        fprintf (fp, "  0\n%s\n", dxf_entity_name);
        fprintf (fp, "  2\n%s\n", dxf_dimstyle.dimstyle_name);
        if (!dxf_dimstyle.dimpost)
        {
                dxf_dimstyle.dimpost = strdup ("");
        }
        fprintf (fp, "  3\n%s\n", dxf_dimstyle.dimpost);
        if (!dxf_dimstyle.dimapost)
        {
                dxf_dimstyle.dimapost = strdup ("");
        }
        fprintf (fp, "  4\n%s\n", dxf_dimstyle.dimapost);
        if (!dxf_dimstyle.dimblk)
        {
                dxf_dimstyle.dimblk = strdup ("");
        }
        fprintf (fp, "  5\n%s\n", dxf_dimstyle.dimblk);
        if (!dxf_dimstyle.dimblk1)
        {
                dxf_dimstyle.dimblk1 = strdup ("");
        }
        fprintf (fp, "  6\n%s\n", dxf_dimstyle.dimblk1);
        if (!dxf_dimstyle.dimblk2)
        {
                dxf_dimstyle.dimblk2 = strdup ("");
        }
        fprintf (fp, "  7\n%s\n", dxf_dimstyle.dimblk2);
        fprintf (fp, " 40\n%f\n", dxf_dimstyle.dimscale);
        fprintf (fp, " 41\n%f\n", dxf_dimstyle.dimasz);
        fprintf (fp, " 42\n%f\n", dxf_dimstyle.dimexo);
        fprintf (fp, " 43\n%f\n", dxf_dimstyle.dimdli);
        fprintf (fp, " 44\n%f\n", dxf_dimstyle.dimexe);
        fprintf (fp, " 45\n%f\n", dxf_dimstyle.dimrnd);
        fprintf (fp, " 46\n%f\n", dxf_dimstyle.dimdle);
        fprintf (fp, " 47\n%f\n", dxf_dimstyle.dimtp);
        fprintf (fp, " 48\n%f\n", dxf_dimstyle.dimtm);
        fprintf (fp, " 70\n%d\n", dxf_dimstyle.flag);
        fprintf (fp, " 71\n%d\n", dxf_dimstyle.dimtol);
        fprintf (fp, " 72\n%d\n", dxf_dimstyle.dimlim);
        fprintf (fp, " 73\n%d\n", dxf_dimstyle.dimtih);
        fprintf (fp, " 74\n%d\n", dxf_dimstyle.dimtoh);
        fprintf (fp, " 75\n%d\n", dxf_dimstyle.dimse1);
        fprintf (fp, " 76\n%d\n", dxf_dimstyle.dimse2);
        fprintf (fp, " 77\n%d\n", dxf_dimstyle.dimtad);
        fprintf (fp, " 78\n%d\n", dxf_dimstyle.dimzin);
        fprintf (fp, "140\n%f\n", dxf_dimstyle.dimtxt);
        fprintf (fp, "141\n%f\n", dxf_dimstyle.dimcen);
        fprintf (fp, "142\n%f\n", dxf_dimstyle.dimtsz);
        fprintf (fp, "143\n%f\n", dxf_dimstyle.dimaltf);
        fprintf (fp, "144\n%f\n", dxf_dimstyle.dimlfac);
        fprintf (fp, "145\n%f\n", dxf_dimstyle.dimtvp);
        fprintf (fp, "146\n%f\n", dxf_dimstyle.dimtfac);
        fprintf (fp, "147\n%f\n", dxf_dimstyle.dimgap);
        fprintf (fp, "170\n%d\n", dxf_dimstyle.dimalt);
        fprintf (fp, "171\n%d\n", dxf_dimstyle.dimaltd);
        fprintf (fp, "172\n%d\n", dxf_dimstyle.dimtofl);
        fprintf (fp, "173\n%d\n", dxf_dimstyle.dimsah);
        fprintf (fp, "174\n%d\n", dxf_dimstyle.dimtix);
        fprintf (fp, "175\n%d\n", dxf_dimstyle.dimsoxd);
        fprintf (fp, "176\n%d\n", dxf_dimstyle.dimclrd);
        fprintf (fp, "177\n%d\n", dxf_dimstyle.dimclre);
        fprintf (fp, "178\n%d\n", dxf_dimstyle.dimclrt);
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_dimstyle_write () function.\n",
                __FILE__, __LINE__);
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
        DxfDimStyle *dxf_dimstyle
                /*!< Pointer to the memory occupied by the DXF \c
                 * DIMSTYLE entity. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_dimstyle_free () function.\n",
                __FILE__, __LINE__);
#endif
        if (dxf_dimstyle->next != NULL)
        {
              fprintf (stderr, "ERROR in dxf_dimstyle_free () pointer to next DxfDimStyle was not NULL.\n");
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
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_dimstyle_free () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
