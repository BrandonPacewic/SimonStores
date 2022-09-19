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

#include <array>
#include <iostream>
#include <vector>

#include "src/math/balanced_ternary_converter.h"
#include "src/math/base_36_type.h"
#include "src/math/mod_type.h"
#include "src/ruleset/color_sequence.h"
#include "src/ruleset/inital_calculations.h"
#include "src/stages/stage_one.h"
#include "src/stages/stage_three.h"
#include "src/stages/stage_two.h"
#include "src/user_handling/user_input.h"

constexpr uint16_t stage_one_flashes = 3;
constexpr uint16_t stage_two_flashes = 4;
constexpr uint16_t total_flashes = 5;

int main() {
    do {
        std::cout << "Enter the Serial#(Ex: 12qmt0): ";
        std::string serial = user_input::input_check(6);
        base_36::base_36_type serial_base(serial);

        std::cout << "Enter the Order of the Colors"
                     " in Clockwise Order(Ex: rmybcg): ";
        std::string color_order = user_input::input_check(6);
        color_sequence::setup(color_order);

        std::array<std::string, total_flashes> stage_flashes;

        for (uint16_t i = 0; i < stage_one_flashes; ++i) {
            std::cout << "Enter flash #" << i + 1 << "(EX: rmy): ";
            stage_flashes[i] = user_input::input_check(-1, 1, 3);
        }

        std::vector<mod_types::mod_type<int16_t>> alpha(5, 0), bravo(6, 0),
            charlie(7, 0);

        alpha.front() = inital_calculations::alpha(serial_base);
        bravo.front() = inital_calculations::bravo(serial_base);
        charlie.front() = inital_calculations::charlie(serial_base);
        const int16_t delta = inital_calculations::delta(serial_base);

        uint16_t current_stage = 1;

        for (uint16_t step = 1; step <= stage_one_flashes; ++step) {
            alpha[step] = stages::one_calculations(stage_flashes[step - 1],
                                                   alpha, step, delta);
        }

        std::cout << color_sequence::determine_stage_color_sequence(
                         current_stage)
                  << '\n';
        auto stage_ternary = ternary::balanced_convert(int16_t(alpha[3]));
        std::cout << stage_ternary << std::endl;
        ++current_stage;

        std::cout << "Enter flash #" << stage_two_flashes << "(EX: rmy): ";
        stage_flashes[stage_two_flashes - 1] =
            user_input::input_check(-1, 1, 3);

        for (uint16_t step = 1; step <= stage_two_flashes; ++step) {
            alpha[step] = stages::two_calculations(stage_flashes[step - 1],
                                                   alpha, bravo, step, delta);
        }

        std::cout << color_sequence::determine_stage_color_sequence(
                         current_stage)
                  << '\n';
        stage_ternary = ternary::balanced_convert(int16_t(bravo[4]));
        std::cout << stage_ternary << std::endl;
        ++current_stage;

        std::cout << "Enter flash #" << total_flashes << "(EX: rmy): ";
        stage_flashes[total_flashes - 1] = user_input::input_check(-1, 1, 3);

        for (uint16_t step = 1; step <= total_flashes; ++step) {
            charlie[step] = stages::three_calculations(
                stage_flashes[step - 1], alpha, bravo, charlie, step, delta);
        }

        std::cout << color_sequence::determine_stage_color_sequence(
                         current_stage)
                  << '\n';
        stage_ternary = ternary::balanced_convert(int16_t(charlie[5]));
        std::cout << stage_ternary << std::endl;
        ++current_stage;
    } while ([]() -> bool {
        char input;
        std::cout << "Enter 0 to quit or 1 to continue: ";
        std::cin >> input;

        while (input != '0' || input != '1') {
            std::cout << "You did not enter a valid input. "
                         "Please try again: ";
            std::cin >> input;
        }

        return (input == '0') ? false : true;
    });

    return 0;
}