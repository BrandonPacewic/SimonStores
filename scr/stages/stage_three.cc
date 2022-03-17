/*
 * Copyright (c) 2022 Brandon Pacewic
 *
 * Developed and tested by Brandon Pacewic
 * 
 * stage_three.cc
 */

#ifndef _STAGE_THREE_C
#define _STAGE_THREE_C 1

#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

#include "../math/mod_type.h"
using mod_types::mod_type;

#include "../math/static_mod_type.h"
using mod_types::static_mod_type;

namespace stages {

namespace {

constexpr int mod_limit = 365;

const std::unordered_map<
    char, std::function<int(
        std::vector<mod_type<int>>, std::vector<mod_type<int>>, int, int, int
    )>
> color_to_function_map = {
    {'r', [](const std::vector<mod_type<int>>& a , 
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



} // namespace

} // namespace stages

#endif // _STAGE_THREE_C