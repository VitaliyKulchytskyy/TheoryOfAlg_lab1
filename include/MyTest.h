#ifndef LAB1_TEST_CPP
#define LAB1_TEST_H

#include <iostream>

template<typename T>
bool ASSUME_EQ(const std::string &testName, T inputAnswer, T trueAnswer) {
    bool output = inputAnswer == trueAnswer;
    string assuming = (output) ? testName + " - passed." : testName + " - error.";
    std::cout << assuming << '\n';

    return output;
}

#endif //LAB1_TEST_CPP