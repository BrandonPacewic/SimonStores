#include <vector>
#include <array>

class initalCalculations {
private:
    static const int modOpperator = 365;
    static const int base36factor = 36;
    static const int charAdd = 9;

    static int local_initalAlphaCalculation(const std::array<int, 6> serialBase36, const std::array<char, 6> numOrChar) {
        int tempOne, tempTwo;

        if (numOrChar[2] == 'i') {
            tempOne = serialBase36[2] * base36factor;
        } else {
            tempOne = (serialBase36[2] + charAdd) * base36factor;
        }

        if (numOrChar[3] == 'i') {
            tempTwo = serialBase36[3];
        } else {
            tempOne = serialBase36[3] + charAdd;
        }
        
        tempOne %= modOpperator;
        tempTwo %= modOpperator;

        return tempOne + tempTwo;
    }

    static int local_initalBravoCalculation(const std::array<int, 6> serialBase36, const std::array<char, 6> numOrChar) {
        int temp;

        if (numOrChar[4] == 'i') {
            temp = serialBase36[4] * base36factor;
        } else {
            temp = (serialBase36[4] + charAdd) * base36factor; 
        }

        temp %= modOpperator;

        //serial index 5 is always a num
        return temp + serialBase36[5];
    }

    static int local_initalCharlieCalculation(const std::array<int, 6> serialBase36, const std::array<char, 6> numOrChar) {
        int tempOne, tempTwo;
        
        if (numOrChar[0] == 'i') {
            tempOne = serialBase36[0] * base36factor;
        } else {
            tempOne = (serialBase36[0] + charAdd) * base36factor;
        }

        if (numOrChar[1] == 'c') {
            tempTwo = serialBase36[1] + charAdd;
        } else {
            tempTwo = serialBase36[1];
        }

        tempOne %= modOpperator;
        tempTwo %= modOpperator;

        return tempOne + tempTwo;
    }

    static int local_initalDeltaCalculation(const std::array<int, 6> serialBase36, const std::array<char, 6> numOrChar) {
        int D = 0;

        for (int i = 0; i < serialBase36.size(); i++) {
            if (numOrChar[i] == 'i') {
                D += serialBase36[i];
            } else {
                D += serialBase36[i] + charAdd;
            }
        }

        D %= modOpperator;

        return D;
    }

public:
    static void initalNatoCalculations(const std::array<int, 6> serialBase36, const std::array<char, 6> numOrChar, std::vector<int> &A, std::array<int, 6> &B, std::array<int, 7> &C) {
        A[0] = local_initalAlphaCalculation(serialBase36, numOrChar);

        B[0] = local_initalBravoCalculation(serialBase36, numOrChar);

        C[0] = local_initalCharlieCalculation(serialBase36, numOrChar);
    }

    static int initalDCalculation(const std::array<int, 6> serialBase36, const std::array<char, 6> numOrChar) {
        return local_initalDeltaCalculation(serialBase36, numOrChar);
    }
};