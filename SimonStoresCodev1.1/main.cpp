#include <bits/stdc++.h>
#define pb push_back
#define endl cout << '\n'

using namespace std;
#include "modualRuleset.cpp" //<-includes "localMath.cpp"
#include "balancedConverter.hpp"

//dbg
template <typename T> T printList(T in, const int si) { for (int i = 0; i < si; i++) { cout << in[i] << ' '; } return in; }
template <typename T> T printReverse(T in, const int si) { for (int i = si - 1; i >= 0; i--) { cout << in[i]; } endl; return in; }
template <typename funfun> funfun intDbg(funfun test, const int si) { cout << "{ "; printList(test, si); cout << " } \n"; return test; }

//user menu
int userMenu() {
    char x;
    cout << "What would you like to do? \n Continue or Quit (c,q): ";
    cin >> x;
    while (tolower(x) != 'q' && tolower(x) != 'c') {
        cout << "You did not enter a valid input please try again. \n";
        cout << "What would you like to do? \n Continue or Quit (c,q): ";
        cin >> x;
    }
    if (tolower(x) == 'c')
        return 1;
    return 0;
}

int main() {
    //vars
    int numOrChar[6];//used for base 36 convertion
    int serialBase36[6];//the base 36 value of the serial number
    int a[5];//each arr only has pos for the numbers we need
    int b[6];//a,b and c values specifyed from the manual page
    int c[7];
    int d = 0;//sum of base 36 in serial#
    string stageFlash[6];
    string serial, colorOrder, stageColorOrder, flash;

    //color list arrs    
    const string colorStageOne = "rgbcmy";
    const string colorStageTwo = "ybgmcr"; 
    const string colorStageThree = "bmrygc";

    //intro
    cout << "\n Welcome to F3m4s's Script for sloving Simon Stores! \n";
    cout << "Lets get started! \n";

    do {
        //user input
        //cout << "Enter the Serial#: ";
        cin >> serial;
        //cout << "Order of Colors: ";
        cin >> colorOrder;
        //cout << "First Color Flash: ";
        cin >> stageFlash[0];
        //cout << "Second Color Flash: ";
        cin >> stageFlash[1];
        //cout << "Third Color Flash: ";
        cin >> stageFlash[2]; 
        endl;

        //base 36 convertion
        local_baseConverter(serial, numOrChar, serialBase36);

        //inital calculations
        if (1) {
            vector<int> temp(6, 0);
            local_initalCalculations(serialBase36, numOrChar, a, b, c, temp);
        }

        //calculating d
        d = local_dCalculation(serialBase36, numOrChar);

        //*********//
        //stage one//
        //*********//
        for (int s = 1; s <= 3; s++) {//s being the step in the stage (starts at 1)
            flash = stageFlash[s-1];

            //one color flash
            if (flash.length() == 1) {
                a[s] = local_stageOne(flash[0], a[s-1], s, d);
            } else if (flash.length() == 2) {
                vector<int> temp(6, 0);

                //two color flashes
                temp[2] = local_addColorMix(flash, temp);
                cout << "temp[2]" << temp[2]; endl; 

                //ans 1
                temp[0] = local_stageOne(flash[0], a[s-1], s, d);

                //ans 2
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

                //three color flashes
                temp[3] = local_addColorMix(flash, temp);

                if (temp[3] == 3) {
                    a[s] = local_moduloRule(a[s-1] + a[0]);
                } else if (temp[3] == 4 || temp[3] == 5) {
                    for (int  i = 0; i < 3; i++) {
                        temp[i] = local_stageOne(flash[i], a[s-1], s, d);
                    }
                    if (temp[3] == 4) {
                        a[s] = local_max(temp, 3);
                    } else { 
                        a[s] = local_min(temp, 3);
                    }
                } else {
                    a[s] = local_moduloRule(a[s-1] - a[0]);
                }
            }
        }

        local_colorSumbitingOrder(colorOrder, colorStageOne);
        local_ternaryConverter(a[3]);

        //*********//
        //stage two//
        //*********//

        //cout << "Forth Color Flash: ";
        cin >> stageFlash[3];
        endl;

        for (int s = 1; s <= 4; s++) { 
             flash = stageFlash[s-1];

             //one color flash
             if (flash.length() == 1) {
                 b[s] = local_stageTwo(flash[0], b[s-1], s, d, a);
             } else if (flash.length() == 2) {
                 vector<int> temp(6, 0);

                 //two color flashes
                 temp[2] = local_addColorMix(flash, temp);

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

                temp[3] = local_addColorMix(flash, temp);

                if (temp[3] == 3) {
                    b[s] = local_moduloRule(b[s-1] + (local_mod(b[s-1], 4) * b[0]) - a[3]);
                } else if (temp[3] == 4) {
                    for (int i = 0; i < 3; i++) {
                        if (flash[i] == 'r' || flash[i] == 'g' || flash[i] == 'b') {
                            temp[i] = local_stageTwo(flash[i], b[s-1], s, d, a);
                        } else {
                            temp[4] = local_stageTwo(flash[i], a[s-1], s, d, a);
                        }
                        b[s] = local_moduloRule(b[s-1] + temp[0] + temp[1] + temp[2] - temp[4]);
                    }
                } else if (temp[3] == 5) {
                    for (int i = 0; i < 3; i++) {
                        cout << i << ' ' << flash[i]; endl;
                        if (flash[i] == 'm' || flash[i] == 'c' || flash[i] == 'y') {
                            temp[i] = local_stageTwo(flash[i], a[s-1], s, d, a);
                        } else {
                            temp[4] = local_stageTwo(flash[i], b[s-1], s, d, a);
                        }
                    }
                    b[s] = local_moduloRule(b[s-1] + temp[0] + temp[1] + temp[2] - temp[4]);
                } else if (temp[3] == 6) {
                    b[s] = local_moduloRule(b[s-1] + (local_mod(b[0], 4) * b[s-1]) - a[3]);
                }
            }
        } 


        local_colorSumbitingOrder(colorOrder, colorStageTwo);
        local_ternaryConverter(b[4]);
        
        //***********//
        //Stage Three//
        //***********//

        //cout << "Fith Color Flash: ";
        cin >> stageFlash[4];
        endl;

        for (int s = 1; s <= 5; s++) {
            flash = stageFlash[s-1]; 

            if (flash.length() == 1) {
                c[s] = local_stageThr(flash[0], c[s-1], s, d, a, b);
            } else if (flash.length() == 2) {
                vector<int> temp(6, 0);
                temp[4] = local_addColorMix(flash, temp);

                if (temp[4] == 2) {
                    char cl = local_missingColor(flash);
                    c[s] = local_stageThr(cl, c[s-1], s, d, a, b) + local_stageThr(cl, b[s-1], s, d, a, b) + local_stageThr(cl, a[s-1], s, d, a, b);
                } else if (temp[4] == 3) {
                    for (int i = 0; i < 2; i++)
                        temp[i] = local_stageThr(flash[i], c[s-1], s, d, a, b); 
                    temp[2] = -1 * local_abs(local_stageThr(flash[0], c[s-1], s, d, a, b) - local_stageThr(flash[1], c[s-1], s, d, a, b));
                    c[s] = local_min(temp, 3);

                } else if (temp[4] == 4) {
                    c[s] = local_stageThr(local_missingColor(flash), c[s-1], s, d, a, b) - local_stageThr(flash[0], c[s-1], s, d, a, b) - local_stageThr(flash[1], c[s-1], s, d, a, b);
                }

            } else if (flash.length() == 3) {
                vector<int> temp(6, 0); 
                temp[5] = local_addColorMix(flash, temp);
                if (temp[5] == 3) {
                    c[s] = c[s-1] + (local_mod(c[s-1], 3) * c[0]) - (local_mod(b[s-1], 3) * b[0]) + (local_mod(a[s-1], 3) * a[0]);
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
                    c[s] = temp[0] + temp[1] + temp[2] - temp[3] - temp[4];

                } else if (temp[5] == 6) {
                    c[s] = c[s-1] + (local_mod(c[0], 3) * c[s-1]) - (local_mod(b[0], 3) * b[s-1]) + (local_mod(a[0], 3) * a[s-1]);
                }
            }
        }

        local_colorSumbitingOrder(colorOrder, colorStageThree);
        local_ternaryConverter(c[5]);

    } while (userMenu);
}