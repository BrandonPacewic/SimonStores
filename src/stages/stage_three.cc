/* MIT License
 *
 * Copyright (c) 2022 Brandon Pacewic
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "stage_three.h"

#include <algorithm>
#include <array>
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

using color_determine::primary_secondary_mix;
using mod_types::mod_type;
using mod_types::static_mod_type;

using nato_type = std::vector<mod_type<int16_t>>;

namespace stages {
namespace {

constexpr uint16_t mod_limit = 365;

const std::unordered_map<
    char,
    std::function<int16_t(nato_type, nato_type, int16_t, uint16_t, int16_t)>>
    color_to_function_map = {
        {'r',
         [](const nato_type& a, const nato_type& b, const int16_t& x,
            const uint16_t& s, const int16_t& d) -> int16_t {
             static_mod_type<int16_t> answer(mod_limit);
             answer += x + int16_t(b[s - 1]) - int16_t(a[s - 1]);
             return int16_t(answer);
         }},
        {'g',
         [](const nato_type& a, const nato_type& b, const int16_t& x,
            const uint16_t& s, const int16_t& d) -> int16_t {
             static_mod_type<int16_t> answer(mod_limit);
             answer += x - (int16_t(b[s - 1]) * 2);
             return int16_t(answer);
         }},
        {'b',
         [](const nato_type& a, const nato_type& b, const int16_t& x,
            const uint16_t& s, const int16_t& d) -> int16_t {
             static_mod_type<int16_t> answer(mod_limit);
             answer += x + int16_t(b[0]) - int16_t(a[3]);
             return int16_t(answer);
         }},
        {'c',
         [](const nato_type& a, const nato_type& b, const int16_t& x,
            const uint16_t& s, const int16_t& d) -> int16_t {
             static_mod_type<int16_t> answer(mod_limit);
             answer += x - int16_t(b[s - 1]) + int16_t(a[s - 1]);
             return int16_t(answer);
         }},
        {'m',
         [](const nato_type& a, const nato_type& b, const int16_t& x,
            const uint16_t& s, const int16_t& d) -> int16_t {
             static_mod_type<int16_t> answer(mod_limit);
             answer += x - (int16_t(a[s - 1]) * 2);
             return int16_t(answer);
         }},
        {'y',
         [](const nato_type& a, const nato_type& b, const int16_t& x,
            const uint16_t& s, const int16_t& d) -> int16_t {
             static_mod_type<int16_t> answer(mod_limit);
             answer += x + int16_t(b[4]) - int16_t(a[0]);
             return int16_t(answer);
         }},
};

int16_t one_color_flash(const std::string& flash, const nato_type& alpha,
                        const nato_type& bravo, const nato_type& charlie,
                        const uint16_t& step, const int16_t& delta) {
    assert(flash.length() == 1);

    int16_t answer = color_to_function_map.at(flash[0])(
        alpha, bravo, int16_t(charlie[step - 1]), step, delta);

    return answer;
}

int16_t two_color_flash(const std::string& flash, const nato_type& alpha,
                        const nato_type& bravo, const nato_type& charlie,
                        const uint16_t& step, const int16_t& delta) {
    assert(flash.length() == 2);

    const uint16_t color_mix_value = primary_secondary_mix(flash);
    static_mod_type<int16_t> answer(mod_limit);

    if (color_mix_value == 2) {
        const char absent_color = color_determine::missing_color(flash);

        answer += (color_to_function_map.at(absent_color)(
                       alpha, bravo, int16_t(charlie[step - 1]), step, delta) +
                   color_to_function_map.at(absent_color)(
                       alpha, bravo, int16_t(bravo[step - 1]), step, delta) +
                   color_to_function_map.at(absent_color)(
                       alpha, bravo, int16_t(alpha[step - 1]), step, delta));
    } else if (color_mix_value == 3) {
        std::vector<int16_t> color_values(flash.length() + 1);

        color_values[0] = color_to_function_map.at(flash[0])(
            alpha, bravo, int16_t(charlie[step - 1]), step, delta);
        color_values[1] = color_to_function_map.at(flash[1])(
            alpha, bravo, int16_t(charlie[step - 1]), step, delta);
        color_values[2] = -abs(color_values[0] - color_values[1]);

        answer += *std::min_element(color_values.begin(), color_values.end());
    } else {
        const char absent_color = color_determine::missing_color(flash);

        answer += (color_to_function_map.at(absent_color)(
                       alpha, bravo, int16_t(charlie[step - 1]), step, delta) -
                   color_to_function_map.at(flash[0])(
                       alpha, bravo, int16_t(charlie[step - 1]), step, delta) -
                   color_to_function_map.at(flash[1])(
                       alpha, bravo, int16_t(charlie[step - 1]), step, delta));
    }

    return int16_t(answer);
}

int16_t three_color_flash(const std::string& flash, const nato_type& alpha,
                          const nato_type& bravo, const nato_type& charlie,
                          const uint16_t& step, const int16_t& delta) {
    assert(flash.length() == 3);

    const uint16_t color_mix_value = primary_secondary_mix(flash);
    static_mod_type<int16_t> answer(mod_limit);

    if (color_mix_value == 3) {
        answer += int16_t(
            (charlie[step - 1] + ((charlie[step - 1] % 3) * charlie[0])) -
            (((bravo[step - 1] % 3 * bravo[0])) +
             (((alpha[step - 1] % 3) * alpha[0]))));
    } else if (color_mix_value == 4) {
        std::vector<int16_t> color_values(flash.length() + 2, 0);

        for (uint16_t i = 0; i < uint16_t(flash.length()); ++i) {
            if (color_determine::is_primary(flash[i])) {
                color_values[i] = color_to_function_map.at(flash[i])(
                    alpha, bravo, int16_t(charlie[step - 1]), step, delta);
            } else {
                color_values[3] = color_to_function_map.at(flash[i])(
                    alpha, bravo, int16_t(bravo[step - 1]), step, delta);
                color_values[4] = color_to_function_map.at(flash[i])(
                    alpha, bravo, int16_t(alpha[step - 1]), step, delta);
            }
        }

        answer += std::accumulate(color_values.begin(), color_values.end(), 0);
    } else if (color_mix_value == 5) {
        std::vector<int16_t> color_values(flash.length() + 2, 0);

        for (uint16_t i = 0; i < uint16_t(flash.length()); ++i) {
            if (color_determine::is_secondary(flash[i])) {
                color_values[i] = color_to_function_map.at(flash[i])(
                    alpha, bravo, int16_t(charlie[step - 1]), step, delta);
            } else {
                color_values[3] = color_to_function_map.at(flash[i])(
                    alpha, bravo, int16_t(bravo[step - 1]), step, delta);
                color_values[4] = color_to_function_map.at(flash[i])(
                    alpha, bravo, int16_t(alpha[step - 1]), step, delta);
            }
        }

        answer += std::accumulate(color_values.begin(), color_values.end(), 0);
    } else {
        answer += int16_t(
            (charlie[step - 1] + ((charlie[0] % 3) * charlie[step - 1])) -
            ((bravo[0] % 3) * bravo[step - 1]) +
            ((alpha[0] % 3) * alpha[step - 1]));
    }

    return int16_t(answer);
}

}  // namespace

int16_t three_calculations(const std::string& flash, const nato_type& alpha,
                           const nato_type& bravo, const nato_type& charlie,
                           const uint16_t& step, const int16_t& delta) {
    assert(flash.length() <= 3);

    uint16_t answer;

    switch (flash.length()) {
        case 1:
            answer = one_color_flash(flash, alpha, bravo, charlie, step, delta);
            break;
        case 2:
            answer = two_color_flash(flash, alpha, bravo, charlie, step, delta);
            break;
        case 3:
            answer =
                three_color_flash(flash, alpha, bravo, charlie, step, delta);
            break;
        default:
            assert(false);
    }

    return answer;
}

}  // namespace stages