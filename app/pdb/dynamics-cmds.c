/* GIMP - The GNU Image Manipulation Program
 * Copyright (C) 1995-2003 Spencer Kimball and Peter Mattis
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/* NOTE: This file is auto-generated by pdbgen.pl. */

#include "config.h"

#include <gegl.h>

#include <gdk-pixbuf/gdk-pixbuf.h>

#include "libgimpbase/gimpbase.h"

#include "pdb-types.h"

#include "core/gimp.h"
#include "core/gimpcontainer-filter.h"
#include "core/gimpcontainer.h"
#include "core/gimpdatafactory.h"
#include "core/gimpparamspecs.h"

#include "gimppdb.h"
#include "gimpprocedure.h"
#include "internal-procs.h"


static GimpValueArray *
dynamics_refresh_invoker (GimpProcedure         *procedure,
                          Gimp                  *gimp,
                          GimpContext           *context,
                          GimpProgress          *progress,
                          const GimpValueArray  *args,
                          GError               **error)
{
  gimp_data_factory_data_refresh (gimp->dynamics_factory, context);

  return gimp_procedure_get_return_values (procedure, TRUE, NULL);
}

static GimpValueArray *
dynamics_get_list_invoker (GimpProcedure         *procedure,
                           Gimp                  *gimp,
                           GimpContext           *context,
                           GimpProgress          *progress,
                           const GimpValueArray  *args,
                           GError               **error)
{
  gboolean success = TRUE;
  GimpValueArray *return_vals;
  const gchar *filter;
  gint32 num_dynamics = 0;
  gchar **dynamics_list = NULL;

  filter = g_value_get_string (gimp_value_array_index (args, 0));

  if (success)
    {
      dynamics_list = gimp_container_get_filtered_name_array (gimp_data_factory_get_container (gimp->dynamics_factory),
                                                              filter, &num_dynamics);
    }

  return_vals = gimp_procedure_get_return_values (procedure, success,
                                                  error ? *error : NULL);

  if (success)
    {
      g_value_set_int (gimp_value_array_index (return_vals, 1), num_dynamics);
      gimp_value_take_stringarray (gimp_value_array_index (return_vals, 2), dynamics_list, num_dynamics);
    }

  return return_vals;
}

void
register_dynamics_procs (GimpPDB *pdb)
{
  GimpProcedure *procedure;

  /*
   * gimp-dynamics-refresh
   */
  procedure = gimp_procedure_new (dynamics_refresh_invoker);
  gimp_object_set_static_name (GIMP_OBJECT (procedure),
                               "gimp-dynamics-refresh");
  gimp_procedure_set_static_strings (procedure,
                                     "gimp-dynamics-refresh",
                                     "Refresh current paint dynamics. This function always succeeds.",
                                     "This procedure retrieves all paint dynamics currently in the user's paint dynamics path and updates the paint dynamics dialogs accordingly.",
                                     "Michael Natterer <mitch@gimp.org>",
                                     "Michael Natterer",
                                     "2011",
                                     NULL);
  gimp_pdb_register_procedure (pdb, procedure);
  g_object_unref (procedure);

  /*
   * gimp-dynamics-get-list
   */
  procedure = gimp_procedure_new (dynamics_get_list_invoker);
  gimp_object_set_static_name (GIMP_OBJECT (procedure),
                               "gimp-dynamics-get-list");
  gimp_procedure_set_static_strings (procedure,
                                     "gimp-dynamics-get-list",
                                     "Retrieve the list of loaded paint dynamics.",
                                     "This procedure returns a list of the paint dynamics that are currently available.",
                                     "Michael Natterer <mitch@gimp.org>",
                                     "Michael Natterer",
                                     "2011",
                                     NULL);
  gimp_procedure_add_argument (procedure,
                               gimp_param_spec_string ("filter",
                                                       "filter",
                                                       "An optional regular expression used to filter the list",
                                                       FALSE, TRUE, FALSE,
                                                       NULL,
                                                       GIMP_PARAM_READWRITE));
  gimp_procedure_add_return_value (procedure,
                                   gimp_param_spec_int32 ("num-dynamics",
                                                          "num dynamics",
                                                          "The number of available paint dynamics",
                                                          0, G_MAXINT32, 0,
                                                          GIMP_PARAM_READWRITE));
  gimp_procedure_add_return_value (procedure,
                                   gimp_param_spec_string_array ("dynamics-list",
                                                                 "dynamics list",
                                                                 "The list of paint dynamics names",
                                                                 GIMP_PARAM_READWRITE));
  gimp_pdb_register_procedure (pdb, procedure);
  g_object_unref (procedure);
}