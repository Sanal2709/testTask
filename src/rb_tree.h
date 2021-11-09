#ifndef RB_TREE_H
#define RB_TREE_H

#ifdef __cplusplus
extern "C" {
#endif

/*includes====================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include "stock_types.h"
/*defines=====================================================================*/

/*types=======================================================================*/
typedef struct Node Node_t;

typedef int (*compare_fn)(const order_t * const a, const order_t * const b);

typedef struct {
  Node_t * root;
  compare_fn fn;
} rb_tree_t;

/*prototypes==================================================================*/

/**
 * @brief Delete all rb Tree
 * 
 * @return pointer to the rb Tree
 */
rb_tree_t * rb_create(compare_fn fn);

/**
 * @brief Delete all rb Tree
 * 
 * @param rb_tree pointer to the rb Tree
 */
void rb_destroy(rb_tree_t * rb_tree);

/**
 * @brief Insert order to rb Tree
 * 
 * @param rb_tree pointer to the rb Tree
 * @param order income order
 * @return None
 */
void rb_insert_order(rb_tree_t * rb_tree, const order_t * order);

/**
 * @brief Delete order from rb Tree
 * 
 * @param rb_tree pointer to the rb Tree
 * @param order income order
 * @return None
 */
void rb_delete_order(rb_tree_t * rb_tree, order_t * order);

/**
 * @brief Search order
 * 
 * @param rb_tree pointer to the rb Tree
 * @param order income order
 * @return order_t* order that was found
 */
order_t * rb_search_order(rb_tree_t * rb_tree, order_t * order);

/**
 * @brief Get min order from rb Tree
 * 
 * @param rb_tree pointer to the rb Tree
 * @param order income order
 * @return order_t* minimum order
 */
order_t * rb_get_min(rb_tree_t * rb_tree);

/**
 * @brief Get max order from rb Tree
 * 
 * @param rb_tree pointer to the rb Tree
 * @param order income order
 * @return order_t* maximum order
 */
order_t * rb_get_max(rb_tree_t * rb_tree);


#ifdef __cplusplus
}
#endif

#endif /*RB_TREE_H*/