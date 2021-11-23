#include "localMath.hpp"

class local {
    public:

        //math
        int mod(int x, const int y) {
            return local_mod(x, y);
        }

        int moduloRule(int x) {
            return local_moduloRule(x);
        }

        void bace36Converter(string serial, int numOrChar[], int base36[]) {
            local_baseConverter(serial, numOrChar, base36);
        }

        int pow(int base, const int exponent) {
            return local_pow(base, exponent);
        }

        int max(vector<int> x, const int size) {
            return local_max(x, size);
        }
        
        int min(vector<int> x, const int size) {
            return local_min(x, size);
        }

        int abs(int x) {
            return local_abs(x);
        }

};