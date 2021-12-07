#include <array>
#include <string>
#include <cmath>
#include <algorithm>
#include <cassert>
#include <vector>
#include "colorDetermineFunctions.hpp"
#include "../math/modulo.hpp"

class stageThree {
private:
	static const int INF = int(1e9) + 5;
	static const int modOperator = 365;

	static int stageFunctions(const char color, const std::vector<int> A, const std::array<int, 6> B, const std::array<int, 7> C, const int X, const int S, const int D) {
		int Y;

		switch (tolower(color)) {
        case 'r':
            Y = X + B[S - 1] - A[S - 1];
            break;

        case 'g':
            Y = X - (B[S - 1] * 2);
            break;

        case 'b':
            Y = X + B[0] - A[3];
            break;

        case 'c':
            Y = X - B[S - 1] + A[S - 1];
            break;

        case 'm':
            Y = X - (A[S - 1] * 2);
            break;

        case 'y':
            Y = X + B[4] - A[0];
            break;
    	}

    	Y %= modOperator;

    	return Y;
	}

	static int oneColorFlash(const std::string flash, const std::vector<int> A, const std::array<int, 6> B, const std::array<int, 7> C, const int S, const int D) {
		assert(flash.length() == 1);

		return stageFunctions(flash[0], A, B, C, C[S - 1], S, D);
	}

	static int twoColorFlash(const std::string flash, const std::vector<int> A, const std::array<int, 6> B, const std::array<int, 7> C, const int S, const int D) {
		assert(flash.length() == 2);

		int colorMixValue = colorDetermine::primaryVsSecondaryMix(flash);

		if (colorMixValue == 2) {
			char missingColor = colorDetermine::missingColor(flash);

			return (stageFunctions(missingColor, A, B, C, C[S - 1], S, D) + stageFunctions(missingColor, A, B, C, B[S - 1], S, D) + stageFunctions(missingColor, A, B, C, A[S - 1], S, D)) % modOperator;
		
		} else if (colorMixValue == 3) {
			int colorValueOne = stageFunctions(flash[0], A, B, C, C[S - 1], S, D);
			int colorValueTwo = stageFunctions(flash[1], A, B, C, C[S - 1], S, D);
			int colorValueThree = -1 * abs(colorValueOne - colorValueTwo);

			return std::min({colorValueOne, colorValueTwo, colorValueThree});
		}

		char missingColor = colorDetermine::missingColor(flash);

		return stageFunctions(missingColor, A, B, C, C[S - 1], S, D) - stageFunctions(flash[0], A, B, C, C[S - 1], S, D) - stageFunctions(flash[1], A, B, C, C[S - 1], S, D);
	}

	static int threeColorFlash(const std::string flash, const std::vector<int> A, const std::array<int, 6> B, const std::array<int, 7> C, const int S, const int D) {
		assert(flash.length() == 3);

		int colorMixValue = colorDetermine::primaryVsSecondaryMix(flash);

		if (colorMixValue == 3) {
			return C[S - 1] + ((C[S - 1] <mod> 3) * C[0]) - ((B[S - 1] <mod> 3) * B[0]) + ((A[S - 1] <mod> 3) * A[0]) % modOperator;
		
		} else if (colorMixValue == 4) {
			std::vector<int> colorValues(flash.length() + 2, 0);

			for (int i = 0; i < flash.length(); i++) {
				if (flash[i] == 'r' || flash[i] == 'g' || flash[i] == 'b') {
					colorValues[i] = stageFunctions(flash[i], A, B, C, C[S - 1], S, D);
				} else {
					colorValues[3] = stageFunctions(flash[i], A, B, C, B[S - 1], S, D);
					colorValues[4] = stageFunctions(flash[i], A, B, C, A[S - 1], S, D);					
				}
			}

			return (colorValues[0] + colorValues[1] + colorValues[2] + colorValues[3] + colorValues[4]) % modOperator;
		
		} else if (colorMixValue == 5) {
			std::vector<int> colorValues(flash.length() + 2, 0);

			for (int i = 0; i < flash.length(); i++) {
				if (flash[i] == 'c' || flash[i] == 'm' || flash[i] == 'y') {
					colorValues[i] = stageFunctions(flash[i], A, B, C, C[S - 1], S, D);
				} else {
					colorValues[3] = stageFunctions(flash[i], A, B, C, B[S - 1], S, D);
					colorValues[4] = stageFunctions(flash[i], A, B, C, A[S - 1], S, D);
				}
			}

			return (colorValues[0] + colorValues[1] + colorValues[2] - colorValues[3] - colorValues[4]) % modOperator;
		}

		return (C[S - 1] + ((C[0] <mod> 3) * C[S - 1]) - ((B[0] <mod> 3) * B[S - 1]) + ((A[0] <mod> 3) * A[S - 1])) % modOperator;
	}

public:
	static const int stageThreeCalculation(const std::string flash, const std::vector<int> A, const std::array<int, 6> B, const std::array<int, 7> C, const int S, const int D) {
		assert(flash.length() <= 3);

		switch (flash.length()) {
			case 1:
				return oneColorFlash(flash, A, B, C, S, D);

			case 2:
				return twoColorFlash(flash, A, B, C, S, D);

			case 3:
				return threeColorFlash(flash, A, B, C, S, D);

			default:
				return -INF;
		}
	}
};