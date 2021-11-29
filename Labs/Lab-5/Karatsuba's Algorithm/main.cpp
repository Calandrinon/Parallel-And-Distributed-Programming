#include <iostream>
#include "Polynomial.h"
#include "PolynomialArithmetic.h"
#include <fstream>
#include <tuple>

#define POLYNOMIAL_PRINT_FLAG true

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

    firstPolynomial.print(POLYNOMIAL_PRINT_FLAG);
    secondPolynomial.print(POLYNOMIAL_PRINT_FLAG);

    Polynomial regularPolynomialMultiplicationResult = PolynomialArithmetic::computeRegularPolynomialMultiplication(
            firstPolynomial, secondPolynomial);
    Polynomial karatsubaPolynomialMultiplicationResult = PolynomialArithmetic::computeKaratsubaPolynomialMultiplication(
            firstPolynomial, secondPolynomial);

    std::cout << "Sequential regular multiplication result:\n";
    regularPolynomialMultiplicationResult.print(POLYNOMIAL_PRINT_FLAG);
    std::cout << "Sequential Karatsuba multiplication result:\n";
    karatsubaPolynomialMultiplicationResult.print(POLYNOMIAL_PRINT_FLAG);
    std::cout << "Parallel regular multiplication result:\n";
    Polynomial parallelRegularPolynomialMultiplicationResult = PolynomialArithmetic::computeParallelizedRegularPolynomialMultiplication(
            firstPolynomial, secondPolynomial);
    parallelRegularPolynomialMultiplicationResult.print(POLYNOMIAL_PRINT_FLAG);
    std::cout << "Parallel Karatsuba multiplication result:\n";
    Polynomial parallelKaratsubaPolynomialMultiplicationResult = PolynomialArithmetic::computeParallelizedKaratsubaPolynomialMultiplication(
            firstPolynomial, secondPolynomial, 4);
    parallelKaratsubaPolynomialMultiplicationResult.print(POLYNOMIAL_PRINT_FLAG);
    return 0;
}
