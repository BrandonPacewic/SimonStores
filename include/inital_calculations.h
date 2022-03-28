/*
 * Copyright (c) 2022 Brandon Pacewic
 *
 * Developed and tested by Brandon Pacewic
 * 
 * inital_calculations.h
 */

#pragma once
#ifndef _INITAL_CALCULATIONS_H
#define _INITAL_CALCULATIONS_H 1

#include "../math/base_36_type.h"
using base_36::base_36_type;

namespace inital_calculations {

int alpha(const base_36_type& serial_base);
int bravo(const base_36_type& serial_base);
int charlie(const base_36_type& serial_base);
int delta(const base_36_type& serial_base);

} // namespace inital_calculations

#endif // _INITAL_CALCULATIONS_H