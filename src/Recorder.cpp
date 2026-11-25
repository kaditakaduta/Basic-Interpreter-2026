#include "Recorder.hpp"

#include <iostream>

void Recorder::add(int line, std::shared_ptr<Statement> stmt) {
  record_[line] = stmt;
}

void Recorder::remove(int line) {
  if (record_.find(line) != record_.end()) {
    record_.erase(line);
  }
}

const std::shared_ptr<Statement> Recorder::get(int line) const noexcept {
  auto it = record_.find(line);
  if (it != record_.end()) {
    return (*it).second;
  }
  return nullptr;
}

bool Recorder::hasLine(int line) const noexcept {
  return record_.find(line) != record_.end();
}

void Recorder::clear() noexcept { record_.clear(); }

void Recorder::printLines() const {
  for (auto rec : record_) {
    // if (rec.second != nullptr) {
    std::cout << rec.second->text() << std::endl;
    //}
  }
}

int Recorder::nextLine(int line) const noexcept {
  if (record_.empty() || (*record_.crbegin()).first <= line) {
    return -1;
  }  // cannot find: either no statement or at the end.

  /*auto it = record_.find(line);
  if (it != record_.end()) {  // if this "line" exists, skip to the next line in
                              // the list.
    ++it;
    if (it != record_.end()) {
      return (*it).first;
    }
    return -1;  // actually cannot reach!
  }*/

  ++line;  // if this line does not exist, try to find the following line.
  while (record_.find(line) == record_.end()) {
    ++line;
  }
  return line;
}
