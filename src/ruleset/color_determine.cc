/*
 * Copyright (c) 2022 Brandon Pacewic
 *
 * Developed and tested by Brandon Pacewic
 *
 * color_determine.cc
 */

#include "color_determine.h"

#include <algorithm>
#include <numeric>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

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
    const std::unordered_map<char, int> color_to_value_map = {
        {'r', 1}, {'g', 2}, {'b', 3}, {'c', 4}, {'m', 5}, {'y', 6}};

    int total_color_value = 0;

    std::for_each(flash.begin(), flash.end(), [&](const char& ch) {
        total_color_value += color_to_value_map.find(ch)->second;
    });

    char answer = '\0';

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