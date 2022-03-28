# *
# * Copyright (c) 2022 Brandon Pacewic
# *
# * Developed and tested by Brandon Pacewic
# * 
# * MakeFile for Simon Stores
# *

# Options
CPP = gcc
DEBUG = # -g

# Expected File Directories
INCLUDE = ../include
MATH = ../src/math
RULESET = ../src/ruleset
STAGES = ../src/stages
USER_HANDLING = ../src/user_handling
MAIN = ..

# Main executable
# TODO: Create a list of all dependencies here
executable: main.o
	${CPP} ${DEBUG} main.o balanced_ternary_converter.o base_36_type.o 
	color_determine.o color_sequence.o inital_calculations.o mod_type.o 
	stage_one.o stage_two.o stage_three.o static_mod_type.o user_input.o -o main

# Math object files
balanced_ternary_converter.o: ${MATH}/balanced_ternary_converter.cc ${INCLUDE}/balanced_ternary_converter.h
	${CPP} ${DEBUG} -c ${MATH}/balanced_ternary_converter.cc -o balanced_ternary_converter.o

base_36_type.o: ${MATH}/base_36_type.cc ${INCLUDE}/base_36_type.h
	${CPP} ${DEBUG} -c ${MATH}/base_36_type.cc -o base_36_type.o

mod_type.o: ${MATH}/mod_type.cc ${INCLUDE}/mod_type.h
	${CPP} ${DEBUG} -c ${MATH}/mod_type.cc -o mod_type.o

static_mod_type.o: ${MATH}/static_mod_type.cc ${INCLUDE}/static_mod_type.h
	${CPP} ${DEBUG} -c ${MATH}/static_mod_type.cc -o static_mod_type.o

# Ruleset object files
color_determine.o: ${RULESET}/color_determine.cc ${INCLUDE}/color_determine.h
	${CPP} ${DEBUG} -c ${RULESET}/color_determine.cc -o color_determine.o

color_sequence.o: ${RULESET}/color_sequence.cc ${INCLUDE}/color_sequence.h
	${CPP} ${DEBUG} -c ${RULESET}/color_sequence.cc -o color_sequence.o

inital_calculations.o: ${RULESET}/inital_calculations.cc ${INCLUDE}/inital_calculations.h
	${CPP} ${DEBUG} -c ${RULESET}/inital_calculations.cc -o inital_calculations.o

# Stages object files
stage_one.o: ${STAGES}/stage_one.cc ${INCLUDE}/stage_one.h
	${CPP} ${DEBUG} -c ${STAGES}/stage_one.cc -o stage_one.o

stage_two.o: ${STAGES}/stage_two.cc ${INCLUDE}/stage_two.h
	${CPP} ${DEBUG} -c ${STAGES}/stage_two.cc -o stage_two.o

stage_three.o: ${STAGES}/stage_three.cc ${INCLUDE}/stage_three.h
	${CPP} ${DEBUG} -c ${STAGES}/stage_three.cc -o stage_three.o

user_input.o: ${USER_HANDLING}/user_input.cc ${INCLUDE}/user_input.h
	${CPP} ${DEBUG} -c ${USER_HANDLING}/user_input.cc -o user_input.o

main.o: ${MAIN}/main.cc
	${CPP} ${DEBUG} -c ${MAIN}/main.cc -o main.o