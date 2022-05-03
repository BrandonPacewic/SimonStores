/*
 * Copyright (c) 2022 Brandon Pacewic
 *
 * Developed and tested by Brandon Pacewic
 *
 * stage_one.h
 */

#pragma once
#ifndef SIMON_STORES_STAGES_STAGE_ONE_H_
#define SIMON_STORES_STAGES_STAGE_ONE_H_

#include <string>
#include <vector>

#include "../math/mod_type.h"
using mod_types::mod_type;

namespace stages {

int16_t one_calculations(const std::string& flash,
                         const std::vector<mod_type<int16_t>>& alpha,
                         const uint16_t& step, const int16_t& delta);

}  // namespace stages

#endif  // SIMON_STORES_STAGES_STAGE_ONE_H_