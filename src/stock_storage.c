#include "stock_storage.h"
#include "rb_tree.h"
#include <stddef.h>
#include <stdlib.h>

static rb_tree_t * g_sell_orders;
static rb_tree_t * g_buy_orders;
static rb_tree_t * g_all_orders;

static int compare_price_orders(const order_t * const a, const order_t * const b){
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

static int compare_id_orders(const order_t * const a, const order_t * const b){
  if(a->id < b->id){
    return -1;
  }
  else if(a->id > b->id){
    return 1;
  }

  return 0;
}

int stock_storage_init(void){
  g_sell_orders = rb_create(compare_price_orders);
  g_buy_orders = rb_create(compare_price_orders);
  g_all_orders = rb_create(compare_id_orders);
}

int stock_storage_cleanup(void){
  rb_destroy(g_sell_orders);
  rb_destroy(g_buy_orders);
  rb_destroy(g_all_orders);
}

int stock_storage_insert(const order_t * order){
  if(!order){
    return -1;
  }

  if(order->side == BUY){
    rb_insert_order(g_buy_orders, order);
  }
  else{
    rb_insert_order(g_sell_orders, order);
  }

  rb_insert_order(g_all_orders, order);

  return 0;
}

int stock_storage_delete(uint64_t order_id){
  static order_t dummy_order;
  dummy_order.id = order_id;
  order_t * order = rb_search_order(g_all_orders, &dummy_order);
  if(!order){
    return -1;
  }

  if(order->side == SELL){
    rb_delete_order(g_sell_orders, order);
  }
  else{
    rb_delete_order(g_buy_orders, order);
  }

  rb_delete_order(g_all_orders, order);

  return 0;
}

order_t * stock_storage_get_buy_order(void){
  order_t * max_price = rb_get_max(g_buy_orders);
  if(max_price == NULL){
    return NULL;
  }

  return max_price;
}

order_t * stock_storage_get_sell_order(void){
  order_t * min_price = rb_get_min(g_sell_orders);
  if(min_price == NULL){
    return NULL;
  }

  return min_price;
}