#include "balancedTernaryConverter/balancedTernaryConverter.hpp"
#include "local/modualRuleSet/modualRuleset.hpp"
using namespace std;


//lizard easter egg
const string lizard = "lizard";
bool lizard_test(string test) {
    int lizard_count = 0;    
    for (int i = 0; i < test.size(); i++) 
        if (test[i] == lizard[i])
            lizard_count++;
    if (lizard_count == 6)
        return true;
    return false;
}

//error catch, m for max value r for required value
#include <cassert>
template<typename N> N errorCatch(N testVal, const int maxSize, const char type) {
    string dataType = typeid(testVal).name();
    const string string_type = "NSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE";

    assert (dataType == string_type && (type == 'm' || type == 'r'));
    string test = testVal;

    while (lizard_test(test)) {
        cout << "\n\nStop it, you know that lizard is not a valid input\n";
        cout << R"(https://github.com/BrandonPacewic/SimonStores/blob/main/images/lizardIsNotAValidInput.png)";
        cout << "Please try again: ";
        getline(cin, test);   
    }

    if (type == 'm') {
        while (test.length() > maxSize) {
            cout << "\n\nYou exceeded the maximum size for this value \nThe max size is " << maxSize << ". \nPlease try again: ";
            getline(cin, test);
        }
        
    } else if (type == 'r') 
        while (test.length() != maxSize) {
            cout << "\n\nYou did not meet the required size for this value \nThe required size is " << maxSize << ". \nPlease try again: ";
            getline(cin, test);
        }

    return test;
}

//user menu
bool userMenu() {
    string x;
    cout << "What would you like to do? \n Continue or Quit (c,q): ";
    getline(cin, x);
    while (tolower(x[0]) != 'q' && tolower(x[0]) != 'c' || x.length() != 1) {
        cout << "You did not enter a valid input please try again. \n";
        cout << "What would you like to do? \n Continue or Quit (c,q): ";
        getline(cin, x);
    }
    if (tolower(x[0]) == 'c')
        return true;
    return false;
}

