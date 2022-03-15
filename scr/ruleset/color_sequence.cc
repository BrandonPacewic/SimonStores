/*
 * Copyright (c) 2022 Brandon Pacewic
 *
 * Developed and tested by Brandon Pacewic
 * 
 * color_sequence.cc
 */

#ifndef _COLOR_SEQUENCE_C
#define _COLOR_SEQUENCE_C 1

#include <algorithm>
#include <string>
#include <unordered_map>

namespace color_sequence {

namespace {

// TODO: Could use class enumerations
const bool is_primary(const char& ch) {
    const std::string primarys = "rbg";
    return primarys.find(ch) != std::string::npos; 
}

const bool is_secondary(const char& ch) {
    const std::string secondarys = "cmy";
    return secondarys.find(ch) != std::string::npos;
}

const std::unordered_map<char, char> color_to_complementary_map = {
    {'r', 'c'}, {'c', 'r'},
    {'g', 'm'}, {'m', 'g'},
    {'b', 'y'}, {'y', 'b'}
};

const std::unordered_map<char, char> primary_cycle_map = {
    {'r', 'g'}, {'g', 'b'}, {'b', 'r'}
};

void shift_right(const std::unordered_map<char, int>& color_placment_map,
                                            std::string& base_color_sequence) {
    constexpr int required_placement = 0;

    if (color_placment_map.find('y')->second == required_placement) {
        std::next_permutation(base_color_sequence.begin(), 
            base_color_sequence.end());
    }
}

void swap_complementary(const std::unordered_map<char, int>& color_placment_map,
                                            std::string& base_color_sequence) {
    const int opposite_adjustment = int(base_color_sequence.length() / 2);
    const auto& red_placement = color_placment_map.find('r')->second;
    const auto& cyan_placement = color_placment_map.find('c')->second;

    if (red_placement + opposite_adjustment == cyan_placement ||
        cyan_placement + opposite_adjustment == red_placement) {
        for (auto& ch : base_color_sequence) {
            ch = color_to_complementary_map.find(ch)->second;
        }
    }
}


} // namespace

} // namespace color_sequence

#endif // _COLOR_SEQUENCE_C