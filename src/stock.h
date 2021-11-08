#ifndef STOCK_H
#define STOCK_H

#ifdef __cplusplus
extern "C" {
#endif

/*includes====================================================================*/
#include "stock_types.h"
#include "stdio.h"
/*defines=====================================================================*/

/*types=======================================================================*/

/*prototypes==================================================================*/
/**
 * @brief Initiate stock
 * 
 * @return If 0 - ok, else - error
 */
int stock_init(FILE *out_fp);

/**
 * @brief Release all acquired resources
 * 
 * @return If 0 - ok, else - error
 */
int stock_cleanup(void);

/**
 * @brief Handle input signal
 * 
 * @param[in] signal input signal, order or cancel
 * @return If 0 - ok, else - error
 */
int stock_handle_signal(signal_t * signal);

#ifdef __cplusplus
}
#endif

#endif /*STOCK_H*/