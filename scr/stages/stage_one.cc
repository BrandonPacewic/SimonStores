/*
 * Copyright (c) 2022 Brandon Pacewic
 *
 * Developed and tested by Brandon Pacewic
 * 
 * stage_one.cc
 */

#ifndef _STAGE_ONE_C
#define _STAGE_ONE_C 1

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <functional>
#include <unordered_map>
#include <vector>

#include "../math/static_mod_type.h"
#include "../ruleset/color_determine.h"
using mod_types::static_mod_type;
using color_determine::primary_secondary_mix;

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

    const int color_mix_value = primary_secondary_mix(flash);

    const int first = color_to_function_map.find(flash[0])->second(
        alpha[step-1], step, delta
    );
    const int second = color_to_function_map.find(flash[1])->second(
        alpha[step-1], step, delta
    );

    static_mod_type<int> answer(mod_limit);

    switch (color_mix_value) {
        case 2:
            answer += std::max(first, second);
            break;
        case 3:
            answer += first + second - (delta * 2);
            break;
        case 4:
            answer += std::min(first, second);
            break;
    }

    return int(answer);
}

int three_color_flash(const std::string& flash, const std::vector<int>& alpha,
    const int& step, const int& delta) {
    assert(flash.length() == 3);

    int color_mix_value = primary_secondary_mix(flash);
    static_mod_type<int> answer(mod_limit);

    if (color_mix_value == 3) {
        answer += alpha[step-1] + alpha[0];
    }
    else if (color_mix_value == 4 || color_mix_value == 5) {
        std::array<int, 3> color_calculations;

        for (int i = 0; i < 3; ++i) {
            color_calculations[i] = (
                color_to_function_map.find(flash[i])->second(
                    alpha[step-1], step, delta
                )
            );
        }

        switch (color_mix_value) {
            case 4:
                answer += *std::max_element(
                    color_calculations.begin(), color_calculations.end()
                );
                break;
            case 5:
                answer += *std::min_element(
                    color_calculations.begin(), color_calculations.end()
                );
                break;
        }
    }
    else {
        answer += alpha[step-1] - alpha[0];
    }

    return int(answer);
}

} // namespace

int one_calculations(const std::string& flash, 
    const std::vector<int>& alpha, const int& step, const int& delta) {
    assert(flash.length() <= 3);

    int answer = -999;

    switch (flash.length()) {
        case 1:
            answer = one_color_flash(flash, alpha, step, delta);
            break;
        case 2:
            answer = two_color_flash(flash, alpha, step, delta);
            break;
        case 3:
            answer = three_color_flash(flash, alpha, step, delta);
            break;
    }

    return answer;
}

} // namespace stages

#endif // _STAGE_ONE_C