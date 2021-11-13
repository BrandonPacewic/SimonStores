template<typename T> T local_ternaryConverter(T conVal) {
    int64_t inVal = int64_t(conVal);
    bool neg = false;
    if (inVal < 0) {
        neg = true;
        inVal *= int64_t(-1);
    }

    vector<int64_t> vals;
    for (int i = 0; pow(3, i) <= 364; i++) 
        vals.pb(int64_t(pow(3, i)));
        
    sort(vals.begin(), vals.end(), greater<int64_t>());

    vector<int> balTer(vals.size(), 0);
    for (int i = 0; i < vals.size(); i++) 
        for (int j = 0; j < 2; j++) 
            if (inVal >= vals[i]) {
                balTer[i]++;
                inVal -= vals[i]; 
            }
    
    for (int i = balTer.size() - 1; i > 0; i--) {
        if (balTer[i] == 3) {
            balTer[i] = 0;
            balTer[i-1]++;
        } else if (balTer[i] == 2) {
                balTer[i-1]++; 
                balTer[i] = -1;
        } 
    }

    vector<char> ans(balTer.size(), '0');
    for (int i = 0; i < balTer.size(); i++) {
        if (balTer[i] == 1) {
            ans[i] = '+';
        } else if (balTer[i] == -1) 
            ans[i] = '-';
    }

    if (neg)
        for (auto &i: ans)
            if (i == '+') {
                i = '-';
            } else if (i == '-')
                i = '+';

    for (int i = ans.size() - 1; i >= 0; i--)
        cout << ans[i];

    endl;
    return conVal;
}