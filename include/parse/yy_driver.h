#pragma once

#include <cstddef>
#include <istream>
#include <memory>
#include <string>
#include <utility>

#include "ast/ast.h"
#include "yy_parser.tab.hh"

// Give Flex the prototype of yylex we want ...
#define YY_DECL auto yylex(yy::YYDriver &drv)->yy::YYParser::symbol_type
// ... and declare it for the parser's sake.
YY_DECL;

namespace yy {

class YYDriver {
public:
  YYDriver() = default;
  YYDriver(const YYDriver &) = delete;
  YYDriver(YYDriver &&) = delete;
  auto operator=(const YYDriver &) -> YYDriver & = delete;
  auto operator=(YYDriver &&) -> YYDriver & = delete;
  ~YYDriver() = default;

  explicit YYDriver(std::string filename, bool trace_parsing = false,
                    bool trace_scanning = false)
      : filename_(std::move(filename)), trace_parsing_(trace_parsing),
        trace_scanning_(trace_scanning) {}

  auto parse() -> int;

  auto parse(const std::string &filename) -> int;

  auto get_location() -> location & { return location_; }

  /**
   * @brief 关于词法分析器的接口
   */
  void scan_begin();
  void scan_end();

  [[nodiscard]] auto trace_parsing() const -> bool { return trace_parsing_; }
  void set_trace_parsing(bool trace_parsing) { trace_parsing_ = trace_parsing; }

  [[nodiscard]] auto trace_scanning() const -> bool { return trace_scanning_; }
  void set_trace_scanning(bool trace_scanning) {
    trace_scanning_ = trace_scanning;
  }

  [[nodiscard]] auto program() const -> const std::unique_ptr<cai::Program> & {
    return program_;
  }
  [[nodiscard]] auto program() -> std::unique_ptr<cai::Program> & { return program_; }

  void set_program(std::unique_ptr<cai::Program> program) {
    program_ = std::move(program);
  }

private:
  location location_;

  std::string filename_;

  std::unique_ptr<cai::Program> program_;

  // for unittest default to true
  bool trace_parsing_ = true;
  bool trace_scanning_ = true;
};

} // namespace yy
