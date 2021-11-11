#include "localMath.cpp"

//function for re-ordering color list for input
void local_colorSumbitingOrder (std::string colorOrder, std::string colorStage) {

    //if y is on the top right
    if (colorOrder[0] == 'y') {
        //each color gets shifted 1 right
        std::vector<char> temp(6, '-');
        for (int i = 0; i < 6; i++) 
            temp[i] = colorStage[i];
        
        for (int i = 0; i < 5; i++) 
            colorStage[i+1] = temp[i];
        
        colorStage[0] = temp[5];
    }

    //find r and c in the string if they are opposite swap complementary
    int r, c;
    for (int i = 0; i < 6; i++) { 
        if (colorOrder[i] == 'r') 
            r = i;
        
        if (colorOrder[i] == 'c') 
            c = i;
        
    }

    //swap complementary
    if (r + 3 == c || c + 3 == r) {
        for (int i = 0; i < 6; i++) {
            if (colorStage[i] == 'r') {
                colorStage[i] = 'c';
            } else if (colorStage[i] == 'c') {
                colorStage[i] = 'r';
            } else if (colorStage[i] == 'g') {
                colorStage[i] = 'm';
            } else if (colorStage[i] == 'm') {
                colorStage[i] = 'g';
            } else if (colorStage[i] == 'b') {
                colorStage[i] = 'y';
            } else if (colorStage[i] == 'y') {
                colorStage[i] = 'b';
            }
        }        
    }

    //find g and w in the string if they are adjacent cycle primary colors
    if (colorOrder[0] == 'g' || colorOrder[5] == 'g') {
        //cycle primary colors
        for (int i = 0; i < 6; i++) {
            if (colorStage[i] == 'r') {
                colorStage[i] = 'g';
            } else if (colorStage[i] == 'g') {
                colorStage[i] = 'b';
            } else if (colorStage[i] == 'b') {
                colorStage[i] = 'r';
            }
        }
    }

    //find m if it is at 3 or 4 cycle secondary colors
    int m;
    if (colorOrder[2] == 'm' || colorOrder[3] == 'm') {
        //cycle secondary colors 
        for (int i = 0; i < 6; i++) {
            if (colorStage[i] == 'c') {
                colorStage[i] = 'm';
            } else if (colorStage[i] == 'm') {
                colorStage[i] = 'y';
            } else if (colorStage[i] == 'y') {
                colorStage[i] = 'c';
            }
        }
    }

    //find b and y if they are on the same side swap blue with its opposite
    int b, y, bl; //if value is 1 its on the right if the value is 2 its on the left
    for (int i = 0; i < 6; i++) {
        if (colorOrder[i] == 'b') { 
            if (i <= 2) {
                b = 2;
            } else {
                b = 1;
            }
        }
        if (colorOrder[i] == 'y') {
            if (i <= 2) {
                y = 2;
            } else {
                y = 1;
            }
        }
    }

    if (b == 1 && y == 1 || b == 2 && y == 2) {
        for (int i = 0; i < 6; i++) {
            if (colorStage[i] == 'b') {
                bl = i;
            }
        }
        //swap blue with its opposite
        int opp;
        char temp;
        if (bl == 0) {
            opp = 5;
        } else if (bl == 1) {
            opp = 4;
        } else if (bl == 2) {
            opp = 3;
        } else if (bl == 3) {
            opp = 2;
        } else if (bl == 4) {
            opp = 1;
        } else { 
            opp = 0;
        }

        temp = colorStage[opp];
        colorStage[opp] = 'b';
        colorStage[bl] = temp;
    }

    //if r is on the right swap r and y, we know r and y from a previous step
    if (r <= 2) {
        //swap r and y
        for (int i = 0; i < 6; i++) {
            if (colorStage[i] == 'y') {
                colorStage[i] = 'r';
            } else if (colorStage[i] == 'r') {
                colorStage[i] = 'y';
            }
        }
    }

    //if b is on the left side swap g and c, we know b from a previous step
    if (b == 1) {
        //swap g and c
        for (int i = 0; i < 6; i++) {
            if (colorStage[i] == 'g') {
                colorStage[i] = 'c';
            } else if (colorStage[i] == 'c') {
                colorStage[i] = 'g';
            }
        }
    }

    std::cout << colorStage << '\n';
}

