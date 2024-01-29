#include "parse/yy_driver.h"
#include <fstream>
#include <gtest/gtest.h>

/**
 * @brief 符合语法规则的测试
 */
TEST(ParserTest, Return2) {
  yy::YYDriver driver;
  driver.set_trace_parsing(true);

  std::cout << driver.parse("test_files/valid/return_2.test") << std::endl;
}

TEST(ParserTest, Return0) {
  yy::YYDriver driver;
  driver.set_trace_parsing(true);

  std::cout << driver.parse("test_files/valid/return_0.test") << std::endl;
}

/**
 * @brief 不符合语法规则的测试
 */

TEST(ParserTest, MissingParen) {
  yy::YYDriver driver;
  driver.set_trace_parsing(true);

  std::cout << driver.parse("test_files/invalid/missing_paren.test")
            << std::endl;
}