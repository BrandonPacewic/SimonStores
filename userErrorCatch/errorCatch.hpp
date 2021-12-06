#include <iostream>
#include <cassert>

class ErrorCatch {
private:

    static void local_checkForRequiredSize(std::string &testStr, const int requiredSize) {
        while (testStr.length() != requiredSize) {
            std::cout << '\n' << '\n' << "You did not meet the required size of " << requiredSize << '.' << '\n' << "Please try again:";
            getline(std::cin, testStr);
        }
    }

    static void local_checkForMaxSize(std::string &testStr, const int maxSize) {
        while (testStr.length() > maxSize) {
            std::cout << '\n' << '\n' << "You exceeded the maximum size of " << maxSize << '.' << '\n' << "please try again:";
            getline(std::cin, testStr);
        }
    }

public:

    static std::string userStringInput(const std::string inputType, const int expectedLength) {
        std::string userInputStr;
        getline(std::cin, userInputStr);

        if (inputType == "CheckForRequiredSize") {
            local_checkForRequiredSize(userInputStr, expectedLength);
        } else if (inputType == "CheckForMaxSize") {
            local_checkForMaxSize(userInputStr, expectedLength);
        } else {
            assert(false);
        }

        return userInputStr;
    }

};