/*
 * Copyright (c) 2022 Brandon Pacewic
 *
 * Developed and tested by Brandon Pacewic
 * 
 * stage_one.cc
 */

#ifndef _STAGE_ONE_C
#define _STAGE_ONE_C 1

#include <cassert>
#include <cmath>
#include <functional>
#include <unordered_map>
#include <vector>

#include "../math/static_mod_type.h"
using mod_types::static_mod_type;

#include "stage_one.h"

namespace stages {

namespace {

constexpr int mod_limit = 365;

const std::unordered_map<
    char, std::function<int(int, int, int)>
> color_to_function_map = {
    {'r', [](const int& x, const int&, const int& d) -> int {
        static_mod_type<int> answer(mod_limit);
        answer += x + d;
        return int(answer);
    }},
    {'g', [](const int& x, const int&, const int& d) -> int {
        static_mod_type<int> answer(mod_limit);
        answer += x - d;
        return int(answer);
    }},
    {'b', [](const int& x, const int&, const int& d) -> int {
        static_mod_type<int> answer(mod_limit);
        answer += (2 * x) - d;
        return int(answer);
    }},
    {'c', [](const int& x, const int& s, const int& d) -> int {
        static_mod_type<int> answer(mod_limit);
        answer += d - x - (s * 8);
        return int(answer);
    }},
    {'m', [](const int& x, const int& s, const int&) -> int {
        static_mod_type<int> answer(mod_limit);
        answer += (3 * pow(s, 3)) - (2 * x);
        return int(answer);
    }},
    {'y', [](const int& x, const int& s, const int& d) -> int {
        static_mod_type<int> answer(mod_limit);
        answer += (x + d) - (s * 6);
        return int(answer);
    }},
};

int one_color_flash(const std::string& flash, const std::vector<int>& alpha,
    const int& step, const int& delta) {
    assert(flash.length() == 1);

    return color_to_function_map.find(flash[0])->second(
        alpha[step-1], step, delta
    );
}

int two_color_flash(const std::string& flash, const std::vector<int>& alpha,
    const int& step, const int& delta) {
    assert(flash.length() == 2);

    //TODO: add color determine functions
    // const int color_mix_value

    return 0;
}

} // namespace

} // namespace stages

#endif // _STAGE_ONE_C