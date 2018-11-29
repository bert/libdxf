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


/*!
 * \brief Set the \c visibility for a DXF \c MESH entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an
 * error occurred.
 */
DxfMesh *
dxf_mesh_set_visibility
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        int16_t visibility
                /*!< the \c visibility to be set for the entity. */
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
        if (visibility < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (visibility > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        mesh->visibility = visibility;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the \c color from a DXF \c MESH entity.
 *
 * \return color.
 */
int
dxf_mesh_get_color
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
        if (mesh->color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh->color);
}


/*!
 * \brief Set the \c color for a DXF \c MESH entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an error
 * occurred.
 */
DxfMesh *
dxf_mesh_set_color
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        int color
                /*!< the \c color to be set for the entity. */
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
        if (color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        mesh->color = color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the \c paperspace flag value from a DXF \c MESH entity.
 *
 * \return \c paperspace flag value.
 */
int
dxf_mesh_get_paperspace
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
        if (mesh->paperspace < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (mesh->paperspace > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh->paperspace);
}


/*!
 * \brief Set the \c paperspace flag for a DXF \c MESH entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an error
 * occurred.
 */
DxfMesh *
dxf_mesh_set_paperspace
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        int paperspace
                /*!< the \c paperspace flag value to be set for the
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
                return (NULL);
        }
        if (paperspace < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (paperspace > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        mesh->paperspace = paperspace;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the \c graphics_data_size value from a DXF \c MESH entity.
 *
 * \return \c graphics_data_size value when successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
int
dxf_mesh_get_graphics_data_size
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
        if (mesh->graphics_data_size < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (mesh->graphics_data_size == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh->graphics_data_size);
}


/*!
 * \brief Set the \c graphics_data_size value for a DXF \c MESH entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an
 * error occurred.
 */
DxfMesh *
dxf_mesh_set_graphics_data_size
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        int graphics_data_size
                /*!< the \c graphics_data_size value to be set for the
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
                return (NULL);
        }
        if (graphics_data_size < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (graphics_data_size == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero value was passed.\n")),
                  __FUNCTION__);
        }
        mesh->graphics_data_size = graphics_data_size;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the \c shadow_mode from a DXF \c MESH entity.
 *
 * \return \c shadow_mode when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_mesh_get_shadow_mode
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
        if (mesh->shadow_mode < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (mesh->shadow_mode > 3)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh->shadow_mode);
}


/*!
 * \brief Set the \c shadow_mode for a DXF \c MESH entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an error
 * occurred.
 */
DxfMesh *
dxf_mesh_set_shadow_mode
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        int16_t shadow_mode
                /*!< the \c shadow_mode to be set for the entity. */
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
        if (shadow_mode < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        if (shadow_mode > 3)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
        }
        mesh->shadow_mode = shadow_mode;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the pointer to the \c binary_graphics_data from a DXF
 * \c MESH entity.
 *
 * \return pointer to the \c binary_graphics_data.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfBinaryGraphicsData *
dxf_mesh_get_binary_graphics_data
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
        if (mesh->binary_graphics_data ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfBinaryGraphicsData *) mesh->binary_graphics_data);
}


/*!
 * \brief Set the pointer to the \c binary_graphics_data for a DXF
 * \c MESH entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an error
 * occurred.
 */
DxfMesh *
dxf_mesh_set_binary_graphics_data
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        DxfBinaryGraphicsData *data
                /*!< a string containing the pointer to the
                 * \c binary_graphics_data for the entity. */
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
        if (data == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mesh->binary_graphics_data = (DxfBinaryGraphicsData *) data;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_soft from a DXF 
 * \c MESH entity.
 *
 * \return pointer to the \c dictionary_owner_soft.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_mesh_get_dictionary_owner_soft
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
        if (mesh->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mesh->dictionary_owner_soft));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_soft for a DXF
 * \c MESH entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an error
 * occurred.
 */
DxfMesh *
dxf_mesh_set_dictionary_owner_soft
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the \c
                 * dictionary_owner_soft for the entity. */
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
        if (dictionary_owner_soft == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mesh->dictionary_owner_soft = strdup (dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the soft pointer to the object owner from a DXF 
 * \c MESH entity.
 *
 * \return soft pointer to the object owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_mesh_get_object_owner_soft
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
        if (mesh->object_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mesh->object_owner_soft));
}


