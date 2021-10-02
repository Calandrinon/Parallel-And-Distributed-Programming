//
// Created by calandrinon on 10/2/21.
//

#include "BankAccount.h"

BankAccount::BankAccount(std::string owner) {
    this->owner = owner;
    this->balance = 0;
    this->operationLog = new OperationLog();
    this->creationDate = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
}

BankAccount::~BankAccount() {

}

double BankAccount::getBalance() {
    return this->balance;
}

void BankAccount::setBalance(double balance) {
    this->balance = balance;
}

OperationLog *BankAccount::getOperationLog() const {
    return operationLog;
}

void BankAccount::setOperationLog(OperationLog *operationLog) {
    BankAccount::operationLog = operationLog;
}

const std::string &BankAccount::getOwner() const {
    return owner;
}

void BankAccount::setOwner(const std::string &owner) {
    BankAccount::owner = owner;
}

time_t BankAccount::getCreationDate() const {
    return creationDate;
}

void BankAccount::setCreationDate(time_t creationDate) {
    BankAccount::creationDate = creationDate;
}

int BankAccount::getId() {
    return this->id;
}

void BankAccount::setId(int id) {
    this->id = id;
}
