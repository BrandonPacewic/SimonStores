/*
 * Copyright (c) 2022 Brandon Pacewic
 *
 * Developed and tested by Brandon Pacewic
 * 
 * base_36_type.h
 */

#pragma once
#ifndef _BASE_36_TYPE_H
#define _BASE_36_TYPE_H 1

#include <string>
#include <vector>

namespace base_36_type {

class base_36_type {
private:
    std::string char_base;
    std::vector<int> num_base;
    std::vector<bool> is_num;
    std::size_t sz;

public:
    base_36_type(std::string _char_base) 
        : char_base{_char_base}, sz{_char_base.length()} {
        num_base.assign(sz, 0);
        is_num.assign(sz, false);
    }
};

} // namespace base_36_type

#endif // _BASE_36_TYPE_H