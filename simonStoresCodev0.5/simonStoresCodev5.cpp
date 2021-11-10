/*
Simon Stores v0.5

This code is to slove the K.T.A.N.E modual Simon Stores consitered to be the most math intensive modual currently in the game
(next to ultra stores of corse)

The only time I have ever sloved this math puzzle by hand it took me over 30min, and that is 
skipping over the hours of work it took just to learn it in the first place.

I have seen it done in under 5, however the time it would take to become this good at a puzzle this hard is unimaginable.
Not to mention with the number of calculations that are required it becomes very easy to make a mistake.

Fortunately computers are much better at math than we are and with the help of Fred here I can slove a puzzle that used to take me over half an hour
in just under 10 seconds.

Lets see if it takes this edit to github

*/

#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

//function for mod 365
int mod(int i){
    if(i > 364){
        i = i % 365;
    }else{
        while(i < -364){
            i = i + 365;
        }
    }
    return(i);
}

//function for balenced ternary convertion
string ternaryConverter(int x, int ternary[]){
    //x is the value to be converted
    //y is the value to be returned
    string y = "------";
    bool neg = false;

    if(x < 0){
        neg = true;
    }

    //first int if number is > 243
    if(abs(x) >= 243){
        ternary[0] = 1;
        x = abs(x) - 243;
    }

    //next is more than 81
    if(abs(x) >= 81){
        ternary[1] = 1;
        x = abs(x) - 81;
        if(x >= 81){
            ternary[1] = 2;
            x = x - 81;
        }
    }

    //more than 27
    if(abs(x) >= 27){
        ternary[2] = 1;
        x = abs(x) - 27;
        if(x >= 27){
            ternary[2] = 2;
            x = x -27;
        }
    }

    //more than 9
    if(abs(x) >= 9){
        ternary[3] = 1;
        x = abs(x) - 9;
        if(x >= 9){
            ternary[3] = 2;
            x = x - 9;
        }
    }

    //more than 3
    if(abs(x) >= 3){
        ternary[4] = 1;
        x = abs(x) - 3;
        if(x >= 3){
            ternary[4] = 2;
            x = x - 3;
        }
    }

    //more than 1 leftover
    if(abs(x) >= 1){
        ternary[5] = 1;
        x = abs(x) - 1;
        if(x == 1){
            ternary[5] = 2;
        }
    }

    
    //now we convert ternary(0, 1, 2) into balenced ternary (-1, 0, 1)
    for(int i = 5; i >= 0; i--){
        if(ternary[i] == 3){
            ternary[i] = 0;
            ternary[i-1] = ternary[i-1] + 1;
        }else if(ternary[i] == 2){
            ternary[i] = -1;
            ternary[i-1] = ternary[i-1] + 1;
        }
    }
    
    
    //if intial number was neg we invert all the signs
    if(neg == true){
        for(int i = 0; i < 6; i++){
            if(ternary[i] == 1){
                ternary[i] = -1;
            }else if(ternary[i] == -1){
                ternary[i] = 1;
            }
        }
    }

    //string set up for white (w) and black(k) for 1, -1
    for(int i = 0; i < 6; i++){
        if(ternary[i] == 1){
            y[i] = 'w';
        }else if(ternary[i] == -1){
            y[i] = 'k';
        }
    }

    //reseting the array
    for(int i = 0; i < 6; i++){
        ternary[i] = 0;
    }
    return(y);
}

