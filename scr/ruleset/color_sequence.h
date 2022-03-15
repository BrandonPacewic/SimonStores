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

// Setup must be run afetr retreving the color sequence from the user
// Should only be called once
void setup(const std::string& color_sequence);

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