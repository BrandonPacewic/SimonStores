/*
 * Copyright (c) 2022 Brandon Pacewic
 *
 * Developed and tested by Brandon Pacewic
 * 
 * color_sequence.h
 */

#pragma once
#ifndef SIMON_STORES_RULESET_COLOR_SEQUENCE_H
#define SIMON_STORES_RULESET_COLOR_SEQUENCE_H

#include <string>

namespace color_sequence {

// Setup must be run afetr retreving the color sequence from the user
// Should only be called once
void setup(const std::string& color_sequence);

std::string determine_stage_color_sequence(const uint16_t& stage);

} // namespace color_sequence

#endif // SIMON_STORES_RULESET_COLOR_SEQUENCE_H