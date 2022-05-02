/*
 * Copyright (c) 2022 Brandon Pacewic
 *
 * Developed and tested by Brandon Pacewic
 *
 * stage_three.h
 */

#pragma once
#ifndef _STAGE_THREE_H
#define _STAGE_THREE_H 1

#include <string>
#include <vector>

#include "../math/mod_type.h"
using mod_types::mod_type;

namespace stages {

int three_calculations(const std::string& flash,
                       const std::vector<mod_type<int>>& alpha,
                       const std::vector<mod_type<int>>& bravo,
                       const std::vector<mod_type<int>>& charlie,
                       const int& step, const int& delta);

}  // namespace stages

#endif  // _STAGE_THREE_H