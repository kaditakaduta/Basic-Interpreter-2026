#pragma once

#include <memory>
#include <string>

#include "Expression.hpp"

class Program;
class VarState;

class Statement {
 public:
  explicit Statement(std::string source);
  virtual ~Statement() = default;

  virtual void execute(VarState& state, Program& program) const = 0;

  const std::string& text() const noexcept;

 private:
  std::string source_;
};

// TODO: Other statement types derived from Statement, e.g., GOTOStatement,
// LetStatement, etc.

class LetStatement : public Statement {
 public:
  explicit LetStatement(std::string source, std::string name,
                        std::shared_ptr<Expression> expr);
  void execute(VarState& state, Program& program) const final;

 private:
  std::string name_;
  std::shared_ptr<Expression> expr_;
};

class PrintStatement : public Statement {
 public:
  explicit PrintStatement(std::string source, std::shared_ptr<Expression> expr);
  void execute(VarState& state, Program& program) const final;

 private:
  std::shared_ptr<Expression> expr_;
};

class InputStatement : public Statement {
 public:
  explicit InputStatement(std::string source, std::string name);
  void execute(VarState& state, Program& program) const final;

 private:
  std::string name_;
};

class GotoStatement : public Statement {
 public:
  explicit GotoStatement(std::string source, int line);
  void execute(VarState& state, Program& program) const final;

 private:
  int line_;
};

class IfStatement : public Statement {
 public:
  explicit IfStatement(std::string source,
                       std::shared_ptr<CompareExpression> expL, int line);
  void execute(VarState& state, Program& program) const final;

 private:
  std::shared_ptr<CompareExpression> exp_;
  int line_;
};

class RemStatement : public Statement {
 public:
  explicit RemStatement(std::string source);
  void execute(VarState& state, Program& program) const final;
};

class EndStatement : public Statement {
 public:
  explicit EndStatement(std::string source);
  void execute(VarState& state, Program& program) const final;
};

class IndentStatement : public Statement {
 public:
  explicit IndentStatement(std::string source);
  void execute(VarState& state, Program& program) const final;
};

class DedentStatement : public Statement {
 public:
  explicit DedentStatement(std::string source);
  void execute(VarState& state, Program& program) const final;
};