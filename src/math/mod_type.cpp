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

#include "mod_type.h"

#include <cstdint>
#include <iostream>

using mod_types::mod_type;

template <typename _Tp>
mod_type<_Tp>::mod_type() : value{0} {}

template <typename _Tp>
mod_type<_Tp>::mod_type(_Tp _value) : value{_value} {}

template <typename _Tp>
mod_type<_Tp>::operator int16_t() const {
    return value;
}

template <typename _Tp>
mod_type<_Tp>::operator uint16_t() const {
    return value;
}

template <typename _Tp>
mod_type<_Tp>::operator int() const {
    return value;
}

template <typename _Tp>
mod_type<_Tp>::operator int64_t() const {
    return value;
}

template <typename _Tp>
mod_type<_Tp>::operator float() const {
    return value;
}

template <typename _Tp>
mod_type<_Tp>::operator double() const {
    return value;
}

template <typename _Tp>
mod_type<_Tp>::operator long double() const {
    return value;
}

template <typename _Tp>
mod_type<_Tp>& mod_type<_Tp>::operator%=(const mod_type<_Tp>& other) {
    value %= other.value;
    if (value < 0) {
        value += other.value;
    }
    return *this;
}

template <typename _Tp>
mod_type<_Tp> mod_type<_Tp>::operator%(const mod_type<_Tp>& other) const {
    mod_type tmp = *this;
    tmp.value %= other.value;
    if (tmp.value < 0) {
        tmp.value += other.value;
    }
    return tmp;
}

template <typename _Tp>
mod_type<_Tp>& mod_type<_Tp>::operator++() {
    ++value;
    return *this;
}

template <typename _Tp>
mod_type<_Tp>& mod_type<_Tp>::operator--() {
    --value;
    return *this;
}

template <typename _Tp>
mod_type<_Tp>& mod_type<_Tp>::operator+=(const mod_type<_Tp>& other) {
    value += other.value;
    return *this;
}

template <typename _Tp>
mod_type<_Tp>& mod_type<_Tp>::operator-=(const mod_type<_Tp>& other) {
    value -= other.value;
    return *this;
}

template <typename _Tp>
mod_type<_Tp>& mod_type<_Tp>::operator*=(const mod_type<_Tp>& other) {
    value *= other.value;
    return *this;
}

template <typename _Tp>
mod_type<_Tp>& mod_type<_Tp>::operator/=(const mod_type<_Tp>& other) {
    value /= other.value;
    return *this;
}

template <typename _Tp>
mod_type<_Tp> mod_type<_Tp>::operator+(const mod_type<_Tp>& other) const {
    return value + other.value;
}

template <typename _Tp>
mod_type<_Tp> mod_type<_Tp>::operator-(const mod_type<_Tp>& other) const {
    return value + other.value;
}

template <typename _Tp>
mod_type<_Tp> mod_type<_Tp>::operator*(const mod_type<_Tp>& other) const {
    return value * other.value;
}

template <typename _Tp>
mod_type<_Tp> mod_type<_Tp>::operator/(const mod_type<_Tp>& other) const {
    return value / other.value;
}

template <typename _Tp>
bool mod_type<_Tp>::operator==(const mod_type<_Tp>& other) const {
    return value == other.value;
}

template <typename _Tp>
bool mod_type<_Tp>::operator!=(const mod_type<_Tp>& other) const {
    return value != other.value;
}

template <typename _Tp>
bool mod_type<_Tp>::operator<(const mod_type<_Tp>& other) const {
    return value < other.value;
}

template <typename _Tp>
bool mod_type<_Tp>::operator>(const mod_type<_Tp>& other) const {
    return value > other.value;
}

template <typename _Tp>
bool mod_type<_Tp>::operator<=(const mod_type<_Tp>& other) const {
    return value <= other.value;
}

template <typename _Tp>
bool mod_type<_Tp>::operator>=(const mod_type<_Tp>& other) const {
    return value >= other.value;
}

template <typename _Tp>
std::ostream& operator<<(std::ostream& os, const mod_type<_Tp>& a) {
    return os << a.value;
}

template <typename _Tp>
std::istream& operator>>(std::istream& is, mod_type<_Tp>& a) {
    return is >> a.value;
}