int main() {
// part of dbg
#ifdef TEXT_IO 
    freopen("in.txt", "r", stdin);
    freopen("ou.txt", "w", stdout);
#endif

    int numOrChar[6];//used for base 36 convertion
    int serialBase36[6];//the base 36 value of the serial number
    vector<int> a(5, 0);//each arr only has pos for the numbers we need
    int b[6];//a,b and c values specifyed from the manual page
    int c[7];
    int d = 0;//sum of base 36 in serial#
    string stageFlash[6];
    string serial, colorOrder, stageColorOrder, flash;

    const string colorStageOne = "rgbcmy";
    const string colorStageTwo = "ybgmcr"; 
    const string colorStageThree = "bmrygc";

    BALANCED_TERNARY_CONVERTER balancedTernaryConverter; // balanced ternary type

    //intro
    cout << "\nWelcome to a c++ Script for sloving Simon Stores!\n";
    cout << "Lets get started! \n";

    do {
        //user input + valid input check
        cout << "Enter the Serial# Ex(MA9KR5): ";
        getline(cin, serial);
        serial = errorCatch(serial, 6, 'r');

        cout << "Order of Colors in clockwise order, Ignoring White and black Ex(RMYCBG): ";
        getline(cin, colorOrder);
        colorOrder = errorCatch(colorOrder, 6, 'r');

        cout << "First Color Flash Ex(RM): ";
        getline(cin, stageFlash[0]);
        stageFlash[0] = errorCatch(stageFlash[0], 3, 'm');

        cout << "Second Color Flash Ex(RM): ";
        getline(cin, stageFlash[1]);
        stageFlash[1] = errorCatch(stageFlash[1], 3, 'm');

        cout << "Third Color Flash Ex(RM): ";
        getline(cin, stageFlash[2]);
        stageFlash[2] = errorCatch(stageFlash[2], 3, 'm');
        cout << endl;

        //base 36 convertion
        local_baseConverter(serial, numOrChar, serialBase36);

        //inital calculations
        local_initalCalculations(serialBase36, numOrChar, a, b, c);
        
        //calculating d
        d = local_dCalculation(serialBase36, numOrChar);

        //*********//
        //stage one//
        //*********//
        for (int s = 1; s <= 3; s++) {//s being the step in the stage (starts at 1)
            flash = stageFlash[s-1];

            if (flash.length() == 1) {
                a[s] = local_stageOne(flash[0], a[s-1], s, d);
            } else if (flash.length() == 2) {
                vector<int> temp(6, 0);

                temp[2] = local_addColorMix(flash);

                temp[0] = local_stageOne(flash[0], a[s-1], s, d);
                temp[1] = local_stageOne(flash[1], a[s-1], s, d);

                switch (temp[2]) {
                    case 2:
                        a[s] = local_max(temp, 2);
                        break;
                    case 3:
                        a[s] = temp[0] + temp[1] - (d * 2);
                        break;
                    case 4:
                        a[s] = local_min(temp, 2);
                        break;
                    default:
                        cout << "Something broke come find it";
                        return(0);
                        break;
                }
            } else if (flash.length() == 3) {
                vector<int> temp(6, 0);

                temp[5] = local_addColorMix(flash);

                if (temp[5] == 3) {
                    a[s] = local_moduloRule(a[s-1] + a[0]);
                } else if (temp[5] == 4 || temp[5] == 5) {

                    for (int  i = 0; i < 3; i++) 
                        temp[i] = local_stageOne(flash[i], a[s-1], s, d);

                    if (temp[5] == 4) {
                        a[s] = local_max(temp, 3);

                    } else { 
                        a[s] = local_min(temp, 3);
                    }

                } else {
                    a[s] = local_moduloRule(a[s-1] - a[0]);
                }
            }
        }


        // local_colorSumbitingOrder(colorOrder, colorStageOne);
        balancedTernaryConverter.convert(a[3]);

        //*********//
        //stage two//
        //*********//

        cout << "Forth Color Flash: ";
        getline(cin, stageFlash[3]);
        stageFlash[3] = errorCatch(stageFlash[3], 3, 'm');
        cout << "\n\n";

        for (int s = 1; s <= 4; s++) { 
             flash = stageFlash[s-1];

             //one color flash
             if (flash.length() == 1) {
                 b[s] = local_stageTwo(flash[0], b[s-1], s, d, a);
             } else if (flash.length() == 2) {
                 vector<int> temp(6, 0);

                 //two color flashes
                 temp[2] = local_addColorMix(flash);

                 if (temp[2] == 2 || temp[2] == 3) {
                     for (int i = 0; i < 2; i++) {
                         temp[i] = local_stageTwo(flash[i], b[s-1], s, d, a);
                    }
                    if (temp[2] == 2) {
                        b[s] = local_moduloRule(local_abs(temp[0] - temp[1]));
                    } else {
                        b[s] = local_moduloRule((4 * d) - local_abs(temp[0] - temp[1]));
                    }
                 } else {
                    switch (local_missingColor(flash)) {
                        case 'c':
                            temp[0] = local_stageTwo('c', b[s-1], s, d, a);
                            temp[1] = local_stageTwo('c', a[s-1], s, d, a);
                            break;
                        case 'm':
                            temp[0] = local_stageTwo('m', b[s-1], s, d, a);
                            temp[1] = local_stageTwo('m', a[s-1], s, d, a);
                            break;
                        case 'y':
                            temp[0] = local_stageTwo('y', b[s-1], s, d, a);
                            temp[1] = local_stageTwo('y', a[s-1], s, d, a);
                            break;
                    }
                b[s] = local_min(temp, 2);
                }
            } else if (flash.length() == 3) {
                //three color flashes
                vector<int> temp(6, 0);

                temp[3] = local_addColorMix(flash);

                if (temp[3] == 3) {
                    b[s] = localMath.moduloRule(b[s-1] + (localMath.mod(b[s-1], 4) * b[0]) - a[3]);
                } else if (temp[3] == 4) {
                    for (int i = 0; i < 3; i++) {
                        if (flash[i] == 'r' || flash[i] == 'g' || flash[i] == 'b') {
                            temp[i] = local_stageTwo(flash[i], b[s-1], s, d, a);
                        } else {
                            temp[4] = local_stageTwo(flash[i], a[s-1], s, d, a);
                        }
                        b[s] = localMath.moduloRule(b[s-1] + temp[0] + temp[1] + temp[2] - temp[4]);
                    }
                } else if (temp[3] == 5) {
                    for (int i = 0; i < 3; i++) {
                        cout << i << ' ' << flash[i] << '\n';
                        if (flash[i] == 'm' || flash[i] == 'c' || flash[i] == 'y') {
                            temp[i] = local_stageTwo(flash[i], a[s-1], s, d, a);
                        } else {
                            temp[4] = local_stageTwo(flash[i], b[s-1], s, d, a);
                        }
                    }
                    b[s] = localMath.moduloRule(b[s-1] + temp[0] + temp[1] + temp[2] - temp[4]);
                } else if (temp[3] == 6) {
                    b[s] = localMath.moduloRule(b[s-1] + (localMath.mod(b[0], 4) * b[s-1]) - a[3]);
                }
            }
        } 


        local_colorSumbitingOrder(colorOrder, colorStageTwo);
        balancedTernaryConverter.convert(b[4]);
        cout << endl;
        
        //***********//
        //Stage Three//
        //***********//

        cout << "Fith Color Flash: ";
        getline(cin, stageFlash[4]);
        stageFlash[4] = errorCatch(stageFlash[4], 3, 'm');  
        cout << "\n\n";

        for (int s = 1; s <= 5; s++) {
            flash = stageFlash[s-1]; 

            if (flash.length() == 1) {
                c[s] = local_stageThr(flash[0], c[s-1], s, d, a, b);
            } else if (flash.length() == 2) {
                vector<int> temp(6, 0);
                temp[4] = local_addColorMix(flash);

                if (temp[4] == 2) {
                    c[s] = local_moduloRule(local_stageThr(local_missingColor(flash), c[s-1], s, d, a, b) + local_stageThr(local_missingColor(flash), b[s-1], s, d, a, b) + local_stageThr(local_missingColor(flash), a[s-1], s, d, a, b));
                
                } else if (temp[4] == 3) {
                    for (int i = 0; i < 2; i++)
                        temp[i] = local_stageThr(flash[i], c[s-1], s, d, a, b); 
                    temp[2] = local_moduloRule(-1 * local_abs(local_stageThr(flash[0], c[s-1], s, d, a, b) - local_stageThr(flash[1], c[s-1], s, d, a, b)));
                    c[s] = local_min(temp, 3);

                } else if (temp[4] == 4) {
                    c[s] = local_moduloRule(local_stageThr(local_missingColor(flash), c[s-1], s, d, a, b) - local_stageThr(flash[0], c[s-1], s, d, a, b) - local_stageThr(flash[1], c[s-1], s, d, a, b));
                }

            } else if (flash.length() == 3) {
                vector<int> temp(6, 0); 
                temp[5] = local_addColorMix(flash);

                if (temp[5] == 3) {
                    c[s] = local_moduloRule(c[s-1] + (local_mod(c[s-1], 3) * c[0]) - (local_mod(b[s-1], 3) * b[0]) + (local_mod(a[s-1], 3) * a[0]));
                    
                } else if (temp[5] == 4) {
                    for (int i = 0; i < 3; i++) {
                        if (flash[i] == 'r' || flash[i] == 'g' || flash[i] == 'b') {
                            temp[i] = local_stageThr(flash[i], c[s-1], s, d, a, b);
                        } else {
                            temp[3] = local_stageThr(flash[i], b[s-1], s, d, a, b);
                            temp[4] = local_stageThr(flash[i], a[s-1], s, d, a, b);
                        }
                    }
                    c[s] = temp[0] + temp[1] + temp[2] - temp[3] - temp[4];

                } else if (temp[5] == 5) {
                    for (int i = 0; i < 3; i++) {
                        if (flash[i] == 'c' || flash[i] == 'm' || flash[i] == 'y') {
                            temp[i] = local_stageThr(flash[i], c[s-1], s, d, a, b);
                        } else {
                            temp[3] = local_stageThr(flash[i], b[s-1], s, d, a, b);
                            temp[4] = local_stageThr(flash[i], a[s-1], s, d, a, b);
                        }
                    }
                    c[s] = local_moduloRule(temp[0] + temp[1] + temp[2] - temp[3] - temp[4]);

                } else if (temp[5] == 6) {
                    c[s] = local_moduloRule(c[s-1] + (local_mod(c[0], 3) * c[s-1]) - (local_mod(b[0], 3) * b[s-1]) + (local_mod(a[0], 3) * a[s-1]));
                }
            }
        }

        local_colorSumbitingOrder(colorOrder, colorStageThree);
        balancedTernaryConverter.convert(c[5]);
        cout << endl;

    } while (userMenu());
}