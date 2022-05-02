/*
 * Copyright (c) 2022 Brandon Pacewic
 *
 * Developed and tested by Brandon Pacewic
 * 
 * inital_calculations.h
 */

#pragma once
#ifndef SIMON_STORES_RULESET_INITAL_CALCULATIONS_H
#define SIMON_STORES_RULESET_INITAL_CALCULATIONS_H

#include "../math/base_36_type.h"

namespace inital_calculations {

int16_t alpha(const base_36::base_36_type& serial_base);
int16_t bravo(const base_36::base_36_type& serial_base);
int16_t charlie(const base_36::base_36_type& serial_base);
int16_t delta(const base_36::base_36_type& serial_base);

} // namespace inital_calculations

#endif // SIMON_STORES_RULESET_INITAL_CALCULATIONS_H