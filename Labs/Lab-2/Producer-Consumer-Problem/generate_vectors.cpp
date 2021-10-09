//
// Created by calandrinon on 10/9/21.
//

#include <iostream>
#include <chrono>
#include <random>
#include <vector>
#include <fstream>

int main() {
    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    auto randomEngine = std::default_random_engine(seed);
    unsigned long numberOfElements = randomEngine() % 1000000;
    std::vector<unsigned long> firstVector, secondVector;

    for (int i = 0; i < numberOfElements; i++) {
        auto numberForTheFirstVector = randomEngine(),
             numberForTheSecondVector = randomEngine();

        firstVector.push_back(numberForTheFirstVector);
        secondVector.push_back(numberForTheSecondVector);
    }

    std::ofstream out("vectors.txt");

    for (int i = 0; i < numberOfElements; i++)
        out << firstVector[i] << " ";
    out << "\n";

    for (int i = 0; i < numberOfElements; i++)
        out << secondVector[i] << " ";

    return 0;
}