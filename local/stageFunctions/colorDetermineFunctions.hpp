#include <string>
#include <vector>

#ifndef __colorDetermine__
#define __colorDetermine__
namespace colorDetermine {

    int primaryVsSecondaryMix(const std::string flash) {
        std::vector<int> temp(3, 0);
        
        for (int i = flash.length(); i > 0; i--) {
            if (tolower(flash[i-1]) == 'r' || tolower(flash[i-1]) == 'g' || tolower(flash[i-1]) == 'b') {
                temp[i-1] = 1;
            } else {
                temp[i-1] = 2;
            }
        }

        return temp[0] + temp[1] + temp[2];
    }

    char missingColor(const std::string flash) {
        int x = 0;
        bool primaryColors = false;

        for (auto ch : flash) {
            switch (tolower(ch)) {
                case 'r':
                    x = x + 1;
                    primaryColors = true;
                    break;

                case 'g':
                    x = x + 2;
                    primaryColors = true;
                    break;

                case 'b':
                    x = x + 3;
                    primaryColors = true;
                    break;

                case 'c':
                    x = x + 1;
                    break;

                case 'm':
                    x = x + 2;
                    break;

                case 'y':
                    x = x + 3;
                    break;            
            }
        }

        if (primaryColors) {
            switch (x) {
                case 5:
                    return('r');
                    break;

                case 4:
                    return('g');
                    break;

                case 3:
                    return('b');
                    break;
                default:
                    return 'X';
            }

        } else {
            switch (x) {
                case 5:
                    return('c');
                    break;

                case 4:
                    return('m');
                    break;

                case 3:
                    return('y');
                    break;
                
                default:
                    return 'X';
            }
        }
    }
}
#endif