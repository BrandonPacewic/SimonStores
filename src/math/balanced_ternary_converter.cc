/*
 * Copyright (c) 2022 Brandon Pacewic
 *
 * Developed and tested by Brandon Pacewic
 *
 * balanced_ternary_converter.cc
 */

#include "balanced_ternary_converter.h"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

namespace ternary {
namespace {

std::vector<int16_t> initalize_values(const int16_t& value) {
    std::vector<int16_t> values;

    for (int16_t i = 0; pow(3, i) <= value; ++i) {
        values.push_back(pow(3, i));
    }

    std::reverse(values.begin(), values.end());

    return values;
}

std::vector<int16_t> make_ternary(const std::vector<int16_t>& values,
                                  int16_t value) {
    std::vector<int16_t> ternary(values.size(), 0);

    for (int i = 0; i < values.size(); ++i) {
        for (int step = 0; step < 2; ++step) {
            if (value >= values[i]) {
                ++ternary[i];
                value -= values[i];
            }
        }
    }

    return ternary;
}

std::vector<int16_t> convert_to_balanced(std::vector<int16_t>& ternary) {
    for (auto it = ternary.rbegin(); it != ternary.rend(); ++it) {
        if (*it == 3) {
            *it = 0;
            ++*(it + 1);
        } else if (*it == 2) {
            *it = -1;
            ++*(it + 1);
        }
    }

    return ternary;
}

std::string convert_to_symbols(const std::vector<int16_t>& balanced_ternary,
                               const bool& invert_signs) {
    std::string symbols(balanced_ternary.size(), '0');

    for (std::size_t i = 0; i < balanced_ternary.size(); ++i) {
        if (balanced_ternary[i] == 1) {
            symbols[i] = (invert_signs) ? '-' : '+';
        } else if (balanced_ternary[i] == -1) {
            symbols[i] = (invert_signs) ? '+' : '-';
        }
    }

    return symbols;
}

constexpr int16_t max_expected_value = 364;
std::unordered_map<int, std::vector<int16_t>> value_to_values_map;

}  // namespace

std::string balanced_convert(int16_t value) {
    bool invert_signs = false;

    if (value < 0) {
        invert_signs = true;
        value = abs(value);
    }

    if (!value_to_values_map.count(max_expected_value)) {
        value_to_values_map[max_expected_value] =
            initalize_values(max_expected_value);
    }

    auto ternary = make_ternary(
        value_to_values_map.find(max_expected_value)->second, value);

    ternary = convert_to_balanced(ternary);
    std::string symbols = convert_to_symbols(ternary, invert_signs);

    return symbols;
}

}  // namespace ternary