#include "stock.h"
#include "stock_types.h"
#include "stock_storage.h"
#include "stock_utils.h"
#include <stddef.h>
#include <stdlib.h>

static uint64_t g_trade_count = 1;
static FILE *g_out_fp;

int stock_init(FILE *out_fp){
  if(!out_fp){
    fprintf(stderr, "Output file error\n");
    exit(EXIT_FAILURE);
  }

  g_out_fp = out_fp;
  stock_storage_init();
}

int stock_cleanup(void){
  stock_storage_cleanup();
}

static int stock_handle_buy_order(order_t * buy_order){
  if(!buy_order){
    return -1;
  }

  static trade_t trade = {0};
  for(;;){
    order_t * sell_order = stock_storage_get_sell_order();
    if(!sell_order || (sell_order->price > buy_order->price)){
      //there is no appropriate order, so just save and exit
      stock_storage_insert(buy_order);
      break;
    }

    trade.id = g_trade_count++;
    trade.side = SELL;
    trade.oid1 = sell_order->id;
    trade.oid2 = buy_order->id;
    trade.quantity = (sell_order->quantity < buy_order->quantity)? sell_order->quantity : buy_order->quantity;
    trade.price = sell_order->price;

    stock_utils_print_trade(g_out_fp, &trade);

    sell_order->quantity -= trade.quantity;
    if(sell_order->quantity == 0){
      //this buy order was closed
      stock_storage_delete(sell_order->id);
    }

    buy_order->quantity -= trade.quantity;
    if(buy_order->quantity == 0){
      break;
    }
  }

  return 0;
}

static int stock_handle_sell_order(order_t * sell_order){
  if(!sell_order){
    return -1;
  }

  static trade_t trade = {0};
  for(;;){
    order_t * buy_order = stock_storage_get_buy_order();
    if(!buy_order || (buy_order->price < sell_order->price)){
      //there is no appropriate order, so just save and exit
      stock_storage_insert(sell_order);
      break;
    }

    trade.id = g_trade_count++;
    trade.side = BUY;
    trade.oid1 = buy_order->id;
    trade.oid2 = sell_order->id;
    trade.quantity = (sell_order->quantity < buy_order->quantity)? sell_order->quantity : buy_order->quantity;
    trade.price = buy_order->price;

    stock_utils_print_trade(g_out_fp, &trade);

    buy_order->quantity -= trade.quantity;
    if(buy_order->quantity == 0){
      //this buy order was closed
      stock_storage_delete(buy_order->id);
    }

    sell_order->quantity -= trade.quantity;
    if(sell_order->quantity == 0){
      break;
    }
  }

  return 0;
}

int stock_handle_signal(signal_t * signal){
  if(!signal){
    return -1;
  }

  if(signal->type == CANCEL){
    if(stock_storage_delete(signal->data.cancel.order_id) == 0){
      stock_utils_print_cancel(g_out_fp, signal->data.cancel.order_id);
    }
    return 0;
  }

  if(signal->data.order.side == SELL){
    return stock_handle_sell_order(&(signal->data.order));
  }

  return stock_handle_buy_order(&(signal->data.order));
}