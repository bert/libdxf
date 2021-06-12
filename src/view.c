/*!
 * \file view.c
 *
 * \author Copyright (C) 2015, 2017, 2018, 2019, 2020, 2021
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF View symbol table entry (\c VIEW).
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
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


#include "view.h"


/*!
 * \brief Allocate memory for a DXF \c VIEW.
 *
 * Fill the memory contents with zeros.
 *
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfView *
dxf_view_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfView *view = NULL;
        size_t size;

        size = sizeof (DxfView);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((view = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfView struct.\n")),
                  __FUNCTION__);
                view = NULL;
        }
        else
        {
                memset (view, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (view);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c VIEW
 * entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfView *
dxf_view_init
(
        DxfView *view
                /*!< a pointer to the DXF \c VIEW symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (view == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                view = dxf_view_new ();
        }
        if (view == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory for a DxfView struct.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        view->id_code = 0;
        view->name = strdup ("");
        view->p0 = dxf_point_new ();
        view->p0 = dxf_point_init (view->p0);
        view->p0->x0 = 0.0;
        view->p0->y0 = 0.0;
        view->p1 = dxf_point_new ();
        view->p1 = dxf_point_init (view->p1);
        view->p1->x0 = 0.0;
        view->p1->y0 = 0.0;
        view->p1->z0 = 0.0;
        view->p2 = dxf_point_new ();
        view->p2 = dxf_point_init (view->p2);
        view->p2->x0 = 0.0;
        view->p2->y0 = 0.0;
        view->p2->z0 = 0.0;
        view->height = 0.0;
        view->width = 0.0;
        view->lens_length = 0.0;
        view->front_plane_offset = 0.0;
        view->back_plane_offset = 0.0;
        view->twist_angle = 0.0;
        view->flag = 0;
        view->mode = 0;
        view->dictionary_owner_soft = strdup ("");
        view->dictionary_owner_hard = strdup ("");
        view->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (view);
}


/*!
 * \brief Read data from a DXF file into a DXF \c VIEW entity.
 *
 * The last line read from file contained the string "VIEW". \n
 * Now follows some data for the \c VIEW, to be terminated with a "  0"
 * string announcing the following table record, or the end of the
 * \c TABLE section marker \c ENDTAB. \n
 * While parsing the DXF file store data in \c view. \n
 *
 * \return a pointer to \c view.
 */
DxfView *
dxf_view_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfView *view
                /*!< a pointer to the DXF \c VIEW symbol table entry. */
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
        if (view == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                view = dxf_view_init (view);
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
                if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", (uint *) &view->id_code);
                }
                else if (strcmp (temp_string, "2") == 0)
                {
                        /* Now follows a string containing a view
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, view->name);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the View center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &view->p0->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the View center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &view->p0->y0);
                }
                else if (strcmp (temp_string, "11") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the View direction from
                         * target. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &view->p1->x0);
                }
                else if (strcmp (temp_string, "21") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the View direction from
                         * target. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &view->p1->y0);
                }
                else if (strcmp (temp_string, "31") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the View direction from
                         * target. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &view->p1->z0);
                }
                else if (strcmp (temp_string, "12") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the Target point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &view->p2->x0);
                }
                else if (strcmp (temp_string, "22") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the Target point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &view->p2->y0);
                }
                else if (strcmp (temp_string, "32") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the Target point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &view->p2->z0);
                }
                else if (strcmp (temp_string, "40") == 0)
                {
                        /* Now follows a string containing the view
                         * height. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &view->height);
                }
                else if (strcmp (temp_string, "41") == 0)
                {
                        /* Now follows a string containing the view
                         * width. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &view->width);
                }
                else if (strcmp (temp_string, "42") == 0)
                {
                        /* Now follows a string containing the lens
                         * length. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &view->lens_length);
                }
                else if (strcmp (temp_string, "43") == 0)
                {
                        /* Now follows a string containing the Front
                         * clipping plane - offset from target point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &view->front_plane_offset);
                }
                else if (strcmp (temp_string, "44") == 0)
                {
                        /* Now follows a string containing the Back
                         * clipping plane - offset from target point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &view->back_plane_offset);
                }
                else if (strcmp (temp_string, "50") == 0)
                {
                        /* Now follows a string containing the view
                         * twist angle. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &view->twist_angle);
                }
                else if (strcmp (temp_string, "70") == 0)
                {
                        /* Now follows a string containing the
                         * standard flag value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &view->flag);
                }
                else if (strcmp (temp_string, "71") == 0)
                {
                        /* Now follows a string containing the view mode
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &view->mode);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        if ((strcmp (temp_string, "AcDbSymbolTableRecord") != 0)
                        && ((strcmp (temp_string, "AcDbViewTableRecord") != 0)))
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () found a bad subclass marker in: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                        }
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing Soft-pointer
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, view->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, view->dictionary_owner_hard);
                }
                else if (strcmp (temp_string, "999") == 0)
                {
                        /* Now follows a string containing a comment. */
                        (fp->line_number)++;
                        fscanf (fp->fp, DXF_MAX_STRING_FORMAT, temp_string);
                        fprintf (stdout, "DXF comment: %s\n", temp_string);
                }
                else
                {
                        fprintf (stderr,
                          (_("Warning in %s () unknown string tag found while reading from: %s in line: %d.\n")),
                          __FUNCTION__, fp->filename, fp->line_number);
                }
        }
        /* Clean up. */
        free (temp_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (view);
}


