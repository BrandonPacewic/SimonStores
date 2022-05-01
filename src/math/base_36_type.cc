/*
 * Copyright (c) 2022 Brandon Pacewic
 *
 * Developed and tested by Brandon Pacewic
 *
 * base_36_type.cc
 */

#include "base_36_type.h"

#include <string>
#include <vector>

using base_36::base_36_type;

base_36_type::base_36_type(std::string _char_base)
    : char_base{_char_base}, sz{_char_base.length()} {
    num_base.assign(sz, 0);
    is_num.assign(sz, false);

    for (int i = 0; i < sz; ++i) {
        if (std::isdigit(char_base[i]) != 0) {
            is_num[i] = true;
        }

        num_base[i] = int(char_base[i] - '0');
    }
}

const char& base_36_type::operator[](int index) const {
    return char_base[index];
}

const std::string& base_36_type::string() const { return char_base; }
const std::vector<int>& base_36_type::number_base() const { return num_base; }
const std::vector<bool>& base_36_type::is_number() const { return is_num; }
