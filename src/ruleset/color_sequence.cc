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

#include "color_determine.h"
using color_determine::is_primary;
using color_determine::is_secondary;

#include "color_sequence.h"

namespace color_sequence {

namespace {

constexpr int expected_color_sequence_length = 6;
constexpr int right_cutoff = 2;

const std::unordered_map<char, char> color_to_complementary_map = {
    {'r', 'c'}, {'c', 'r'}, {'g', 'm'}, {'m', 'g'}, {'b', 'y'}, {'y', 'b'}};

const std::unordered_map<char, char> primary_cycle_map = {
    {'r', 'g'}, {'g', 'b'}, {'b', 'r'}};

const std::unordered_map<char, char> secondary_cycle_map = {
    {'c', 'm'}, {'m', 'y'}, {'y', 'c'}};

std::unordered_map<char, int> create_color_placement_map(
    const std::string& color_sequence) {
    std::unordered_map<char, int> color_placement_map;

    for (int i = 0; i < expected_color_sequence_length; ++i) {
        color_placement_map[color_sequence[i]] = i;
    }

    return color_placement_map;
}

std::string shift_right(std::string& base_color_sequence) {
    std::next_permutation(base_color_sequence.begin(),
                          base_color_sequence.end());

    return base_color_sequence;
}

std::string swap_complementary(std::string& base_color_sequence) {
    for (auto& ch : base_color_sequence) {
        ch = color_to_complementary_map.find(ch)->second;
    }

    return base_color_sequence;
}

std::string cycle_primary(std::string& base_color_sequence) {
    for (auto& ch : base_color_sequence) {
        if (is_primary(ch)) {
            ch = primary_cycle_map.find(ch)->second;
        }
    }

    return base_color_sequence;
}

std::string cycle_secondary(std::string& base_color_sequence) {
    for (auto& ch : base_color_sequence) {
        if (is_secondary(ch)) {
            ch = secondary_cycle_map.find(ch)->second;
        }
    }

    return base_color_sequence;
}

std::string swap_blue_with_opposite(std::string& base_color_sequence) {
    for (int i = 0; i < int(base_color_sequence.length()); ++i) {
        if (base_color_sequence[i] == 'b') {
            const int opposite = (i > right_cutoff) ? i - 3 : i + 3;
            base_color_sequence[i] = base_color_sequence[opposite];
            base_color_sequence[opposite] = 'b';
            break;
        }
    }

    return base_color_sequence;
}

std::string swap_red_yellow(std::string& base_color_sequence) {
    for (auto& ch : base_color_sequence) {
        if (ch == 'y') {
            ch = 'r';
        } else if (ch == 'r') {
            ch = 'y';
        }
    }

    return base_color_sequence;
}

std::string swap_green_cyan(std::string& base_color_sequence) {
    for (auto& ch : base_color_sequence) {
        if (ch == 'g') {
            ch = 'c';
        } else if (ch == 'c') {
            ch = 'g';
        }
    }

    return base_color_sequence;
}

const std::string get_base_color_sequence(const int& stage) {
    assert(stage >= 1 && stage <= 3);

    const std::array<std::string, 3> base_color_sequences = {"rgbcmy", "ybgmcr",
                                                             "bmrygc"};

    return base_color_sequences[stage - 1];
}

std::unordered_map<char, int> color_placement_map;

}  // namespace

void setup(const std::string& color_sequence) {
    color_placement_map = create_color_placement_map(color_sequence);
}

void print_stage_color_sequence(const int& stage) {
    auto base_color_sequence = get_base_color_sequence(stage);
    const auto& yellow_placement = color_placement_map.find('y')->second;

    // Yellow in position 0
    if (yellow_placement == 0) {
        base_color_sequence = shift_right(base_color_sequence);
    }

    const auto& red_placement = color_placement_map.find('r')->second;
    const auto& cyan_placement = color_placement_map.find('c')->second;

    // Red and cyan opposite
    if (red_placement + int(base_color_sequence.length()) == cyan_placement ||
        cyan_placement + int(base_color_sequence.length()) == red_placement) {
        base_color_sequence = swap_complementary(base_color_sequence);
    }

    const auto& green_placement = color_placement_map.find('g')->second;

    // Green in first or last position
    if (green_placement == 0 || green_placement == 5) {
        base_color_sequence = cycle_primary(base_color_sequence);
    }

    const auto& magenta_placement = color_placement_map.find('m')->second;

    // Magenta in 2nd or 3rd
    if (magenta_placement == 2 || magenta_placement == 3) {
        base_color_sequence = cycle_secondary(base_color_sequence);
    }

    const auto& blue_placement = color_placement_map.find('b')->second;
    const bool blue_on_right = blue_placement <= right_cutoff;

    const bool yellow_on_right = yellow_placement <= right_cutoff;

    // Blue or yellow on right but not both
    if (blue_on_right != yellow_on_right) {
        base_color_sequence = swap_blue_with_opposite(base_color_sequence);
    }

    // Red on right
    if (red_placement <= right_cutoff) {
        base_color_sequence = swap_red_yellow(base_color_sequence);
    }

    // Blue on left
    if (blue_placement > right_cutoff) {
        base_color_sequence = swap_green_cyan(base_color_sequence);
    }

    std::cout << base_color_sequence << '\n';
}

}  // namespace color_sequence

#endif  // _COLOR_SEQUENCE_C