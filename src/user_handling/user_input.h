/*
 * Copyright (c) 2022 Brandon Pacewic
 *
 * Developed and tested by Brandon Pacewic
 *
 * user_input.h
 */

#pragma once
#ifndef _USER_INPUT_H
#define _USER_INPUT_H

#include <string>

namespace user_input {

std::string input_check(const int& required_size = -1, const int& min_size = -1,
                        const int& max_size = -1);

}  // namespace user_input

#endif  // _USER_INPUT_H