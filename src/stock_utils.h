#ifndef STOCK_UTILS_H
#define STOCK_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

/*includes====================================================================*/
#include "stock_types.h"
#include <stdio.h>
/*defines=====================================================================*/

/*types=======================================================================*/

/*prototypes==================================================================*/

/**
 * @brief Parse input signal
 * 
 * @param[in] line null-terminated string, will be modified
 * @param[out] signal type of signal and it's corresponding data
 * @return If 0 - ok, else - error
 */
int stock_utils_parse_signal(char * line, signal_t * signal);

/**
 * @brief Print trade event to file
 * 
 * @param out_fp output file
 * @param trade trade info
 * @return int 0 - ok, else - error
 */
int stock_utils_print_trade(FILE *out_fp, const trade_t * const trade);

/**
 * @brief Print cancel order event to file
 * 
 * @param out_fp output file
 * @param order_id id of order that was canceled
 * @return int int 0 - ok, else - error
 */
int stock_utils_print_cancel(FILE *out_fp, uint64_t order_id);

#ifdef __cplusplus
}
#endif

#endif /*STOCK_UTILS_H*/