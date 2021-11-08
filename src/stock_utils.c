#include "stock_utils.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>

int stock_utils_parse_signal(char * line, signal_t * signal){
  memset(signal, 0, sizeof(signal_t));
  if(!line){
    return -1;
  }

  char * type_str = strtok(line, ",");
  if(type_str == NULL){
    return -1;
  }
  char * id_str = strtok(NULL, ",");
  if(id_str == NULL){
    return -1;
  }
  uint64_t order_id = atoll(id_str);

  if(strcmp(type_str, "O") == 0){
    signal->type = ORDER;
    signal->data.order.id = order_id;

    char * side_str = strtok(NULL, ",");
    if(side_str == NULL){
      return -1;
    }
    if(strcmp(side_str, "S") == 0){
      signal->data.order.side = SELL;
    }
    else if(strcmp(side_str, "B") == 0){
      signal->data.order.side = BUY;
    }

    char * quantity_str = strtok(NULL, ",");
    if(quantity_str == NULL){
      return -1;
    }
    signal->data.order.quantity = atoll(quantity_str);

    char * price_str = strtok(NULL, ",");
    if(price_str == NULL){
      return -1;
    }
    signal->data.order.price = atof(price_str);
  }
  else if(strcmp(type_str, "C") == 0){
    signal->type = CANCEL;
    signal->data.cancel.order_id = order_id;
  }

  return 0;
}

int stock_utils_print_trade(FILE *out_fp, const trade_t * const trade){
  if(!trade){
    return -1;
  }

  char type[2] = {0};
  if(trade->side == SELL){
    type[0] = 'S';
  }
  else{
    type[0] = 'B';
  }

  fprintf(out_fp, "T,%"PRIu64",%s,%"PRIu64",%"PRIu64",%"PRIu64",%g\n", trade->id, type, trade->oid1, trade->oid2, trade->quantity, trade->price);
  return 0;
}

int stock_utils_print_cancel(FILE *out_fp, uint64_t order_id){
  fprintf(out_fp, "X,%"PRIu64"\n", order_id);
}