/*!
 * \brief Write DXF output to a file for a DXF \c VIEW entity.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_view_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfView *view
                /*!< a pointer to the DXF \c VIEW symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("VIEW");

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
        if (view == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if ((view->name == NULL)
          || (strcmp (view->name, "") == 0))
        {
                fprintf (stderr,
                  (_("Error in %s () empty UCS name string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, view->id_code);
                fprintf (stderr,
                  (_("\t%s entity is discarded from output.\n")),
                  dxf_entity_name);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (view->id_code != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", view->id_code);
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
        if ((strcmp (view->dictionary_owner_soft, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", view->dictionary_owner_soft);
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (view->dictionary_owner_hard, "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", view->dictionary_owner_hard);
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbSymbolTableRecord\n");
                fprintf (fp->fp, "100\nAcDbViewTableRecord\n");
        }
        fprintf (fp->fp, "  2\n%s\n", view->name);
        fprintf (fp->fp, " 40\n%f\n", view->height);
        fprintf (fp->fp, " 70\n%d\n", view->flag);
        fprintf (fp->fp, " 10\n%f\n", view->p0->x0);
        fprintf (fp->fp, " 20\n%f\n", view->p0->y0);
        fprintf (fp->fp, " 41\n%f\n", view->width);
        fprintf (fp->fp, " 11\n%f\n", view->p1->x0);
        fprintf (fp->fp, " 21\n%f\n", view->p1->y0);
        fprintf (fp->fp, " 31\n%f\n", view->p1->z0);
        fprintf (fp->fp, " 12\n%f\n", view->p2->x0);
        fprintf (fp->fp, " 22\n%f\n", view->p2->y0);
        fprintf (fp->fp, " 32\n%f\n", view->p2->z0);
        fprintf (fp->fp, " 42\n%f\n", view->lens_length);
        fprintf (fp->fp, " 43\n%f\n", view->front_plane_offset);
        fprintf (fp->fp, " 44\n%f\n", view->back_plane_offset);
        fprintf (fp->fp, " 50\n%f\n", view->twist_angle);
        fprintf (fp->fp, " 71\n%d\n", view->mode);
        /* Clean up. */
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c VIEW and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_view_free
(
        DxfView *view
                /*!< a pointer to the DXF \c VIEW symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (view == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (view->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (view->name);
        free (view->dictionary_owner_soft);
        free (view->dictionary_owner_hard);
        free (view);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c VIEW symbol table and all their data fields.
 */
void
dxf_view_free_list
(
        DxfView *views
                /*!< a pointer to the single linked list of DXF \c VIEW
                 * symbol table entries. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (views == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (views != NULL)
        {
                DxfView *iter = (DxfView *) views->next;
                dxf_view_free (views);
                views = (DxfView *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the \c id_code from a DXF \c VIEW symbol table entry.
 *
 * \return \c id_code.
 */
int
dxf_view_get_id_code
(
        DxfView *view
                /*!< a pointer to a DXF \c VIEW symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (view == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (view->id_code < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (view->id_code);
}


/*!
 * \brief Set the \c id_code for a DXF \c VIEW symbol table entry.
 */
DxfView *
dxf_view_set_id_code
(
        DxfView *view,
                /*!< a pointer to a DXF \c VIEW symbol table entry. */
        int id_code
                /*!< the \c id_code to be set for the entry.\n
                 * This is to be an unique (sequential) number in the
                 * DXF file. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (view == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (id_code < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        view->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (view);
}


/*!
 * \brief Get the \c name from a DXF \c VIEW symbol table entry.
 *
 * \return \c name when sucessful, \c NULL when an error occurred.
 */
char *
dxf_view_get_name
(
        DxfView *view
                /*!< a pointer to a DXF \c VIEW symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (view == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (view->name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (view->name));
}


/*!
 * \brief Set the \c name for a DXF \c VIEW symbol table entry.
 */
DxfView *
dxf_view_set_name
(
        DxfView *view,
                /*!< a pointer to a DXF \c VIEW symbol table entry. */
        char *name
                /*!< a pointer to a string containing the \c name
                 * to be set for the entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (view == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (name == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        view->name = strdup (name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (view);
}


/*!
 * \brief Get the view center point \c p0 of a DXF \c VIEW
 * symbol table entry.
 *
 * \return the view center point \c p0.
 */
DxfPoint *
dxf_view_get_p0
(
        DxfView *view
                /*!< a pointer to a DXF \c VIEW symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (view == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (view->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (view->p0);
}


/*!
 * \brief Set the view center point \c p0 of a DXF \c VIEW
 * symbol table entry.
 *
 * \return a pointer to a DXF \c VIEW symbol table entry.
 */
DxfView *
dxf_view_set_p0
(
        DxfView *view,
                /*!< a pointer to a DXF \c VIEW symbol table entry. */
        DxfPoint *p0
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (view == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        view->p0 = p0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (view);
}


/*!
 * \brief Get the X-value of the view center point \c x0 of a DXF
 * \c VIEW symbol table entry.
 *
 * \return the X-value of the view center point \c x0.
 */
double
dxf_view_get_x0
(
        DxfView *view
                /*!< a pointer to a DXF \c VIEW symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (view == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (view->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (view->p0->x0);
}


/*!
 * \brief Set the X-value of the view center point \c x0 of a DXF
 * \c VIEW symbol table entry.
 *
 * \return a pointer to \c view when successful, or \c NULL when an
 * error occurred.
 */
DxfView *
dxf_view_set_x0
(
        DxfView *view,
                /*!< a pointer to a DXF \c VIEW symbol table entry. */
        double x0
                /*!< the X-value of the view center point \c x0 of a DXF
                 * \c VIEW symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (view == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (view->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        view->p0->x0 = x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (view);
}


/*!
 * \brief Get the Y-value of the view center point \c y0 of a DXF
 * \c VIEW symbol table entry.
 *
 * \return the Y-value of the view center point \c y0.
 */
double
dxf_view_get_y0
(
        DxfView *view
                /*!< a pointer to a DXF \c VIEW symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (view == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (view->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (view->p0->y0);
}


/*!
 * \brief Set the Y-value of the view center point \c y0 of
 * a DXF \c VIEW symbol table entry.
 *
 * \return a pointer to \c view when successful, or \c NULL when an
 * error occurred.
 */
DxfView *
dxf_view_set_y0
(
        DxfView *view,
                /*!< a pointer to a DXF \c VIEW symbol table entry. */
        double y0
                /*!< the Y-value of the view center point \c y0 of a DXF
                 * \c VIEW symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (view == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (view->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        view->p0->y0 = y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (view);
}


/*!
 * \brief Get the view direction from target \c p1 of a DXF \c VIEW
 * symbol table entry.
 *
 * \return the view direction from target \c p1.
 */
DxfPoint *
dxf_view_get_p1
(
        DxfView *view
                /*!< a pointer to a DXF \c VIEW symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (view == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (view->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (view->p1);
}


/*!
 * \brief Set the view direction from target \c p1 of a DXF \c VIEW
 * symbol table entry.
 *
 * \return a pointer to a DXF \c VIEW symbol table entry.
 */
DxfView *
dxf_view_set_p1
(
        DxfView *view,
                /*!< a pointer to a DXF \c VIEW symbol table entry. */
        DxfPoint *p1
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (view == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        view->p1 = p1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (view);
}


/*!
 * \brief Get the X-value of the view direction from target \c x1 of a
 * DXF \c VIEW symbol table entry.
 *
 * \return the X-value of the view direction from target \c x1.
 */
double
dxf_view_get_x1
(
        DxfView *view
                /*!< a pointer to a DXF \c VIEW symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (view == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (view->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (view->p1->x0);
}


/*!
 * \brief Set the X-value of the view direction from target
 * \c x1 of a DXF \c VIEW symbol table entry.
 *
 * \return a pointer to \c view when successful, or \c NULL when an
 * error occurred.
 */
DxfView *
dxf_view_set_x1
(
        DxfView *view,
                /*!< a pointer to a DXF \c VIEW symbol table entry. */
        double x1
                /*!< the X-value of the view direction from target
                 * \c x1 of a DXF \c VIEW symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (view == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (view->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        view->p1->x0 = x1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (view);
}


/*!
 * \brief Get the Y-value of the view direction from target \c y1 of a
 * DXF \c VIEW symbol table entry.
 *
 * \return the Y-value of the view direction from target \c y1.
 */
double
dxf_view_get_y1
(
        DxfView *view
                /*!< a pointer to a DXF \c VIEW symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (view == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (view->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (view->p1->y0);
}


/*!
 * \brief Set the Y-value of the view direction from target
 * \c y1 of a DXF \c VIEW symbol table entry.
 *
 * \return a pointer to \c view when successful, or \c NULL when an
 * error occurred.
 */
DxfView *
dxf_view_set_y1
(
        DxfView *view,
                /*!< a pointer to a DXF \c VIEW symbol table entry. */
        double y1
                /*!< the Y-value of the view direction from target
                 * \c y1 of a DXF \c VIEW symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (view == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (view->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        view->p1->y0 = y1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (view);
}


/*!
 * \brief Get the Z-value of the view direction from target \c z1 of a
 * DXF \c VIEW symbol table entry.
 *
 * \return the Z-value of the view direction from target \c z1.
 */
double
dxf_view_get_z1
(
        DxfView *view
                /*!< a pointer to a DXF \c VIEW symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (view == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (view->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (view->p1->z0);
}


/*!
 * \brief Set the Z-value of the view direction from target
 * \c z1 of a DXF \c VIEW symbol table entry.
 *
 * \return a pointer to \c view when successful, or \c NULL when an
 * error occurred.
 */
DxfView *
dxf_view_set_z1
(
        DxfView *view,
                /*!< a pointer to a DXF \c VIEW symbol table entry. */
        double z1
                /*!< the Z-value of the view direction from target
                 * \c z1 of a DXF \c VIEW symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (view == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (view->p1 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        view->p1->z0 = z1;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (view);
}


/*!
 * \brief Get the view target point \c p2 of a DXF \c VIEW symbol table
 * entry.
 *
 * \return the view direction from target \c p2.
 */
DxfPoint *
dxf_view_get_p2
(
        DxfView *view
                /*!< a pointer to a DXF \c VIEW symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (view == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (view->p2 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (view->p2);
}


/*!
 * \brief Set the view target point \c p2 of a DXF \c VIEW
 * symbol table entry.
 *
 * \return a pointer to a DXF \c VIEW symbol table entry.
 */
DxfView *
dxf_view_set_p2
(
        DxfView *view,
                /*!< a pointer to a DXF \c VIEW symbol table entry. */
        DxfPoint *p2
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (view == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (p2 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        view->p2 = p2;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (view);
}


/*!
 * \brief Get the X-value of the view target point \c x2 of a
 * DXF \c VIEW symbol table entry.
 *
 * \return the X-value of the view target point \c x2.
 */
double
dxf_view_get_x2
(
        DxfView *view
                /*!< a pointer to a DXF \c VIEW symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (view == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (view->p2 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (view->p2->x0);
}


/*!
 * \brief Set the X-value of the view target point \c x2 of a DXF
 * \c VIEW symbol table entry.
 *
 * \return a pointer to \c view when successful, or \c NULL when an
 * error occurred.
 */
DxfView *
dxf_view_set_x2
(
        DxfView *view,
                /*!< a pointer to a DXF \c VIEW symbol table entry. */
        double x2
                /*!< the X-value of the view target point \c x2 of a DXF
                 * \c VIEW symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (view == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (view->p2 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        view->p2->x0 = x2;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (view);
}


/*!
 * \brief Get the Y-value of the view target point \c y2 of a
 * DXF \c VIEW symbol table entry.
 *
 * \return the Y-value of the view target point \c y2.
 */
double
dxf_view_get_y2
(
        DxfView *view
                /*!< a pointer to a DXF \c VIEW symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (view == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (view->p2 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (view->p2->y0);
}


/*!
 * \brief Set the Y-value of the view target point \c y2 of a DXF
 * \c VIEW symbol table entry.
 *
 * \return a pointer to \c view when successful, or \c NULL when an
 * error occurred.
 */
DxfView *
dxf_view_set_y2
(
        DxfView *view,
                /*!< a pointer to a DXF \c VIEW symbol table entry. */
        double y2
                /*!< the Y-value of the view target point \c y2 of a DXF
                 * \c VIEW symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (view == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (view->p2 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        view->p2->y0 = y2;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (view);
}


/*!
 * \brief Get the Z-value of the view target point \c z2 of a
 * DXF \c VIEW symbol table entry.
 *
 * \return the Z-value of the view target point \c z2.
 */
double
dxf_view_get_z2
(
        DxfView *view
                /*!< a pointer to a DXF \c VIEW symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (view == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (view->p2 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (view->p2->z0);
}


/*!
 * \brief Set the Z-value of the view target point \c z2 of a DXF
 * \c VIEW symbol table entry.
 *
 * \return a pointer to \c view when successful, or \c NULL when an
 * error occurred.
 */
DxfView *
dxf_view_set_z2
(
        DxfView *view,
                /*!< a pointer to a DXF \c VIEW symbol table entry. */
        double z2
                /*!< the Z-value of the view target point \c z2 of a DXF
                 * \c VIEW symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (view == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (view->p2 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        view->p2->z0 = z2;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (view);
}


/*!
 * \brief Get the \c height of a DXF \c VIEW symbol table entry.
 *
 * \return \c height.
 */
double
dxf_view_get_height
(
        DxfView *view
                /*!< a pointer to a DXF \c VIEW symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (view == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (view->height);
}


/*!
 * \brief Set the \c height of a DXF \c VIEW symbol table entry.
 *
 * \return a pointer to \c view when successful, or \c NULL when an
 * error occurred.
 */
DxfView *
dxf_view_set_height
(
        DxfView *view,
                /*!< a pointer to a DXF \c VIEW symbol table entry. */
        double height
                /*!< the \c height of a DXF \c VIEW symbol table
                 * entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (view == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        view->height = height;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (view);
}


/*!
 * \brief Get the \c width of a DXF \c VIEW symbol table entry.
 *
 * \return \c width.
 */
double
dxf_view_get_width
(
        DxfView *view
                /*!< a pointer to a DXF \c VIEW symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (view == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (view->width);
}


/*!
 * \brief Set the \c width of a DXF \c VIEW symbol table entry.
 *
 * \return a pointer to \c view when successful, or \c NULL when an
 * error occurred.
 */
DxfView *
dxf_view_set_width
(
        DxfView *view,
                /*!< a pointer to a DXF \c VIEW symbol table entry. */
        double width
                /*!< the \c width of a DXF \c VIEW symbol table
                 * entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (view == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        view->width = width;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (view);
}


/*!
 * \brief Get the \c lens_length of a DXF \c VIEW symbol table entry.
 *
 * \return \c lens_length.
 */
double
dxf_view_get_lens_length
(
        DxfView *view
                /*!< a pointer to a DXF \c VIEW symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (view == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (view->lens_length);
}


/*!
 * \brief Set the \c lens_length of a DXF \c VIEW symbol table entry.
 *
 * \return a pointer to \c view when successful, or \c NULL when an
 * error occurred.
 */
DxfView *
dxf_view_set_lens_length
(
        DxfView *view,
                /*!< a pointer to a DXF \c VIEW symbol table entry. */
        double lens_length
                /*!< the \c lens_length of a DXF \c VIEW symbol table
                 * entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (view == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        view->lens_length = lens_length;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (view);
}


/*!
 * \brief Get the \c front_plane_offset of a DXF \c VIEW symbol table
 * entry.
 *
 * \return \c front_plane_offset.
 */
double
dxf_view_get_front_plane_offset
(
        DxfView *view
                /*!< a pointer to a DXF \c VIEW symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (view == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (view->front_plane_offset);
}


/*!
 * \brief Set the \c front_plane_offset of a DXF \c VIEW symbol table
 * entry.
 *
 * \return a pointer to \c view when successful, or \c NULL when an
 * error occurred.
 */
DxfView *
dxf_view_set_front_plane_offset
(
        DxfView *view,
                /*!< a pointer to a DXF \c VIEW symbol table entry. */
        double front_plane_offset
                /*!< the \c front_plane_offset of a DXF \c VIEW symbol
                 * table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (view == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        view->front_plane_offset = front_plane_offset;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (view);
}


/*!
 * \brief Get the \c back_plane_offset of a DXF \c VIEW symbol table
 * entry.
 *
 * \return \c back_plane_offset.
 */
double
dxf_view_get_back_plane_offset
(
        DxfView *view
                /*!< a pointer to a DXF \c VIEW symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (view == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (view->back_plane_offset);
}


/*!
 * \brief Set the \c back_plane_offset of a DXF \c VIEW symbol table
 * entry.
 *
 * \return a pointer to \c view when successful, or \c NULL when an
 * error occurred.
 */
DxfView *
dxf_view_set_back_plane_offset
(
        DxfView *view,
                /*!< a pointer to a DXF \c VIEW symbol table entry. */
        double back_plane_offset
                /*!< the \c back_plane_offset of a DXF \c VIEW symbol
                 * table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (view == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        view->back_plane_offset = back_plane_offset;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (view);
}


/*!
 * \brief Get the \c twist_angle of a DXF \c VIEW symbol table
 * entry.
 *
 * \return \c twist_angle.
 */
double
dxf_view_get_twist_angle
(
        DxfView *view
                /*!< a pointer to a DXF \c VIEW symbol table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (view == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (view->twist_angle);
}


/*!
 * \brief Set the \c twist_angle of a DXF \c VIEW symbol table
 * entry.
 *
 * \return a pointer to \c view when successful, or \c NULL when an
 * error occurred.
 */
DxfView *
dxf_view_set_twist_angle
(
        DxfView *view,
                /*!< a pointer to a DXF \c VIEW symbol table entry. */
        double twist_angle
                /*!< the \c twist_angle of a DXF \c VIEW symbol
                 * table entry. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (view == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        view->twist_angle = twist_angle;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (view);
}


/*!
 * \brief Get the \c flag from a DXF \c VIEW symbol table entry.
 *
 * \return \c flag.
 */
int
dxf_view_get_flag
(
        DxfView *view
                /*!< a pointer to a DXF \c VIEW symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (view == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (view->flag < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (view->flag);
}


/*!
 * \brief Set the \c flag for a DXF \c VIEW symbol table entry.
 */
DxfView *
dxf_view_set_flag
(
        DxfView *view,
                /*!< a pointer to a DXF \c VIEW symbol table entry. */
        int flag
                /*!< the \c flag to be set for the entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (view == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (flag < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        view->flag = flag;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (view);
}


/*!
 * \brief Get the \c mode from a DXF \c VIEW symbol table entry.
 *
 * \return \c mode.
 */
int
dxf_view_get_mode
(
        DxfView *view
                /*!< a pointer to a DXF \c VIEW symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (view == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (view->mode < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (view->mode);
}


/*!
 * \brief Set the \c mode for a DXF \c VIEW symbol table entry.
 */
DxfView *
dxf_view_set_mode
(
        DxfView *view,
                /*!< a pointer to a DXF \c VIEW symbol table entry. */
        int mode
                /*!< the \c mode to be set for the entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (view == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mode < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        view->mode = mode;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (view);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_soft from a DXF 
 * \c VIEW symbol table entry.
 *
 * \return pointer to the \c dictionary_owner_soft.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_view_get_dictionary_owner_soft
(
        DxfView *view
                /*!< a pointer to a DXF \c VIEW symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (view == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (view->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (view->dictionary_owner_soft));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_soft for a DXF
 * \c VIEW symbol table entry.
 */
DxfView *
dxf_view_set_dictionary_owner_soft
(
        DxfView *view,
                /*!< a pointer to a DXF \c VIEW symbol table entry. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the \c
                 * dictionary_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (view == NULL)
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
        view->dictionary_owner_soft = strdup (dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (view);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_hard from a DXF 
 * \c VIEW symbol table entry.
 *
 * \return pointer to the \c dictionary_owner_hard.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_view_get_dictionary_owner_hard
(
        DxfView *view
                /*!< a pointer to a DXF \c VIEW symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (view == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (view->dictionary_owner_hard ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (view->dictionary_owner_hard));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_hard for a DXF
 * \c VIEW symbol table entry.
 */
DxfView *
dxf_view_set_dictionary_owner_hard
(
        DxfView *view,
                /*!< a pointer to a DXF \c VIEW symbol table entry. */
        char *dictionary_owner_hard
                /*!< a string containing the pointer to the \c
                 * dictionary_owner_hard for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (view == NULL)
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
        view->dictionary_owner_hard = strdup (dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (view);
}


/*!
 * \brief Get the pointer to the next \c VIEW symbol table entry from a
 * DXF \c VIEW symbol table entry.
 *
 * \return pointer to the next \c VIEW symbol table entry.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfView *
dxf_view_get_next
(
        DxfView *view
                /*!< a pointer to a DXF \c VIEW symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (view == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (view->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfView *) view->next);
}


/*!
 * \brief Set the pointer to the next \c VIEW for a DXF \c VIEW symbol
 * table entry.
 */
DxfView *
dxf_view_set_next
(
        DxfView *view,
                /*!< a pointer to a DXF \c VIEW symbol table entry. */
        DxfView *next
                /*!< a pointer to the next \c VIEW for the entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (view == NULL)
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
        view->next = (struct DxfView *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (view);
}


/*!
 * \brief Get the pointer to the last \c VIEW symbol table entry from a
 * linked list of DXF \c VIEW symbol table entries.
 *
 * \return pointer to the last \c VIEW symbol table entry.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfView *
dxf_view_get_last
(
        DxfView *view
                /*!< a pointer to a DXF \c VIEW symbol table entry. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (view == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (view->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfView *) view);
        }
        DxfView *iter = (DxfView *) view->next;
        while (iter->next != NULL)
        {
                iter = (DxfView *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfView *) iter);
}


/* EOF */
