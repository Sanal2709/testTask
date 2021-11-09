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

/**
 * @brief Init storage
 * 
 * @return int 0 - ok, else - error
 */
int stock_storage_init(void);

/**
 * @brief Release all resources
 * 
 * @return int 0 - ok, else - error
 */
int stock_storage_cleanup(void);

/**
 * @brief Add new order to storage
 * 
 * @param order order that will be saved
 * @return int 0 - ok, else - error
 */
int stock_storage_insert(const order_t * order);

/**
 * @brief Delete given order
 * 
 * @param order_id order id that should be deleted
 * @return int 0 - ok, else - error
 */
int stock_storage_delete(uint64_t order_id);

/**
 * @brief Get appropriate buy order
 * 
 * @return order_t* pointer to the found order
 */
order_t * stock_storage_get_buy_order(void);

/**
 * @brief Get appropriate sell order
 * 
 * @return order_t* order_t* pointer to the found order
 */
order_t * stock_storage_get_sell_order(void);

#ifdef __cplusplus
}
#endif

#endif /*STOCK_STORAGE_H*/