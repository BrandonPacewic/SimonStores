#include <iterator>
#include <string>
#include <cmath>
#include <array>
#include <algorithm>
#include <cassert>
#include "colorDetermineFunctions.hpp"

class stageOne {
private:
    static const int INF = int(1e9) + 5;
    static const int modOperator = 364;

    static int stageFunctions(const char color, const int X, const int S, const int D) {
        int Y;

        switch (tolower(color)) {
        case 'r':
            Y = X + D;
            break;

        case 'g':
            Y = X - D;
            break;

        case 'b':
            Y = (2 * X) - D;
            break;

        case 'c':
            Y = D - X - (S * 8);
            break;

        case 'm':
            Y = (3 * pow(S, 3)) - (2 * X);
            break;

        case 'y':
            Y = (X + D) - (S * 6);
            break;
        }

        Y %= modOperator;

        return Y;
    }

    static int oneColorFlash(const std::string flash, const std::vector<int> A, const int S, const int D) {
        assert(flash.length() == 1);

        return stageFunctions(flash[0], A[S - 1], S, D);
    }

    static int twoColorFlash(const std::string flash, const std::vector<int> A, const int S, const int D) {
        assert(flash.length() == 2);

        int colorMixValue = colorDetermine::primaryVsSecondaryMix(flash);

        int colorOneValue = stageFunctions(flash[0], A[S - 1], S, D);
        int colorTwoValue = stageFunctions(flash[1], A[S - 1], S, D);

        switch (colorMixValue) {
            case 2:
                return std::max(colorOneValue, colorTwoValue);

            case 3:
                return colorOneValue + colorTwoValue - (D * 2);

            case 4:
                return std::min(colorOneValue, colorTwoValue);

            default:
                return -INF;
        }
    }

    static int threeColorFlash(const std::string flash, const std::vector<int> A, const int S, const int D) {
        assert(flash.length() == 3);

        int colorMixValue = colorDetermine::primaryVsSecondaryMix(flash);

        if (colorMixValue == 3) {
            return (A[S - 1] + A[0]) % modOperator;
        
        } else if (colorMixValue == 4 || colorMixValue == 5) {
            //3 is == to flash.length()
            std::array<int, 3> colorValues;

            for (int i = 0; i < flash.length(); i++) {
                colorValues[i] = stageFunctions(flash[i], A[S - 1], S, D);
            }

            switch (colorMixValue) {
                case 4:
                    return int(std::max_element(colorValues.begin(), colorValues.end()) - colorValues.begin());

                case 5:
                    return int(std::min_element(colorValues.begin(), colorValues.end()) - colorValues.begin());

                default:
                    return -INF;
            }

        } else {
            return (A[S - 1] - A[0]) % modOperator;
        }
    }

public:
    static int stageOneCalculations(const std::string flash, const std::vector<int> A, const int S, const int D) {
        assert(flash.length() <= 3);

        switch (flash.length()) {
            case 1:
                return oneColorFlash(flash, A, S, D);

            case 2:
                return twoColorFlash(flash, A, S, D);

            case 3:
                return threeColorFlash(flash, A, S, D);

            default:
                return -INF;
        }
    }
};