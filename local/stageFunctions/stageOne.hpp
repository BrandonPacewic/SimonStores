#include <string>
#include <cmath>
#include <cassert>

#include "colorDetermineFunctions.hpp"
using namespace colorDetermine;

class stageOne {
private:
    static const int modOperator = 364;

    static int local_stageFunctions(const char color, const int X, const int S, const int D) {
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

        return local_stageFunctions(flash[0], A[S - 1], S, D);
    }

    static int twoColorFlash(const std::string flash, const int X, const int S, const int D) {
        assert(flash.length() == 2);

        int colorMixValue = primaryVsSecondaryMix(flash);

        
    }

public:


};