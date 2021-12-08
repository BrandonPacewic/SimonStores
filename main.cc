#include "local/local.hpp"
using namespace std;
using namespace local;

const int STAGE_ONE_FLASHES = 3;
const int STAGE_TWO_FLASHES = 1;
const int STAGE_THREE_FLASHES = 1;
const int TOTAL_FLASHES = STAGE_ONE_FLASHES + STAGE_TWO_FLASHES + STAGE_THREE_FLASHES;

int main() {
    do {
        cout << "Enter the Serial#(Ex: 12qm5): ";
        string serial = user::stringInput("CheckForRequiredSize", 6);

        cout << "Enter the Order of the Colors in Clockwise Order(Ex: rmybcg): ";
        string colorOrder = user::stringInput("CheckForRequiredSize", 6);

        array<string, TOTAL_FLASHES> stageFlashes;

        for (int i = 0; i < STAGE_ONE_FLASHES; i++) {
            cout << "Enter flash #" << i + 1 << "(Ex: rmy): "; 
            stageFlashes[i] = user::stringInput("CheckForMaxSize", 3);
        }

        array<char, 6> numOrChar;
        array<int, 6> serialBase36;
        math::base36Converter(serial, numOrChar, serialBase36);

        vector<int> A(5, 0);
        array<int, 6> B;
        array<int, 7> C;
        preCompute::nato(serialBase36, numOrChar, A, B, C);
        int D = preCompute::D(serialBase36, numOrChar);

        //-----------
        //-Stage One-
        //-----------

        for (int S = 1; S <= STAGE_ONE_FLASHES; S++) {
            A[S] = stage::one::calculations(stageFlashes[S - 1], A, S, D);
        }

        stageColorSequence::print(1, colorOrder);
        balancedTernary::convert(A[3]);

        //-----------
        //-Stage Two-
        //-----------

        cout << "Enter flash #4: ";
        stageFlashes[3] = user::stringInput("CheckForMaxSize", 3);

        for (int S = 1; S <= STAGE_ONE_FLASHES + STAGE_TWO_FLASHES; S++) {
            B[S] = stage::two::calculations(stageFlashes[S - 1], A, B, S, D);
        }

        stageColorSequence::print(2, colorOrder);
        balancedTernary::convert(B[4]);

        //-------------
        //-Stage Three-
        //-------------


        cout << "Enter flash #5: ";
        stageFlashes[4] = user::stringInput("CheckForMaxSize", 3);


        for (int S = 1; S <= TOTAL_FLASHES; S++) {
            C[S] = stage::three::calculations(stageFlashes[S - 1], A, B, C, S, D);
        }

        stageColorSequence::print(3, colorOrder);
        balancedTernary::convert(C[5]);

    } while (user::menu());
}