//function for re-ordering color list for input
void colorSumbitingOrder(string colorOrder, char colorList[]){
    
    //if y is on the top right
    if(colorOrder[0] == 'y'){
        //each color gets shifted 1 right
        string temp = "------";
        for(int i = 0; i < 6; i++){
            temp[i] = colorList[i];
        }
        for(int i = 0; i < 5; i++){
            colorList[i+1] = temp[i];
        }
        colorList[0] = temp[5];
    }

    //find r and c in the string if they are opposite swap complementary
    int r, c;
    for(int i = 0; i < 6; i++){
        if(colorOrder[i] == 'r'){
            r = i;
        }
        if(colorOrder[i] == 'c'){
            c = i;
        }
    }

    //swap complementary
    if(r + 3 == c || c + 3 == r){
        for(int i = 0; i < 6; i++){
            if(colorList[i] == 'r'){
                colorList[i] = 'c';
            }else if(colorList[i] == 'c'){
                colorList[i] = 'r';
            }else if(colorList[i] == 'g'){
                colorList[i] = 'm';
            }else if(colorList[i] == 'm'){
                colorList[i] = 'g';
            }else if(colorList[i] == 'b'){
                colorList[i] = 'y';
            }else if(colorList[i] == 'y'){
                colorList[i] = 'b';
            }
        }        
    }

    //find g and w in the string if they are adjacent cycle primary colors
    if(colorOrder[0] == 'g' || colorOrder[5] == 'g'){
        //cycle primary colors
        for(int i = 0; i < 6; i++){
            if(colorList[i] == 'r'){
                colorList[i] = 'g';
            }else if(colorList[i] == 'g'){
                colorList[i] = 'b';
            }else if(colorList[i] == 'b'){
                colorList[i] = 'r';
            }
        }
    }

    //find m if it is at 3 or 4 cycle secondary colors
    int m;
    if(colorOrder[2] == 'm' || colorOrder[3] == 'm'){
        //cycle secondary colors 
        for(int i = 0; i < 6; i++){
            if(colorList[i] == 'c'){
                colorList[i] = 'm';
            }else if(colorList[i] == 'm'){
                colorList[i] = 'y';
            }else if(colorList[i] == 'y'){
                colorList[i] = 'c';
            }
        }
    }

    //find b and y if they are on the same side swap blue with its opposite
    int b, y, bl; //if value is 1 its on the right if the value is 2 its on the left
    for(int i = 0; i < 6; i++){
        if(colorOrder[i] == 'b'){
            if(i <= 2){
                b = 2;
            }else{
                b = 1;
            }
        }
        if(colorOrder[i] == 'y'){
            if(i <= 2){
                y = 2;
            }else{
                y = 1;
            }
        }
    }

    if(b == 1 && y == 1 || b == 2 && y == 2){
        for(int i = 0; i < 6; i++){
            if(colorList[i] == 'b'){
                bl = i;
            }
        }
        //swap blue with its opposite
        int opp;
        char temp;
        if(bl == 0){
            opp = 5;
        }else if(bl == 1){
            opp = 4;
        }else if(bl == 2){
            opp = 3;
        }else if(bl == 3){
            opp = 2;
        }else if(bl == 4){
            opp = 1;
        }else{
            opp = 0;
        }

        temp = colorList[opp];
        colorList[opp] = 'b';
        colorList[bl] = temp;
    }

    //if r is on the right swap r and y, we know r and y from a previous step
    if(r <= 2){
        //swap r and y
        for(int i = 0; i < 6; i++){
            if(colorList[i] == 'y'){
                colorList[i] = 'r';
            }else if(colorList[i] == 'r'){
                colorList[i] = 'y';
            }
        }
    }

    //if b is on the left side swap g and c, we know b from a previous step
    if(b == 1){
        //swap g and c
        for(int i = 0; i < 6; i++){
            if(colorList[i] == 'g'){
                colorList[i] = 'c';
            }else if(colorList[i] == 'c'){
                colorList[i] = 'g';
            }
        }
    }
}

//function for printing array(int)
void printArray(int s, int array[]){
    cout << "{ ";
    for(int i = 0; i < s; i++){
        cout << array[i] << " ";
    }
    cout << "}" << endl;
}

//function for printing array in reverse (used for ternary)
void printReverse(int s, string str){
    for(int i = 5; i >= 0; i--){
        cout << str[i];
    }
    cout << endl;
}

//function for printing array (char)
void printChar(int s, char array[]){
    for(int i = 0; i < s; i++){
        cout << array[i];
    }
    cout << endl;
}

//functions for stage 1 color calculations
//red1 = x + d
int rOne(int s, int d, int a[]){
    int tmp = a[s-1] + d;
    if(tmp > 364){
        tmp = tmp % 365;
    }
    while(tmp < -364){
        tmp = tmp + 365;
    }
    return(tmp);
}
//green1 = x - d
int gOne(int s, int d, int a[]){
    int tmp = a[s-1] - d;
    if(tmp > 364){
        tmp = tmp % 365;
    }
    while(tmp < -364){
        tmp = tmp + 365;
    }
    return(tmp);
}
//blue1 = 2x - d
int bOne(int s, int d, int a[]){
    int tmp = (2 * a[s-1]) - d;
    if(tmp > 364){
        tmp = tmp % 365;
    }
    while(tmp < -364){
        tmp = tmp + 365;
    }
    return(tmp);
}
//cyan1 = d - x - 8s
int cOne(int s, int d, int a[]){
    int tmp = d - a[s-1] - (8 * s);
    if(tmp > 364){
        tmp = tmp % 365;
    }
    while(tmp < -364){
        tmp = tmp + 365;
    }
    return(tmp);
}
//magenta1 = 3s^3 - 2x
int mOne(int s, int a[]){
    cout << "s = " << s << " a[s-1] = " << a[s-1] << endl;
    int tmp = (3 * pow(s, 3)) - (2 * a[s-1]);
    cout << "tmp = " << tmp << endl;
    if(tmp > 364){
        tmp = tmp % 365;
    }
    while(tmp < -364){
        tmp = tmp + 365;
    }
    return(tmp);
}
//yellow1 = x + d - 6s
int yOne(int s, int d, int a[]){
    int tmp = a[s-1] + d - (6 * s);
    if(tmp > 364){
        tmp = tmp % 365;
    }
    while(tmp < -364){
        tmp = tmp + 365;
    }
    return(tmp);
}