//function for a0 b0 and c0 inital calculations
void local_initalCalculations (int serialBase36[],const int numOrChar[], int a[], int b[], int c[], std::vector<int> temp) {
    //a0
    if (numOrChar[2] == 0) {
        temp[0] = serialBase36[2] * 36;
    } else {
        temp[0] = (serialBase36[2] + 9) * 36;
    }
    if (numOrChar[3] == 0) {
        temp[1] = serialBase36[3];
    } else {
        temp[1] = serialBase36[3] + 9;
    }
    if (temp[0] > 364) {
        temp[0] = temp[0] % 365;
    }
    if (temp[1] > 364) {
        temp[1] = temp[1] % 365;
    }
    a[0] = temp[0] + temp[1];

    //b0
    if (numOrChar[4] == 0) {
        temp[0] = serialBase36[4] * 36;
    } else {
        temp[0] = (serialBase36[4] + 9) * 36; 
    }
    if (temp[0] > 364) {
        temp[0] = temp[0] % 365;
    }
    b[0] = temp[0] + serialBase36[5];//serial pos 5 is always a num

    //c0
    if (numOrChar[0] == 0) {
        temp[0] = serialBase36[0] * 36;
    } else {
        temp[0] = (serialBase36[0] + 9) * 36;
    }
    if (numOrChar[1] == 1) {
        temp[1] = serialBase36[1] + 9;
    } else {
        temp[1] = serialBase36[1];
    }
    if (temp[0] > 364) {
        temp[0] = temp[0] % 365;
    }
    if (temp[1] > 364) {
        temp[1] = temp[1] % 365;
    }
    c[0] = temp[0] + temp[1];
}

int local_dCalculation (int serialBase36[], int numOrChar[]) {
    int d = 0;
    for (int i = 0; i < 6; i++) {
        if (numOrChar[i] == 0) {
        d = d + serialBase36[i];
        } else {
            d = d + (serialBase36[i] + 9);
        }
    }
    return(d);
}

//stage 1 color calculations
int local_stageOne (const char color, int x, int s, int d) {
    int y;
    switch (tolower(color)) {
        case 'r':
            y = x + d;
            break;
        case 'g':
            y = x - d;
            break;
        case 'b':
            y = (2 * x) - d;
            break;
        case 'c':
            y = d - x - (s * 8);
            break;
        case 'm':
            y = (3 * local_pow(s, 3)) - (2 * x);
            break;
        case 'y':
            y = x + d - (s * 6);
            break;
    }
    y = local_moduloRule(y);
    return(y);
}

//stage 2 color calculations
int local_stageTwo (const char color, int x, int s, int d, int a[]) {
    int y;
    switch (tolower(color)) {
        case 'r':
            y = x + a[s-1] + local_pow(s, 2);
            break;
        case 'g':
            y = (x * 2) - a[s-1];
            break;
        case 'b':
            y = (x * 2) - a[0] - (4 * local_pow(s, 2));
            break;
        case 'c':
            y = x + a[1];
            break;
        case 'm':
            y = x + a[2] - d;
            break;
        case 'y':
            y = x + a[3] - a[s-1];
            break;
    }
    y = local_moduloRule(y);
    return(y);
}

//stage 3 color calculations
int local_stageThr (const char color, int x, int s, int d, int a[], int b[]) {
    int y;
    a[4] = 0;//a4 is marked as 0 because we only have 4 A values
    switch (tolower(color)) {
        case 'r':
            y = x + b[s-1] - a[s-1];
            break;
        case 'g':
            y = x - (b[s-1] * 2);
            break;
        case 'b':
            y = x + b[0] - a[3];
            break;
        case 'c':
            y = x - b[s-1] + a[s-1];
            break;
        case 'm':
            y = x - (a[s-1] * 2);
            break;
        case 'y':
            y = x + b[4] - a[0];
            break;
    }
    y = local_moduloRule(y);
    return(y);
}
    
//function for determining the number of primary or seconday color flashes in a muit color flash sequence
int local_addColorMix (std::string flash, std::vector<int> temp) {
    
    for (int i = flash.length(); i > 0; i--) {
        if (flash[i-1] == 'r' || flash[i-1] == 'g' || flash[i-1] == 'b') {
            temp[i-1] = 1;
        } else {
            temp[i-1] = 2;
        }
    }
    return(temp[0] + temp[1] + temp[2]);
}

//function for detmining what color of two did not flash
auto local_missingColor (std::string flash) {
    int x = 0, primary = 0;
    for (int i = 0; i < 2; i++) {
        switch (flash[i]) {
            case 'r':
                x = x + 1;
                primary = 1;
                break;
            case 'g':
                x = x + 2;
                primary = 1;
                break;
            case 'b':
                x = x + 3;
                primary = 1;
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

    if (primary) {
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
        }
    }
}
