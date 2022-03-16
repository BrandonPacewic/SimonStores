/*
 * Copyright (c) 2022 Brandon Pacewic
 *
 * Developed and tested by Brandon Pacewic
 * 
 * stage_one.h
 */

#pragma once
#ifndef _STAGE_ONE_H
#define _STAGE_ONE_H 1

#include <string>
#include <vector>

namespace stages {

    int one_calculations(const std::string& flash, 
        const std::vector<int>& alpha, const int& step, const int& delta);

} // namespace stages

#endif // _STAGE_ONE_H