//poop (Danny was here)
//functions for stage 2 color calculations
//red2 = x + as-1 + s^2
int rTwo(int s, int a[], int b[]){
    int tmp = b[s-1] + a[s-1] + pow(s, 2);
    if(tmp > 364){
        tmp = tmp % 365;
    }
    while(tmp < -364){
        tmp = tmp + 365;
    }
    return(tmp);
}
//green2 = 2x - as-1
int gTwo(int s, int a[], int b[]){
    int tmp = (2 * b[s-1]) - a[s-1];
    if(tmp > 364){
        tmp = tmp % 365;
    }
    while(tmp < -364){
        tmp = tmp + 365;
    }
    return(tmp);
}
//blue2 = 2x - a0 - 4s^2
int bTwo(int s, int a[], int b[]){
    int tmp = (2 * b[s-1]) - a[0] - (4 * pow(s, 2));
    if(tmp > 364){
        tmp = tmp % 365;
    }
    while(tmp < -364){
        tmp = tmp + 365;
    }
    return(tmp);
}
//cyan2 = x + a1
int cTwo(int s, int a[], int b[]){
    int tmp = b[s-1] + a[1];
    if(tmp > 364){
        tmp = tmp % 365;
    }
    while(tmp < -364){
        tmp = tmp + 365;
    }
    return(tmp);
}
//magenta2 = x + a2 - d
int mTwo(int s, int a[], int b[], int d){
    int tmp = b[s-1] + a[2] - d;
    if(tmp > 364){
        tmp = tmp % 365;
    }
    while(tmp < -364){
        tmp = tmp + 365;
    }
    return(tmp);
}
//yellow2 = x + a3 - as-1
int yTwo(int s, int a[], int b[]){
    int tmp = b[s-1] + a[3] - a[s-1];
    if(tmp > 364){
        tmp = tmp % 365;
    }
    while(tmp < -364){
        tmp = tmp + 365;
    }
    return(tmp);
}

//functions for stage 3 color calculations
//red3 = x + bs-1 - as-1
int rThr(int s, int a[], int b[], int c[]){
    int tmp = c[s-1] + b[s-1] - a[s-1];
    if(tmp > 364){
        tmp = tmp % 365;
    }
    while(tmp < -364){
        tmp = tmp + 365;
    }
    return(tmp);
}
//green3 = x - 2bs-1
int gThr(int s, int b[], int c[]){
    int tmp = c[s-1] - (2 * b[s-1]);
    if(tmp > 364){
        tmp = tmp % 365;
    }
    while(tmp < -364){
        tmp = tmp + 365;
    }
    return(tmp);
}

//blue3 = x + b0 - a3
int bThr(int s, int a[], int b[], int c[]){
    int tmp = c[s-1] + b[0] - a[3];
    if(tmp > 364){
        tmp = tmp % 365;
    }
    while(tmp < -364){
        tmp = tmp + 365;
    }
    return(tmp);
}

//cyan3 = x - bs-1 + as-1
int cThr(int s, int a[], int b[], int c[]){
    int tmp = c[s-1] - b[s-1] + a[s-1];
    if(tmp > 364){
        tmp = tmp % 365;
    }
    while(tmp < -364){
        tmp = tmp + 365;
    }
    return(tmp);
}

//magenta3 = x - 2as-1
int mThr(int s, int a[], int c[]){
    int tmp = c[s-1] - (2 * a[s-1]);
    if(tmp > 364){
        tmp = tmp % 365;
    }
    while(tmp < -364){
        tmp = tmp + 365;
    }
    return(tmp);
}

//yellow = x + b4 - a0
int yThr(int s, int a[], int b[], int c[]){
    int tmp = c[s-1] + b[4] - a[0];
    if(tmp > 364){
        tmp = tmp % 365;
    }
    while(tmp < -364){
        tmp = tmp + 365;
    }
    return(tmp);
}



