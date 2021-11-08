#include <gtest/gtest.h>
#include "stock_utils.h"
#include "stock_types.h"

TEST(stock_utils_parse_signal, parse_order_positive) {
  signal_t signal = {};
  char string[] = "O,1,S,42,251.36";

  EXPECT_EQ(stock_utils_parse_signal(string, &signal), 0);

  EXPECT_EQ(signal.type, ORDER);
  EXPECT_EQ(signal.data.order.side, SELL);
  EXPECT_EQ(signal.data.order.quantity, 42);
  EXPECT_FLOAT_EQ(signal.data.order.price, 251.36);
}

TEST(stock_utils_parse_signal, parse_cancel_positive) {
  signal_t signal = {};
  char string[] = "C,1";

  EXPECT_EQ(stock_utils_parse_signal(string, &signal), 0);

  EXPECT_EQ(signal.type, CANCEL);
  EXPECT_EQ(signal.data.cancel.order_id, 1);
}
