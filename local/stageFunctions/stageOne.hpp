#include <array>
#include <vector>
#include <cmath>

class stageOne {
private:
    static const int modOperator = 364;

    static int local_stageOneFunctions(const char color, const int X, const int S, const int D) {
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
};