/*
 * Copyright (c) 2022 Brandon Pacewic
 *
 * Developed and tested by Brandon Pacewic
 * 
 * stage_three.cc
 */

#ifndef _STAGE_THREE_C
#define _STAGE_THREE_C 1

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

#include "../math/mod_type.h"
using mod_types::mod_type;

#include "../math/static_mod_type.h"
using mod_types::static_mod_type;

#include "../ruleset/color_determine.h"
using color_determine::primary_secondary_mix;

namespace stages {

namespace {

constexpr int mod_limit = 365;

const std::unordered_map<
    char, std::function<int(
        std::vector<mod_type<int>>, std::vector<mod_type<int>>, int, int, int
    )>
> color_to_function_map = {
    {'r', [](const std::vector<mod_type<int>>& a, 
        const std::vector<mod_type<int>>& b, 
        const int& x, const int& s, const int& d) -> int {
        static_mod_type<int> answer(mod_limit);
        answer += x + int(b[s-1]) - int(a[s-1]);
        return int(answer);
    }},
    {'g', [](const std::vector<mod_type<int>>& a,
        const std::vector<mod_type<int>>& b,
        const int& x, const int& s, const int& d) -> int {
        static_mod_type<int> answer(mod_limit);
        answer += x - (int(b[s-1]) * 2);
        return int(answer);
    }},
    {'b', [](const std::vector<mod_type<int>>& a, 
        const std::vector<mod_type<int>>& b,
        const int& x, const int& s, const int& d) -> int {
        static_mod_type<int> answer(mod_limit);
        answer += x + int(b[0]) - int(a[3]);
        return int(answer);
    }},
    {'c', [](const std::vector<mod_type<int>>& a,
        const std::vector<mod_type<int>>& b,
        const int& x, const int& s, const int& d) -> int {
        static_mod_type<int> answer(mod_limit);
        answer += x - int(b[s-1]) + int(a[s-1]);
        return int(answer);
    }},
    {'m', [](const std::vector<mod_type<int>>& a,
        const std::vector<mod_type<int>>& b,
        const int& x, const int& s, const int& d) -> int {
        static_mod_type<int> answer(mod_limit);
        answer += x - (int(a[s-1]) * 2);
        return int(answer);
    }},
    {'y', [](const std::vector<mod_type<int>>& a,
        const std::vector<mod_type<int>>& b,
        const int& x, const int& s, const int& d) -> int {
        static_mod_type<int> answer(mod_limit);
        answer += x + int(b[4]) - int(a[0]);
        return int(answer);
    }},
};

int one_color_flash(const std::string& flash, 
    const std::vector<mod_type<int>>& alpha, 
    const std::vector<mod_type<int>>& bravo,
    const std::vector<mod_type<int>>& charlie,
    const int& step, const int& delta) {
    assert(flash.length() == 1);

    static_mod_type<int> answer(mod_limit);
    answer += color_to_function_map.find(flash[0])->second(
        alpha, bravo, int(charlie[step-1]), step, delta
    );

    return int(answer);
}

int two_color_flash(const std::string& flash,
    const std::vector<mod_type<int>>& alpha,
    const std::vector<mod_type<int>>& bravo,
    const std::vector<mod_type<int>>& charlie,
    const int& step, const int& delta) {
    assert(flash.length() == 2);

    const int color_mix_value = primary_secondary_mix(flash);
    static_mod_type<int> answer(mod_limit);

    if (color_mix_value == 2) {
        const char absent_color = color_determine::missing_color(flash);

        answer += (
            color_to_function_map.find(absent_color)->second(
                alpha, bravo, int(charlie[step-1]), step, delta
            ) + (
                color_to_function_map.find(absent_color)->second(
                    alpha, bravo, int(bravo[step-1]), step, delta
            )) + (
                color_to_function_map.find(absent_color)->second(
                    alpha, bravo, int(alpha[step-1]), step, delta
            ))
        );
    }
    else if (color_mix_value == 3) {
        std::array<int, 3> color_values;
        color_values[0] = color_to_function_map.find(flash[0])->second(
            alpha, bravo, int(charlie[step-1]), step, delta
        );
        color_values[1] = color_to_function_map.find(flash[1])->second(
            alpha, bravo, int(charlie[step-1]), step, delta
        );
        color_values[2] = -1 * abs(color_values[0] - color_values[1]);

        answer += *std::min_element(color_values.begin(), color_values.end());
    }
    else {
        const char absent_color = color_determine::missing_color(flash);

        answer += int(
            color_to_function_map.find(absent_color)->second(
                alpha, bravo, int(charlie[step-1]), step, delta
            ) - (
                color_to_function_map.find(flash[0])->second(
                    alpha, bravo, int(charlie[step-1]), step, delta
            )) - (
                color_to_function_map.find(flash[1])->second(
                    alpha, bravo, int(charlie[step-1]), step, delta
            ))
        );
    }

    return int(answer);
}


} // namespace

} // namespace stages

#endif // _STAGE_THREE_C