/*
 * Copyright (c) 2022 Brandon Pacewic
 *
 * Developed and tested by Brandon Pacewic
 * 
 * mod_type.h
 */

#pragma once
#ifndef SIMON_STORES_MATH_MOD_TYPE_H_
#define SIMON_STORES_MATH_MOD_TYPE_H_

#include <cstdint>

namespace mod_types {

template<typename _Tp>
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

} // namespace mod_types

#endif // SIMON_STORES_MATH_MOD_TYPE_H_
