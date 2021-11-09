#include "rb_tree.h"
#include <stddef.h>
#include <string.h>
#include <stdio.h>

#define NIL &sentinel

typedef enum {RED, BLACK} Color_t;

struct Node{
  order_t order;
  Color_t color;
  Node_t * left;
  Node_t * right;
  Node_t * parent;
};

static Node_t sentinel = {{0}, BLACK, NIL, NIL, NULL};

static Node_t * rb_create_node(const order_t * order, Node_t * parent){
  Node_t * new_elem = malloc(sizeof(Node_t));
  if(!new_elem){
    fprintf(stderr, "Could not allocate memory\n");
    return NULL;
  }

  memcpy(&(new_elem->order), order, sizeof(order_t));
  new_elem->left = NIL;
  new_elem->right = NIL;
  new_elem->parent = parent;
  new_elem->color = RED;

  return new_elem;
}

static void rb_rotate_left(rb_tree_t * tree, Node_t * x){
  Node_t *y = x->right;

  x->right = y->left;
  if (y->left != NIL) y->left->parent = x;

  if (y != NIL) y->parent = x->parent;
  if (x->parent) {
      if (x == x->parent->left)
          x->parent->left = y;
      else
          x->parent->right = y;
  } else {
      tree->root = y;
  }

  y->left = x;
  if (x != NIL) x->parent = y;
}

static void rb_rotate_right(rb_tree_t * tree, Node_t * x){
 Node_t *y = x->left;

  x->left = y->right;
  if (y->right != NIL) y->right->parent = x;

  if (y != NIL) y->parent = x->parent;
  if (x->parent) {
      if (x == x->parent->right)
          x->parent->right = y;
      else
          x->parent->left = y;
  } else {
      tree->root = y;
  }

  y->right = x;
  if (x != NIL) x->parent = y;
}

static void rb_insert_fix(rb_tree_t * tree, Node_t * x){
  while (x != tree->root && x->parent->color == RED){
    if (x->parent == x->parent->parent->left){
      Node_t *y = x->parent->parent->right;
      if (y->color == RED){
        x->parent->color = BLACK;
        y->color = BLACK;
        x->parent->parent->color = RED;
        x = x->parent->parent;
      }
      else{
        if (x == x->parent->right){
          x = x->parent;
          rb_rotate_left(tree, x);
        }

        x->parent->color = BLACK;
        x->parent->parent->color = RED;
        rb_rotate_right(tree, x->parent->parent);
      }
    }
    else{
      Node_t *y = x->parent->parent->left;
      if (y->color == RED){
        x->parent->color = BLACK;
        y->color = BLACK;
        x->parent->parent->color = RED;
        x = x->parent->parent;
      }
      else{
        if (x == x->parent->left){
          x = x->parent;
          rb_rotate_right(tree, x);
        }
        x->parent->color = BLACK;
        x->parent->parent->color = RED;
        rb_rotate_left(tree, x->parent->parent);
      }
    }
  }
  tree->root->color = BLACK;
}

static Node_t * rb_insert(rb_tree_t * tree, const order_t * order, compare_fn compare_orders){
  Node_t * current = tree->root;
  Node_t * x = NULL;
  Node_t * parent = NULL;

  while (current != NIL){
    if(compare_orders(&(current->order), order) == 0){
      return (current);
    }

    parent = current;

    if(compare_orders(&(current->order), order) > 0){
      current = current->left;
    }
    else{
      current = current->right;
    }
  }

  x = rb_create_node(order, parent);
  if(!x){
    fprintf(stderr, "Could not allocate memory\n");
    return NULL;
  }

  x->parent = parent;
  x->left = NIL;
  x->right = NIL;
  x->color = RED;

  if(parent){
    if (compare_orders(&(parent->order), order) > 0){
      parent->left = x;
    }
    else{
      parent->right = x;
    }
  }
  else{
    tree->root = x;
  }

  rb_insert_fix(tree, x);
  return (x);
}

static void rb_delete(Node_t * root){
  if(root == NIL){
    return;
  }

  rb_delete(root->left);
  rb_delete(root->right);
  free(root);
}

static Node_t * rb_get_min_rec(Node_t * root){
  if(root->left != NIL){
    return rb_get_min_rec(root->left);
  }

  if(root == NIL){
    return NULL;
  }

  return root;
}

static Node_t * rb_get_max_rec(Node_t * root){
  if(root->right != NIL){
    return rb_get_max_rec(root->right);
  }

  if(root == NIL){
    return NULL;
  }

  return root;
}

