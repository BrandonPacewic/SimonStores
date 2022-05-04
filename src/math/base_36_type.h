/* MIT License
 *
 * Copyright (c) 2022 Brandon Pacewic
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
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