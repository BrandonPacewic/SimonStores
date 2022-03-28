/*
 * Copyright (c) 2022 Brandon Pacewic
 *
 * Developed and tested by Brandon Pacewic
 * 
 * mod_type.cc
 */

#ifndef _BRANDON_MOD_TYPE_C
#define _BRANDON_MOD_TYPE_C 1

#include <cstdint>
#include <iostream>
#include <istream>

#include "../../include/mod_type.h"
using mod_types::mod_type;

template<typename _Tp>
mod_type<_Tp>::mod_type(_Tp _value) : value{_value} {}

template<typename _Tp>
mod_type<_Tp>::mod_type() : value{0} {}

template<typename _Tp>
mod_type<_Tp>::operator int() const { return value; }

template<typename _Tp>
mod_type<_Tp>::operator int64_t() const { return value; }

template<typename _Tp>
mod_type<_Tp>::operator float() const { return value; }

template<typename _Tp>
mod_type<_Tp>::operator double() const { return value; }

template<typename _Tp>
mod_type<_Tp>::operator long double() const { return value; }

template<typename _Tp>
mod_type<_Tp>& mod_type<_Tp>::operator%=(const mod_type<_Tp>& other) {
	value %= other.value;
	if (value < 0) { value += other.value; }
	return *this;
}

template<typename _Tp>
mod_type<_Tp> mod_type<_Tp>::operator%(const mod_type<_Tp>& other) const {
	mod_type tmp = *this;
	tmp.value %= other.value;
	if (tmp.value < 0) { tmp.value += other.value;}
	return tmp;
}

template<typename _Tp>
mod_type<_Tp>& mod_type<_Tp>::operator++() { 
    ++value; 
    return *this; 
}

template<typename _Tp>
mod_type<_Tp>& mod_type<_Tp>::operator--() { 
    --value; 
    return *this; 
}

template<typename _Tp>
mod_type<_Tp>& mod_type<_Tp>::operator+=(const mod_type<_Tp>& other) { 
	value += other.value; 
	return *this; 
}

template<typename _Tp>
mod_type<_Tp>& mod_type<_Tp>::operator-=(const mod_type<_Tp>& other) { 
	value -= other.value; 
	return *this; 
}

template<typename _Tp>
mod_type<_Tp>& mod_type<_Tp>::operator*=(const mod_type<_Tp>& other) { 
	value *= other.value; 
	return *this; 
}

template<typename _Tp>
mod_type<_Tp>& mod_type<_Tp>::operator/=(const mod_type<_Tp>& other){ 
	value /= other.vaule; 
	return *this; 
}

template<typename _Tp>
mod_type<_Tp> mod_type<_Tp>::operator+(const mod_type<_Tp>& other) const
{ return value + other.value; }

template<typename _Tp>
mod_type<_Tp> mod_type<_Tp>::operator-(const mod_type<_Tp>& other) const
{ return value + other.value; }

template<typename _Tp>
mod_type<_Tp> mod_type<_Tp>::operator*(const mod_type<_Tp>& other) const
{ return value * other.value; }

template<typename _Tp>
mod_type<_Tp> mod_type<_Tp>::operator/(const mod_type<_Tp>& other) const
{ return value / other.value; }

template<typename _Tp>
bool mod_type<_Tp>::operator==(const mod_type<_Tp>& other) const
{ return value == other.value; }

template<typename _Tp>
bool mod_type<_Tp>::operator!=(const mod_type<_Tp>& other) const
{ return value != other.value; }

template<typename _Tp>
bool mod_type<_Tp>::operator<(const mod_type<_Tp>& other) const
{ return value < other.value; }

template<typename _Tp>
bool mod_type<_Tp>::operator>(const mod_type<_Tp>& other) const
{ return value > other.value; }

template<typename _Tp>
bool mod_type<_Tp>::operator<=(const mod_type<_Tp>& other) const
{ return value <= other.value; }

template<typename _Tp>
bool mod_type<_Tp>::operator>=(const mod_type<_Tp>& other) const
{ return value >= other.value; }

template<typename _Tp>
std::ostream& operator<<(std::ostream& os, const mod_type<_Tp>& a)
{ return os << a.value; }

template<typename _Tp>
std::istream& operator>>(std::istream& is, mod_type<_Tp>& a)
{ return is >> a.value; }

#endif // _BRANDON_MOD_TYPE_C
