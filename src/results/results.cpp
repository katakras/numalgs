#include <numalgs/results.hpp>

template <typename TResult>
Result<TResult>::Result(std::optional<TResult> value, ResultStatus status)
    : value_(std::move(value)), status_(status) {}

template class Result<double>;