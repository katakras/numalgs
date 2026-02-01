#pragma once

#include <numalgs/functions.hpp>

namespace root_finding {
double bisection(const std::shared_ptr<const functions::Function>& f, double a,
                 double b);
}  // namespace root_finding