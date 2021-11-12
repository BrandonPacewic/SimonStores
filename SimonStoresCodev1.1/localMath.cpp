//fixed modulo value 0-y
int local_mod (int x, const int y) {
    if (x >= y) {
        x = x % y;
    } else if(x < 0) {
        x = (x % y) + y;
    }
    return(x);
}

//modual rule range = -364/364
int local_moduloRule (int x) {
    if (x >= 365 || x <= -365) 
        x = x % 365;
    return(x);
}

//function for balenced ternary convertion
std::string local_ternaryConverter (int x) {
    //x is the value to be converted
    //y is the value to be returned
    std::vector<int> ternaryArr(6, 0);
    std::string y = "------";
    bool neg = false;

    if (x < 0) neg = true;
    
    //first int if number is > 243
    if (abs(x) >= 243) {
        ternaryArr[0] = 1;
        x = abs(x) - 243;
    }

    //next is more than 81
    if (abs(x) >= 81) {
        ternaryArr[1] = 1;
        x = abs(x) - 81;
        if (x >= 81) {
            ternaryArr[1] = 2;
            x = x - 81;
        }
    }

    //more than 27
    if (abs(x) >= 27) {
        ternaryArr[2] = 1;
        x = abs(x) - 27;
        if (x >= 27) { 
            ternaryArr[2] = 2;
            x = x -27;
        }
    }

    //more than 9
    if (abs(x) >= 9) {
        ternaryArr[3] = 1;
        x = abs(x) - 9;
        if (x >= 9) {
            ternaryArr[3] = 2;
            x = x - 9;
        }
    }

    //more than 3
    if (abs(x) >= 3) {
        ternaryArr[4] = 1;
        x = abs(x) - 3;
        if (x >= 3) {
            ternaryArr[4] = 2;
            x = x - 3;
        }
    }

    //more than 1 leftover
    if (abs(x) >= 1) {
        ternaryArr[5] = 1;
        x = abs(x) - 1;
        if (x == 1) { 
            ternaryArr[5] = 2;
        }
    }

    
    //now we convert ternaryArr(0, 1, 2) into balenced ternaryArr (-1, 0, 1)
    for (int i = 5; i >= 0; i--) {
        if (ternaryArr[i] == 3) {
            ternaryArr[i] = 0;
            ternaryArr[i-1] = ternaryArr[i-1] + 1;
        } else if(ternaryArr[i] == 2) {
            ternaryArr[i] = -1;
            ternaryArr[i-1] = ternaryArr[i-1] + 1;
        }
    }
    
    //if intial number was neg we invert all the signs
    if (neg == true) {
        for (int i = 0; i < 6; i++) {
            if (ternaryArr[i] == 1) {
                ternaryArr[i] = -1;
            } else if(ternaryArr[i] == -1) 
                ternaryArr[i] = 1;
        }
    }

    //string set up for white (w) and black(k) for 1, -1
    for (int i = 0; i < 6; i++) {
        if (ternaryArr[i] == 1) {
            y[i] = 'w';
        } else if(ternaryArr[i] == -1) 
            y[i] = 'k';
    }
    return(y);
}

//base 36 convertion
void local_baseConverter (std::string str, int numOrChar[], int base36[]) {
    for (int i = 0; i < 6; i++) 
        base36[i] = str[i] - 96;
    
    for (int i = 0; i < 6; i++) {
        if (base36[i] < 0) {
            base36[i] = base36[i] + 48;
            numOrChar[i] = 0;//if int = 0
        } else {
            numOrChar[i] = 1;//if char = 1
        }
    }
}

//exponent function
int local_pow (int base, const int exponent) {
    if (exponent == 0)
        return 1;

    int x = base;
    for (int i = 0; i < exponent - 1; i++) 
        base *= x;
    return(base);
}

//max function
int local_max (std::vector<int> x, const int size) {
    int y = -999;
    for (int i = 0; i < size; i++) 
        if (x[i] > y) 
            y = x[i];
    return(y);
}

//min function
int local_min (std::vector<int> x, const int size) {
    int y = 999;
    for (int i = 0; i < size; i++) 
        if (x[i] < y) 
            y = x[i];
    return(y);
}

//absolute value function
int local_abs (int x) {
    if (x < 0) 
        x = x * -1;
    return(x);
}