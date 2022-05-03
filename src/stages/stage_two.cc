/*
 * Copyright (c) 2022 Brandon Pacewic
 *
 * Developed and tested by Brandon Pacewic
 *
 * stage_two.cc
 */

#include "stage_two.h"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <functional>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

#include "../math/mod_type.h"
#include "../math/static_mod_type.h"
#include "../ruleset/color_determine.h"

using color_determine::missing_color;
using color_determine::primary_secondary_mix;
using mod_types::mod_type;
using mod_types::static_mod_type;

namespace stages {
namespace {

constexpr uint16_t mod_limit = 365;

const std::unordered_map<char,
                         std::function<int16_t(std::vector<mod_type<int16_t>>,
                                               int16_t, uint16_t, int16_t)>>
    color_to_function_map = {
        {'r',
         [](const std::vector<mod_type<int16_t>>& a, const int16_t& x,
            const uint16_t& s, const int16_t& d) -> int16_t {
             static_mod_type<int16_t> answer(mod_limit);
             answer += x + int16_t(a[s - 1]) + pow(s, 2);
             return int16_t(answer);
         }},
        {'g',
         [](const std::vector<mod_type<int16_t>>& a, const int16_t& x,
            const uint16_t& s, const int16_t& d) -> int16_t {
             static_mod_type<int16_t> answer(mod_limit);
             answer += (x * 2) - int16_t(a[s - 1]);
             return int16_t(answer);
         }},
        {'b',
         [](const std::vector<mod_type<int16_t>>& a, const int16_t& x,
            const uint16_t& s, const int16_t& d) -> int16_t {
             static_mod_type<int16_t> answer(mod_limit);
             answer += (x * 2) - int16_t(a[0]) - (4 * pow(s, 2));
             return int16_t(answer);
         }},
        {'c',
         [](const std::vector<mod_type<int16_t>>& a, const int16_t& x,
            const uint16_t& s, const int16_t& d) -> int16_t {
             static_mod_type<int16_t> answer(mod_limit);
             answer += x + int16_t(a[1]);
             return int16_t(answer);
         }},
        {'m',
         [](const std::vector<mod_type<int16_t>>& a, const int16_t& x,
            const uint16_t& s, const int16_t& d) -> int16_t {
             static_mod_type<int16_t> answer(mod_limit);
             answer += x + int16_t(a[2]) - d;
             return int16_t(answer);
         }},
        {'y',
         [](const std::vector<mod_type<int16_t>>& a, const int16_t& x,
            const uint16_t& s, const int16_t& d) -> int16_t {
             static_mod_type<int16_t> answer(mod_limit);
             answer += x + int16_t(a[3] - a[s - 1]);
             return int16_t(answer);
         }},
};

int one_color_flash(const std::string& flash,
                    const std::vector<mod_type<int16_t>>& alpha,
                    const std::vector<mod_type<int16_t>>& bravo,
                    const uint16_t& step, const int16_t& delta) {
    assert(flash.length() == 1);

    int16_t answer = color_to_function_map.at(flash[0])(
        alpha, int16_t(bravo[step - 1]), step, delta);

    return answer;
}

int two_color_flash(const std::string& flash,
                    const std::vector<mod_type<int16_t>>& alpha,
                    const std::vector<mod_type<int16_t>>& bravo,
                    const uint16_t& step, const int16_t& delta) {
    assert(flash.length() == 2);

    const uint16_t color_mix_value = primary_secondary_mix(flash);
    static_mod_type<int16_t> answer(mod_limit);

    if (color_mix_value == 2 || color_mix_value == 3) {
        std::vector<int16_t> answers;

        std::for_each(flash.begin(), flash.end(), [&](const char& ch) {
            answers.push_back(color_to_function_map.at(ch)(
                alpha, int16_t(bravo[step - 1]), step, delta));
        });

        if (color_mix_value == 2) {
            answer += abs(answers.front() - answers.back());
        } else {
            answer += (4 * delta) - abs(answers.front() - answers.back());
        }
    } else {
        assert(color_mix_value == 4);

        const char absent_color = missing_color(flash);
        const int16_t first = color_to_function_map.at(absent_color)(
            alpha, int16_t(alpha[step - 1]), step, delta);
        const int16_t second = color_to_function_map.at(absent_color)(
            alpha, int16_t(bravo[step - 1]), step, delta);

        answer += std::min(first, second);
    }

    return int16_t(answer);
}

int three_color_flash(const std::string& flash,
                      const std::vector<mod_type<int16_t>>& alpha,
                      const std::vector<mod_type<int16_t>>& bravo,
                      const uint16_t& step, const int16_t& delta) {
    assert(flash.length() == 3);

    const uint16_t color_mix_value = primary_secondary_mix(flash);
    static_mod_type<int16_t> answer(mod_limit);

    if (color_mix_value == 3) {
        answer += int16_t(bravo[step - 1] + ((bravo[step - 1] % 4) * bravo[0]) -
                          alpha[3]);
    } else if (color_mix_value == 4) {
        std::vector<int16_t> color_values(flash.length() + 1, 0);

        for (uint16_t i = 0; i < uint16_t(flash.length()); ++i) {
            if (color_determine::is_primary(flash[i])) {
                color_values[i] = color_to_function_map.at(flash[i])(
                    alpha, int16_t(bravo[step - 1]), step, delta);
            } else {
                color_values[3] = color_to_function_map.at(flash[i])(
                    alpha, int16_t(alpha[step - 1]), step, delta);
            }
        }

        answer +=
            int16_t(bravo[step - 1] + std::accumulate(color_values.begin(),
                                                      color_values.end(), 0));
    } else if (color_mix_value == 5) {
        std::vector<int> color_values(flash.length() + 1, 0);

        for (uint16_t i = 0; i < uint16_t(flash.length()); ++i) {
            if (color_determine::is_secondary(flash[i])) {
                color_values[i] = color_to_function_map.at(flash[i])(
                    alpha, int16_t(bravo[step - 1]), step, delta);
            } else {
                color_values[i] = color_to_function_map.at(flash[i])(
                    alpha, int16_t(alpha[step - 1]), step, delta);
            }
        }

        answer +=
            int16_t(bravo[step - 1] + std::accumulate(color_values.begin(),
                                                      color_values.end(), 0));
    } else {
        answer += int16_t(bravo[step - 1] + ((bravo[0] % 4) * bravo[step - 1]) -
                          alpha[3]);
    }

    return int16_t(answer);
}

}  // namespace

int16_t two_calculations(const std::string& flash,
                         const std::vector<mod_type<int16_t>>& alpha,
                         const std::vector<mod_type<int16_t>>& bravo,
                         const uint16_t& step, const int16_t& delta) {
    assert(flash.length() <= 3);

    int16_t answer = -999;

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
        default:
            assert(false);
    }

    return answer;
}

}  // namespace stages