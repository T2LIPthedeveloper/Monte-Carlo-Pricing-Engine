// option.cpp - Option Pricing Implementation
#include "option.h"
#include <algorithm>

double callPayoff(double S, double K) {
    return std::max(S - K, 0.0);
}

double putPayoff(double S, double K) {
    return std::max(K - S, 0.0);
}