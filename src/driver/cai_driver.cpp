#include "driver/cai_driver.h"
#include "inter/ir_visitor.h"
#include "parse/yy_driver.h"
#include "util/cai_log.h"

namespace cai {

auto CaiDriver::get() -> CaiDriver & {
  static CaiDriver instance;
  return instance;
}

auto CaiDriver::init_module() -> CaiDriver& {
  context_ = std::make_unique<llvm::LLVMContext>();
  builder_ = std::make_unique<llvm::IRBuilder<>>(*context_);
  module_ = std::make_unique<llvm::Module>(input_file_, *context_);
  return *this;
}

auto CaiDriver::set_input_file(std::string input_file) -> CaiDriver & {
  input_file_ = std::move(input_file);
  return *this;
}

auto CaiDriver::set_output_file(std::string output_file) -> CaiDriver & {
  output_file_ = std::move(output_file);
  return *this;
}

auto CaiDriver::set_emit_ir(bool emit_ir) -> CaiDriver & {
  emit_ir_ = emit_ir;
  return *this;
}

auto CaiDriver::set_optimize_level(int optimize_level) -> CaiDriver & {
  optimize_level_ = optimize_level;
  return *this;
}

//===============================================================================
// parse
//===============================================================================

auto CaiDriver::parse() -> int {
  yy::YYDriver driver(input_file_);
  int res = driver.parse();
  if (res == 0) {
    program_ = std::move(driver.program());
  }
  return res;
}

//===============================================================================
// compile
//===============================================================================

void CaiDriver::compile() {
  assert(program_ != nullptr);

  // visit AST
  IRVisitor ir_visitor;
  program_->accept(ir_visitor);

  // if (emit_ir_) {
  module_->print(llvm::errs(), nullptr);
  // }
}

} // namespace cai