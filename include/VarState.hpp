#pragma once

#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

class VarState {
 public:
  VarState();
  void setValue(const std::string& name, int value);
  int getValue(const std::string& name) const;
  void clear();
  void Indent();
  void Dedent();

 private:
  std::vector<std::unordered_map<std::string, int>> values_;
  int indentcnt_ = 0;
};