/*!
 * \brief Set the pointer to the \c object_owner_soft for a DXF
 * \c MESH entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an error
 * occurred.
 */
DxfMesh *
dxf_mesh_set_object_owner_soft
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        char *object_owner_soft
                /*!< a string containing the pointer to the
                 * \c object_owner_soft for the entity. */
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
        if (object_owner_soft == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mesh->object_owner_soft = strdup (object_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the pointer to the \c material from a DXF \c MESH entity.
 *
 * \return a pointer to \c material when successful, or \c NULL when an
 * error occurred.
 *
 * \warning No checks are performed on the returned pointer.
 */
char *
dxf_mesh_get_material
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
        if (mesh->material ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mesh->material));
}


/*!
 * \brief Set the pointer to the \c material for a DXF \c MESH entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an error
 * occurred.
 */
DxfMesh *
dxf_mesh_set_material
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        char *material
                /*!< a string containing the pointer to the \c
                 * material for the entity. */
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
        if (material == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mesh->material = strdup (material);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the pointer to the \c dictionary_owner_hard from a DXF 
 * \c MESH entity.
 *
 * \return pointer to the \c dictionary_owner_hard.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_mesh_get_dictionary_owner_hard
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
        if (mesh->dictionary_owner_hard ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mesh->dictionary_owner_hard));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_hard for a DXF
 * \c MESH entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an error
 * occurred.
 */
DxfMesh *
dxf_mesh_set_dictionary_owner_hard
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        char *dictionary_owner_hard
                /*!< a string containing the pointer to the \c
                 * dictionary_owner_hard for the entity. */
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
        if (dictionary_owner_hard == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mesh->dictionary_owner_hard = strdup (dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the \c lineweight from a DXF \c MESH entity.
 *
 * \return \c lineweight when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_mesh_get_lineweight
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
        return (mesh->lineweight);
}


/*!
 * \brief Set the \c lineweight for a DXF \c MESH entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an error
 * occurred.
 */
DxfMesh *
dxf_mesh_set_lineweight
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        int16_t lineweight
                /*!< the \c lineweight to be set for the entity. */
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
        mesh->lineweight = lineweight;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the \c plot_style_name from a DXF \c MESH entity.
 *
 * \return a pointer to \c plot_style_name when successful, or \c NULL
 * when an error occurred.
 */
char *
dxf_mesh_get_plot_style_name
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
        if (mesh->plot_style_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mesh->plot_style_name));
}


/*!
 * \brief Set the \c plot_style_name for a DXF \c MESH entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an error
 * occurred.
 */
DxfMesh *
dxf_mesh_set_plot_style_name
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        char *plot_style_name
                /*!< a string containing the \c plot_style_name for the
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
                return (NULL);
        }
        if (plot_style_name == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mesh->plot_style_name = strdup (plot_style_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the \c color_value from a DXF \c MESH entity.
 *
 * \return \c color_value when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
long
dxf_mesh_get_color_value
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
        return (mesh->color_value);
}


/*!
 * \brief Set the \c color_value for a DXF \c MESH entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an error
 * occurred.
 */
DxfMesh *
dxf_mesh_set_color_value
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        long color_value
                /*!< the \c color_value to be set for the entity. */
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
        mesh->color_value = color_value;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the \c color_name from a DXF \c MESH entity.
 *
 * \return \c color_name when successful, or \c NULL when an error
 * occurred.
 */
char *
dxf_mesh_get_color_name
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
        if (mesh->color_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (mesh->color_name));
}


/*!
 * \brief Set the \c color_name for a DXF \c MESH entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an error
 * occurred.
 */
DxfMesh *
dxf_mesh_set_color_name
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        char *color_name
                /*!< a string containing the \c color_name for the
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
                return (NULL);
        }
        if (color_name == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mesh->color_name = strdup (color_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the \c transparency from a DXF \c MESH entity.
 *
 * \return \c transparency when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
long
dxf_mesh_get_transparency
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
        return (mesh->transparency);
}


/*!
 * \brief Set the \c transparency for a DXF \c MESH entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an error
 * occurred.
 */
DxfMesh *
dxf_mesh_set_transparency
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        long transparency
                /*!< the \c transparency to be set for the entity. */
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
        mesh->transparency = transparency;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the vertex position \c p0 of a DXF \c MESH entity.
 *
 * \return the vertex position \c p0.
 */
