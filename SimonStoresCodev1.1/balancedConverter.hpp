template<typename T> T local_ternaryConverter(T conVal) {
    int64_t inVal = int64_t(conVal);
    vector<int64_t> vals;
    for (int i = 0; pow(3, i) <= conVal; i++) 
        vals.pb(int64_t(pow(3, i)));
        
    vals.pb(int64_t(pow(3, vals.size())));
    sort(vals.begin(), vals.end(), greater<int64_t>());

    vector<char> outPut(vals.size(), '0');
    vector<int> balTer(vals.size(), 0);
    for (int i = 0; i < vals.size(); i++) 
        for (int j = 0; j < 2; j++) 
            if (inVal >= vals[i]) {
                balTer[i]++;
                inVal -= vals[i]; 
            }
    
    for (int i = balTer.size() - 1; i >= 0; i--) {
        if (balTer[i] == 3) {
            balTer[i] = 0;
            balTer[i-1]++;
        } else if (balTer[i] == 2) {
                balTer[i-1]++; outPut[i] = '-';
        } else if (balTer[i] == 1) {
            outPut[i] = '+';
        }
    }
    
    for (auto i: balTer)
        cout << i;

    return conVal;
}