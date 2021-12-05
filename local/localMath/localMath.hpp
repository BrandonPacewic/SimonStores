#include <vector>
#include <string>


class localMath {
private:

    static const int INF = int(1e9) + 5;

    static int local_moduloRule(int x) {
        return x % 365;
    }

    //TODO: remake bace36 converter 
    static void local_baseConverter(std::string str, int numOrChar[], int base36[]) {
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

public:

    static int moduloRule(int x) {
        return local_moduloRule(x);
    }

    static void bace36Converter(std::string serial, int numOrChar[], int base36[]) {
        local_baseConverter(serial, numOrChar, base36);
    }
};