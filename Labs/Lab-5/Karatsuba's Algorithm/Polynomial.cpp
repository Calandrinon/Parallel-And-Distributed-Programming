//
// Created by calandrinon on 11/27/21.
//

#include <memory>
#include "Polynomial.h"

Polynomial::Polynomial(int _degree): degree(_degree) {
    for (int index = 0; index < _degree + 1; index++)
        coefficients.push_back(0);
}

Polynomial::Polynomial(std::deque<int> _coefficients, int _degree): coefficients(std::move(_coefficients)), degree(_degree) {}

Polynomial Polynomial::copy() {
    Polynomial copiedPolynomial(this->coefficients, this->degree);
    return copiedPolynomial;
}

const std::deque<int> &Polynomial::getCoefficients() const {
    return coefficients;
}

void Polynomial::setCoefficients(const std::deque<int> &coefficients) {
    this->coefficients = coefficients;
}

int Polynomial::getDegree() const {
    return degree;
}

void Polynomial::setDegree(int degree) {
    this->degree = degree;
}

int Polynomial::getCoefficientOfDegree(int degree) const {
    return this->coefficients[degree];
}

void Polynomial::setCoefficientOfDegree(int degree, int value) {
    this->coefficients[degree] = value;
}

int Polynomial::getNumberOfCoefficients() const {
    return this->coefficients.size();
}

void Polynomial::print(bool completePrint = false) {
    if (this->degree <= 8 || completePrint) {
        for (int index = 0; index < this->degree + 1; index++) {
            if (index > 0)
                std::cout << "+ ";
            std::cout << this->coefficients[index] << "X^" << index << " ";
        }
    } else {
        for (int index = 0; index < 4; index++) {
            std::cout << this->coefficients[index] << "X^" << index << " ";
            std::cout << "+ ";
        }
        std::cout << "... ";
        for (int index = this->degree - 3; index < this->degree + 1; index++) {
            if (index > 0)
                std::cout << "+ ";
            std::cout << this->coefficients[index] << "X^" << index << " ";
        }
    }

    std::cout << "\n";
}

void Polynomial::padWithZeroes(int numberOfZeroes) {
    for (int index = 0; index < numberOfZeroes; index++) {
        this->coefficients.push_front(0);
        this->degree++;
    }
}

std::shared_ptr<Polynomial> Polynomial::copyInHeap() {
    return std::make_shared<Polynomial>(*this);
}
