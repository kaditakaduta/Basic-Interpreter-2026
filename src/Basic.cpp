#include <iostream>
#include <memory>
#include <string>

#include "Lexer.hpp"
#include "Parser.hpp"
#include "Program.hpp"
#include "Token.hpp"
#include "utils/Error.hpp"

void printHelp() {
  std::cout
      << "支持的命令:\n"
      << "  RUN - 开始执行程序\n"
      << "  LIST - 列出当前所有的程序行\n"
      << "  CLEAR - 清除当前所有的程序行\n"
      << "  QUIT - 退出解释器\n"
      << "  HELP - 打印帮助信息\n"
      << "\n程序指令:\n"
      << "  [行号] REM <注释> - 注释行\n"
      << "  [行号] LET <变量> = <表达式> - 赋值语句\n"
      << "  [行号] PRINT <表达式> - 打印表达式值\n"
      << "  [行号] INPUT <变量> - 输入变量值\n"
      << "  [行号] END - 结束程序\n"
      << "  [行号] GOTO <行号> - 跳转到指定行\n"
      << "  [行号] IF <表达式1> <操作符> <表达式2> THEN <行号> - 条件跳转\n"
      << "  [行号] INDENT - 进入新的作用域块\n"
      << "  [行号] DEDENT - 退出当前作用域块\n"
      << "\n立即执行指令 (不带行号):\n"
      << "  LET <变量> = <表达式>\n"
      << "  PRINT <表达式>\n"
      << "  INPUT <变量>\n"
      << "  INDENT\n"
      << "  DEDENT\n";
}

int main() {
  Lexer lexer;
  Parser parser;
  Program program;

  std::string line;
  while (std::getline(std::cin, line)) {
    if (line.empty()) {
      continue;
    }
    try {
      // TODO: The main function.
      auto tstream = lexer.tokenize(line);
      auto peek = tstream.peek();
      if (peek == nullptr) {
        throw BasicError("SYNTAX ERROR");
      } else if (peek->type == TokenType::RUN) {
        program.run();
      } else if (peek->type == TokenType::LIST) {
        program.list();
      } else if (peek->type == TokenType::CLEAR) {
        program.clear();
      } else if (peek->type == TokenType::HELP) {
        printHelp();
      } else if (peek->type == TokenType::QUIT) {
        return 0;
      } else if (peek->type == TokenType::NUMBER) {
        int s;
        try {
          s = std::stoi(peek->text);
        } catch (const std::exception& e) {
          throw BasicError("SYNTAX ERROR");
        }
        auto stmt = (parser.parseLine(tstream, line).getStatement());
        if (stmt != nullptr) {
          program.addStmt(s, stmt);
        } else {
          program.removeStmt(s);
        }
      } else if (peek->type == TokenType::UNKNOWN) {
        throw BasicError("SYNTAX ERROR");
      } else {
        auto stmt = (parser.parseLine(tstream, line).getStatement());
        if (stmt != nullptr) {
          program.execute(stmt);
        }
      }
    } catch (const BasicError& e) {
      std::cout << e.message() << "\n";
    }
  }
  return 0;
}