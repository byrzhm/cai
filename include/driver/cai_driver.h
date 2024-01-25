#pragma once

#include "parse/yy_driver.h"

namespace cai {

class CaiDriver {
public:
  CaiDriver() = default;
  CaiDriver(const CaiDriver &) = delete;
  CaiDriver(CaiDriver &&) = delete;
  auto operator=(const CaiDriver &) -> CaiDriver & = delete;
  auto operator=(CaiDriver &&) -> CaiDriver & = delete;
  ~CaiDriver() = default;

  /**
   * parse - parse from a file
   * @param filename - valid string with input file
   */
  auto parse(const std::string &filename) -> int;

  [[nodiscard]] auto trace_parsing() const -> bool { return trace_parsing_; }
  void set_trace_parsing(bool trace_parsing) { trace_parsing_ = trace_parsing; }

  [[nodiscard]] auto trace_scanning() const -> bool { return trace_scanning_; }
  void set_trace_scanning(bool trace_scanning) {
    trace_scanning_ = trace_scanning;
  }

  [[nodiscard]] auto program() const -> const Program & { return *program_; }
  [[nodiscard]] auto program() -> Program & { return *program_; }

  void set_program(std::unique_ptr<Program> program) {
    program_ = std::move(program);
  }

private:
  std::unique_ptr<Program> program_;

  bool trace_parsing_ = false;
  bool trace_scanning_ = false;

  yy::YYDriver yy_driver_;
};

} // namespace cai