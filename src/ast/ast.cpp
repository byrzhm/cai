#include "ast/ast.h"
#include "ast/ast_visitor.h"

namespace cai {

void Program::accept(AstNodeVisitor &visitor) { visitor.visit(*this); }

auto FunctionDeclaration::accept(AstNodeVisitor &visitor) -> llvm::Function * {
  return visitor.visit(*this);
}

auto ReturnStatement::accept(AstNodeVisitor &visitor) -> llvm::Value * {
  return visitor.visit(*this);
}

auto IntegerLiteral::accept(AstNodeVisitor &visitor) -> llvm::Value * {
  return visitor.visit(*this);
}

} // namespace cai