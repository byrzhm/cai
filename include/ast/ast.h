#pragma once

#include <memory>
#include <string>

namespace cai {

class FunctionDeclaration;
class Statement;

class AstNode {
public:
  AstNode() = default;
  AstNode(const AstNode &) = default;
  AstNode(AstNode &&) = default;
  virtual ~AstNode() = default;

  auto operator=(const AstNode &) -> AstNode & = default;
  auto operator=(AstNode &&) -> AstNode & = default;

  // IR generation
  virtual void irgen() {}
};

class Program : public AstNode {
public:
  Program() = delete;
  Program(const Program &) = delete; // unique_ptr
  Program(Program &&) = default;
  auto operator=(const Program &) -> Program & = delete; // unique_ptr
  auto operator=(Program &&) -> Program & = default;
  ~Program() override = default;

  explicit Program(std::unique_ptr<FunctionDeclaration> func_decl)
      : func_decl_(std::move(func_decl)) {}

  [[nodiscard]] auto func_decl() const -> const FunctionDeclaration & {
    return *func_decl_;
  }

  [[nodiscard]] auto func_decl() -> FunctionDeclaration & {
    return *func_decl_;
  }

  void irgen() override;

private:
  // TODO(): vector of declarations
  std::unique_ptr<FunctionDeclaration> func_decl_;
};

class Declaration : public AstNode {
public:
  Declaration() = default;
  Declaration(const Declaration &) = default;
  Declaration(Declaration &&) = default;
  auto operator=(const Declaration &) -> Declaration & = default;
  auto operator=(Declaration &&) -> Declaration & = default;
  ~Declaration() override = default;
};

class FunctionDeclaration : public Declaration {
public:
  FunctionDeclaration() = default;
  FunctionDeclaration(const FunctionDeclaration &) = delete;
  FunctionDeclaration(FunctionDeclaration &&) = default;
  auto operator=(const FunctionDeclaration &) -> FunctionDeclaration & = delete;
  auto operator=(FunctionDeclaration &&) -> FunctionDeclaration & = default;
  ~FunctionDeclaration() override = default;

  FunctionDeclaration(std::string name, std::unique_ptr<Statement> body)
      : name_(std::move(name)), body_(std::move(body)) {}

  [[nodiscard]] auto name() const -> const std::string & { return name_; }
  [[nodiscard]] auto body() const -> const Statement & { return *body_; }
  [[nodiscard]] auto body() -> Statement & { return *body_; }

  void irgen() override;

private:
  std::string name_;
  // TODO(): vector of parameters
  // TODO(): return type
  // TODO(): body is vector of statements
  std::unique_ptr<Statement> body_; // body may be nullptr, means purely
                                    // declaration
};

class Expression : public AstNode {
public:
  Expression() = default;
  Expression(const Expression &) = default;
  Expression(Expression &&) = default;
  ~Expression() override = default;

  auto operator=(const Expression &) -> Expression & = default;
  auto operator=(Expression &&) -> Expression & = default;
};

class IntegerLiteral : public Expression {
public:
  IntegerLiteral() = delete;
  IntegerLiteral(const IntegerLiteral &) = default;
  IntegerLiteral(IntegerLiteral &&) = default;
  ~IntegerLiteral() override = default;

  auto operator=(const IntegerLiteral &) -> IntegerLiteral & = default;
  auto operator=(IntegerLiteral &&) -> IntegerLiteral & = default;

  explicit IntegerLiteral(int value) : value_(value) {}

  [[nodiscard]] auto value() const -> int { return value_; }

  void irgen() override;

private:
  int value_;
};

class Statement : public AstNode {
public:
  Statement() = default;
  Statement(const Statement &) = default;
  Statement(Statement &&) = default;
  ~Statement() override = default;

  auto operator=(const Statement &) -> Statement & = default;
  auto operator=(Statement &&) -> Statement & = default;
};

class ReturnStatement : public Statement {
public:
  ReturnStatement() = default;
  ReturnStatement(const ReturnStatement &) = delete;
  ReturnStatement(ReturnStatement &&) = default;
  auto operator=(const ReturnStatement &) -> ReturnStatement & = delete;
  auto operator=(ReturnStatement &&) -> ReturnStatement & = default;
  ~ReturnStatement() override = default;

  explicit ReturnStatement(std::unique_ptr<Expression> expr)
      : expr_(std::move(expr)) {}

  [[nodiscard]] auto expr() const -> const Expression & { return *expr_; }
  [[nodiscard]] auto expr() -> Expression & { return *expr_; }

  void irgen() override;

private:
  std::unique_ptr<Expression> expr_;
};

} // namespace cai
