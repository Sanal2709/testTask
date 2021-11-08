#ifndef STOCK_STORAGE_H
#define STOCK_STORAGE_H

#ifdef __cplusplus
extern "C" {
#endif

/*includes====================================================================*/
#include "stock_types.h"
/*defines=====================================================================*/

/*types=======================================================================*/

/*prototypes==================================================================*/

int stock_storage_init(void);

int stock_storage_cleanup(void);

int stock_storage_insert(const order_t * order);

int stock_storage_delete(uint64_t order_id);

order_t * stock_storage_get_buy_order(void);

order_t * stock_storage_get_sell_order(void);

#ifdef __cplusplus
}
#endif

#endif /*STOCK_STORAGE_H*/