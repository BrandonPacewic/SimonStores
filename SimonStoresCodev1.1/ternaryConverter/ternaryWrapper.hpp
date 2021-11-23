#include "balancedConverter.hpp"

class balancedConverter {
    public:
        const int MAX_VALUE = 364; //max size to be converted in the manual
        template<typename T>
        void convert(T valueToBeConverted) {
            int64_t reValueToBeConverted = int64_t(valueToBeConverted);
            
            bool invertSigns = false;

            if (reValueToBeConverted < 0) {
                invertSigns = true;
            }
            
            vector<int64_t> values = initalizeValues(MAX_VALUE);
            vector<int> ternaryArray = makeTernaryArray(values, valueToBeConverted);
            convertTernaryArrayToBalancedTernary(ternaryArray);

            vector<char> ans = convertToSymbols(ternaryArray, invertSigns);

            for (auto i : ans) {
                cout << i;
            }
            endl;
        }
};