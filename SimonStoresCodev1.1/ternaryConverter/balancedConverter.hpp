#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define endl cout << '\n'
#define endl2 cout << "\n\n"

//max value that will need to be converted specifyed in the manual
const int MAX_VAL = 364;

// template<typename T> T local_ternaryConverter(T conVal) {
//     int64_t ReConVal = int64_t(conVal);
//     bool neg = false;
//     if (ReConVal < 0) {
//         neg = true;
//         ReConVal *= int64_t(-1);
//     }

//     vector<int64_t> vals;
//     for (int i = 0; pow(3, i) <= MAX_VAL; i++) 
//         vals.pb(int64_t(pow(3, i)));
        
//     sort(vals.begin(), vals.end(), greater<int64_t>());

//     vector<int> balTer(vals.size(), 0);
//     for (int i = 0; i < vals.size(); i++) 
//         for (int j = 0; j < 2; j++) 
//             if (ReConVal >= vals[i]) {
//                 balTer[i]++;
//                 ReConVal -= vals[i]; 
//             }
    
//     for (int i = balTer.size() - 1; i > 0; i--) {
//         if (balTer[i] == 3) {template<typename T> T local_ternaryConverter(T conVal) {
//     int64_t ReConVal = int64_t(conVal);
//     bool neg = false;
//     if (ReConVal < 0) {
//         neg = true;
//         ReConVal *= int64_t(-1);
//     }

//     vector<int64_t> vals;
//     for (int i = 0; pow(3, i) <= MAX_VAL; i++) 
//         vals.pb(int64_t(pow(3, i)));
        
//     sort(vals.begin(), vals.end(), greater<int64_t>());

//     vector<int> balTer(vals.size(), 0);
//     for (int i = 0; i < vals.size(); i++) 
//         for (int j = 0; j < 2; j++) 
//             if (ReConVal >= vals[i]) {
//                 balTer[i]++;
//                 ReConVal -= vals[i]; 
//             }
    
//     for (int i = balTer.size() - 1; i > 0; i--) {
//         if (balTer[i] == 3) {
//             balTer[i] = 0;
//             balTer[i-1]++;
//         } else if (balTer[i] == 2) {
//                 balTer[i-1]++; 
//                 balTer[i] = -1;
//         } 
//     }

//     vector<char> ans(balTer.size(), '0');
//     for (int i = 0; i < balTer.size(); i++) {
//         if (balTer[i] == 1) {
//             ans[i] = '+';
//         } else if (balTer[i] == -1) 
//             ans[i] = '-';
//     }

//     if (neg)
//         for (auto &i: ans) {
//             if (i == '+') {
//                 i = '-';
//             } else if (i == '-') {
//                 i = '+';
//             }
//         }
        
//     for (int i = ans.size() - 1; i >= 0; i--)
//         cout << ans[i];
//     endl;

//     return conVal;
// }
//             balTer[i] = 0;
//             balTer[i-1]++;
//         } else if (balTer[i] == 2) {
//                 balTer[i-1]++; 
//                 balTer[i] = -1;
//         } 
//     }

//     vector<char> ans(balTer.size(), '0');
//     for (int i = 0; i < balTer.size(); i++) {
//         if (balTer[i] == 1) {
//             ans[i] = '+';
//         } else if (balTer[i] == -1) 
//             ans[i] = '-';
//     }

//     if (neg)
//         for (auto &i: ans) {
//             if (i == '+') {
//                 i = '-';
//             } else if (i == '-') {
//                 i = '+';
//             }
//         }
        
//     for (int i = ans.size() - 1; i >= 0; i--)
//         cout << ans[i];
//     endl;

//     return conVal;
// }

template<typename T_Num> 
vector<int64_t> initalizeValues(T_Num ValueToBeConverted) {
    vector<int64_t> vals;

    for (int i = 0; pow(3, i) <= ValueToBeConverted; i++) {
        vals.pb(int64_t(pow(3, i)));
    }
        
    sort(vals.begin(), vals.end(), greater<int64_t>());
    
    return vals;
}

vector<int> makeTernaryArray(vector<int64_t> VALS, int64_t valueToBeConverted) {
    vector<int> ternaryArray(VALS.size(), 0);

    for (int i = 0; i < VALS.size(); i++) { 
        for (int j = 0; j < 2; j++) { 
            if (abs(valueToBeConverted) >= VALS[i]) {
                ternaryArray[i]++;
                valueToBeConverted = abs(valueToBeConverted) - VALS[i]; 
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