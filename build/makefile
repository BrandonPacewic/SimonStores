# *
# * Copyright {c} 2022 Brandon Pacewic
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

# Math object files
balanced_ternary_converter.o: ${MATH}/balanced_ternary_converter.cc ${INCLUDE}/balanced_ternary_converter.h
	${CPP} ${DEBUG} -c ${MATH}/balanced_ternary_converter.cc -o balanced_ternary_converter.o

base_36_type.o: ${MATH}/base_36_type.cc ${INCLUDE}/base_36_type.h
	${CPP} ${DEBUG} -c ${MATH}/base_36_type.cc -o base_36_type.o

mod_type.o: ${MATH}/mod_type.cc ${INCLUDE}/mod_type.h
	${CPP} ${DEBUG} -c ${MATH}/mod_type.cc -o mod_type.o

static_mod_type.o: ${MATH}/static_mod_type.cc ${INCLUDE}/static_mod_type.h
	${CPP} ${DEBUG} -c ${MATH}/static_mod_type.cc -o static_mod_type.o

