//
// Created by calandrinon on 10/2/21.
//

#include "Operation.h"


Operation::Operation(std::string transferer, std::string transferee, double amount) {
    this->transferer = transferer;
    this->transferee = transferee;
    this->amount = amount;
    this->transactionTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
}

int Operation::getSerialNumber() const { return serialNumber;
}

void Operation::setSerialNumber(int serialNumber) {
    this->serialNumber = serialNumber;
}

time_t Operation::getTransactionTime() const {
    return transactionTime;
}

double Operation::getAmount() {
    return this->amount;
}

void Operation::setAmount(double amount) {
    this->amount = amount;
}

const std::string &Operation::getTransferer() const {
    return transferer;
}

void Operation::setTransferer(const std::string &transferer) {
    Operation::transferer = transferer;
}

const std::string &Operation::getTransferee() const {
    return transferee;
}

void Operation::setTransferee(const std::string &transferee) {
    Operation::transferee = transferee;
}

void Operation::setTransactionTime(time_t transactionTime) {
    Operation::transactionTime = transactionTime;
}
