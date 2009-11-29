/*****************************************************************************
 * tdestroy.c: GNU tdestroy() replacement
 *****************************************************************************
 * Copyright © 1998-2009 the VideoLAN project
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <stdlib.h>
#include <search.h>

typedef struct node_t
{
    void        *key;
    struct node_t *left, *right;
} node;

static void tdestroy_recurse (node *root, __free_fn_t freefct)
{
    if (root->left != NULL)
        tdestroy_recurse (root->left, freefct);
    if (root->right != NULL)
        tdestroy_recurse (root->right, freefct);
    (*freefct) ((void *) root->key);
    /* Free the node itself.  */
    free (root);
}

void tdestroy (void *vroot, __free_fn_t freefct)
{
    node *root = (node *) vroot;
    if (root != NULL) {
        tdestroy_recurse (root, freefct);
    }
}
