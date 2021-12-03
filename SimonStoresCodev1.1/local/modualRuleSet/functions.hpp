#include <iostream>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>


class LOCAL_FUNCTIONS {
private:

    std::unordered_map<char, int> createColorMap(const std::string &stageColorSequence) {
        std::unordered_map<char, int> colorMap;

        for (int i = 0; i < stageColorSequence.length(); i++) {
            colorMap[tolower(stageColorSequence[i])] = i;
        }

        return colorMap;
    }

    void shiftRight(const std::unordered_map<char, int> colorMap, std::string &stageColorSequence) {
        if (colorMap.find('y') -> second == 0) {
            for (int i = 1; i < stageColorSequence.length(); i++) {
                char temp = stageColorSequence[i];
                stageColorSequence[i] = stageColorSequence[0];
                stageColorSequence[i] = temp;
            }
        }
    }

    void swapComplementary(const std::unordered_map<char, int> colorMap, std::string &stageColorSequence) {
        if (colorMap.find('r') -> second + 3 == colorMap.find('c') -> second || colorMap.find('c') -> second + 3 == colorMap.find('r') -> second) {
            for (auto &cl : stageColorSequence) {
                switch (tolower(cl)) {
                    case 'r':
                        cl = 'c';
                        break; //breaks might need to be changed to continue

                    case 'c':
                        cl = 'r';
                        break;

                    case 'g':
                        cl = 'm';
                        break;

                    case 'm':
                        cl = 'g';
                        break;

                    case 'b':
                        cl = 'y';
                        break;

                    case 'y':
                        cl = 'b';
                        break;

                    default:
                        cl = 'X';
                }
            }
        }
    }

    void cyclePrimary(const std::unordered_map<char, int> colorMap, std::string &stageColorSequence) {
        if (colorMap.find('g') -> second == 0 || colorMap.find('g') -> second == 5) {
            for (int i = 0; i < stageColorSequence.length(); i++) {

            }
        }
    }



    //function for re-ordering color list for input
    void local_colorSumbitingOrder(const std::string colorOrder, std::string colorStage) {

        //find g and w in the string if they are adjacent cycle primary colors
        if (colorOrder[0] == 'g' || colorOrder[5] == 'g') {
            //cycle primary colors
            for (int i = 0; i < 6; i++) {
                if (colorStage[i] == 'r') {
                    colorStage[i] = 'g';
                } else if (colorStage[i] == 'g') {
                    colorStage[i] = 'b';
                } else if (colorStage[i] == 'b') {
                    colorStage[i] = 'r';
                }
            }
        }

        //find m if it is at 3 or 4 cycle secondary colors
        int m;
        if (colorOrder[2] == 'm' || colorOrder[3] == 'm') {
            //cycle secondary colors 
            for (int i = 0; i < 6; i++) {
                if (colorStage[i] == 'c') {
                    colorStage[i] = 'm';
                } else if (colorStage[i] == 'm') {
                    colorStage[i] = 'y';
                } else if (colorStage[i] == 'y') {
                    colorStage[i] = 'c';
                }
            }
        }

        //find b and y if they are on the same side swap blue with its opposite
        int b, y, bl; //if value is 1 its on the right if the value is 2 its on the left
        for (int i = 0; i < 6; i++) {
            if (colorOrder[i] == 'b') { 
                if (i <= 2) {
                    b = 2;
                } else {
                    b = 1;
                }
            }
            if (colorOrder[i] == 'y') {
                if (i <= 2) {
                    y = 2;
                } else {
                    y = 1;
                }
            }
        }

        if (b == 1 && y == 1 || b == 2 && y == 2) {
            for (int i = 0; i < 6; i++) {
                if (colorStage[i] == 'b') {
                    bl = i;
                }
            }
            //swap blue with its opposite
            int opp;
            char temp;
            if (bl == 0) {
                opp = 5;
            } else if (bl == 1) {
                opp = 4;
            } else if (bl == 2) {
                opp = 3;
            } else if (bl == 3) {
                opp = 2;
            } else if (bl == 4) {
                opp = 1;
            } else { 
                opp = 0;
            }

            temp = colorStage[opp];
            colorStage[opp] = 'b';
            colorStage[bl] = temp;
        }

        //if r is on the right swap r and y, we know r and y from a previous step
        if (r <= 2) {
            //swap r and y
            for (int i = 0; i < 6; i++) {
                if (colorStage[i] == 'y') {
                    colorStage[i] = 'r';
                } else if (colorStage[i] == 'r') {
                    colorStage[i] = 'y';
                }
            }
        }

        //if b is on the left side swap g and c, we know b from a previous step
        if (b == 1) {
            //swap g and c
            for (int i = 0; i < 6; i++) {
                if (colorStage[i] == 'g') {
                    colorStage[i] = 'c';
                } else if (colorStage[i] == 'c') {
                    colorStage[i] = 'g';
                }
            }
        }

        std::cout << colorStage << '\n';
    }

};