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

#include "static_mod_type.h"

#include <cstdint>
#include <iostream>
#include <istream>

using mod_types::static_mod_type;

template <typename _Tp>
static_mod_type<_Tp>::static_mod_type(uint16_t _ceil) : value{0}, ceil{_ceil} {}

template <typename _Tp>
static_mod_type<_Tp>::operator int16_t() const {
    return value;
}

template <typename _Tp>
static_mod_type<_Tp>::operator uint16_t() const {
    return value;
}

template <typename _Tp>
static_mod_type<_Tp>::operator int() const {
    return value;
}

template <typename _Tp>
static_mod_type<_Tp>::operator int64_t() const {
    return value;
}

template <typename _Tp>
static_mod_type<_Tp>::operator float() const {
    return value;
}

template <typename _Tp>
static_mod_type<_Tp>::operator double() const {
    return value;
}

template <typename _Tp>
static_mod_type<_Tp>::operator long double() const {
    return value;
}

template <typename _Tp>
static_mod_type<_Tp>& static_mod_type<_Tp>::operator%=(
    const static_mod_type<_Tp>& other) {
    value %= other.value;
    return *this;
}

template <typename _Tp>
static_mod_type<_Tp>& static_mod_type<_Tp>::operator+=(
    const static_mod_type<_Tp>& other) {
    value += other.value;
    return *this %= ceil;
}

template <typename _Tp>
static_mod_type<_Tp>& static_mod_type<_Tp>::operator-=(
    const static_mod_type<_Tp>& other) {
    value -= other.value;
    return *this %= ceil;
}

template <typename _Tp>
static_mod_type<_Tp>& static_mod_type<_Tp>::operator*=(
    const static_mod_type<_Tp>& other) {
    value *= other.value;
    return *this %= ceil;
}

template <typename _Tp>
static_mod_type<_Tp>& static_mod_type<_Tp>::operator++() {
    return *this += 1;
}

template <typename _Tp>
static_mod_type<_Tp>& static_mod_type<_Tp>::operator--() {
    return *this -= 1;
}

template <typename _Tp>
static_mod_type<_Tp>& static_mod_type<_Tp>::operator/=(
    const static_mod_type<_Tp>& other) {
    return value /= other.value;
}

template <typename _Tp>
static_mod_type<_Tp> static_mod_type<_Tp>::operator+(
    const static_mod_type<_Tp>& other) const {
    auto tmp = *this;
    return tmp += other;
}

template <typename _Tp>
static_mod_type<_Tp> static_mod_type<_Tp>::operator-(
    const static_mod_type<_Tp>& other) const {
    auto tmp = *this;
    return tmp -= other;
}

template <typename _Tp>
static_mod_type<_Tp> static_mod_type<_Tp>::operator*(
    const static_mod_type<_Tp>& other) const {
    auto tmp = *this;
    return tmp *= other;
}

template <typename _Tp>
static_mod_type<_Tp> static_mod_type<_Tp>::operator/(
    const static_mod_type<_Tp>& other) const {
    auto tmp = *this;
    return tmp /= other;
}

template <typename _Tp>
static_mod_type<_Tp> static_mod_type<_Tp>::operator%(
    const static_mod_type<_Tp>& other) const {
    auto tmp = *this;
    return tmp %= other;
}

template <typename _Tp>
bool static_mod_type<_Tp>::operator==(const static_mod_type<_Tp>& other) const {
    return value == other.value;
}

template <typename _Tp>
bool static_mod_type<_Tp>::operator!=(const static_mod_type<_Tp>& other) const {
    return value != other.value;
}

template <typename _Tp>
bool static_mod_type<_Tp>::operator<(const static_mod_type<_Tp>& other) const {
    return value < other.value;
}

template <typename _Tp>
bool static_mod_type<_Tp>::operator>(const static_mod_type<_Tp>& other) const {
    return value > other.value;
}

template <typename _Tp>
bool static_mod_type<_Tp>::operator<=(const static_mod_type<_Tp>& other) const {
    return value <= other.value;
}

template <typename _Tp>
bool static_mod_type<_Tp>::operator>=(const static_mod_type<_Tp>& other) const {
    return value >= other.value;
}

template <typename _Tp>
std::ostream& operator<<(std::ostream& os, const static_mod_type<_Tp>& a) {
    return os << a.value;
}

template <typename _Tp>
std::istream& operator>>(std::istream& is, static_mod_type<_Tp>& a) {
    return is >> a.value;
}