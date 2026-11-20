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
      if (tstream.peek()->type == TokenType::RUN) {
        program.run();
      } else if (tstream.peek()->type == TokenType::LIST) {
        program.list();
      } else if (tstream.peek()->type == TokenType::CLEAR) {
        program.clear();
      } else if (tstream.peek()->type == TokenType::HELP) {
        std::cout << "Welcome to Basic Interpreter!" << std::endl;
      } else if (tstream.peek()->type == TokenType::QUIT) {
        return 0;
      } else if (tstream.peek()->type == TokenType::NUMBER) {
        auto s = tstream.peek()->text;
        program.addStmt(std::stoi(s),
                        parser.parseLine(tstream, line).getStatement());
      } else if (tstream.peek()->type == TokenType::UNKNOWN) {
        throw("SYNTAX ERROR");
      } else {
        program.execute(parser.parseLine(tstream, line).getStatement());
      }
    } catch (const BasicError& e) {
      std::cout << e.message() << "\n";
    }
  }
  return 0;
}