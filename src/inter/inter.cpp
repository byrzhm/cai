#include "ast/ast.h"
#include "driver/cai_driver.h"
#include "inter/ir_visitor.h"

#include <iostream>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/Verifier.h>

namespace cai {

void IRVisitor::visit(Program &program) { program.func_decl().accept(*this); }

auto IRVisitor::visit(FunctionDeclaration &func_decl) -> llvm ::Function * {
  // TODO(zhm): add arguments
  llvm::FunctionType *func_type = llvm::FunctionType::get(
      llvm::Type::getInt32Ty(*CaiDriver::get().context_), false);
  llvm::Function *func =
      llvm::Function::Create(func_type, llvm::Function::ExternalLinkage,
                             func_decl.name(), CaiDriver::get().module_.get());

  // TODO(zhm): argument name
  // ...

  // create basic block
  llvm::BasicBlock *bb =
      llvm::BasicBlock::Create(*CaiDriver::get().context_, "entry", func);
  CaiDriver::get().builder_->SetInsertPoint(bb);

  // TODO(zhm): visit function body
  llvm::Value *ret_val = func_decl.body().accept(*this);

  if (ret_val == nullptr) {
    func->eraseFromParent();
    return nullptr;
  }

  llvm::verifyFunction(*func);
  return func;
}

auto IRVisitor::visit(ReturnStatement &ret_stmt) -> llvm::Value * {
  auto *return_value = ret_stmt.expr().accept(*this);
  CaiDriver::get().builder_->CreateRet(return_value);
  return return_value;
}

auto IRVisitor::visit(IntegerLiteral &int_lit) -> llvm::Value * {
  return llvm::ConstantInt::get(*CaiDriver::get().context_,
                                llvm::APInt(32, int_lit.value()));
}

} // namespace cai