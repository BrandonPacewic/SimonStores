/*
 * Copyright (c) 2022 Brandon Pacewic
 *
 * Developed and tested by Brandon Pacewic
 * 
 * stage_two.h
 */

#pragma once
#ifndef _STAGE_TWO_H
#define _STAGE_TWO_H 1

#include <string>
#include <vector>

namespace stages {

    int two_calculations(const std::string& flash, 
        const std::vector<int>& alpha, const int& step, const int& delta);

} // namespace stages

#endif // _STAGE_TWO_H

{
    "version": "2.0.0",
    "tasks": [
        {
            "type": "shell",
            "label": "g++ build active file",
            "command": "/usr/bin/g++",
            "args": ["-g", "${file}", "-o", "${fileDirname}/${fileBasenameNoExtension}"],
            "options": {
                "cwd": "/usr/bin"
            },
            "problemMatcher": ["$gcc"],
            "group": {
                "kind": "build",
                "isDefault": true
            }
        }
    ]
}