/*
 * Copyright (c) 2022 Brandon Pacewic
 *
 * Developed and tested by Brandon Pacewic
 *
 * static_mod_type.h
 */

#pragma once
#ifndef SIMON_STORES_MATH_STATIC_MOD_TYPE_H_
#define SIMON_STORES_MATH_STATIC_MOD_TYPE_H_

#include <cstdint>

namespace mod_types {

template <typename _Tp>
class static_mod_type {
   public:
    _Tp value;
    uint16_t ceil;

    static_mod_type(uint16_t);

    explicit operator int16_t() const;
    explicit operator uint16_t() const;
    explicit operator int() const;
    explicit operator int64_t() const;
    explicit operator float() const;
    explicit operator double() const;
    explicit operator long double() const;

    static_mod_type& operator%=(const static_mod_type&);
    static_mod_type& operator+=(const static_mod_type&);
    static_mod_type& operator-=(const static_mod_type&);
    static_mod_type& operator*=(const static_mod_type&);
    static_mod_type& operator/=(const static_mod_type&);

    static_mod_type& operator++();
    static_mod_type& operator--();

    static_mod_type operator+(const static_mod_type&) const;
    static_mod_type operator-(const static_mod_type&) const;
    static_mod_type operator*(const static_mod_type&) const;
    static_mod_type operator/(const static_mod_type&) const;
    static_mod_type operator%(const static_mod_type&) const;

    bool operator==(const static_mod_type&) const;
    bool operator!=(const static_mod_type&) const;
    bool operator<(const static_mod_type&) const;
    bool operator>(const static_mod_type&) const;
    bool operator<=(const static_mod_type&) const;
    bool operator>=(const static_mod_type&) const;
};

}  // namespace mod_types

#endif  // SIMON_STORES_MATH_STATIC_MOD_TYPE_H_