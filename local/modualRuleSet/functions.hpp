#include <iostream>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>


class LOCAL_FUNCTIONS {
private:

    template<typename T> T abs(T num) {
        return num < 0 ? num *= -1 : num;
    }

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
                        break; //TODO: breaks might need to be changed to continue

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
            for (auto &cl : stageColorSequence) {
                switch (tolower(cl)) {
                    case 'r':
                        cl = 'g';
                        break;

                    case 'g':
                        cl = 'b';
                        break;

                    case 'b':
                        cl = 'r';
                        break;
                }
            }
        }
    }

    void cycleSecondary(const std::unordered_map<char, int> colorMap, std::string &stageColorSequence) {
        if (colorMap.find('m') -> second == 2 || colorMap.find('m') -> second == 3) {
            for (auto &cl : stageColorSequence) {
                switch (tolower(cl)) {
                    case 'c':
                        cl = 'm';
                        break;

                    case 'm':
                        cl = 'y';
                        break;

                    case 'y':
                        cl = 'c';
                        break;
                }
            }
        }
    }

    void swapBlueOpposite(const std::unordered_map<char, int> colorMap, std::string &stageColorSequence) {
        if ((colorMap.find('b') -> second <= 2 && colorMap.find('y') -> second <= 2) || (colorMap.find('b') -> second > 2 && colorMap.find('y') -> second > 2)) {
            
        }
    }

    void swapRedAndYellow(const std::unordered_map<char, int> colorMap, std::string &stageColorSequence) {
        if (colorMap.find('r') -> second <= 2) {
            
        }
    }

    //function for re-ordering color list for input
    void local_colorSumbitingOrder(const std::string colorOrder, std::string colorStage) {


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