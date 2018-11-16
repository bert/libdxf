/*!
 * \file mesh.c
 *
 * \author Copyright (C) 2018 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF mesh entity (\c MESH).
 *
 * \since The \c MESH entity was introduced in DXF R2011.
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


#include "mesh.h"


/*!
 * \brief Allocate memory for a DXF \c MESH entity.
 *
 * Fill the memory contents with zeros.
 *
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfMesh *
dxf_mesh_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfMesh *mesh = NULL;
        size_t size;

        size = sizeof (DxfMesh);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((mesh = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                mesh = NULL;
        }
        else
        {
                memset (mesh, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c MESH
 * entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when successful.
 */
DxfMesh *
dxf_mesh_init
(
        DxfMesh *mesh
                /*!< a pointer to the DXF \c MESH entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                mesh = dxf_mesh_new ();
        }
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mesh->id_code = 0;
        mesh->linetype = strdup (DXF_DEFAULT_LINETYPE);
        mesh->layer = strdup (DXF_DEFAULT_LAYER);
        mesh->elevation = 0.0;
        mesh->thickness = 0.0;
        mesh->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        mesh->visibility = DXF_DEFAULT_VISIBILITY;
        mesh->color = DXF_COLOR_BYLAYER;
        mesh->paperspace = DXF_MODELSPACE;
        mesh->graphics_data_size = 0;
        mesh->shadow_mode = 0;
        mesh->binary_graphics_data = (DxfBinaryGraphicsData *) dxf_binary_graphics_data_new ();
        mesh->dictionary_owner_soft = strdup ("");
        mesh->object_owner_soft = strdup ("");
        mesh->material = strdup ("");
        mesh->dictionary_owner_hard = strdup ("");
        mesh->lineweight = 0;
        mesh->plot_style_name = strdup ("");
        mesh->color_value = 0;
        mesh->color_name = strdup ("");
        mesh->transparency = 0;
        mesh->p0 = dxf_point_new ();
        mesh->p0 = dxf_point_init (mesh->p0);
        mesh->p0->x0 = 0.0;
        mesh->p0->y0 = 0.0;
        mesh->p0->z0 = 0.0;
        mesh->version = 0;
        mesh->blend_crease_property = 0;
        mesh->face_list_item = 0;
        mesh->edge_vertex_index = 0;
        mesh->number_of_property_overridden_sub_entities = 0;
        mesh->property_type = 0;
        mesh->subdivision_level = 0;
        mesh->sub_entity_marker = 0;
        mesh->vertex_count_level_0 = 0;
        mesh->count_of_property_overridden = 0;
        mesh->face_list_size_level_0 = 0;
        mesh->edge_count_level_0 = 0;
        mesh->edge_crease_count_level_0 = 0;
        mesh->edge_create_value = 0.0;
        mesh->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Free the allocated memory for a DXF \c MESH entity and all
 * it's data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_mesh_free
(
        DxfMesh *mesh
                /*!< a pointer to the memory occupied by the DXF \c MESH
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mesh->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (mesh->linetype);
        free (mesh->layer);
        free (mesh->dictionary_owner_soft);
        free (mesh->object_owner_soft);
        free (mesh->material);
        free (mesh->dictionary_owner_hard);
        free (mesh->plot_style_name);
        free (mesh->color_name);
        dxf_point_free (mesh->p0);
        free (mesh);
        mesh = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a single linked list of DXF
 * \c MESH entities and all their data fields.
 */
void
dxf_mesh_free_list
(
        DxfMesh *meshes
                /*!< a pointer to the single linked list of DXF
                 * \c MESH entities. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (meshes == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (meshes != NULL)
        {
                DxfMesh *iter = (DxfMesh *) meshes->next;
                dxf_mesh_free (meshes);
                meshes = (DxfMesh *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the \c id_code from a DXF \c MESH entity.
 *
 * \return \c id_code.
 */
int
dxf_mesh_get_id_code
(
        DxfMesh *mesh
                /*!< a pointer to a DXF \c MESH entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mesh->id_code < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh->id_code);
}


/*!
 * \brief Set the \c id_code for a DXF \c MESH entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an error
 * occurred.
 */
DxfMesh *
dxf_mesh_set_id_code
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        int id_code
                /*!< the \c id_code to be set for the entity.\n
                 * This is to be an unique (sequential) number in the
                 * DXF file. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
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
        mesh->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the \c linetype from a DXF \c MESH entity.
 *
 * \return \c linetype when successful, \c NULL when an error occurred.
 */
char *
dxf_mesh_get_linetype
(
        DxfMesh *mesh
                /*!< a pointer to a DXF \c MESH entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mesh->linetype ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mesh->linetype));
}


/*!
 * \brief Set the \c linetype for a DXF \c MESH entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an error
 * occurred.
 */
DxfMesh *
dxf_mesh_set_linetype
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        char *linetype
                /*!< a pointer to a string containing the \c linetype
                 * to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
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
        mesh->linetype = strdup (linetype);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the \c layer from a DXF \c MESH entity.
 *
 * \return \c layer when successful, \c NULL when an error occurred.
 */
char *
dxf_mesh_get_layer
(
        DxfMesh *mesh
                /*!< a pointer to a DXF \c MESH entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (mesh->layer ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mesh->layer));
}


/*!
 * \brief Set the \c layer for a DXF \c MESH entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an error
 * occurred.
 */
DxfMesh *
dxf_mesh_set_layer
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        char *layer
                /*!< a pointer to a string containing the \c layer to be
                 * set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
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
        mesh->layer = strdup (layer);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the \c elevation from a DXF \c MESH entity.
 *
 * \return \c elevation.
 */
double
dxf_mesh_get_elevation
(
        DxfMesh *mesh
                /*!< a pointer to a DXF \c MESH entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh->elevation);
}


/*!
 * \brief Set the \c elevation for a DXF \c MESH entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an error
 * occurred.
 */
DxfMesh *
dxf_mesh_set_elevation
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        double elevation
                /*!< the \c elevation to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mesh->elevation = elevation;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the \c thickness from a DXF \c MESH entity.
 *
 * \return \c thickness.
 */
double
dxf_mesh_get_thickness
(
        DxfMesh *mesh
                /*!< a pointer to a DXF \c MESH entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mesh->thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh->thickness);
}


/*!
 * \brief Set the \c thickness for a DXF \c MESH entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an error
 * occurred.
 */
DxfMesh *
dxf_mesh_set_thickness
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        double thickness
                /*!< the \c thickness to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        mesh->thickness = thickness;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the \c linetype_scale from a DXF \c MESH entity.
 *
 * \return \c linetype_scale.
 */
double
dxf_mesh_get_linetype_scale
(
        DxfMesh *mesh
                /*!< a pointer to a DXF \c MESH entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mesh->linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh->linetype_scale);
}


/*!
 * \brief Set the \c linetype_scale for a DXF \c MESH entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an
 * error occurred.
 */
DxfMesh *
dxf_mesh_set_linetype_scale
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        double linetype_scale
                /*!< the \c linetype_scale to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        mesh->linetype_scale = linetype_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the \c visibility from a DXF \c MESH entity.
 *
 * \return \c visibility.
 */
int16_t
dxf_mesh_get_visibility
(
        DxfMesh *mesh
                /*!< a pointer to a DXF \c MESH entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (mesh == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (mesh->visibility < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (mesh->visibility > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh->visibility);
}


/* EOF*/
