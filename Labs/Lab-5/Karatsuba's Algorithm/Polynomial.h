//
// Created by calandrinon on 11/27/21.
//

#ifndef KARATSUBA_S_ALGORITHM_POLYNOMIAL_H
#define KARATSUBA_S_ALGORITHM_POLYNOMIAL_H
#include <iostream>
#include <deque>
#include <utility>
#define MAX_POLYNOMIAL_DEGREE 100

class Polynomial {
    private:
        std::deque<int> coefficients;
        int degree;

    public:
        Polynomial(int _degree);
        Polynomial(std::deque<int> _coefficients, int _degree);
        Polynomial copy();
        const std::deque<int> &getCoefficients() const;
        void setCoefficients(const std::deque<int> &coefficients);
        int getDegree() const;
        void setDegree(int degree);
        int getCoefficientOfDegree(int degree) const;
        void setCoefficientOfDegree(int degree, int value);
        int getNumberOfCoefficients() const;
        void print(bool completePrint);
        void padWithZeroes(int numberOfZeroes);
};


#endif //KARATSUBA_S_ALGORITHM_POLYNOMIAL_H
