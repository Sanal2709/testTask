#include <gtest/gtest.h>
#include "stock_types.h"
#include "stock_storage.h"
#include "rb_tree.h"
#include <stdlib.h>

static int compare_orders(const order_t * const a, const order_t * const b){
  float precision = 0.001;
  if( (a->price - precision < b->price) && (a->price + precision > b->price) ){
    if(a->id > b->id){
      return -1;
    }
    else if(a->id < b->id){
      return 1;
    }
    return 0;
  }
  else if(a->price < b->price){
    return -1;
  }

  return 1;
}

TEST(rb_tree, sort_feature)
{
  rb_tree_t *rb = rb_create(compare_orders);
  order_t order;
  order.id = 1;
  order.price = 250.12f;
  order.quantity = 10;
  order.side = BUY;
  rb_insert_order(rb, &order);

  order.id = 2;
  order.price = 249.10f;
  order.quantity = 8;
  order.side = BUY;
  rb_insert_order(rb, &order);

  order.id = 3;
  order.price = 250.12f;
  order.quantity = 5;
  order.side = BUY;
  rb_insert_order(rb, &order);

  order.id = 4;
  order.price = 250.6f;
  order.quantity = 15;
  order.side = BUY;
  rb_insert_order(rb, &order);

  order_t *max = rb_get_max(rb);
  EXPECT_EQ(max->id, 4);
  EXPECT_EQ(max->side, BUY);
  EXPECT_EQ(max->quantity, 15);
  EXPECT_FLOAT_EQ(max->price, 250.6f);
  rb_delete_order(rb, max);

  max = rb_get_max(rb);
  EXPECT_EQ(max->id, 1);
  EXPECT_EQ(max->side, BUY);
  EXPECT_EQ(max->quantity, 10);
  EXPECT_FLOAT_EQ(max->price, 250.12f);
  rb_delete_order(rb, max);

  max = rb_get_max(rb);
  EXPECT_EQ(max->id, 3);
  EXPECT_EQ(max->side, BUY);
  EXPECT_EQ(max->quantity, 5);
  EXPECT_FLOAT_EQ(max->price, 250.12f);
  rb_delete_order(rb, max);

  max = rb_get_max(rb);
  EXPECT_EQ(max->id, 2);
  EXPECT_EQ(max->side, BUY);
  EXPECT_EQ(max->quantity, 8);
  EXPECT_FLOAT_EQ(max->price, 249.10f);
  rb_delete_order(rb, max);

  rb_destroy(rb);
}