#include <iostream>
#include <thread>
#include <vector>
#include <fstream>

std::ifstream in("");

std::vector<int> productsBuffer;
std::atomic<int> atomicSum;

std::pair<std::vector<int>, std::vector<int>> readVectors() {
    std::vector<int> firstVector, secondVector;

    // read from vectors.txt

    return std::make_pair(firstVector, secondVector);
}

void productsProducer() {
    // produce products
}

void sumConsumer() {
    // compute the sum of the products (dot product of the two vectors)
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
