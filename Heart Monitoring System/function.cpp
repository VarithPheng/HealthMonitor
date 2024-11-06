#include <iostream>
#include <string>
#include "function.h"
using namespace std;

// check if the input is male
bool isMale(string gender) {
    if (gender == "male") {
        return true;
    }
    else {
        return false;
    }
}

// check if the input is female
bool isFemale(string gender) {
    if (gender == "female") {
        return true;
    }
    else {
        return false;
    }
}

// assign the input into respective ageGroup
string assignAgeGroup(int ageGroup) {
    string ageGroupArray[8] = {
        "Newborn",
        "Infant",
        "Toddler",
        "Preschooler",
        "School-Aged Children",
        "Teenager",
        "Adult",
        "Older Adult"
    };
    return ageGroupArray[ageGroup - 1];
}
