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

namespace color_sequence {

// Setup must be run afetr retreving the color sequence from the user
// Should only be called once
void setup(const std::string& color_sequence);

// Outputs the color sequence submit order for the desired stage
// the modual color sequence is not needed thanks to setup
void print_stage_color_sequence(const int& stage);

} // namespace color_sequence

#endif // _color_sequence_H