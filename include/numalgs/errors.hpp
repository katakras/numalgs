#pragma once

#include <stdexcept>
#include <string>

struct NumalgsError : public std::runtime_error {
  explicit NumalgsError(const std::string& msg) : std::runtime_error(msg) {}
};

#define THROW(msg) throw NumalgsError(msg)