#include <bits/stdc++.h>
using namespace std;

class balancedTernaryConverter {

private: 
    template<typename T_Num>
    vector<int64_t> initalizeValues(T_Num ValueToBeConverted) {
        vector<int64_t> VALUES;

        for (int i = 0; pow(3, i) <= ValueToBeConverted; i++) {
            VALUES.push_back(int64_t(pow(3, i)));
        }
            
        sort(VALUES.begin(), VALUES.end(), greater<int64_t>());
        
        return VALUES;
    }

    vector<int> makeTernaryArray(vector<int64_t> VALUES, int64_t valueToBeConverted) {
        vector<int> ternaryArray(VALUES.size(), 0);

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

    void convertTernaryArrayToBalancedTernary(vector<int> &ternaryArray) {
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

    vector<char> convertToSymbols(vector<int> balancedTernaryArray, bool invertSigns = false) {
        vector<char> ans(balancedTernaryArray.size(), '0');
        
        for (int i = 0; i < balancedTernaryArray.size(); i++) {
            if (balancedTernaryArray[i] == 1) {
                ans[i] = invertSigns ? '-' : '+';
            } else if (balancedTernaryArray[i] == -1) 
                ans[i] = invertSigns ? '+' : '-';
        }

        return ans;
    }

    void printAnswer(vector<char> ans) {
        for (auto i : ans) {
            cout << i;
        }
        cout << endl;
    }

public:
    const int MAX_VALUE = 364; //max int size to be converted found in the manual

    template<typename T_Num>
    void convert(T_Num valueToBeConverted) {
        int64_t standardizedValueToBeConverted = int64_t(valueToBeConverted);
        bool invertSigns = false;

        if (standardizedValueToBeConverted < 0) {
            invertSigns = true;
        }

        vector<int64_t> values = initalizeValues(MAX_VALUE);

        vector<int> ternaryArray = makeTernaryArray(values, standardizedValueToBeConverted);

        convertTernaryArrayToBalancedTernary(ternaryArray);

        vector<char> ans = convertToSymbols(ternaryArray, invertSigns);

        printAnswer(ans);
    }
};