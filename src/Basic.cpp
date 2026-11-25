#include <iostream>
#include <memory>
#include <string>

#include "Lexer.hpp"
#include "Parser.hpp"
#include "Program.hpp"
#include "Token.hpp"
#include "utils/Error.hpp"

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
        throw "ERROR";
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