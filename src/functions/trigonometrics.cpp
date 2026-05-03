#include <cmath>

#include <numalgs/functions.hpp>

namespace functions {

double Sin::operator()(const double x) const { return std::sin(x); }

double Cos::operator()(const double x) const { return std::cos(x); }

double Tan::operator()(const double x) const { return std::tan(x); }

}  // namespace functions
