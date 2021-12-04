#include <vector>
#include <string>

const int INF = int(1e9) + 5;

class localMath {
private:

    static int local_moduloRule(int x) {
        if (x >= 365 || x <= -365) {
            x = x % 365;
        }
        
        return x;
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

    static int local_pow(int base, const int exponent) {
        if (exponent == 0) {
            return 1;
        }

        auto x = base;

        for (int i = 0; i < exponent - 1; i++) { 
            base *= x;
        }

        return base;
    }

    static int local_max(const std::vector<int> &x, const int size) {
        int y = -INF;

        for (int i = 0; i < size; i++) {
            if (x[i] > y) {
                y = x[i];
            }
        }

        return y;
    }

    static int local_min(const std::vector<int> &x, const int size) {
        int y = INF;

        for (int i = 0; i < size; i++) 
            if (x[i] < y) 
                y = x[i];
        return y;
    }

    static int local_abs(int x) {
        return x < 0 ? x *= -1 : x;
    }

public:

    static int moduloRule(int x) {
        return local_moduloRule(x);
    }

    static void bace36Converter(std::string serial, int numOrChar[], int base36[]) {
        local_baseConverter(serial, numOrChar, base36);
    }

    static int pow(int base, const int exponent) {
        return local_pow(base, exponent);
    }

    static int max(std::vector<int> x, const int size) {
        return local_max(x, size);
    }
    
    static int min(std::vector<int> x, const int size) {
        return local_min(x, size);
    }

    static int abs(int x) {
        return local_abs(x);
    }
};