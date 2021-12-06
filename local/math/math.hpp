#include <vector>
#include <string>


class math {
public:

    static const int INF = int(1e9) + 5;

    static int moduloRule(int x) {
        return x % 365;
    }

    //TODO: remake bace36 converter 
    static void baseConverter(std::string str, int numOrChar[], int base36[]) {
        for (int i = 0; i < 6; i++) {
            base36[i] = tolower(str[i]) - 96;
        }

        for (int i = 0; i < 6; i++) {
            if (base36[i] < 0) {
                base36[i] = base36[i] + 48;
                numOrChar[i] = 0;//if int = 0
            } else {
                numOrChar[i] = 1;//if char = 1
            }
        }
    }
};