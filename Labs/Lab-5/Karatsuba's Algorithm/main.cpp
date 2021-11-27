#include <iostream>
#include "Polynomial.h"
#include "PolynomialArithmetic.h"
#include <fstream>
#include <tuple>

#define MAX_POLYNOMIAL_DEGREE 100

std::tuple<Polynomial, Polynomial> readPolynomials(std::string filename) {
    std::ifstream in(filename);
    std::deque<int> coefficientsOfTheFirstPolynomial, coefficientsOfTheSecondPolynomial;
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

    Polynomial firstPolynomial(coefficientsOfTheFirstPolynomial, polynomialSize - 1);
    Polynomial secondPolynomial(coefficientsOfTheSecondPolynomial, polynomialSize - 1);

    return std::make_tuple(firstPolynomial, secondPolynomial);
}


int main() {
    // CLion only reads files from the debug directory, hence the ../ expression used in the filepath
    auto [firstPolynomial, secondPolynomial] = readPolynomials("../polynomials.txt");

    firstPolynomial.print();
    secondPolynomial.print();

    Polynomial regularPolynomialMultiplicationResult = PolynomialArithmetic::computeRegularPolynomialMultiplication(
            firstPolynomial, secondPolynomial);
    Polynomial karatsubaPolynomialMultiplicationResult = PolynomialArithmetic::computeKaratsubaPolynomialMultiplication(
            firstPolynomial, secondPolynomial);

    std::cout << "Regular multiplication result:\n";
    regularPolynomialMultiplicationResult.print();
    std::cout << "Karatsuba multiplication result:\n";
    karatsubaPolynomialMultiplicationResult.print();

    return 0;
}
