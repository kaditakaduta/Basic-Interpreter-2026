#include "Program.hpp"

#include "utils/Error.hpp"

void Program::addStmt(int line, std::shared_ptr<Statement> stmt) {
  if (line <= 0) {
    throw BasicError("LINE NUMBER ERROR");  // 只允许正整数行号
  }
  recorder_.add(line, stmt);
}

void Program::removeStmt(int line) {
  if (line <= 0) {
    throw BasicError("LINE NUMBER ERROR");  // 只允许正整数行号
  }
  recorder_.remove(line);
}

void Program::run() {
  programEnd_ = false;
  vars_.resetScopes();
  programCounter_ = recorder_.nextLine(0);
  while (programCounter_ != -1) {
    if (programEnd_) {
      break;
    }
    pcChanged_ = false;
    execute(recorder_.get(programCounter_));
    if (!pcChanged_) {  // if "execute" didn't call changePC
      programCounter_ = recorder_.nextLine(programCounter_);
    }
  }
  programEnd();
}

void Program::list() const { recorder_.printLines(); }

void Program::clear() {
  recorder_.clear();
  vars_.clear();
}

void Program::execute(std::shared_ptr<Statement> stmt) {
  if (stmt) {  // safe check, CRITICAL!!
    stmt->execute(vars_, (*this));
  }
}

int Program::getPC() const noexcept { return programCounter_; }

void Program::changePC(int line) {
  if (recorder_.hasLine(line)) {
    pcChanged_ = true;
    programCounter_ = line;
  } else {
    throw BasicError("LINE NUMBER ERROR");
  }
}

void Program::programEnd() { programEnd_ = true; }

void Program::resetAfterRun() noexcept {}
