#include <vector>
#include <string>

class LOCAL_MATH {

private:

    const int INF = int(1e9) + 5;

    //fixed modulo value 0-y
    int local_mod(int x, const int y) {
        if (x >= y) {
            x = x % y;
        } else if(x < 0) {
            x = (x % y) + y;
        }
        return x;
    }

    int local_moduloRule(int x) {
        if (x >= 365 || x <= -365) {
            x = x % 365;
        }
        
        return x;
    }

    void local_baseConverter(std::string str, int numOrChar[], int base36[]) {
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

    template<typename T_Num>
    T_Num local_pow(T_Num base, const T_Num exponent) {
        if (exponent == 0) {
            return 1;
        }

        auto x = base;

        for (int i = 0; i < exponent - 1; i++) { 
            base *= x;
        }

        return base;
    }

    int local_max(const std::vector<int> &x, const int size) {
        int y = -INF;

        for (int i = 0; i < size; i++) {
            if (x[i] > y) {
                y = x[i];
            }
        }

        return y;
    }

    int local_min(const std::vector<int> &x, const int size) {
        int y = INF;

        for (int i = 0; i < size; i++) 
            if (x[i] < y) 
                y = x[i];
        return y;
    }

    int local_abs(int x) {
        return x < 0 ? x *= -1 : x;
    }

public:
    int mod(int x, const int y) {
        return local_mod(x, y);
    }

    int moduloRule(int x) {
        return local_moduloRule(x);
    }

    void bace36Converter(std::string serial, int numOrChar[], int base36[]) {
        local_baseConverter(serial, numOrChar, base36);
    }

    int pow(int base, const int exponent) {
        return local_pow(base, exponent);
    }

    int max(std::vector<int> x, const int size) {
        return local_max(x, size);
    }
    
    int min(std::vector<int> x, const int size) {
        return local_min(x, size);
    }

    int abs(int x) {
        return local_abs(x);
    }
};