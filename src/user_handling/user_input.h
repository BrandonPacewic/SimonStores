/*
 * Copyright (c) 2022 Brandon Pacewic
 *
 * Developed and tested by Brandon Pacewic
 *
 * user_input.h
 */

#ifndef SIMON_STORES_USER_HANDLING_USER_INPUT_H_
#define SIMON_STORES_USER_HANDLING_USER_INPUT_H_

#include <string>

namespace user_input {

std::string input_check(const int16_t& required_size = -1,
                        const int16_t& min_size = -1,
                        const int16_t& max_size = -1);

}  // namespace user_input

#endif  // SIMON_STORES_USER_HANDLING_USER_INPUT_H_