#include <array>
#include <cstdlib>
#include <iterator>
#include <string>
#include <cmath>
#include <algorithm>
#include <cassert>
#include <vector>
#include "colorDetermineFunctions.hpp"

class stageTwo {
private:
	static const int INF = int(1e9) + 5;
	static const int modOperator = 365;

	static int stageFunctions(const char color, const std::vector<int> A, const std::array<int, 6> B, const int X, const int S, const int D) {
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

	        case 'Y':
	            Y = X + B[4] - A[0];
	            break;

	    }

	    Y %= modOperator;

	    return Y;
	}

	static int oneColorFlash(const std::string flash, const std::vector<int> A, const std::array<int, 6> B, const int S, const int D) {
		assert(flash.length() == 1);

		return stageFunctions(flash[0], A, B, B[S - 1], S, D);
	}

	static int twoColorFlash(const std::string flash, const std::vector<int> A, const std::array<int, 6> B, const int S, const int D) {
		assert(flash.length() == 2);

		int colorMixValue = colorDetermine::primaryVsSecondaryMix(flash);

		if (colorMixValue == 2 || colorMixValue == 3) {			
			int colorValueOne = stageFunctions(flash[0], A, B, B[S - 1], S, D);
			int colorValueTwo = stageFunctions(flash[1], A, B, B[S - 1], S, D);

			if (colorMixValue == 2) {
				return abs(colorValueOne - colorValueTwo) % modOperator;
			}

			return ((4 * D) - abs(colorValueOne - colorValueTwo)) % modOperator;
		}

		//colorMixValue == 4 (both colors are secondary)
		char missingColor = colorDetermine::missingColor(flash);

		int colorValueOne = stageFunctions(missingColor, A, B, A[S - 1], S, D);
		int colorValueTwo = stageFunctions(missingColor, A, B, B[S - 1], S, D);

		return std::min(colorValueOne, colorValueTwo);
	}

	static int threeColorFlash(const std::string flash, const std::vector<int> A, const std::array<int, 6> B, const int S, const int D0 {
		assert(flash.length() == 3);
	
		
	}

};