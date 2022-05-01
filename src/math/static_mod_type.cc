/*
 * Copyright (c) 2022 Brandon Pacewic
 *
 * Developed and tested by Brandon Pacewic
 *
 * static_mod_type.cc
 */

#ifndef _BRANDON_STATIC_MOD_TYPE_C
#define _BRANDON_STATIC_MOD_TYPE_C 1

#include "static_mod_type.h"

#include <cstdint>
#include <iostream>
#include <istream>
using mod_types::ceil_num;
using mod_types::static_mod_type;

template <typename _Tp>
static_mod_type<_Tp>::static_mod_type(ceil_num _ceil) : value{0}, ceil{_ceil} {}

template <typename _Tp>
static_mod_type<_Tp>::~static_mod_type() = default;

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
    if (value < 0) {
        value += other.value;
    }
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

#endif  // _BRANDON_STATIC_MOD_TYPE_C