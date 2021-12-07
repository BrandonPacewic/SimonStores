#include "balancedTernaryConverter/balancedTernaryConverter.hpp"
#include "math/math.hpp"
#include "math/modulo.hpp"
#include "modualRuleSet/colorSequence.hpp"
#include "modualRuleSet/initalCalculations.hpp"
#include "stageFunctions/stageOne.hpp"
#include "stageFunctions/stageTwo.hpp"
#include "stageFunctions/stageThree.hpp"
#include "userInput/userErrorCatch/errorCatch.hpp"
#include "userInput/userMenu.hpp"

namespace local {
	namespace preCompute{
		void nato(const std::array<int, 6> serialBase36, const std::array<char, 6> numOrChar, std::vector<int> &A, std::array<int, 6> &B, std::array<int, 7> &C) {
			initalCalculations::initalNatoCalculations(serialBase36, numOrChar, A, B, C);
		}

		int D(const std::array<int, 6> serialBase36, const std::array<char, 6> numOrChar) {
			return initalCalculations::initalDCalculation(serialBase36, numOrChar);
		}
	}

	namespace stageColorSequence {
		void print(const int stage, const std::string colorOrder) {
			colorSequence::printStageColorSequence(stage, colorOrder);
		}
	}

	namespace balancedTernary {
		void convert(int valueToBeConverted) {
			balancedTernaryConverter::convert(valueToBeConverted);
		}
	}

	namespace stage {
		namespace one {
			int calculations(const std::string flash, const std::vector<int> A, const int S, const int D) {
				return stageOne::stageOneCalculations(flash, A, S, D);
			}
		}

		namespace two {
			int calculations(const std::string flash, const std::vector<int> A, const std::array<int, 6> B, const int S, const int D) {
				return stageTwo::stageOneCalculation(flash, A, B, S, D);
			}
		}

		namespace three {
			int calculations(const std::string flash, const std::vector<int> A, const std::array<int, 6> B, const std::array<int, 7> C, const int S, const int D) {
				return stageThree::stageThreeCalculation(flash, A, B, C, S, D);
			}
		}
	}

	namespace user {
		std::string stringInput(const std::string inputType, const int expectedLength) {
			return errorCatch::userStringInput(inputType, expectedLength);
		}

		bool menu() {
			return userInput::userMenu();
		}
	}
}