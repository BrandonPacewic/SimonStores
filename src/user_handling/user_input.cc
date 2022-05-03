/*
 * Copyright (c) 2022 Brandon Pacewic
 *
 * Developed and tested by Brandon Pacewic
 *
 * user_input.cc
 */

#include "user_input.h"

#include <iostream>
#include <string>

namespace user_input {
namespace {

std::string required_size_check(std::string& str,
                                const int16_t& required_size) {
    while (str.length() != required_size) {
        std::cout << "\n\nYou did not meet the required size of "
                  << required_size << ".\nPlease try again: ";
        getline(std::cin, str);
    }

    return str;
}

std::string max_size_check(std::string& str, const int16_t& max_size) {
    while (str.length() > max_size) {
        std::cout << "\n\nYou exceeded the max size of " << max_size
                  << ".\nPlease try again: ";
        getline(std::cin, str);
    }

    return str;
}

std::string min_size_check(std::string& str, const int16_t& min_size) {
    while (str.length() < min_size) {
        std::cout << "\n\nYou did not meet the min size of " << min_size
                  << ".\nPlease try again: ";
        getline(std::cin, str);
    }

    return str;
}

std::string string_to_lower(std::string& str) {
    for (auto& ch : str) {
        ch = tolower(ch);
    }

    return str;
}

void lizard_check(std::string& str) {
    const std::string lizard = "lizard";

    if (str == lizard) {
        while (true) {
            std::cout << " Congratulations it's a lizard! ";
        }
    }
}

}  // namespace

std::string input_check(const int& required_size, const int& min_size,
                        const int& max_size) {
    std::string str;
    getline(std::cin, str);
    str = string_to_lower(str);

    lizard_check(str);

    if (required_size != -1) {
        str = required_size_check(str, required_size);
    } else if (max_size != -1) {
        str = max_size_check(str, max_size);
    } else if (min_size != -1) {
        str = min_size_check(str, min_size);
    }

    return str;
}

}  // namespace user_input