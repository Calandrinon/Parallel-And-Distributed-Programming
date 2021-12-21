//
// Created by calandrinon on 11/27/21.
//

#include <mutex>
#include <vector>
#include <thread>
#include <chrono>
#include <future>
#include <mpi.h>
#include "PolynomialArithmetic.h"
#include "Polynomial.h"


Polynomial PolynomialArithmetic::computeRegularPolynomialMultiplication(Polynomial firstPolynomial,
                                                                      Polynomial secondPolynomial) {
    Polynomial result(firstPolynomial.getDegree() + secondPolynomial.getDegree());

    for (int firstIndex = 0; firstIndex < firstPolynomial.getDegree() + 1; firstIndex++) {
        for (int secondIndex = 0; secondIndex < secondPolynomial.getDegree() + 1; secondIndex++) {
            int previousValue = result.getCoefficientOfDegree(firstIndex + secondIndex);
            result.setCoefficientOfDegree(firstIndex + secondIndex,
                                          previousValue + firstPolynomial.getCoefficientOfDegree(firstIndex)
                                                * secondPolynomial.getCoefficientOfDegree(secondIndex));
        }
    }

    return result;
}


Polynomial PolynomialArithmetic::computeSimplePolynomialOperation(Polynomial firstPolynomial,
                                                                  Polynomial secondPolynomial, char operation) {
    int minimumDegree = std::min(firstPolynomial.getDegree(), secondPolynomial.getDegree());
    int maximumDegree = std::max(firstPolynomial.getDegree(), secondPolynomial.getDegree());
    Polynomial result(maximumDegree);
    int sign = (operation == '-' ? -1 : 1);

    for (int index = 0; index < minimumDegree + 1; index++)
        result.setCoefficientOfDegree(index,
  firstPolynomial.getCoefficientOfDegree(index) + sign * secondPolynomial.getCoefficientOfDegree(index));

    if (maximumDegree != minimumDegree) {
        if (maximumDegree == firstPolynomial.getDegree()) {
            for (int index = minimumDegree + 1; index <= maximumDegree; index++) {
                result.setCoefficientOfDegree(index, sign * firstPolynomial.getCoefficientOfDegree(index));
            }
        } else {
            for (int index = minimumDegree + 1; index <= maximumDegree; index++) {
                result.setCoefficientOfDegree(index, sign * secondPolynomial.getCoefficientOfDegree(index));
            }
        }
    }

    return result;
}

Polynomial PolynomialArithmetic::computeKaratsubaPolynomialMultiplication(Polynomial firstPolynomial,
                                                                          Polynomial secondPolynomial) {
    if (firstPolynomial.getDegree() != secondPolynomial.getDegree())
        throw std::invalid_argument("The polynomials should have the same degree.");

    if (firstPolynomial.getNumberOfCoefficients() <= 1 || secondPolynomial.getNumberOfCoefficients() <= 1)
        return computeRegularPolynomialMultiplication(firstPolynomial, secondPolynomial);

    int halfSize = firstPolynomial.getNumberOfCoefficients() / 2;

    Polynomial a(halfSize - 1), b(halfSize - 1), c(halfSize - 1), d(halfSize - 1);

    for (int index = 0; index < halfSize; index++) {
        a.setCoefficientOfDegree(index, firstPolynomial.getCoefficientOfDegree(index));
        b.setCoefficientOfDegree(index, firstPolynomial.getCoefficientOfDegree(halfSize + index));
    }

    for (int index = 0; index < halfSize; index++) {
        c.setCoefficientOfDegree(index, secondPolynomial.getCoefficientOfDegree(index));
        d.setCoefficientOfDegree(index, secondPolynomial.getCoefficientOfDegree(halfSize + index));
    }

    Polynomial ac = computeKaratsubaPolynomialMultiplication(a, c);
    Polynomial bd = computeKaratsubaPolynomialMultiplication(b, d);
    Polynomial aPlusB = computeSimplePolynomialOperation(a, b, '+');
    Polynomial cPlusD = computeSimplePolynomialOperation(c, d, '+');
    Polynomial aPlusBTimesCPlusD = computeKaratsubaPolynomialMultiplication(aPlusB, cPlusD);

    Polynomial paddedBc = bd.copy();
    paddedBc.padWithZeroes(2*halfSize);
    Polynomial aPlusBTimesCPlusDMinusBd = computeSimplePolynomialOperation(aPlusBTimesCPlusD, bd, '-');
    Polynomial partialResult = computeSimplePolynomialOperation(aPlusBTimesCPlusDMinusBd, ac, '-');
    partialResult.padWithZeroes(halfSize);

    return computeSimplePolynomialOperation(computeSimplePolynomialOperation(paddedBc, partialResult, '+'), ac, '+');
}


static void computeMasterMultiplicationTask(Polynomial& firstPolynomial, Polynomial& secondPolynomial,
                                            int numberOfProcesses) {
    int chunkSize = (firstPolynomial.getDegree() - 1) / (numberOfProcesses - 1);
    int intervalStart = 0, intervalEnd = 0;

    for (int processIndex = 1; processIndex < numberOfProcesses; processIndex++) {
        intervalStart = processIndex;
        intervalEnd = (processIndex == numberOfProcesses - 1 ? firstPolynomial.getDegree() - 1 : intervalStart + chunkSize);

        //MPI_Send(firstPolynomial, 0, )
    }

}
