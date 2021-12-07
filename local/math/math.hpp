#include <vector>
#include <array>
#include <string>

class math {
public:

    static const int modOperator = 365;
    static const int INF = int(1e9) + 5;

    static int moduloRule(int x) {
        return x % modOperator;
    }

    //TODO: remake bace36 converter 
    static void baseConverter(std::string str, std::array<char, 6> &numOrChar, std::array<int, 6> &base36) {
        for (int i = 0; i < 6; i++) {
            base36[i] = tolower(str[i]) - 96;
        }

        for (int i = 0; i < 6; i++) {
            if (base36[i] < 0) {
                base36[i] = base36[i] + 48;
                numOrChar[i] = 'i';//if int = 0
            } else {
                numOrChar[i] = 'c';//if char = 1
            }
        }
    }
};