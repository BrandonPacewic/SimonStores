/*
 * Copyright (c) 2022 Brandon Pacewic
 *
 * Developed and tested by Brandon Pacewic
 * 
 * stage_two.cc
 */

#ifndef _STAGE_TWO_C
#define _STAGE_ONE_C 1

#include <cassert>
#include <cmath>
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

#include "../math/static_mod_type.h"
#include "../ruleset/color_determine.h"
using mod_types::static_mod_type;
using color_determine::primary_secondary_mix;
using color_determine::missing_color;

namespace stages {

namespace {

constexpr int mod_limit = 365;

const std::unordered_map<
    char, std::function<int(std::vector<int>, int, int, int)>
> color_to_function_map = {
    {'r', [](const std::vector<int>& a, const int& x, 
        const int& s, const int& d) -> int {
        static_mod_type<int> answer(mod_limit);
        answer += x + a[s-1] + pow(s, 2);
        return int(answer);
    }},
    {'g', [](const std::vector<int>& a, const int& x,
        const int& s, const int& d) -> int {
        static_mod_type<int> answer(mod_limit);
        answer += (x * 2) - a[s-1];
        return int(answer);
    }},
    {'b', [](const std::vector<int>& a, const int& x,
        const int& s, const int& d) -> int {
        static_mod_type<int> answer(mod_limit);
        answer += (x * 2) - a[0] - (4 * pow(s, 2));
        return int(answer);
    }},
    {'c', [](const std::vector<int>& a, const int& x,
        const int& s, const int& d) -> int {
        static_mod_type<int> answer(mod_limit);
        answer += x + a[1];
        return int(answer);
    }},
    {'m', [](const std::vector<int>& a, const int& x,
        const int& s, const int& d) -> int {
        static_mod_type<int> answer(mod_limit);
        answer += x + a[2] - d;
        return int(answer);
    }},
    {'y', [](const std::vector<int>& a, const int& x,
        const int& s, const int& d) -> int {
        static_mod_type<int> answer(mod_limit);
        answer += x + a[3] - a[s-1];
        return int(answer);
    }},
};

int one_color_flash(const std::string& flash, const std::vector<int>& alpha,
    const std::vector<int>& bravo, const int& step, const int& delta) {
    assert(flash.length() == 1);

    return color_to_function_map.find(flash[0])->second(
        alpha, bravo[step-1], step, delta
    );
}

int two_color_flash(const std::string& flash, const std::vector<int>& alpha,
    const std::vector<int>& bravo, const int& step, const int& delta) {
    assert(flash.length() == 2);

    const int color_mix_value = primary_secondary_mix(flash);
    static_mod_type<int> answer(mod_limit);

    if (color_mix_value == 2 || color_mix_value == 3) {
        const int first = color_to_function_map.find(flash[0])->second(
            alpha, bravo[step-1], step, delta
        );
        const int second = color_to_function_map.find(flash[1])->second(
            alpha, bravo[step-1], step, delta
        );

        if (color_mix_value == 2) {
            answer += abs(first - second);
        }
        else {
            answer += (4 * delta) - abs(second - first);
        }
    }
    else {
        assert(color_mix_value == 4); // both colors are secondary

        const char absent_color = missing_color(flash);
        const int first = color_to_function_map.find(absent_color)->second(
            alpha, alpha[step-1], step, delta
        );
        const int second = color_to_function_map.find(absent_color)->second(
            alpha, bravo[step-1], step, delta
        );

        answer += std::min(first, second);
    }

    return int(answer);
}

} // namespace

} // namespace stages

#endif // _STAGE_ONE_C