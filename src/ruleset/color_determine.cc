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

#include "color_determine.h"

#include <algorithm>
#include <string>
#include <unordered_map>
#include <unordered_set>

namespace color_determine {

uint16_t primary_secondary_mix(const std::string& flash) {
    const std::unordered_set<char> primary_colors = {'r', 'g', 'b'};
    uint16_t total_value = 0;

    std::for_each(flash.begin(), flash.end(), [&](const char& ch) {
        if (primary_colors.count(ch)) {
            total_value += 1;
        } else {
            total_value += 2;
        }
    });

    return total_value;
}

char missing_color(const std::string& flash) {
    const std::unordered_map<char, uint16_t> color_to_value_map = {
        {'r', 1}, {'g', 2}, {'b', 3}, {'c', 4}, {'m', 5}, {'y', 6}};

    uint16_t total_color_value = 0;

    std::for_each(flash.begin(), flash.end(), [&](const char& ch) {
        total_color_value += color_to_value_map.find(ch)->second;
    });

    char answer;

    switch (total_color_value) {
        case 5:
            answer = 'r';
            break;
        case 4:
            answer = 'g';
            break;
        case 3:
            answer = 'b';
            break;
        case 11:
            answer = 'c';
            break;
        case 10:
            answer = 'm';
            break;
        case 9:
            answer = 'y';
            break;
        default:
            answer = '?';
            break;
    }

    return answer;
}

const bool is_primary(const char& color) {
    const std::string primarys = "rbg";
    return primarys.find(color) != std::string::npos;
}

const bool is_secondary(const char& color) {
    const std::string secondarys = "cmy";
    return secondarys.find(color) != std::string::npos;
}

}  // namespace color_determine