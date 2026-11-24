#include "Statement.hpp"

#include <iostream>
#include <limits>
#include <sstream>
#include <utility>

#include "Program.hpp"
#include "VarState.hpp"
#include "utils/Error.hpp"

Statement::Statement(std::string source) : source_(std::move(source)) {}

const std::string& Statement::text() const noexcept { return source_; }

// TODO: Imply interfaces declared in the Statement.hpp.

LetStatement::LetStatement(std::string source, std::string name,
                           std::shared_ptr<Expression> expr)
    : Statement(source), name_(name), expr_(expr) {}

void LetStatement::execute(VarState& state, Program& program) const {
  state.setValue(name_, expr_->evaluate(state));
}

PrintStatement::PrintStatement(std::string source,
                               std::shared_ptr<Expression> expr)
    : Statement(source), expr_(expr) {}

void PrintStatement::execute(VarState& state, Program& program) const {
  std::cout << expr_->evaluate(state) << std::endl;
}

InputStatement::InputStatement(std::string source, std::string name)
    : Statement(source), name_(name) {}

void InputStatement::execute(VarState& state, Program& program) const {
  std::string vals;
  bool flag = false;
  while (true) {
    std::cout << " ? ";
    if (!std::getline(std::cin, vals)) break;
    flag = true;
    for (auto& c : vals) {
      if (!isdigit(c) && c != '-' && !isblank(c)) {
        std::cout << "INVALID NUMBER" << std::endl;
        flag = false;
        break;
      }
    }
    if (flag) {
      int val;
      try {
        val = std::stoi(vals);
      } catch (const std::exception& e) {
        std::cout << "INVALID NUMBER" << std::endl;
        continue;
      }
      state.setValue(name_, val);
      return;
    }
  }
}

GotoStatement::GotoStatement(std::string source, int line) : Statement(source) {
  line_ = line;
}

void GotoStatement::execute(VarState& state, Program& program) const {
  program.changePC(line_);
}

IfStatement::IfStatement(std::string source,
                         std::shared_ptr<CompareExpression> exp, int line)
    : Statement(source), exp_(exp), line_(line) {}

void IfStatement::execute(VarState& state, Program& program) const {
  if (exp_->evaluate(state)) {
    program.changePC(line_);
  }
};

RemStatement::RemStatement(std::string source) : Statement(source) {}

void RemStatement::execute(VarState& state, Program& program) const {}

EndStatement::EndStatement(std::string source) : Statement(source) {}

void EndStatement::execute(VarState& state, Program& program) const {
  program.programEnd();
}

IndentStatement::IndentStatement(std::string source) : Statement(source) {}

void IndentStatement::execute(VarState& state, Program& program) const {
  state.Indent();
}

DedentStatement::DedentStatement(std::string source) : Statement(source) {}

void DedentStatement::execute(VarState& state, Program& program) const {
  state.Dedent();
}
