/*
 * Copyright (c) 2022 Brandon Pacewic
 *
 * Developed and tested by Brandon Pacewic
 *
 * base_36_type.h
 */

#pragma once
#ifndef SIMON_STORES_MATH_BASE_36_TYPE_H_
#define SIMON_STORES_MATH_BASE_36_TYPE_H_

#include <cstdint>
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

    const char& operator[](int index) const;

    const std::string& string() const;
    const std::vector<int>& number_base() const;
    const std::vector<bool>& is_number() const;
};

}  // namespace base_36

#endif  // SIMON_STORES_MATH_BASE_36_TYPE_H_