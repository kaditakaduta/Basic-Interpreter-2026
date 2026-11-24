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
  std::string val;
  bool flag = false;
  while (true) {
    std::cout << " ? ";
    std::getline(std::cin, val);
    flag = true;
    for (auto& c : val) {
      if (!isdigit(c) && c != '-') {
        std::cout << "INVALID NUMBER" << std::endl;
        flag = false;
        break;
      }
    }
    if (flag) {
      break;
    }
  }
  state.setValue(name_, std::stoi(val));
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
