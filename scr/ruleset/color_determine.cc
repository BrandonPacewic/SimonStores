/*
 * Copyright (c) 2022 Brandon Pacewic
 *
 * Developed and tested by Brandon Pacewic
 * 
 * color_determine.cc
 */

#ifndef _COLOR_DETERMINE_C
#define _COLOR_DETERMINE_C 1

#include <numeric>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "color_determine.h"

namespace color_determine {

int primary_secondary_mix(const std::string& flash) {
    const std::unordered_set<char> primary_colors = {'r', 'g', 'b'};
    int total_value = 0;

    for (const auto& ch : flash) {
        if (primary_colors.count(ch)) {
            total_value += 1;
        }
        else {
            total_value += 2;
        }
    }

    return total_value;
}

char missing_color(const std::string& flash) {
    const std::unordered_map<char, int> color_to_value_map = {
        {'r', 1}, {'g', 2}, {'b', 3}, {'c', 4}, {'m', 5}, {'y', 6}
    };

    int total_color_value = 0;

    for (const auto& ch : flash) {
        total_color_value += color_to_value_map.find(ch)->second;
    }

    char answer = '\0';

    switch (total_color_value) {
        case 5:
            answer = 'r'; break;
        case 4:
            answer = 'g'; break;
        case 3:
            answer = 'b'; break;
        case 11:
            answer = 'c'; break;
        case 10:
            answer = 'm'; break;
        case 9:
            answer = 'y'; break;
    }

    return answer;
}

} // namespace color_determine

#endif // _COLOR_DETERMINE_C
