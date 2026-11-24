#include "VarState.hpp"

#include <algorithm>

#include "utils/Error.hpp"

VarState::VarState() {
  values_.push_back(std::unordered_map<std::string, int>());
}

void VarState::setValue(const std::string& name, int value) {
  (*values_.rbegin())[name] = value;
}

int VarState::getValue(const std::string& name) const {
  for (int i = values_.size() - 1; i >= 0; --i) {
    auto it = values_[i].find(name);
    if (it != values_[i].end()) {
      return it->second;
    }
  }
  throw BasicError("VARIABLE NOT DEFINED");
}

void VarState::clear() { values_ = {std::unordered_map<std::string, int>()}; }

void VarState::Indent() {
  values_.push_back(std::unordered_map<std::string, int>());
}

void VarState::Dedent() {
  if (values_.size() == 1) {
    throw BasicError("SCOPE UNDERFLOW");
  }
  values_.pop_back();
}