rb_tree_t * rb_create(compare_fn fn){
  rb_tree_t * new_rb = malloc(sizeof(rb_tree_t));
  if(!new_rb){
    fprintf(stderr, "Could not allocate memory\n");
    return NULL;
  }

  new_rb->root = NIL;
  new_rb->fn = fn;
}

void rb_destroy(rb_tree_t * rb_tree){
  rb_delete(rb_tree->root);
  free(rb_tree);
}

void rb_insert_order(rb_tree_t * rb_tree, const order_t * order){
  if(!order){
    fprintf(stderr, "Empty order\n");
    return;
  }

  rb_insert(rb_tree, order, rb_tree->fn);
}

void rb_delete_fix(rb_tree_t * rb_tree, Node_t *x)
{
  while(x != rb_tree->root && x->color == BLACK){
    if (x == x->parent->left){
      Node_t *w = x->parent->right;
      if (w->color == RED){
        w->color = BLACK;
        x->parent->color = RED;
        rb_rotate_left(rb_tree, x->parent);
        w = x->parent->right;
      }
      if (w->left->color == BLACK && w->right->color == BLACK){
        w->color = RED;
        x = x->parent;
      }
      else{
        if (w->right->color == BLACK){
          w->left->color = BLACK;
          w->color = RED;
          rb_rotate_right(rb_tree, w);
          w = x->parent->right;
        }
        w->color = x->parent->color;
        x->parent->color = BLACK;
        w->right->color = BLACK;
        rb_rotate_left(rb_tree, x->parent);
        x = rb_tree->root;
      }
    }
    else{
      Node_t *w = x->parent->left;
      if (w->color == RED){
        w->color = BLACK;
        x->parent->color = RED;
        rb_rotate_right(rb_tree, x->parent);
        w = x->parent->left;
      }
      if (w->right->color == BLACK && w->left->color == BLACK){
        w->color = RED;
        x = x->parent;
      }
      else{
        if (w->left->color == BLACK){
          w->right->color = BLACK;
          w->color = RED;
          rb_rotate_left(rb_tree, w);
          w = x->parent->left;
        }
        w->color = x->parent->color;
        x->parent->color = BLACK;
        w->left->color = BLACK;
        rb_rotate_right(rb_tree, x->parent);
        x = rb_tree->root;
      }
    }
  }
  x->color = BLACK;
}

static void rb_delete_node(rb_tree_t * rb_tree, Node_t * z){
  Node_t *x, *y;

  if (!z || z == NIL){
    return;
  }

  if (z->left == NIL || z->right == NIL){
    y = z;
  }
  else{
    y = z->right;
    while (y->left != NIL){
      y = y->left;
    }
  }

  if (y->left != NIL){
    x = y->left;
  }
  else{
    x = y->right;
  }

  x->parent = y->parent;
  if (y->parent){
    if (y == y->parent->left){
      y->parent->left = x;
    }
    else{
      y->parent->right = x;
    }
  }
  else{
    rb_tree->root = x;
  }

  if (y != z){
    z->order = y->order;
  }

  if (y->color == BLACK){
    rb_delete_fix(rb_tree, x);
  }

  free(y);
}

static Node_t *rb_find_node(rb_tree_t * rb_tree, order_t * order, compare_fn compare_orders) {
  Node_t *current = rb_tree->root;
  while (current != NIL){
    if (compare_orders(&(current->order), order) == 0)
      return (current);
    else if(compare_orders(&(current->order), order) > 0){
      current = current->left;
    }
    else{
      current = current->right;
    }
  }

  return NULL;
}

void rb_delete_order(rb_tree_t * rb_tree, order_t * order){
  if(!rb_tree || !order){
    return;
  }

  Node_t * to_delete = rb_find_node(rb_tree, order, rb_tree->fn);
  if(!to_delete){
    return;
  }
  
  rb_delete_node(rb_tree, to_delete);
}

order_t * rb_get_min(rb_tree_t * rb_tree){
  if(rb_tree == NULL){
    return NULL;
  }

  Node_t * min_node = rb_get_min_rec(rb_tree->root);

  if(!min_node){
    return NULL;
  }

  return &(min_node->order);
}

order_t * rb_get_max(rb_tree_t * rb_tree){
  if(rb_tree == NULL || rb_tree->root == NULL){
    return NULL;
  }

  Node_t * max_node = rb_get_max_rec(rb_tree->root);

  if(!max_node){
    return NULL;
  }

  return &(max_node->order);
}

order_t * rb_search_order(rb_tree_t * rb_tree, order_t * order){
  Node_t * node = rb_find_node(rb_tree, order, rb_tree->fn);
  if(!node){
    return NULL;
  }

  return &(node->order);
}