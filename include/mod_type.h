/*
 * Copyright (c) 2022 Brandon Pacewic
 *
 * Developed and tested by Brandon Pacewic
 * 
 * mod_type.h
 */

#pragma once
#ifndef _BRANDON_MOD_TYPE_H
#define _BRANDON_MOD_TYPE_H 1

#include <cstdint>

namespace mod_types {

template<typename _Tp>
class mod_type {
public:
	_Tp value;

	mod_type(_Tp _value);
	mod_type();

	explicit operator int() const;
	explicit operator int64_t() const;
	explicit operator float() const;
	explicit operator double() const;
	explicit operator long double() const;

    // Main feature of mod_type<> class, modular arithmetic in C++ works
    // different than it otherwise should. In C and C++ the % operator creates
    // a value between -b and b when in most other cases the expected return 
    // value should be between 0 and b. This is a simple fix.
	mod_type& operator%=(const mod_type&);
	mod_type operator%(const mod_type&) const;

    // Other basic math operators, nothing changes
    // besides modular arithmetic
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

} // namespace mod_types

#endif // _BRANDON_MOD_TYPE_H
