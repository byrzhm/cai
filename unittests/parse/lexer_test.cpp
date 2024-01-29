#include "parse/yy_driver.h"
#include <fstream>
#include <gtest/gtest.h>

TEST(LexerTest, BasicTest) {
  yy::YYDriver driver("test_files/valid/return_2.test", false, true);

  driver.scan_begin();
  while (true) {
    yy::YYParser::symbol_type token = yylex(driver);

    if (token.kind_ == yy::YYParser::symbol_kind_type::S_YYEOF) {
      break;
    }

    std::cout << driver.get_location().begin.line << ":"
              << driver.get_location().begin.column << " - "
              << driver.get_location().end.line << ":"
              << driver.get_location().end.column << " " << token.kind_ << '\n';
  }
  driver.scan_end();
}