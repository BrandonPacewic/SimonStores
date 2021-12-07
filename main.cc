#include "local/balancedTernaryConverter/balancedTernaryConverter.hpp"
#include "local/modualRuleSet/modualRuleset.hpp"
#include "local/modualRuleSet/functions.hpp"
#include "local/localMath/modulo.hpp"
#include <algorithm>
using namespace std;


int main() {
    int numOrChar[6];//used for base 36 convertion
    int serialBase36[6];//the base 36 value of the serial number
    vector<int> a(5, 0);//each arr only has pos for the numbers we need
    int b[6];//a,b and c values specifyed from the manual page
    int c[7];
    int d = 0;//sum of base 36 in serial#
    string stageFlash[6];
    string serial, colorOrder, stageColorOrder, flash;

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
        localMath::bace36Converter(serial, numOrChar, serialBase36);

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
                        a[s] = int(max_element(temp.begin(), temp.begin() + 3) - temp.begin());
                        break;
                    case 3:
                        a[s] = temp[0] + temp[1] - (d * 2);
                        break;
                    case 4:
                        a[s] = int(min_element(temp.begin(), temp.begin() + 3) - temp.begin());
                        break;
                }

            } else if (flash.length() == 3) {
                vector<int> temp(6, 0);

                temp[5] = local_addColorMix(flash);

                if (temp[5] == 3) {
                    a[s] = localMath::moduloRule(a[s-1] + a[0]);
                } else if (temp[5] == 4 || temp[5] == 5) {

                    for (int  i = 0; i < 3; i++) 
                        temp[i] = local_stageOne(flash[i], a[s-1], s, d);

                    if (temp[5] == 4) {
                        a[s] = int(max_element(temp.begin(), temp.begin() + 4) - temp.begin());

                    } else { 
                        a[s] = int(max_element(temp.begin(), temp.begin() + 4) - temp.begin());
                    }

                } else {
                    a[s] = localMath::moduloRule(a[s-1] - a[0]);
                }
            }
        }


        localFunctions::printStageColorSequenceStageOne(1, colorOrder);
        balancedTernaryConverter::convert(a[3]);

        //*********//
        //stage two//
        //*********//

        cout << "Forth Color Flash: ";
        getline(cin, stageFlash[3]);
        stageFlash[3] = errorCatch(stageFlash[3], 3, 'm');
        cout << "\n\n";

        for (int s = 1; s <= 4; s++) { 
             flash = stageFlash[s-1];

             if (flash.length() == 1) {
                 b[s] = local_stageTwo(flash[0], b[s-1], s, d, a);


             } else if (flash.length() == 2) {
                 vector<int> temp(6, 0);

                 temp[2] = local_addColorMix(flash);

                 if (temp[2] == 2 || temp[2] == 3) {
                     for (int i = 0; i < 2; i++) {
                         temp[i] = local_stageTwo(flash[i], b[s-1], s, d, a);
                    }

                    if (temp[2] == 2) {
                        b[s] = localMath::moduloRule(abs(temp[0] - temp[1]));
                    } else {
                        b[s] = localMath::moduloRule((4 * d) - abs(temp[0] - temp[1]));
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

                b[s] = int(min_element(temp.begin(), temp.begin() + 3) - temp.begin());
                }


            } else if (flash.length() == 3) {
                vector<int> temp(6, 0);

                temp[3] = local_addColorMix(flash);

                if (temp[3] == 3) {
                    b[s] = localMath::moduloRule(b[s-1] + ((b[s-1] <mod> 4) * b[0]) - a[3]);
                } else if (temp[3] == 4) {
                    for (int i = 0; i < 3; i++) {
                        if (flash[i] == 'r' || flash[i] == 'g' || flash[i] == 'b') {
                            temp[i] = local_stageTwo(flash[i], b[s-1], s, d, a);
                        } else {
                            temp[4] = local_stageTwo(flash[i], a[s-1], s, d, a);
                        }
                        b[s] = localMath::moduloRule(b[s-1] + temp[0] + temp[1] + temp[2] - temp[4]);
                    }
                } else if (temp[3] == 5) {
                    for (int i = 0; i < 3; i++) {
                        if (flash[i] == 'm' || flash[i] == 'c' || flash[i] == 'y') {
                            temp[i] = local_stageTwo(flash[i], a[s-1], s, d, a);
                        } else {
                            temp[4] = local_stageTwo(flash[i], b[s-1], s, d, a);
                        }
                    }

                    b[s] = localMath::moduloRule(b[s-1] + temp[0] + temp[1] + temp[2] - temp[4]);

                } else if (temp[3] == 6) {
                    b[s] = localMath::moduloRule(b[s-1] + ((b[0] <mod> 4) * b[s-1]) - a[3]);
                }
            }
        } 


        localFunctions::printStageColorSequenceStageOne(2, colorOrder);
        balancedTernaryConverter::convert(b[4]);
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
                    c[s] = localMath::moduloRule(local_stageThr(local_missingColor(flash), c[s-1], s, d, a, b) + local_stageThr(local_missingColor(flash), b[s-1], s, d, a, b) + local_stageThr(local_missingColor(flash), a[s-1], s, d, a, b));
                
                } else if (temp[4] == 3) {
                    for (int i = 0; i < 2; i++)
                        temp[i] = local_stageThr(flash[i], c[s-1], s, d, a, b); 
                    temp[2] = localMath::moduloRule(-1 * abs(local_stageThr(flash[0], c[s-1], s, d, a, b) - local_stageThr(flash[1], c[s-1], s, d, a, b)));
                    c[s] = int(min_element(temp.begin(), temp.begin() + 4) - temp.begin());

                } else if (temp[4] == 4) {
                    c[s] = localMath::moduloRule(local_stageThr(local_missingColor(flash), c[s-1], s, d, a, b) - local_stageThr(flash[0], c[s-1], s, d, a, b) - local_stageThr(flash[1], c[s-1], s, d, a, b));
                }

            } else if (flash.length() == 3) {
                vector<int> temp(6, 0); 
                temp[5] = local_addColorMix(flash);

                if (temp[5] == 3) {
                    c[s] = localMath::moduloRule(c[s-1] + ((c[s-1] <mod> 3) * c[0]) - ((b[s-1] <mod> 3) * b[0]) + ((a[s-1] <mod> 3) * a[0]));
                    
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
                    c[s] = localMath::moduloRule(temp[0] + temp[1] + temp[2] - temp[3] - temp[4]);

                } else if (temp[5] == 6) {
                    c[s] = localMath::moduloRule(c[s-1] + ((c[0] <mod> 3) * c[s-1]) - ((b[0] <mod> 3) * b[s-1]) + ((a[0] <mod> 3) * a[s-1]));
                }
            }
        }

        localFunctions::printStageColorSequenceStageOne(3, colorOrder);
        balancedTernaryConverter::convert(c[5]);
        cout << endl;

    } while (userMenu());
}