//main
int main(){
    //arrays
    int numOrChar[10];//if the serial pos is a number value == 0, char == 1
    int serialBace36[10];//bace 36 value of serial#
    int alpha[99];//a values
    int bravo[99];//b values
    int charlie[99];//c values
    int ternary[6] = {0, 0, 0, 0, 0, 0};//bace set for ternary calculations
    string stageFlash[10];
    
    //color sequence arrs
    char colorStageOne[6] = { 'r', 'g', 'b', 'c', 'm', 'y' };
    char colorStageTwo[6] = { 'y', 'b', 'g', 'm', 'c', 'r' };
    char colorStageThree[6] = { 'b', 'm', 'r', 'y', 'g', 'c' };
    
    //bomb info vars
    string serial, colorOrder, flash;
    int temp, temp1, temp2;
    alpha[4] = 0; //a4 is refered to as 0
    
    //modual info
    int n = 1; //step of the modual
    int d = 0; //sum of base 36 serial number

    //loop
    int loopControl;
    cout << "Press 1 to continue: ";
    cin >> loopControl;

    while(loopControl == 1){
        //reseting serialbace36
        for(int i = 0; i < 6; i++){
            serialBace36[i] = 0;
        }
        d = 0;

    //user input bomb info
    cout << "Serial#: ";
    cin >> serial;
    cout << endl << "Order of colors: ";
    cin >> colorOrder;
    cout << "First color flash: ";
    cin >> stageFlash[1];//skipping over pos 1 in array (leaving it blank)
    cout << "Second color flash: ";
    cin >> stageFlash[2];
    cout << "Third color flash: ";
    cin >> stageFlash[3];

    //converting serial# into bace 36
    for(int i = 0; i < 6; i++){
        serialBace36[i] = serial[i] - 96;
    }
    for(int i = 0; i < 6; i++){
        if(serialBace36[i] < 0){
            serialBace36[i] = serialBace36[i] + 48;
            numOrChar[i] = 0;
        }else{
            numOrChar[i] = 1;
        }
    }

    //a0 b0 and c0
    //a0 calculations
    //alpha[0] = (serialBace36[2] * 36) + (serialBace36[3] + 9);
    if(numOrChar[2] == 0){
        temp1 = serialBace36[2] * 36;
    }else{
        temp1 = (serialBace36[2] + 9) * 36;
    }
    if(numOrChar[3] == 0){
        temp2 = serialBace36[3];
    }else{
        temp2 = serialBace36[3] + 9;
    }
    if(temp1 > 364){
        temp1 = temp1 % 365;
    }
    if(temp2 > 364){
        temp2 = temp2 % 365;
    }
    alpha[0] = temp1 + temp2;
    
    //b0 calculations
    //bravo[0] = ((serialBace36[4] + 9) * 36) + serialBace36[5];
    if(numOrChar[4] == 0){
        temp1 = serialBace36[4] * 36;
    }else{
        temp1 = (serialBace36[4] + 9) * 36; 
    }
    if(temp1 > 364){
        temp1 = temp1 % 365;
    }
    if(temp2 > 364){
        temp2 = temp2 % 365;
    }
    bravo[0] = temp1 + serialBace36[5];

    //c0 calculations
    //charlie[0] = ((serialBace36[0] + 9) * 36) + (serialBace36[1] + 9);
    if(numOrChar[0] == 0){
        temp1 = serialBace36[0] * 36;
    }else{
        temp1 = (serialBace36[0] + 9) * 36;
    }
    if(numOrChar[1] == 1){
        temp2 = serialBace36[1] + 9;
    }else{
        temp2 = serialBace36[1];
    }
    if(temp1 > 364){
        temp1 = temp1 % 365;
    }
    if(temp2 > 364){
        temp2 = temp2 % 365;
    }
    charlie[0] = temp1 + temp2;

    //d sum bace36
    for(int i = 0; i < 6; i++){
        if(numOrChar[i] == 0){
        d = d + serialBace36[i];
        }else{
            d = d + (serialBace36[i] + 9);
        }
    }


    //------------------------//
    //calculations for stage 1//
    //------------------------//
    for(int i = 1; i <= 3; i++){//starting at 1 so i matches the step of the stage
        flash = stageFlash[i];

        //one color flash
        if(flash.length() == 1){
            if(flash == "r"){
                alpha[i] = rOne(i, d, alpha);
            }else if(flash == "g"){
                alpha[i] = gOne(i, d, alpha);
            }else if(flash == "b"){
                alpha[i] = bOne(i, d, alpha);
            }else if(flash == "c"){
                alpha[i] = cOne(i, d, alpha);
            }else if(flash == "m"){
                alpha[i] = mOne(i, alpha);
            }else if(flash == "y"){
                alpha[i] = yOne(i, d, alpha);
            }
        }

        //two colors flash
        if(flash.length() == 2){
            //stage specific vars
            int ans1, ans2;
            bool pp = false, ps = false, ss = false;

            //find what colors are flashing (primary, secondary)
            if(flash[0] == 'r' || flash[0] == 'g' || flash[0] == 'b'){
                if(flash[1] == 'r' || flash[1] == 'g' || flash[1] == 'b'){
                    pp = true;
                }else{
                    ps = true;
                }
            }else{
                if(flash[1] == 'r' || flash[1] == 'g' || flash[1] == 'b'){
                    ps = true;
                }else{
                    ss = true;
                }
            }
  
            //ans1
            if(flash[0] == 'r'){
                ans1 = rOne(i, d, alpha);
            }else if(flash[0] == 'g'){
                ans1 = gOne(i, d, alpha);
            }else if(flash[0] == 'b'){
                ans1 = bOne(i, d, alpha);
            }else if(flash[0] == 'c'){
                ans1 = cOne(i, d, alpha);
                }else if(flash[0] == 'm'){
                ans1 = mOne(i, alpha);
            }else if(flash[0] == 'y'){
                ans1 = yOne(i, d, alpha);
            }else{
                return(1);
            }

            //ans2
            if(flash[1] == 'r'){
                ans2 = rOne(i, d, alpha);
            }else if(flash[1] == 'g'){
                ans2 = gOne(i, d, alpha);
            }else if(flash[1] == 'b'){
                ans2 = bOne(i, d, alpha);
            }else if(flash[1] == 'c'){
                ans2 = cOne(i, d, alpha);
            }else if(flash[1] == 'm'){
                ans2 = mOne(i, alpha);
            }else if(flash[1] == 'y'){
                ans2 = yOne(i, d, alpha);
            }else{
                return(2);
            }
            
            if(pp == true){
                alpha[i] = max(ans1, ans2);
            }else if(ps == true){
                alpha[i] = ans1 + ans2 - (2 * d);
            }else if(ss == true){
                alpha[i] = min(ans1, ans2);
            }
        }
    
       //three colors flash
        if(flash.length() == 3){
            //stage specific vars
            int ans[5];
            bool primary = false, pps = false, pss = false, sss = false;
            for(int u = 0; u < 3; u++){
                if(flash[u] == 'r' || flash[u] == 'g' || flash[u] == 'b'){
                    ans[u] = 1;//if primary value == 1
                }else{
                    ans[u] = 2;//if secondary value == 2
                }
                cout << "---" << u << " - " << ans[u] << "---" << endl;
            }

            if(ans[0] + ans[1] + ans[2] == 3){
                primary = true;
            }else if(ans[0] + ans[1] + ans[2] == 4){
                pps = true;
            }else if(ans[0] + ans[1] + ans[2] == 5){
                pss = true;
            }else if(ans[0] + ans[1] + ans[2] == 6){
                sss = true;
            }

            //calculations
            if(primary == true){
                cout <<  i << " - ppp" << endl;
                alpha[i] = mod(alpha[i-1] + alpha[0]);
            }else if(pps == true || pss == true){
                cout << "i = " << i << endl;
                for(int f = 0; f < 3; f++){
                    if(flash[f] == 'r'){
                        ans[f] = rOne(i, d, alpha);
                    }else if(flash[f] == 'g'){
                        ans[f] = gOne(i, d, alpha);
                    }else if(flash[f] == 'b'){
                        ans[f] = bOne(i, d, alpha);
                    }else if(flash[f] == 'c'){
                        ans[f] = cOne(i, d, alpha);
                    }else if(flash[f] == 'm'){
                        ans[f] = mOne(i, alpha);
                    }else if(flash[f] == 'y'){
                        ans[f] = yOne(i, d, alpha);
                    }
                    cout << "ans[" << f << "] = " << ans[f] << endl; 
                }
                if(pps == true){
                    cout << "pps" << endl;
                    alpha[i] = max(ans[0], max(ans[1], ans[2]));
                }else if(pss == true){
                    cout << "pss" << endl;
                    alpha[i] = min(ans[0], min(ans[1], ans[2]));
                }
            }
            if(sss == true){
                cout << "sss" << endl;
                alpha[i] = mod(alpha[i-2] = alpha[0]);
            }
        }
    }

    //ternary for stage 1
    string prs = ternaryConverter(alpha[3], ternary);

    //color order for stage 1
    colorSumbitingOrder(colorOrder, colorStageOne);

    //debugging info
    cout << "d = " << d << endl;
    printArray(4, alpha);

    //printing answer for stage 1
    //ternary
    cout << endl;
    printReverse(6, prs);

    //color sequence
    printChar(6, colorStageOne);

    //------------------------//
    //Calculations for stage 2//
    //------------------------//

    cout << "Forth color Flash: ";
    cin >> stageFlash[4];

    for(int i = 1; i <= 4; i++){
        flash = stageFlash[i];

        //one color flash
        if(flash.length() == 1){
            if(flash == "r"){
                bravo[i] = rTwo(i, alpha, bravo);
            }else if(flash == "g"){
                bravo[i] = gTwo(i, alpha, bravo);
            }else if(flash == "b"){
                bravo[i] = bTwo(i, alpha, bravo);
            }else if(flash == "c"){
                bravo[i] = cTwo(i, alpha, bravo);
            }else if(flash == "m"){
                bravo[i] = mTwo(i, alpha, bravo, d);
            }else if(flash == "y"){
                bravo[i] = yTwo(i, alpha, bravo);
            }
        }

        //two colors flash
        if(flash.length() == 2){
            //specific stage vars
            int ans[5];
            bool pp = false, ps = false, ss = false;

            for(int u = 0; u < 2; u++){
                if(flash[u] == 'r' || flash[u] == 'g' || flash[u] == 'b'){
                    ans[u] = 1;
                }else{
                    ans[u] = 2;
                }
            }

            ans[4] = ans[1] + ans[0];
            if(ans[0] + ans[1] == 2){
                pp = true;
            }else if(ans[4] == 3){
                ps = true;
            }else if(ans[1] + ans[0] == 4){
                ss = true;
            }

            if(pp == true || ps == true){
                for(int u = 0; u < 2; u++){
                    if(flash[u] == 'r'){
                        ans[u] = rTwo(i, alpha, bravo);
                    }else if(flash[u] == 'g'){
                        ans[u] = gTwo(i, alpha, bravo);
                    }else if(flash[u] == 'b'){
                        ans[u] = bTwo(i, alpha, bravo);
                    }else if(flash[u] == 'c'){
                        ans[u] = cTwo(i, alpha, bravo);
                    }else if(flash[u] == 'm'){
                        ans[u] = mTwo(i, alpha, bravo, d);
                    }else if(flash[u] == 'y'){
                        ans[u] = yTwo(i, alpha, bravo);
                    }
                }
                
                cout << " i = " << i << endl;
                if(pp == true){
                    bravo[i] = mod(abs(ans[0] - ans[1]));
                }else if(ps == true){
                    cout << ans[0] << "--" << ans[1] << endl;
                    temp1 = mod(abs(ans[0] - ans[1]));
                    bravo[i] = mod((4 * d) - temp1);
                }
            }
            
            if(ss == true){
                for(int u = 0; u < 2; u++){
                    if(flash[u] == 'c'){
                        ans[u] = 1;
                    }else if(flash[u] == 'm'){
                        ans[u] = 2;
                    }else if(flash[u] == 'y'){
                        ans[u] = 3;
                    }
                }

                switch (ans[0] + ans[1]){
                    case 5:
                        //cyan
                        ans[0] = cTwo(i, alpha, bravo);
                        ans[1] = mod(alpha[i-1] + alpha[1]);
                        break;
                    case 4:
                        //magenta
                        ans[0] = mTwo(i, alpha, bravo, d);
                        ans[1] = mod(alpha[i-1] + alpha[2] + d);
                        break;
                    case 3:
                        //yellow
                        ans[0] = yTwo(i, alpha, bravo);
                        ans[1] = alpha[3];
                        break;
                }
                
                bravo[i] = max(ans[0], ans[1]);
           }
        }

        //three colors flash
        if(flash.length() == 3){
            //stage specific vars
            int pOrS[10]; //identifying if ans came from primary or secondary color
            int ans[5]; 
            int p1, p2, s1, s2;
            bool ppp = false, pps = false, pss = false, sss = false;

            for(int u = 0; u < 3; u++){
                if(flash[u] == 'r' || flash[u] == 'g' || flash[u] == 'b'){
                    ans[u] = 1;
                }else{
                    ans[u] = 2;
                }
            }

            switch (ans[0] + ans[1] + ans[2]){
                case 3:
                    ppp = true;
                    break;
                case 4:
                    pps = true;
                    break;
                case 5:
                    pss = true;
                    break;
                case 6:
                    sss = true;
                    break;
            }

            if(ppp == true){
                //not the problem
                temp2 = bravo[i-1];
                while(temp2 <= 0){
                    temp2 = temp2 + 4;
                }
                if(temp2 >= 4){
                    temp2 = temp2 % 4;
                }
                //temp1 = mod((bravo[i-1] + (temp2 * bravo[0])) - alpha[3]);
                temp1 = mod(temp2 * bravo[0]);
                bravo[i] = mod((bravo[i-1] + temp1) - alpha[3]);
            }else if(pps == true){
                for(int u = 0; u < 3; u++){
                    if(flash[u] == 'r'){
                        ans[u] = rTwo(i, alpha, bravo);
                        pOrS[u] = 1;
                    }else if(flash[u] == 'g'){
                        ans[u] = gTwo(i, alpha, bravo);
                        pOrS[u] = 1;
                    }else if(flash[u] == 'b'){
                        ans[u] = bTwo(i, alpha, bravo);
                        pOrS[u] = 1;
                    }else if(flash[u] == 'c'){
                        ans[u] = mod(alpha[i-1] + alpha[1]);
                        pOrS[u] = 2;
                    }else if(flash[u] == 'm'){
                        ans[u] = mod(alpha[i-1] + alpha[2] - d);
                        pOrS[u] = 2;
                    }else if(flash[u] == 'y'){
                        ans[u] = mod(alpha[i-1] + alpha[3] - alpha[i-1]);
                        pOrS[u] = 2;
                    }
                }

                cout << "ans[0] " << ans[0] << " ans[1] " << ans[1] << " ans[2]" << ans[2] << endl;
                //reorginising ans so it is in order of pps
                temp1 = 0;
                for(int u = 0; u < 3; u++){
                    if(pOrS[u] == 1){
                        if(temp1 == 0){
                            p1 = ans[u];
                            temp1++;
                        }else if(temp1 == 1){
                            p2 = ans[u];
                        }
                    }else{
                        s1 = ans[u];
                    }           
                }
                bravo[i] = mod(bravo[i-1] + p1 + p2 - s1);
            }else if(pss == true){
                for(int u = 0; u < 3; u++){
                    if(flash[u] == 'r'){
                        ans[u] = rTwo(i, alpha, bravo);
                        pOrS[u] = 1;
                    }else if(flash[u] == 'g'){
                        ans[u] = gTwo(i, alpha, bravo);
                        pOrS[u] = 1;
                    }else if(flash[u] == 'b'){
                        ans[u] = bTwo(i, alpha, bravo);
                        pOrS[u] = 1;
                    }else if(flash[u] == 'c'){
                        ans[u] = mod(alpha[i-1] + alpha[1]);
                        pOrS[u] = 2;
                    }else if(flash[u] == 'm'){
                        ans[u] = mod(alpha[i-1] + alpha[2] - d);
                        pOrS[u] = 2;
                    }else if(flash[u] == 'y'){
                        ans[u] = mod(alpha[i-1] + alpha[3] - alpha[i-1]);
                        pOrS[u] = 2;
                    }
                }
                //reorginising ans so it is in order of ssp
                temp1 = 1;
                for(int u = 0; u < 3; u++){
                    if(pOrS[u] == 2){
                        cout << "secondary color detected" << endl;
                        if(temp1 == 1){
                            cout << "set s1" << endl;
                            s1 = ans[u];
                            temp1++;
                        }else if(temp1 == 2){
                            cout << "set s2" << endl;
                            s2 = ans[u];
                        }                    
                    }else{
                        cout << "set p1" << endl;
                        p1 = ans[u];
                    }
                }

                //cout << ans[0] << " -- " << ans[1] << " -- " << ans[2] << endl;

                cout << "p1 = " << p1 << " s1 = " << s1 << " s2 = " << s2 << endl;
                bravo[i] = mod(bravo[i-1] + s1 + s2 - p1);                
            }else if(sss == true){
                bravo[i] = mod(bravo[i-1] + ((bravo[0] % 4) * bravo[i-1]) - alpha[3]);
            }
        }
    }

    //ternary for stage 2
    prs = ternaryConverter(bravo[4], ternary);

    //color order for stage 2
    colorSumbitingOrder(colorOrder, colorStageTwo);

    //debugging info
    printArray(5, bravo);

    //printing answer for stage 2
    //ternary
    cout << endl;
    printReverse(6, prs);

    //color sequence
    printChar(6, colorStageTwo);


    //------------------------
    //Calculations for Stage 3 
    //------------------------

    cout << "Fith color Flash: ";
    cin >> stageFlash[5];

    for(int i = 1; i <= 5; i++){
        flash = stageFlash[i];

        //one color flash
        if(flash.length() == 1){
            if(flash == "r"){
                charlie[i] = rThr(i, alpha, bravo, charlie);
            }else if(flash == "g"){
                charlie[i] = gThr(i, bravo, charlie);
            }else if(flash == "b"){
                charlie[i] = bThr(i, alpha, bravo, charlie);
            }else if(flash == "c"){
                charlie[i] = cThr(i, alpha, bravo, charlie);
            }else if(flash == "m"){
                charlie[i] = mThr(i, alpha, charlie);
            }else if(flash == "y"){
                charlie[i] = yThr(i, alpha, bravo, charlie);
            }
        }

        //two color flashes
        if(flash.length() == 2){
            //stage specific vars
            int ans[5];
            bool pp = false, ps = false, ss = false;

            for(int u = 0; u < 2; u++){
                if(flash[u] == 'r' || flash[u] == 'g' || flash[u] == 'b'){
                    ans[u] = 1;
                }else{
                    ans[u] = 2;
                }
            }

            if(ans[0] + ans[1] == 2){
                pp = true;
            }else if(ans[0] + ans[1] == 3){
                ps = true;
            }else if(ans[0] + ans[1] == 4){
                ss = true;
            }

            
            if(pp == true){
                for(int u = 0; u < 2; u++){
                    if(flash[u] == 'r'){
                        ans[u] = 1;
                    }else if(flash[u] == 'g'){
                        ans[u] = 2;
                    }else if(flash[u] == 'b'){
                        ans[u] = 3;
                    }
                }

                //switch statment for finding color that did not flash
                switch (ans[0] + ans[1]){
                    case 5:
                        //red
                        ans[0] = rThr(i, alpha, bravo, charlie);
                        ans[1] = mod(bravo[i-1] + bravo[i-1] - alpha[i-1]);
                        ans[2] = mod(alpha[i-1] + bravo[i-1] - alpha[i-1]);
                        break;
                    case 4:
                        //green
                        ans[0] = gThr(i, bravo, charlie);
                        ans[1] = mod(bravo[i-1] - (2 * bravo[i-1]));
                        ans[2] = mod(alpha[i-1] - (2 * bravo[i-1]));
                        break;
                    case 3:
                        //blue
                        ans[0] = bThr(i, alpha, bravo, charlie);
                        ans[1] = mod(bravo[i-1] + bravo[0] - alpha[3]);
                        ans[2] = mod(alpha[i-1] + bravo[0] - alpha[3]);
                        break;
                }

                //final calculation
                charlie[i] = mod(ans[0] + ans[1] + ans[2]);
            }

            if(ps == true){
                //need both color flash numbers
                for(int u = 0; u < 2; u++){
                    if(flash[u] == 'r'){
                        ans[u] = rThr(i, alpha, bravo, charlie);
                    }else if(flash[u] == 'g'){
                        ans[u] = gThr(i, bravo, charlie);
                    }else if(flash[u] == 'b'){
                        ans[u] = bThr(i, alpha, bravo, charlie);
                    }else if(flash[u] == 'c'){
                        ans[u] = cThr(i, alpha, bravo, charlie);
                    }else if(flash[u] == 'm'){
                        ans[u] = mThr(i, alpha, charlie);
                    }else if(flash[u] == 'y'){
                        ans[u] = yThr(i, alpha, bravo, charlie);
                    }
                }

                //final calculation
                ans[2] = mod(abs(ans[0] - ans[1])) - (mod(abs(ans[0] - ans[1])) * 2);
                charlie[i] = min(ans[0], min(ans[1], ans[2]));
            }

            if(ss == true){
                for(int u = 0; u < 2; u++){
                    if(flash[u] == 'c'){
                        ans[u] = 1;
                    }else if(flash[u] == 'm'){
                        ans[u] = 2;
                    }else if(flash[u] == 'y'){
                        ans[u] = 3;
                    }
                }

                switch (ans[0] + ans[1]){
                    case 5:
                        //cyan
                        ans[2] = cThr(i, alpha, bravo, charlie);
                        break;
                    case 4:
                        //magenta
                        ans[2] = mThr(i, alpha, charlie);
                        break;
                    case 3:
                        //yellow
                        ans[2] = yThr(i, alpha, bravo, charlie);
                        break;
                }

                for(int u = 0; u < 2; u++){
                    if(flash[u] == 'c'){
                        ans[u] = cThr(i, alpha, bravo, charlie);
                    }else if(flash[u] == 'm'){
                        ans[u] = mThr(i, alpha, charlie);
                    }else if(flash[u] == 'y'){
                        ans[u] = yThr(i, alpha, bravo, charlie);
                    }
                }
                charlie[i] = mod(ans[2] - ans[0] - ans[1]);
            }
        }

        //three color flashes
        if(flash.length() == 3){
            cout << "3 flash detected" << endl;
            //stage specific vars
            int pOrS[10];
            int ans[7];
            int p1, p2, s1, s2;
            bool ppp = false, pps = false, pss = false, sss = false;

            for(int u = 0; u < 3; u++){
                if(flash[u] == 'r' || flash[u] == 'g' || flash[u] == 'b'){
                    ans[u] = 1;
                }else{
                    ans[u] = 2;
                }
                cout << "loop 1 ran:" << u << endl; 
            }

            switch (ans[0] + ans[1] + ans[2]){
                case 3:
                    ppp = true;
                    cout << "switch 1 worked" << endl;
                    break;
                case 4:
                    pps = true;
                    cout << "switch 1 worked" << endl;
                    break;
                case 5:
                    pss = true;
                    cout << "switch 1 worked" << endl;
                    break;
                case 6:
                    sss = true;
                    cout << "switch 1 worked" << endl;
                    break;
            }

            //3 primary
            if(ppp == true){
                charlie[i] = mod(charlie[i-1] + ((charlie[i-1] % 3) * charlie[0]) - ((bravo[i-1] % 3) * bravo[0]) + ((alpha[i-1] % 3) * alpha[0]));
            }

            //2 primary 1 secondary
            if(pps == true){
                //filling ans will 0s to prevent crash
                for(int u = 0; u < 3; u++){
                    ans[u] = 0;
                }
                for(int u = 0; u < 3; u++){
                    if(flash[u] == 'r'){
                        ans[u] = rThr(i, alpha, bravo, charlie);
                    }else if(flash[u] == 'g'){
                        ans[u] = gThr(i, bravo, charlie);
                    }else if(flash[u] == 'b'){
                        ans[u] = bThr(i, alpha, bravo, charlie);
                    }
                }

                for(int u = 0; u < 3; u++){
                    if(flash[u] == 'c'){
                        ans[4] = bravo[i-1] - bravo[i-1] + alpha[i-1];
                        ans[5] = alpha[i-1] - bravo[i-1] + alpha[i-1];
                    }else if(flash[u] == 'm'){
                        ans[4] = bravo[i-1] - (2 * alpha[i-1]);
                        ans[5] = alpha[i-1] - (2 * alpha[i-1]);
                    }else if(flash[u] == 'y'){
                        ans[4] = bravo[i-1] + bravo[4] - alpha[0];
                        ans[5] = alpha[i-1] + bravo[4] - alpha[0];
                    }
                }

                //final calculations
                charlie[i] = mod(ans[0] + ans[1] + ans[2] - ans[4] - ans[5]);
                
            }

            //1 primary 2 secondary
            if(pss == true){
                cout << "if 1 worked" << endl;
                //fixing later step by filling ans with 0s
                for(int u = 0; u < 3; u++){
                    ans[u] = 0;
                }

                for(int u = 0; u < 3; u++){
                    
                    //broken
                    if(flash[u] == 'c'){
                        ans[u] = cThr(i, alpha, bravo, charlie);
                    }else if(flash[u] == 'm'){
                        ans[u] = mThr(i, alpha, charlie);
                    }else if(flash[u] == 'y'){
                        ans[u] = yThr(i, alpha, bravo, charlie);
                    }
                }

                for(int u = 0; u < 3; u++){
                    if(flash[u] == 'r'){
                        ans[4] = bravo[i-1] + bravo[i-1] - alpha[i-1];
                        ans[5] = alpha[i-1] + bravo[i-1] - alpha[i-1];
                    }else if(flash[u] == 'g'){
                        ans[4] = bravo[i-1] - (2 * bravo[i-1]);
                        ans[5] = alpha[i-1] - (2 * bravo[i-1]);
                    }else if(flash[u] == 'b'){
                        ans[4] = bravo[i-1] + bravo[0] - alpha[3];
                        ans[5] = alpha[i-1] + bravo[0] - alpha[3];
                    }
                }
                cout << "done with 3 flash calculations" << endl;
                //final calculation
                charlie[i] = mod(ans[0] + ans[1] + ans[2] - ans[4] - ans[5]);
            }

            //3 secondary
            if(sss == true){
                charlie[i] = mod(charlie[i-1] + ((charlie[0] % 3) * charlie[i-1]) - ((bravo[0] % 3) * bravo[i-1]) + ((alpha[0] % 3) * alpha[i-1]));
            }
        }
    }

    //ternary for stage 3
    prs = ternaryConverter(charlie[5], ternary);

    //color order for stage 3
    colorSumbitingOrder(colorOrder, colorStageThree);

    //debugging info
    printArray(6, charlie);

    //answer for stage 3
    cout << endl;
    printReverse(6, prs);

    //color sequence
    printChar(6, colorStageThree);


    //loop control
    cout << "Press 1 to continue: ";
    cin >> loopControl;


    }//loop end


}