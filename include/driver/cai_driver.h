#pragma once

#include "ast/ast.h"
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>

#include <utility>

namespace cai {

class CaiDriver {
  friend class IRVisitor;

public:
  CaiDriver(const CaiDriver &) = delete;
  CaiDriver(CaiDriver &&) = delete;
  auto operator=(const CaiDriver &) -> CaiDriver & = delete;
  auto operator=(CaiDriver &&) -> CaiDriver & = delete;
  ~CaiDriver() = default;

  static auto get() -> CaiDriver &;

  /**
   * parse - parse from a file
   */
  auto parse() -> int;

  auto compile() -> void;

  auto init_module() -> CaiDriver &;

  auto set_input_file(std::string input_file) -> CaiDriver &;

  auto set_output_file(std::string output_file) -> CaiDriver &;

  auto set_emit_ir(bool emit_ir) -> CaiDriver &;

  auto set_optimize_level(int optimize_level) -> CaiDriver &;

private:
  CaiDriver() = default;

  std::string input_file_;  ///< input file
  std::string output_file_; ///< output file

  // TODO(zhm): set default value to false
  bool emit_ir_ = true;    ///< emit IR
  int optimize_level_ = 0; ///< optimization level

  std::unique_ptr<Program> program_;

  std::unique_ptr<llvm::LLVMContext> context_; ///< LLVM context
  std::unique_ptr<llvm::IRBuilder<>> builder_; ///< LLVM IR builder
  std::unique_ptr<llvm::Module> module_;       ///< LLVM module
};

} // namespace cai