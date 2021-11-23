template<typename T_Num> 
vector<int64_t> initalizeValues(T_Num ValueToBeConverted) {
    vector<int64_t> vals;

    for (int i = 0; pow(3, i) <= ValueToBeConverted; i++) {
        vals.push_back(int64_t(pow(3, i)));
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