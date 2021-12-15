#include <iostream>
#include <cassert>

class errorCatch {
private:

    static void local_checkForRequiredSize(std::string &testStr, const int requiredSize) {
        while (testStr.length() != requiredSize) {
            std::cout << '\n' << '\n' << "You did not meet the required size of " << requiredSize << '.' << '\n' << "Please try again: ";
            getline(std::cin, testStr);
        }

        std::cout << '\n';
    }

    static void local_checkForMaxSize(std::string &testStr, const int maxSize) {
        while (testStr.length() > maxSize) {
            std::cout << '\n' << '\n' << "You exceeded the maximum size of " << maxSize << '.' << '\n' << "please try again: ";
            getline(std::cin, testStr);
        }

        std::cout << '\n';
    }

    static std::string local_convertToLower(std::string &str) {
        for (auto &ch : str) {
            ch = tolower(ch);
        }

        return str;
    }

    static void checkForLizzardInput(std::string &testStr) {
        while (local_convertToLower(testStr) == "lizard") {
            std::cout << '\n' << '\n' << "Stop it... You know that Lizard is not a valid input..." << '\n' << "I guess try again? ";
            getline(std::cin, testStr);
        }
    }

public:

    static std::string userStringInput(const std::string inputType, const int expectedLength) {
        assert(inputType == "CheckForRequiredSize" || inputType == "CheckForMaxSize");
        
        std::string userInputStr;
        getline(std::cin, userInputStr);

        //Lizard is never a valid input
        checkForLizzardInput(userInputStr);

        if (inputType == "CheckForRequiredSize") {
            local_checkForRequiredSize(userInputStr, expectedLength);

        } else if (inputType == "CheckForMaxSize") {
            local_checkForMaxSize(userInputStr, expectedLength);
        }

        return userInputStr;
    }

};