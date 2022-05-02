/*
 * Copyright (c) 2022 Brandon Pacewic
 *
 * Developed and tested by Brandon Pacewic
 *
 * inital_calculations.cc
 */

#include "inital_calculations.h"

#include <cassert>
#include <vector>

#include "../math/base_36_type.h"
#include "../math/static_mod_type.h"

using base_36::base_36_type;
using mod_types::static_mod_type;

namespace inital_calculations {

constexpr uint16_t mod_limit = 365;
constexpr uint16_t base_36_factor = 36;
constexpr uint16_t character_add = 9;

int alpha(const base_36_type& serial_base) {
    static_mod_type<int16_t> first(mod_limit), second(mod_limit);
    const auto& serial_is_number = serial_base.is_number();
    const auto& serial_number_base = serial_base.number_base();

    if (serial_is_number[2]) {
        first += serial_number_base[2] * base_36_factor;
    } else {
        first += (serial_number_base[2] + character_add) * base_36_factor;
    }

    if (serial_is_number[3]) {
        second += serial_number_base[3];
    } else {
        second += serial_number_base[3] + character_add;
    }

    return int16_t(first + second);
}

int bravo(const base_36_type& serial_base) {
    static_mod_type<int16_t> first(mod_limit);
    const auto& serial_is_number = serial_base.is_number();
    const auto& serial_number_base = serial_base.number_base();

    if (serial_is_number[4]) {
        first += serial_number_base[4] * base_36_factor;
    } else {
        first += (serial_number_base[4] + character_add) * base_36_factor;
    }

    assert(serial_is_number[5]);

    return int16_t(first + serial_number_base[5]);
}

int charlie(const base_36_type& serial_base) {
    static_mod_type<int16_t> first(mod_limit), second(mod_limit);
    const auto& serial_is_number = serial_base.is_number();
    const auto& serial_number_base = serial_base.number_base();

    if (serial_is_number[0]) {
        first += serial_number_base[0] * base_36_factor;
    } else {
        first += (serial_number_base[0] + character_add) * base_36_factor;
    }

    if (serial_is_number[1]) {
        second += serial_number_base[1];
    } else {
        second += serial_number_base[1] + character_add;
    }

    return int16_t(first + second);
}

int delta(const base_36_type& serial_base) {
    static_mod_type<int16_t> delta(mod_limit);
    const auto& serial_is_number = serial_base.is_number();
    const auto& serial_number_base = serial_base.number_base();

    for (std::size_t i = 0; i < serial_number_base.size(); ++i) {
        if (serial_is_number[i]) {
            delta += serial_number_base[i];
        } else {
            delta += serial_number_base[i] + character_add;
        }
    }

    return int16_t(delta);
}

}  // namespace inital_calculations