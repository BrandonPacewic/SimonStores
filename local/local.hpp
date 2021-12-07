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
#include <array>

namespace local {
	namespace initalCalculations {
		void initalNatoCalculations(const std::array<int, 6> serialBase36, const std::array<char, 6> numOrChar, std::vector<int> &A, std::array<int, 6> &B, std::array<int, 7> &C) {
			initalCalculations::initalNatoCalculations(serialBase36, numOrChar, A, B, C);
		}

		int initalDCalculation(const std::array<int, 6> serialBase36, const std::array<char, 6> numOrChar) {
			return initalCalculations::initalDCalculation(serialBase36, numOrChar);
		}
	}

	namespace colorSequence {
		
	}
}