/*
 * Copyright (c) 2022 Brandon Pacewic
 *
 * Developed and tested by Brandon Pacewic
 *
 * stage_one.cc
 */

#include "stage_one.h"

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <functional>
#include <unordered_map>
#include <vector>

#include "../math/mod_type.h"
#include "../math/static_mod_type.h"
#include "../ruleset/color_determine.h"

using color_determine::primary_secondary_mix;
using mod_types::mod_type;
using mod_types::static_mod_type;

namespace stages {
namespace {

constexpr uint16_t mod_limit = 365;

const std::unordered_map<char,
                         std::function<int16_t(int16_t, uint16_t, int16_t)>>
    color_to_function_map = {
        {'r',
         [](const int16_t& x, const uint16_t&, const int16_t& d) -> int16_t {
             static_mod_type<int16_t> answer(mod_limit);
             answer += x + d;
             return int16_t(answer);
         }},
        {'g',
         [](const int16_t& x, const uint16_t&, const int16_t& d) -> int16_t {
             static_mod_type<int16_t> answer(mod_limit);
             answer += x - d;
             return int16_t(answer);
         }},
        {'b',
         [](const int16_t& x, const uint16_t&, const int16_t& d) -> int16_t {
             static_mod_type<int16_t> answer(mod_limit);
             answer += (2 * x) - d;
             return int16_t(answer);
         }},
        {'c',
         [](const int16_t& x, const uint16_t& s, const int16_t& d) -> int16_t {
             static_mod_type<int16_t> answer(mod_limit);
             answer += d - x - (s * 8);
             return int16_t(answer);
         }},
        {'m',
         [](const int16_t& x, const uint16_t& s, const int16_t&) -> int16_t {
             static_mod_type<int16_t> answer(mod_limit);
             answer += (3 * pow(s, 3)) - (2 * x);
             return int16_t(answer);
         }},
        {'y',
         [](const int16_t& x, const uint16_t& s, const int16_t& d) -> int16_t {
             static_mod_type<int16_t> answer(mod_limit);
             answer += (x + d) - (s * 6);
             return int16_t(answer);
         }},
};

int16_t one_color_flash(const std::string& flash,
                        const std::vector<mod_type<int16_t>>& alpha,
                        const uint16_t& step, const int16_t& delta) {
    assert(flash.length() == 1);

    int16_t answer = color_to_function_map.at(flash[0])(
        int16_t(alpha[step - 1]), step, delta);

    return answer;
}

int16_t two_color_flash(const std::string& flash,
                        const std::vector<mod_type<int16_t>>& alpha,
                        const uint16_t& step, const int16_t& delta) {
    assert(flash.length() == 2);

    const uint16_t color_mix_value = primary_secondary_mix(flash);
    std::vector<int16_t> answers;

    std::for_each(flash.begin(), flash.end(), [&](const char& ch) {
        answers.push_back(color_to_function_map.at(ch)(int16_t(alpha[step - 1]),
                                                       step, delta));
    });

    static_mod_type<int16_t> answer(mod_limit);

    switch (color_mix_value) {
        case 2:
            answer += std::max(answers.front(), answers.back());
            break;
        case 3:
            answer += answers.front() + answers.back() - (delta * 2);
            break;
        case 4:
            answer += std::min(answers.front(), answers.back());
            break;
        default:
            assert(false);
    }

    return int16_t(answer);
}

int16_t three_color_flash(const std::string& flash,
                          const std::vector<mod_type<int16_t>>& alpha,
                          const uint16_t& step, const int16_t& delta) {
    assert(flash.length() == 3);

    uint16_t color_mix_value = primary_secondary_mix(flash);
    static_mod_type<int16_t> answer(mod_limit);

    if (color_mix_value == 3) {
        answer += int16_t(alpha[step - 1]) + int16_t(alpha[0]);
    } else if (color_mix_value == 4 || color_mix_value == 5) {
        std::vector<int16_t> color_calculations;

        std::for_each(flash.begin(), flash.end(), [&](const char& ch) {
            color_calculations.push_back(color_to_function_map.at(ch)(
                int16_t(alpha[step - 1]), step, delta));
        });

        switch (color_mix_value) {
            case 4:
                answer += *std::max_element(color_calculations.begin(),
                                            color_calculations.end());
                break;
            case 5:
                answer += *std::min_element(color_calculations.begin(),
                                            color_calculations.end());
                break;
        }
    } else {
        answer += int16_t(alpha[step - 1]) - int16_t(alpha[0]);
    }

    return int16_t(answer);
}

}  // namespace

int16_t one_calculations(const std::string& flash,
                         const std::vector<mod_type<int16_t>>& alpha,
                         const uint16_t& step, const int16_t& delta) {
    assert(flash.length() <= 3);

    int16_t answer;

    switch (uint16_t(flash.length())) {
        case 1:
            answer = one_color_flash(flash, alpha, step, delta);
            break;
        case 2:
            answer = two_color_flash(flash, alpha, step, delta);
            break;
        case 3:
            answer = three_color_flash(flash, alpha, step, delta);
            break;
        default:
            assert(false);
    }

    return answer;
}

}  // namespace stages