DxfPoint *
dxf_mesh_get_p0
(
        DxfMesh *mesh
                /*!< a pointer to a DXF \c MESH entity. */
)
{
#ifdef DEBUG
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
        if (mesh->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh->p0);
}


/*!
 * \brief Set the vertex position \c p0 of a DXF \c MESH entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an error
 * occurred.
 */
DxfMesh *
dxf_mesh_set_p0
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        DxfPoint *p0
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
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
        if (p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mesh->p0 = p0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the X-value of the vertex position \c x0 of a DXF \c MESH
 * entity.
 *
 * \return the X-value of the vertex position \c x0.
 */
double
dxf_mesh_get_x0
(
        DxfMesh *mesh
                /*!< a pointer to a DXF \c MESH entity. */
)
{
#ifdef DEBUG
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
        if (mesh->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh->p0->x0);
}


/*!
 * \brief Set the X-value of the vertex position \c x0 of a DXF \c MESH
 * entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an error
 * occurred.
 */
DxfMesh *
dxf_mesh_set_x0
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        double x0
                /*!< the X-value of the vertex position \c x0 of a DXF
                 * \c MESH entity. */
)
{
#ifdef DEBUG
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
        if (mesh->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mesh->p0->x0 = x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the Y-value of the vertex position \c y0 of a DXF \c MESH
 * entity.
 *
 * \return the Y-value of the vertex position \c y0.
 */
double
dxf_mesh_get_y0
(
        DxfMesh *mesh
                /*!< a pointer to a DXF \c MESH entity. */
)
{
#ifdef DEBUG
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
        if (mesh->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh->p0->y0);
}


/*!
 * \brief Set the Y-value of the vertex position \c y0 of a DXF \c MESH
 * entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an error
 * occurred.
 */
DxfMesh *
dxf_mesh_set_y0
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        double y0
                /*!< the Y-value of the vertex position \c y0 of a DXF
                 * \c MESH entity. */
)
{
#ifdef DEBUG
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
        if (mesh->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mesh->p0->y0 = y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the Z-value of the vertex position \c z0 of a DXF \c MESH
 * entity.
 *
 * \return the Z-value of the vertex position \c z0.
 */
double
dxf_mesh_get_z0
(
        DxfMesh *mesh
                /*!< a pointer to a DXF \c MESH entity. */
)
{
#ifdef DEBUG
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
        if (mesh->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh->p0->z0);
}


/*!
 * \brief Set the Z-value of the vertex position \c z0 of a DXF \c MESH
 * entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an error
 * occurred.
 */
DxfMesh *
dxf_mesh_set_z0
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        double z0
                /*!< the Z-value of the vertex position \c z0 of a DXF
                 * \c MESH entity. */
)
{
#ifdef DEBUG
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
        if (mesh->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        mesh->p0->z0 = z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the \c version from a DXF \c MESH entity.
 *
 * \return \c version.
 */
int16_t
dxf_mesh_get_version
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
        if (mesh->version < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh->version);
}


/*!
 * \brief Set the \c version for a DXF \c MESH entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an error
 * occurred.
 */
DxfMesh *
dxf_mesh_set_version
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        int16_t version
                /*!< the \c version to be set for the entity. */
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
        if (version < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        mesh->version = version;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the \c blend_crease_property from a DXF \c MESH entity.
 *
 * \return \c blend_crease_property.
 */
int16_t
dxf_mesh_get_blend_crease_property
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
        if (mesh->blend_crease_property < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (mesh->blend_crease_property > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh->blend_crease_property);
}


/*!
 * \brief Set the \c blend_crease_property for a DXF \c MESH entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an error
 * occurred.
 */
DxfMesh *
dxf_mesh_set_blend_crease_property
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        int16_t blend_crease_property
                /*!< the \c blend_crease_property to be set for the
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
                return (NULL);
        }
        if (blend_crease_property < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (blend_crease_property > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
        mesh->blend_crease_property = blend_crease_property;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the \c face_list_item from a DXF \c MESH entity.
 *
 * \return \c face_list_item.
 */
int32_t
dxf_mesh_get_face_list_item
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
        return (mesh->face_list_item);
}


/*!
 * \brief Set the \c face_list_item for a DXF \c MESH entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an
 * error occurred.
 */
DxfMesh *
dxf_mesh_set_face_list_item
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        int32_t face_list_item
                /*!< the \c face_list_item to be set for the
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
                return (NULL);
        }
        mesh->face_list_item = face_list_item;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the \c edge_vertex_index from a DXF \c MESH entity.
 *
 * \return \c edge_vertex_index.
 */
int32_t
dxf_mesh_get_edge_vertex_index
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
        return (mesh->edge_vertex_index);
}


/*!
 * \brief Set the \c edge_vertex_index for a DXF \c MESH entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an
 * error occurred.
 */
DxfMesh *
dxf_mesh_set_edge_vertex_index
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        int32_t edge_vertex_index
                /*!< the \c edge_vertex_index to be set for the
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
                return (NULL);
        }
        mesh->edge_vertex_index = edge_vertex_index;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the \c number_of_property_overridden_sub_entities from a
 * DXF \c MESH entity.
 *
 * \return \c number_of_property_overridden_sub_entities.
 */
int32_t
dxf_mesh_get_number_of_property_overridden_sub_entities
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
        return (mesh->number_of_property_overridden_sub_entities);
}


/*!
 * \brief Set the \c number_of_property_overridden_sub_entities for a
 * DXF \c MESH entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an
 * error occurred.
 */
DxfMesh *
dxf_mesh_set_number_of_property_overridden_sub_entities
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        int32_t number_of_property_overridden_sub_entities
                /*!< the \c number_of_property_overridden_sub_entities
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
        mesh->number_of_property_overridden_sub_entities = number_of_property_overridden_sub_entities;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the \c property_type from a DXF \c MESH entity.
 *
 * \return \c property_type.
 */
int32_t
dxf_mesh_get_property_type
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
        if (mesh->property_type < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (mesh->property_type > 3)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh->property_type);
}


