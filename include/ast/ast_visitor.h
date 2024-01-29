#pragma once

#include <llvm/IR/Value.h>

namespace cai {

class AstNodeVisitor {
public:
  AstNodeVisitor() = default;
  AstNodeVisitor(const AstNodeVisitor &) = default;
  AstNodeVisitor(AstNodeVisitor &&) = delete;
  auto operator=(const AstNodeVisitor &) -> AstNodeVisitor & = default;
  auto operator=(AstNodeVisitor &&) -> AstNodeVisitor & = delete;
  virtual ~AstNodeVisitor() = default;

  virtual void visit([[maybe_unused]] class Program &program) = 0;
  virtual auto visit([[maybe_unused]] class IntegerLiteral &int_lit)
      -> llvm::Value * = 0;
  virtual auto visit([[maybe_unused]] class ReturnStatement &ret_stmt)
      -> llvm::Value * = 0;
  virtual auto visit([[maybe_unused]] class FunctionDeclaration &func_decl)
      -> llvm::Function * = 0;
};

} // namespace cai