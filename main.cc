/*
 * Copyright (c) 2022 Brandon Pacewic
 *
 * Developed and tested by Brandon Pacewic
 * 
 * main file for SimonStores
 */

#include <array>
#include <iostream>
#include <vector>

#include "include/module_necessities.h"

constexpr int stage_one_flashes = 3;
constexpr int stage_two_flashes = 4;
constexpr int total_flashes = 5;

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

        for (int i = 0; i < stage_one_flashes; ++i) {
            std::cout << "Enter flash #" << i + 1 << "(EX: rmy): ";
            stage_flashes[i] = user_input::input_check(-1, 1, 3);
        }

        std::vector<
            mod_types::mod_type<int>
        > alpha(5, 0), bravo(6, 0), charlie(7, 0);

        alpha.front() = inital_calculations::alpha(serial_base);
        bravo.front() = inital_calculations::bravo(serial_base);
        charlie.front() = inital_calculations::charlie(serial_base);
        const int delta = inital_calculations::delta(serial_base);

        // Stage One
        for (int step = 1; step <= stage_one_flashes; ++step) {
            alpha[step] = stages::one_calculations(
                stage_flashes[step-1], alpha, step, delta
            );
        }

        color_sequence::print_stage_color_sequence(1); // stage#
        auto stage_ternary = ternary::balanced_convert(int(alpha[3]));

        // Stage Two
        for (int step = 1; step <= stage_two_flashes; ++step) {
            alpha[step] = stages::two_calculations(
                stage_flashes[step-1], alpha, bravo, step, delta
            );
        }

        color_sequence::print_stage_color_sequence(2); // stage#
        stage_ternary = ternary::balanced_convert(int(bravo[4]));

        // Stage Three
        for (int step = 1; step <= total_flashes; ++step) {
            charlie[step] = stages::three_calculations(
                stage_flashes[step-1], alpha, bravo, charlie, step, delta
            );
        }

        color_sequence::print_stage_color_sequence(3); // stage#
        stage_ternary = ternary::balanced_convert(int(charlie[5]));

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