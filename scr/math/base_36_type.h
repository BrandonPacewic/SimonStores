/*
 * Copyright (c) 2022 Brandon Pacewic
 *
 * Developed and tested by Brandon Pacewic
 * 
 * base_36_type.h
 */

// TODO: more info comment
// Once this class has been initalized it cannot be modfyed in any way
// The idea is just to hold information in a more convinient way without the
// need for changing the data

#pragma once
#ifndef _BASE_36_TYPE_H
#define _BASE_36_TYPE_H 1

#include <string>
#include <vector>

namespace base_36 {

class base_36_type {
private:
    std::string char_base;
    std::vector<int> num_base;
    std::vector<bool> is_num;
    std::size_t sz;

public:
    base_36_type(std::string _char_base);
    ~base_36_type() = default;

    const char& operator[](int index) const;

    const std::string& string() const;
    const std::vector<int>& number_base() const;
    const std::vector<bool>& is_number() const;
};

} // namespace base_36

#endif // _BASE_36_TYPE_H