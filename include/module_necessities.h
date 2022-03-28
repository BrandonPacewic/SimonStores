/*
 * Copyright (c) 2022 Brandon Pacewic
 *
 * Developed and tested by Brandon Pacewic
 * 
 * module_necessities.h
 */

// Includes all the header files needed to run the main
// solver as well as the tests

#pragma once
#ifndef _MODULE_NECESSITIES_H
#define _MODULE_NECESSITIES_H 1

// math + math types
#include "balanced_ternary_converter.h"
#include "mod_type.h"
#include "static_mod_type.h"
#include "base_36_type.h"

// ruleset
#include "color_determine.h"
#include "color_sequence.h"
#include "inital_calculations.h"

// stages
#include "stage_one.h"
#include "stage_two.h"
#include "stage_three.h"

// user_handling
#include "user_input.h"

#endif // _MODULE_NECESSITIES_H