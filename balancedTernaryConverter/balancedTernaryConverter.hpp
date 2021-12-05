#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

class balancedTernaryConverter {
private: 

    static std::vector<int> initalizeValues(const int ValueToBeConverted) {
        std::vector<int> VALUES;

        for (int i = 0; pow(3, i) <= ValueToBeConverted; i++) {
            VALUES.push_back(pow(3, i));
        }

        sort(VALUES.begin(), VALUES.end(), std::greater<int>());
        
        return VALUES;
    }

    static std::vector<int> makeTernaryArray(const std::vector<int> VALUES, int valueToBeConverted) {
        std::vector<int> ternaryArray(VALUES.size(), 0);

        for (int i = 0; i < VALUES.size(); i++) { 
            for (int j = 0; j < 2; j++) { 
                if (abs(valueToBeConverted) >= VALUES[i]) {
                    ternaryArray[i]++;
                    valueToBeConverted = abs(valueToBeConverted) - VALUES[i]; 
                }
            }
        }

        return ternaryArray;
    }

    static void convertTernaryArrayToBalancedTernary(std::vector<int> &ternaryArray) {
        for (int i = ternaryArray.size() - 1; i > 0; i--) {
            if (ternaryArray[i] == 3) {
                ternaryArray[i] = 0;
                ternaryArray[i-1]++;
            } else if (ternaryArray[i] == 2) {
                    ternaryArray[i-1]++; 
                    ternaryArray[i] = -1;
            } 
        }
    }

    static std::vector<char> convertToSymbols(const std::vector<int> &balancedTernaryArray, const bool invertSigns = false) {
        std::vector<char> ans(balancedTernaryArray.size(), '0');
        
        for (int i = 0; i < balancedTernaryArray.size(); i++) {
            if (balancedTernaryArray[i] == 1) {
                ans[i] = invertSigns ? '-' : '+';
            } else if (balancedTernaryArray[i] == -1) 
                ans[i] = invertSigns ? '+' : '-';
        }

        return ans;
    }

    static void printAnswer(std::vector<char> ans) {
        for (auto i : ans) {
            std::cout << i;
        }
        std::cout << std::endl;
    }

public:
    //max int size to be converted found in the manual
    static const int MAX_VALUE = 364; 

    static void convert(int valueToBeConverted) {
        bool invertSigns = false;

        if (valueToBeConverted < 0) {
            invertSigns = true;
        }

        std::vector<int> values = initalizeValues(MAX_VALUE);

        std::vector<int> ternaryArray = makeTernaryArray(values, valueToBeConverted);

        convertTernaryArrayToBalancedTernary(ternaryArray);

        std::vector<char> ans = convertToSymbols(ternaryArray, invertSigns);

        printAnswer(ans);
    }
};