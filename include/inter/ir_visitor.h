#pragma
#include "ast/ast_visitor.h"

namespace cai {

class IRVisitor : public AstNodeVisitor {
public:
  void visit(class Program &program) override;
  auto visit(class IntegerLiteral &int_lit) -> llvm::Value * override;
  auto visit(class ReturnStatement &ret_stmt) -> llvm::Value * override;
  auto visit(class FunctionDeclaration &func_decl) -> llvm::Function * override;
};

} // namespace cai