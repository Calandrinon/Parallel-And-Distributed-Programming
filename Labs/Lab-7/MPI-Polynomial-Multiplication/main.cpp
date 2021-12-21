#include <iostream>
#include "Polynomial.h"
#include "PolynomialArithmetic.h"
#include <fstream>
#include <tuple>
#include <chrono>
#include "mpi.h"

#define POLYNOMIAL_LENGTH 31 // must be of the form (2^n - 1)
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

void regularMultiplication(Polynomial* firstPolynomial, Polynomial* secondPolynomial) {
    auto start = std::chrono::steady_clock::now();
    Polynomial regularPolynomialMultiplicationResult = PolynomialArithmetic::computeRegularPolynomialMultiplication(
            *firstPolynomial, *secondPolynomial);
    auto end = std::chrono::steady_clock::now();
    std::cout << "Regular multiplication result:\n";
    regularPolynomialMultiplicationResult.print(POLYNOMIAL_PRINT_FLAG);
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "Elapsed time: " << elapsed_seconds.count() << " seconds\n";
}


void karatsubaMultiplication(Polynomial* firstPolynomial, Polynomial* secondPolynomial) {
    auto start = std::chrono::steady_clock::now();
    Polynomial karatsubaPolynomialMultiplicationResult = PolynomialArithmetic::computeKaratsubaPolynomialMultiplication(
            *firstPolynomial, *secondPolynomial);
    auto end = std::chrono::steady_clock::now();
    std::cout << "Karatsuba multiplication result:\n";
    karatsubaPolynomialMultiplicationResult.print(POLYNOMIAL_PRINT_FLAG);
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "Elapsed time: " << elapsed_seconds.count() << " seconds\n";
}


void runMasterAndWorker(int argc, char* argv[]) {
    int rank, size, len;
    char version[MPI_MAX_LIBRARY_VERSION_STRING];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Get_library_version(version, &len);
    printf("Hello, world, I am %d of %d, (%s, %d)\n",
           rank, size, version, len);
    MPI_Finalize();
}


int main(int argc, char* argv[]) {
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (!rank) {
        // CLion only reads files from the debug directory, hence the ../ expression used in the filepath
        Polynomial firstPolynomial = Polynomial::generateRandomPolynomialOfSpecificDegree(POLYNOMIAL_LENGTH);
        Polynomial secondPolynomial = Polynomial::generateRandomPolynomialOfSpecificDegree(POLYNOMIAL_LENGTH);

        std::cout << "\n";
        printf("I am master process %d.\n", rank);

        firstPolynomial.print(POLYNOMIAL_PRINT_FLAG);
        secondPolynomial.print(POLYNOMIAL_PRINT_FLAG);

        PolynomialArithmetic::computeMasterMultiplicationTask(firstPolynomial, secondPolynomial, size);
    } else {
        printf("I am worker process %d.\n", rank);
        PolynomialArithmetic::runWorkerComputingRegularMultiplication(rank);
    }

    MPI_Finalize();

    return 0;
}
