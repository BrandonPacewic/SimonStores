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
#ifndef SIMON_STORES_MATH_MOD_TYPE_H_
#define SIMON_STORES_MATH_MOD_TYPE_H_

#include <cstdint>

namespace mod_types {

template <typename _Tp>
class mod_type {
   public:
    _Tp value;

    mod_type();
    mod_type(_Tp _value);

    explicit operator int16_t() const;
    explicit operator uint16_t() const;
    explicit operator int() const;
    explicit operator int64_t() const;
    explicit operator float() const;
    explicit operator double() const;
    explicit operator long double() const;

    mod_type& operator%=(const mod_type&);
    mod_type operator%(const mod_type&) const;

    mod_type& operator++();
    mod_type& operator--();
    mod_type& operator+=(const mod_type&);
    mod_type& operator-=(const mod_type&);
    mod_type& operator*=(const mod_type&);
    mod_type& operator/=(const mod_type&);
    mod_type operator+(const mod_type&) const;
    mod_type operator-(const mod_type&) const;
    mod_type operator*(const mod_type&) const;
    mod_type operator/(const mod_type&) const;

    bool operator==(const mod_type&) const;
    bool operator!=(const mod_type&) const;
    bool operator<(const mod_type&) const;
    bool operator>(const mod_type&) const;
    bool operator<=(const mod_type&) const;
    bool operator>=(const mod_type&) const;
};

}  // namespace mod_types

#endif  // SIMON_STORES_MATH_MOD_TYPE_H_
