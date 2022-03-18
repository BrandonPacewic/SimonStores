/*
 * Copyright (c) 2022 Brandon Pacewic
 *
 * Developed and tested by Brandon Pacewic
 * 
 * user_input.cc
 */

#ifndef _USER_INPUT_C
#define _USER_INPUT_C

#include <iostream>
#include <string>

#include "user_input.h"

namespace user_input {

namespace {

void required_size_check(std::string& str, const int& required_size) {
    while (str.length() != required_size) {
        std::cout << "\n\nYou did not meet the required size of " << 
            required_size << ".\nPlease try again: ";
        getline(std::cin, str);
    }
}

void max_size_check(std::string& str, const int& max_size) {
    while (str.length() > max_size) {
        std::cout << "\n\nYou exceeded the max size of " << max_size <<
            ".\nPlease try again: ";
        getline(std::cin, str);
    }
}

void min_size_check(std::string& str, const int& min_size) {
    while (str.length() < min_size) {
        std::cout << "\n\nYou did not meet the min size of " << min_size <<
            ".\nPlease try again: ";
        getline(std::cin, str);
    }
}

} // namespace

} // namespace user_input

#endif // _USER_INPUT_C