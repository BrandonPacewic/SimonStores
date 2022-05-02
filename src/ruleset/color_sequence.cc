/*
 * Copyright (c) 2022 Brandon Pacewic
 *
 * Developed and tested by Brandon Pacewic
 *
 * color_sequence.cc
 */

#include "color_sequence.h"

#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>

#include "color_determine.h"

using color_determine::is_primary;
using color_determine::is_secondary;

namespace color_sequence {
namespace {

constexpr uint16_t expected_color_sequence_length = 6;
constexpr uint16_t right_cutoff = expected_color_sequence_length / 3;

const std::unordered_map<char, char> color_to_complementary_map = {
    {'r', 'c'}, {'c', 'r'}, {'g', 'm'}, {'m', 'g'}, {'b', 'y'}, {'y', 'b'}};

const std::unordered_map<char, char> primary_cycle_map = {
    {'r', 'g'}, {'g', 'b'}, {'b', 'r'}};

const std::unordered_map<char, char> secondary_cycle_map = {
    {'c', 'm'}, {'m', 'y'}, {'y', 'c'}};

std::unordered_map<char, uint16_t> create_color_placement_map(
    const std::string& color_sequence) {
    std::unordered_map<char, uint16_t> color_placement_map;

    for (uint16_t i = 0; i < expected_color_sequence_length; ++i) {
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
    std::for_each(
        base_color_sequence.begin(), base_color_sequence.end(),
        [&](char& ch) { ch = color_to_complementary_map.find(ch)->second; });

    return base_color_sequence;
}

std::string cycle_primary(std::string& base_color_sequence) {
    std::for_each(base_color_sequence.begin(), base_color_sequence.end(),
                  [](char& ch) {
                      if (is_primary(ch)) {
                          ch = primary_cycle_map.find(ch)->second;
                      }
                  });

    return base_color_sequence;
}

std::string cycle_secondary(std::string& base_color_sequence) {
    std::for_each(base_color_sequence.begin(), base_color_sequence.end(),
                  [](char& ch) {
                      if (is_secondary(ch)) {
                          ch = secondary_cycle_map.find(ch)->second;
                      }
                  });

    return base_color_sequence;
}

std::string swap_blue_with_opposite(std::string& base_color_sequence) {
    for (uint16_t i = 0; i < expected_color_sequence_length; ++i) {
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
    std::for_each(base_color_sequence.begin(), base_color_sequence.end(),
                  [](char& ch) {
                      if (ch == 'y') {
                          ch = 'r';
                      } else if (ch == 'r') {
                          ch = 'y';
                      }
                  });

    return base_color_sequence;
}

std::string swap_green_cyan(std::string& base_color_sequence) {
    std::for_each(base_color_sequence.begin(), base_color_sequence.end(),
                  [](char& ch) {
                      if (ch == 'g') {
                          ch = 'c';
                      } else if (ch == 'c') {
                          ch = 'g';
                      }
                  });

    return base_color_sequence;
}

const std::string get_base_color_sequence(const uint16_t& stage) {
    assert(stage >= 1 && stage <= 3);

    const std::array<std::string, 3> base_color_sequences = {"rgbcmy", "ybgmcr",
                                                             "bmrygc"};

    return base_color_sequences[stage - 1];
}

std::unordered_map<char, uint16_t> color_placement_map;

}  // namespace

void setup(const std::string& color_sequence) {
    color_placement_map = create_color_placement_map(color_sequence);
}

std::string determine_stage_color_sequence(const uint16_t& stage) {
    auto base_color_sequence = get_base_color_sequence(stage);
    const auto& yellow_placement = color_placement_map.find('y')->second;
    const uint16_t required_yellow_placement = 0;

    if (yellow_placement == required_yellow_placement) {
        base_color_sequence = shift_right(base_color_sequence);
    }

    const auto& red_placement = color_placement_map.find('r')->second;
    const auto& cyan_placement = color_placement_map.find('c')->second;

    // Red and cyan opposite
    if (red_placement + expected_color_sequence_length == cyan_placement ||
        cyan_placement + expected_color_sequence_length == red_placement) {
        base_color_sequence = swap_complementary(base_color_sequence);
    }

    const auto& green_placement = color_placement_map.find('g')->second;
    const std::array<uint16_t, 2> required_green_placements = {0, 5};

    if (std::find_if(required_green_placements.begin(),
                     required_green_placements.end(), [&](uint16_t placement) {
                         return green_placement == placement;
                     }) != required_green_placements.end()) {
        base_color_sequence = cycle_primary(base_color_sequence);
    }

    const auto& magenta_placement = color_placement_map.find('m')->second;
    const std::array<uint16_t, 2> required_magenta_placements = {2, 3};

    if (std::find_if(required_magenta_placements.begin(),
                     required_magenta_placements.end(),
                     [&](uint16_t placement) {
                         return magenta_placement == placement;
                     }) != required_magenta_placements.end()) {
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

    return base_color_sequence;
}

}  // namespace color_sequence