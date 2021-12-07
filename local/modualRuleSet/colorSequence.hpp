#include <iostream>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>
#include <cassert>

class colorSequence {
private:
    template<typename T> T abs(T num) {
        return num < 0 ? num *= -1 : num;
    }

    static std::unordered_map<char, int> createColorMap(const std::string colorOrder) {
        std::unordered_map<char, int> colorMap;

        for (int i = 0; i < colorOrder.length(); i++) {
            colorMap[tolower(colorOrder[i])] = i;
        }

        return colorMap;
    }

    static void shiftRight(const std::unordered_map<char, int> colorMap, std::string &stageColorSequence) {
        if (colorMap.find('y') -> second == 0) {
            for (int i = 1; i < stageColorSequence.length(); i++) {
                char temp = stageColorSequence[i];
                stageColorSequence[i] = stageColorSequence[0];
                stageColorSequence[i] = temp;
            }
        }
    }

    static void swapComplementary(const std::unordered_map<char, int> colorMap, std::string &stageColorSequence) {
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

    static void cyclePrimary(const std::unordered_map<char, int> colorMap, std::string &stageColorSequence) {
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

    static void cycleSecondary(const std::unordered_map<char, int> colorMap, std::string &stageColorSequence) {
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

    static void swapBlueOpposite(const std::unordered_map<char, int> colorMap, std::string &stageColorSequence) {
        if ((colorMap.find('b') -> second <= 2 && colorMap.find('y') -> second <= 2) || (colorMap.find('b') -> second > 2 && colorMap.find('y') -> second > 2)) {
            for (int i = 0; i < stageColorSequence.length(); i++) {
                if (tolower(stageColorSequence[i]) == 'b') {
                    int opposite = i > 2 ? i - 3 : i + 3;
                    stageColorSequence[i] = stageColorSequence[opposite];
                    stageColorSequence[opposite] = 'b';
                    break;
                }
            }
        }
    }

    static void swapRedAndYellow(const std::unordered_map<char, int> colorMap, std::string &stageColorSequence) {
        if (colorMap.find('r') -> second <= 2) {
            for (auto &cl : stageColorSequence) {
                if (tolower(cl) == 'y') {
                    cl = 'r';
                } else if (tolower(cl) == 'r') {
                    cl = 'y';
                }
            }
        }
    }

    static void swapGreenAndCyan(const std::unordered_map<char, int> colorMap, std::string &stageColorSequence) {
        if (colorMap.find('b') -> second > 2) {
            for (auto &cl : stageColorSequence) {
                if (tolower(cl) == 'g') {
                    cl = 'c';
                } else if (tolower(cl) == 'c') {
                    cl = 'g';
                }
            }
        }
    }

public:
    static std::string getbaseColorOrder(const int stage) {
        const std::string baseColorOrderStageOne = "rgbcmy";
        const std::string baseColorCrderStageTwo = "ybgmcr";
        const std::string baseColorOrderStageThree = "bmrygc";

        return stage == 1 ? baseColorOrderStageOne : stage == 2 ? baseColorCrderStageTwo : baseColorOrderStageThree;
    }

    static std::string createColorSubmittingOrder(const std::string colorOrder, std::string stageColorSequence) {
        std::unordered_map<char, int> colorMap = createColorMap(colorOrder);

        shiftRight(colorMap, stageColorSequence);

        swapComplementary(colorMap, stageColorSequence);

        cyclePrimary(colorMap, stageColorSequence);

        cycleSecondary(colorMap, stageColorSequence);

        swapBlueOpposite(colorMap, stageColorSequence);

        swapRedAndYellow(colorMap, stageColorSequence);

        swapGreenAndCyan(colorMap, stageColorSequence);

        return stageColorSequence;
    }

    static void printStageColorSequence(const int stage, const std::string colorOrder) {
        assert(stage == 1 || stage == 2 || stage == 3);

        std::string colorSequence = createColorSubmittingOrder(colorOrder, getbaseColorOrder(stage));

        std::cout << colorSequence << '\n';
    }
};