/*!
 * \brief Set the \c property_type for a DXF \c MESH entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an error
 * occurred.
 */
DxfMesh *
dxf_mesh_set_property_type
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        int32_t property_type
                /*!< the \c property_type to be set for the entity. */
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
        if (property_type < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (property_type > 3)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
        mesh->property_type = property_type;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the \c subdivision_level from a DXF \c MESH entity.
 *
 * \return \c subdivision_level.
 */
int32_t
dxf_mesh_get_subdivision_level
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
        return (mesh->subdivision_level);
}


/*!
 * \brief Set the \c subdivision_level for a DXF \c MESH entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an error
 * occurred.
 */
DxfMesh *
dxf_mesh_set_subdivision_level
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        int32_t subdivision_level
                /*!< the \c subdivision_level to be set for the entity. */
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
        mesh->subdivision_level = subdivision_level;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the \c sub_entity_marker from a DXF \c MESH entity.
 *
 * \return \c sub_entity_marker.
 */
int32_t
dxf_mesh_get_sub_entity_marker
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
        return (mesh->sub_entity_marker);
}


/*!
 * \brief Set the \c sub_entity_marker for a DXF \c MESH entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an error
 * occurred.
 */
DxfMesh *
dxf_mesh_set_sub_entity_marker
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        int32_t sub_entity_marker
                /*!< the \c sub_entity_marker to be set for the entity. */
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
        mesh->sub_entity_marker = sub_entity_marker;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the \c vertex_count_level_0 from a DXF \c MESH entity.
 *
 * \return \c vertex_count_level_0.
 */
int32_t
dxf_mesh_get_vertex_count_level_0
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
        return (mesh->vertex_count_level_0);
}


/*!
 * \brief Set the \c vertex_count_level_0 for a DXF \c MESH entity.
 *
 * \return a pointer to \c mesh when successful, or \c NULL when an error
 * occurred.
 */
DxfMesh *
dxf_mesh_set_vertex_count_level_0
(
        DxfMesh *mesh,
                /*!< a pointer to a DXF \c MESH entity. */
        int32_t vertex_count_level_0
                /*!< the \c vertex_count_level_0 to be set for the
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
                return (NULL);
        }
        mesh->vertex_count_level_0 = vertex_count_level_0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (mesh);
}


/*!
 * \brief Get the \c count_of_property_overridden from a DXF \c MESH
 * entity.
 *
 * \return \c count_of_property_overridden.
 */
int32_t
dxf_mesh_get_count_of_property_overridden
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
        return (mesh->count_of_property_overridden);
}


/* EOF*/
