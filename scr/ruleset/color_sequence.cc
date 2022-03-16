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
#include <array>
#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>

#include "color_sequence.h"

namespace color_sequence {

namespace {

constexpr int expected_color_sequence_length = 6;
constexpr int right_cutoff = 2;

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

const std::unordered_map<char, char> secondary_cycle_map = {
    {'c', 'm'}, {'m', 'y'}, {'y', 'c'}
};

std::unordered_map<char, int> create_color_placement_map(
    const std::string& color_sequence) {
    std::unordered_map<char, int> color_placement_map;

    for (int i = 0; i < expected_color_sequence_length; ++i) {
        color_placement_map[color_sequence[i]] = i;
    }

    return color_placement_map;
}

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
    const int opposite_adjustment = int(base_color_sequence.length()) / 2;
    const auto& red_placement = color_placment_map.find('r')->second;
    const auto& cyan_placement = color_placment_map.find('c')->second;

    if (red_placement + opposite_adjustment == cyan_placement ||
        cyan_placement + opposite_adjustment == red_placement) {
        for (auto& ch : base_color_sequence) {
            ch = color_to_complementary_map.find(ch)->second;
        }
    }
}

void cycle_primary(const std::unordered_map<char, int>& color_placment_map,
    std::string& base_color_sequence) {
    const auto& green_placement = color_placment_map.find('g')->second;
    const std::array<int, 2> required_placements = {0, 5};
    
    if (green_placement == required_placements[0] || 
        green_placement == required_placements[1]) {
        for (auto& ch : base_color_sequence) {
            if (is_primary(ch)) {
                ch = primary_cycle_map.find(ch)->second;
            }
        }
    }
}

void cycle_secondary(const std::unordered_map<char, int>& color_placment_map,
    std::string& base_color_sequence) {
    const auto& magenta_placement = color_placment_map.find('m')->second;

    if (magenta_placement == 2 || magenta_placement == 3) {
        for (auto& ch : base_color_sequence) {
            if (is_secondary(ch)) {
                ch = secondary_cycle_map.find(ch)->second;
            }
        }
    }
}

void swap_blue_with_opposite(
    const std::unordered_map<char, int>& color_placment_map, 
    std::string& base_color_sequence) {
    const auto& blue_placement = color_placment_map.find('b')->second;
    const bool blue_on_right = blue_placement <= right_cutoff;
    
    const auto& yellow_placement = color_placment_map.find('y')->second;
    const bool yellow_on_right = yellow_placement <= right_cutoff;

    if (blue_on_right != yellow_on_right) {
        for (int i = 0; i < int(base_color_sequence.length()); ++i) {
            if (base_color_sequence[i] == 'b') {
                const int opposite = (i > right_cutoff) ? i - 3 : i + 3;
                base_color_sequence[i] = base_color_sequence[opposite];
                base_color_sequence[opposite] = 'b';
                break;
            }
        }
    }
}

void swap_red_yellow(const std::unordered_map<char, int>& color_placment_map,
    std::string& base_color_sequence) {
    const auto& red_placement = color_placment_map.find('r')->second;

    if (red_placement <= right_cutoff) {
        for (auto& ch : base_color_sequence) {
            if (ch == 'y') {
                ch = 'r';
            }
            else if (ch == 'r') {
                ch = 'y';
            }
        }
    }
}

void swap_green_cyan(const std::unordered_map<char, int>& color_placment_map,
    std::string& base_color_sequence) {
    const auto& blue_placement = color_placment_map.find('b')->second;

    if (blue_placement > right_cutoff) {
        for (auto& ch : base_color_sequence) {
            if (ch == 'g') {
                ch = 'c';
            }
            else if (ch == 'c') {
                ch = 'g';
            }
        }
    }
}

const std::string get_base_color_sequence(const int& stage) {
    assert(stage >= 1 && stage <= 3);
    
    const std::array<std::string, 3> base_color_sequences = {
        "rgbcmy", "ybgmcr", "bmrygc"
    };

    return base_color_sequences[stage - 1];
}

std::unordered_map<char, int> color_placement_map;

} // namespace

void setup(const std::string& color_sequence) {
    color_placement_map = create_color_placement_map(color_sequence);
}

void print_stage_color_sequence(const int& stage) {
    auto base_color_sequence = get_base_color_sequence(stage);
    shift_right(color_placement_map, base_color_sequence);
    swap_complementary(color_placement_map, base_color_sequence);
    cycle_primary(color_placement_map, base_color_sequence);
    cycle_secondary(color_placement_map, base_color_sequence);
    swap_blue_with_opposite(color_placement_map, base_color_sequence);
    swap_red_yellow(color_placement_map, base_color_sequence);
    swap_green_cyan(color_placement_map, base_color_sequence);

    std::cout << base_color_sequence << '\n';
}

} // namespace color_sequence

#endif // _COLOR_SEQUENCE_C