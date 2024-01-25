#include "ast/ast.h"
#include <iostream>

namespace {

const int INDENT_SIZE = 4;

auto padding(int n = INDENT_SIZE) -> std::ostream & {
  for (int i = 0; i < n; ++i) {
    std::cout << ' ';
  }
  return std::cout;
}

} // namespace

namespace cai {

void Program::irgen() { func_decl_->irgen(); }

void FunctionDeclaration::irgen() {
  padding(0) << "define " << name_ << " () {\n";
  body_->irgen();
  padding(0) << "}\n";
}

void IntegerLiteral::irgen() { padding() << "t0 := " << value_ << ";\n"; }

void ReturnStatement::irgen() {
  expr_->irgen();
  padding() << "%r0 := t0;\n";
  padding() << "return r0;\n";
}

} // namespace cai