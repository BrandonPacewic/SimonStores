#include <iostream>
#include <string>

bool userMenu() {
    std::string x;
    std::cout << "What would you like to do?" << '\n' << "Continue or Quit(c,q): ";
    getline(std::cin, x);

    while (tolower(x[0]) != 'q' && tolower(x[0]) != 'c' || x.length() != 1) {
        std::cout << "You did not enter a valid input please try again." << '\n' << "What would you like to do?" << '\n' << "Continue or Quit(c,q):";
        getline(std::cin, x);
    }

    if (tolower(x[0]) == 'c') {
        return true;
    }

    return false;
}