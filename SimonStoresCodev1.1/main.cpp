#include <bits/stdc++.h>
#define pb push_back
#define endl std::cout << '\n'
#include "modualRuleset.cpp" //<-includes "localMath.cpp"

//print int
void printInt (int s, int array[]) {
    std::cout << "{ ";
    for (int i = 0; i < s; i++) 
        std::cout << array[i] << " ";
    std::cout << "} \n";
}

//print reverse
void printReverse (std::string str, int s) {
    for (int i = s-1; i >= 0; i--) 
        std::cout << str[i];
    endl;
}

//print vec<char>
void printVec (std::vector<char> vec) {
    for (auto i: vec)
        std::cout << i;
    endl;
}

//user menu
int userMenu () {
    char x;
    std::cout << "What would you like to do? \n Continue or Quit (c,q): ";
    std::cin >> x;
    x = tolower(x);
    while (x != 'q' && x != 'c') {
        std::cout << "You did not enter a valid input please try again. \n";
        std::cout << "What would you like to do? \n Continue or Quit (c,q): ";
        std::cin >> x;
        x = tolower(x);
    }
    return(x);
}

int main(){
    //vars
    int numOrChar[6];//used for base 36 convertion
    int serialBase36[6];//the base 36 value of the serial number
    int a[5];//each arr only has pos for the numbers we need
    int b[6];//a,b and c values specifyed from the manual page
    int c[7];
    int d = 0;//sum of base 36 in serial#
    std::string stageFlash[6];
    std::string serial, colorOrder, stageColorOrder, flash;

    //color list arrs    
    const std::string colorStageOne = "rgbcmy";
    const std::string colorStageTwo = "ybgmcr"; 
    const std::string colorStageThree = "bmrygc";

    //first instance of the user menu
    char loopControl = userMenu();

    if (loopControl == 'c') {
        //intro
        std::cout << "\n Welcome to F3m4s's Script for sloving Simon Stores! \n";
        std::cout << "Lets get started! \n";
    }

    //user menu loop
    while (loopControl == 'c') {
        //user input
        std::cout << "Enter the Serial#: ";
        std::cin >> serial;
        std::cout << "Order of Colors: ";
        std::cin >> colorOrder;
        std::cout << "First Color Flash: ";
        std::cin >> stageFlash[0];
        std::cout << "Second Color Flash: ";
        std::cin >> stageFlash[1];
        std::cout << "Third Color Flash: ";
        std::cin >> stageFlash[2]; 

        //base 36 convertion
        local_baseConverter(serial, numOrChar, serialBase36);

        //inital calculations
        if (1) {
            std::vector<int> temp(6, 0);
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
                std::vector<int> temp(6, 0);

                //two color flashes
                temp[2] = local_addColorMix(flash, temp);
                std::cout << "temp[2]" << temp[2]; endl; 

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
                        std::cout << "Something broke come find it";
                        return(0);
                        break;
                }
            } else if (flash.length() == 3) {
                std::vector<int> temp(6, 0);

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

        std::cout << "d = " << d; endl;
        printInt(4, a);

        std::string prs = local_ternaryConverter(a[3]);
        local_colorSumbitingOrder(colorOrder, colorStageOne);
        std::cout << "\n";
        printReverse(prs, 6);

        //*********//
        //stage two//
        //*********//

        std::cout << "Forth Color Flash: ";
        std::cin >> stageFlash[3];

        for (int s = 1; s <= 4; s++) { 
             flash = stageFlash[s-1];

             //one color flash
             if (flash.length() == 1) {
                 b[s] = local_stageTwo(flash[0], b[s-1], s, d, a);
             } else if (flash.length() == 2) {
                 std::vector<int> temp(6, 0);

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
                std::vector<int> temp(6, 0);

                temp[3] = local_addColorMix(flash, temp);

                if (temp[3] == 3) {
                    b[s] = local_moduloRule(b[s-1] + (local_mod(b[s-1], 4) * b[0]) - a[3]);
                } else if (temp[3] == 4) {
                    for (int i = 0; i < 3; i++) {
                        std::cout << "i = " << i; endl; //error
                        if (flash[i] == 'r' || flash[i] == 'g' || flash[i] == 'b') {
                            temp[i] = local_stageTwo(flash[i], b[s-1], s, d, a);
                        } else {
                            temp[4] = local_stageTwo(flash[i], a[s-1], s, d, a);
                        }
                        std::cout << temp[0] << temp[1] << temp[2] << temp[4]; endl; //error
                        b[s] = local_moduloRule(b[s-1] + temp[0] + temp[1] + temp[2] - temp[4]);
                    }
                } else if (temp[3] == 5) {
                    for (int i = 0; i < 3; i++) {
                        if (flash[i] == 'r' || flash[i] == 'g' || flash[i] == 'b') {
                            temp[i] = local_stageTwo(flash[i], b[s-1], s, d, a);
                        } else {
                            temp[4] = local_stageTwo(flash[i], a[s-1], s, d, a);
                        }
                    }
                    b[s] = local_moduloRule(b[s-1] + temp[0] + temp[1] + temp[2] - temp[4]);
                } else if (temp[3] == 6) {
                    b[s] = local_moduloRule(b[s-1] + (local_mod(b[0], 4) * b[s-1]) - a[3]);
                }
            }
        } 

        printInt(5, b);

        prs = local_ternaryConverter(b[4]);
        local_colorSumbitingOrder(colorOrder, colorStageTwo);
        printReverse(prs, 6);
        

        //***********//
        //Stage Three//
        //***********//

        std::cout << "Fith Color Flash: ";
        std::cin >> stageFlash[4];




        //end of loop
        loopControl = userMenu();
    }
}