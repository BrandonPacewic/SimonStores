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
#include <string>
#include <unordered_map>
#include <vector>

namespace ternary {
namespace {

std::vector<int> initalize_values(const int& value) {
    std::vector<int> values;

    for (int i = 0; pow(3, i) <= value; ++i) {
        values.push_back(pow(3, i));
    }

    std::reverse(values.begin(), values.end());

    return values;
}

std::vector<int> make_ternary(const std::vector<int>& values, int value) {
    std::vector<int> ternary(values.size(), 0);

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

std::vector<int> convert_to_balanced(std::vector<int>& ternary) {
    for (int i = ternary.size() - 1; i >= 0; --i) {
        if (ternary[i] == 3) {
            ternary[i] = 0;
            ++ternary[i - 1];
        } else if (ternary[i] == 2) {
            ternary[i] = -1;
            ++ternary[i - 1];
        }
    }

    return ternary;
}

std::string convert_to_symbols(const std::vector<int>& balanced_ternary,
                               const bool& invert_signs) {
    std::string symbols(balanced_ternary.size(), '0');

    for (int i = 0; i < int(balanced_ternary.size()); ++i) {
        if (balanced_ternary[i] == 1) {
            symbols[i] = (invert_signs) ? '-' : '+';
        } else if (balanced_ternary[i] == -1) {
            symbols[i] = (invert_signs) ? '+' : '-';
        }
    }

    return symbols;
}

constexpr int max_expected_value = 364;
std::unordered_map<int, std::vector<int>> value_to_values_map;

}  // namespace

std::string balanced_convert(int value) {
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
    auto symbols = convert_to_symbols(ternary, invert_signs);

    return symbols;
}

}  // namespace ternary