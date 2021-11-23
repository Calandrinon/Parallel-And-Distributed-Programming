#include <iostream>
#include <deque>
#include <fstream>
#include <tuple>

#define MAX_POLYNOMIAL_DEGREE 100

std::tuple<std::deque<int>, std::deque<int>> readPolynomials(std::string filename) {
    std::deque<int> coefficientsOfTheFirstPolynomial, coefficientsOfTheSecondPolynomial;
    std::ifstream in(filename);

    int polynomialSize, currentNumber;
    in >> polynomialSize;
    for (int i = 0; i < polynomialSize; i++) {
        in >> currentNumber;
        coefficientsOfTheFirstPolynomial.push_back(currentNumber);
    }

    in >> polynomialSize;
    for (int i = 0; i < polynomialSize; i++) {
        in >> currentNumber;
        coefficientsOfTheSecondPolynomial.push_back(currentNumber);
    }

    return std::make_tuple(coefficientsOfTheFirstPolynomial, coefficientsOfTheSecondPolynomial);
}

std::deque<int> computeRegularPolynomialMultiplication(std::deque<int>& coefficientsOfTheFirstPolynomial,
                                                       std::deque<int>& coefficientsOfTheSecondPolynomial) {
    std::deque<int> result(MAX_POLYNOMIAL_DEGREE, 0);

    for (int firstIndex = 0; firstIndex < coefficientsOfTheFirstPolynomial.size(); firstIndex++) {
        for (int secondIndex = 0; secondIndex < coefficientsOfTheSecondPolynomial.size(); secondIndex++)
            result[firstIndex + secondIndex] += coefficientsOfTheFirstPolynomial[firstIndex] * coefficientsOfTheSecondPolynomial[secondIndex];
    }

    return result;
}

void printResultOfThePolynomialMultiplication(std::deque<int>& firstPolynomial, std::deque<int>& secondPolynomial) {
    int resultSize = firstPolynomial.size() * secondPolynomial.size();
    std::deque<int> result = computeRegularPolynomialMultiplication(firstPolynomial, secondPolynomial);

    for (int index = 0; index < resultSize; index++) {
        if (result[index]) {
            if (index)
                std::cout << " + ";
            std::cout << result[index] << "X^" << index;
        }
    }
}

int main() {
    auto [coefficientsOfTheFirstPolynomial, coefficientsOfTheSecondPolynomial] = readPolynomials("polynomials.txt");
    printResultOfThePolynomialMultiplication(coefficientsOfTheFirstPolynomial, coefficientsOfTheSecondPolynomial);
    return 0;
}
