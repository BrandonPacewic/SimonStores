/*
 * Copyright (c) 2022 Brandon Pacewic
 *
 * Developed and tested by Brandon Pacewic
 * 
 * static_mod_type.h
 */

#pragma once
#ifndef _BRANDON_STATIC_MOD_TYPE_H
#define _BRANDON_STATIC_MOD_TYPE_H 1

#include <cstdint>

namespace mod_types {

// TODO: Check overflow; default is int
typedef int ceil_num;

template<typename _Tp>
class static_mod_type {
public:
	_Tp value;
	ceil_num ceil;

	static_mod_type(ceil_num _ceil);
	~static_mod_type();

	explicit operator int() const;
	explicit operator int64_t() const;
	explicit operator float() const;
	explicit operator double() const;
	explicit operator long double() const;

    // Side feature of static_mod_type<> class, modular arithmetic in C++ works
    // different than it otherwise should. In C and C++ the % operator creates
    // a value between -b and b when in most other cases the expected return 
    // value should be between 0 and b. This is a simple fix. This, not the
    // main feature of this class, is found in both the static_mod_type<> class 
    // as well as the mod_type<> class. This change also can be found for the
    // operator%

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

} // namespace mod_types

#endif