/*
 * Copyright (c) 2022 Brandon Pacewic
 *
 * Developed and tested by Brandon Pacewic
 * 
 * color_determine.h
 */

#pragma once
#ifndef _COLOR_DETERMINE_H
#define _COLOR_DETERMINE_H 1

#include <string>

namespace color_determine {

int primary_secondary_mix(const std::string& flash);
char missing_color(const std::string& flash);
bool is_primary(const char& color);
bool is_secondary(const char& color);

} // namespace color_determine

#endif // _COLOR_DETERMINE_H