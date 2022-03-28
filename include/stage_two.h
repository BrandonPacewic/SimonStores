/*
 * Copyright (c) 2022 Brandon Pacewic
 *
 * Developed and tested by Brandon Pacewic
 * 
 * stage_two.h
 */

#pragma once
#ifndef _STAGE_TWO_H
#define _STAGE_TWO_H 1

#include <string>
#include <vector>

#include "mod_type.h"
using mod_types::mod_type;

namespace stages {

    int two_calculations(const std::string& flash, 
        const std::vector<mod_type<int>>& alpha, 
        const std::vector<mod_type<int>>& bravo,
        const int& step, const int& delta);

} // namespace stages

#endif // _STAGE_TWO_H
