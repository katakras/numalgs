#pragma once

#include <optional>

enum ResultStatus { success, error, not_converged };

template <typename TResult>
class Result {
 public:
  Result(std::optional<TResult> value, const ResultStatus status);

  const auto& value() const { return value_; }
  const auto& status() const { return status_; }

 private:
  std::optional<TResult> value_;
  ResultStatus status_;
};