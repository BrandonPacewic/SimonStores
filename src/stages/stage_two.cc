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
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

#include "../math/static_mod_type.h"
using mod_types::static_mod_type;

#include "../math/mod_type.h"
using mod_types::mod_type;

#include "../ruleset/color_determine.h"
using color_determine::primary_secondary_mix;
using color_determine::missing_color;

#include "stage_two.h"

namespace stages {

namespace {

constexpr int mod_limit = 365;

const std::unordered_map<
    char, std::function<int(std::vector<mod_type<int>>, int, int, int)>
> color_to_function_map = {
    {'r', [](const std::vector<mod_type<int>>& a, const int& x, 
        const int& s, const int& d) -> int {
        static_mod_type<int> answer(mod_limit);
        answer += x + int(a[s-1]) + pow(s, 2);
        return int(answer);
    }},
    {'g', [](const std::vector<mod_type<int>>& a, const int& x,
        const int& s, const int& d) -> int {
        static_mod_type<int> answer(mod_limit);
        answer += (x * 2) - int(a[s-1]);
        return int(answer);
    }},
    {'b', [](const std::vector<mod_type<int>>& a, const int& x,
        const int& s, const int& d) -> int {
        static_mod_type<int> answer(mod_limit);
        answer += (x * 2) - int(a[0]) - (4 * pow(s, 2));
        return int(answer);
    }},
    {'c', [](const std::vector<mod_type<int>>& a, const int& x,
        const int& s, const int& d) -> int {
        static_mod_type<int> answer(mod_limit);
        answer += x + int(a[1]);
        return int(answer);
    }},
    {'m', [](const std::vector<mod_type<int>>& a, const int& x,
        const int& s, const int& d) -> int {
        static_mod_type<int> answer(mod_limit);
        answer += x + int(a[2]) - d;
        return int(answer);
    }},
    {'y', [](const std::vector<mod_type<int>>& a, const int& x,
        const int& s, const int& d) -> int {
        static_mod_type<int> answer(mod_limit);
        answer += x + int(a[3] - a[s-1]);
        return int(answer);
    }},
};

int one_color_flash(const std::string& flash, 
    const std::vector<mod_type<int>>& alpha,
    const std::vector<mod_type<int>>& bravo, 
    const int& step, const int& delta) {
    assert(flash.length() == 1);

    return color_to_function_map.find(flash[0])->second(
        alpha, int(bravo[step-1]), step, delta
    );
}

int two_color_flash(const std::string& flash, 
    const std::vector<mod_type<int>>& alpha,
    const std::vector<mod_type<int>>& bravo, 
    const int& step, const int& delta) {
    assert(flash.length() == 2);

    const int color_mix_value = primary_secondary_mix(flash);
    static_mod_type<int> answer(mod_limit);

    if (color_mix_value == 2 || color_mix_value == 3) {
        const int first = color_to_function_map.find(flash[0])->second(
            alpha, int(bravo[step-1]), step, delta
        );
        const int second = color_to_function_map.find(flash[1])->second(
            alpha, int(bravo[step-1]), step, delta
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
            alpha, int(alpha[step-1]), step, delta
        );
        const int second = color_to_function_map.find(absent_color)->second(
            alpha, int(bravo[step-1]), step, delta
        );

        answer += std::min(first, second);
    }

    return int(answer);
}

int three_color_flash(const std::string& flash, 
    const std::vector<mod_type<int>>& alpha,
    const std::vector<mod_type<int>>& bravo, 
    const int& step, const int& delta) {
    assert(flash.length() == 3);

    const int color_mix_value = primary_secondary_mix(flash);
    static_mod_type<int> answer(mod_limit);

    if (color_mix_value == 3) {
        answer += int(
            bravo[step-1] + ((bravo[step-1] % 4) * bravo[0]) - alpha[3]
        );
    }
    else if (color_mix_value == 4) {
        // One secondary, two primarys
        // Value returned from the secondary color will be stored in the 3rd
        // index of this container, the primary colors will be stored in either
        // the 0, 1, or 2 index
        std::vector<int> color_values(flash.length() + 1, 0);

        for (int i = 0; i < int(flash.length()); ++i) {
            if (color_determine::is_primary(flash[i])) {
                color_values[i] = color_to_function_map.find(flash[i])->second(
                    alpha, int(bravo[step-1]), step, delta
                );
            }
            else {
                color_values[3] = color_to_function_map.find(flash[i])->second(
                    alpha, int(alpha[step-1]), step, delta
                );
            }
        }

        answer += int(bravo[step-1] + std::accumulate(
            color_values.begin(), color_values.end(), 0)
        );
    }
    else if (color_mix_value == 5) {
        // Same as step above except two secondarys and one primary
        // Same thing but in reverse
        std::vector<int> color_values(flash.length() + 1, 0);

        for (int i = 0; i < flash.length(); ++i) {
            if (color_determine::is_secondary(flash[i])) {
                color_values[i] = color_to_function_map.find(flash[i])->second(
                    bravo, int(alpha[step-1]), step, delta
                );
            }
            else {
                color_values[i] = color_to_function_map.find(flash[i])->second(
                    bravo, int(bravo[step-1]), step, delta
                );
            }
        }

        answer += int(bravo[step-1] + std::accumulate(
            color_values.begin(), color_values.end(), 0)
        );
    }
    else {
        answer += int(
            bravo[step-1] + ((bravo[0] % 4) * bravo[step-1]) - alpha[3]
        );
    }

    return int(answer);
}

} // namespace

int two_calculations(const std::string& flash,
    const std::vector<mod_type<int>>& alpha,
    const std::vector<mod_type<int>>& bravo, 
    const int& step, const int& delta) {
    assert(flash.length() <= 3);

    int answer = -999;

    switch (flash.length()) {
        case 1:
            answer = one_color_flash(flash, alpha, bravo, step, delta);
            break;
        case 2:
            answer = two_color_flash(flash, alpha, bravo, step, delta);
            break;
        case 3:
            answer = three_color_flash(flash, alpha, bravo, step, delta);
            break;
    }

    return answer;
}

} // namespace stages

#endif // _STAGE_ONE_C