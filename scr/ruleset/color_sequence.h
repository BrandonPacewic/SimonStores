/*
 * Copyright (c) 2022 Brandon Pacewic
 *
 * Developed and tested by Brandon Pacewic
 * 
 * color_sequence.h
 */

#pragma once
#ifndef _color_sequence_H
#define _color_sequence_H 1

#include <string>
#include <unordered_map>

namespace color_sequence {

// Maps the color order on the modual to the placement of each color
// this map is only generated once
std::unordered_map<char, int> create_color_to_placment_map(
    const std:: string& color_order);

// Stores the starting color sequence that gets modified at the end of each
// stage calculation
const std::string get_base_colors(const int& stage);

// Reorders the base color sequence for each stage
std::string get_color_submitting_order(const std::string& color_order, 
    std::string& base_color_sequence);

void print_stage_color_sequence(const int& stage, 
    const std::string& color_order);

} // namespace color_sequence

#endif // _color_sequence_H