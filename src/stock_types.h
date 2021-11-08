#ifndef STOCK_TYPES_H
#define STOCK_TYPES_H

#ifdef	__cplusplus
extern "C" {
#endif

/*includes====================================================================*/
#include <stdint.h>
/*defines=====================================================================*/

/*types=======================================================================*/
typedef enum { ORDER = 0, CANCEL = 1} stock_signal_t;

typedef enum { BUY = 0, SELL = 1} transaction_side_t;

typedef struct{
  uint64_t id;
  transaction_side_t side;
  uint64_t quantity;
  float price;
} order_t;

typedef struct{
  uint64_t order_id;
} cancel_t;

typedef struct {
  stock_signal_t type;
  union{
    order_t order;
    cancel_t cancel;
  } data;
} signal_t;

typedef struct{
  uint64_t id;
  transaction_side_t side;
  uint64_t oid1;
  uint64_t oid2;
  uint64_t quantity;
  float price;
} trade_t;

/*prototypes==================================================================*/

#ifdef __cplusplus
}
#endif

#endif /*STOCK_TYPES_H*/