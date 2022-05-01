/*
 * Copyright (c) 2022 Brandon Pacewic
 *
 * Developed and tested by Brandon Pacewic
 * 
 * color_determine.h
 */

#pragma once
#ifndef SIMON_STORES_RULESET_COLOR_DETERMINE_H
#define SIMON_STORES_RULESET_COLOR_DETERMINE_H

#include <string>

namespace color_determine {

int primary_secondary_mix(const std::string& flash);
char missing_color(const std::string& flash);
const bool is_primary(const char& color);
const bool is_secondary(const char& color);

} // namespace color_determine

#endif // SIMON_STORES_RULESET_COLOR_DETERMINE_H