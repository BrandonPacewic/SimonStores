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
