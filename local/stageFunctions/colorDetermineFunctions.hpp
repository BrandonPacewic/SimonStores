#include <string>
#include <array>
#include <vector>

namespace colorDetermine {
    int addColorMix(std::string &flash) {
        std::vector<int> temp(3, 0);

        for (auto &i: flash)
            i = tolower(i);
        
        for (int i = flash.length(); i > 0; i--) {
            if (flash[i-1] == 'r' || flash[i-1] == 'g' || flash[i-1] == 'b') {
                temp[i-1] = 1;
            } else {
                temp[i-1] = 2;
            }
        }
        return(temp[0] + temp[1] + temp[2]);
    }
}