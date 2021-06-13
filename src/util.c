/*!
 * \file util.c
 *
 * \author Copyright (C) 2010 by Luis Matos <gass@otiliamatos.ath.cx>.
 *
 * \author Copyright (C) 2010, 2012, 2015, 2017, 2018, 2019
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for libDXF coding utilities.
 *
 * <hr>
 * <h1><b>Copyright Notices.</b></h1>\n
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.\n\n
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


#include <stdarg.h>
#include "util.h"


/*!
 * \brief Allocate memory for a \c DxfChar.
 *
 * Fill the memory contents with zeros.
 */
DxfChar *
dxf_char_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfChar *c = NULL;
        size_t size;

        size = sizeof (DxfChar);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((c = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                c = NULL;
        }
        else
        {
                memset (c, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (c);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c DxfChar
 * object.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfChar *
dxf_char_init
(
        DxfChar *c
                /*!< a pointer to the DxfChar object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (c == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                c = dxf_char_new ();
        }
        if (c == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory.\n")),
                __FUNCTION__);
              return (NULL);
        }
        c->value = strdup ("");
        c->length = 0;
        c->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (c);
}


/*!
 * \brief Get the \c value of a \c DxfChar object.
 *
 * \return the \c value.
 */
char *
dxf_char_get_value
(
        DxfChar *c
                /*!< a pointer to a \c DxfChar object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (c == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (c->value));
}


/*!
 * \brief Set the \c value of a \c DxfChar object.
 *
 * \return a pointer to \c c when successful, or \c NULL when an error
 * occurred.
 */
DxfChar *
dxf_char_set_value
(
        DxfChar *c,
                /*!< a pointer to a \c DxfDouble object. */
        char *value
                /*!< a pointer to a char \c value. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (c == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (value == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        c->value = strdup (value);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (c);
}


/*!
 * \brief Get the \c length of a \c DxfChar object.
 *
 * \return the \c length.
 */
int
dxf_char_get_length
(
        DxfChar *c
                /*!< a pointer to a \c DxfChar object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (c == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (c->length == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a value of zero was found.\n")),
                  __FUNCTION__);
        }
        if (c->length < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (c->length);
}


/*!
 * \brief Set the \c length of a \c DxfChar object.
 *
 * \return a pointer to \c c when successful, or \c NULL when an error
 * occurred.
 */
DxfChar *
dxf_char_set_length
(
        DxfChar *c,
                /*!< a pointer to a \c DxfDouble object. */
        int length
                /*!< \c length. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (c == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (length == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a value of zero was passed.\n")),
                  __FUNCTION__);
        }
        if (length < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        c->length = length;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (c);
}


/*!
 * \brief Get the \c next DxfChar object of a \c DxfChar object
 * (single linked list).
 *
 * \return the \c next DxfChar object in a single linked list.
 */
DxfChar *
dxf_char_get_next
(
        DxfChar *c
                /*!< a pointer to a \c DxfChar object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (c == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (c->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfChar *) c->next);
}


/*!
 * \brief Set the \c next DxfChar object of a \c DxfChar object
 * (single linked list).
 *
 * \return a pointer to \c c when successful, or \c NULL when an error
 * occurred.
 */
DxfChar *
dxf_char_set_next
(
        DxfChar *c,
                /*!< a pointer to a \c DxfChar object. */
        DxfChar *next
                /*!< a pointer to a \c DxfChar object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (c == NULL)
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
        c->next = (struct DxfChar *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (c);
}


/*!
 * \brief Get the pointer to the last \c DxfChar object from a linked
 * list of DXF \c DxfChar objects.
 *
 * \return pointer to the last \c DxfChar object.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfChar *
dxf_char_get_last
(
        DxfChar *c
                /*!< a pointer to a DXF \c DxfChar object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (c == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (c->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfChar *) c);
        }
        DxfChar *iter = (DxfChar *) c->next;
        while (iter->next != NULL)
        {
                iter = (DxfChar *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfChar *) iter);
}


/*!
 * \brief Free the allocated memory for a DxfChar object and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_char_free
(
        DxfChar *c
                /*!< a pointer to the memory occupied by the DxfChar
                 * object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (c == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (c->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (c->value);
        free (c);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DxfChar
 * objects and all their data fields.
 */
int
dxf_char_free_list
(
        DxfChar *chars
                /*!< a pointer to the single linked list of DxfChar
                 * objects. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (chars == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        while (chars != NULL)
        {
                DxfChar *iter = (DxfChar *) chars->next;
                dxf_char_free (chars);
                chars = (DxfChar *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Allocate memory for a \c DxfDouble.
 *
 * Fill the memory contents with zeros.
 */
DxfDouble *
dxf_double_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfDouble *d = NULL;
        size_t size;

        size = sizeof (DxfDouble);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((d = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                d = NULL;
        }
        else
        {
                memset (d, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (d);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c DxfDouble
 * object.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfDouble *
dxf_double_init
(
        DxfDouble *d
                /*!< a pointer to the DxfDouble object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (d == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                d = dxf_double_new ();
        }
        if (d == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory.\n")),
                __FUNCTION__);
              return (NULL);
        }
        d->value = 0.0;
        d->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (d);
}


/*!
 * \brief Get the \c value of a \c DxfDouble object.
 *
 * \return the \c value.
 */
double
dxf_double_get_value
(
        DxfDouble *d
                /*!< a pointer to a \c DxfDouble object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (d == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((double) d->value);
}


/*!
 * \brief Set the \c value of a \c DxfDouble object.
 *
 * \return a pointer to \c d when successful, or \c NULL when an error
 * occurred.
 */
DxfDouble *
dxf_double_set_value
(
        DxfDouble *d,
                /*!< a pointer to a \c DxfDouble object. */
        double value
                /*!< a double \c value. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (d == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        d->value = (double) value;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (d);
}


/*!
 * \brief Get the \c next DxfDouble object of a \c DxfDouble object
 * (single linked list).
 *
 * \return the \c next DxfDouble object in a single linked list.
 */
DxfDouble *
dxf_double_get_next
(
        DxfDouble *d
                /*!< a pointer to a \c DxfDouble object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (d == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (d->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfDouble *) d->next);
}


/*!
 * \brief Set the \c next DxfDouble object of a \c DxfDouble object
 * (single linked list).
 *
 * \return a pointer to \c d when successful, or \c NULL when an error
 * occurred.
 */
DxfDouble *
dxf_double_set_next
(
        DxfDouble *d,
                /*!< a pointer to a \c DxfDouble object. */
        DxfDouble *next
                /*!< a pointer to a \c DxfDouble object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (d == NULL)
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
        d->next = (struct DxfDouble *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (d);
}


/*!
 * \brief Get the pointer to the last \c DxfDouble object from a linked
 * list of DXF \c DxfDouble objects.
 *
 * \return pointer to the last \c DxfDouble object.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfDouble *
dxf_double_get_last
(
        DxfDouble *d
                /*!< a pointer to a DXF \c DxfDouble object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (d == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (d->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfDouble *) d);
        }
        DxfDouble *iter = (DxfDouble *) d->next;
        while (iter->next != NULL)
        {
                iter = (DxfDouble *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfDouble *) iter);
}


/*!
 * \brief Free the allocated memory for a DxfDouble object and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_double_free
(
        DxfDouble *d
                /*!< a pointer to the memory occupied by the DxfDouble
                 * object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (d == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (d->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (d);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of
 * DxfDouble objects and all their data fields.
 */
int
dxf_double_free_list
(
        DxfDouble *doubles
                /*!< a pointer to the single linked list of DxfDouble
                 * objects. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (doubles == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        while (doubles != NULL)
        {
                DxfDouble *iter = (DxfDouble *) doubles->next;
                dxf_double_free (doubles);
                doubles = (DxfDouble *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Allocate memory for a \c DxfInt.
 *
 * Fill the memory contents with zeros.
 */
DxfInt *
dxf_int_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfInt *i = NULL;
        size_t size;

        size = sizeof (DxfInt);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((i = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                i = NULL;
        }
        else
        {
                memset (i, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (i);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c DxfInt
 * object.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfInt *
dxf_int_init
(
        DxfInt *i
                /*!< a pointer to the DxfInt object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (i == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                i = dxf_int_new ();
        }
        if (i == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory.\n")),
                __FUNCTION__);
              return (NULL);
        }
        i->value = 0;
        i->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (i);
}


/*!
 * \brief Get the \c value of a \c DxfInt object.
 *
 * \return the \c value.
 */
int
dxf_int_get_value
(
        DxfInt *i
                /*!< a pointer to a \c DxfInt object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (i == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((int) i->value);
}


/*!
 * \brief Set the \c value of a \c DxfInt object.
 *
 * \return a pointer to \c i when successful, or \c NULL when an error
 * occurred.
 */
DxfInt *
dxf_int_set_value
(
        DxfInt *i,
                /*!< a pointer to a \c DxfInt object. */
        int value
                /*!< an int \c value. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (i == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        i->value = (int) value;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (i);
}


/*!
 * \brief Get the \c next DxfInt object of a \c DxfInt object
 * (single linked list).
 *
 * \return the \c next DxfInt object in a single linked list.
 */
DxfInt *
dxf_int_get_next
(
        DxfInt *i
                /*!< a pointer to a \c DxfInt object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (i == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (i->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfInt *) i->next);
}


/*!
 * \brief Set the \c next DxfInt object of a \c DxfInt object
 * (single linked list).
 *
 * \return a pointer to \c i when successful, or \c NULL when an error
 * occurred.
 */
DxfInt *
dxf_int_set_next
(
        DxfInt *i,
                /*!< a pointer to a \c DxfInt object. */
        DxfInt *next
                /*!< a pointer to a \c DxfInt object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (i == NULL)
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
        i->next = (struct DxfInt *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (i);
}


/*!
 * \brief Get the pointer to the last \c DxfInt object from a linked
 * list of DXF \c DxfInt objects.
 *
 * \return pointer to the last \c DxfInt object.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfInt *
dxf_int_get_last
(
        DxfInt *i
                /*!< a pointer to a DXF \c DxfInt object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (i == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (i->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfInt *) i);
        }
        DxfInt *iter = (DxfInt *) i->next;
        while (iter->next != NULL)
        {
                iter = (DxfInt *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfInt *) iter);
}


/*!
 * \brief Free the allocated memory for a DxfInt object and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_int_free
(
        DxfInt *i
                /*!< a pointer to the memory occupied by the DxfInt
                 * object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (i == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (i->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (i);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DxfInt
 * objects and all their data fields.
 */
int
dxf_int_free_list
(
        DxfInt *ints
                /*!< a pointer to the single linked list of DxfInt
                 * objects. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (ints == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        while (ints != NULL)
        {
                DxfInt *iter = (DxfInt *) ints->next;
                dxf_int_free (ints);
                ints = (DxfInt *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Allocate memory for a \c DxfInt16.
 *
 * Fill the memory contents with zeros.
 */
DxfInt16 *
dxf_int16_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfInt16 *i = NULL;
        size_t size;

        size = sizeof (DxfInt16);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((i = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                i = NULL;
        }
        else
        {
                memset (i, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (i);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c DxfInt16
 * object.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfInt16 *
dxf_int16_init
(
        DxfInt16 *i
                /*!< a pointer to the DxfInt16 object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (i == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                i = dxf_int16_new ();
        }
        if (i == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory.\n")),
                __FUNCTION__);
              return (NULL);
        }
        i->value = 0;
        i->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (i);
}


/*!
 * \brief Get the \c value of a \c DxfInt16 object.
 *
 * \return the \c value.
 */
int16_t
dxf_int16_get_value
(
        DxfInt16 *i
                /*!< a pointer to a \c DxfInt16 object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (i == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((int16_t) i->value);
}


/*!
 * \brief Set the \c value of a \c DxfInt16 object.
 *
 * \return a pointer to \c i when successful, or \c NULL when an error
 * occurred.
 */
DxfInt16 *
dxf_int16_set_value
(
        DxfInt16 *i,
                /*!< a pointer to a \c DxfInt object. */
        int16_t value
                /*!< an int16_t \c value. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (i == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        i->value = (int16_t) value;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (i);
}


/*!
 * \brief Get the \c next DxfInt16 object of a \c DxfInt16 object
 * (single linked list).
 *
 * \return the \c next DxfInt16 object in a single linked list.
 */
DxfInt16 *
dxf_int16_get_next
(
        DxfInt16 *i
                /*!< a pointer to a \c DxfInt16 object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (i == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (i->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfInt16 *) i->next);
}


/*!
 * \brief Set the \c next DxfInt16 object of a \c DxfInt16 object
 * (single linked list).
 *
 * \return a pointer to \c i when successful, or \c NULL when an error
 * occurred.
 */
DxfInt16 *
dxf_int16_set_next
(
        DxfInt16 *i,
                /*!< a pointer to a \c DxfInt16 object. */
        DxfInt16 *next
                /*!< a pointer to a \c DxfInt16 object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (i == NULL)
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
        i->next = (struct DxfInt16 *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (i);
}


/*!
 * \brief Get the pointer to the last \c DxfInt16 object from a linked
 * list of DXF \c DxfInt16 objects.
 *
 * \return pointer to the last \c DxfInt16 object.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfInt16 *
dxf_int16_get_last
(
        DxfInt16 *i
                /*!< a pointer to a DXF \c DxfInt16 object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (i == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (i->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfInt16 *) i);
        }
        DxfInt16 *iter = (DxfInt16 *) i->next;
        while (iter->next != NULL)
        {
                iter = (DxfInt16 *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfInt16 *) iter);
}


/*!
 * \brief Free the allocated memory for a DxfInt16 object and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_int16_free
(
        DxfInt16 *i
                /*!< a pointer to the memory occupied by the DxfInt16
                 * object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (i == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (i->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (i);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DxfInt16
 * objects and all their data fields.
 */
int
dxf_int16_free_list
(
        DxfInt16 *ints
                /*!< a pointer to the single linked list of DxfInt16
                 * objects. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (ints == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        while (ints != NULL)
        {
                DxfInt16 *iter = (DxfInt16 *) ints->next;
                dxf_int16_free (ints);
                ints = (DxfInt16 *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Allocate memory for a \c DxfInt32.
 *
 * Fill the memory contents with zeros.
 */
DxfInt32 *
dxf_int32_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfInt32 *i = NULL;
        size_t size;

        size = sizeof (DxfInt32);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((i = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                i = NULL;
        }
        else
        {
                memset (i, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (i);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c DxfInt32
 * object.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfInt32 *
dxf_int32_init
(
        DxfInt32 *i
                /*!< a pointer to the DxfInt32 object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (i == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                i = dxf_int32_new ();
        }
        if (i == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory.\n")),
                __FUNCTION__);
              return (NULL);
        }
        i->value = 0;
        i->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (i);
}


/*!
 * \brief Get the \c value of a \c DxfInt32 object.
 *
 * \return the \c value.
 */
int32_t
dxf_int32_get_value
(
        DxfInt32 *i
                /*!< a pointer to a \c DxfInt32 object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (i == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((int32_t) i->value);
}


/*!
 * \brief Set the \c value of a \c DxfInt32 object.
 *
 * \return a pointer to \c i when successful, or \c NULL when an error
 * occurred.
 */
DxfInt32 *
dxf_int32_set_value
(
        DxfInt32 *i,
                /*!< a pointer to a \c DxfInt32 object. */
        int32_t value
                /*!< an int32_t \c value. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (i == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        i->value = (int32_t) value;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (i);
}


/*!
 * \brief Get the \c next DxfInt32 object of a \c DxfInt32 object
 * (single linked list).
 *
 * \return the \c next DxfInt32 object in a single linked list.
 */
DxfInt32 *
dxf_int32_get_next
(
        DxfInt32 *i
                /*!< a pointer to a \c DxfInt32 object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (i == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (i->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfInt32 *) i->next);
}


/*!
 * \brief Set the \c next DxfInt32 object of a \c DxfInt32 object
 * (single linked list).
 *
 * \return a pointer to \c i when successful, or \c NULL when an error
 * occurred.
 */
DxfInt32 *
dxf_int32_set_next
(
        DxfInt32 *i,
                /*!< a pointer to a \c DxfInt32 object. */
        DxfInt32 *next
                /*!< a pointer to a \c DxfInt32 object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (i == NULL)
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
        i->next = (struct DxfInt32 *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (i);
}


/*!
 * \brief Get the pointer to the last \c DxfInt32 object from a linked
 * list of DXF \c DxfInt32 objects.
 *
 * \return pointer to the last \c DxfInt32 object.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfInt32 *
dxf_int32_get_last
(
        DxfInt32 *i
                /*!< a pointer to a DXF \c DxfInt32 object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (i == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (i->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfInt32 *) i);
        }
        DxfInt32 *iter = (DxfInt32 *) i->next;
        while (iter->next != NULL)
        {
                iter = (DxfInt32 *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfInt32 *) iter);
}


/*!
 * \brief Free the allocated memory for a DxfInt32 object and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_int32_free
(
        DxfInt32 *i
                /*!< a pointer to the memory occupied by the DxfInt32
                 * object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (i == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (i->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (i);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DxfInt32
 * objects and all their data fields.
 */
int
dxf_int32_free_list
(
        DxfInt32 *ints
                /*!< a pointer to the single linked list of DxfInt32
                 * objects. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (ints == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        while (ints != NULL)
        {
                DxfInt32 *iter = (DxfInt32 *) ints->next;
                dxf_int32_free (ints);
                ints = (DxfInt32 *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Allocate memory for a \c DxfInt64.
 *
 * Fill the memory contents with zeros.
 */
DxfInt64 *
dxf_int64_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfInt64 *i = NULL;
        size_t size;

        size = sizeof (DxfInt64);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((i = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                i = NULL;
        }
        else
        {
                memset (i, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (i);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c DxfInt64
 * object.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfInt64 *
dxf_int64_init
(
        DxfInt64 *i
                /*!< a pointer to the DxfInt64 object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (i == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                i = dxf_int64_new ();
        }
        if (i == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory.\n")),
                __FUNCTION__);
              return (NULL);
        }
        i->value = 0;
        i->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (i);
}


/*!
 * \brief Get the \c value of a \c DxfInt64 object.
 *
 * \return the \c value.
 */
int64_t
dxf_int64_get_value
(
        DxfInt64 *i
                /*!< a pointer to a \c DxfInt64 object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (i == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((int64_t) i->value);
}


/*!
 * \brief Set the \c value of a \c DxfInt64 object.
 *
 * \return a pointer to \c i when successful, or \c NULL when an error
 * occurred.
 */
DxfInt64 *
dxf_int64_set_value
(
        DxfInt64 *i,
                /*!< a pointer to a \c DxfInt64 object. */
        int64_t value
                /*!< an int64_t \c value. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (i == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        i->value = (int64_t) value;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (i);
}


/*!
 * \brief Get the \c next DxfInt64 object of a \c DxfInt64 object
 * (single linked list).
 *
 * \return the \c next DxfInt64 object in a single linked list.
 */
DxfInt64 *
dxf_int64_get_next
(
        DxfInt64 *i
                /*!< a pointer to a \c DxfInt64 object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (i == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (i->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfInt64 *) i->next);
}


/*!
 * \brief Set the \c next DxfInt64 object of a \c DxfInt64 object
 * (single linked list).
 *
 * \return a pointer to \c i when successful, or \c NULL when an error
 * occurred.
 */
DxfInt64 *
dxf_int64_set_next
(
        DxfInt64 *i,
                /*!< a pointer to a \c DxfInt64 object. */
        DxfInt64 *next
                /*!< a pointer to a \c DxfInt64 object. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (i == NULL)
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
        i->next = (struct DxfInt64 *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (i);
}


/*!
 * \brief Get the pointer to the last \c DxfInt64 object from a linked
 * list of DXF \c DxfInt64 objects.
 *
 * \return pointer to the last \c DxfInt64 object.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfInt64 *
dxf_int64_get_last
(
        DxfInt64 *i
                /*!< a pointer to a DXF \c DxfInt64 object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (i == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (i->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfInt64 *) i);
        }
        DxfInt64 *iter = (DxfInt64 *) i->next;
        while (iter->next != NULL)
        {
                iter = (DxfInt64 *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfInt64 *) iter);
}


/*!
 * \brief Free the allocated memory for a DxfInt64 object and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_int64_free
(
        DxfInt64 *i
                /*!< a pointer to the memory occupied by the DxfInt64
                 * object. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (i == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (i->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (i);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DxfInt64
 * objects and all their data fields.
 */
int
dxf_int64_free_list
(
        DxfInt64 *ints
                /*!< a pointer to the single linked list of DxfInt64
                 * objects. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (ints == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        while (ints != NULL)
        {
                DxfInt64 *iter = (DxfInt64 *) ints->next;
                dxf_int64_free (ints);
                ints = (DxfInt64 *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Test for double type group codes.
 */
int
dxf_read_is_double
(
        int type
                /*!< Group code. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        if ((type >= 10 && type < 60)
          || (type >= 110 && type < 150)
          || (type >= 210 && type < 240)
          || (type >= 460 && type < 470)
          || (type >= 1010 && type < 1060))
        {
#if DEBUG
        DXF_DEBUG_END
#endif
                return TRUE;
        }
        else
        {
#if DEBUG
        DXF_DEBUG_END
#endif
                return FALSE;
        }
}


/*!
 * \brief Test for int type group codes (Boolean).
 */
int
dxf_read_is_int
(
        int type
                /*!< Group code. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (type >= 290 && type < 300)
        {
#if DEBUG
        DXF_DEBUG_END
#endif
                return TRUE;
        }
        else
        {
#if DEBUG
        DXF_DEBUG_END
#endif
                return FALSE;
        }
}


/*!
 * \brief Test for int16_t type group codes.
 */
int
dxf_read_is_int16_t
(
        int type
                /*!< Group code. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        if ((type >= 60 && type < 80)
          || (type >= 170 && type < 180)
          || (type >= 270 && type < 290)
          || (type >= 370 && type < 390)
          || (type >= 400 && type < 410)
          || (type >= 1060 && type < 1071))
        {
#if DEBUG
        DXF_DEBUG_END
#endif
                return TRUE;
        }
        else
        {
#if DEBUG
        DXF_DEBUG_END
#endif
                return FALSE;
        }
}


/*!
 * \brief Test for int32_t type group codes.
 */
int
dxf_read_is_int32_t
(
        int type
                /*!< Group code. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        if ((type >= 90 && type < 100)
          || (type >= 420 && type < 430)
          || (type == 1071))
        {
#if DEBUG
        DXF_DEBUG_END
#endif
                return TRUE;
        }
        else
        {
#if DEBUG
        DXF_DEBUG_END
#endif
                return FALSE;
        }
}


/*!
 * \brief Test for int64_t type group codes.
 */
int
dxf_read_is_int64_t
(
        int type
                /*!< Group code. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (type >= 160 && type < 170)
        {
#if DEBUG
        DXF_DEBUG_END
#endif
                return TRUE;
        }
        else
        {
#if DEBUG
        DXF_DEBUG_END
#endif
                return FALSE;
        }
}


/*!
 * \brief Test for string type group codes.
 */
int
dxf_read_is_string
(
        int type
                /*!< Group code. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        if ((type >= 0 && type < 10)
          || (type == 100)
          || (type == 102)
          || (type == 105)
          || (type >= 300 && type < 370)
          || (type >= 390 && type < 400)
          || (type >= 410 && type < 420)
          || (type >= 430 && type < 440)
          || (type >= 470 && type < 482)
          || (type >= 999 && type < 1010))
        {
#if DEBUG
        DXF_DEBUG_END
#endif
                return TRUE;
        }
        else
        {
#if DEBUG
        DXF_DEBUG_END
#endif
                return FALSE;
        }
}

/*!
 * \brief Opens a DxfFile, does error checking and resets the line number
 * counter.
 * 
 * Reset the line counting to 0.
 *
 * \todo add a test for invalid characters in \c filename.
 * You may use any character in the current code page (Unicode/ANSI
 * above 127), except:
 * <ul>
 * <li> < > : " / \ | ? * </li>
 * <li> Characters whose integer representations are 0-31 (less than
 *      ASCII space)</li>
 * <li> Any other character that the target file system does not allow
 *      (say, trailing periods or spaces)</li>
 * <li> Any of the DOS names: CON, PRN, AUX, NUL, COM0, COM1, COM2,
 *      COM3, COM4, COM5, COM6, COM7, COM8, COM9, LPT0, LPT1, LPT2,
 *      LPT3, LPT4, LPT5, LPT6, LPT7, LPT8, LPT9 (and avoid AUX.txt,
 *      etc)</li>
 * <li> The file name is all periods</li>
 * <li> File paths (including the file name) may not have more than 260
 *      characters (that don't use the \?\ prefix)</li>
 * <li> Unicode file paths (including the file name) with more than
 *      32,000 characters when using \?\ (note that prefix may expand
 *      directory components and cause it to overflow the 32,000 limit)</li>
 * </ul>
 */
DxfFile *
dxf_read_init
(
        const char *filename
                /*!< Filename. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfFile * file = NULL;
        FILE *fp;
        if (!filename)
        {
                fprintf (stderr,
                  (_("Error: filename is not initialised (NULL pointer).\n")));
                return (NULL);
        }
        if (strcmp (filename, "") == 0)
        {
                fprintf (stderr,
                  (_("Error: filename contains an empty string.\n")));
                return (NULL);
        }
        fp = fopen (filename, "r");
        if (!fp)
        {
                fprintf (stderr,
                  (_("Error: could not open file: %s for reading (NULL pointer).\n")),
                  filename);
                return (NULL);
        }
        file = malloc (sizeof(DxfFile));
        file->fp = fp;
        file->filename = strdup(filename);
        file->line_number = 0;
        /*! \todo do dxf header and blocks need initialized ?
         * dxf_header_init (file->dxf_header);
         * dxf_block_init (file->dxf_block);
         */
#if DEBUG
        DXF_DEBUG_END
#endif
        return file;
}


void
dxf_read_close
(
        DxfFile *file
                /*!< DXF file pointer to an output file (or device). */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (file == NULL)
        {
                fprintf (stderr,
                  (_("Error: file is not initialised (NULL pointer).\n")));
        }
        else
        {
                fclose (file->fp);
                free (file->filename);
                /*! \todo free other sub structures */
                free (file);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Reads a line from a file.
 * 
 * Reads the next line from \c fp file and stores it into the temp_string.
 * 
 */
int
dxf_read_line (char * temp_string, DxfFile *fp)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int ret;

        ret = fscanf (fp->fp, "%[^\n]\n", temp_string);
        if (ferror (fp->fp))
        {
                fprintf (stderr,
                  (_("Error: while reading from: %s in line: %d.\n")),
                  fp->filename, fp->line_number);
                return (EXIT_FAILURE);
        }
        if (ret)
        {
                fp->line_number++;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ret;
}

/*!
 * \brief Uses of fscanf with other features.
 * 
 * Uses fscanf for file parsing, but also tracks the lines it reads;
 * 
 */
int
dxf_read_scanf (DxfFile *fp, const char *template, ...)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int ret;
        va_list lst;
        va_start (lst, template);
        ret = vfscanf (fp->fp, template, lst);
        if (ferror (fp->fp))
        {
                fprintf (stderr,
                  (_("Error: while reading from: %s in line: %d.\n")),
                  fp->filename, fp->line_number);
                return (EXIT_FAILURE);
        }
        va_end (lst);
        if (ret)
        {
                /*
                 * we have to find each \n from the template to know how many lines will we read;
                 */
                char * search_result;
                search_result = (char *) template;
                while (TRUE)
                {
                        search_result = strstr (search_result, "\n");
                        if (search_result == NULL)
                                break;
                        fp->line_number++;
                        *++search_result;
                }
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ret;
}


/* EOF */
